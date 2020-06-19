TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH += "C:/SFML-2.5.1/include"
LIBS += -L"C:/SFML-2.5.1/lib"
CONFIG(debug, debug|release){
    LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-system-d -lsfml-window-d
} else {
    LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-system -lsfml-window
}

SOURCES += \
        coin_class.cpp \
        enemy_class.cpp \
        main.cpp \
        map_class.cpp \
        platform_class.cpp \
        player_class.cpp

HEADERS += \
    coin_class.h \
    enemy_class.h \
    entity.h \
    hitbox.h \
    map_class.h \
    platform_class.h \
    player_class.h
