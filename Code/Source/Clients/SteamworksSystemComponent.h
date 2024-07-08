
#pragma once

#include <AzCore/Component/Component.h>
#include <AzCore/Component/TickBus.h>
#include <Steamworks/SteamworksBus.h>

#include "Steam/sdk/public/steam/steam_api.h"

namespace Steamworks
{
    class SteamworksSystemComponent
        : public AZ::Component
        , protected SteamworksRequestBus::Handler
        , protected SteamUserStatsRequestBus::Handler
        , protected SteamUserRequestBus::Handler
        , protected SteamFriendsRequestBus::Handler
        , public AZ::TickBus::Handler
    {
    public:
        AZ_COMPONENT_DECL(SteamworksSystemComponent);

        static void Reflect(AZ::ReflectContext* context);

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        SteamworksSystemComponent();
        ~SteamworksSystemComponent();

        STEAM_CALLBACK(SteamworksSystemComponent, OnUserStatsReceived, UserStatsReceived_t, m_CallbackUserStatsReceived);
        STEAM_CALLBACK(SteamworksSystemComponent, OnAchievementStored, UserAchievementStored_t, m_CallbackAchievementStored);
        STEAM_CALLBACK(SteamworksSystemComponent, OnGameOverlayActivated, GameOverlayActivated_t, m_CallbackGameOverlayActivated);

        struct SteamAchievement {
            int m_eAchievementID;
            const char* m_pchAchievementID;
            char m_rgchName[128];
            char m_rgchDescription[256];
            bool m_bAchieved;
            int m_iIconImage;
        };

        

    protected:
        ////////////////////////////////////////////////////////////////////////
        // SteamworksRequestBus interface implementation

        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // AZ::Component interface implementation
        void Init() override;
        void Activate() override;
        void Deactivate() override;
        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // AZTickBus interface implementation
        void OnTick(float deltaTime, AZ::ScriptTimePoint time) override;
        ////////////////////////////////////////////////////////////////////////

        bool steamAPIInitialized;
        bool requestStatsInitialized;

        uint32 appId;
        ISteamUser* m_pSteamUser;
        ISteamUserStats* m_pSteamUserStats;
        ISteamFriends* m_pSteamFriends;

        // SteamworksRequestBus::Handler interface implementation
        
        //SteamUserStatsRequestBus::Handler interface implementation

        bool SR_RequestCurrentStats() override;
        //bool GetAchievement(const char* name, bool* achieved) override;
        bool SR_SetAchievement(const char* name) override;
        //bool ClearAchievement(const char* name) override;
        //bool GetAchievementProgressLimitsInt32(const char* name, int32* minProgress, int32* maxProgress) override;
        //bool GetAchievementProgressLimitsFloat(const char* name, float* minProgress, float* maxProgress) override;
        bool SR_SteamInitialized() override;

        //SteamUserRequestBus::Handler interface implementation

        unsigned long long SR_GetAccountID() override;

        //SteamFriendsRequestBus::handler interface implementation
        bool SR_SetRichPresence(const char* pchKey, const char* pchValue) override;
    };

} // namespace Steamworks
