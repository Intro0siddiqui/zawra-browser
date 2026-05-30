list(APPEND WTF_PUBLIC_HEADERS
    SocketMonitor.h
)

list(APPEND WTF_SOURCES
    SocketMonitor.cpp
)

list(APPEND WTF_PRIVATE_INCLUDE_DIRECTORIES
    "${CMAKE_SOURCE_DIR}/../../patches/webkit/Source/WTF/wtf"
)