# Building & Installing from source in Windows platform
```
last updated: 2020-10-11
tested at: 2020-10-11
```

## Prerequisite

The steps are tested under this environment. Please prepare these installed.

```
Windows 10 (64 bit)
Visual Studio Community 2017
Cmake 3.18.3
OpenCV 3.4.11
libwebp 1.1.0 windows-x64
```

- Download Visual Studio Community 2017, please visit [here](https://visualstudio.microsoft.com/vs/older-downloads/).
- Download Cmake 3.18.3, please visit [here](https://cmake.org/download/).
- Download OpenCV 3.4.11, please visit [here](https://opencv.org/releases/).
- Download libwebp 1.1.0, please visit [here](https://storage.googleapis.com/downloads.webmproject.org/releases/webp/index.html).


## Notes on install Cmake

In order to run Cmake in `CMD`, please make sure `PATH environment variable` contains the folder of Cmake. eg: `C:\Program Files\CMake\bin`

One may check this by by running `echo %PATH%` in CMD.


## Notes on install OpenCV

The folder location of OpenCV is important. This program depends on this library.
The downloaded OpenCV file is usually an archive (self-extracting archive). Please extract to a certain folder. eg: `D:\opencv` (i.e. the `opencv extracted folder`)

Copy files listed below from folder `D:\opencv\build\x64\vc15\bin` to `System32 folder`. One may need Administrator right of the Windows system to do so.
```
opencv_ffmpeg3411_64.dll
opencv_world3411.dll
opencv_world3411.pdb
opencv_world3411d.dll
opencv_world3411d.pdb
```

**Alternatively**, one may add the path of OpenCV binary (eg: `D:\opencv\build\x64\vc15\bin`) to `PATH environment variable`. You may refer to this [web page](https://www.deciphertechnic.com/install-opencv-with-visual-studio/).


## Notes on install libwebp, using `vcpkg`

It is known that `libwebp` uses pthread in Linux/MacOS platforms, the equivalence in Windows would be `pthreadVC3`.

In Windows, you need to rename the files if you download libwebp from [here](https://storage.googleapis.com/downloads.webmproject.org/releases/webp/index.html):
```
libwebp.lib -> webp.lib
libwebpdemux.lib -> webpdemux.lib
libwebpmux.lib -> webpmux.lib
```

There is a tool named `vcpkg`, a product developed by Microsoft for managing packages for Visual Studio C++ project, it handles it automatically. Please refer the steps from this [web page](https://github.com/microsoft/vcpkg#quick-start-windows). It is advised to clone the vcpkg repository to `splitwebp` root directory, i.e. the folder of `vcpkg` would be `D:\splitwebp\vcpkg`

Alternatively, you may need to modify this line: `link_directories("vcpkg/installed/x64-windows/lib")` in CMakeLists.txt accordingly.


## Steps to compile

1. Prepare the prerequisite

2. Clone this repository to `splitwebp` root directory, eg: `D:\splitwebp`

3. Create a new folder named `build` under `splitwebp` root directory, eg: `D:\splitwebp\build` (i.e. the `build folder`)

4. Open `CMD`, change the current directory to `build folder`

5. Run `..\vcpkg\vcpkg install pthreads:x64-windows libwebp[core,nearlossless,simd,unicode]:x64-windows`

6. Run `cmake .. && cmake -DCMAKE_GENERATOR_PLATFORM=x64 --build .`

7. Visit Windows Explorer in `build folder`. Open the Visual Studio Project by double clicking `splitwebp.vcxproj`

8. Change Project properties (Solution Explorer > right click `splitwebp` > Properties)

    8.1. pointing Include folder of OpenCV

        In Properties, go to C/C++ > Additional Include Directories > click on the value and see a pull down menu > click Edit.. > click New Line. And add these paths:

        (if your `opencv extracted folder` is `D:\opencv`)

        D:\opencv\build\include
        D:\splitwebp\vcpkg\installed\x64-windows\include

    8.2. remove `/machine:x86` to build for x64 platform (64 bit). Delete `/machine:x86` in Additional Option, and click Apply.
        ![s](/docs/images/remove-x86.png)

    8.3. Add project Environment variable

        go to Debugging > go to Environment > click on the value and see a pull down menu > click Edit.. > click New Line. And add these paths:

        PATH=%PATH%;D:\splitwebp\vcpkg\installed\x64-windows\bin


9. Build solution, click Visual Studio's menu > Build > Build Solution (F7)

10. If no errors, the compiled exe file should be located at `Release` or `Debug` folder under the `build folder`, eg: `D:\splitwebp\build`


## Troubleshoot

1) > By not providing "FindOpenCV.cmake" in CMAKE_MODULE_PATH

    Solution: set the `environment variable` named `OPENCV_DIR`. Open `CMD`, and run this command (This may require Administrator right. ):

    `setx -m OPENCV_DIR D:\opencv\build\x64\vc15\lib`

2) > Cannot find or open the PDB file

    is shown in the Output window of Visual Studio shows:

    Solution: Turn on `Microsoft Symbol Servers` for debugging symbol. Please refer to this [web page](https://docs.microsoft.com/en-us/visualstudio/debugger/specify-symbol-dot-pdb-and-source-files-in-the-visual-studio-debugger?view=vs-2019) for further details.

3) > webp.dll not found

    Solution: Press Alt F7 > go to Debugging > go to Environment > click on the value and see a pull down menu > click Edit.. > click New Line. And add these paths:

    `PATH=%PATH%;D:\splitwebp\vcpkg\installed\x64-windows\bin`

## Glossary
- `CMD` Command Prompt in Windows, accept user's command. Run it by: Start Menu => search "cmd" => click "Command Prompt" OR Start Menu > "Run" > type "cmd" > press Enter

- `build folder` The folder where the Visual Studio project generated by Cmake locates at. eg: `D:\splitwebp\build`

- `PATH environment variable` contains the paths that Windows system would try to find out the executive files to run when a user enter a command in CMD. One can view the content by running `echo %PATH%` in CMD.

- `System32 folder` An important folder for Windows to run. It contains system files and libraries binary. It usually locates at `C:\Windows\System32`

- `opencv extracted folder` eg: `D:/opencv`

- `OPENCV_DIR` This is the path where the library files locates at. It should be inside sub-folders in `opencv extracted folder`, eg: `D:/opencv/build/x64/vc15/lib`
