program VideoDebug;

uses
  Forms,
  VideoDebugUnit in 'VideoDebugUnit.pas' {FormVideoDebug};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TFormVideoDebug, FormVideoDebug);
  Application.Run;
end.
