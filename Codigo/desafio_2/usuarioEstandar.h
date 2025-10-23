#ifndef USUARIOESTANDAR_H
#define USUARIOESTANDAR_H

#include "usuario.h"

class UsuarioEstandar : public Usuario {
private:

    int anuncios;

public:

    UsuarioEstandar();
    UsuarioEstandar(const char* nick, const char* tipo, const char* ciudad, const char* pais, const char* fecha);
    UsuarioEstandar(const UsuarioEstandar& otro);

    ~UsuarioEstandar();

    int getAnuncios() const;
    int getCalidadAudio() const;

    void setAnuncios(int cantidad);

    void reproducirMusica();
    void mostrarInfo() const;
    void mostrarPublicidad();

    UsuarioEstandar& operator=(const UsuarioEstandar& otro);
};

#endif // USUARIO_ESTANDAR_H
