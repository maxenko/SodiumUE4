// Copyright 1998-2024 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class SodiumUE4 : ModuleRules
{
    public SodiumUE4(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDefinitions.Add("SODIUM_STATIC=1");
        PublicDefinitions.Add("SODIUM_EXPORT=");

        string sodiumIncludes = Path.Combine(ModuleDirectory, "../ThirdParty/libsodium/");

        PublicIncludePaths.AddRange(
			new string[] {
				"SodiumUE4/Public",
                sodiumIncludes
			}
			);

		PrivateIncludePaths.AddRange(new string[] {"SodiumUE4/Private"});

		PublicDependencyModuleNames.AddRange(new string[]{"Core"});

		PrivateDependencyModuleNames.AddRange(
			new string[]{
				"CoreUObject",
				"Engine",
                "Slate",
                "SlateCore",
                "Projects"
            }
			);

        // Platform-specific library linking
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            string PlatformString = "x64";
            string path = Path.Combine(ModuleDirectory, "../ThirdParty/libsodium/Build/Release/" + PlatformString + "/libsodium.lib");
            PublicAdditionalLibraries.Add(path);
        }
        else if (Target.Platform == UnrealTargetPlatform.Win32)
        {
            string PlatformString = "Win32";
            string path = Path.Combine(ModuleDirectory, "../ThirdParty/libsodium/Build/Release/" + PlatformString + "/libsodium.lib");
            PublicAdditionalLibraries.Add(path);
        }
        // Add support for other platforms as needed (Linux, Mac, etc.)
    }
}
