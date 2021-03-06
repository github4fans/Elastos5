
#include "CSSLContextImpl.h"

namespace Org {
namespace Apache {
namespace Harmony {
namespace Xnet {
namespace Provider {
namespace Jsse {

CAR_OBJECT_IMPL(CSSLContextImpl)

ECode CSSLContextImpl::EngineInit(
    /* [in] */ ArrayOf<Elastosx::Net::Ssl::IKeyManager *> * pKm,
    /* [in] */ ArrayOf<Elastosx::Net::Ssl::ITrustManager *> * pTm,
    /* [in] */ ArrayOf<Elastos::Security::ISecureRandom *> * pSr)
{
    // TODO: Add your code here
    return E_NOT_IMPLEMENTED;
}

ECode CSSLContextImpl::EngineGetSocketFactory(
    /* [out] */ Elastosx::Net::Ssl::ISSLSocketFactory ** ppFactory)
{
    // TODO: Add your code here
    return E_NOT_IMPLEMENTED;
}

ECode CSSLContextImpl::EngineGetServerSocketFactory(
    /* [out] */ Elastosx::Net::Ssl::ISSLServerSocketFactory ** ppFactory)
{
    // TODO: Add your code here
    return E_NOT_IMPLEMENTED;
}

ECode CSSLContextImpl::EngineCreateSSLEngine(
    /* [in] */ const String& host,
    /* [in] */ Int32 port,
    /* [out] */ Elastosx::Net::Ssl::ISSLEngine ** ppEngine)
{
    // TODO: Add your code here
    return E_NOT_IMPLEMENTED;
}

ECode CSSLContextImpl::EngineCreateSSLEngineEx(
    /* [out] */ Elastosx::Net::Ssl::ISSLEngine ** ppEngine)
{
    // TODO: Add your code here
    return E_NOT_IMPLEMENTED;
}

ECode CSSLContextImpl::EngineGetServerSessionContext(
    /* [out] */ Elastosx::Net::Ssl::ISSLSessionContext ** ppContext)
{
    // TODO: Add your code here
    return E_NOT_IMPLEMENTED;
}

ECode CSSLContextImpl::EngineGetClientSessionContext(
    /* [out] */ Elastosx::Net::Ssl::ISSLSessionContext ** ppContext)
{
    // TODO: Add your code here
    return E_NOT_IMPLEMENTED;
}

ECode CSSLContextImpl::EngineGetDefaultSSLParameters(
    /* [out] */ Elastosx::Net::Ssl::ISSLParameters ** ppParam)
{
    // TODO: Add your code here
    return E_NOT_IMPLEMENTED;
}

ECode CSSLContextImpl::EngineGetSupportedSSLParameters(
    /* [out] */ Elastosx::Net::Ssl::ISSLParameters ** ppParam)
{
    // TODO: Add your code here
    return E_NOT_IMPLEMENTED;
}

ECode CSSLContextImpl::constructor()
{
    // TODO: Add your code here
    return E_NOT_IMPLEMENTED;
}

}
}
}
}
}
}

