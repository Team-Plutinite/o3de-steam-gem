
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
    inline constexpr const char* SteamworksNotificationsTypeId = "{35536BD8-70BB-4EF1-BB45-EA1A839CC9FC}";

    inline constexpr const char* SteamUserStatsRequestsTypeId = "{54B6504E-F753-458C-AAE0-58903486C4BC}";
    inline constexpr const char* SteamUserStatsNotificationsTypeId = "{532EA45B-CF45-4EAA-9CEE-A97DB31E4CBE}";
    inline constexpr const char* SteamUserRequestsTypeId = "{0969F156-0FA7-4600-AFA9-36550896E1C2}";
    inline constexpr const char* SteamFriendsRequestsTypeId = "{B86050B4-5C5F-4512-A156-F49CB3B0FC90}";
    inline constexpr const char* SteamFriendsNotificationsTypeId = "{A2286575-6FA0-4444-9F12-14D99E227389}";
} // namespace Steamworks
