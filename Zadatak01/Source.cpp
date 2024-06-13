#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace this_thread;
using namespace chrono;


const int canvasRow = 20;
const int canvasCol = 40;

void clearScreen() {
    #if defined _WIN32
        system("cls");
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__) || defined (__APPLE__)
        system("clear"); 
    #endif
}

void draw(int row, int col, int rowA, int colA, int rowB, int colB, bool finished) {
    clearScreen();
    for (int i = 1; i <= canvasRow; i++) {
        for (int j = 1; j <= canvasCol; j++) {
            if (i == rowA && j == colA) {
                cout << "A";
            }
            else if (i == rowB && j == colB && !finished) {
                cout << "B";
            }
            else if (i == row && j == col) {
                cout << "*";
            }
            else {
                cout << "-";
            }
        }
        cout << endl;
    }
    sleep_for(milliseconds(100));
}

int main() {
    int rowA, colA, rowB, colB;

    do
    {
        cout << "Insert row and column position for A seperated by space (example: 1 1): ";
        cin >> rowA >> colA;

        cout << "Insert row and column position for B seperated by space (example: 1 40): ";
        cin >> rowB >> colB;

        if (rowA < 1 || rowA > canvasRow || colA < 1 || colA > canvasCol || rowB < 1 || rowB > canvasRow || colB < 1 || colB > canvasCol)
        {
            cout << "Invalid input" << endl;
        }

        else
        {
            break;
        }

    } while (true);

  

    int row = rowA;
    int col = colA;
    bool finished = false;

    while (row != rowB) {
        draw(row, col, rowA, colA, rowB, colB, finished);

        if (row < rowB) {
            row++;
        }
        else {
            row--;
        }
    }

    while (col != colB) {
        draw(row, col, rowA, colA, rowB, colB, finished);

        if (col < colB) {
            col++;
        }
        else {
            col--;
        }
    }



    finished = true;
    draw(rowB, colB, rowA, colA, rowB, colB, finished);

    return 0;
}