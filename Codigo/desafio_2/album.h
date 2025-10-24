#ifndef ALBUM_H
#define ALBUM_H
#include "cancion.h"

class Album
{
private:
    string nombre;
    int codigo;
    string fechaDeLanzamiento;
    string sello;
    string rutaPortada;
    string genero[4];
    int numGeneros;
    float puntuacion;
    float duracionTotal;
    Cancion *canciones;
    int numcanciones;
    int IdAlbum;

public:
    Album();
    Album(string nom,int cod, string fecha, string sello, string portada);
    Album(const Album &copia);

    ~Album();

    void agregarGenero(const string &g);
    void agregarCancion(const Cancion &c);
    void mostrar() const;

    float getPuntuacion() const;
    string getNombre() const;
    string getPortada() const;
    int getIdAlbum() const;
    void setPuntuacion(float p);
    void cargarAlbumes(const string &nombreArchivo, Album *&albumes, int &numAlbumes);
};

#endif // ALBUM_H
