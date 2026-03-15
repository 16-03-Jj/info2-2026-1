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
    // ... resto del juego
    freeBoard(board, rows);
    return 0;
}
