cd %~dp0
FOR /R "%~dp0src" %%G IN (*.cpp) DO (
del "%~dp0%%~nxG"
)

FOR /R "%~dp0src" %%G IN (*.h) DO (
del "%~dp0%%~nxG"
)
pause