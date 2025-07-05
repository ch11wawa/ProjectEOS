// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class ProjectEOS : ModuleRules
{
	public ProjectEOS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core",
			"CoreUObject",
			"Engine", 
			"InputCore",
			"EnhancedInput",
			"GameplayTags",
			"GameplayTasks",
			"UMG",
			"Slate",
			"SlateCore",
            "MotionWarping",
            "Niagara",
            "LevelSequence",
			"MovieScene",
			"MovieSceneTracks",
			"NavigationSystem",
			"Sockets",
            "AnimGraphRuntime"
        });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
