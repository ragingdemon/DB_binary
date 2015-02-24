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
    int size;
    unsigned pointer_content;
public:
    Contenido(Registro *registro);
    ~Contenido();
    void setContent();
    void setString(Campo *campo);
    void setInt(Campo *campo);
    void setDouble(Campo *campo);
    void readContent(fstream &fs);
    void writeContent(fstream &fs);
    void printContent();
    void printString(Campo *campo);
    void printInt(Campo *campo);
    void printDouble(Campo *campo);
};

#endif // CONTENIDO_H
