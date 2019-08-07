cmake_minimum_required (VERSION 3.0)
project (test_MIPS32SOC)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake/")

find_package(VERILATOR REQUIRED)

set(CPP_SRCDIR "${CMAKE_SOURCE_DIR}/../../cpp")
set(VERILOG_SRCDIR "${CMAKE_SOURCE_DIR}/../verilog")
set(VERILOG_SOURCES "${VERILOG_SRCDIR}/ALU.v ${VERILOG_SRCDIR}/ControlUnit.v \
                    ${VERILOG_SRCDIR}/MIPS32SOC.v ${VERILOG_SRCDIR}/DataMemory.v \
                    ${VERILOG_SRCDIR}/InstMemory.v ${VERILOG_SRCDIR}/RegisterFile.v \
                    ${VERILOG_SRCDIR}/BitExtender.v")
set(VTOPMODULE "MIPS32SOC")
set(VERILOG_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/verilog-build")
set(MIPS32SOC_LIB "${VERILOG_BINARY_DIR}/V${VTOPMODULE}__ALL.a")
separate_arguments(VERILOG_SOURCES)

# Run verilator to compile the MIPS32SOC
add_custom_command (
    OUTPUT ${MIPS32SOC_LIB}
    COMMAND ${VERILATOR} -DNO_INIT_MEM -Wall -Wno-fatal -I${VERILOG_SRCDIR} --cc ${VERILOG_SOURCES}
            --top-module ${VTOPMODULE} -Mdir ${VERILOG_BINARY_DIR} -CFLAGS  "-I${CPP_SRCDIR} -std=c++14 -O2 -DNDEBUG"
    COMMAND make CC=${CMAKE_C_COMPILER} CXX=${CMAKE_CXX_COMPILER} -C ${VERILOG_BINARY_DIR} -f V${VTOPMODULE}.mk
    MAIN_DEPENDENCY ${VERILOG_SRCDIR}/${VTOPMODULE}.v
    DEPENDS ${VERILOG_SOURCES}
  )

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
 
add_executable(${PROJECT_NAME} ${VERILATOR_INCLUDE_DIR}/verilated.cpp
                                     ${PROJECT_NAME}.cpp)

target_link_libraries(${PROJECT_NAME} ${MIPS32SOC_LIB})
target_link_libraries(${PROJECT_NAME} -static-libgcc -static-libstdc++)