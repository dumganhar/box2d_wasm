#!/usr/bin/env bash

set -e

echo -e "\033[01;32m --------------- START -------------------- \033[0m"

get_current_time_in_seconds() {
    local now=$(date +'%Y-%m-%d %H:%M:%S')
    local total_seconds
    if [[ "$OSTYPE" == "darwin"* ]]; then
        total_seconds=$(date -j -f "%Y-%m-%d %H:%M:%S" "$now" "+%s")
    else
        total_seconds=$(date --date="$now" +%s)
    fi
    echo "$total_seconds"
}

start_time=$(get_current_time_in_seconds)

core_count=$(nproc)
echo "CPU core count：$core_count"

rm -rf BUILD_WASM
mkdir -p BUILD_WASM
cd BUILD_WASM

rm -rf dist
mkdir dist

# make for debug/release and wasm/asm respectively
#check if imput parameter is debug
if [ "$1" = "debug" ]; then
    echo -e "\033[01;32m --------------- Build Debug --------------- \033[0m"
    cmake .. -G "Unix Makefiles" -B ./ -DBUILD_WASM=ON -DCMAKE_BUILD_TYPE=debug -DCMAKE_TOOLCHAIN_FILE=${EMSCRIPTEN}/cmake/Modules/Platform/Emscripten.cmake
    make -j 12
    echo -e "\033[01;32m ---------- Build wasm debug DONE ----------  \033[0m"
    
    cmake .. -G "Unix Makefiles" -B ./ -DBUILD_WASM=OFF -DCMAKE_BUILD_TYPE=debug -DCMAKE_TOOLCHAIN_FILE=${EMSCRIPTEN}/cmake/Modules/Platform/Emscripten.cmake
    make -j 12
    echo -e "\033[01;32m ---------- Build asm debug DONE ----------  \033[0m"

    cp -r ./bin/box2d.debug.asm.js ../../cocos-engine/native/external/emscripten/box2d
    cp -r ./bin/box2d.debug.wasm.js ../../cocos-engine/native/external/emscripten/box2d
    cp -r ./bin/box2d.debug.wasm.wasm ../../cocos-engine/native/external/emscripten/box2d

    echo -e "\033[01;32m ------------ Copy Done --------------  \033[0m"
else
    echo -e "\033[01;32m --------------- Build Release --------------- \033[0m"
    cmake .. -G "Unix Makefiles" -B ./ -DBUILD_WASM=ON -DCMAKE_BUILD_TYPE=release -DCMAKE_TOOLCHAIN_FILE=${EMSCRIPTEN}/cmake/Modules/Platform/Emscripten.cmake
    make -j ${core_count}

    echo -e "\033[01;32m --------------- Copy --------------- \033[0m"

    cp libbox2d-fat.release.a ../dist/
    
    echo -e "\033[01;32m ---------- Build release DONE ----------  \033[0m"
fi


end_time=$(get_current_time_in_seconds)

echo -e "\033[01;32m Time Used: "$((end_time-start_time))"s  \033[1m"
echo -e "\033[01;32m ------------- END -----------------  \033[0m"