# o3de-steam-gem
Gem connecting the Steamworks SDK to O3DE.\
Note: You will need to download the SDK yourself and place the "sdk" folder in the Code/Include/Steam directory. (There is a file called "put SDK folder here", the sdk folder goes there.)\
As a warning, the gem was developed on Windows and it's currently unknown if it works on other platforms. If you are on another platform and want to add support you are encouraged to do so. \
\
This gem was developed alongside our game [State of Matter](https://store.steampowered.com/app/2844240/State_of_Matter/) and currently only contains features that our game uses, as I wasn't able to test anything else. If you use this gem and add support for any new features, I encourage you to do a pull request and add them so others in the community can use them!\
\
Currently supported:

 - Connecting to steam API (Automatically runs SteamAPI_RestartAppIfNecessary if in release mode, and runs SteamAPI_Init and connects to all currently implemented interfaces)
 - Achievements
 - Rich Presence
