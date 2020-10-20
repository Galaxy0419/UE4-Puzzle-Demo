using System.IO;
using UnrealBuildTool;

public class Assignment : ModuleRules
{
    public Assignment(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "AIModule", "NavigationSystem", "Niagara" });
        PublicIncludePaths.AddRange(new string[] { "Assignment",
            Path.Combine(EngineDirectory, "Plugins/FX/Niagara/Source/Niagara/Public"),
            Path.Combine(EngineDirectory, "Plugins/FX/Niagara/Source/Niagara/Classes"),
            Path.Combine(EngineDirectory, "Plugins/FX/Niagara/Source/Niagara/Private")
        });

    }
}
