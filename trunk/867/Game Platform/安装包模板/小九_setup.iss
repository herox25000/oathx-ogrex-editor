[Setup]
AppName=541游戏中心-小九安装包
AppVerName=541游戏中心-小九
DefaultDirName={code:GetInstallDir}
OutputBaseFilename=小九_Setup
WizardImageFile=embedded\WizardImage.bmp
WizardSmallImageFile=embedded\WizardSmallImage.bmp
UsePreviousAppDir=no
Compression=zip/9
SolidCompression=yes

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

[Languages]
Name: "chinesesimp"; MessagesFile: "compiler:Default.isl"
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

[Files]
;拷贝单目录下的文件
Source: "Game\XiaoJiu.exe"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs
;能拷贝目录下的子文件夹Source: "Game\Resource\Games\XiaoJiu\*"; DestDir: "{app}\Resource\Games\XiaoJiu\"; Flags:ignoreversion recursesubdirs

//写入安装包版本号
[INI]
Filename: "{app}\Version.ini"; Section: "102"; Flags: uninsdeletesection
Filename: "{app}\Version.ini"; Section: "102"; Key: "GameName"; String: "小九"
Filename: "{app}\Version.ini"; Section: "102"; Key: "Version"; String: "1.1"

[Code]
function InitializeSetup(): Boolean;
var
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
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
function GetInstallDir(Param: String): string;
begin
    RegQueryStringValue(HKEY_CURRENT_USER, 'Software\541\Plaza', 'Path', Result);
end;
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------









