
#pragma once

#include <AzToolsFramework/API/ToolsApplicationAPI.h>

#include <Clients/SteamworksSystemComponent.h>

namespace Steamworks
{
    /// System component for Steamworks editor
    class SteamworksEditorSystemComponent
        : public SteamworksSystemComponent
        , protected AzToolsFramework::EditorEvents::Bus::Handler
    {
        using BaseSystemComponent = SteamworksSystemComponent;
    public:
        AZ_COMPONENT_DECL(SteamworksEditorSystemComponent);

        static void Reflect(AZ::ReflectContext* context);

        SteamworksEditorSystemComponent();
        ~SteamworksEditorSystemComponent();

    private:
        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        // AZ::Component
        void Activate() override;
        void Deactivate() override;
    };
} // namespace Steamworks
