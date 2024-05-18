
#include <AzCore/Serialization/SerializeContext.h>
#include "SteamworksEditorSystemComponent.h"

#include <Steamworks/SteamworksTypeIds.h>

namespace Steamworks
{
    AZ_COMPONENT_IMPL(SteamworksEditorSystemComponent, "SteamworksEditorSystemComponent",
        SteamworksEditorSystemComponentTypeId, BaseSystemComponent);

    void SteamworksEditorSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<SteamworksEditorSystemComponent, SteamworksSystemComponent>()
                ->Version(0);
        }
    }

    SteamworksEditorSystemComponent::SteamworksEditorSystemComponent() = default;

    SteamworksEditorSystemComponent::~SteamworksEditorSystemComponent() = default;

    void SteamworksEditorSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        BaseSystemComponent::GetProvidedServices(provided);
        provided.push_back(AZ_CRC_CE("SteamworksEditorService"));
    }

    void SteamworksEditorSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        BaseSystemComponent::GetIncompatibleServices(incompatible);
        incompatible.push_back(AZ_CRC_CE("SteamworksEditorService"));
    }

    void SteamworksEditorSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        BaseSystemComponent::GetRequiredServices(required);
    }

    void SteamworksEditorSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
        BaseSystemComponent::GetDependentServices(dependent);
    }

    void SteamworksEditorSystemComponent::Activate()
    {
        SteamworksSystemComponent::Activate();
        AzToolsFramework::EditorEvents::Bus::Handler::BusConnect();
    }

    void SteamworksEditorSystemComponent::Deactivate()
    {
        AzToolsFramework::EditorEvents::Bus::Handler::BusDisconnect();
        SteamworksSystemComponent::Deactivate();
    }

} // namespace Steamworks
