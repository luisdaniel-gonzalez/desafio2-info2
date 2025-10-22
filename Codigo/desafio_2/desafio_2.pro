TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        plataforma.cpp \
        plataforma/plataforma.cpp \
        publicidad.cpp \
        publicidad/publicidad.cpp \
        usuario.cpp \
        usuario/usuario.cpp \
        usuarioEstandar.cpp \
        usuarioEstandar/usuarioEstandar.cpp \
        usuarioPremium.cpp \
        usuarioPremium/usuarioPremium.cpp

HEADERS += \
    plataforma.h \
    plataforma/plataforma.h \
    publicidad.h \
    publicidad/publicidad.h \
    usuario.h \
    usuario/usuario.h \
    usuarioEstandar.h \
    usuarioEstandar/usuarioEstandar.h \
    usuarioPremium.h \
    usuarioPremium/usuarioPremium.h
