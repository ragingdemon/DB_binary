#ifndef REGISTRO_H
#define REGISTRO_H
#include "campo.h"
#include <vector>
#include <fstream>
using std::vector;
using std::fstream;
class Registro
{
    int cantidad_campos;
    vector<Campo*> campos;
    int longitud;
public:
    Registro(int cantidad_campos);
    Registro(fstream &fs);
    ~Registro();
    int getCantidad_campos() const;
    void setCantidad_campos(int value);
    vector<Campo *> getCampos() const;
    void setCampos(const vector<Campo *> &value);
    int getLongitud() const;
    void write(fstream &fs);
};

#endif // REGISTRO_H
