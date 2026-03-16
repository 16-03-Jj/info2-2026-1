#include <QCoreApplication>
#include "desafio1.h"
#include <iostream>
using namespace std;

int main()
{
    int rows=0,columns=0;
    validateData(rows,columns);
    uint8_t** board = nullptr;
    createBoard(board, rows, columns);
    printBoard(board, rows, columns);
    int height, width=0;
    int type = 2;  // prueba con la pieza T
    uint8_t* piece = createPiece(type, height, width);
    printPiece(piece, height, width);
    // ... resto del juego
    delete[] piece;
    freeBoard(board, rows);

    return 0;
}
