
#pragma once

namespace Steamworks
{
    // System Component TypeIds
    inline constexpr const char* SteamworksSystemComponentTypeId = "{77DD5499-D8AE-42DB-9BBB-EDBA2CE06D7D}";
    inline constexpr const char* SteamworksEditorSystemComponentTypeId = "{8083DBF9-B284-408F-8928-953CB310199B}";

    // Module derived classes TypeIds
    inline constexpr const char* SteamworksModuleInterfaceTypeId = "{8D08FC55-843E-47FA-9E88-C8D0F0E77558}";
    inline constexpr const char* SteamworksModuleTypeId = "{5208D02F-194F-4A86-AA9A-E8AD55E962C0}";
    // The Editor Module by default is mutually exclusive with the Client Module
    // so they use the Same TypeId
    inline constexpr const char* SteamworksEditorModuleTypeId = SteamworksModuleTypeId;

    // Interface TypeIds
    inline constexpr const char* SteamworksRequestsTypeId = "{6B49F4E0-4C6A-4251-A794-A734D4F09FF1}";
} // namespace Steamworks
