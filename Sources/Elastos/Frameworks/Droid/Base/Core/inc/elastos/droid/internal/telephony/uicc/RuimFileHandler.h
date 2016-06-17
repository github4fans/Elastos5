#ifndef __ELASTOS_DROID_INTERNAL_TELEPHONY_UICC_RUIMFILEHANDLER_H__
#define __ELASTOS_DROID_INTERNAL_TELEPHONY_UICC_RUIMFILEHANDLER_H__

#include "elastos/droid/ext/frameworkext.h"
#include "elastos/droid/internal/telephony/uicc/IccFileHandler.h"

// import android.os.*;
// import android.telephony.Rlog;
// import com.android.internal.telephony.CommandsInterface;

using Elastos::Droid::Internal::Telephony::ICommandsInterface;

namespace Elastos {
namespace Droid {
namespace Internal {
namespace Telephony {
namespace Uicc {

/**
  * {@hide}
  */
class RuimFileHandler
    : public IccFileHandler
    , public IRuimFileHandler
{
public:
    CAR_INTERFACE_DECL();

    RuimFileHandler();

    //***** Constructor
    CARAPI  constructor(
        /* [in] */ IUiccCardApplication* app,
        /* [in] */ const String& aid,
        /* [in] */ ICommandsInterface* ci);

    //***** Overridden from IccFileHandler
    // @Override
    CARAPI LoadEFImgTransparent(
        /* [in] */ Int32 fileid,
        /* [in] */ Int32 highOffset,
        /* [in] */ Int32 lowOffset,
        /* [in] */ Int32 length,
        /* [in] */ IMessage* onLoaded);

protected:
    // @Override
    CARAPI GetEFPath(
        /* [in] */ Int32 efid,
        /* [out] */ String* result);

    // @Override
    CARAPI Logd(
        /* [in] */ const String& msg);

    // @Override
    CARAPI Loge(
        /* [in] */ const String& msg);

public:
    static const String LOGTAG;
};

} // namespace Uicc
} // namespace Telephony
} // namespace Internal
} // namespace Droid
} // namespace Elastos

#endif // __ELASTOS_DROID_INTERNAL_TELEPHONY_UICC_RUIMFILEHANDLER_H__
