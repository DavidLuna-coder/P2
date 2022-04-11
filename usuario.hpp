#ifndef _CLAVE_
#define _CLAVE_
#include "cadena.hpp"
#include <map>
#include <unordered_map>
#include <unordered_set>

// todo  --- Usuario Constructor ---
// todo  --- Usuario Métodos observadores ---
// todo  --- Usuario Invalido ---
// todo  --- Usuario Asociaciones ---
// todo  --- Operadores de Flujo ---

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

    const Cadena &id() const;
    const Cadena &nombre() const;
    const Cadena &apellidos() const;
    const Cadena &direccion() const;
    const Tarjetas &tarjetas() const;
    const Articulos &compra() const;

    void es_titular_de(const Tarjeta &);
    void no_es_titular_de(const Tarjeta &);
    void compra(const Articulo &A, int cantidad = 1);
    int n_articulos() const;

    class Id_duplicado
    {
    public:
        Id_duplicado(const Cadena &id);
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
#endif