@ECHO OFF

cl.exe /nologo /Ox /MT /W0 /GS- /DNDEBUG /Tcmain.c neuralxor.c apprExp.c /link /OUT:neuralxor.exe /SUBSYSTEM:CONSOLE /MACHINE:x64