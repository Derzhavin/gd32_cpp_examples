BUILD_DIR=build
BUILD_PARALLEL_JOBS=6
GD32_STD_PERIPHERAL_PATH=../../GD32F1x0_Firmware_Library_V3.5.0/Firmware/GD32F1x0_standard_peripheral/
GD32_CMSIS_PATH=../../GD32F1x0_Firmware_Library_V3.5.0/Firmware/CMSIS/

cmake -G "Unix Makefiles" \
      -S . \
      -B ${BUILD_DIR} \
      -D GD32_STD_PERIPHERAL_PATH=${GD32_STD_PERIPHERAL_PATH} \
      -D GD32_CMSIS_PATH=${GD32_CMSIS_PATH} \
      -D CMAKE_BUILD_TYPE=Debug

cmake --build ${BUILD_DIR} -j${BUILD_PARALLEL_JOBS} --verbose