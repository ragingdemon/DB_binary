#include "contenido.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

Contenido::Contenido(Registro *registro)
{
    campos = registro->getCampos();
    size = registro->getLongitud();
    content = new char[size];
    pointer_content = 0;
}

Contenido::~Contenido()
{
    if (content) {
        delete[] content;
        content = nullptr;
    }
}

void Contenido::setContent()
{
    for (int i = 0; i < campos.size(); ++i) {
        Campo *campo = campos.at(i);
        if (campo->getTipo() == Campo::STRING) {
            setString(campo);
        } else if (campo->getTipo() == Campo::INTEGER) {
            setInt(campo);
        } else if (campo->getTipo() == Campo::DOUBLE) {
            setDouble(campo);
        }
    }
    pointer_content = 0;
}

void Contenido::setString(Campo *campo)
{
    int size_campo = campo->getLongitud();
    char *value = new char[size_campo];
    cout<<"Ingrese el dato para campo "<<campo->getNombre()<<"("<<"tipo: "<<campo->getTipo()<<", bytes: "<<size_campo<<"): ";
    cin>>value;
    for (int i = 0; i < size_campo; ++i) {
        content[pointer_content + i] = value[i];
    }
    pointer_content += size_campo;
    delete[] value;
}

void Contenido::setInt(Campo *campo)
{
    int size_campo = campo->getLongitud();
    int integer = 0;
    cout<<"Ingrese el dato para campo "<<campo->getNombre()<<"("<<"tipo: "<<campo->getTipo()<<", bytes: "<<size_campo<<"): ";
    cin>>integer;
    char *value = (char*)&integer;
    for (int i = 0; i < size_campo; ++i) {
        content[pointer_content + i] = value[i];
    }
    pointer_content += size_campo;
    delete[] value;
}

void Contenido::setDouble(Campo *campo)
{
    int size_campo = campo->getLongitud();
    int double_n = 0;
    cout<<"Ingrese el dato para campo "<<campo->getNombre()<<"("<<"tipo: "<<campo->getTipo()<<", bytes: "<<size_campo<<"): ";
    cin>>double_n;
    char *value = (char*)&double_n;
    for (int i = 0; i < size_campo; ++i) {
        content[pointer_content + i] = value[i];
    }
    pointer_content += size_campo;
    delete[] value;
}

void Contenido::readContent(fstream &fs)
{
    fs.read(content,size);
}

void Contenido::writeContent(fstream &fs)
{
    fs.write(content,size);
}

void Contenido::printContent()
{
    if (content) {
        for (int i = 0; i < campos.size(); ++i) {
            Campo *campo = campos.at(i);
            if (campo->getTipo() == Campo::STRING) {
                printString(campo);
            } else if (campo->getTipo() == Campo::INTEGER) {
                printInt(campo);
            } else if (campo->getTipo() == Campo::DOUBLE) {
                printDouble(campo);
            }
            cout<<endl;
        }
        pointer_content = 0;
    }
}

void Contenido::printString(Campo *campo)
{
    int size_campo = campo->getLongitud();
    char *value = new char[size_campo];
    for (int i = 0; i < size_campo; ++i) {
        value[i] = content[pointer_content + i];
    }
    pointer_content += size_campo;
    cout<<*value;
    delete[] value;
}

void Contenido::printInt(Campo *campo)
{
    int size_campo = campo->getLongitud();
    char *value = new char[size_campo];
    for (int i = 0; i < size_campo; ++i) {
        value[i] = content[pointer_content + i];
    }
    pointer_content += size_campo;
    int *numbre = (int*) value;
    cout<<*numbre;
    delete[] value;
}

void Contenido::printDouble(Campo *campo)
{
    int size_campo = campo->getLongitud();
    char *value = new char[size_campo];
    for (int i = 0; i < size_campo; ++i) {
        value[i] = content[pointer_content + i];
    }
    pointer_content += size_campo;
    double *numbre = (double*) value;
    cout<<*numbre;
    delete[] value;
}
