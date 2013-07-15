unit VideoDebugUnit;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Menus;

type
  TFormVideoDebug = class(TForm)
    ListBox1: TListBox;
    MainMenu1: TMainMenu;
    N1: TMenuItem;
    procedure N1Click(Sender: TObject);
  private
    { Private declarations }
  public
    procedure CopyDataMsg(var msg:TWMCopyData); message WM_COPYDATA;
    { Public declarations }
  end;

var
  FormVideoDebug: TFormVideoDebug;

implementation

{$R *.dfm}

procedure TFormVideoDebug.CopyDataMsg(var msg:TWMCopyData);
begin
  ListBox1.Items.Add(pchar(msg.CopyDataStruct.lpData));
end;

procedure TFormVideoDebug.N1Click(Sender: TObject);
begin
  ListBox1.Clear;
end;

end.
