
#include "Elastos.CoreLibrary.IO.h"
#include "CSAXSource.h"
#include "CInputSource.h"

using Elastos::IO::IInputStream;
using Elastosx::Xml::Transform::Stream::IStreamSource;
using Org::Xml::Sax::CInputSource;

namespace Elastosx {
namespace Xml {
namespace Transform {
namespace Sax {

CAR_OBJECT_IMPL(CSAXSource)
CAR_INTERFACE_IMPL_2(CSAXSource, Object, ISAXSource, ISource)

CSAXSource::CSAXSource()
{ }

ECode CSAXSource::constructor(
    /* [in] */ IXMLReader* reader,
    /* [in] */ IInputSource* inputSource)
{
    mReader      = reader;
    mInputSource = inputSource;
    return NOERROR;
}

ECode CSAXSource::constructor(
    /* [in] */ IInputSource* inputSource)
{
    mInputSource = inputSource;
    return NOERROR;
}

ECode CSAXSource::SetXMLReader(
    /* [in] */ IXMLReader* reader)
{
    mReader = reader;
    return NOERROR;
}

ECode CSAXSource::GetXMLReader(
    /* [out] */ IXMLReader** reader)
{
    VALIDATE_NOT_NULL(reader);
    *reader = mReader;
    REFCOUNT_ADD(*reader);
    return NOERROR;
}

ECode CSAXSource::SetInputSource(
    /* [in] */ IInputSource* inputSource)
{
    mInputSource = inputSource;
    return NOERROR;
}

ECode CSAXSource::GetInputSource(
    /* [out] */ IInputSource** is)
{
    VALIDATE_NOT_NULL(is);
    *is = mInputSource;
    REFCOUNT_ADD(*is);
    return NOERROR;
}

ECode CSAXSource::SetSystemId(
    /* [in] */ const String& systemId)
{
    if (NULL == mInputSource) {
        CInputSource::New(systemId, (IInputSource**)&mInputSource);
    } else {
        mInputSource->SetSystemId(systemId);
    }
    return NOERROR;
}

ECode CSAXSource::GetSystemId(
    /* [out] */ String* id)
{
    VALIDATE_NOT_NULL(id);

    if (mInputSource == NULL) {
        *id = NULL;
        return NOERROR;
    }

    return mInputSource->GetSystemId(id);
}

AutoPtr<IInputSource> CSAXSource::SourceToInputSource(
    /* [in] */ ISource* source)
{
    if (ISAXSource::Probe(source)) {
        AutoPtr<IInputSource> s;
        ISAXSource::Probe(source)->GetInputSource((IInputSource**)&s);
        return s;
    } else if (IStreamSource::Probe(source)) {
        AutoPtr<IStreamSource> ss = IStreamSource::Probe(source);
        AutoPtr<IInputSource> isource;
        String id;
        ss->GetSystemId(&id);
        CInputSource::New(id, (IInputSource**)&isource);

        AutoPtr<IInputStream> is;
        ss->GetInputStream((IInputStream**)&is);
        isource->SetByteStream(is);

        AutoPtr<IReader> r;
        ss->GetReader((IReader**)&r);
        isource->SetCharacterStream(r);

        ss->GetPublicId(&id);
        isource->SetPublicId(id);

        return isource;
    }

    return NULL;
}


} // namespace Sax
} // namespace Transform
} // namespace Xml
} // namespace Elastosx
