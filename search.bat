@echo off
set words=%1
set folder_path=%2
rem Add the command you want to execute with "words" and "folder path"

rem Set the path to your C++ source file
set cpp_file_path=D:\private\search\search\Project1\Source.cpp

rem Set the path to the Visual Studio compiler (cl.exe)
set visual_studio_path=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat

rem Set the desired C++ language version
set cxx_version=/std:c++17

rem Call vcvarsall.bat to set up the environment for Visual Studio
call "%visual_studio_path%" x64

rem Compile the C++ program using cl.exe
cl /EHsc %cxx_version% "%cpp_file_path%"

rem Check if compilation was successful
if %errorlevel% neq 0 (
    echo Compilation failed
    exit /b 1
)

rem Run the program and pass words and folder_path as command-line arguments
Source.exe %words% %folder_path%

rem Check if execution was successful
if %errorlevel% neq 0 (
    echo Execution failed
    exit /b 1
)
