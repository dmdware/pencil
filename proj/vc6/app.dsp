# Microsoft Developer Studio Project File - Name="app" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=app - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "app.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "app.mak" CFG="app - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "app - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "app - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "app - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# Begin Special Build Tool
TargetDir=.\Release
TargetName=app
SOURCE="$(InputPath)"
PostBuild_Desc=copy
PostBuild_Cmds=copy /Y "$(TargetDir)$(TargetName).exe" "$(SolutionDir)../../testfolder/"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "app - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# Begin Special Build Tool
TargetDir=.\Debug
TargetName=app
SOURCE="$(InputPath)"
PostBuild_Desc=copy
PostBuild_Cmds=copy /Y "$(TargetDir)$(TargetName).exe" "$(SolutionDir)../../testfolder/"
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "app - Win32 Release"
# Name "app - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\source\math\3dmath.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\gui\layouts\appgui.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\app\appmain.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\gui\widgets\button.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\math\camera.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\gui\cursor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\debug.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\gui\draw2d.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\gui\widgets\droplist.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\gui\widgets\editbox.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\gui\font.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\gui\gui.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\gui\icon.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\gui\widgets\image.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\gui\inevent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\input\input.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\algo\localmap.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\math\matrix.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\math\plane3f.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\platform.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\math\quaternion.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\gui\richtext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\render\shader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\sim\simdef.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\sim\simflow.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\gui\widgets\text.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\texture.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\sys\unicode.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\ustring.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\sys\utf8.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\utils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\math\vec3f.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\math\vec4f.cpp
# End Source File
# Begin Source File

SOURCE="..\..\libs\SDL2-2.0.1\src\main\windows\version.rc"
# End Source File
# Begin Source File

SOURCE=..\..\source\gui\widget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\window.cpp
# End Source File
# Begin Source File

SOURCE=..\..\source\gui\widgets\winw.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\source\math\3dmath.h
# End Source File
# Begin Source File

SOURCE=..\..\source\gui\layouts\appgui.h
# End Source File
# Begin Source File

SOURCE=..\..\source\app\appmain.h
# End Source File
# Begin Source File

SOURCE=..\..\source\app\appres.h
# End Source File
# Begin Source File

SOURCE=..\..\source\gui\widgets\button.h
# End Source File
# Begin Source File

SOURCE=..\..\source\math\camera.h
# End Source File
# Begin Source File

SOURCE=..\..\source\gui\cursor.h
# End Source File
# Begin Source File

SOURCE=..\..\source\debug.h
# End Source File
# Begin Source File

SOURCE=..\..\source\gui\draw2d.h
# End Source File
# Begin Source File

SOURCE=..\..\source\gui\widgets\droplist.h
# End Source File
# Begin Source File

SOURCE=..\..\source\gui\widgets\editbox.h
# End Source File
# Begin Source File

SOURCE=..\..\source\gui\font.h
# End Source File
# Begin Source File

SOURCE=..\..\source\gui\gui.h
# End Source File
# Begin Source File

SOURCE=..\..\source\gui\icon.h
# End Source File
# Begin Source File

SOURCE=..\..\source\gui\widgets\image.h
# End Source File
# Begin Source File

SOURCE=..\..\source\gui\inevent.h
# End Source File
# Begin Source File

SOURCE=..\..\source\input\input.h
# End Source File
# Begin Source File

SOURCE=..\..\source\algo\localmap.h
# End Source File
# Begin Source File

SOURCE=..\..\source\math\matrix.h
# End Source File
# Begin Source File

SOURCE=..\..\source\math\plane3f.h
# End Source File
# Begin Source File

SOURCE=..\..\source\platform.h
# End Source File
# Begin Source File

SOURCE=..\..\source\math\quaternion.h
# End Source File
# Begin Source File

SOURCE=..\..\source\gui\richtext.h
# End Source File
# Begin Source File

SOURCE=..\..\source\render\shader.h
# End Source File
# Begin Source File

SOURCE=..\..\source\sim\simdef.h
# End Source File
# Begin Source File

SOURCE=..\..\source\sim\simflow.h
# End Source File
# Begin Source File

SOURCE=..\..\source\gui\widgets\text.h
# End Source File
# Begin Source File

SOURCE=..\..\source\texture.h
# End Source File
# Begin Source File

SOURCE=..\..\source\sys\unicode.h
# End Source File
# Begin Source File

SOURCE=..\..\source\ustring.h
# End Source File
# Begin Source File

SOURCE=..\..\source\sys\utf8.h
# End Source File
# Begin Source File

SOURCE=..\..\source\utils.h
# End Source File
# Begin Source File

SOURCE=..\..\source\math\vec2f.h
# End Source File
# Begin Source File

SOURCE=..\..\source\math\vec2i.h
# End Source File
# Begin Source File

SOURCE=..\..\source\math\vec3f.h
# End Source File
# Begin Source File

SOURCE=..\..\source\math\vec4f.h
# End Source File
# Begin Source File

SOURCE=..\..\source\gui\widget.h
# End Source File
# Begin Source File

SOURCE=..\..\source\window.h
# End Source File
# Begin Source File

SOURCE=..\..\source\gui\widgets\winw.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
