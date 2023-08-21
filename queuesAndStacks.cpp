#include<iostream>
#include<queue>
#include<stack>
#include<list>
#include<fstream>
#include<string>
#include<sstream>
#include<cstring>
#include "Directorio.h"
using namespace std;

int contar (std::string file_name){
    std::ifstream inputF(file_name);
    int lineas = 0;
    std::string line;
    if(inputF.is_open()){
        while(getline(inputF, line)){
            lineas++;
        }
        inputF.clear();
        inputF.std::istream::seekg(0);

    }else{
        cout<<"No se leyo"<<endl;
    }
    inputF.close();
    return lineas;
}

int contarEspacios(std::string line){
    int espacios = 0;
    for(int i = 0 ; i < line.length() ; i++){
        if(line[i]==' '){
            espacios++;
        }
    }
    return espacios;
}

std::stack<std::list<char *>> leerArvivo(std::string file_name, std::string& substring, int& num_rows){

    std::ifstream inputF(file_name);
    std::string line, word;
    int sizeF = contar(file_name);
    std::stack<std::list<char *>> stackPalabras;
    if(inputF.is_open()){
        for(int j = 0 ; j < sizeF-1 ; j++){

            getline(inputF, line,'\n');
            num_rows = stoi(line);
            cout<<num_rows<<endl;

            getline(inputF, line,'\n');
            substring = line;
            cout<<substring<<endl;

            for(int i = 0 ; i < num_rows-1 ; i++){
                j++;
                getline(inputF, line);
                std::list<char *> palabras;
                int espacios = contarEspacios(line);
                stringstream ss(line);

                for(int k = 0 ; k < espacios+1 ; k++){
                    getline(ss,word,' ');
                    palabras.push_back(strcpy(new char[word.length() + 1], word.c_str()));
                }
                stackPalabras.push(palabras);
            }
        }

        /*int i = 0;
        cout<<"STACK--------"<<endl;
        while(!stackPalabras.empty()){
        cout<<"Stack "<<i+1<<endl;
        std::list<char*> actualList = stackPalabras.top();
        stackPalabras.pop();
        for (char* s : actualList) {
            cout << s << endl;
        }
        i++;
        cout<<"-------------------"<<endl;
        }*/

    }else{
        cout<<"No se leyo"<<endl;
    }
    inputF.close();
    return stackPalabras;
};

void comienzoSubString(Directorio& dic){
    int cont = 0;
    std::stack<std::list<char*>> duplicadoPila = dic.getWords();
    std::list<std::list<char*>> duplicadoLista;
    std::cout<<"Palabras que inician con "<<dic.get_substring()<<std::endl;
    while(!duplicadoPila.empty()){
        duplicadoLista.push_front(duplicadoPila.top());
        duplicadoPila.pop();
    }

    std::list<std::list<char*>>::iterator itDuplicadoLista = duplicadoLista.begin();

    for(;itDuplicadoLista!=duplicadoLista.end();itDuplicadoLista++){
        cont++;
        std::list<char*>::iterator it2daDimension = itDuplicadoLista->begin();
        for(;it2daDimension!=itDuplicadoLista->end();it2daDimension++){
            if(strncmp(*it2daDimension,dic.get_substring(),strlen(dic.get_substring()))==0){
                std::cout<<"Linea "<<cont<<": "<<*it2daDimension<<std::endl;
            }
        }
    }
}

int main(){
    string file_name;
    cout<<"Ingrese nombre del archivo: ";
    cin>>file_name;
    int filas = 0;
    std::string substring;
    std::stack<std::list<char *>> stackP;

    stackP = leerArvivo(file_name, substring, filas);

    Directorio d (filas, &substring[0]);
    d.setStack(stackP);

    cout<<"filas: "<<d.getNum_rows()<<endl;
    cout<<"substr: "<<d.get_substring()<<endl;

    Directorio dic = d;
    
    int i = 0;
    while(!d.getWords().empty()){
        cout<<"Stack "<<i+1<<endl;
        std::stack<std::list<char*>>& wordStack = d.getWords();
        std::list<char*> actualList = wordStack.top();
        wordStack.pop();
        for (char* s : actualList) {
            cout << s << endl;
        }
        i++;
        cout<<"-------------------"<<endl;
    }

    comienzoSubString(dic);

}
//g++ -std=c++11 -o testS Directorio.cxx queuesAndStacks.cpp
