@ECHO OFF
ml /c /coff /Zi asm.asm
link /OPT:NOREF /DEBUG MMA_Lib.lib asm.obj  /SUBSYSTEM:CONSOLE /NODEFAULTLIB:libcurt.lib
call asm.exe