
#include "SteamworksSystemComponent.h"

#include <Steamworks/SteamworksTypeIds.h>

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/RTTI/BehaviorContext.h>
#include <AzCore/Serialization/EditContext.h>

namespace Steamworks
{
    class SteamUserStatsNotificationBusBehaviorHandler :
        public SteamUserStatsNotificationBus::Handler,
        public AZ::BehaviorEBusHandler
    {
    public:
        ~SteamUserStatsNotificationBusBehaviorHandler() override = default;

        AZ_EBUS_BEHAVIOR_BINDER(SteamUserStatsNotificationBusBehaviorHandler, SteamUserStatsNotificationsTypeId,
            AZ::SystemAllocator,
            OnUserStatsReceived,
            OnAchievementStored
        );

        void OnUserStatsReceived() override {
        	Call(FN_OnUserStatsReceived);
        };
        void OnAchievementStored() override {
        	Call(FN_OnAchievementStored);
        };

        static void Reflect(AZ::ReflectContext* context) {
            if (AZ::BehaviorContext* behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context)) {
                behaviorContext->EBus<SteamUserStatsNotificationBus>("Steam User Stats Notifications")
					->Attribute(AZ::Script::Attributes::Category, "Steamworks/Steam User Stats")
					->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Common)
					->Handler<SteamUserStatsNotificationBusBehaviorHandler>();
            }
        };
    };

    class SteamFriendsNotificationBusBehaviorHandler :
        public SteamFriendsNotificationBus::Handler,
        public AZ::BehaviorEBusHandler
    { 
        public:
		~SteamFriendsNotificationBusBehaviorHandler() override = default;

		AZ_EBUS_BEHAVIOR_BINDER(SteamFriendsNotificationBusBehaviorHandler, SteamFriendsNotificationsTypeId,
            			AZ::SystemAllocator,
            			OnGameOverlayActivated
        		);

		void OnGameOverlayActivated(bool enabled) override {
			Call(FN_OnGameOverlayActivated, enabled);
		};

		static void Reflect(AZ::ReflectContext* context) {
            if (AZ::BehaviorContext* behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context)) {
				behaviorContext->EBus<SteamFriendsNotificationBus>("Steam Friends Notifications")
					->Attribute(AZ::Script::Attributes::Category, "Steamworks/Steam Friends")
					->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Common)
					->Handler<SteamFriendsNotificationBusBehaviorHandler>();
			}
		}
	};
    

    AZ_COMPONENT_IMPL(SteamworksSystemComponent, "SteamworksSystemComponent",
        SteamworksSystemComponentTypeId);
   
    void SteamworksSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        //AZ_Printf("Steamworks System Component", "Reflect Called")
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<SteamworksSystemComponent, AZ::Component>()
                ->Version(1);
            
        }
        //AZ_Printf("Steamworks System Component", "Steamworks Requests Reflect Called")
        if (AZ::BehaviorContext* behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context)) {
            behaviorContext->EBus<SteamworksRequestBus>("Steamworks Requests")
                ->Attribute(AZ::Script::Attributes::Category, "Steamworks")
                ->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Common);

            behaviorContext->EBus<SteamUserStatsRequestBus>("SteamUserStats Requests")
                ->Attribute(AZ::Script::Attributes::Category, "Steamworks/Steam User Stats")
                ->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Common)
                ->Event("RequestCurrentStats", &SteamUserStatsRequestBus::Events::SR_RequestCurrentStats)
                ->Event("SetAchievement", &SteamUserStatsRequestBus::Events::SR_SetAchievement)
                ->Event("SteamInitialized", &SteamUserStatsRequestBus::Events::SR_SteamInitialized);

            behaviorContext->EBus<SteamUserRequestBus>("SteamUser Requests")
                ->Attribute(AZ::Script::Attributes::Category, "Steamworks/Steam User")
				->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Common)
				->Event("GetAccountID", &SteamUserRequestBus::Events::SR_GetAccountID);

			behaviorContext->EBus<SteamFriendsRequestBus>("SteamFriends Requests")
				->Attribute(AZ::Script::Attributes::Category, "Steamworks/Steam Friends")
				->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Common)
				->Event("SetRichPresence", &SteamFriendsRequestBus::Events::SR_SetRichPresence);

            SteamUserStatsNotificationBusBehaviorHandler::Reflect(context);
            SteamFriendsNotificationBusBehaviorHandler::Reflect(context);
        }
    }

    

    void SteamworksSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("SteamworksService"));
    }

    void SteamworksSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC_CE("SteamworksService"));
    }

    void SteamworksSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void SteamworksSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }

    SteamworksSystemComponent::SteamworksSystemComponent() :
        m_CallbackUserStatsReceived(this, &SteamworksSystemComponent::OnUserStatsReceived),
        m_CallbackAchievementStored(this, &SteamworksSystemComponent::OnAchievementStored),
        m_CallbackGameOverlayActivated(this, &SteamworksSystemComponent::OnGameOverlayActivated),
        appId(0),
        requestStatsInitialized(false)
    {
        if (SteamworksInterface::Get() == nullptr)
        {
            SteamworksInterface::Register(this);
        }

    }

    SteamworksSystemComponent::~SteamworksSystemComponent()
    {
        if (SteamworksInterface::Get() == this)
        {
            SteamworksInterface::Unregister(this);
        }
    }

    void SteamworksSystemComponent::Init()
    {
    }

    void SteamworksSystemComponent::Activate()
    {
        SteamworksRequestBus::Handler::BusConnect();

        // Initialize steam API, and if it initializes, set everything up, get the appID, and request current stats for the user
        steamAPIInitialized = false;
        steamAPIInitialized = SteamAPI_Init();
        if (steamAPIInitialized) {
            AZ_Printf("Steamworks System Component", "Steam API initialized")
            appId = SteamUtils()->GetAppID();
            AZ_Printf("Steamworks System Component", "App ID: %d", appId)
            m_pSteamUser = SteamUser();
            m_pSteamUserStats = SteamUserStats();
            m_pSteamFriends = SteamFriends();
            SteamworksSystemComponent::SR_RequestCurrentStats();
        }
#ifdef _RELEASE
        // Checks for steam client and initializes steam API - only in release builds
        // NOTE: appId should be already auto-set if steam API is initialized. if not, make sure you have a steam_appid.txt file in the same directory as the executable,
        // or edit the line directly below this to set the appId manually (probably good to do this anyway, but I'm not your boss).
        
        //appId = (your app id here);
        SteamAPI_RestartAppIfNecessary(uint32(appId));
#endif 
        AZ::TickBus::Handler::BusConnect();
    }

    void SteamworksSystemComponent::Deactivate()
    {
        AZ::TickBus::Handler::BusDisconnect();
        SteamworksRequestBus::Handler::BusDisconnect();
        if (steamAPIInitialized) {
			SteamAPI_Shutdown();
		}
    }

    bool SteamworksSystemComponent::SR_RequestCurrentStats() {
        if (m_pSteamUserStats == NULL || m_pSteamUser == NULL) {
            return false;
        }
        if (!m_pSteamUser->BLoggedOn()) {
            return false;
        }
        return m_pSteamUserStats->RequestCurrentStats();
    }

    bool SteamworksSystemComponent::SR_SetAchievement(const char* name)  {
        // If a call back has been received, then we can set the achievement
        if (requestStatsInitialized) {
            m_pSteamUserStats->SetAchievement(name);
            return m_pSteamUserStats->StoreStats();
        }
        else {
			AZ_Printf("Steamworks System Component", "Failed to set achievement %s. Stats not initialized", name);
		}
        return false;
    }

    unsigned long long SteamworksSystemComponent::SR_GetAccountID() {
        if (requestStatsInitialized) {
		    return m_pSteamUser->GetSteamID().ConvertToUint64();
		}
		else {
			AZ_Printf("Steamworks System Component", "Failed to get Account ID. Stats not initialized");
        }
        return 0;
	}

    bool SteamworksSystemComponent::SR_SetRichPresence(const char* pchKey, const char* pchValue) {
        if (steamAPIInitialized){
            AZ_Printf("Steamworks System Component", "Rich presence key set to %s", pchKey);
            AZ_Printf("Steamworks System Component", "Rich presence value set to %s", pchValue)
            // Commented for SoM testing
		    return m_pSteamFriends->SetRichPresence(pchKey, pchValue);
            //return true;
        }
        else {
            AZ_Printf("Steamworks System Component", "Failed to set rich presence. Steam API not initialized");
			return false;
        }
    }

    bool SteamworksSystemComponent::SR_SteamInitialized() {
        return requestStatsInitialized;
    }

    void SteamworksSystemComponent::OnUserStatsReceived(UserStatsReceived_t* pCallback) {
		if (appId == pCallback->m_nGameID) {
            if (pCallback->m_eResult == k_EResultOK) {
                requestStatsInitialized = true;
                AZ_Printf("Steamworks System Component", "Received stats and achievements from Steam");
                Steamworks::SteamUserStatsNotificationBus::Broadcast(&Steamworks::SteamUserStatsNotificationBus::Events::OnUserStatsReceived);
            }
            else {
                AZ_Printf("Steamworks System Component", "Failed to receive stats and achievements from Steam. Error %d", pCallback->m_eResult);
            }
		}
	}

    void SteamworksSystemComponent::OnAchievementStored(UserAchievementStored_t* pCallback) {
        if (appId == pCallback->m_nGameID) {
            if (pCallback->m_nMaxProgress == 0) { // if there is no progress with the achievement, just set it as achieved
                AZ_Printf("Steamworks System Component", "Achievement %s stored", pCallback->m_rgchAchievementName);
                Steamworks::SteamUserStatsNotificationBus::Broadcast(&Steamworks::SteamUserStatsNotificationBus::Events::OnAchievementStored);
            }
            else {
                AZ_Printf("Steamworks System Component", "Achievement %s stored with progress %d", pCallback->m_rgchAchievementName, pCallback->m_nCurProgress);
            }
        }
    }

    void SteamworksSystemComponent::OnGameOverlayActivated(GameOverlayActivated_t* pCallback) {
        if (appId == pCallback->m_nAppID) {
            Steamworks::SteamFriendsNotificationBus::Broadcast(&Steamworks::SteamFriendsNotificationBus::Events::OnGameOverlayActivated, pCallback->m_bActive);
        }
    }

    void SteamworksSystemComponent::OnTick([[maybe_unused]] float deltaTime, [[maybe_unused]] AZ::ScriptTimePoint time)
    {
		SteamAPI_RunCallbacks();
    }

} // namespace Steamworks
