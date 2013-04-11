[Setup]
AppName=541游戏中心大厅更新包
AppVerName=541游戏中心
DefaultDirName={code:GetInstallDir}
DefaultGroupName=541游戏中心
OutputBaseFilename=541游戏中心大厅_Updata
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
Source: "Lobby\*"; DestDir: "{app}"; Flags: recursesubdirs

;Source: "Lobby\DownLoad\*"; DestDir: "{app}\DownLoad\"; Flags: recursesubdirs;Source: "Lobby\Res\*.*"; DestDir: "{app}\Res\"; Flags: recursesubdirs
Source: "sys\AVCtrl.dll"; DestDir: "{sys}"; Flags: regserver
Source: "sys\Audio.acm"; DestDir: "{sys}";
Source: "sys\Video.dll"; DestDir: "{sys}";

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

[Registry]
Root: HKCU; Subkey: "Software\541\Plaza"; ValueName: "Path"; ValueType: String; ValueData: "{app}"; Flags: createvalueifdoesntexist uninsdeletevalue deletevalue
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
  Installdir: string;
begin
    RegQueryStringValue(HKEY_CURRENT_USER, 'Software\541\Plaza', 'Path', Installdir)
    Trim(Installdir);
    if Installdir = '' then
    begin
        MsgBox('您还没有安装游戏大厅，请先安装大厅。', mbInformation, MB_OK);
        Result := False;
    end
    else
    begin
        Result := True;
    end;

    hWnd := FindWindowByClassName('MGLGame541Plaza');
    if  hWnd <> 0  then
    begin
        SendMessage(hWnd, 1125, 0, 0);
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
end;










