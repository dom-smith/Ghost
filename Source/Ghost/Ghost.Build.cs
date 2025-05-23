using UnrealBuildTool;

public class Ghost : ModuleRules
{
    public Ghost(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "UMG",
            "BlueprintGraph"
        });

        PrivateDependencyModuleNames.AddRange(new[] { "Projects" });
    }
}
