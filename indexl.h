#ifndef INDEXL_H
#define INDEXL_H
#include "registro.h"
#include "campo.h"
#include <cstring>
#include <map>
using std::map;



class IndexL
{    
    struct cmp_str
    {
        bool operator()(char const *a, char const *b)
        {
            return std::strcmp(a, b) < 0;
        }
    };
    char archivo[51];
    Campo *llave;
public:
    map<char *, int, cmp_str> index;
    IndexL(const char*,Registro*);
    ~IndexL();
    void write();
    void read();
};

#endif // INDEXL_H
