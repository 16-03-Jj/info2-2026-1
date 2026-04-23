#include "practicaTres.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <stdexcept>
using namespace std;

char rotarIzquierda(char byte, int n){
    n=n%8;
    unsigned char b=(unsigned char)byte;
    return (b<<n)|(b>>(8-n));
}

char rotarDerecha(char byte, int n){
    n=n%8;
    unsigned char b=(unsigned char)byte;
    return (b>>n)|(b<<(8-n));
}

char encriptar(char byte, int n, char key){
    return rotarIzquierda(byte,n)^key;
}

char desencriptar(char byte, int n, char key){
    return rotarDerecha(byte^key,n);
}

void RLE(string text){
    string compression="";
    int counter=1;
    for(int a=0;a<text.size();a++){
        if(a+1<text.size()&&text[a]==text[a+1]){
            counter++;
        }else{
            if(counter>1){
                compression+=to_string(counter);
            }
            compression+=text[a];
            counter=1;
        }
    }
    cout<<"The word is: "<<compression<<endl;
}

string comprimirRLE(string text){
    string compression="";
    int counter=1;
    for(int a=0;a<text.size();a++){
        if(a+1<text.size()&&text[a]==text[a+1]){
            counter++;
        }else{
            if(counter>1){
                compression+=to_string(counter);
            }
            compression+=text[a];
            counter=1;
        }
    }
    return compression;
}

string descomprimirRLE(string text){
    string result="";
    int a=0;
    while(a<text.size()){
        if(isdigit(text[a])){
            int count=0;
            while(a<text.size()&&isdigit(text[a])){
                count=count*10+(text[a]-'0');
                a++;
            }
            for(int i=0;i<count;i++){
                result+=text[a];
            }
        }else{
            result+=text[a];
        }
        a++;
    }
    return result;
}

void LZ78(string text){
    struct dictionary{
        int k;
        char v;
    };
    dictionary* diccionario=new dictionary[500];
    int size=0;
    int prefijo=0;
    for(int i=0;i<text.size();i++){
        int encontrado=-1;
        for(int b=0;b<size;b++){
            if(diccionario[b].k==prefijo&&diccionario[b].v==text[i]){
                encontrado=b+1;
                break;
            }
        }
        if(encontrado!=-1){
            prefijo=encontrado;
        }else{
            cout<<"("<<prefijo<<","<<text[i]<<")"<<endl;
            diccionario[size].k=prefijo;
            diccionario[size].v=text[i];
            size++;
            prefijo=0;
        }
    }
    delete[] diccionario;
}

string leerArchivo(string nombreArchivo){
    ifstream archivo(nombreArchivo);
    if(!archivo.is_open()){
        throw runtime_error("No se pudo abrir el archivo");
    }
    string contenido="",linea;
    while(getline(archivo,linea)){
        contenido+=linea;  // sin + "\n"
    }
    archivo.close();
    return contenido;
}

void escribirArchivo(string nombreArchivo, string contenido){
    ofstream archivo(nombreArchivo);
    if(!archivo.is_open()){
        throw runtime_error("No se pudo crear el archivo");
    }
    archivo<<contenido;
    archivo.close();
}
