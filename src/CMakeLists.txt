# Specify the name of the executable.
add_executable(main)

# Specify the source files to be compiled.
target_sources(main PRIVATE main.c input_asm.S morse.h morse.c level_setup.c)

# Generate the PIO header file from the PIO source file.
pico_generate_pio_header(ws2812_rgb ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio)

# Pull in commonly used features.
target_link_libraries(main PRIVATE pico_stdlib hardware_pio)

# Create map/bin/hex file etc.
pico_add_extra_outputs(main)

# Add the URL via pico_set_program_url.
apps_auto_set_url(main)
