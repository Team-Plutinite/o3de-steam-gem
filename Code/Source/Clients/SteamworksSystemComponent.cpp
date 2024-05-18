
#include "SteamworksSystemComponent.h"

#include <Steamworks/SteamworksTypeIds.h>

#include <AzCore/Serialization/SerializeContext.h>

namespace Steamworks
{
    AZ_COMPONENT_IMPL(SteamworksSystemComponent, "SteamworksSystemComponent",
        SteamworksSystemComponentTypeId);

    void SteamworksSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<SteamworksSystemComponent, AZ::Component>()
                ->Version(0)
                ;
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

    SteamworksSystemComponent::SteamworksSystemComponent()
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
        AZ::TickBus::Handler::BusConnect();
    }

    void SteamworksSystemComponent::Deactivate()
    {
        AZ::TickBus::Handler::BusDisconnect();
        SteamworksRequestBus::Handler::BusDisconnect();
    }

    void SteamworksSystemComponent::OnTick([[maybe_unused]] float deltaTime, [[maybe_unused]] AZ::ScriptTimePoint time)
    {
    }

} // namespace Steamworks
