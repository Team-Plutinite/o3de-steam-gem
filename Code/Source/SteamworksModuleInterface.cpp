
#include "SteamworksModuleInterface.h"
#include <AzCore/Memory/Memory.h>

#include <Steamworks/SteamworksTypeIds.h>

#include <Clients/SteamworksSystemComponent.h>

namespace Steamworks
{
    AZ_TYPE_INFO_WITH_NAME_IMPL(SteamworksModuleInterface,
        "SteamworksModuleInterface", SteamworksModuleInterfaceTypeId);
    AZ_RTTI_NO_TYPE_INFO_IMPL(SteamworksModuleInterface, AZ::Module);
    AZ_CLASS_ALLOCATOR_IMPL(SteamworksModuleInterface, AZ::SystemAllocator);

    SteamworksModuleInterface::SteamworksModuleInterface()
    {
        // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
        // Add ALL components descriptors associated with this gem to m_descriptors.
        // This will associate the AzTypeInfo information for the components with the the SerializeContext, BehaviorContext and EditContext.
        // This happens through the [MyComponent]::Reflect() function.
        m_descriptors.insert(m_descriptors.end(), {
            SteamworksSystemComponent::CreateDescriptor(),
            });
    }

    AZ::ComponentTypeList SteamworksModuleInterface::GetRequiredSystemComponents() const
    {
        return AZ::ComponentTypeList{
            azrtti_typeid<SteamworksSystemComponent>(),
        };
    }
} // namespace Steamworks
