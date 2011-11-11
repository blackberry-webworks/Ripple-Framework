find_package(Qt4 COMPONENTS QtCore QtGui QtXml QtSql QtNetwork QtWebKit REQUIRED)
include(${QT_USE_FILE})

SET(RIPPLELIBRARY_INCLUDE_DIRECTORIES
    "${CMAKE_BINARY_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_SOURCE_DIR}/qjson/include"
)

LIST(APPEND RIPPLELIBRARY_HEADERS
    ConfigData.h
    PortScanner.h
    RemoteDebugger.h
    TCPChannel/TCPBridge.h
    TCPChannel/TCPBridgeWorker.h
    TCPChannel/Message.h
    TCPChannel/MessageHandler.h
    TCPChannel/TCPMessageHandler.h
)

LIST(APPEND RIPPLELIBRARY_SOURCES
    ConfigData.cpp
    QtStageWebView.cpp
    StageViewMsgHandler.cpp
    PortScanner.cpp
    ScrollHandler.cpp
    RemoteDebugger.cpp
    TCPChannel/TCPBridge.cpp
    TCPChannel/TCPBridgeWorker.cpp
    TCPChannel/Message.cpp
    TCPChannel/MessageHandler.cpp
    TCPChannel/TCPMessageHandler.cpp
)

SET(RIPPLELIBRARY_MOC_HEADERS
    QtStageWebView.h
    StageViewMsgHandler.h
    ScrollHandler.h
    RemoteDebugger.h
    TCPChannel/TCPBridge.h
    TCPChannel/TCPBridgeWorker.h
    TCPChannel/MessageHandler.h
    TCPChannel/TCPMessageHandler.h
)

QT4_WRAP_CPP(RIPPLELIBRARY_MOC_SRCS ${RIPPLELIBRARY_MOC_HEADERS})

LIST(APPEND RIPPLELIBRARY_SOURCES ${RIPPLELIBRARY_HEADERS})
LIST(APPEND RIPPLELIBRARY_SOURCES ${RIPPLELIBRARY_MOC_HEADERS})
LIST(APPEND RIPPLELIBRARY_SOURCES ${RIPPLELIBRARY_MOC_SRCS})

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${RIPPLELIBRARY_INCLUDE_DIRECTORIES})
include_directories(${QT_INCLUDE_DIR})

ADD_LIBRARY(RippleLibrary ${RIPPLELIBRARY_SOURCES})
TARGET_LINK_LIBRARIES(RippleLibrary ${QT_LIBRARIES})