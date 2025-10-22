#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include "usuario.h"
#include "publicidad.h"
//#include "artista.h" // Lo hace jean

class Plataforma {
private:
    Usuario* usuarios[100];
    //Artista* artistas[50];
    Publicidad* publicidades[50];

    int numUsuarios;
    int numArtistas;
    int numPublicidades;

    Usuario* usuarioActual;
    int ultimaPublicidadMostrada;

    char* copiarString(const char* str);
    int compararStrings(const char* str1, const char* str2) const;

public:
    Plataforma();
    ~Plataforma();

    void cargarDatos();
    void guardarDatos();

    bool agregarUsuario(Usuario* usuario);
    //bool agregarArtista(Artista* artista);
    bool agregarPublicidad(Publicidad* pub);

    bool buscarUsuario(const char* nickname);
    Usuario* obtenerUsuario(const char* nickname);

    bool iniciarSesion(const char* nickname);
    void cerrarSesion();
    Usuario* getUsuarioActual() const;

    void reproduccionAleatoria();
    void mostrarPublicidadPonderada();

    void gestionarListaFavoritos();
    void mostrarMenu();

    void medirConsumoRecursos(int iteraciones) const;
    int calcularMemoriaTotal() const;

    int getCantidadUsuarios() const;
    int getCantidadPublicidades() const;
    int getCantidadArtistas() const;

    void mostrarReproduccion(const char* mensajePublicidad,
                             char categoriaPublicidad,
                             const char* cantante,
                             const char* album,
                             const char* rutaPortada,
                             const char* tituloCancion,
                             const char* rutaAudio,
                             int duracionSegundos);
};

#endif // PLATAFORMA_H
