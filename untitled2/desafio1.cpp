#include "desafio1.h"
#include <iostream>
using namespace std;
void validateData(int &rows, int &columns){
    cout<<"Enter the number of rows (multiple of 8): "<<endl;
    cin>>rows;
    while (cin.fail() || rows < 8 || rows % 8 != 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Enter a number multiple of 8 and >= 8: "<<endl;
        cin >> rows;
    }
    cout<<"Enter the number of columns (multiple of 8): "<<endl;
    cin>>columns;
    while (cin.fail() || columns < 8 || columns % 8 != 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Enter a number multiple of 8 and >= 8: "<<endl;
        cin >> columns;
    }

}
#include <cstdint>

void createBoard(uint8_t** &board, int rows, int columns){
    int bytesPerRow = columns / 8;
    board = new uint8_t*[rows];
    for(int i = 0; i < rows; i++){
        board[i] = new uint8_t[bytesPerRow];
        for(int j = 0; j < bytesPerRow; j++){
            board[i][j] = 0;  // todo vacío al inicio
        }
    }
}

void freeBoard(uint8_t** board, int rows){
    for(int i = 0; i < rows; i++){
        delete[] board[i];
    }
    delete[] board;
}
void printBoard(uint8_t** board, int rows, int columns){
    int bytesPerRow = columns / 8;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < bytesPerRow; j++){
            for(int bit = 7; bit >= 0; bit--){
                if(board[i][j] & (1 << bit)){
                    cout << "#";
                } else {
                    cout << ".";
                }
            }
        }
        cout << endl;
    }
}
uint8_t* rotatePiece(uint8_t* piece, int height, int width, int &newHeight, int &newWidth){
    newHeight = width;
    newWidth = height;

    uint8_t* rotated = new uint8_t[newHeight];
    for(int i = 0; i < newHeight; i++){
        rotated[i] = 0;
    }

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if(piece[i] & (1 << (width - 1 - j))){
                // rotación 90° horario: nueva fila=j, nueva col=height-1-i
                int newRow = j;
                int newCol = height - 1 - i;
                rotated[newRow] |= (1 << (newWidth - 1 - newCol));
            }
        }
    }
    return rotated;
}
uint8_t* createPiece(int type, int &height, int &width){
    uint8_t* piece = nullptr;

    if(type == 0){        // pieza I
        height = 1;
        width = 4;
        piece = new uint8_t[height];
        piece[0] = 0b00001111;  // # # # #

    } else if(type == 1){ // pieza O
        height = 2;
        width = 2;
        piece = new uint8_t[height];
        piece[0] = 0b00000011;  // # #
        piece[1] = 0b00000011;  // # #

    } else if(type == 2){ // pieza T
        height = 2;
        width = 3;
        piece = new uint8_t[height];
        piece[0] = 0b00000010;  // . # .
        piece[1] = 0b00000111;  // # # #

    } else if(type == 3){ // pieza S
        height = 2;
        width = 3;
        piece = new uint8_t[height];
        piece[0] = 0b00000110;  // . # #
        piece[1] = 0b00000011;  // # # .

    } else if(type == 4){ // pieza Z
        height = 2;
        width = 3;
        piece = new uint8_t[height];
        piece[0] = 0b00000011;  // # # .
        piece[1] = 0b00000110;  // . # #

    } else if(type == 5){ // pieza J
        height = 3;
        width = 2;
        piece = new uint8_t[height];
        piece[0] = 0b00000010;  // # .
        piece[1] = 0b00000010;  // # .
        piece[2] = 0b00000011;  // # #

    } else if(type == 6){ // pieza L
        height = 3;
        width = 2;
        piece = new uint8_t[height];
        piece[0] = 0b00000001;  // . #
        piece[1] = 0b00000001;  // . #
        piece[2] = 0b00000011;  // # #
    }
    return piece;
}
void printPiece(uint8_t* piece, int height, int width){
    for(int i = 0; i < height; i++){
        for(int j = width - 1; j >= 0; j--){
            if(piece[i] & (1 << j)){
                cout << "# ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}
void printBoardWithPiece(uint8_t** board, int rows, int columns, uint8_t* piece, int pieceHeight, int pieceWidth, int pieceRow, int pieceCol){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){

            // verificar si la pieza ocupa esta celda (i,j)
            int pieceRowIndex = i - pieceRow;
            int pieceColIndex = j - pieceCol;

            bool enPieza = false;
            if(pieceRowIndex >= 0 && pieceRowIndex < pieceHeight &&
                pieceColIndex >= 0 && pieceColIndex < pieceWidth){
                enPieza = piece[pieceRowIndex] & (1 << (pieceWidth - 1 - pieceColIndex));
            }

            // verificar si el tablero tiene algo en (i,j)
            int byteIndex = j / 8;
            int bitIndex  = 7 - (j % 8);
            bool enTablero = board[i][byteIndex] & (1 << bitIndex);

            if(enPieza || enTablero){
                cout << "#";
            } else {
                cout << ".";
            }
        }
        cout << endl;
    }
}
bool canMove(uint8_t** board, int rows, int columns, uint8_t* piece, int pieceHeight, int pieceWidth, int newRow, int newCol){
    for(int i = 0; i < pieceHeight; i++){
        for(int j = 0; j < pieceWidth; j++){
            if(piece[i] & (1 << (pieceWidth - 1 - j))){
                int boardRow = newRow + i;
                int boardCol = newCol + j;

                // ← ignorar filas que están fuera por arriba
                if(boardRow < 0) continue;

                // verificar bordes
                if(boardRow >= rows || boardCol < 0 || boardCol >= columns){
                    return false;
                }

                // verificar colisión
                int byteIndex = boardCol / 8;
                int bitIndex  = 7 - (boardCol % 8);
                if(board[boardRow][byteIndex] & (1 << bitIndex)){
                    return false;
                }
            }
        }
    }
    return true;
}
void fixPiece(uint8_t** board, int columns, uint8_t* piece, int pieceHeight, int pieceWidth, int pieceRow, int pieceCol){
    int bytesPerRow = columns / 8;
    for(int i = 0; i < pieceHeight; i++){
        for(int j = 0; j < pieceWidth; j++){
            if(piece[i] & (1 << (pieceWidth - 1 - j))){
                int boardRow = pieceRow + i;
                int boardCol = pieceCol + j;

                // ← verificar que esté dentro del tablero
                if(boardRow < 0 || boardCol < 0 || boardCol >= columns){
                    continue;  // ignorar bits fuera del tablero
                }

                int byteIndex = boardCol / 8;
                int bitIndex  = 7 - (boardCol % 8);
                board[boardRow][byteIndex] |= (1 << bitIndex);
            }
        }
    }
}
void clearLines(uint8_t** board, int rows, int columns){
    int bytesPerRow = columns / 8;

    for(int i = rows - 1; i >= 0; i--){

        // verificar si la fila está llena
        bool full = true;
        for(int j = 0; j < bytesPerRow; j++){
            if(board[i][j] != 255){
                full = false;
                break;
            }
        }

        // si está llena, bajar todas las filas superiores
        if(full){
            for(int k = i; k > 0; k--){
                for(int j = 0; j < bytesPerRow; j++){
                    board[k][j] = board[k-1][j];
                }
            }
            // limpiar fila superior
            for(int j = 0; j < bytesPerRow; j++){
                board[0][j] = 0;
            }
            i++;
        }
    }
}
void gameLoop(uint8_t** board, int rows, int columns){
    srand(time(0));
    int height = 0, width = 0;  // ← inicializar en 0
    int type = rand() % 7;
    uint8_t* piece = createPiece(type, height, width);
    int pieceRow = -(height - 1);
    int pieceCol = (columns / 2) - (width / 2);
    bool gameOver = false;
    char accion;
    int rotation = 0;

    while(!gameOver){
        printBoardWithPiece(board, rows, columns, piece, height, width, pieceRow, pieceCol);
        cout << "Accion: [A]Izq [D]Der [S]Bajar [W]Rotar [Q]Salir: ";
        cin >> accion;

        if(accion == 'q' || accion == 'Q'){
            gameOver = true;

        } else if(accion == 'a' || accion == 'A'){
            if(canMove(board, rows, columns, piece, height, width, pieceRow, pieceCol - 1)){
                pieceCol--;
            }

        } else if(accion == 'd' || accion == 'D'){
            if(canMove(board, rows, columns, piece, height, width, pieceRow, pieceCol + 1)){
                pieceCol++;
            }

        } else if(accion == 's' || accion == 'S'){
            if(canMove(board, rows, columns, piece, height, width, pieceRow + 1, pieceCol)){
                pieceRow++;
            } else {
                fixPiece(board, columns, piece, height, width, pieceRow, pieceCol);
                clearLines(board, rows, columns);
                delete[] piece;

                type = rand() % 7;
                height = 0; width = 0;  // ← resetear antes
                piece = createPiece(type, height, width);
                pieceRow = -(height - 1);  // ← usar height actualizado
                pieceCol = (columns / 2) - (width / 2);
                rotation = 0;

                if(!canMove(board, rows, columns, piece, height, width, pieceRow, pieceCol)){
                    gameOver = true;
                    cout << "GAME OVER" << endl;
                }
            }

        } else if(accion == 'w' || accion == 'W'){
            int nextRotation = (rotation + 1) % 4;
            int newHeight = 0, newWidth = 0;  // ← inicializar en 0
            uint8_t* original = createPiece(type, newHeight, newWidth);

            for(int r = 0; r < nextRotation; r++){
                int rh, rw;
                uint8_t* temp = rotatePiece(original, newHeight, newWidth, rh, rw);
                delete[] original;
                original = temp;
                newHeight = rh;
                newWidth = rw;
            }

            if(canMove(board, rows, columns, original, newHeight, newWidth, pieceRow, pieceCol)){
                delete[] piece;
                piece = original;
                height = newHeight;
                width = newWidth;
                rotation = nextRotation;
            } else {
                delete[] original;
            }
        }
    }
    delete[] piece;
}
