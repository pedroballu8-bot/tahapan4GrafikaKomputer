@echo off
echo ==============================
echo  Compile OpenGL FreeGLUT
echo ==============================
echo.

g++ -o museum_app.exe main.cpp camera.cpp lighting.cpp textures.cpp collision.cpp building.cpp interior.cpp objects.cpp museum.cpp -I/ucrt64/include -L/ucrt64/lib -lfreeglut -lopengl32 -lglu32 -lm

if %errorlevel% == 0 (
    echo Compile berhasil.
    echo File hasil: museum_app.exe
) else (
    echo Gagal compile.
)

pause