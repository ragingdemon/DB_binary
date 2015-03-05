#ifndef HEADER_H
#define HEADER_H
#include "registro.h"
#include "campo.h"
#include "contenido.h"
#include <fstream>

using std::fstream;
class Header
{
    char archivo[21];
    char tipo;
    Registro *registro;
    int avail_list_offset;
    int datos_offset;
public:
    const static char NO_INDEX;
    const static char INDEXL;
    const static char INDEXB;
    Header(char tipo);
    Header(const char * nombre);
    ~Header();
    const char* getArchivo()const;
    Registro *getRegistro() const;
    int getAvail_list_offset() const;
    int getDatos_offset() const;
    void write(fstream &fs);
    int getAvailList(fstream &fs);
    bool setAvailList(fstream &fs, int value);
    bool addRegistro(const char* file);
    bool addRegistro(const char* file, Contenido &contenido);
    bool removeRegistro(const char* file, int rrn);
    bool modRegistro(int rrn);
    bool leerRegistro(int rrn);
    void allRegistros();
    void compactar();
};

#endif // HEADER_H
