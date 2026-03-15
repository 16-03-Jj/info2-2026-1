#ifndef DESAFIO1_H
#define DESAFIO1_H
#include <cstdint>
void validateData(int &rows, int &columns);
void createBoard(uint8_t** &board, int rows, int columns);
void freeBoard(uint8_t** board, int rows);
void printBoard(uint8_t** board, int rows, int columns);

#endif // DESAFIO1_H
