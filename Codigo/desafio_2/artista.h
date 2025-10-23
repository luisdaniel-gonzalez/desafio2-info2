#ifndef ARTISTA_H
#define ARTISTA_H
#include <iostream>
#include <string>

using namespace std;
#include "album.h"

class artista
{
private:
    int codigo;
    string nombre;
    int edad;
    string pais;
    int seguidores;
    int posicion;
    alum *albumes;
    int numAlbumes;

public:
    artista();
    artista(int cod,string nom, int ed, string pais);
    artista(const artista &copia);

    ~Artista();

    void agregarAlbum(const album &a);
    void mostrar() const;

    int getCodigo() const;
    string getNombre;
};

#endif // ARTISTA_H
