// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class SodiumUE4 : ModuleRules
{



    public SodiumUE4(TargetInfo Target)
	{

        RulesAssembly r;
        FileReference CheckProjectFile;
        UProjectInfo.TryGetProjectForTarget("MachRace", out CheckProjectFile);
        r = RulesCompiler.CreateProjectRulesAssembly(CheckProjectFile);
        FileReference f = r.GetModuleFileName(this.GetType().Name);
        string ModulePath = Path.GetDirectoryName(f.CanonicalName);
        string sodiumDllPath = Path.GetFullPath(Path.Combine(ModulePath, "../../Binaries/Win64/libsodiumUE4.dll"));

        PublicIncludePaths.AddRange(
			new string[] {
				"SodiumUE4/Public"
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"SodiumUE4/Private",
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "CoreUObject",
                "Engine",
                "SodiumUE4Library",
				"Projects"
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);



        //RuntimeDependencies.Add(GetUProjectPath()+"/Plugins/SodiumUE4/Binaries/Win64/libsodiumUE4.dll", StagedFileType.NonUFS);

        RuntimeDependencies.Add(new RuntimeDependency(sodiumDllPath));

        AddEngineThirdPartyPrivateStaticDependencies(Target,"SodiumUE4Library");
	}
}
