Qt += network serialport

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/VLink_Links/VLink.h \
    $$PWD/Vlink_Packs/VLink_Pack.h \
    $$PWD/VLink_Defines.h \
    $$PWD/Mng_Connection.h \
    $$PWD/VLink_Infos/LinkInfo.h \
    $$PWD/VLink_Infos/TCPClient_Info.h \
    $$PWD/VLink_Infos/TCPServer_Info.h \
    $$PWD/VLink_Infos/UDP_Info.h \
    $$PWD/VLink_Links/UDP_VLink.h \
    $$PWD/VLink_Communication.h \
    $$PWD/VLink_LinkManager.h \
    $$PWD/VLink_PackManager.h \
    $$PWD/VLink_Links/Serial_VLink.h \
    $$PWD/VLink_Infos/Serial_Info.h

SOURCES += \
    $$PWD/VLink_Links/VLink.cpp \
    $$PWD/Vlink_Packs/VLink_Pack.cpp \
    $$PWD/Mng_Connection.cpp \
    $$PWD/VLink_Infos/LinkInfo.cpp \
    $$PWD/VLink_Infos/TCPClient_Info.cpp \
    $$PWD/VLink_Infos/TCPServer_Info.cpp \
    $$PWD/VLink_Infos/UDP_Info.cpp \
    $$PWD/VLink_Links/UDP_VLink.cpp \
    $$PWD/VLink_Communication.cpp \
    $$PWD/VLink_LinkManager.cpp \
    $$PWD/VLink_PackManager.cpp \
    $$PWD/VLink_Links/Serial_VLink.cpp \
    $$PWD/VLink_Infos/Serial_Info.cpp

