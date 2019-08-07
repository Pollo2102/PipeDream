find_path(FLTK_BIN_DIR fltk-config
          PATHS $ENV{FLTK_DIR} /usr /usr/local /opt /opt/local
          PATH_SUFFIXES bin fltk/bin
         )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FLTK_CONFIG DEFAULT_MSG FLTK_BIN_DIR)

mark_as_advanced(FLTK_BIN_DIR)

if(FLTK_CONFIG_FOUND)
    get_filename_component(FLTK_ROOT_DIR ${FLTK_BIN_DIR} DIRECTORY)
    set(FLTK_INCLUDE_DIR ${FLTK_ROOT_DIR}/include)
    execute_process(
        COMMAND ${FLTK_BIN_DIR}/fltk-config --ldstaticflags
        OUTPUT_VARIABLE FLTK_LIBRARIES
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    separate_arguments(FLTK_LIBRARIES)
else(FLTK_CONFIG_FOUND)
    message(FATAL_ERROR "FLTK was not found.")
endif(FLTK_CONFIG_FOUND) 
