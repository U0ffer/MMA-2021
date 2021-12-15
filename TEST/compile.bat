@ECHO OFF
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x86
ml /c /coff /Zi asm.asm
link /OPT:NOREF /DEBUG MMA_Lib.lib asm.obj  /SUBSYSTEM:CONSOLE /NODEFAULTLIB:libcurt.lib
call asm.exe