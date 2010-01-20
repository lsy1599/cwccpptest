object Form1: TForm1
  Left = 192
  Top = 107
  Width = 696
  Height = 480
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 120
    Top = 112
    Width = 75
    Height = 25
    Caption = 'Button1'
    TabOrder = 0
    OnClick = Button1Click
  end
  object xDoc: TmsDOMDocument
    AutoConnect = False
    ConnectKind = ckRunningOrNew
    Left = 48
    Top = 32
  end
  object DOMDocument601: TDOMDocument60
    AutoConnect = False
    ConnectKind = ckRunningOrNew
    Left = 296
    Top = 120
  end
  object msDOMDocument301: TmsDOMDocument30
    AutoConnect = False
    ConnectKind = ckRunningOrNew
    Left = 360
    Top = 64
  end
end
