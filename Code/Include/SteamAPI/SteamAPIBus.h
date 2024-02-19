
#pragma once

#include <SteamAPI/SteamAPITypeIds.h>

#include <AzCore/EBus/EBus.h>
#include <AzCore/Interface/Interface.h>

namespace SteamAPI
{
    class SteamAPIRequests
    {
    public:
        AZ_RTTI(SteamAPIRequests, SteamAPIRequestsTypeId);
        virtual ~SteamAPIRequests() = default;
        // Put your public methods here
    };

    class SteamAPIBusTraits
        : public AZ::EBusTraits
    {
    public:
        //////////////////////////////////////////////////////////////////////////
        // EBusTraits overrides
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
        //////////////////////////////////////////////////////////////////////////
    };

    using SteamAPIRequestBus = AZ::EBus<SteamAPIRequests, SteamAPIBusTraits>;
    using SteamAPIInterface = AZ::Interface<SteamAPIRequests>;

} // namespace SteamAPI
