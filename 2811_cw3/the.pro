QT += core gui widgets multimedia multimediawidgets

CONFIG += c++11


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        ctrlbuttons.cpp \
        the_button.cpp \
        the_player.cpp \
        tomeo.cpp

HEADERS += \
    ctrlbuttons.h \
    the_button.h \
    the_player.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Icons/playerIcons.qrc

DISTFILES += \
    Icons/back.svg \
    Icons/fast-forward.svg \
    Icons/list.svg \
    Icons/magnifying-glass.svg \
    Icons/next.svg \
    Icons/pause.svg \
    Icons/play-button.svg \
    Icons/rewind.svg \
    Icons/speaker-mute.svg \
    Icons/speaker.svg

