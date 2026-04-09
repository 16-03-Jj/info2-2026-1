#include "practicaTres.h"
#include <iostream>
using namespace std;

void RLE(string text){
    string compression="";
    int counter=1;
    for(int a=0;a<text.size();a++){
        if(text[a]==text[a+1]){
            counter++;
        }else{
            if(counter>1){
                compression+=counter+'0';
            }
            compression+=text[a];
            counter=1;
        }
    }
    cout<<"The word is: "<<compression<<endl;
}
#include "practicaTres.h"

void LZ78(){
    char* text=new char[100];
    cout<<"Enter the text: "<<endl;
    cin>>text;

    struct dictionary{
        int k;
        char v;
    };

    dictionary* diccionario=new dictionary[100];
    int size=0;
    int prefijo=0;

    for(int i=0; text[i]!='\0'; i++){
        int encontrado=-1;
        for(int b=0; b<size; b++){
            if(diccionario[b].k==prefijo && diccionario[b].v==text[i]){
                encontrado=b+1;
                break;
            }
        }
        if(encontrado!=-1){
            prefijo=encontrado;
        } else {
            cout<<"("<<prefijo<<","<<text[i]<<")"<<endl;
            diccionario[size].k=prefijo;
            diccionario[size].v=text[i];
            size++;
            prefijo=0;
        }
    }

    delete[] text;
    delete[] diccionario;
}
