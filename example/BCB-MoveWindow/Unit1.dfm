object Form1: TForm1
  Left = 192
  Top = 133
  Width = 336
  Height = 235
  Caption = '範例'
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
    Left = 40
    Top = 40
    Width = 75
    Height = 25
    Caption = '左上'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 120
    Top = 40
    Width = 75
    Height = 25
    Caption = '上'
    TabOrder = 1
    OnClick = Button2Click
  end
  object CheckBox1: TCheckBox
    Left = 48
    Top = 160
    Width = 57
    Height = 17
    Caption = '重繪'
    Checked = True
    State = cbChecked
    TabOrder = 2
  end
  object Button3: TButton
    Left = 200
    Top = 40
    Width = 75
    Height = 25
    Caption = '右上'
    TabOrder = 3
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 40
    Top = 120
    Width = 75
    Height = 25
    Caption = '左下'
    TabOrder = 4
    OnClick = Button4Click
  end
  object Button5: TButton
    Left = 120
    Top = 120
    Width = 75
    Height = 25
    Caption = '下'
    TabOrder = 5
    OnClick = Button5Click
  end
  object Button6: TButton
    Left = 200
    Top = 120
    Width = 75
    Height = 25
    Caption = '右下'
    TabOrder = 6
    OnClick = Button6Click
  end
  object Button7: TButton
    Left = 40
    Top = 80
    Width = 75
    Height = 25
    Caption = '左'
    TabOrder = 7
    OnClick = Button7Click
  end
  object Button8: TButton
    Left = 120
    Top = 80
    Width = 75
    Height = 25
    Caption = '中'
    TabOrder = 8
    OnClick = Button8Click
  end
  object Button9: TButton
    Left = 200
    Top = 80
    Width = 75
    Height = 25
    Caption = '右'
    TabOrder = 9
    OnClick = Button9Click
  end
end
