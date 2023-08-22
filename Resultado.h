#ifndef __RESULTADO__H__
#define __RESULTADO__H__
#include<string>
#include<cstring>

class Resultado{
private:
    int linea;
    char* word;
public:
    Resultado(int l, char* w);
    int getLinea();
    char* getWord();
};
#endif
