#include "indexl.h"
#include <cstring>
#include <fstream>
using std::map;
using std::fstream;
using std::ios;
using std::pair;

IndexL::IndexL(Header h)
{
    std::strcpy(archivo,h.getArchivo());
    std::strcat(archivo,".idxl");
    llave = h.getRegistro()->getCampos().at(0);
}

void IndexL::write()
{
    fstream fs(archivo,ios::out|ios::binary);
    if(fs.is_open()){
        int size_llave = llave->getLongitud();
        //fs.write((char*)&size_llave,sizeof(size_llave));
        for (map<char*,int>::iterator it = index.begin(); it != index.end(); ++it){
            char *str = it->first;
            int n = it->second;
            fs.write(str,size_llave);
            fs.write((char*)&n,sizeof(int));
        }
    }
    fs.close();
}

void IndexL::read()
{
    fstream fs(archivo,ios::in|ios::out|ios::binary);
    if(fs.is_open()){
        int size_llave = llave->getLongitud();
        //fs.read((char*)&size_llave,sizeof(size_llave));
        int rrn;
        bool loop = false;
        do {
            char *llave;
            int offset;
            fs.read(llave,size_llave);
            fs.read((char*)&offset,sizeof(offset));
            loop = fs.rdstate() == ios::goodbit;
            if(loop)
                index.insert(pair<char*,int>(llave,offset));
        } while (loop);
    }
    fs.close();
}
