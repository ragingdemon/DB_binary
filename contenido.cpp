#include "contenido.h"


Contenido::Contenido(Registro *registro)
{
    campos = registro->getCampos();
    content = new char[registro->getLongitud()];
}

Contenido::~Contenido()
{
    if (content) {
        delete[] content;
    }
}

void Contenido::writeContent()
{
    for (int i = 0; i < campos.size(); ++i) {
        Campo *campo = campos.at(i);
        if (campo->getTipo() == Campo::STRING) {
            writeString();
        } else if (campo->getTipo() == Campo::INTEGER) {
            writeInt();
        } else if (campo->getTipo() == Campo::DOUBLE) {
            writeDouble();
        }
    }
}

void Contenido::writeString()
{

}

void Contenido::writeInt()
{

}

void Contenido::writeDouble()
{

}
