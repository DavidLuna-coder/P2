#include "tarjeta.hpp"
#include "usuario.hpp"
#include "numero.hpp"
#include <iomanip>
Tarjeta::Tarjeta(const Numero &num, Usuario &titular, const Fecha &f) : num_(num), titular_(&titular), caducidad_(f), activa_(true)
{
    if (!tarjetas_.insert(num_).second)
    {
        throw Num_duplicado(num_);
    }

    Fecha hoy;
    if (f < hoy)
    {
        throw Caducada(f);
    }

    titular_->es_titular_de(*this);
}

const Tarjeta::Tipo Tarjeta::tipo() const
{
    Tipo tipo = Otro;
    if (num_.num_[0] == '3')
    {
        if (num_.num_[1] == '4' || num_.num_[1] == '7')
            tipo = AmericanExpress;

        else
            tipo = JCB;
    }
    else if (num_.num_[0] == '4')
        tipo = VISA;

    else if (num_.num_[0] == '5')
        tipo = Mastercard;

    else if (num_.num_[0] == '6')
        tipo = Maestro;

    return tipo;
}

void Tarjeta::anula_titular()
{
    if (titular_ != TITULAR_NULO)
        titular_ = TITULAR_NULO;
}

std::ostream &operator<<(std::ostream &os, Tarjeta::Tipo t)
{
    if (t == Tarjeta::Otro)
        os << "Otro";
    else if (t == Tarjeta::VISA)
        os << "VISA";
    else if (t == Tarjeta::Mastercard)
        os << "Mastercard";
    else if (t == Tarjeta::Maestro)
        os << "Maestro";
    else if (t == Tarjeta::JCB)
        os << "JCB";
    else if (t == Tarjeta::AmericanExpress)
        os << "AmericanExpress";

    return os;
}

std::ostream &operator<<(std::ostream &os, Tarjeta T)
{
    os << T.tipo() << '\n';
    os << T.numero() << '\n';
    os << T.titular().nombre() << " ";
    os << T.titular().apellidos() << '\n';
    os << "Caduca: " << std::setw(2) << std::setfill('0') << T.caducidad().mes() << '/' << std::setw(2) << std::setfill('0') << T.caducidad().anno() % 100;
    return os;
}