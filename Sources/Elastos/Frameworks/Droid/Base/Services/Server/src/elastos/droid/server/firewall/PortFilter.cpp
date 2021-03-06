#include "elastos/droid/server/firewall/PortFilter.h"
#include <elastos/core/StringUtils.h>
#include "Elastos.Droid.Content.h"

using Elastos::Core::StringUtils;
using Elastos::Droid::Content::IIntent;

namespace Elastos {
namespace Droid {
namespace Server {
namespace Firewall {

//------------------------------------------------------------------------------
// PortFilter::FACTORY_FilterFactory
//------------------------------------------------------------------------------

PortFilter::FACTORY_FilterFactory::FACTORY_FilterFactory(
    /* [in] */ const String& tag)
{
    FilterFactory::constructor(tag);
}

IFilter* PortFilter::FACTORY_FilterFactory::NewFilter(
    /* in */ IXmlPullParser* parser)
{
    Int32 lowerBound = NO_BOUND;
    Int32 upperBound = NO_BOUND;

    String equalsValue;
    parser->GetAttributeValue(String(NULL), ATTR_EQUALS, &equalsValue);
    if (equalsValue != NULL) {
        Int32 value;
        value = StringUtils::ParseInt32(equalsValue);

        //throw new XmlPullParserException("Invalid port value: " + equalsValue,
        //        parser, NULL);

        lowerBound = value;
        upperBound = value;
    }

    String lowerBoundString;
    String upperBoundString;

    parser->GetAttributeValue(String(NULL), ATTR_MIN, &lowerBoundString);
    parser->GetAttributeValue(String(NULL), ATTR_MAX, &upperBoundString);

    if (lowerBoundString != NULL || upperBoundString != NULL) {
        if (equalsValue != NULL) {
            //throw new XmlPullParserException(
            //        "Port filter cannot use both equals and range filtering",
            //        parser, NULL);
            return NULL;
        }

        if (lowerBoundString != NULL) {
            lowerBound = StringUtils::ParseInt32(lowerBoundString);
            // throw new XmlPullParserException(
            //        "Invalid minimum port value: " + lowerBoundString,
            //        parser, NULL);
        }

        if (upperBoundString != NULL) {
            upperBound = StringUtils::ParseInt32(upperBoundString);

            //throw new XmlPullParserException(
            //        "Invalid maximum port value: " + upperBoundString,
            //        parser, NULL);
        }
    }

    // an empty port filter is explicitly allowed, and checks for the existence of a port
    AutoPtr<PortFilter> portFilter = new PortFilter(lowerBound, upperBound);
    REFCOUNT_ADD(portFilter);

    return (IFilter*)portFilter;
}

//=======================================================================================
// PortFilter
//=======================================================================================

CAR_INTERFACE_IMPL(PortFilter, Object, IFilter);

const AutoPtr<PortFilter::FACTORY_FilterFactory> PortFilter::FACTORY = new PortFilter::FACTORY_FilterFactory(String("port"));
const String PortFilter::ATTR_EQUALS("equals");
const String PortFilter::ATTR_MIN("min");
const String PortFilter::ATTR_MAX("max");
const Int32 PortFilter::NO_BOUND = -1;

PortFilter::PortFilter(
    /* [in] */ Int32 lowerBound,
    /* [in] */ Int32 upperBound)
{
    mLowerBound = lowerBound;
    mUpperBound = upperBound;
}

ECode PortFilter::Matches(
    /* [in] */ IIntentFirewall* ifw,
    /* [in] */ IComponentName* resolvedComponent,
    /* [in] */ IIntent* intent,
    /* [in] */ Int32 callerUid,
    /* [in] */ Int32 callerPid,
    /* [in] */ const String& resolvedType,
    /* [in] */ Int32 receivingUid,
    /* [out] */ Boolean *ret)
{
    Int32 port = -1;
    AutoPtr<IUri> uri;
    intent->GetData((IUri**)&uri);

    if (uri != NULL) {
        uri->GetPort(&port);
    }
    *ret = (port != -1 &&
            (mLowerBound == NO_BOUND || mLowerBound <= port) &&
            (mUpperBound == NO_BOUND || mUpperBound >= port));

    return NOERROR;
}

} // Firewall
} // Server
} // Droid
} // Elastos
