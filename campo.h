#ifndef CAMPO_H
#define CAMPO_H
#include <fstream>
using std::fstream;
class Campo
{
    int campo; //4
    char nombre[21]; //21
    char tipo; //1
    int longitud; //4
    bool llave; //1

    const static int SIZE_CAMPO;
    //size of campo = 31
public:
    Campo(int campo);
    Campo(int campo, const char *nombre,char tipo, int longitud, bool llave);
    Campo(fstream & fs);
    static int getSIZE_CAMPO();
    int getCampo() const;
    void setCampo(int value);
    const char *getNombre()const;
    void setNombre(char *nombre);
    char getTipo() const;
    void setTipo(char value);
    int getLongitud() const;
    void setLongitud(int value);
    void write(fstream & fs);
};

#endif // CAMPO_H
