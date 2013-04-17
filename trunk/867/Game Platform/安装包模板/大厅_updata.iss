[Setup]
AppName=541��Ϸ���Ĵ������°�
AppVerName=541��Ϸ����
DefaultDirName={code:GetInstallDir}
DefaultGroupName=541��Ϸ����
OutputBaseFilename=541��Ϸ���Ĵ���_Updata
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
;������Ŀ¼�µ��ļ�;Source: "Lobby\*"; DestDir: "{app}"; Flags: ignoreversion
;�ܿ���Ŀ¼�µ����ļ���
Source: "Lobby\541Game.exe"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs
Source: "Lobby\plugin_relation.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs
Source: "Lobby\plugin_framework.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs
Source: "Lobby\plugin_network.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs
Source: "Lobby\plugin_downLoad.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs
Source: "Lobby\plugin_skinResource.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs
Source: "Lobby\plugin_level.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs
Source: "Lobby\plugin_video.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs
Source: "Lobby\plugin_head.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs
Source: "Lobby\plugin_channel.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs
Source: "Lobby\plugin_common.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirsSource: "Lobby\plugin_share.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs
Source: "Lobby\plugin_property.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs
Source: "Lobby\plugin_ui.dll"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs
Source: "Lobby\Lobby.ini"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs


Source: "Game\Baccarat.exe"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs
Source: "Game\PaiJiu.exe"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs
Source: "Game\XiaoJiu.exe"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs
                 
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
Filename: "{app}\541Game.exe"; Description: "{cm:LaunchProgram,541��Ϸ����}"; Flags: nowait postinstall skipifsilent
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
        MsgBox('����û�а�װ��Ϸ���������Ȱ�װ������', mbInformation, MB_OK);
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
            if MsgBox('�������˳���Ϸ���ر���Ϸ������Ȼ��� "��" ������װ��', mbInformation, MB_YESNO)=IDNO  then
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










