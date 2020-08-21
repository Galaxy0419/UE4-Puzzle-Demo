using UnrealBuildTool;
using System.Collections.Generic;

public class Assignment_1Target : TargetRules
{
    public Assignment_1Target(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V2;
        ExtraModuleNames.AddRange(new string[] { "Assignment_1" });
    }
}
