# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.9

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\diguie_t\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\173.3415.24\bin\cmake\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\diguie_t\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\173.3415.24\bin\cmake\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\Desktop\BeyondLight\Git\BeyondLight\client

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\Desktop\BeyondLight\Git\BeyondLight\client\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\CEFOffScreen.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\CEFOffScreen.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\CEFOffScreen.dir\flags.make

CMakeFiles\CEFOffScreen.dir\browser_client.cpp.obj: CMakeFiles\CEFOffScreen.dir\flags.make
CMakeFiles\CEFOffScreen.dir\browser_client.cpp.obj: ..\browser_client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Desktop\BeyondLight\Git\BeyondLight\client\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CEFOffScreen.dir/browser_client.cpp.obj"
	"E:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\VC\Tools\MSVC\14.11.25503\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\CEFOffScreen.dir\browser_client.cpp.obj /FdCMakeFiles\CEFOffScreen.dir\ /FS -c E:\Desktop\BeyondLight\Git\BeyondLight\client\browser_client.cpp
<<

CMakeFiles\CEFOffScreen.dir\browser_client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CEFOffScreen.dir/browser_client.cpp.i"
	"E:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\VC\Tools\MSVC\14.11.25503\bin\Hostx86\x86\cl.exe" > CMakeFiles\CEFOffScreen.dir\browser_client.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Desktop\BeyondLight\Git\BeyondLight\client\browser_client.cpp
<<

CMakeFiles\CEFOffScreen.dir\browser_client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CEFOffScreen.dir/browser_client.cpp.s"
	"E:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\VC\Tools\MSVC\14.11.25503\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\CEFOffScreen.dir\browser_client.cpp.s /c E:\Desktop\BeyondLight\Git\BeyondLight\client\browser_client.cpp
<<

CMakeFiles\CEFOffScreen.dir\browser_client.cpp.obj.requires:

.PHONY : CMakeFiles\CEFOffScreen.dir\browser_client.cpp.obj.requires

CMakeFiles\CEFOffScreen.dir\browser_client.cpp.obj.provides: CMakeFiles\CEFOffScreen.dir\browser_client.cpp.obj.requires
	$(MAKE) -f CMakeFiles\CEFOffScreen.dir\build.make /nologo -$(MAKEFLAGS) CMakeFiles\CEFOffScreen.dir\browser_client.cpp.obj.provides.build
.PHONY : CMakeFiles\CEFOffScreen.dir\browser_client.cpp.obj.provides

CMakeFiles\CEFOffScreen.dir\browser_client.cpp.obj.provides.build: CMakeFiles\CEFOffScreen.dir\browser_client.cpp.obj


CMakeFiles\CEFOffScreen.dir\gl_core.cpp.obj: CMakeFiles\CEFOffScreen.dir\flags.make
CMakeFiles\CEFOffScreen.dir\gl_core.cpp.obj: ..\gl_core.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Desktop\BeyondLight\Git\BeyondLight\client\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/CEFOffScreen.dir/gl_core.cpp.obj"
	"E:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\VC\Tools\MSVC\14.11.25503\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\CEFOffScreen.dir\gl_core.cpp.obj /FdCMakeFiles\CEFOffScreen.dir\ /FS -c E:\Desktop\BeyondLight\Git\BeyondLight\client\gl_core.cpp
<<

CMakeFiles\CEFOffScreen.dir\gl_core.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CEFOffScreen.dir/gl_core.cpp.i"
	"E:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\VC\Tools\MSVC\14.11.25503\bin\Hostx86\x86\cl.exe" > CMakeFiles\CEFOffScreen.dir\gl_core.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Desktop\BeyondLight\Git\BeyondLight\client\gl_core.cpp
<<

CMakeFiles\CEFOffScreen.dir\gl_core.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CEFOffScreen.dir/gl_core.cpp.s"
	"E:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\VC\Tools\MSVC\14.11.25503\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\CEFOffScreen.dir\gl_core.cpp.s /c E:\Desktop\BeyondLight\Git\BeyondLight\client\gl_core.cpp
<<

CMakeFiles\CEFOffScreen.dir\gl_core.cpp.obj.requires:

.PHONY : CMakeFiles\CEFOffScreen.dir\gl_core.cpp.obj.requires

CMakeFiles\CEFOffScreen.dir\gl_core.cpp.obj.provides: CMakeFiles\CEFOffScreen.dir\gl_core.cpp.obj.requires
	$(MAKE) -f CMakeFiles\CEFOffScreen.dir\build.make /nologo -$(MAKEFLAGS) CMakeFiles\CEFOffScreen.dir\gl_core.cpp.obj.provides.build
.PHONY : CMakeFiles\CEFOffScreen.dir\gl_core.cpp.obj.provides

CMakeFiles\CEFOffScreen.dir\gl_core.cpp.obj.provides.build: CMakeFiles\CEFOffScreen.dir\gl_core.cpp.obj


CMakeFiles\CEFOffScreen.dir\main.cpp.obj: CMakeFiles\CEFOffScreen.dir\flags.make
CMakeFiles\CEFOffScreen.dir\main.cpp.obj: ..\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Desktop\BeyondLight\Git\BeyondLight\client\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/CEFOffScreen.dir/main.cpp.obj"
	"E:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\VC\Tools\MSVC\14.11.25503\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\CEFOffScreen.dir\main.cpp.obj /FdCMakeFiles\CEFOffScreen.dir\ /FS -c E:\Desktop\BeyondLight\Git\BeyondLight\client\main.cpp
<<

CMakeFiles\CEFOffScreen.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CEFOffScreen.dir/main.cpp.i"
	"E:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\VC\Tools\MSVC\14.11.25503\bin\Hostx86\x86\cl.exe" > CMakeFiles\CEFOffScreen.dir\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Desktop\BeyondLight\Git\BeyondLight\client\main.cpp
<<

CMakeFiles\CEFOffScreen.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CEFOffScreen.dir/main.cpp.s"
	"E:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\VC\Tools\MSVC\14.11.25503\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\CEFOffScreen.dir\main.cpp.s /c E:\Desktop\BeyondLight\Git\BeyondLight\client\main.cpp
<<

CMakeFiles\CEFOffScreen.dir\main.cpp.obj.requires:

.PHONY : CMakeFiles\CEFOffScreen.dir\main.cpp.obj.requires

CMakeFiles\CEFOffScreen.dir\main.cpp.obj.provides: CMakeFiles\CEFOffScreen.dir\main.cpp.obj.requires
	$(MAKE) -f CMakeFiles\CEFOffScreen.dir\build.make /nologo -$(MAKEFLAGS) CMakeFiles\CEFOffScreen.dir\main.cpp.obj.provides.build
.PHONY : CMakeFiles\CEFOffScreen.dir\main.cpp.obj.provides

CMakeFiles\CEFOffScreen.dir\main.cpp.obj.provides.build: CMakeFiles\CEFOffScreen.dir\main.cpp.obj


CMakeFiles\CEFOffScreen.dir\render_handler.cpp.obj: CMakeFiles\CEFOffScreen.dir\flags.make
CMakeFiles\CEFOffScreen.dir\render_handler.cpp.obj: ..\render_handler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Desktop\BeyondLight\Git\BeyondLight\client\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/CEFOffScreen.dir/render_handler.cpp.obj"
	"E:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\VC\Tools\MSVC\14.11.25503\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\CEFOffScreen.dir\render_handler.cpp.obj /FdCMakeFiles\CEFOffScreen.dir\ /FS -c E:\Desktop\BeyondLight\Git\BeyondLight\client\render_handler.cpp
<<

CMakeFiles\CEFOffScreen.dir\render_handler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CEFOffScreen.dir/render_handler.cpp.i"
	"E:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\VC\Tools\MSVC\14.11.25503\bin\Hostx86\x86\cl.exe" > CMakeFiles\CEFOffScreen.dir\render_handler.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Desktop\BeyondLight\Git\BeyondLight\client\render_handler.cpp
<<

CMakeFiles\CEFOffScreen.dir\render_handler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CEFOffScreen.dir/render_handler.cpp.s"
	"E:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\VC\Tools\MSVC\14.11.25503\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\CEFOffScreen.dir\render_handler.cpp.s /c E:\Desktop\BeyondLight\Git\BeyondLight\client\render_handler.cpp
<<

CMakeFiles\CEFOffScreen.dir\render_handler.cpp.obj.requires:

.PHONY : CMakeFiles\CEFOffScreen.dir\render_handler.cpp.obj.requires

CMakeFiles\CEFOffScreen.dir\render_handler.cpp.obj.provides: CMakeFiles\CEFOffScreen.dir\render_handler.cpp.obj.requires
	$(MAKE) -f CMakeFiles\CEFOffScreen.dir\build.make /nologo -$(MAKEFLAGS) CMakeFiles\CEFOffScreen.dir\render_handler.cpp.obj.provides.build
.PHONY : CMakeFiles\CEFOffScreen.dir\render_handler.cpp.obj.provides

CMakeFiles\CEFOffScreen.dir\render_handler.cpp.obj.provides.build: CMakeFiles\CEFOffScreen.dir\render_handler.cpp.obj


CMakeFiles\CEFOffScreen.dir\web_core.cpp.obj: CMakeFiles\CEFOffScreen.dir\flags.make
CMakeFiles\CEFOffScreen.dir\web_core.cpp.obj: ..\web_core.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Desktop\BeyondLight\Git\BeyondLight\client\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/CEFOffScreen.dir/web_core.cpp.obj"
	"E:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\VC\Tools\MSVC\14.11.25503\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\CEFOffScreen.dir\web_core.cpp.obj /FdCMakeFiles\CEFOffScreen.dir\ /FS -c E:\Desktop\BeyondLight\Git\BeyondLight\client\web_core.cpp
<<

CMakeFiles\CEFOffScreen.dir\web_core.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CEFOffScreen.dir/web_core.cpp.i"
	"E:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\VC\Tools\MSVC\14.11.25503\bin\Hostx86\x86\cl.exe" > CMakeFiles\CEFOffScreen.dir\web_core.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Desktop\BeyondLight\Git\BeyondLight\client\web_core.cpp
<<

CMakeFiles\CEFOffScreen.dir\web_core.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CEFOffScreen.dir/web_core.cpp.s"
	"E:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\VC\Tools\MSVC\14.11.25503\bin\Hostx86\x86\cl.exe" @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\CEFOffScreen.dir\web_core.cpp.s /c E:\Desktop\BeyondLight\Git\BeyondLight\client\web_core.cpp
<<

CMakeFiles\CEFOffScreen.dir\web_core.cpp.obj.requires:

.PHONY : CMakeFiles\CEFOffScreen.dir\web_core.cpp.obj.requires

CMakeFiles\CEFOffScreen.dir\web_core.cpp.obj.provides: CMakeFiles\CEFOffScreen.dir\web_core.cpp.obj.requires
	$(MAKE) -f CMakeFiles\CEFOffScreen.dir\build.make /nologo -$(MAKEFLAGS) CMakeFiles\CEFOffScreen.dir\web_core.cpp.obj.provides.build
.PHONY : CMakeFiles\CEFOffScreen.dir\web_core.cpp.obj.provides

CMakeFiles\CEFOffScreen.dir\web_core.cpp.obj.provides.build: CMakeFiles\CEFOffScreen.dir\web_core.cpp.obj


# Object files for target CEFOffScreen
CEFOffScreen_OBJECTS = \
"CMakeFiles\CEFOffScreen.dir\browser_client.cpp.obj" \
"CMakeFiles\CEFOffScreen.dir\gl_core.cpp.obj" \
"CMakeFiles\CEFOffScreen.dir\main.cpp.obj" \
"CMakeFiles\CEFOffScreen.dir\render_handler.cpp.obj" \
"CMakeFiles\CEFOffScreen.dir\web_core.cpp.obj"

# External object files for target CEFOffScreen
CEFOffScreen_EXTERNAL_OBJECTS =

CEFOffScreen.exe: CMakeFiles\CEFOffScreen.dir\browser_client.cpp.obj
CEFOffScreen.exe: CMakeFiles\CEFOffScreen.dir\gl_core.cpp.obj
CEFOffScreen.exe: CMakeFiles\CEFOffScreen.dir\main.cpp.obj
CEFOffScreen.exe: CMakeFiles\CEFOffScreen.dir\render_handler.cpp.obj
CEFOffScreen.exe: CMakeFiles\CEFOffScreen.dir\web_core.cpp.obj
CEFOffScreen.exe: CMakeFiles\CEFOffScreen.dir\build.make
CEFOffScreen.exe: ..\lib\glfw\glfw3dll.lib
CEFOffScreen.exe: CMakeFiles\CEFOffScreen.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\Desktop\BeyondLight\Git\BeyondLight\client\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable CEFOffScreen.exe"
	C:\Users\diguie_t\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\173.3415.24\bin\cmake\bin\cmake.exe -E vs_link_exe --intdir=CMakeFiles\CEFOffScreen.dir --manifests  -- "E:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\VC\Tools\MSVC\14.11.25503\bin\Hostx86\x86\link.exe" /nologo @CMakeFiles\CEFOffScreen.dir\objects1.rsp @<<
 /out:CEFOffScreen.exe /implib:CEFOffScreen.lib /pdb:E:\Desktop\BeyondLight\Git\BeyondLight\client\cmake-build-debug\CEFOffScreen.pdb /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:windows  -LIBPATH:E:\Desktop\BeyondLight\Git\BeyondLight\client\lib\cef\Debug  -LIBPATH:E:\Desktop\BeyondLight\Git\BeyondLight\client\lib\glew\lib\Release\Win32 libcef_dll_wrapper.lib libcef.lib opengl32.lib glew32.lib ..\lib\glfw\glfw3dll.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\CEFOffScreen.dir\build: CEFOffScreen.exe

.PHONY : CMakeFiles\CEFOffScreen.dir\build

CMakeFiles\CEFOffScreen.dir\requires: CMakeFiles\CEFOffScreen.dir\browser_client.cpp.obj.requires
CMakeFiles\CEFOffScreen.dir\requires: CMakeFiles\CEFOffScreen.dir\gl_core.cpp.obj.requires
CMakeFiles\CEFOffScreen.dir\requires: CMakeFiles\CEFOffScreen.dir\main.cpp.obj.requires
CMakeFiles\CEFOffScreen.dir\requires: CMakeFiles\CEFOffScreen.dir\render_handler.cpp.obj.requires
CMakeFiles\CEFOffScreen.dir\requires: CMakeFiles\CEFOffScreen.dir\web_core.cpp.obj.requires

.PHONY : CMakeFiles\CEFOffScreen.dir\requires

CMakeFiles\CEFOffScreen.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\CEFOffScreen.dir\cmake_clean.cmake
.PHONY : CMakeFiles\CEFOffScreen.dir\clean

CMakeFiles\CEFOffScreen.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" E:\Desktop\BeyondLight\Git\BeyondLight\client E:\Desktop\BeyondLight\Git\BeyondLight\client E:\Desktop\BeyondLight\Git\BeyondLight\client\cmake-build-debug E:\Desktop\BeyondLight\Git\BeyondLight\client\cmake-build-debug E:\Desktop\BeyondLight\Git\BeyondLight\client\cmake-build-debug\CMakeFiles\CEFOffScreen.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\CEFOffScreen.dir\depend

