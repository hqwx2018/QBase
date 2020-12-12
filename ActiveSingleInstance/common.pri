QMAKE_CXXFLAGS += /MP /GS /EHsc
QMAKE_CXXFLAGS_RELEASE += /Zi /Ob1
QMAKE_LFLAGS_RELEASE += /DEBUG
QMAKE_LFLAGS_RELEASE += /OPT:REF /OPT:NOICF
QMAKE_LFLAGS += /MACHINE:X86
QMAKE_LFLAGS_DEBUG += /debugtype:cv,fixup

CharacterSet = 1
DEFINES += UNICODE
DEFINES += QT_MESSAGELOGCONTEXT
DEFINES += DEV_BUILD ## 默认
contains(DEFINES, OFFICIAL_BUILD){
    message("official build");
    DEFINES -= DEV_BUILD
    DEFINES -= TEST_BUILD
}
contains(DEFINES, DEV_BUILD){
    message("dev build");
}
contains(DEFINES, TEST_BUILD){
    message("test build");
    DEFINES += DEV_BUILD
}

CONFIG += c++14
CONFIG += precompile_header
CONFIG += skip_target_version_ext

CONFIG(debug, debug|release) {
    CONFIGURE = debug
} else {
    CONFIGURE = release
}

DESTDIR = $${BUILD_DIR}/$${CONFIGURE}/bin
QMAKE_LIBDIR += $${DESTDIR}

TEMP_DIR = $${BUILD_DIR}/$${CONFIGURE}/tmp
TARGET_TEMP_DIR = $${TEMP_DIR}/$${TARGET}
OBJECTS_DIR = $${TARGET_TEMP_DIR}/$${CONFIGURE}/obj

## 临时文件目录
MOC_DIR = $${TARGET_TEMP_DIR}/moc
RCC_DIR = $${TARGET_TEMP_DIR}/rcc
UI_DIR = $${TARGET_TEMP_DIR}/ui
UI_HEADERS_DIR = $${TARGET_TEMP_DIR}/ui
UI_SOURCES_DIR = $${TARGET_TEMP_DIR}/ui

message(BUILD_DIR = $${BUILD_DIR})
message(DESTDIR = $${DESTDIR})
message(OUT_PWD = $${OUT_PWD})
message(CONFIG = $${CONFIG})
message(TEMP_DIR = $${TEMP_DIR})
message(TARGET_TEMP_DIR = $${TARGET_TEMP_DIR})
message(OBJECTS_DIR = $${OBJECTS_DIR})
## -----------------------------------------------

INCLUDEPATH += $${MOC_DIR}
