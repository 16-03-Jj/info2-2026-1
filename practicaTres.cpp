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

unsigned char rotarIzquierda(unsigned char byte, int n){
    return (byte << n) | (byte >> (8-n));
}

unsigned char xorByte(unsigned char byte, unsigned char k){
    return byte ^ k;
}

unsigned char encriptar(unsigned char byte, int n, unsigned char k){
    return xorByte(rotarIzquierda(byte, n), k);
}

unsigned char desencriptar(unsigned char byte, int n, unsigned char k){
    unsigned char sinXor = byte ^ k;
    return (sinXor >> n) | (sinXor << (8-n));
}

void encriptarDatos(int* keys, char* values, int size, int n, unsigned char k){
    cout<<"Encrypted: "<<endl;
    for(int i=0; i<size; i++){
        keys[i]=encriptar((unsigned char)keys[i], n, k);
        values[i]=encriptar((unsigned char)values[i], n, k);
        cout<<"("<<keys[i]<<","<<values[i]<<")"<<endl;
    }
}

void desencriptarDatos(int* keys, char* values, int size, int n, unsigned char k){
    cout<<"Decrypted: "<<endl;
    for(int i=0; i<size; i++){
        keys[i]=desencriptar((unsigned char)keys[i], n, k);
        values[i]=desencriptar((unsigned char)values[i], n, k);
        cout<<"("<<keys[i]<<","<<values[i]<<")"<<endl;
    }
}

void LZ78decompress(int* keys, char* values, int size){
    char* result = new char[1000];
    int pos = 0;
    for(int i=0; i<size; i++){
        if(keys[i]==0){
            result[pos]=values[i];
            pos++;
        } else {
            int idx=keys[i];
            int* cadena=new int[100];
            int csize=0;
            while(idx!=0){
                cadena[csize]=idx-1;
                csize++;
                idx=keys[idx-1];
            }
            for(int j=csize-1; j>=0; j--){
                result[pos]=values[cadena[j]];
                pos++;
            }
            result[pos]=values[i];
            pos++;
            delete[] cadena;
        }
    }
    result[pos]='\0';
    cout<<"Decompressed: "<<result<<endl;
    delete[] result;
}

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
    if(prefijo!=0){
        cout<<"("<<prefijo<<","<<'\0'<<")"<<endl;
    }

    int* keys=new int[size];
    char* values=new char[size];
    for(int i=0; i<size; i++){
        keys[i]=diccionario[i].k;
        values[i]=diccionario[i].v;
    }

    int n;
    unsigned char k;
    int temp;
    cout<<"Enter rotation value (1-7): ";
    cin>>n;
    cout<<"Enter XOR key (0-255): ";
    cin>>temp;
    k=(unsigned char)temp;

    encriptarDatos(keys, values, size, n, k);
    desencriptarDatos(keys, values, size, n, k);
    LZ78decompress(keys, values, size);

    delete[] keys;
    delete[] values;
    delete[] text;
    delete[] diccionario;
}
