// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Loopstone_IslandEditor : ModuleRules
{
    public Loopstone_IslandEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        //Public module names that this module uses.
        //In case you would like to add various classes that you're going to use in your game
        //you should add the core,coreuobject and engine dependencies.
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "Loopstone_Island" });
        PrivateDependencyModuleNames.AddRange(new string[] { "UnrealEd", "GenericGraphRuntime" });

        //The path for the header files
        PublicIncludePaths.AddRange(new string[] { "Loopstone_IslandEditor/Public" });

        //The path for the source files
        PrivateIncludePaths.AddRange(new string[] { "Loopstone_IslandEditor/Private" });
    }
}
