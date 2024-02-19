
#include "SteamAPISystemComponent.h"

#include <SteamAPI/SteamAPITypeIds.h>

#include <AzCore/Serialization/SerializeContext.h>

namespace SteamAPI
{
    AZ_COMPONENT_IMPL(SteamAPISystemComponent, "SteamAPISystemComponent",
        SteamAPISystemComponentTypeId);

    void SteamAPISystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<SteamAPISystemComponent, AZ::Component>()
                ->Version(0)
                ;
        }
    }

    void SteamAPISystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("SteamAPIService"));
    }

    void SteamAPISystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC_CE("SteamAPIService"));
    }

    void SteamAPISystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void SteamAPISystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }

    SteamAPISystemComponent::SteamAPISystemComponent()
    {
        if (SteamAPIInterface::Get() == nullptr)
        {
            SteamAPIInterface::Register(this);
        }
    }

    SteamAPISystemComponent::~SteamAPISystemComponent()
    {
        if (SteamAPIInterface::Get() == this)
        {
            SteamAPIInterface::Unregister(this);
        }
    }

    void SteamAPISystemComponent::Init()
    {
    }

    void SteamAPISystemComponent::Activate()
    {
        SteamAPIRequestBus::Handler::BusConnect();
        AZ::TickBus::Handler::BusConnect();
    }

    void SteamAPISystemComponent::Deactivate()
    {
        AZ::TickBus::Handler::BusDisconnect();
        SteamAPIRequestBus::Handler::BusDisconnect();
    }

    void SteamAPISystemComponent::OnTick([[maybe_unused]] float deltaTime, [[maybe_unused]] AZ::ScriptTimePoint time)
    {
    }

} // namespace SteamAPI
