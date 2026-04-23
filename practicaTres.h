#ifndef PRACTICATRES_H
#define PRACTICATRES_H
#include <string>
#include <stdexcept>
using namespace std;

char rotarIzquierda(char byte, int n);
char rotarDerecha(char byte, int n);
char encriptar(char byte, int n, char key);
char desencriptar(char byte, int n, char key);
string leerArchivo(string nombreArchivo);
void escribirArchivo(string nombreArchivo, string contenido);
void RLE(string text);
string comprimirRLE(string text);
string descomprimirRLE(string text);
void LZ78(string text);

#endif
