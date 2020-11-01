using System.IO;
using UnrealBuildTool;

public class Assignment : ModuleRules
{
    public Assignment(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new[] {
            /* Default Modules */
            "Core", "CoreUObject", "Engine", "InputCore",
            /* Additional Modules for the Project */
            "UMG", "AIModule", "NavigationSystem", "Niagara", "LevelSequence", "MovieScene"
        });
        PublicIncludePaths.AddRange(new string[] { "Assignment",
            Path.Combine(EngineDirectory, "Plugins/FX/Niagara/Source/Niagara/Public"),
            Path.Combine(EngineDirectory, "Plugins/FX/Niagara/Source/Niagara/Classes"),
            Path.Combine(EngineDirectory, "Plugins/FX/Niagara/Source/Niagara/Private")
        });
    }
}
