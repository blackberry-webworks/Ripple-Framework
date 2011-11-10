find_package(Qt4 COMPONENTS QtCore REQUIRED)
include(${QT_USE_FILE})

SET(QJSON_INCLUDE_DIRECTORIES
    "${CMAKE_BINARY_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_SOURCE_DIR}/qjson/include"
)

LIST(APPEND QJSON_HEADERS
)

LIST(APPEND QJSON_SOURCES
    parser.cpp
    qobjecthelper.cpp
    json_scanner.cpp
    json_parser.cc
    parserrunnable.cpp
    serializer.cpp
    serializerrunnable.cpp
)

SET(QJSON_MOC_HEADERS
    parserrunnable.h
    serializerrunnable.h
)

QT4_WRAP_CPP(QJSON_MOC_SRCS ${QJSON_MOC_HEADERS})

LIST(APPEND QJSON_SOURCES ${QJSON_HEADERS})
LIST(APPEND QJSON_SOURCES ${QJSON_MOC_HEADERS})
LIST(APPEND QJSON_SOURCES ${QJSON_MOC_SRCS})

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${QJSON_INCLUDE_DIRECTORIES})
include_directories(${QT_INCLUDE_DIR})

ADD_LIBRARY(${QJSON_LIBRARY_NAME} ${QJSON_SOURCES})
TARGET_LINK_LIBRARIES(${QJSON_LIBRARY_NAME} ${QT_LIBRARIES})
