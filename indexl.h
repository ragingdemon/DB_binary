#ifndef INDEXL_H
#define INDEXL_H
#include "header.h"
#include "campo.h"
#include <cstring>
#include <map>
using std::map;

struct cmp_str
{
    bool operator()(char const *a, char const *b)
    {
        return std::strcmp(a, b) < 0;
    }
};

class IndexL
{
    char archivo[51];
    Campo *llave;
public:
    map<char *, int, cmp_str> index;
    IndexL(Header h);
    void write();
    void read();
};

#endif // INDEXL_H
