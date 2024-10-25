using UnrealBuildTool;
using System.IO;  // For Path.Combine

public class TTS_Test_SAPI : ModuleRules
{
    public TTS_Test_SAPI(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });

        // Windows SDK version
        string WindowsSdkDir = Target.WindowsPlatform.WindowsSdkDir;
        string SdkVersion = "10.0.26100.0";

        // Add system library paths
        PublicSystemLibraryPaths.Add(Path.Combine(WindowsSdkDir, "Lib", SdkVersion, "um", "x64"));

        // Add the required libraries
        PublicAdditionalLibraries.Add("sapi.lib");    // For SAPI (Speech API)
        PublicAdditionalLibraries.Add("Ole32.lib");   // For CoInitialize and CoUninitialize functions
        PublicAdditionalLibraries.Add(@"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.41.34120\atlmfc\lib\x64\atls.lib");

        // Optionally add include paths if needed (e.g., for headers)
        PublicIncludePaths.Add(@"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.41.34120\atlmfc\include");
    }
}