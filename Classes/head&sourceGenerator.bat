@echo off
set /p name=请输入文件名:
pause
echo 你输入的是%name%
echo #ifndef __%name%_H__ > %name%.h
echo #define __%name%_H__ >> %name%.h
echo. >> %name%.h
echo. >> %name%.h
echo #endif __%name%_H__ >> %name%.h
echo #include "%name%.h" > %name%.cpp