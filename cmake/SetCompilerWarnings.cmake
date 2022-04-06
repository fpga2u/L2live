# Compiler warnings

# Store origin compile flags
set(CMAKE_C_FLAGS_ORIGIN ${CMAKE_C_FLAGS})
set(CMAKE_CXX_FLAGS_ORIGIN ${CMAKE_CXX_FLAGS})

# Create custom compile flags
set(CMAKE_C_FLAGS_CUSTOM ${CMAKE_C_FLAGS})
set(CMAKE_CXX_FLAGS_CUSTOM ${CMAKE_CXX_FLAGS})

if(MSVC)

  # Set warnings level 4
  set(CMAKE_C_WARNING_LEVEL 4)
  set(CMAKE_CXX_WARNING_LEVEL 4)
  if(CMAKE_C_FLAGS_CUSTOM MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_C_FLAGS_CUSTOM ${CMAKE_C_FLAGS_CUSTOM})
  else()
    set(CMAKE_C_FLAGS_CUSTOM "${CMAKE_C_FLAGS_CUSTOM} /W4")
  endif()
  if(CMAKE_CXX_FLAGS_CUSTOM MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS_CUSTOM ${CMAKE_CXX_FLAGS_CUSTOM})
  else()
    set(CMAKE_CXX_FLAGS_CUSTOM "${CMAKE_CXX_FLAGS_CUSTOM} /W4")
  endif()

  # Make all warnings into errors and increases the number of sections that an object file can contain
  if(CMAKE_WARN_AS_ERROR)
    set(CMAKE_C_FLAGS_CUSTOM "${CMAKE_C_FLAGS_CUSTOM} /WX /bigobj") # /utf-8
    set(CMAKE_CXX_FLAGS_CUSTOM "${CMAKE_CXX_FLAGS_CUSTOM} /WX /bigobj") # /utf-8
    message(STATUS "----- CMAKE_WARN_AS_ERROR ON -----")
  else()
    message(STATUS "----- CMAKE_WARN_AS_ERROR OFF -----")
  endif()

  # Common compile flags
  # C4100: 'identifier' : unreferenced formal parameter
  # C4250: 'class1' : inherits 'class2::member' via dominance
  set(COMMON_COMPILE_FLAGS "/wd4100 /wd4250")

  # # C4244: 'conversion' conversion from 'type1' to 'type2', possible loss of data
  # set(COMMON_COMPILE_FLAGS "${COMMON_COMPILE_FLAGS} /wd4244") [NOT good to open THIS]

  # # C4127: conditional expression is constant
  set(COMMON_COMPILE_FLAGS "${COMMON_COMPILE_FLAGS} /wd4127")

  # # C4458: declaration of 'identifier' hides class member [ activeMQ ]
  set(COMMON_COMPILE_FLAGS "${COMMON_COMPILE_FLAGS} /wd4458")

  # Pedantic compile flags
  set(PEDANTIC_COMPILE_FLAGS ${COMMON_COMPILE_FLAGS})

else()
  # GCC flags
    set(CMAKE_CXX_FLAGS_CUSTOM "${CMAKE_CXX_FLAGS_CUSTOM} -pthread -std=c++17 -lstdc++fs")

  # Make all warnings into errors
  if(CMAKE_WARN_AS_ERROR)
    set(CMAKE_C_FLAGS_CUSTOM "${CMAKE_C_FLAGS_CUSTOM} -Wall -Werror")
    set(CMAKE_CXX_FLAGS_CUSTOM "${CMAKE_CXX_FLAGS_CUSTOM} -Wall -Wno-reorder -Wno-deprecated -Werror")
    message(STATUS "----- CMAKE_WARN_AS_ERROR ON -----")
  else()
    message(STATUS "----- CMAKE_WARN_AS_ERROR OFF -----")
  endif()

  # Common compile flags
  message( STATUS "COMMON_COMPILE_FLAGS = " ${COMMON_COMPILE_FLAGS} )
  set(COMMON_COMPILE_FLAGS "")

  # Pedantic compile flags
  set(PEDANTIC_COMPILE_FLAGS "${COMMON_COMPILE_FLAGS} -pedantic")

endif()

# Update compile flags
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS_CUSTOM})
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS_CUSTOM})

message( STATUS "COMPILE_FLAGS = " ${COMPILE_FLAGS})
message( STATUS "CMAKE_C_FLAGS = " ${CMAKE_C_FLAGS} )
message( STATUS "CMAKE_CXX_FLAGS = " ${CMAKE_CXX_FLAGS} )
message( STATUS "PEDANTIC_COMPILE_FLAGS = " ${PEDANTIC_COMPILE_FLAGS} )
