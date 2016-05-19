
#include "CUnicodeDialerKeyListenerHelper.h"
#include "UnicodeDialerKeyListener.h"

namespace Elastos{
namespace Apps{
namespace Dialer {
namespace Dialpad {

CAR_INTERFACE_IMPL(CUnicodeDialerKeyListenerHelper, Singleton, IUnicodeDialerKeyListenerHelper)

CAR_SINGLETON_IMPL(CUnicodeDialerKeyListenerHelper)

ECode CUnicodeDialerKeyListenerHelper::GetINSTANCE(
    /* [out] */ IUnicodeDialerKeyListener** instance)
{
    VALUE_NOT_NULL(instance);
    *instance = UnicodeDialerKeyListener::INSTANCE;
    REFCOUNT_ADD(*instance);
    return NOERROR;
}

} // Dialpad
} // Dialer
} // Apps
} // Elastos
