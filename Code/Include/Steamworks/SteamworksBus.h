
#pragma once

#include <Steamworks/SteamworksTypeIds.h>

#include <AzCore/EBus/EBus.h>
#include <AzCore/Interface/Interface.h>

namespace Steamworks
{
    class SteamworksRequests
    {
    public:
        AZ_RTTI(SteamworksRequests, SteamworksRequestsTypeId);
        virtual ~SteamworksRequests() = default;
        // Put your public methods here
    };

    class SteamworksBusTraits
        : public AZ::EBusTraits
    {
    public:
        //////////////////////////////////////////////////////////////////////////
        // EBusTraits overrides
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
        //////////////////////////////////////////////////////////////////////////
    };

    using SteamworksRequestBus = AZ::EBus<SteamworksRequests, SteamworksBusTraits>;
    using SteamworksInterface = AZ::Interface<SteamworksRequests>;

} // namespace Steamworks
