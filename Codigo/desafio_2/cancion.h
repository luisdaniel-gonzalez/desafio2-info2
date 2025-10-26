#ifndef CANCION_H
#define CANCION_H
#include "creditos.h"

class Album;

class Cancion
{
private:
    string nombre;
    int id;
    float duracion;
    string ruta;
    int reproducciones;
    Creditos *creditos;
    int numCreditos;
    string rutaBase;
    string ruta128;
    string ruta320;
    string rutaPortada;
    int idAlbum;
    string nombreAlbum;
    string cantante;

public:
    Cancion();
    Cancion(int id, string nom, float dur,string rut);
    Cancion(const Cancion &copia);

    ~Cancion();

    void agregarCredito(const Creditos &c);
    void reproducir(int calidad) const;
    void mostrar() const;
    int getId() const;
    int getIdAlbum() const;
    string getNombre() const;
    string getRutaBase() const;
    string getCantante() const;
    string getRutaPortada() const;
    float getDuracion() const;
    int getReproducciones() const;
    string Ruta() const;
    void setReproducciones(int newReproducciones);
    void cargarCanciones(const string &nombreArchivo, Cancion *&canciones, int &numCanciones,
                         Album* albumes, int numAlbumes);

    void setRuta320(const string &ruta);
    void setRutaPortada(const string &ruta);
    void setNombreAlbum(const string &nombre);
    void setIdAlbum(int id);
    void setCantante(const string &c);

    string getRuta128() const;
    string getRuta320() const;
    string getNombreAlbum() const;

};

#endif // CANCION_H
