#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include "usuario.h"
#include "artista.h"

class Publicidad;

class Plataforma {
private:
    Usuario* usuarios[100];
    Artista* artistas[50];
    Publicidad* publicidades[50];

    int numUsuarios;
    int numArtistas;
    int numPublicidades;
    int contadorCanciones;

    Usuario* usuarioActual;
    int ultimaPublicidadMostrada;

    char* copiarString(const char* str);
    int compararStrings(const char* str1, const char* str2) const;

public:
    Plataforma();
    ~Plataforma();

    void cargarDatos(const string &nombreArchivo, Plataforma &plataforma);
    void guardarDatos();

    bool agregarUsuario(Usuario* usuario);
    bool agregarPublicidad(Publicidad* pub);

    bool buscarUsuario(const char* nickname);
    Usuario* obtenerUsuario(const char* nickname);
    Usuario* obtenerContrasena(const char* contrasena);

    bool iniciarSesion(const char* nickname, const char* contrasena);
    void cerrarSesion();
    Usuario* getUsuarioActual() const;

    void reproduccionAleatoria();
    void mostrarPublicidadPonderada();

    void mostrarUsuarios();
    void mostrarArtistas();
    void mostrarPublicidades();

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
                             int duracionSegundos,
                             bool modoRepetir,
                             Usuario* usuario);
};

#endif // PLATAFORMA_H
