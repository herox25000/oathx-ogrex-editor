# Microsoft Developer Studio Project File - Name="工具" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=工具 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "工具.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "工具.mak" CFG="工具 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "工具 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "工具 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "工具 - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /I "../../../开发库/Include" /I "../../../开发库/Include" /I "." /ZI /W3 /Od /D "WIN32" /D "_WINDOWS" /D "_DEBUG" /D "_AFXDLL" /D "_MBCS" /Gm /Yu"stdafx.h" /GZ /c /GX 
# ADD CPP /nologo /MDd /I "../../../开发库/Include" /I "../../../开发库/Include" /I "." /ZI /W3 /Od /D "WIN32" /D "_WINDOWS" /D "_DEBUG" /D "_AFXDLL" /D "_MBCS" /Gm /Yu"stdafx.h" /GZ /c /GX 
# ADD BASE MTL /nologo /D"_DEBUG" /win32 
# ADD MTL /nologo /D"_DEBUG" /win32 
# ADD BASE RSC /l 2052 /d "_DEBUG" /i "$(IntDir)" 
# ADD RSC /l 2052 /d "_DEBUG" /i "$(IntDir)" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /out:"..\..\..\运行\_ToolBox.e" /incremental:yes /libpath:"../../../开发库/" /debug /pdbtype:sept /subsystem:windows /machine:ix86 
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /out:"..\..\..\运行\_ToolBox.e" /incremental:yes /libpath:"../../../开发库/" /debug /pdbtype:sept /subsystem:windows /machine:ix86 

!ELSEIF  "$(CFG)" == "工具 - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /I "../../../开发库/Include" /I "../../../开发库/Include" /I "." /Zi /W3 /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c /GX 
# ADD CPP /nologo /MD /I "../../../开发库/Include" /I "../../../开发库/Include" /I "." /Zi /W3 /D "WIN32" /D "_WINDOWS" /D "NDEBUG" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c /GX 
# ADD BASE MTL /nologo /D"NDEBUG" /win32 
# ADD MTL /nologo /D"NDEBUG" /win32 
# ADD BASE RSC /l 2052 /d "NDEBUG" /i "$(IntDir)" 
# ADD RSC /l 2052 /d "NDEBUG" /i "$(IntDir)" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /out:"..\..\..\运行\ToolBox.e" /incremental:no /libpath:"../../../开发库/" /debug /pdbtype:sept /subsystem:windows /opt:ref /opt:icf /machine:ix86 /IGNORE:4089
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /out:"..\..\..\运行\ToolBox.e" /incremental:no /libpath:"../../../开发库/" /debug /pdbtype:sept /subsystem:windows /opt:ref /opt:icf /machine:ix86 /IGNORE:4089

!ENDIF

# Begin Target

# Name "工具 - Win32 Debug"
# Name "工具 - Win32 Release"
# Begin Group "源"

# PROP Default_Filter "cpp;c;cxx;def;odl;idl;hpj;bat;asm;asmx"
# Begin Source File

SOURCE=.\GameClient.cpp
# End Source File
# Begin Source File

SOURCE=.\GameClientDlg.cpp

!IF  "$(CFG)" == "工具 - Win32 Debug"

# ADD CPP /nologo /Yu"stdafx.h" /GZ /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\Stdafx.cpp

!IF  "$(CFG)" == "工具 - Win32 Debug"

# ADD CPP /nologo /Yc"stdafx.h" /GZ /GX 
!ELSEIF  "$(CFG)" == "工具 - Win32 Release"

# ADD CPP /nologo /Yc"stdafx.h" /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=.\TransDialog.cpp
# End Source File
# End Group
# Begin Group "头"

# PROP Default_Filter "h;hpp;hxx;hm;inl;inc;xsd"
# Begin Source File

SOURCE=.\GameClient.h
# End Source File
# Begin Source File

SOURCE=.\GameClientDlg.h
# End Source File
# Begin Source File

SOURCE=..\..\..\开发库\Include\GlobalFram
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Stdafx.h
# End Source File
# Begin Source File

SOURCE=.\TransDialog.h
# End Source File
# End Group
# Begin Group "资源"

# PROP Default_Filter "rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe;resx"
# Begin Source File

SOURCE=.\Res\GAME_LOGO.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\GameClient.ico
# End Source File
# Begin Source File

SOURCE=.\GameClient.rc
# End Source File
# Begin Source File

SOURCE=.\res\GameClient.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\Res\manifest.xml
# End Source File
# End Target
# End Project

