
#include <SteamAPI/SteamAPITypeIds.h>
#include <SteamAPIModuleInterface.h>
#include "SteamAPIEditorSystemComponent.h"

namespace SteamAPI
{
    class SteamAPIEditorModule
        : public SteamAPIModuleInterface
    {
    public:
        AZ_RTTI(SteamAPIEditorModule, SteamAPIEditorModuleTypeId, SteamAPIModuleInterface);
        AZ_CLASS_ALLOCATOR(SteamAPIEditorModule, AZ::SystemAllocator);

        SteamAPIEditorModule()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            // Add ALL components descriptors associated with this gem to m_descriptors.
            // This will associate the AzTypeInfo information for the components with the the SerializeContext, BehaviorContext and EditContext.
            // This happens through the [MyComponent]::Reflect() function.
            m_descriptors.insert(m_descriptors.end(), {
                SteamAPIEditorSystemComponent::CreateDescriptor(),
            });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         * Non-SystemComponents should not be added here
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList {
                azrtti_typeid<SteamAPIEditorSystemComponent>(),
            };
        }
    };
}// namespace SteamAPI

#if defined(O3DE_GEM_NAME)
AZ_DECLARE_MODULE_CLASS(AZ_JOIN(Gem_, O3DE_GEM_NAME, _Editor), SteamAPI::SteamAPIEditorModule)
#else
AZ_DECLARE_MODULE_CLASS(Gem_SteamAPI_Editor, SteamAPI::SteamAPIEditorModule)
#endif
