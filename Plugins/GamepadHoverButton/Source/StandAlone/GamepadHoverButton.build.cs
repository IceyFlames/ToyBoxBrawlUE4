using UnrealBuildTool;
using System.IO;

public class GamepadHoverButton : ModuleRules
{
    public GamepadHoverButton(TargetInfo Target)
    {
        PrivateIncludePaths.AddRange(new string[] { "StandAlone/Private" });
        PublicIncludePaths.AddRange(new string[] { "StandAlone/Public" });

        PublicDependencyModuleNames.AddRange(new string[] { "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
                }
              );

        PrivateDependencyModuleNames.AddRange(
            new string[] {
             "Slate",
             "SlateCore",
             "UMG"
             }
            );
    }
}