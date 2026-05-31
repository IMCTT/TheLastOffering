// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TheLastOffering : ModuleRules
{
	public TheLastOffering(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"NavigationSystem",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"Niagara",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"TheLastOffering",
			"TheLastOffering/Variant_Strategy",
			"TheLastOffering/Variant_Strategy/UI",
			"TheLastOffering/Variant_TwinStick",
			"TheLastOffering/Variant_TwinStick/AI",
			"TheLastOffering/Variant_TwinStick/Gameplay",
			"TheLastOffering/Variant_TwinStick/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
