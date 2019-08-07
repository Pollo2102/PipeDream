find_program (VERILATOR verilator
              PATHS $ENV{VERILATOR_ROOT} /usr /usr/local /opt /opt/local
              PATH_SUFFIXES verilator/bin bin )

find_path(VERILATOR_INCLUDE_DIR verilated.h
          PATHS $ENV{VERILATOR_ROOT} /usr /usr/local /opt /opt/local
          PATH_SUFFIXES include share/verilator/include verilator/include verilator/share/verilator/include include/x86_64-linux-gnu x86_64-linux-gnu
         )

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(VERILATOR DEFAULT_MSG VERILATOR VERILATOR_INCLUDE_DIR)

mark_as_advanced(VERILATOR)

if(VERILATOR_FOUND)
    set(VERILATOR_DPI_INCLUDE_DIR "${VERILATOR_INCLUDE_DIR}/vltstd")
else(VERILATOR_FOUND)
    message(FATAL_ERROR "verilator was not found.")
endif(VERILATOR_FOUND) 
