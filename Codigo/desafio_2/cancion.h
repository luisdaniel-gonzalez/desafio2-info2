#ifndef CANCION_H
#define CANCION_H
#include "creditos.h"

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
    int idAlbum;
public:
    Cancion();
    Cancion(string nom,int id, float dur,string rut);
    Cancion(const Cancion &copia);

    ~Cancion();

    void agregarCredito(const Creditos &c);
    void reproducir(int calidad) const;
    void mostrar() const;
    int getId() const;
    int getIdAlbum() const;
    string getNombre() const;
    string getRutaBase() const;
    float getDuracion() const;
    int getReproducciones() const;
    string Ruta() const;
    void setReproducciones(int newReproducciones);
    void cargarCanciones(const string &nombreArchivo, Cancion *&canciones, int &numCanciones);
};

#endif // CANCION_H
