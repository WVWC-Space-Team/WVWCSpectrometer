mkdir build
cd build
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DPICO_SDK_PATH=%PICO_SDK_PATH% -DCMAKE_TOOLCHAIN_FILE=%PICO_SDK_PATH%\cmake\preload\toolchains\pico_arm_gcc.cmake ..
make
cd ..