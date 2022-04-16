#include "tarjeta.hpp"
#include "usuario.hpp"
#include "numero.hpp"

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
    if(titular_ != TITULAR_NULO)
        titular_ = TITULAR_NULO;
}