using UnrealBuildTool;

public class AssignmentEditorTarget : TargetRules
{
    public AssignmentEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V2;
        ExtraModuleNames.AddRange(new[] { "Assignment" });
    }
}
