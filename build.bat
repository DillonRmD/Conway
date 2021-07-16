@echo off

call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\Tools\vsdevcmd.bat" -no_logo

IF NOT EXIST build\ mkdir build\

pushd build\

set CommonCompilerFlags=-DDUNGEON_DEBUG -diagnostics:column -WL -nologo -fp:fast -Gm- -GR- -EHa- -Od -FC -Zi -w
set CommonLinkerFlags= -incremental:no -opt:ref

cl %CommonCompilerFlags% ..\conway.cpp -link %CommonLinkerFlags%

popd