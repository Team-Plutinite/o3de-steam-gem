#pragma once

#include <Steamworks/SteamworksTypeIds.h>

#include <AzCore/EBus/EBus.h>
#include <AzCore/Interface/Interface.h>
#include <AzCore/RTTI/BehaviorContext.h>


namespace Steamworks
{
    class SteamworksRequests
    {
    public:
        AZ_RTTI(SteamworksRequests, SteamworksRequestsTypeId);
        virtual ~SteamworksRequests() = default;
        // Put your public methods here
        
        // Prefacing everything with SR_ ("Steamworks Requests") to make sure no steam_api or etc conflicts
        static void Reflect(AZ::ReflectContext* context);
    };

    class SteamUserStatsRequests 
    {
        public:
            AZ_RTTI(SteamUserStatsRequests, SteamUserStatsRequestsTypeId);
			virtual ~SteamUserStatsRequests() = default;
			// Put your public methods here
            // steamuserstats Requests
            //virtual bool GetAchievement(const char *name, bool *achieved) = 0;
            virtual bool SR_SetAchievement(const char* name) = 0;
            //virtual bool ClearAchievement(const char *name) = 0;
            //virtual bool GetAchievementProgressLimitsInt32(const char *name, int32 *minProgress, int32 *maxProgress) = 0;
            //virtual bool GetAchievementProgressLimitsFloat(const char *name, float *minProgress, float *maxProgress) = 0;
            virtual bool SR_SteamInitialized() = 0;

            static void Reflect(AZ::ReflectContext* context);

    };

    class SteamUserRequests 
    {
        public:
            AZ_RTTI(SteamUserRequests, SteamUserRequestsTypeId);
			virtual ~SteamUserRequests() = default;
			// Put your public methods here
			// steamuser Requests
			virtual unsigned long long SR_GetAccountID() = 0;

			static void Reflect(AZ::ReflectContext* context);
    };

    class SteamFriendsRequests 
    {
        public:
            AZ_RTTI(SteamFriendsRequests, SteamFriendsRequestsTypeId);
            virtual ~SteamFriendsRequests() = default;
            // Put your public methods here
            // steamfriends Requests
            virtual bool SR_SetRichPresence(const char* pchKey, const char* pchValue) = 0;

            static void Reflect(AZ::ReflectContext* context);
    };

    class SteamUserStatsNotifications 
        : public AZ::EBusTraits 
    {
        public:
            virtual ~SteamUserStatsNotifications() = default;
            static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;
            static const AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;

            // currently these just ping if it was successful
            virtual void OnUserStatsReceived() {};
            virtual void OnAchievementStored() {};
    };


    class SteamFriendsNotifications
        : public AZ::EBusTraits
    {
		public:
			virtual ~SteamFriendsNotifications() = default;
			static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;
			static const AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;

			virtual void OnGameOverlayActivated(bool /*enabled*/) {};
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
    using SteamUserStatsRequestBus = AZ::EBus<SteamUserStatsRequests, SteamworksBusTraits>;
    using SteamUserRequestBus = AZ::EBus<SteamUserRequests, SteamworksBusTraits>;
    using SteamFriendsRequestBus = AZ::EBus<SteamFriendsRequests, SteamworksBusTraits>;
    using SteamUserStatsNotificationBus = AZ::EBus<SteamUserStatsNotifications>;
    using SteamFriendsNotificationBus = AZ::EBus<SteamFriendsNotifications>;
    using SteamworksInterface = AZ::Interface<SteamworksRequests>;

} // namespace Steamworks
