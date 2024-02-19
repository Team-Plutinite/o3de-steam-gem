
#include <SteamAPI/SteamAPITypeIds.h>
#include <SteamAPIModuleInterface.h>
#include "SteamAPISystemComponent.h"

namespace SteamAPI
{
    class SteamAPIModule
        : public SteamAPIModuleInterface
    {
    public:
        AZ_RTTI(SteamAPIModule, SteamAPIModuleTypeId, SteamAPIModuleInterface);
        AZ_CLASS_ALLOCATOR(SteamAPIModule, AZ::SystemAllocator);
    };
}// namespace SteamAPI

#if defined(O3DE_GEM_NAME)
AZ_DECLARE_MODULE_CLASS(AZ_JOIN(Gem_, O3DE_GEM_NAME), SteamAPI::SteamAPIModule)
#else
AZ_DECLARE_MODULE_CLASS(Gem_SteamAPI, SteamAPI::SteamAPIModule)
#endif
