#include "tarjeta.hpp"
#include "usuario.hpp"
#include "cadena.hpp"
#include <cstring>
#include <iostream>
#include <iomanip>
#include <set>

std::set<Numero> Tarjeta:: tarjetas_;
Tarjeta::Tarjeta(const Numero &num, Usuario &titular, const Fecha &f) : num_(num), titular_(&titular), caducidad_(f), activa_(true)
{
    Fecha hoy;
    if (f < hoy)
    {
        throw Caducada(f);
    }
    const_cast<Usuario*>(titular_)->es_titular_de(*this);
    
    if (!tarjetas_.insert(num_).second)
    {
        throw Num_duplicado(num_);
    }

    
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
    if (titular_ != nullptr)
        titular_ = nullptr;
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

std::ostream &operator<<(std::ostream &os, const Tarjeta& T)
{
    os << T.tipo() << '\n';
    os << T.numero() << '\n';
    os << T.titular().nombre() << " ";
    os << T.titular().apellidos() << '\n';
    os << "Caduca: " << std::setw(2) << std::setfill('0') << T.caducidad().mes() << '/' << std::setw(2) << std::setfill('0') << T.caducidad().anno() % 100;
    return os;
}


Tarjeta::~Tarjeta()
{

    tarjetas_.erase(num_);
}

bool luhn(const Cadena& numero);
Numero::Numero(const Cadena& C)
{
    char aux[C.length() + 1];
    
    int i = 0;

    for(int j = 0; j != C.length(); j++)
    {
        if (isdigit(C[j]) )
        {
            aux[i] = C[j];
            i++; 
        }
        else if(isalpha(C[j]))
        {
            throw Incorrecto(DIGITOS);
        }
    }
    aux[i] = '\0';
    Cadena AUX = aux;

    if (!luhn(AUX))
    {
        throw Incorrecto(NO_VALIDO);
    }
    if (AUX.length() < 13 || AUX.length() > 19)
    {
        throw Incorrecto(LONGITUD);
    }
    
    

    num_ = AUX;
}

Numero::operator const char *() const
{
    return num_.c_str();
}

bool operator < (const Numero& N,const Numero& M)
{
    return N.num_ < M.num_;
}