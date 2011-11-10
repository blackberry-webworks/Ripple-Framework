CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(Ripple)


# -----------------------------------------------------------------------------
# Determine the target processor
# -----------------------------------------------------------------------------
IF (CMAKE_SYSTEM_PROCESSOR MATCHES "(arm|xscale)")
    SET(WTF_CPU_ARM 1)
    add_definitions(-DWTF_CPU_ARM=1)
ELSEIF (CMAKE_SYSTEM_PROCESSOR MATCHES "(x86_64)")
    SET(WTF_CPU_X86_64 1)
    add_definitions(-DWTF_CPU_X86_64=1)
ELSEIF (CMAKE_SYSTEM_PROCESSOR MATCHES "(i[3-6]86|x86)")
    SET(WTF_CPU_X86 1)
    add_definitions(-DWTF_CPU_X86=1)
ELSE ()
    MESSAGE(FATAL_ERROR "Unknown CPU '${CMAKE_SYSTEM_PROCESSOR}'")
ENDIF ()

#don't link the boot datatime library
ADD_DEFINITIONS(-DBOOST_DATE_TIME_NO_LIB)

# -----------------------------------------------------------------------------
# Determine the operating system
# -----------------------------------------------------------------------------
IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    SET(WTF_OS_UNIX 1)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    SET(WTF_OS_WINDOWS 1)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "RVCT")
    # FIXME: Better way of determining Olympia
    SET(WTF_OS_OLYMPIA 1)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    SET(WTF_OS_MAC_OS_X 1)
    #SET(CMAKE_OSX_ARCHITECTURES x86_64)
ELSE ()
    MESSAGE(WARNING "Unknown OS '${CMAKE_SYSTEM_NAME}'")
ENDIF ()

# -----------------------------------------------------------------------------
# Default target names (can be overrriden in Options${PORT}.cmake file)
# -----------------------------------------------------------------------------
SET(WebKit_LIBRARY_NAME WebKit)
SET(RIPPLELIBRARY_LIBRARY_NAME RippleLibrary)
SET(QJSON_LIBRARY_NAME qjson)

# -----------------------------------------------------------------------------
# Port-specific options
# -----------------------------------------------------------------------------
#INCLUDE(OptionsCommon)

SET(CMAKE_SRC ${CMAKE_SOURCE_DIR})
SET(CMAKE_SOURCE_DIR ${CMAKE_SRC})


# -----------------------------------------------------------------------------
# Add module directories
# -----------------------------------------------------------------------------
ADD_SUBDIRECTORY(RippleLibrary)
ADD_SUBDIRECTORY(Ripple)
ADD_SUBDIRECTORY(TestFramework)
ADD_SUBDIRECTORY(TCPClientTest)
ADD_SUBDIRECTORY(qjson/src)


ADD_DEPENDENCIES(Ripple
    ${QJSON_LIBRARY_NAME}
    ${RIPPLELIBRARY_LIBRARY_NAME} 
)

ADD_DEPENDENCIES(TestFramework
    ${RIPPLELIBRARY_LIBRARY_NAME}
    ${WebKit_LIBRARY_NAME}
    ${QJSON_LIBRARY_NAME}
)
