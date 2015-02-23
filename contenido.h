#ifndef CONTENIDO_H
#define CONTENIDO_H
#include "campo.h"
#include "registro.h"
#include <vector>
using std::vector;
class Contenido
{
    vector<Campo*> campos;
    char *content;
public:
    Contenido(Registro *registro);
    ~Contenido();
    void writeContent();
    void writeString();
    void writeInt();
    void writeDouble();
};

#endif // CONTENIDO_H
