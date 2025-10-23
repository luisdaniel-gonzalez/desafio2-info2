#ifndef ARTISTA_H
#define ARTISTA_H
#include "album.h"

class Artista
{
private:
    int codigo;
    string nombre;
    int edad;
    string pais;
    int seguidores;
    int posicion;
    Album *albumes;
    int numAlbumes;
    int ranking;

public:
    Artista();
    Artista(int cod,string nom, int ed, string p);
    Artista(const Artista &copia);

    ~Artista();

    void agregarAlbum(const Album &a);
    void mostrar() const;

    int getCodigo() const;
    string getNombre() const;
    string getPais() const;
    int getEdad() const;

    void setSeguidores(int s);
    void setRanking(float r);
};
#endif // ARTISTA_H
