if (NOT WIN32)
   # try using pkg-config to get the directories and then use these values
   # in the find_path() and find_library() calls
   find_package(PkgConfig QUIET)
   PKG_CHECK_MODULES(PC_LIBFFI QUIET libffi)
endif ()

find_library(SDL2_LIBRARY NAMES SDL2 libSDL2
        PATHS $ENV{SDL2_DIR} ${SDL2_DIR} /usr /usr/local /opt/local
        PATH_SUFFIXES lib lib64 x86_64-linux-gnu lib/x86_64-linux-gnu
        HINTS ${PC_LIBSDL2_LIBDIR} ${PC_LIBSDL2_LIBRARY_DIRS}
)

find_path(SDL2_INCLUDE_DIR SDL.h
          PATHS $ENV{SDL2_DIR} ${SDL2_DIR} /usr /usr/local /opt/local
          PATH_SUFFIXES include include/SDL2 include/x86_64-linux-gnu x86_64-linux-gnu
          HINTS ${PC_LIBSDL2_INCLUDEDIR} ${PC_LIBSDL2_INCLUDE_DIRS}
         )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set SDL2_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(SDL2  DEFAULT_MSG
                                  SDL2_LIBRARY SDL2_INCLUDE_DIR)
mark_as_advanced(SDL2_INCLUDE_DIR SDL2_LIBRARY)

if(SDL2_FOUND)
    set(SDL2_LIBRARIES ${SDL2_LIBRARY})
    set(SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIR})
else(SDL2_FOUND)
    message(FATAL_ERROR "SDL2 was not found.")
endif(SDL2_FOUND) 
