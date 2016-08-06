
#ifndef __ELASTOS_DROID_CONTACTS_COMMON_LIST_PHONENUMBERPICKERFRAGMENT_H__
#define __ELASTOS_DROID_CONTACTS_COMMON_LIST_PHONENUMBERPICKERFRAGMENT_H__

#include "elastos/droid/contacts/common/ContactEntryListFragment.h"

using Elastos::Droid::Content::ILoader;
using Elastos::Droid::Net::IUri;
using Elastos::Droid::Os::IBundle;
using Elastos::Droid::View::IViewOnClickListener;
using Elastos::Droid::View::IView;
using Elastos::Droid::View::ILayoutInflater;
using Elastos::Droid::View::IViewGroup;
using Elastos::Droid::View::IMenuItem;

namespace Elastos {
namespace Droid {
namespace Contacts {
namespace Common {
namespace List {

/**
 * Fragment containing a phone number list for picking.
 */
class PhoneNumberPickerFragment
    : public ContactEntryListFragment
    , public IOnShortcutIntentCreatedListener
{
private:
    class FilterHeaderClickListener
        : public Object
        , public IViewOnClickListener
    {
    public:
        FilterHeaderClickListener(
            /* [in] */ PhoneNumberPickerFragment* host)
            : mHost(host)
        {}

        CAR_INTERFACE_DECL()

        // @Override
        CARAPI OnClick(
            /* [in] */ IView* view);

    private:
        PhoneNumberPickerFragment* mHost;
    };

public:
    PhoneNumberPickerFragment();

    CAR_INTERFACE_DECL()

    CARAPI_(void) SetDirectorySearchEnabled(
        /* [in] */ Boolean flag);

    CARAPI_(void) SetOnPhoneNumberPickerActionListener(
        /* [in] */ IOnPhoneNumberPickerActionListener* listener);

    CARAPI_(AutoPtr<IOnPhoneNumberPickerActionListener>) GetOnPhoneNumberPickerListener();

    // @Override
    CARAPI RestoreSavedState(
        /* [in] */ IBundle* savedState);

    // @Override
    CARAPI OnSaveInstanceState(
        /* [in] */ IBundle* outState);

    // @Override
    CARAPI OnOptionsItemSelected(
        /* [in] */ IMenuItem* item,
        /* [out] */ Boolean* result);

    /**
     * @param shortcutAction either {@link Intent#ACTION_CALL} or
     *            {@link Intent#ACTION_SENDTO} or null.
     */
    CARAPI_(void) SetShortcutAction(
        /* [in] */ const String& shortcutAction);

    // @Override
    CARAPI OnLoadFinished(
        /* [in] */ ILoader* loader,
        /* [in] */ IInterface* data);

    CARAPI_(void) SetUseCallableUri(
        /* [in] */ Boolean useCallableUri);

    CARAPI_(Boolean) UsesCallableUri();

    CARAPI_(void) PickPhoneNumber(
        /* [in] */ IUri* uri);

    CARAPI_(void) OnShortcutIntentCreated(
        /* [in] */ IUri* uri,
        /* [in] */ IIntent* shortcutIntent);

    // @Override
    CARAPI OnPickerResult(
        /* [in] */ IIntent* data);

    // @Override
    CARAPI OnActivityResult(
        /* [in] */ Int32 requestCode,
        /* [in] */ Int32 resultCode,
        /* [in] */ IIntent* data);

    CARAPI_(AutoPtr<IContactListFilter>) GetFilter();

    CARAPI_(void) SetFilter(
        /* [in] */ IContactListFilter* filter);

    CARAPI_(void) SetPhotoPosition(
        /* [in] */ PhotoPosition photoPosition);

protected:
    // @Override
    CARAPI OnCreateView(
        /* [in] */ ILayoutInflater* inflater,
        /* [in] */ IViewGroup* container);

    CARAPI_(Boolean) GetVisibleScrollbarEnabled();

    // @Override
    CARAPI SetSearchMode(
        /* [in] */ Boolean flag);

    // @Override
    CARAPI OnItemClick(
        /* [in] */ Int32 position,
        /* [in] */ Int64 id);

    CARAPI_(void) CacheContactInfo(
        /* [in] */ Int32 position);

    CARAPI_(String) GetPhoneNumber(
        /* [in] */ Int32 position);

    CARAPI_(AutoPtr<IUri>) GetPhoneUri(
        /* [in] */ Int32 position);

    // @Override
    CARAPI StartLoading();

    // @Override
    CARAPI_(AutoPtr<IContactEntryListAdapter>) CreateListAdapter();

    // @Override
    CARAPI_(void) ConfigureAdapter();

    CARAPI_(void) SetPhotoPosition(
        /* [in] */ IContactEntryListAdapter* adapter);

    // @Override
    CARAPI InflateView(
        /* [in] */ ILayoutInflater* inflater,
        /* [in] */ IViewGroup* container,
        /* [out] */ IView** view);

    CARAPI_(void) StartPhoneNumberShortcutIntent(
        /* [in] */ IUri* uri);

private:
    CARAPI_(void) UpdateFilterHeaderView();g1

private:
    static const String TAG;

    static const Int32 REQUEST_CODE_ACCOUNT_FILTER = 1;

    static const String KEY_SHORTCUT_ACTION;

    static const String KEY_FILTER;

    AutoPtr<IOnPhoneNumberPickerActionListener> mListener;
    String mShortcutAction;

    AutoPtr<IContactListFilter> mFilter;

    AutoPtr<IView> mAccountFilterHeader;
    /**
     * Lives as ListView's header and is shown when {@link #mAccountFilterHeader} is set
     * to View.GONE.
     */
    AutoPtr<IView> mPaddingView;

    /** true if the loader has started at least once. */
    Boolean mLoaderStarted;

    Boolean mUseCallableUri;

    PhotoPosition mPhotoPosition; //= ContactListItemView.getDefaultPhotoPosition(false /* normal/non opposite */);

    AutoPtr<IViewOnClickListener> mFilterHeaderClickListener;// = new FilterHeaderClickListener();

    friend class FilterHeaderClickListener;
};

} // List
} // Common
} // Contacts
} // Apps
} // Elastos

#endif //__ELASTOS_DROID_CONTACTS_COMMON_LIST_PHONENUMBERPICKERFRAGMENT_H__
