#ifndef DESAFIO1_H
#define DESAFIO1_H
#include <cstdint>
void validateData(int &rows, int &columns);
void createBoard(uint8_t** &board, int rows, int columns);
void freeBoard(uint8_t** board, int rows);
void printBoard(uint8_t** board, int rows, int columns);
uint8_t* rotatePiece(uint8_t* piece, int height, int width, int &newHeight, int &newWidth);
uint8_t* createPiece(int type, int &height, int &width);
void printPiece(uint8_t* piece, int height, int width);

#endif // DESAFIO1_H
