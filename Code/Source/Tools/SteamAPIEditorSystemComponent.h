
#pragma once

#include <AzToolsFramework/API/ToolsApplicationAPI.h>

#include <Clients/SteamAPISystemComponent.h>

namespace SteamAPI
{
    /// System component for SteamAPI editor
    class SteamAPIEditorSystemComponent
        : public SteamAPISystemComponent
        , protected AzToolsFramework::EditorEvents::Bus::Handler
    {
        using BaseSystemComponent = SteamAPISystemComponent;
    public:
        AZ_COMPONENT_DECL(SteamAPIEditorSystemComponent);

        static void Reflect(AZ::ReflectContext* context);

        SteamAPIEditorSystemComponent();
        ~SteamAPIEditorSystemComponent();

    private:
        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        // AZ::Component
        void Activate() override;
        void Deactivate() override;
    };
} // namespace SteamAPI
