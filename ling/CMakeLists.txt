cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)
include(pico_extras_import_optional.cmake)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall 
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        )

if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wno-maybe-uninitialized)
endif()

pico_sdk_init()


include(example_auto_set_url.cmake)


project(Ling C CXX ASM)

add_executable(Ling
    "src/main.cpp"
) 

target_include_directories(Ling PRIVATE "Inc/")

# Add pico_stdlib library, add more if used
target_link_libraries(Ling pico_stdlib pico_multicore hardware_pwm hardware_adc hardware_uart)

# enable usb output, disable uart output
# pico_enable_stdio_usb(Crankcase 1)
# pico_enable_stdio_uart(Crankcase 0)

# Need to generate UF2 file for upload to RP2040
# create map/bin/hex file etc.
pico_add_extra_outputs(Ling)

# add url via pico_set_program_url
# example_auto_set_url(Crankcase)