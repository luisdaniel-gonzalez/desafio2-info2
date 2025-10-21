TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        plataforma/plataforma.cpp \
        publicidad/publicidad.cpp \
        usuario/usuario.cpp \
        usuarioEstandar/usuarioEstandar.cpp \
        usuarioPremium/usuarioPremium.cpp

HEADERS += \
    plataforma/plataforma.h \
    publicidad/publicidad.h \
    usuario/usuario.h \
    usuarioEstandar/usuarioEstandar.h \
    usuarioPremium/usuarioPremium.h
