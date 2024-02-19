
#include <AzCore/Serialization/SerializeContext.h>
#include "SteamAPIEditorSystemComponent.h"

#include <SteamAPI/SteamAPITypeIds.h>

namespace SteamAPI
{
    AZ_COMPONENT_IMPL(SteamAPIEditorSystemComponent, "SteamAPIEditorSystemComponent",
        SteamAPIEditorSystemComponentTypeId, BaseSystemComponent);

    void SteamAPIEditorSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<SteamAPIEditorSystemComponent, SteamAPISystemComponent>()
                ->Version(0);
        }
    }

    SteamAPIEditorSystemComponent::SteamAPIEditorSystemComponent() = default;

    SteamAPIEditorSystemComponent::~SteamAPIEditorSystemComponent() = default;

    void SteamAPIEditorSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        BaseSystemComponent::GetProvidedServices(provided);
        provided.push_back(AZ_CRC_CE("SteamAPIEditorService"));
    }

    void SteamAPIEditorSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        BaseSystemComponent::GetIncompatibleServices(incompatible);
        incompatible.push_back(AZ_CRC_CE("SteamAPIEditorService"));
    }

    void SteamAPIEditorSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        BaseSystemComponent::GetRequiredServices(required);
    }

    void SteamAPIEditorSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
        BaseSystemComponent::GetDependentServices(dependent);
    }

    void SteamAPIEditorSystemComponent::Activate()
    {
        SteamAPISystemComponent::Activate();
        AzToolsFramework::EditorEvents::Bus::Handler::BusConnect();
    }

    void SteamAPIEditorSystemComponent::Deactivate()
    {
        AzToolsFramework::EditorEvents::Bus::Handler::BusDisconnect();
        SteamAPISystemComponent::Deactivate();
    }

} // namespace SteamAPI
