@echo off
set /p name=�������ļ���:
pause
echo ���������%name%
echo #ifndef __%name%_H__ > %name%.h
echo #define __%name%_H__ >> %name%.h
echo. >> %name%.h
echo. >> %name%.h
echo #endif __%name%_H__ >> %name%.h
echo #include "%name%.h" > %name%.cpp