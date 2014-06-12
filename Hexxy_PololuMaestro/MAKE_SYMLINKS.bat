cd %~dp0
FOR /R "%~dp0src" %%G IN (*.cpp) DO (
del "%~dp0%%~nxG"
mklink "%%~nxG" "%%G"
)

FOR /R "%~dp0src" %%G IN (*.h) DO (
del "%~dp0%%~nxG"
mklink "%%~nxG" "%%G"
)
pause