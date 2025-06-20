# o3de-steam-gem
Gem connecting the Steamworks SDK to O3DE.\
Note: You will need to download the SDK yourself and place the "sdk" folder in the Code/Include/Steam directory. (There is a file called "put SDK folder here", the sdk folder goes there.)\
This gem is only tested to work on SDK version **1.59**. Using it past there may cause it to not compile.\
As a warning, the gem was developed on Windows and it's currently unknown if it works on other platforms. If you are on another platform and want to add support you are encouraged to do so. \
\
This gem was developed alongside our game [State of Matter](https://store.steampowered.com/app/2844240/State_of_Matter/) and currently only contains features that our game uses, as I wasn't able to test anything else. If you use this gem and add support for any new features, I encourage you to do a pull request and add them so others in the community can use them!\
\
Important to note: you will need to place steamapi_64.dll in your game build folder (e.g. StateOfMatter/build/windows/profile) and wherever your Editor.exe is (e.g. install/bin/Windows/profile/Default folder for a pre-built engine SDK).\
For any release, make sure steam_api64.dll is also in the folder with your game executable (e.g. StateOfMatter.GameLauncher.exe).
\
\
If you have any issues with installation, feel free to ping me (Jack [SOM]) on the O3DE discord and I'll help you out (and get this documentation updated with whatever isn't clear).
\
\
Currently supported:

 - Connecting to steam API (Automatically runs SteamAPI_RestartAppIfNecessary if in release mode, and runs SteamAPI_Init and connects to all currently implemented interfaces)
 - Achievements
 - Rich Presence
