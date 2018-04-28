QT += widgets

HEADERS = include/serialshot.h
SOURCES = src/main.cpp \
    src/serialshot.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/desktop/screenshot
INSTALLS += target
