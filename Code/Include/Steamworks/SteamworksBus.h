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
        

        // Prefacing everything with SR_ ("Steamworks Requests") to make sure no steam_api or etc conflicts
        // Eventually probably split this into multiple buses by header file, but as of rn this is fine cause so little is testable/implemented (testable is what i'm worried about)

        // steamuserstats Requests
        // Achievements (currently the only thing supported because our game only uses achievements)
        virtual bool SR_RequestCurrentStats() = 0;
        //virtual bool GetAchievement(const char *name, bool *achieved) = 0;
        virtual bool SR_SetAchievement(const char *name) = 0;
        //virtual bool ClearAchievement(const char *name) = 0;
        //virtual bool GetAchievementProgressLimitsInt32(const char *name, int32 *minProgress, int32 *maxProgress) = 0;
        //virtual bool GetAchievementProgressLimitsFloat(const char *name, float *minProgress, float *maxProgress) = 0;
        virtual bool SR_SteamInitialized() = 0;

        //steamuser Requests
        virtual CSteamID SR_GetSteamID() = 0;
        virtual uint64 SR_GetAccountID() = 0;

        static void Reflect(AZ::ReflectContext* context);
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
