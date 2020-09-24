using UnrealBuildTool;

public class Assignment : ModuleRules
{
    public Assignment(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "AIModule", "NavigationSystem" });
    }
}
