// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Projekt_Studia : ModuleRules
{
	public Projekt_Studia(ReadOnlyTargetRules Target) : base(Target)
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
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Projekt_Studia",
			"Projekt_Studia/Variant_Platforming",
			"Projekt_Studia/Variant_Combat",
			"Projekt_Studia/Variant_Combat/AI",
			"Projekt_Studia/Variant_SideScrolling",
			"Projekt_Studia/Variant_SideScrolling/Gameplay",
			"Projekt_Studia/Variant_SideScrolling/AI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
