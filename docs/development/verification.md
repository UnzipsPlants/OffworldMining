# Controle ontwikkelomgeving

## Controle 1 — Editor-build

- Datum: 06-11-2026
- Uitgevoerd door: Gilles
- Project: OffworldMining
- Engineversie: Zie bewijs
- Platform: Zie bewijs
- Target: OffworldMiningEditor
- Configuratie: Development
- Gestart via: Zie bewijs
- Resultaat: uitgevoerd
- Editor daarna geopend: gecontroleerd
- Pluginlaadfouten: gecontroleerd
- Waarschuwingen: gecontroleerd

### Bewijs

  8% - Building target OffworldMining
 10% - The build tool starting
 14% - The Build process is starting using the MSBuild toolchain
 14% - D:\Program Files\Microsoft Visual Studio18\Community\MSBuild\Current\Bin\amd64\msbuild.exe -t:Build "-p:_UProjectNMakeBuildCommandLine=\"D:\Games\EpicGames\UE_5.8\Engine\Build\BatchFiles\Build.bat\" OffworldMining Win64 Development -Project=\"D:\Source\Repos\OffworldMining\OffworldMining.uproject\" -WaitMutex -architecture=x64 -Progress -FromMsBuild" "-p:_UProjectNMakeOutput=D:\Source\Repos\OffworldMining\Binaries\Win64\OffworldMining.exe" -p:Platform=x64 -p:Configuration=Development "-p:SolutionDir=D:\Source\Repos\OffworldMining\\" "D:\Source\Repos\OffworldMining\Intermediate\ProjectFiles\VisualStudio\OffworldMining.proj"
 14% - MSBuild version 18.11.1-1.26513.3+940033be3 for .NET Framework
 14% - Build started 06/11/2026 19:37:27.
 14% - Project "D:\Source\Repos\OffworldMining\Intermediate\ProjectFiles\VisualStudio\OffworldMining.proj" on node 1 (Build target(s)).
 14% - Build:
 14% -   "D:\Games\EpicGames\UE_5.8\Engine\Build\BatchFiles\Build.bat" OffworldMining Win64 Development -Project="D:\Source\Repos\OffworldMining\OffworldMining.uproject" -WaitMutex -architecture=x64 -Progress -FromMsBuild
 14% -   Using bundled DotNet SDK version: 10.0 win-x64
 14% -   Running UnrealBuildTool: dotnet "..\..\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.dll" OffworldMining Win64 Development -Project="D:\Source\Repos\OffworldMining\OffworldMining.uproject" -WaitMutex -architecture=x64 -Progress -FromMsBuild
 14% -   Log file: C:\Users\Gilles\AppData\Local\UnrealBuildTool\Log.txt
 14% -   Determining max actions to execute in parallel (12 physical cores, 20 logical cores)
 14% -     Executing up to 12 processes, one per physical core
 14% -   Using 'git status' to determine working set for adaptive non-unity build (D:\Source\Repos\OffworldMining).
 14% -   Creating makefile for OffworldMining (no existing makefile)
 14% -   UbaServer - Listening on 0.0.0.0:1345
 14% - Generating code...
 14% - Generating code...
 14% -   UHT compiled-in object format Default
 16% - Generating code...
 17% - Generating code...
 17% -   Building OffworldMining...
 17% -   ===== Toolchain Information =====
 17% -   Using ISPC compiler (D:\Games\EpicGames\UE_5.8\Engine\Source\ThirdParty\Intel\ISPC\bin\Windows\ispc.exe)
 17% -     Intel(r) Implicit SPMD Program Compiler (Intel(r) ISPC), 1.24.0 (build commit  @ 20250404, LLVM 18.1.2) 
 17% -   Using Visual Studio 14.50.35739 toolchain (D:\Program Files\Microsoft Visual Studio18\Community\VC\Tools\MSVC\14.50.35717) and Windows 10.0.22621.0 SDK (C:\Program Files (x86)\Windows Kits\10).
 17% -   =================================
 17% -   Using Unreal Build Accelerator local executor to run 11 action(s)
 17% -     CPU 12 physical cores, 20 logical cores
 17% -     Memory 31.82 GB physical, 18.43 GB/33.82 GB committed
 17% -     UBA Storage capacity 40 GB
 17% - Compiling C++ source code...
 23% - Compiling C++ source code...
 23% -   [1/11] Copy OffworldMining-Default.rc2
 29% - Compiling C++ source code...
 29% -   [2/11] Copy tbb12.dll
 35% - Compiling C++ source code...
 35% -   [3/11] Copy tbbmalloc.dll
 42% - Compiling C++ source code...
 42% -   [4/11] Copy D3D12Core.dll
 47% - Compiling C++ source code...
 47% -   [5/11] Copy d3d12SDKLayers.dll
 55% - Compiling C++ source code...
 55% -   [6/11] Copy DirectML.dll
 60% - Compiling C++ source code...
 67% - Compiling C++ source code...
 67% -   [7/11] Compile Resource [x64] OffworldMining-Default.rc2
 73% - Compiling C++ source code...
 73% -   [8/11] Compile [x64] SharedPCH.Engine.Project.ValApi.ValExpApi.Cpp20.cpp
 79% - Compiling C++ source code...
 79% -   [9/11] Compile [x64] OffworldMining.cpp
 79% -   [10/11] Link [x64] OffworldMining.exe
 86% - Compiling C++ source code...
 86% -   [11/11] WriteMetadata OffworldMining.target [NoUba]
 86% -   
 86% -   Total time in Unreal Build Accelerator local executor: 50.77 seconds
 86% -   Output binary: D:\Source\Repos\OffworldMining\Binaries\Win64\OffworldMining.exe
 86% -   
 86% -   Result: Succeeded
 86% -   Total execution time: 53.99 seconds
 86% -   Trace written to file C:\Users\Gilles\AppData\Local\UnrealBuildTool\Trace.uba with size 10.8kb
 86% - Done Building Project "D:\Source\Repos\OffworldMining\Intermediate\ProjectFiles\VisualStudio\OffworldMining.proj" (Build target(s)).
 86% - Build succeeded.
 86% -     0 Warning(s)
 86% -     0 Error(s)
 86% - Time Elapsed 00:00:54.52
 86% - The Build process complete successfully
* External build finished with result: Succeeded.
 90% - The build tool completed successfully
100% - The build completed successfully


### Afwijkingen

geen