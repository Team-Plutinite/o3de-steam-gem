
#include "SteamworksSystemComponent.h"

#include <Steamworks/SteamworksTypeIds.h>

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/RTTI/BehaviorContext.h>
#include <AzCore/Serialization/EditContext.h>

namespace Steamworks
{
    AZ_COMPONENT_IMPL(SteamworksSystemComponent, "SteamworksSystemComponent",
        SteamworksSystemComponentTypeId);
   /*
    void SteamworksRequests::Reflect(AZ::ReflectContext* context) {
        AZ_Printf("Steamworks System Component", "Steamworks Requests Reflect Called")
        if (AZ::BehaviorContext* behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context)) {
           AZ_Printf("Steamworks System Component", "Reflecting Steamworks Requests");
           behaviorContext->EBus<SteamworksRequestBus>("Steamworks Requests")
                ->Attribute(AZ::Script::Attributes::Category, "Steamworks/Steam User Stats")
                ->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Common)
                ->Event("RequestCurrentStats", &SteamworksRequestBus::Events::RequestCurrentStats)
                ->Event("SetAchievement", &SteamworksRequestBus::Events::SetAchievement);
            AZ_Printf("Steamworks System Component", "Reflected Steamworks Requests")
        }
    }
    */
    void SteamworksSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        //AZ_Printf("Steamworks System Component", "Reflect Called")
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<SteamworksSystemComponent, AZ::Component>()
                ->Version(1);

            //if (AZ::EditContext* ec = serializeContext->GetEditContext()) {
            //    ec->Class<SteamworksSystemComponent>("Steamworks", "Steamworks System Component")
            //        ->ClassElement(AZ::Edit::ClassElements::EditorData, "");
            //}
            
        }
        //AZ_Printf("Steamworks System Component", "Steamworks Requests Reflect Called")
        if (AZ::BehaviorContext* behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context)) {
            AZ_Printf("Steamworks System Component", "Reflecting Steamworks Requests");
            behaviorContext->EBus<SteamworksRequestBus>("Steamworks Requests")
                ->Attribute(AZ::Script::Attributes::Category, "Steamworks/Steam User Stats")
                ->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Common)
                ->Event("RequestCurrentStats", &SteamworksRequestBus::Events::SR_RequestCurrentStats)
                ->Event("SetAchievement", &SteamworksRequestBus::Events::SR_SetAchievement);
            AZ_Printf("Steamworks System Component", "Reflected Steamworks Requests")
        }
        //SteamworksRequestBus::Handler::Reflect(context);
        //SteamworksRequests::Reflect(context);
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
            SteamworksSystemComponent::SR_RequestCurrentStats();
        }
#ifdef _RELEASE
        // Checks for steam client and initializes steam API - only in release builds
        // NOTE: appId should be already auto-set if steam API is initialized. if not, make sure you have a steam_appid.txt file in the same directory as the executable,
        // or edit the line directly below this to set the appId manually (probably good to do this anyway, but I'm not your boss).
        
        //appId = (your app id here);
        SteamAPI_RestartAppIfNecessary(uint64(appId));
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

    void SteamworksSystemComponent::OnUserStatsReceived(UserStatsReceived_t* pCallback) {
		if (appId == pCallback->m_nGameID) {
            if (pCallback->m_eResult == k_EResultOK) {
                requestStatsInitialized = true;
                AZ_Printf("Steamworks System Component", "Received stats and achievements from Steam");
            }
            else {
                AZ_Printf("Steamworks System Component", "Failed to receive stats and achievements from Steam. Error %d", pCallback->m_eResult);
            }
		}
	}

    void SteamworksSystemComponent::OnAchievementStored(UserAchievementStored_t* pCallback) {
        if (appId == pCallback->m_nGameID) {
            if (pCallback->m_nMaxProgress == 0) {
                AZ_Printf("Steamworks System Component", "Achievement %s stored", pCallback->m_rgchAchievementName);
            }
            else {
                AZ_Printf("Steamworks System Component", "Achievement %s stored with progress %d", pCallback->m_rgchAchievementName, pCallback->m_nCurProgress);
            }
        }
    }

    void SteamworksSystemComponent::OnTick([[maybe_unused]] float deltaTime, [[maybe_unused]] AZ::ScriptTimePoint time)
    {
		SteamAPI_RunCallbacks();
    }

} // namespace Steamworks
