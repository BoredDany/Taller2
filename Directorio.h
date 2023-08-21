#ifndef __DIRECTORIO__H__
#define __DIRECTORIO__H__
#include<list>
#include<stack>
#include<string>
#include<cstring>

class Directorio{
private:
    int num_rows;
    char * substring;
    std::stack<std::list<char*>> words;
public:
    Directorio(int n, char * ss);
    int getNum_rows();
    char * get_substring();
    void setStack(std::stack<std::list<char*>>& stackP);
    std::stack<std::list<char*>>& getWords();
};
#endif
