# Try to find UUID library and include path.
# Once done this will define
#
# S4libLite_FOUND
# S4libLite_INCLUDE_DIR
# S4libLite_LIBRARIES

set(INCLUDE_PREX S4)
set(HEADER_FILE common/s4logger.h)
SET(S4libLite_NAMES S4libLite)

FIND_PATH(S4libLite_INCLUDE_DIR ${HEADER_FILE}
        HINTS
        ${S4libLite_ROOT}/include
        PATHS
        /usr/local/include
        /usr/include
        /usr/local/${INCLUDE_PREX}/include
        /usr/local/${INCLUDE_PREX}/include/${LIB_FILE}
        )
IF (S4libLite_INCLUDE_DIR)
    message(STATUS "Found S4libLite_INCLUDE_DIR = ${S4libLite_INCLUDE_DIR}")
ELSE (S4libLite_INCLUDE_DIR)
    message(STATUS "Not found S4libLite_INCLUDE_DIR")
ENDIF (S4libLite_INCLUDE_DIR)
foreach(S4libLite ${S4libLite_NAMES})
    FIND_LIBRARY(S4libLite_LIBRARY_${S4libLite}
            NAMES ${S4libLite}
            HINTS
            ${S4libLite_ROOT}/lib
            PATHS
            /usr/lib
            /usr/local/lib
            /usr/local/${INCLUDE_PREX}/lib
            /usr/local/${INCLUDE_PREX}/lib/${LIB_FILE}
            )
    IF (S4libLite_LIBRARY_${S4libLite})
        list(APPEND S4libLite_LIBRARIES "${S4libLite_LIBRARY_${S4libLite}}")
    endif()
endforeach()

IF (S4libLite_LIBRARIES)
    message(STATUS "Found S4libLite_LIBRARIES = ${S4libLite_LIBRARIES}")
ELSE (S4libLite_LIBRARIES)
    message(STATUS "Not found S4libLite_LIBRARIES")
ENDIF (S4libLite_LIBRARIES)

IF (S4libLite_LIBRARIES AND S4libLite_INCLUDE_DIR)
    SET(S4libLite_FOUND "YES")
ELSE (S4libLite_LIBRARIES AND S4libLite_INCLUDE_DIR)
    SET(S4libLite_FOUND "NO")
ENDIF (S4libLite_LIBRARIES AND S4libLite_INCLUDE_DIR)


IF (S4libLite_FOUND)
    IF (NOT S4libLite_FIND_QUIETLY)
        MESSAGE(STATUS "Found S4libLite headers: ${S4libLite_INCLUDE_DIR}")
        MESSAGE(STATUS "Found S4libLite library: ${S4libLite_LIBRARIES}")
    ENDIF (NOT S4libLite_FIND_QUIETLY)
ELSE (S4libLite_FOUND)
    IF (S4libLite_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find S4libLite library")
    ENDIF (S4libLite_FIND_REQUIRED)
ENDIF (S4libLite_FOUND)

# message(STATUS "S4libLite_INCLUDE_DIR = ${S4libLite_INCLUDE_DIR}")
# message(STATUS "S4libLite_LIBRARY = ${S4libLite_LIBRARY}")

# Handle the REQUIRED argument and set S4libLite_FOUND
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(S4libLite DEFAULT_MSG S4libLite_LIBRARIES S4libLite_INCLUDE_DIR)

mark_as_advanced(S4libLite_INCLUDE_DIR)
mark_as_advanced(S4libLite_LIBRARIES)

