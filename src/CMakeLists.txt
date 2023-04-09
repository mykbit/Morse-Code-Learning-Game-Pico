# Specify the name of the executable.
add_executable(main)

# Specify the source files to be compiled.
target_sources(main PRIVATE main.c input_asm.S)

# Pull in commonly used features.
target_link_libraries(main PRIVATE pico_stdlib)

# Create map/bin/hex file etc.
pico_add_extra_outputs(main)
