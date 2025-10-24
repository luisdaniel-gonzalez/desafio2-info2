TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
 
SOURCES += \
    album.cpp \
    artista.cpp \
    cancion.cpp \
    creditos.cpp \
    main.cpp \
    plataforma.cpp \
    publicidad.cpp \
    usuario.cpp \
    usuarioEstandar.cpp \
    usuarioPremium.cpp
 
HEADERS += \
    album.h \
    artista.h \
    cancion.h \
    creditos.h \
    plataforma.h \
    publicidad.h \
    usuario.h \
    usuarioEstandar.h \
    usuarioPremium.h