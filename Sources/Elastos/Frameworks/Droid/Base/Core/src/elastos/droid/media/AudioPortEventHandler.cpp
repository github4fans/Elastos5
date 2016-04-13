#include "elastos/droid/media/AudioPortEventHandler.h"
#include "elastos/droid/os/Looper.h"
#include <elastos/core/AutoLock.h>
#include <elastos/utility/logging/Logger.h>

#include <media/AudioSystem.h>

using Elastos::Droid::Os::IMessage;
using Elastos::Droid::Os::Looper;
using Elastos::Utility::Logging::Logger;
using Elastos::Utility::CArrayList;

namespace Elastos {
namespace Droid {
namespace Media {

static const String TAG("AudioPortEventHandler");

const Int32 AudioPortEventHandler::AUDIOPORT_EVENT_PORT_LIST_UPDATED = 1;
const Int32 AudioPortEventHandler::AUDIOPORT_EVENT_PATCH_LIST_UPDATED = 2;
const Int32 AudioPortEventHandler::AUDIOPORT_EVENT_SERVICE_DIED = 3;
const Int32 AudioPortEventHandler::AUDIOPORT_EVENT_NEW_LISTENER = 4;

//===================================================================================
//              JNIAudioPortCallback
//===================================================================================

// ----------------------------------------------------------------------------
// ref-counted object for callbacks
class JNIAudioPortCallback: public android::AudioSystem::AudioPortCallback
{
public:
    JNIAudioPortCallback(IWeakReference* weak_thiz);
    ~JNIAudioPortCallback();

    virtual void onAudioPortListUpdate();
    virtual void onAudioPatchListUpdate();
    virtual void onServiceDied();

private:
    void sendEvent(int event);

    AutoPtr<IWeakReference>     mObject;    // Weak ref to AudioPortEventHandlerDelegate Java object to call on
};

JNIAudioPortCallback::JNIAudioPortCallback(IWeakReference* weak_thiz)
{
    // We use a weak reference so the SoundTriggerModule object can be garbage collected.
    // The reference is only used as a proxy for callbacks.
    mObject  = weak_thiz;
}

JNIAudioPortCallback::~JNIAudioPortCallback()
{
}

void JNIAudioPortCallback::sendEvent(int event)
{
    AudioPortEventHandler::PostEventFromNative(mObject, event, 0, 0, NULL);
}

void JNIAudioPortCallback::onAudioPortListUpdate()
{
    sendEvent(AudioPortEventHandler::AUDIOPORT_EVENT_PORT_LIST_UPDATED);
}

void JNIAudioPortCallback::onAudioPatchListUpdate()
{
    sendEvent(AudioPortEventHandler::AUDIOPORT_EVENT_PATCH_LIST_UPDATED);
}

void JNIAudioPortCallback::onServiceDied()
{
    sendEvent(AudioPortEventHandler::AUDIOPORT_EVENT_SERVICE_DIED);
}

//===================================================================================
//              AudioPortEventHandler::EventHandler
//===================================================================================

ECode AudioPortEventHandler::EventHandler::HandleMessage(
    /* [in] */ IMessage* msg)
{
    AutoPtr<IArrayList> listeners;
    synchronized(this) {
        Int32 what;
        msg->GetWhat(&what);
        if (what == AUDIOPORT_EVENT_NEW_LISTENER) {
            CArrayList::New((IArrayList**)&listeners);
            AutoPtr<IInterface> obj;
            msg->GetObj((IInterface**)&obj);
            Boolean b;
            mHost->mListeners->Contains(obj, &b);
            if (b) {
                listeners->Add(obj);
            }
        } else {
            listeners = mHost->mListeners;
        }
    }
    Boolean b;
    if (listeners == NULL || listeners->IsEmpty(&b), b) {
        return NOERROR;
    }
    // reset audio port cache if the event corresponds to a change coming
    // from audio policy service or if mediaserver process died.
    Int32 what;
    msg->GetWhat(&what);
    if (what == AUDIOPORT_EVENT_PORT_LIST_UPDATED ||
            what == AUDIOPORT_EVENT_PATCH_LIST_UPDATED ||
            what == AUDIOPORT_EVENT_SERVICE_DIED) {
        Int32 gen;
        mHost->mAudioManager->ResetAudioPortGeneration(&gen);
    }
    AutoPtr<IArrayList> ports;
    CArrayList::New((IArrayList**)&ports);
    AutoPtr<IArrayList> patches;
    CArrayList::New((IArrayList**)&patches);
    if (what != AUDIOPORT_EVENT_SERVICE_DIED) {
        Int32 status;
        mHost->mAudioManager->UpdateAudioPortCache(ports, patches, &status);
        if (status != IAudioManager::SUCCESS) {
            return NOERROR;
        }
    }

    switch (what) {
    case AUDIOPORT_EVENT_NEW_LISTENER:
    case AUDIOPORT_EVENT_PORT_LIST_UPDATED: {
        // AudioPort[] portList = ports.toArray(new AudioPort[0]);
        AutoPtr<ArrayOf<IInterface*> > objs = ArrayOf<IInterface*>::Alloc(0);
        AutoPtr<ArrayOf<IInterface*> > array;
        ports->ToArray(objs, (ArrayOf<IInterface*>**)&array);
        AutoPtr<ArrayOf<IAudioPort*> > portList = ArrayOf<IAudioPort*>::Alloc(array->GetLength());
        for (Int32 i = 0; i < array->GetLength(); i++) {
            portList->Set(i, IAudioPort::Probe(((*array)[i])));
        }

        Int32 num;
        listeners->GetSize(&num);
        for (Int32 i = 0; i < num; i++) {
            AutoPtr<IInterface> obj;
            listeners->Get(i, ((IInterface**)&obj));
            IAudioManagerOnAudioPortUpdateListener::Probe(obj)->OnAudioPortListUpdate(portList);
        }
        if (what == AUDIOPORT_EVENT_PORT_LIST_UPDATED) {
            break;
        }
        // FALL THROUGH
    }
    case AUDIOPORT_EVENT_PATCH_LIST_UPDATED: {
        // AudioPatch[] patchList = patches.toArray(new AudioPatch[0]);
        AutoPtr<ArrayOf<IInterface*> > objs = ArrayOf<IInterface*>::Alloc(0);
        AutoPtr<ArrayOf<IInterface*> > array;
        patches->ToArray(objs, (ArrayOf<IInterface*>**)&array);
        AutoPtr<ArrayOf<IAudioPatch*> > patchList = ArrayOf<IAudioPatch*>::Alloc(array->GetLength());
        for (Int32 i = 0; i < array->GetLength(); i++) {
            patchList->Set(i, IAudioPatch::Probe(((*array)[i])));
        }

        Int32 num;
        listeners->GetSize(&num);
        for (Int32 i = 0; i < num; i++) {
            AutoPtr<IInterface> obj;
            listeners->Get(i, ((IInterface**)&obj));
            IAudioManagerOnAudioPortUpdateListener::Probe(obj)->OnAudioPatchListUpdate(patchList);
        }
        break;
    }
    case AUDIOPORT_EVENT_SERVICE_DIED: {
        Int32 num;
        listeners->GetSize(&num);
        for (Int32 i = 0; i < num; i++) {
            AutoPtr<IInterface> obj;
            listeners->Get(i, ((IInterface**)&obj));
            IAudioManagerOnAudioPortUpdateListener::Probe(obj)->OnServiceDied();
        }
        break;
    }
    default:
        break;
    }
    return NOERROR;
}

//===================================================================================
//              AudioPortEventHandler
//===================================================================================
AudioPortEventHandler::AudioPortEventHandler()
{
}

AudioPortEventHandler::~AudioPortEventHandler()
{
    NativeFinalize();
}

ECode AudioPortEventHandler::constructor(
    /* [in] */ IAudioManager* audioManager)
{
    mAudioManager = audioManager;
    CArrayList::New((IArrayList**)&mListeners);

    // find the looper for our new event handler
    AutoPtr<ILooper> looper = Looper::GetMainLooper();
    if (looper != NULL) {
        mHandler = new EventHandler(this, looper);
    }

    AutoPtr<IWeakReference> wr;
    GetWeakReference((IWeakReference**)&wr);
    NativeSetup(wr);
    return NOERROR;
}

ECode AudioPortEventHandler::RegisterListener(
    /* [in] */ IAudioManagerOnAudioPortUpdateListener* l)
{
    synchronized(this) {
        mListeners->Add(l);
    }
    if (mHandler != NULL) {
        AutoPtr<IMessage> m;
        mHandler->ObtainMessage(AUDIOPORT_EVENT_NEW_LISTENER, 0, 0, l, (IMessage**)&m);
        Boolean b;
        mHandler->SendMessage(m, &b);
    }
    return NOERROR;
}

ECode AudioPortEventHandler::UnregisterListener(
    /* [in] */ IAudioManagerOnAudioPortUpdateListener* l)
{
    synchronized(this) {
        mListeners->Remove(l);
    }
    return NOERROR;
}

ECode AudioPortEventHandler::Handler(
    /* [out] */ IHandler** result)
{
    VALIDATE_NOT_NULL(result)
    *result = mHandler;
    REFCOUNT_ADD(*result)
    return NOERROR;
}

ECode AudioPortEventHandler::NativeSetup(
    /* [in] */ IWeakReference* weak_this)
{
    Logger::V(TAG, "eventHandlerSetup");

    android::sp<JNIAudioPortCallback> callback = new JNIAudioPortCallback(weak_this);
    android::AudioSystem::setAudioPortCallback(callback);
    return NOERROR;
}

ECode AudioPortEventHandler::NativeFinalize()
{
    Logger::V(TAG, "eventHandlerFinalize");

    android::sp<JNIAudioPortCallback> callback;
    android::AudioSystem::setAudioPortCallback(callback);
    return NOERROR;
}

ECode AudioPortEventHandler::PostEventFromNative(
    /* [in] */ IWeakReference* module_ref,
    /* [in] */ Int32 what,
    /* [in] */ Int32 arg1,
    /* [in] */ Int32 arg2,
    /* [in] */ IInterface* obj)
{
    AutoPtr<IInterface> o;
    module_ref->Resolve(EIID_IInterface, (IInterface**)&o);
    AudioPortEventHandler* eventHandler = (AudioPortEventHandler*)IObject::Probe(o);

    if (eventHandler == NULL) {
        return NOERROR;
    }

    if (eventHandler != NULL) {
        AutoPtr<IHandler> handler;
        eventHandler->Handler((IHandler**)&handler);
        if (handler != NULL) {
            AutoPtr<IMessage> m;
            handler->ObtainMessage(what, arg1, arg2, obj, (IMessage**)&m);
            Boolean b;
            handler->SendMessage(m, &b);
        }
    }
    return NOERROR;
}

} // namespace Media
} // namepsace Droid
} // namespace Elastos
