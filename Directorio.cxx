#include<list>
#include<stack>
#include<string>
#include "Directorio.h"

Directorio::Directorio(int n, char * ss){
    this->num_rows = n;
    this->substring = new char[strlen(ss)+1];
    strcpy(this->substring, ss);
}

int Directorio::getNum_rows(){
    return num_rows;
}

char * Directorio::get_substring(){
    return substring;
}

void Directorio::setStack(std::stack<std::list<char*>>& stackP){
    this->words = stackP;
};

std::stack<std::list<char*>>& Directorio::getWords(){
    return words;
};
