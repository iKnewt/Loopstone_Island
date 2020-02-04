// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Loopstone_Island : ModuleRules
{
	public Loopstone_Island(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

        //PublicIncludePaths.AddRange(new string[] { "Loopstone_Island" });

        PrivateDependencyModuleNames.AddRange(new string[] { "UnrealEd", "GenericGraphRuntime"});
        //PrivateDependencyModuleNames.AddRange(new string[] { "GenericGraphRuntime"});

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
