find_path(IVERILOG_BIN_DIR iverilog-vpi
          PATHS $ENV{IVERILOG_DIR} /usr /usr/local /opt /opt/local
          PATH_SUFFIXES bin iverilog/bin
         )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(IVERILOG_CONFIG DEFAULT_MSG IVERILOG_BIN_DIR)

mark_as_advanced(IVERILOG_BIN_DIR)

if(IVERILOG_CONFIG_FOUND)
    get_filename_component(IVERILOG_ROOT_DIR ${IVERILOG_BIN_DIR} DIRECTORY)
    set(IVERILOG_INCLUDE_DIR ${IVERILOG_ROOT_DIR}/include)
    execute_process(
        COMMAND ${IVERILOG_BIN_DIR}/iverilog-vpi --ldlibs
        OUTPUT_VARIABLE IVERILOG_LIBFLAGS
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )

    execute_process(
        COMMAND ${IVERILOG_BIN_DIR}/iverilog-vpi --ldflags
        OUTPUT_VARIABLE IVERILOG_LDFLAGS
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    set(IVERILOG_LIBRARIES "${IVERILOG_LDFLAGS} ${IVERILOG_LIBFLAGS}")
    separate_arguments(IVERILOG_LIBRARIES)
    message(STATUS ${IVERILOG_LIBRARIES})

else(IVERILOG_CONFIG_FOUND)
    message(FATAL_ERROR "FLTK was not found.")
endif(IVERILOG_CONFIG_FOUND) 
