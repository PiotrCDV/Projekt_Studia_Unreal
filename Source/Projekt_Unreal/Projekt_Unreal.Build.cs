// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Projekt_Unreal : ModuleRules
{
	public Projekt_Unreal(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Projekt_Unreal",
			"Projekt_Unreal/Variant_Platforming",
			"Projekt_Unreal/Variant_Platforming/Animation",
			"Projekt_Unreal/Variant_Combat",
			"Projekt_Unreal/Variant_Combat/AI",
			"Projekt_Unreal/Variant_Combat/Animation",
			"Projekt_Unreal/Variant_Combat/Gameplay",
			"Projekt_Unreal/Variant_Combat/Interfaces",
			"Projekt_Unreal/Variant_Combat/UI",
			"Projekt_Unreal/Variant_SideScrolling",
			"Projekt_Unreal/Variant_SideScrolling/AI",
			"Projekt_Unreal/Variant_SideScrolling/Gameplay",
			"Projekt_Unreal/Variant_SideScrolling/Interfaces",
			"Projekt_Unreal/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
