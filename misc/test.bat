@echo off
if not exist bin mkdir bin
cl src\jumbo.c /fsanitize=address /link /DEBUG /Feneske.exe
move neske.pdb bin
move neske.exe bin
del *.obj
bin\neske.exe misc/nestest.nes > bin/nestest_out.txt
vimdiff bin/nestest_out.txt misc/ref.txt