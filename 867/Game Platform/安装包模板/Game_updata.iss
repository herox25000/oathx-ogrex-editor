[Setup]
AppName=541游戏中心大厅更新包
AppVerName=541游戏中心
DefaultDirName={code:GetInstallDir}
DefaultGroupName=541游戏中心
OutputBaseFilename=541Update
WizardImageFile=embedded\WizardImage.bmp
WizardSmallImageFile=embedded\WizardSmallImage.bmp
UsePreviousAppDir=no
//不生成卸载exe
Uninstallable=no 
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

[Languages]
Name: "chinesesimp"; MessagesFile: "compiler:Default.isl"
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

[Files]
;拷贝单目录下的文件;Source: "Lobby\*"; DestDir: "{app}"; Flags: ignoreversion
;能拷贝目录下的子文件夹;;;;;;;;修改日期：2013.4.21
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
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
[Run]
Filename: "{app}\541Game.exe"; Description: "{cm:LaunchProgram,541游戏中心}"; Flags: nowait postinstall skipifsilent
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

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
procedure CurStepChanged(CurStep: TSetupStep);
var
  hWnd: HWND;
begin
    if CurStep=ssDone then
    begin
      hWnd := FindWindowByClassName('MGLGame541Plaza');
      begin
        PostMessage(hWnd, 1124, 303, 0);
      end
    end
end;
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
function ShouldSkipPage(PageID: Integer): Boolean;
begin
    case PageID of
    wpSelectDir:
        Result := True;
    else
        Result := False;
    end;
end;

function GetInstallDir(Param: String): string;
begin
    RegQueryStringValue(HKEY_CURRENT_USER, 'Software\541\Plaza', 'Path', Result);
end;










