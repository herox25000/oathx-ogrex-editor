//��ϷID
#define GameID 102
[Setup]
AppName=541��Ϸ����-С�Ű�װ��
AppVerName=541��Ϸ����-С��
DefaultDirName={code:GetInstallDir}
OutputBaseFilename=XiaoJiu
WizardImageFile=embedded\WizardImage.bmp
WizardSmallImageFile=embedded\WizardSmallImage.bmp
UsePreviousAppDir=no
Compression=zip/9
SolidCompression=yes
//������ж��exe
Uninstallable=no 

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

[Languages]
Name: "chinesesimp"; MessagesFile: "compiler:Default.isl"
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

[Files]
;������Ŀ¼�µ��ļ�
Source: "Game\XiaoJiu.exe"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs
;�ܿ���Ŀ¼�µ����ļ���Source: "Game\Resource\Games\XiaoJiu\*"; DestDir: "{app}\Resource\Games\XiaoJiu\"; Flags:ignoreversion recursesubdirs

//д�밲װ���汾��
[INI]
Filename: "{app}\Version.ini"; Section: {#GameID}; Flags: uninsdeletesection
Filename: "{app}\Version.ini"; Section: {#GameID}; Key: "GameName"; String: "С��"
Filename: "{app}\Version.ini"; Section: {#GameID}; Key: "Version"; String: "1.3"

[Code]
function InitializeSetup(): Boolean;
var
    Installdir: string;
begin
    RegQueryStringValue(HKEY_CURRENT_USER, 'Software\541\Plaza', 'Path', Installdir)
    Trim(Installdir);
    if Installdir = '' then
    begin
        MsgBox('����û�а�װ��Ϸ���������Ȱ�װ������', mbInformation, MB_OK);
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
        PostMessage(hWnd, 1124,{#GameID}, 0);
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









