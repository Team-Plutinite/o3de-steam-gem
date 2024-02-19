
#pragma once

namespace SteamAPI
{
    // System Component TypeIds
    inline constexpr const char* SteamAPISystemComponentTypeId = "{62274027-AAF1-4738-A68A-1CDB0884D350}";
    inline constexpr const char* SteamAPIEditorSystemComponentTypeId = "{D3D846D4-4C8C-46A8-840D-45F09DDB152A}";

    // Module derived classes TypeIds
    inline constexpr const char* SteamAPIModuleInterfaceTypeId = "{A68D38A3-711B-4609-B1BE-916170C4A3B3}";
    inline constexpr const char* SteamAPIModuleTypeId = "{E853E924-4E09-4614-9786-F92D89B489A0}";
    // The Editor Module by default is mutually exclusive with the Client Module
    // so they use the Same TypeId
    inline constexpr const char* SteamAPIEditorModuleTypeId = SteamAPIModuleTypeId;

    // Interface TypeIds
    inline constexpr const char* SteamAPIRequestsTypeId = "{AEDC8E78-2235-48C3-9522-B239D98670D1}";
} // namespace SteamAPI
