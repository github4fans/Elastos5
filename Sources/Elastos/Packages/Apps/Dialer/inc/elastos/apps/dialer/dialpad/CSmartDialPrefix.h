#ifndef __ELASTOS_APPS_DIALER_DIALPAD_CSMARTDIALPREFIX_H__
#define __ELASTOS_APPS_DIALER_DIALPAD_CSMARTDIALPREFIX_H__

#include "_Elastos_Apps_Dialer_Dialpad_CSmartDialPrefix.h"
#include <elastos/core/Singleton.h>

namespace Elastos{
namespace Apps{
namespace Dialer {
namespace Dialpad {

CarClass(CSmartDialPrefix)
    , public Singleton
    , public ISmartDialPrefix
{
public:
    CAR_INTERFACE_DECL()

    CAR_SINGLETON_DECL()

    /** Initializes the Nanp settings, and finds out whether user is in a NANP region.*/
    CARAPI InitializeNanpSettings(
        /* [in] */ IContext* context);

    /**
     * Explicitly setting the user Nanp to the given boolean
     */
    // @VisibleForTesting
    CARAPI SetUserInNanpRegion(
        /* [in] */ Boolean userInNanpRegion);

    /**
     * Parses a contact's name into a list of separated tokens.
     *
     * @param contactName Contact's name stored in string.
     * @return A list of name tokens, for example separated first names, last name, etc.
     */
    CARAPI ParseToIndexTokens(
        /* [in] */ const String& contactName,
        /* [out] */ IArrayList** tokens);

    /**
     * Generates a list of strings that any prefix of any string in the list can be used to look
     * up the contact's name.
     *
     * @param index The contact's name in string.
     * @return A List of strings, whose prefix can be used to look up the contact.
     */
    CARAPI GenerateNamePrefixes(
        /* [in] */ const String& index,
        /* [out] */ IArrayList** prefixes);

    /**
     * Computes a list of number strings based on tokens of a given phone number. Any prefix
     * of any string in the list can be used to look up the phone number. The list include the
     * full phone number, the national number if there is a country code in the phone number, and
     * the local number if there is an area code in the phone number following the NANP format.
     * For example, if a user has phone number +41 71 394 8392, the list will contain 41713948392
     * and 713948392. Any prefix to either of the strings can be used to look up the phone number.
     * If a user has a phone number +1 555-302-3029 (NANP format), the list will contain
     * 15553023029, 5553023029, and 3023029.
     *
     * @param number String of user's phone number.
     * @return A list of strings where any prefix of any entry can be used to look up the number.
     */
    CARAPI ParseToNumberTokens(
        /* [in] */ const String& number,
        /* [out] */ IArrayList** tokens);

    /**
     * Parses a phone number to find out whether it has country code and NANP area code.
     *
     * @param number Raw phone number.
     * @return a PhoneNumberToken instance with country code, NANP code information.
     */
    CARAPI ParsePhoneNumber(
        /* [in] */ const String& number,
        /* [out] */ ISmartDialPrefixPhoneNumberTokens** result);

    CARAPI GetMap(
        /* [out] */ ISmartDialMap** map);

    /**
     * Indicates whether the given country uses NANP numbers
     * @see <a href="https://en.wikipedia.org/wiki/North_American_Numbering_Plan">
     *     https://en.wikipedia.org/wiki/North_American_Numbering_Plan</a>
     *
     * @param country ISO 3166 country code (case doesn't matter)
     * @return True if country uses NANP numbers (e.g. US, Canada), false otherwise
     */
    // @VisibleForTesting
    CARAPI IsCountryNanp(
        /* [in] */ const String& country,
        /* [out] */ Boolean* result);

    /**
     * Returns whether the user is in a region that uses Nanp format based on the sim location.
     *
     * @return Whether user is in Nanp region.
     */
    CARAPI GetUserInNanpRegion(
        /* [out] */ Boolean* result);
};

} // Dialpad
} // Dialer
} // Apps
} // Elastos

#endif //__ELASTOS_APPS_DIALER_DIALPAD_CSMARTDIALPREFIX_H__
