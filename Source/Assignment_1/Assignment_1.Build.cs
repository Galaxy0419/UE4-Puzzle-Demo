using UnrealBuildTool;

public class Assignment_1 : ModuleRules
{
    public Assignment_1(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "AIModule", "NavigationSystem", "GameplayTasks" });
    }
}
