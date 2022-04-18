#ifndef _TARJETA_
#define _TARJETA_

#include <iostream>
#include <unordered_set>
#include "fecha.hpp"
#include "numero.hpp"
class Usuario;
class Tarjeta
{
public:
    static const Usuario* TITULAR_NULO;
    enum Tipo
    {
        Otro,
        VISA,
        Mastercard,
        Maestro,
        JCB,
        AmericanExpress
    };

    Tarjeta(const Numero &num,Usuario &titular, const Fecha &f);
    Tarjeta(const Tarjeta &) = delete;
    Tarjeta &operator=(const Tarjeta &) = delete;

    const Numero &numero() const{return num_;};
    const Usuario &titular() const{return *titular_;};
    const Fecha &caducidad() const{return caducidad_;};
    bool activa() const{return activa_;};
    bool activa(bool estado = true){activa_ = estado; return activa_;};
    const Tipo tipo() const;

    class Caducada
    {
    public:
        Caducada(const Fecha &F) : f(F){};
        const Fecha &cuando(){return f;};

    private:
        Fecha f;
    };

    class Num_duplicado
    {
        public:
        Num_duplicado(const Numero& n):numero_(n){};
        const Numero& que(){return numero_;};
        private:
        Numero numero_;
    };

    class Desactivada;

    friend Usuario;
    private: 
    static std::unordered_set<Numero> tarjetas_;
    const Numero num_;
    const Usuario*  titular_;
    const Fecha caducidad_;
    bool activa_;

    void anula_titular();
};

const Usuario* Tarjeta::TITULAR_NULO(nullptr);

std::ostream& operator << (std::ostream& os, Tarjeta::Tipo t);
std::ostream& operator << (std::ostream& os, const Tarjeta& T);
#endif