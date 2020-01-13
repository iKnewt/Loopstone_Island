// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Loopstone_IslandEditorTarget : TargetRules
{
	public Loopstone_IslandEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "Loopstone_Island" } );
	}
}
