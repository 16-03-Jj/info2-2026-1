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
