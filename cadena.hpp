#ifndef _CADENA_
#define _CADENA_

#include <iostream>
#include <iterator>
class Cadena
{
private:
    char* s_;
    unsigned tam_;
    
public:
    explicit Cadena(unsigned t = 0, char c = '\0');
    Cadena(const Cadena& S);
    Cadena(const char* S);
    Cadena(Cadena&& S);
    Cadena substr(int i, unsigned t) const;

    char at (int n) const;
    char& at (int n);
    Cadena& operator = (const Cadena& S);
    Cadena& operator = (const char * S);
    Cadena& operator = (Cadena&& S);

    char operator[](int) const;
    char& operator[](int n);

    Cadena& operator+=(const Cadena& C);   
    friend Cadena operator+ (Cadena& S, Cadena& C);
    const char* c_str() const;

    unsigned length() const;

    //Iteradores
    typedef char* iterator ;
    typedef const char* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;
    reverse_iterator rend();
    const_reverse_iterator rend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;
    
    ~Cadena()
    {
        delete[] s_;
    }
};

Cadena operator+ (Cadena& S, Cadena& C);
bool operator== (const Cadena& S,const Cadena& C);
bool operator < (const Cadena& S, const Cadena & C);
bool operator > (const Cadena& S, const Cadena& C);
bool operator <= (const Cadena& S, const Cadena& C);
bool operator >= (const Cadena& S, const Cadena& C);
bool operator != (const Cadena& S, const Cadena& C);
std::ostream& operator <<(std::ostream& os, const Cadena& C);
std::istream& operator >>(std::istream& is, Cadena& C);

//todo Para P2 y ss.
//* Especialización de la plantilla hash<T>para definir la
//* función hash a utilizar con contenedores desordenados de
//* Cadena, unordered_[set|map|multiset|multimap].
namespace std { // Estaremos dentro del espacio de nombres std
template <> // Es una especialización de una plantilla para Cadena
struct hash<Cadena> { // Es una clase con solo un operador publico
size_t operator() (const Cadena& cad) const // El operador función
{
hash<string> hs;
// Creamos un objeto hash de string
const char * p = cad.c_str(); // Obtenemos la cadena de la Cadena
string s(p);
// Creamos un string desde una cadena
size_t res = hs(s);
// El hash del string. Como hs.operator()(s);
return res;
// Devolvemos el hash del string
}
};
}
#endif