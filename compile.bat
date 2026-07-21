@echo off
echo ==============================
echo  Compile OpenGL FreeGLUT
echo ==============================
echo.

g++ -o app.exe museum.cpp -I/ucrt64/include -L/ucrt64/lib -lfreeglut -lopengl32 -lglu32 -lm

if %errorlevel% == 0 (
    echo Compile berhasil.
    echo File hasil: app.exe
) else (
    echo Gagal compile.
)

pause