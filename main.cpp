#include <iostream>
#include <string>
#include "practicaTres.h"
using namespace std;

int main(){
    try{
        int opcion;
        cout<<"1. Procesar archivo Original (hint)"<<endl;
        cout<<"2. Desencriptar archivo Encriptado"<<endl;
        cout<<"Seleccione una opcion: ";
        cin>>opcion;

        string rutaBase="C:\\Users\\JUAN JOSE\\Downloads\\practicaTres\\";

        if(opcion==1){
            string hint=leerArchivo(rutaBase+"dataset_Original_hint_0.txt");
            cout<<"Original: "<<hint<<endl;

            int metodo;
            cout<<"1. Comprimir con RLE"<<endl;
            cout<<"2. Comprimir con LZ78"<<endl;
            cout<<"Seleccione metodo: ";
            cin>>metodo;

            if(metodo==1){
                string comprimido=comprimirRLE(hint);
                cout<<"Comprimido RLE: "<<comprimido<<endl;
                string descomprimido=descomprimirRLE(comprimido);
                cout<<"Descomprimido: "<<descomprimido<<endl;
                if(hint==descomprimido){
                    cout<<"OK: textos identicos"<<endl;
                }else{
                    cout<<"ERROR: textos diferentes"<<endl;
                }
            }else{
                LZ78(hint);
            }

        }else if(opcion==2){
            string text=leerArchivo(rutaBase+"dataset_Encriptado1.txt");
            string hint=leerArchivo(rutaBase+"dataset_Original_hint_0.txt");

            char key='m';
            int n=5;
            string desencriptado="";
            for(int i=0;i<text.size();i++){
                desencriptado+=desencriptar(text[i],n,key);
            }
            cout<<"Desencriptado: "<<desencriptado<<endl;
            escribirArchivo(rutaBase+"resultado_desencriptado.txt", desencriptado);
            cout<<"Resultado guardado en resultado_desencriptado.txt"<<endl;

            if(desencriptado==hint){
                cout<<"OK: texto desencriptado identico al original"<<endl;
            }else{
                cout<<"ERROR: textos diferentes"<<endl;
                cout<<"Tamano desencriptado: "<<desencriptado.size()<<endl;
                cout<<"Tamano hint: "<<hint.size()<<endl;
            }
        }

    }catch(exception& e){
        cout<<"Error: "<<e.what()<<endl;
    }
    return 0;
}
