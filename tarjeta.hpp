#ifndef _TARJETA_
#define _TARJETA_

#include <unordered_set>
#include "fecha.hpp"
#include "numero.hpp"
class Usuario;
class Tarjeta
{
public:
    enum Tipo
    {
        Otro,
        VISA,
        Mastercard,
        Maestro,
        JCB,
        AmericanExpress
    };

    Tarjeta(const Numero &num, const Usuario &titular, const Fecha &f);
    Tarjeta(const Tarjeta &) = delete;
    Tarjeta &operator=(const Tarjeta &) = delete;

    const Numero &numero() const;
    const Usuario &titular() const;
    const Fecha &caducidad() const;
    bool activa() const;
    bool activa();
    const Tipo tipo();
    class Caducada
    {
    public:
        Caducada(const Fecha &F) : f(F){};
        const Fecha &cuando(){return f;};

    private:
        Fecha f;
    };
    private: 
    static std::unordered_set<Numero> tarjetas_;
    const Numero num_;
    const Usuario *titular_;
    const Fecha caducidad_;
    bool activa;
};

#endif