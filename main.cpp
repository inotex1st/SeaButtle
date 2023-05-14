#include <iostream>
#include <windows.h>
#include <cstdlib>
using namespace std;

const int FIELD_SIZE = 10; // размерность игрового поля

char field[FIELD_SIZE][FIELD_SIZE]; // двумерный массив ячеек поля

const int NUM_SHIPS = 5; // количество кораблей
int shipsSizes[NUM_SHIPS] = {1, 2, 3, 4, 5}; // размерность каждого корабля
int shipsX[NUM_SHIPS]; // координаты кораблей на поле
int shipsY[NUM_SHIPS]; // координаты кораблей на поле
bool shipsVertical[NUM_SHIPS]; // направление кораблей

//функция выстрела
void shoot (int &x, int &y) {
    x = rand() % FIELD_SIZE;
    y = rand() % FIELD_SIZE;
}


int main() {
    SetConsoleOutputCP(CP_UTF8);
    cout << "Приветствую вас в игре морской бой \n";
    cout << "Для начала игры нажмите Enter";
    while (getchar() != '\n'); //ожидание нажатия клавиши Enter
    cout << "Приготовьтесь игра начинается!\n";

    srand(time(NULL)); // инициализировать генератор случайных чисел

    // обнуление игрового поля
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            field[i][j] = ' '; // клетка поля пустая
        }
    }

    // инициализация кораблей
    shipsX[0] = 0;
    shipsY[0] = 0;
    shipsVertical[0] = false; // горизонтальное расположение корабля

    shipsX[1] = 2;
    shipsY[1] = 0;
    shipsVertical[1] = false; // горизонтальное расположение корабля

    shipsX[2] = 4;
    shipsY[2] = 0;
    shipsVertical[2] = false; // горизонтальное расположение корабля

    shipsX[3] = 6;
    shipsY[3] = 0;
    shipsVertical[3] = false; // горизонтальное расположение корабля

    shipsX[4] = 8;
    shipsY[4] = 0;
    shipsVertical[4] = false; // горизонтальное расположение корабля

    // вывод игрового поля
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            cout << field[i][j] << " ";
        }
        cout << endl;
    }

    int hits = 0;
    while (hits < TOTAL_SHIP_CELLS) {
        int x, y;
        shoot(x, y);
        if ((field[y][x] == 'H') || (field[y][x] == 'X')) {
            continue;
        }
        bool hit = false;
        for (int i = 0; i < NUM_SHIPS; i++) {
            if ((x >= shipsX[i]) && (y >= shipsY[i]) &&
                (x < shipsX[i] + shipsSizes[i]) && (y < shipsY[i] + shipsSizes[i])) {
                hit = true;
                break;
            }
        }
        if (hit) {
            field[y][x] = 'X';
            hits++;
            cout << endl << "Попадание!" << endl;
        }
        else {
            field[y][x] = 'O';
            cout << endl << "Промах!" << endl;
        }
    }
    cout << endl << "Вы победили!" << endl;

}

//функция выстрела
void shoot (int &x, int &y) {
    x = rand() % FIELD_SIZE;
    y = rand() % FIELD_SIZE;
}

//проверка расположения корабля
bool checkOverlap(int x, int y, int size, bool vertical) {
    if ((x + size > FIELD_SIZE) || (y + size > FIELD_SIZE))
        return true;

    for (int i = y - 1; i <= y + size; i++) {
        for (int j = x - 1; j <= x + 1; j++) {
            if ((i >= 0) && (j >= 0) && (i < FIELD_SIZE) && (j < FIELD_SIZE)) {
                if (field[i][j] == 'H')
                    return true;
            }
        }
    }

    for (int i = 0; i < size; i++) {
        if (vertical)
            field[y + i][x] = 'H';
        else
            field[y][x + i] = 'H';
    }
    return false;
}