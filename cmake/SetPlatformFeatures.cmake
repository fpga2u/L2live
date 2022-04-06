# Platform features

get_directory_property( DirDefs_old COMPILE_DEFINITIONS )

if(CYGWIN)

  # Base Windows platform
  add_definitions(-DWIN32)

  # Windows 10
  # add_definitions(-D_WIN32_WINNT=0x0A00)

elseif(WIN32)

  # Base Windows platform
  add_definitions(-DWIN32)

  # Disable CRT secure warnings
  add_definitions(-D_CRT_SECURE_NO_DEPRECATE)

  # Disable C++17 deprecation warnings
  add_definitions(-D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)

  # Windows 10
  # add_definitions(-D_WIN32_WINNT=0x0A00)

  # Windows SDK
  # if(MINGW OR CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION STREQUAL "")
  #   string(REGEX REPLACE "^([0-9]+)\\.([0-9]+)\\.([0-9]+)$" "\\3" CMAKE_WIN32_SDK ${CMAKE_SYSTEM_VERSION})
  # else()
  #   string(REGEX REPLACE "^([0-9]+)\\.([0-9]+)\\.([0-9]+)\\.([0-9]+)$" "\\3" CMAKE_WIN32_SDK ${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION})
  # endif()
  # add_definitions(-D_WIN32_SDK=${CMAKE_WIN32_SDK})

endif()

if (WIN32)
    macro(get_WIN32_WINNT version)
        if (CMAKE_SYSTEM_VERSION)
            set(ver ${CMAKE_SYSTEM_VERSION})
            string(REGEX MATCH "^([0-9]+).([0-9])" ver ${ver})
            string(REGEX MATCH "^([0-9]+)" verMajor ${ver})
            # Check for Windows 10, b/c we'll need to convert to hex 'A'.
            if ("${verMajor}" MATCHES "10")
                set(verMajor "A")
                string(REGEX REPLACE "^([0-9]+)" ${verMajor} ver ${ver})
            endif ("${verMajor}" MATCHES "10")
            # Remove all remaining '.' characters.
            string(REPLACE "." "" ver ${ver})
            # Prepend each digit with a zero.
            string(REGEX REPLACE "([0-9A-Z])" "0\\1" ver ${ver})
            set(${version} "0x${ver}")
        endif(CMAKE_SYSTEM_VERSION)
    endmacro(get_WIN32_WINNT)

    get_WIN32_WINNT(ver)
    add_definitions(-D_WIN32_WINNT=${ver})
endif(WIN32)

get_directory_property( DirDefs COMPILE_DEFINITIONS )
foreach( d ${DirDefs} )
    if(NOT ($(d) IN_LIST $(DirDefs_old)))
        message( STATUS "Platform features Define: " ${d} )
    endif()
      
endforeach( d ${DirDefs} )
