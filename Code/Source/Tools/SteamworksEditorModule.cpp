
#include <Steamworks/SteamworksTypeIds.h>
#include <SteamworksModuleInterface.h>
#include "SteamworksEditorSystemComponent.h"

namespace Steamworks
{
    class SteamworksEditorModule
        : public SteamworksModuleInterface
    {
    public:
        AZ_RTTI(SteamworksEditorModule, SteamworksEditorModuleTypeId, SteamworksModuleInterface);
        AZ_CLASS_ALLOCATOR(SteamworksEditorModule, AZ::SystemAllocator);

        SteamworksEditorModule()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            // Add ALL components descriptors associated with this gem to m_descriptors.
            // This will associate the AzTypeInfo information for the components with the the SerializeContext, BehaviorContext and EditContext.
            // This happens through the [MyComponent]::Reflect() function.
            m_descriptors.insert(m_descriptors.end(), {
                SteamworksEditorSystemComponent::CreateDescriptor(),
            });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         * Non-SystemComponents should not be added here
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList {
                azrtti_typeid<SteamworksEditorSystemComponent>(),
            };
        }
    };
}// namespace Steamworks

#if defined(O3DE_GEM_NAME)
AZ_DECLARE_MODULE_CLASS(AZ_JOIN(Gem_, O3DE_GEM_NAME, _Editor), Steamworks::SteamworksEditorModule)
#else
AZ_DECLARE_MODULE_CLASS(Gem_Steamworks_Editor, Steamworks::SteamworksEditorModule)
#endif
