#ifndef USUARIOPREMIUM_H
#define USUARIOPREMIUM_H

#include "usuario.h"

class UsuarioPremium : public Usuario {
private:
    // Cancion** listaDeFavoritos;
    int capacidadFavoritos[10000];
    int cantidadFavoritos;
    UsuarioPremium* siguiente;

public:

    UsuarioPremium();
    UsuarioPremium(const char* nick, const char* tipo, const char* ciudad, const char* pais, const char* fecha);
    UsuarioPremium(const UsuarioPremium& otro);

    ~UsuarioPremium();

    int getCalidadAudio() const;
    int getCantidadFavoritos() const;
    //Cancion** getListaDeFavoritos() const;
    UsuarioPremium* getSiguiente() const;

    void setSiguiente(UsuarioPremium* usuario);

    void editarFavoritos();
    void seguirLista(UsuarioPremium* otroUsuario);
    void ajustarLista();

   // bool agregarFavorito(Cancion* cancion);
    bool eliminarFavorito(int indice);

    void mostrarInfo() const;

    UsuarioPremium& operator=(const UsuarioPremium& otro);
    //Cancion* operator[](int indice) const;
};

#endif // USUARIOPREMIUM_H
