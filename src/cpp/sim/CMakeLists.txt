cmake_minimum_required (VERSION 2.8)
project (Mips32SocSim)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake/")

find_package(VERILATOR REQUIRED)
find_package(SDL2 REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CPP_SRCDIR "${CMAKE_SOURCE_DIR}")
set(VERILOG_SRCDIR "${CMAKE_SOURCE_DIR}/../../verilog")
set(VERILOG_SOURCES "${VERILOG_SRCDIR}/cpu/ALU.v ${VERILOG_SRCDIR}/cpu/ControlUnit.v \
                    ${VERILOG_SRCDIR}/cpu/MIPS32SOC.v ${VERILOG_SRCDIR}/cpu/DataMemory.v \
                    ${VERILOG_SRCDIR}/cpu/InstMemory.v ${VERILOG_SRCDIR}/cpu/RegisterFile.v \
                    ${VERILOG_SRCDIR}/cpu/BitExtender.v ${VERILOG_SRCDIR}/cpu/PCDecoder.v \
                    ${VERILOG_SRCDIR}/cpu/MemDecoder.v ${VERILOG_SRCDIR}/cpu/MemReadDataDecoder.v \
                    ${VERILOG_SRCDIR}/cpu/MemWriteDataEncoder.v ${VERILOG_SRCDIR}/cpu/ClockGenerator.v \
                    ${VERILOG_SRCDIR}/cpu/MillisCounter.v \
                    ${VERILOG_SRCDIR}/vga/DualPortVGARam.v ${VERILOG_SRCDIR}/vga/FontRom.v \
                    ${VERILOG_SRCDIR}/vga/RomColorPalette.v ${VERILOG_SRCDIR}/vga/VGA80X30Color.v \
                    ${VERILOG_SRCDIR}/vga/VGATextCard.v")
set(VTOPMODULE "MIPS32SOC")
set(VERILOG_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/verilog-build")
set(MIPS32SOC_LIB "${VERILOG_BINARY_DIR}/V${VTOPMODULE}__ALL.a")
separate_arguments(VERILOG_SOURCES)

# Run verilator to compile the MIPS32SOC
add_custom_command (
    OUTPUT ${MIPS32SOC_LIB}
    COMMAND ${VERILATOR} -DNO_INIT_MEM -Wall -Wno-fatal -I${VERILOG_SRCDIR}/cpu -I${VERILOG_SRCDIR}/vga --cc ${VERILOG_SOURCES}
            --top-module ${VTOPMODULE} -Mdir ${VERILOG_BINARY_DIR} -CFLAGS "-I${CPP_SRCDIR} -std=c++14 -O2 -DNDEBUG"
    COMMAND make -C ${VERILOG_BINARY_DIR} -f V${VTOPMODULE}.mk
    MAIN_DEPENDENCY ${VERILOG_SRCDIR}/cpu/${VTOPMODULE}.v
    DEPENDS ${VERILOG_SOURCES} ${VERILOG_SRCDIR}/cpu/mips32_opcodes.vh
  )

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${VERILOG_BINARY_DIR})
include_directories(${VERILATOR_INCLUDE_DIR})
include_directories(${VERILATOR_DPI_INCLUDE_DIR})
include_directories(${CPP_SRCDIR})

set_source_files_properties(
    ${PROJECT_NAME}.cpp
    PROPERTIES OBJECT_DEPENDS ${MIPS32SOC_LIB}
)

set_directory_properties(
    PROPERTIES
    ADDITIONAL_MAKE_CLEAN_FILES "${VERILOG_BINARY_DIR}"
)

add_executable(${PROJECT_NAME}  ${VERILATOR_INCLUDE_DIR}/verilated.cpp
                                CmdArgs.cpp
                                VGATextWindow.cpp
                                Mips32SocSim.cpp
                                Main.cpp
              )

target_link_libraries(${PROJECT_NAME} ${MIPS32SOC_LIB})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} -lpthread)