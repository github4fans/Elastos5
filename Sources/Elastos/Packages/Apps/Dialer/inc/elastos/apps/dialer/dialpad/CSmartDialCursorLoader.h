
#ifndef __ELASTOS_APPS_DIALER_DIALPAD_CSMARTDIALCURSORLOADER_H__
#define __ELASTOS_APPS_DIALER_DIALPAD_CSMARTDIALCURSORLOADER_H__

#include "_Elastos_Apps_Dialer_Dialpad_CSmartDialCursorLoader.h"

namespace Elastos{
namespace Apps{
namespace Dialer {
namespace Dialpad {

/**
 * Implements a Loader<Cursor> class to asynchronously load SmartDial search results.
 */
CarClass(CSmartDialCursorLoader)
    , public AsyncTaskLoader
    , public ISmartDialCursorLoader
{
public:
    CAR_INTERFACE_DECL()

    CAR_OBJECT_DECL()

    CSmartDialCursorLoader();

    CARAPI constructor(
        /* [in] */ IContext* context);

    /**
     * Configures the query string to be used to find SmartDial matches.
     * @param query The query string user typed.
     */
    CARAPI ConfigureQuery(
        /* [in] */ const String& query);

    /**
     * Queries the SmartDial database and loads results in background.
     * @return Cursor of contacts that matches the SmartDial query.
     */
    // @Override
    CARAPI LoadInBackground(
        /* [out] */ IInterface** result);

    // @Override
    CARAPI DeliverResult(
        /* [in] */ IInterface* data);

    // @Override
    CARAPI OnCanceled(
        /* [in] */ IInterface* data);
protected:
    // @Override
    CARAPI OnStartLoading();

    // @Override
    CARAPI OnStopLoading();

    // @Override
    CARAPI OnReset();

private:
    CARAPI_(void) ReleaseResources(
        /* [in] */ ICursor* cursor);

private:
    const String TAG; // = SmartDialCursorLoader.class.getSimpleName();
    Boolean DEBUG; // = false;

    AutoPtr<IContext> mContext;

    AutoPtr<ICursor> mCursor;

    String mQuery;
    AutoPtr<ISmartDialNameMatcher> mNameMatcher;
};

} // Dialpad
} // Dialer
} // Apps
} // Elastos

#endif //__ELASTOS_APPS_DIALER_DIALPAD_CSMARTDIALCURSORLOADER_H__
