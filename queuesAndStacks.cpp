#include<iostream>
#include<stack>
#include<list>
#include<fstream>
#include<string>
#include<sstream>
#include<cstring>
#include <cctype>
#include "Directorio.h"
#include "Resultado.h"
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

char* leerPalabraAlReves(const char* word) {
    int longitud = strlen(word);
    char* palabraAlReves = new char[longitud + 1];

    for (int i = 0; i < longitud; i++) {
        palabraAlReves[i] = word[longitud - 1 - i];
    }

    palabraAlReves[longitud] = '\0';

    return palabraAlReves;
}

quitarSignos(std::string& line){
    for(int i = 0 ; i < line.length() ; i++){
        if (ispunct(line[i])) {
                line[i] = ' ';
    }
    }
}

std::stack<std::list<char *>> leerArchivo(std::string file_name, std::string& substring, int& num_rows){

    std::ifstream inputF(file_name);
    std::string line, word;
    int sizeF = contar(file_name);
    std::stack<std::list<char *>> stackPalabras;
    if(inputF.is_open()){
        for(int j = 0 ; j < sizeF-1 ; j++){
            getline(inputF, line,'\n');
            num_rows = stoi(line);
            getline(inputF, line,'\n');
            substring = line;
            for(int i = 0 ; i < num_rows-1 ; i++){
                j++;
                getline(inputF, line);
                std::list<char *> palabras;
                int espacios = contarEspacios(line);
                stringstream ss(line);
                for(int k = 0 ; k < espacios+1 ; k++){
                    getline(ss,word,' ');
                    std::string cleanWord;
                    for(char c: word){
                        if(isalpha(c)){
                            cleanWord+=c;
                        }
                    }
                    if(!cleanWord.empty()){
                        palabras.push_back(strcpy(new char[cleanWord.length() + 1], cleanWord.c_str()));
                    }
                }
                stackPalabras.push(palabras);
            }
        }
    }else{
        cout<<"No se leyo"<<endl;
    }
    inputF.close();
    return stackPalabras;
}

char* SubcadenaInvertida(char * inv){
    int longitud = std::strlen(inv);
    for (int i = 0, j = longitud - 1; i < j; i++, j--) {
        char temp = inv[i];
        inv[i] = inv[j];
        inv[j] = temp;
    }
    return inv;
}

void buscar(Directorio& dic, std::list<Resultado>& comienza, std::list<Resultado>& contiene, std::list<Resultado>& contieneInv){

    int cont = 0;
    char * invC = new char[strlen(dic.get_substring())+1];
    strcpy(invC, dic.get_substring());
    SubcadenaInvertida(invC);

    std::stack<std::list<char*>> duplicadoPila = dic.getWords();
    std::list<std::list<char*>> duplicadoLista;
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
                Resultado r(cont, *it2daDimension);
                comienza.push_back(r);
            }
            if(std::strstr(*it2daDimension, dic.get_substring()) != nullptr){
                Resultado r(cont, *it2daDimension);
                contiene.push_back(r);
            }
            if(std::strstr(*it2daDimension, invC) != nullptr){
                Resultado r(cont, *it2daDimension);
                contieneInv.push_back(r);
            }
        }
    }
    delete[] invC;
}

int main(){

    string file_name;
    cout<<"Ingrese nombre del archivo: ";
    cin>>file_name;
    int filas = 0;
    std::string substring;
    std::stack<std::list<char *>> stackP;

    stackP = leerArchivo(file_name, substring, filas);
    Directorio d (filas, &substring[0]);
    d.setStack(stackP);

    cout<<"\nRenglones en el archivo: "<<d.getNum_rows()<<endl;
    cout<<"Subcadena a buscar: "<<d.get_substring()<<endl<<endl;

    std::list<Resultado> comienza, contiene, contieneInv;
    std::list<Resultado>::iterator itResultado = comienza.begin();
    buscar(d, comienza, contiene, contieneInv);

    cout<<"Hay "<<comienza.size()<<" palabras que comienzan por: "<<d.get_substring()<<endl;
    for(itResultado = comienza.begin() ; itResultado != comienza.end() ; itResultado++){
        cout<<"Linea "<<itResultado->getLinea()<<": "<<itResultado->getWord()<<endl;
    }

    cout<<"\nHay "<<contiene.size()<<" palabras que contienen: "<<d.get_substring()<<endl;
    for(itResultado = contiene.begin() ; itResultado != contiene.end() ; itResultado++){
        cout<<"Linea "<<itResultado->getLinea()<<": "<<itResultado->getWord()<<endl;
    }

    cout<<"\nHay "<<contieneInv.size()<<" palabras que contienen: "<<SubcadenaInvertida(d.get_substring())<<endl;
    for(itResultado = contieneInv.begin() ; itResultado != contieneInv.end() ; itResultado++){
        cout<<"Linea "<<itResultado->getLinea()<<": "<<itResultado->getWord()<<endl;

    // Imprimir la palabra al revés
    char* palabraAlReves = leerPalabraAlReves(itResultado->getWord());
    cout << "Palabra al revés: " << palabraAlReves << endl;
    delete[] palabraAlReves; // Liberar la memoria
    }
    

}
//g++ -std=c++11 -o testS Directorio.cxx Resultado.cxx queuesAndStacks.cpp
