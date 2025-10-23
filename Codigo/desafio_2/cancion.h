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

public:
    Cancion();
    Cancion(string nom,int id, float dur,string rut);
    Cancion(const Cancion &copia);

    ~Cancion();

    void agregarCredito(const Creditos &c);
    void reproducir(int calidad) const;
    void mostrar() const;

    int getId() const;
    string getNombre() const;
    float getDuracion() const;
    int getReproducciones() const;
    string getRuta() const;
};

#endif // CANCION_H
