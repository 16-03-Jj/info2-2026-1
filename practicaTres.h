#ifndef PRACTICATRES_H
#define PRACTICATRES_H
#include <string>
using namespace std;

void RLE(string text);
void LZ78();
void LZ78decompress(int* keys, char* values, int size);
unsigned char rotarIzquierda(unsigned char byte, int n);
unsigned char xorByte(unsigned char byte, unsigned char k);
unsigned char encriptar(unsigned char byte, int n, unsigned char k);
unsigned char desencriptar(unsigned char byte, int n, unsigned char k);
void encriptarDatos(int* keys, char* values, int size, int n, unsigned char k);
void desencriptarDatos(int* keys, char* values, int size, int n, unsigned char k);
void LZ78();
void LZ78decompress(int* keys, char* values, int size);


#endif // PRACTICATRES_H
