// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GEPAssignment2 : ModuleRules
{
	public GEPAssignment2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
