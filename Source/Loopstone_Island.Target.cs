// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Loopstone_IslandTarget : TargetRules
{
	public Loopstone_IslandTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Loopstone_Island" } );


        //if (bBuildEditor) //this will include UnrealEd and will throw errors when packaging
        //        if (Target.Type == TargetType.Editor)//4.16+
        //      {
        //        ExtraModuleNames.AddRange(
        //          new string[]
        //        {
        //          "Loopstone_IslandEditor"
        //    });
        //}

    }
}
