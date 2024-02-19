
#include "SteamAPIModuleInterface.h"
#include <AzCore/Memory/Memory.h>

#include <SteamAPI/SteamAPITypeIds.h>

#include <Clients/SteamAPISystemComponent.h>

namespace SteamAPI
{
    AZ_TYPE_INFO_WITH_NAME_IMPL(SteamAPIModuleInterface,
        "SteamAPIModuleInterface", SteamAPIModuleInterfaceTypeId);
    AZ_RTTI_NO_TYPE_INFO_IMPL(SteamAPIModuleInterface, AZ::Module);
    AZ_CLASS_ALLOCATOR_IMPL(SteamAPIModuleInterface, AZ::SystemAllocator);

    SteamAPIModuleInterface::SteamAPIModuleInterface()
    {
        // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
        // Add ALL components descriptors associated with this gem to m_descriptors.
        // This will associate the AzTypeInfo information for the components with the the SerializeContext, BehaviorContext and EditContext.
        // This happens through the [MyComponent]::Reflect() function.
        m_descriptors.insert(m_descriptors.end(), {
            SteamAPISystemComponent::CreateDescriptor(),
            });
    }

    AZ::ComponentTypeList SteamAPIModuleInterface::GetRequiredSystemComponents() const
    {
        return AZ::ComponentTypeList{
            azrtti_typeid<SteamAPISystemComponent>(),
        };
    }
} // namespace SteamAPI
