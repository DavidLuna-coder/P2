#include "fecha.hpp"
#include <ctime>
#include <locale>
#include <iostream>
#include <cstring>
// std::locale("es_ES.UTF-8");
using namespace std;
time_t now = time(nullptr);
tm *dt = localtime(&now);
// Constructor Predeterminado

Fecha::Fecha(unsigned dia, unsigned mes, unsigned anno)
{
    try
    {
        EstablecerAnno(anno);
        EstablecerMes(mes);
        EstablecerDia(dia, mes, anno);
    }
    catch (const Fecha::Invalida &e)
    {
        cerr << e.por_que() << endl;
    }
}

void Fecha::EstablecerAnno(unsigned anno)
{
    if (anno == 0)
    {
        a = dt->tm_year + 1900;
    }
    else if (anno < Fecha::AnnoMinimo)
    {
        throw Invalida("ERROR: anno menor que el año minimo establecido");
    }
    else if (anno > Fecha::AnnoMaximo)
    {
        throw Invalida("ERROR: anno mayor que el maximo establecido");
    }
    else
        a = anno;
}

void Fecha::EstablecerMes(unsigned mes)
{
    if (mes == 0)
    {
        m = dt->tm_mon + 1;
    }
    else if (mes > 12)
    {
        throw Invalida("ERROR: El mes tiene que ser un numero entre 1 y 12");
    }
    else
    {
        m = mes;
    }
}

void Fecha::EstablecerDia(unsigned dia, unsigned mes, unsigned anno)
{
    if (dia != 0)
    {
        if (dia > 31)
        {
            throw Invalida("ERROR: El mes no puede tener mas de 31 dias");
        }
        else if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30)
        {
            throw Invalida("ERROR: Ese mes no puede tener mas de 30 dias");
        }
        else if (mes == 2)
        {
            if ((anno % 4 != 0 && (anno % 400 == 0 || anno % 100 != 0)) && dia > 28)
            {
                throw Invalida("ERROR: Febrero no puede tener mas de 28 dias si el anno no es bisiesto");
            }
            else if (dia > 29)
            {
                throw Invalida("ERROR: El mes de Febrero del año introducido no puede ser mayor que 29");
            }
        }
        d = dia;
    }
    else
        d = dt->tm_mday;
}

Fecha::Fecha(const Fecha &F) : d(F.d), m(F.m), a(F.a) {}

// Constructor de conversión

Fecha::Fecha(const char *F)
{
    int dia = 0;
    int mes = 0;
    int anno = 0;
    int comprobar = std::sscanf(F, "%d/%d/%d", &dia, &mes, &anno);

    try
    {
        if (comprobar != 3)
        {
            throw "Formato de fecha incorrecta debe ser dia/mes/anno";
        }
        else
        {
            EstablecerAnno(anno);
            EstablecerMes(mes);
            EstablecerDia(dia, mes, anno);
        }
    }
    catch (const Fecha::Invalida &e)
    {
        std::cerr << e.por_que() << '\n';
    }
}

// Métodos observadores
int Fecha::dia() const
{
    return d;
}

int Fecha::mes() const
{
    return m;
}

int Fecha::anno() const
{
    return a;
}

// Conversión implicita/explícita
const char *Fecha::cadena() const
{
    locale::global(locale("es_ES.UTF-8"));
    // setlocale(LC_TIME,"spanish");
    tm *F = localtime(&now);
    F->tm_mday = d;
    F->tm_mon = m - 1;
    F->tm_year = a - 1900;
    static char buffer[80];
    mktime(F);
    strftime(buffer, 80, "%A %d de %B de %Y", F);
    return buffer;
}

Fecha &Fecha::operator=(const Fecha &F)
{
    if (this != &F)
    {
        d = F.d;
        m = F.m;
        a = F.a;
    }
    return *this;
}
// Operadores
Fecha operator+=(Fecha &F, int n)
{
    tm *nuevaFecha = localtime(&now);
    nuevaFecha->tm_mday = F.d + n;
    nuevaFecha->tm_mon = F.m - 1;
    nuevaFecha->tm_year = F.a - 1900;

    mktime(nuevaFecha);
    F.d = nuevaFecha->tm_mday;
    F.m = nuevaFecha->tm_mon + 1;
    try
    {
        F.EstablecerAnno(nuevaFecha->tm_year + 1900);
    }
    catch (const Fecha::Invalida &e)
    {
        std::cerr << e.por_que() << '\n';
    }

    return F;
}

Fecha operator++(Fecha &F, int n)
{
    Fecha t = F;
    F += 1;
    return t;
}

Fecha operator++(Fecha &F)
{
    return F += 1;
}

Fecha operator--(Fecha &F, int n)
{
    Fecha t = F;
    F += -1;
    return t;
}

Fecha operator--(Fecha &F)
{
    return F += -1;
}

Fecha operator+(Fecha &F, int n)
{
    Fecha t = F;
    return t += n;
}

Fecha operator-(Fecha &F, int n)
{
    Fecha t = F;
    return t += -n;
}

Fecha operator-=(Fecha &F, int n)
{
    return F += -n;
}

bool operator==(const Fecha &F, const Fecha &G)
{
    return (F.d == G.d && F.m == G.m && F.a == G.a);
}

bool operator<(const Fecha &F, const Fecha &G)
{
    bool flag = false;
    if (F.a < G.a)
    {
        flag = true;
    }
    else if (F.a == G.a)
    {
        if (F.m < F.m)
        {
            flag = true;
        }
        else if (F.d < G.d)
        {
            flag = true;
        }
    }
    return flag;
}

bool operator!=(const Fecha &F, const Fecha &G)
{
    return !(F == G);
}

bool operator>(const Fecha &F, const Fecha &G)
{
    return !((F == G) || (F < G));
}

bool operator<=(const Fecha &F, const Fecha &G)
{
    return ((F == G) || (F < G));
}

bool operator>=(const Fecha &F, const Fecha &G)
{
    return !(F < G);
}

ostream &operator<<(ostream &os, const Fecha &F)
{
    os << F.cadena();
    return os;
}

std::istream &operator>>(std::istream &is, Fecha &F)
{
    char *cadena;
    is >> cadena;
    int dia = 0;
    int mes = 0;
    int anno = 0;
    if (std::sscanf(cadena, "%d/%d/%d", &dia, &mes, &anno) != 3)
    {
        is.setstate(ios::failbit);
    }
    else
    {
        Fecha C{cadena};
        F = C;
    }

    return is;
}
