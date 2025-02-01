cmake_minimum_required(VERSION 3.15.0)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/toolchains/toolchain-arm-none-eabi.cmake)

project(single_pulse VERSION 0.1.0 LANGUAGES C ASM)

set(CMAKE_VERBOSE_MAKEFILE ON)

if (NOT DEFINED GD32_STD_PERIPHERAL_PATH)
    set(GD32_STD_PERIPHERAL_PATH       "")
endif()
if (NOT DEFINED GD32_CMSIS_PATH)
    set(GD32_CMSIS_PATH    "")
endif()

set(GD32_HAL_DRIVERS
	${GD32_STD_PERIPHERAL_PATH}/Source/gd32f1x0_gpio.c
	${GD32_STD_PERIPHERAL_PATH}/Source/gd32f1x0_rcu.c
	${GD32_STD_PERIPHERAL_PATH}/Source/gd32f1x0_timer.c
	${GD32_STD_PERIPHERAL_PATH}/Source/gd32f1x0_misc.c
)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(LINKER_FILE ${CMAKE_SOURCE_DIR}/gd32f150.ld)

file(GLOB PRJ_SOURCES "src/*.c" "src/*.s")

add_executable(${PROJECT_NAME}.elf 
    ${PRJ_SOURCES}
    ${GD32_HAL_DRIVERS}
    ${GD32_CMSIS_PATH}/GD/GD32F1x0/Source/system_gd32f1x0.c
    src/startup.s
    src/systick.c
)

target_include_directories(${PROJECT_NAME}.elf
    PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/inc
    ${GD32_STD_PERIPHERAL_PATH}/Include
    ${GD32_CMSIS_PATH}
    ${GD32_CMSIS_PATH}/GD/GD32F1x0/Include
)

target_compile_definitions(${PROJECT_NAME}.elf
    PRIVATE
    -DUSE_STDPERIPH_DRIVER
    -DGD32F130_150 
    -DDEBUG   
)

target_compile_options(${PROJECT_NAME}.elf 
    PRIVATE
    -mcpu=cortex-m3
    -mthumb
    -mfloat-abi=softfp
    -fdata-sections
    -ffunction-sections

    -Wall
    -g3
)

target_link_options(${PROJECT_NAME}.elf
    PRIVATE
    -T${LINKER_FILE}
    -mcpu=cortex-m3
    -mfloat-abi=softfp
    -mthumb
    --specs=nano.specs
    --specs=nosys.specs
    -lc
    -lm
    -lnosys
    -Wl,-Map=${PROJECT_NAME}.map,--cref
    -Wl,--gc-sections
    -Xlinker -print-memory-usage -Xlinker
)
