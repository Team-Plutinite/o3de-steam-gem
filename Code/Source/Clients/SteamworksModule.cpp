
#include <Steamworks/SteamworksTypeIds.h>
#include <SteamworksModuleInterface.h>
#include "SteamworksSystemComponent.h"

namespace Steamworks
{
    class SteamworksModule
        : public SteamworksModuleInterface
    {
    public:
        AZ_RTTI(SteamworksModule, SteamworksModuleTypeId, SteamworksModuleInterface);
        AZ_CLASS_ALLOCATOR(SteamworksModule, AZ::SystemAllocator);
    };
}// namespace Steamworks

#if defined(O3DE_GEM_NAME)
AZ_DECLARE_MODULE_CLASS(AZ_JOIN(Gem_, O3DE_GEM_NAME), Steamworks::SteamworksModule)
#else
AZ_DECLARE_MODULE_CLASS(Gem_Steamworks, Steamworks::SteamworksModule)
#endif
