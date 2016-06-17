#ifndef __ELASTOS_APPS_DIALER_DATABASE_DIALERDATABASEHELPERHELPER_H__
#define __ELASTOS_APPS_DIALER_DATABASE_DIALERDATABASEHELPERHELPER_H__

#include "_Elastos_Apps_Dialer_Database_CDialerDatabaseHelperHelper.h"
#include <elastos/core/Singleton.h>

namespace Elastos {
namespace Apps {
namespace Dialer {
namespace Database {

CarClass(CDialerDatabaseHelperHelper)
    , public Singleton
    , public IDialerDatabaseHelperHelper
{
public:
    CAR_INTERFACE_DECL();

    CAR_SINGLETON_DECL();

    /**
     * Access function to get the singleton instance of DialerDatabaseHelper.
     */
    CARAPI GetInstance(
        /* [in] */ IContext* context,
        /* [out] */ IDialerDatabaseHelper** helper);

};

} // Database
} // Dialer
} // Apps
} // Elastos

#endif //__ELASTOS_APPS_DIALER_DATABASE_DIALERDATABASEHELPERHELPER_H__