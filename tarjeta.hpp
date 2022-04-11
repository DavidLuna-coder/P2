#ifndef _TARJETA_
#define _TARJETA_

#include <unordered_set>
class Fecha;
class Numero;
class Usuario;
class Tarjeta
{
public:
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
        const Fecha &cuando(){return f};

    private:
        Fecha f;
    } enum Tipo { Otro,
                  VISA,
                  Mastercard,
                  Maestro,
                  JCB,
                  AmericanExpress };

private:
    static std::unordered_set<Numero> tarjetas_;
    const Numero num_;
    const Usuario *titular_;
    const Fecha caducidad_;
    bool activa;
}

#endif