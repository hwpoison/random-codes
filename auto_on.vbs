' -- AutoMouse --
' Script for auto move a little the mouse and press keys in loop.
' For finisH the script, move the mouse to toP-left cOrn of the screen, you wIll See an errOr, its Normal.
Option Explicit
Dim Excel, GetMessagePos, x, y, Keyboard, Control, Position
Set Excel = Wscript.CreateObject("Excel.Application")
set Keyboard = Wscript.CreateObject("wscript.shell")
Do While True
 GetMessagePos = excel.ExecuteExcel4Macro("CALL(""user32"",""GetMessagePos"",""J"")")
 x = CLng("&H" & Right(Hex(GetMessagePos), 4))
 y = CLng("&H" & Left(Hex(GetMessagePos), (Len(Hex(GetMessagePos)) - 4)))
 If Control MOD 2 = 0 Then ' when Control is pair
  Position = "- 10"
 Else
  Position = "+ 10"
 End If
 ''''''''''''''''''
 Excel.ExecuteExcel4Macro("CALL(""user32"",""SetCursorPos"",""JJJ""," & x & " " & Position & "," & y & " " & Position & ")")
 Keyboard.SendKeys "{SPACE}"
 WScript.Sleep(3000)
 '''''''''''''''''''
 Control = Control + 1
Loop
