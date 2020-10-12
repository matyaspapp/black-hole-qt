QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
RESOURCES += \
    assets/images/player1.png \
    assets/images/player1_targeted.png \
    assets/images/player2.png \
    assets/images/player2_targeted.png \
    assets/images/black_hole.gif \

SOURCES += \
    main.cpp \
    view/blackholeview.cpp \
    model/blackholemodel.cpp \
    data/savegame.cpp \
    data/loadgame.cpp \
    data/blackholedataaccess.cpp \

HEADERS += \
    view/blackholeview.h \
    model/blackholemodel.h \
    data/savegame.h \
    data/loadgame.h \
    data/blackholedataaccess.h \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
