@echo off
if not exist bin mkdir bin
cl /O2 /Ibin\SDL3-x64\include src\jumbo.c bin\SDL3-x64\lib\SDL3.lib /Z7 /Feneske.exe
copy bin\SDL3-x64\bin\* bin
move neske.exe bin
del *.obj