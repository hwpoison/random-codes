' https://media0.giphy.com/media/v1.Y2lkPTc5MGI3NjExa3ZtamNydnFtbG43djBjYjF4NjRqZzBpYTRscW82cnUxbXNmenJhbCZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/l41lUJ1YoZB1lHVPG/giphy.gif
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
 WScript.Sleep(3000)
  ' Key DOWN (VK_SPACE = 32)
    Excel.ExecuteExcel4Macro("CALL(""user32"",""keybd_event"",""JJJJJ"",32,0,0,0)")
    ' Key UP (flag 2 = KEYEVENTF_KEYUP)
    Excel.ExecuteExcel4Macro("CALL(""user32"",""keybd_event"",""JJJJJ"",32,0,2,0)")
 '''''''''''''''''''
 Control = Control + 1
Loop
