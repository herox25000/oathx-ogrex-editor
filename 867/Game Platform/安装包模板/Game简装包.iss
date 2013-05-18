[Setup]
AppName=541游戏中心大厅简装包
AppVerName=541游戏中心
DefaultDirName={code:GetInstallDir}
;DefaultDirName={pf}\541
DefaultGroupName=541游戏中心
OutputBaseFilename=541Game
WizardImageFile=embedded\WizardImage.bmp
WizardSmallImageFile=embedded\WizardSmallImage.bmp
UsePreviousAppDir=no

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

[Languages]
Name: "chinesesimp"; MessagesFile: "compiler:Default.isl"
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

[Files]
;拷贝单目录下的文件;Source: "Lobby\*"; DestDir: "{app}"; Flags: ignoreversion
;能拷贝目录下的子文件夹
Source: "Lobby\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs
                           
;Source: "sys\AVCtrl.dll"; DestDir: "{sys}"; Flags: regserver
;Source: "sys\Audio.acm"; DestDir: "{sys}";
;Source: "sys\Video.dll"; DestDir: "{sys}";

//写入安装包版本号
[INI]
Filename: "{app}\Version.ini"; Section: "PLAZA"; Flags: uninsdeletesection
Filename: "{app}\Version.ini"; Section: "PLAZA"; Key: "Version"; String: "3.4"

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

[Registry]
Root: HKCU; Subkey: "Software\541\Plaza"; ValueName: "Path"; ValueType: String; ValueData: "{app}"; Flags: createvalueifdoesntexist uninsdeletevalue deletevalue

;Root: HKCU; Subkey: "Software\Microsoft\Windows NT\CurrentVersion\Drivers32"; ValueName: "msacm.eqa"; ValueType: String; ValueData: "audio.acm"; Flags: createvalueifdoesntexist uninsdeletevalue deletevalue
;Root: HKCU; Subkey: "Software\Microsoft\Windows NT\CurrentVersion\Drivers32"; ValueName: "vidc.MVE4"; ValueType: String; ValueData: "video.dll"; Flags: createvalueifdoesntexist uninsdeletevalue deletevalue
;Root: HKLM; Subkey: "Software\Microsoft\Windows NT\CurrentVersion\Drivers32"; ValueName: "msacm.eqa"; ValueType: String; ValueData: "audio.acm"; Flags: createvalueifdoesntexist uninsdeletevalue deletevalue
;Root: HKLM; Subkey: "Software\Microsoft\Windows NT\CurrentVersion\Drivers32"; ValueName: "vidc.MVE4"; ValueType: String; ValueData: "video.dll"; Flags: createvalueifdoesntexist uninsdeletevalue deletevalue
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

[Run]
Filename: "{app}\541Game.exe"; Description: "{cm:LaunchProgram,541游戏中心}"; Flags: nowait postinstall skipifsilent
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}";
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}";
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

[Icons]
Name: "{group}\541游戏中心"; Filename: "{app}\541Game.exe";
Name: "{userdesktop}\541游戏中心"; Filename: "{app}\541Game.exe";
Name: "{group}\{cm:UninstallProgram,541游戏中心}"; Filename: "{uninstallexe}";

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

[Code]
function InitializeSetup(): Boolean;
var
  hWnd: HWND;
begin
    hWnd := FindWindowByClassName('MGLGame541Plaza');    
    while  hWnd <> 0  do
    BEGIN
        PostMessage(hWnd, 18, 0, 0); 
        hWnd := FindWindowByClassName('MGLGame541Plaza');
    END  
    
    hWnd := FindWindowByClassName('MGLGame541Plaza');
    if  hWnd <> 0  then
    BEGIN
        Result := True;
        while  hWnd <> 0  do
        BEGIN
            if MsgBox('请您先退出游戏并关闭游戏大厅，然后点 "是" 继续安装。', mbInformation, MB_YESNO)=IDNO  then
            BEGIN
                Result := False;
                break;
            END
            hWnd := FindWindowByClassName('MGLGame541Plaza');
        END
    end
    else
        Result := True;
end;

function GetInstallDir(Param: String): string;
begin
    RegQueryStringValue(HKEY_CURRENT_USER, 'Software\541\Plaza', 'Path', Result);
    if Result='' then
    begin
      Result := 'C:\Program Files\541';
    end
end;









