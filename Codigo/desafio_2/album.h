#ifndef ALBUM_H
#define ALBUM_H
#include <iostream>
#include <string>

using namespace std;
#include "cancion.h"
class album
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
    cancion *canciones;
    int numcanciones;

public:
    album();
    album(string nom,int cod, string fecha, string sello, string portada);
    album(const album &copia);

    ~Album();

    void agregarGenero(const string &g);
    void agregarCancion(const cancion &c);
};

#endif // ALBUM_H
