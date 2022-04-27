#ifndef _CLAVE_
#define _CLAVE_
#include "cadena.hpp"
#include <map>
#include <unordered_map>
#include <unordered_set>


class Cadena;
class Tarjeta;
class Numero;
class Articulo;

class Clave
{
public:
    Clave(const char *clave);

    enum Razon
    {
        CORTA,
        ERROR_CRYPT
    };
    class Incorrecta
    {
    public:
        Incorrecta(Razon r_) : razon_(r_){};
        Razon razon() const;

    private:
        Razon razon_;
    };

    const Cadena &clave() const;
    bool verifica(const char *clave) const;

private:
    Cadena clave_;
};

class Usuario
{
public:
    typedef std::map<Numero, Tarjeta *> Tarjetas;
    typedef std::unordered_map<Articulo *, unsigned int> Articulos;

    Usuario(const Cadena &id, const Cadena &nom, const Cadena &apell, const Cadena &dir, const Clave &cl);
    Usuario(const Usuario &) = delete;
    Usuario &operator=(const Usuario &U) = delete;

    const Cadena &id() const {return id_;}
    const Cadena &nombre() const{return nom_;}
    const Cadena &apellidos() const{return apell_;}
    const Cadena &direccion() const{return dir_;}
    const Tarjetas &tarjetas() const{return T;}
    const Articulos &compra() const{return A;}

    void es_titular_de(Tarjeta &);
    void no_es_titular_de(Tarjeta &);
    void compra(Articulo &A, int cantidad = 1);
    int n_articulos() const;

    friend std::ostream& operator << (std::ostream& os, const Usuario& U);


    class Id_duplicado
    {
    public:
        Id_duplicado(const Cadena &id):idd_(id){};
        Cadena idd() const { return idd_; }

    private:
        Cadena idd_;
    };
    ~Usuario();

private:
    typedef std::unordered_set<Cadena> IDs;
    static IDs IDs_;
    const Cadena id_;
    const Cadena nom_;
    const Cadena apell_;
    const Cadena dir_;
    Clave cl_;
    Tarjetas T;
    Articulos A;
};

inline const Cadena &Clave::clave() const
{
    return clave_;
}
inline typename Clave::Razon Clave::Incorrecta::razon() const
{
    return Clave::Incorrecta::razon_;
}

std::ostream& operator << (std::ostream& os, const Usuario& U);

std::ostream& mostrar_carro(std::ostream& os,const Usuario& U);
#endif