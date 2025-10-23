#ifndef USUARIO_H
#define USUARIO_H

class Usuario {
protected:
    char* nickname;
    char* tipoDeMembresia;
    char* ciudad;
    char* pais;
    char* fechaDeRegistro;
    char* contrasena;

    char* copiarString(const char* str);

public:

    Usuario();
    Usuario(const char* nick, const char* tipo, const char* ciudad, const char* pais, const char* fecha);
    Usuario(const Usuario& otro);

    virtual ~Usuario();

    const char* getNickname() const;
    const char* getTipoDeMembresia() const;
    const char* getCiudad() const;
    const char* getPais() const;
    const char* getFechaDeRegistro() const;


    void setNickname(const char* nick);
    void setTipoDeMembresia(const char* tipo);
    void setCiudad(const char* ciudad);
    void setPais(const char* pais);
    void setFechaDeRegistro(const char* fecha);

    virtual void mostrarInfo() const;
    virtual int getCalidadAudio() const = 0;

    virtual void reproduccionAleatoria();
    virtual void mostrarPublicidad();
    virtual void iniciaSesion();

    bool operator==(const Usuario& otro) const;
    Usuario& operator=(const Usuario& otro);
    char *getContrasena() const;
};

#endif // USUARIO_H
