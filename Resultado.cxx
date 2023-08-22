#include<string>
#include<cstring>
#include "Resultado.h"

Resultado::Resultado(int l, char* w){
    this->linea = l;
    this->word = new char[strlen(w)+1];
    strcpy(this->word, w);
}

int Resultado::getLinea(){
    return linea;
}

char* Resultado::getWord(){
    return word;
}
