#ifndef HEADER_H
#define HEADER_H
#include "registro.h"
#include "campo.h"
#include <fstream>

using std::fstream;
class Header
{
    char archivo[21];
    Registro *registro;
    int avail_list_offset;
    int datos_offset;
public:
    Header();    
    Header(const char * nombre);
    ~Header();
    const char* getArchivo()const;
    Registro *getRegistro() const;
    int getAvail_list_offset() const;
    int getDatos_offset() const;
    void write(fstream &fs);
};

#endif // HEADER_H
