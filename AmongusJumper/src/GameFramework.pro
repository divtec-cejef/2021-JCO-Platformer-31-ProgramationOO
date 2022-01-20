#-------------------------------------------------
#
# Project created by QtCreator 2014-01-31T13:38:06
#
#-------------------------------------------------

QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GameFramework
TEMPLATE = app

#DEFINES += DEBUG_SPRITE_COUNT
#DEFINES += DEBUG_BBOX
#DEFINES += DEBUG_SHAPE
#DEFINES += DEPLOY # Pour une compilation dans un but de déploiement

SOURCES += main.cpp\
    bulio.cpp \
    buliotickhandler.cpp \
    caisseamovible.cpp \
    caisseamovtickhandler.cpp \
    character.cpp \
    entity.cpp \
    entitytickhandler.cpp \
    ground.cpp \
    keytickhandler.cpp \
        mainfrm.cpp \
    gamescene.cpp \
    sprite.cpp \
    gamecore.cpp \
    resources.cpp \
    gameview.cpp \
    utilities.cpp \
    gamecanvas.cpp \
    spritetickhandler.cpp

HEADERS  += mainfrm.h \
    bulio.h \
    buliotickhandler.h \
    caisseamovible.h \
    caisseamovtickhandler.h \
    character.h \
    entity.h \
    entitytickhandler.h \
    gamescene.h \
    ground.h \
    keytickhandler.h \
    sprite.h \
    gamecore.h \
    resources.h \
    gameview.h \
    utilities.h \
    gamecanvas.h \
    spritetickhandler.h

FORMS    += mainfrm.ui
