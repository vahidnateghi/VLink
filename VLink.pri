Qt += network

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/Link/VLink.h \
    $$PWD/Pack/VLink_Pack.h \
    $$PWD/VLink_Defines.h \
    $$PWD/Mng_Connection.h \
    $$PWD/LinkInfo/LinkInfo.h \
    $$PWD/LinkInfo/TCPClient_Info.h \
    $$PWD/LinkInfo/TCPServer_Info.h \
    $$PWD/LinkInfo/UDP_Info.h \
    $$PWD/Link/UDP_VLink.h \
    $$PWD/VLink_Communication.h \
    $$PWD/VLink_LinkManager.h \
    $$PWD/VLink_PackManager.h

SOURCES += \
    $$PWD/Link/VLink.cpp \
    $$PWD/Pack/VLink_Pack.cpp \
    $$PWD/Mng_Connection.cpp \
    $$PWD/LinkInfo/LinkInfo.cpp \
    $$PWD/LinkInfo/TCPClient_Info.cpp \
    $$PWD/LinkInfo/TCPServer_Info.cpp \
    $$PWD/LinkInfo/UDP_Info.cpp \
    $$PWD/Link/UDP_VLink.cpp \
    $$PWD/VLink_Communication.cpp \
    $$PWD/VLink_LinkManager.cpp \
    $$PWD/VLink_PackManager.cpp

