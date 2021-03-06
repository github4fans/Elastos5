
#ifndef __ORG_APACHE_HARMONY_XNET_PROVIDER_JSSE_CSSLCONTEXTIMPL_H__
#define __ORG_APACHE_HARMONY_XNET_PROVIDER_JSSE_CSSLCONTEXTIMPL_H__

#include "_Org_Apache_Harmony_Xnet_Provider_Jsse_CSSLContextImpl.h"
#include <elastos/core/Object.h>

using Elastos::Core::Object;

namespace Org {
namespace Apache {
namespace Harmony {
namespace Xnet {
namespace Provider {
namespace Jsse {

CarClass(CSSLContextImpl)
    , public Object
{
public:
    CAR_OBJECT_DECL()

    CARAPI EngineInit(
        /* [in] */ ArrayOf<Elastosx::Net::Ssl::IKeyManager *> * pKm,
        /* [in] */ ArrayOf<Elastosx::Net::Ssl::ITrustManager *> * pTm,
        /* [in] */ ArrayOf<Elastos::Security::ISecureRandom *> * pSr);

    CARAPI EngineGetSocketFactory(
        /* [out] */ Elastosx::Net::Ssl::ISSLSocketFactory ** ppFactory);

    CARAPI EngineGetServerSocketFactory(
        /* [out] */ Elastosx::Net::Ssl::ISSLServerSocketFactory ** ppFactory);

    CARAPI EngineCreateSSLEngine(
        /* [in] */ const String& host,
        /* [in] */ Int32 port,
        /* [out] */ Elastosx::Net::Ssl::ISSLEngine ** ppEngine);

    CARAPI EngineCreateSSLEngineEx(
        /* [out] */ Elastosx::Net::Ssl::ISSLEngine ** ppEngine);

    CARAPI EngineGetServerSessionContext(
        /* [out] */ Elastosx::Net::Ssl::ISSLSessionContext ** ppContext);

    CARAPI EngineGetClientSessionContext(
        /* [out] */ Elastosx::Net::Ssl::ISSLSessionContext ** ppContext);

    CARAPI EngineGetDefaultSSLParameters(
        /* [out] */ Elastosx::Net::Ssl::ISSLParameters ** ppParam);

    CARAPI EngineGetSupportedSSLParameters(
        /* [out] */ Elastosx::Net::Ssl::ISSLParameters ** ppParam);

    CARAPI constructor();

private:
    // TODO: Add your private member variables here.
};

}
}
}
}
}
}

#endif // __ORG_APACHE_HARMONY_XNET_PROVIDER_JSSE_CSSLCONTEXTIMPL_H__
