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
