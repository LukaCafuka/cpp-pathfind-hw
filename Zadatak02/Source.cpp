#include <iostream>
#include <chrono>
#include <thread>
#include <queue>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;
using namespace this_thread;
using namespace chrono;

const int canvasRow = 20;
const int canvasCol = 40;
char canvas[canvasRow + 1][canvasCol + 1];

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
                cout << canvas[i][j];
            }
        }
        cout << endl;
    }
    sleep_for(milliseconds(100));
}

bool isValid(int row, int col) {
    return row >= 1 && row <= canvasRow && col >= 1 && col <= canvasCol && canvas[row][col] != '#';
}

vector<pair<int, int>> dijkstra(int rowA, int colA, int rowB, int colB) {
    vector<vector<int>> dist(canvasRow + 1, vector<int>(canvasCol + 1, numeric_limits<int>::max()));
    vector<vector<pair<int, int>>> parent(canvasRow + 1, vector<pair<int, int>>(canvasCol + 1, { -1, -1 }));
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    vector<pair<int, int>> path;
    int dr[] = { -1, 1, 0, 0 };
    int dc[] = { 0, 0, -1, 1 };

    pq.push({ 0, {rowA, colA} });
    dist[rowA][colA] = 0;

    while (!pq.empty()) {
        int d = pq.top().first;
        int r = pq.top().second.first;
        int c = pq.top().second.second;
        pq.pop();

        if (r == rowB && c == colB) {
            while (!(r == rowA && c == colA)) {
                path.push_back({ r, c });
                tie(r, c) = parent[r][c];
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (isValid(nr, nc) && dist[nr][nc] > d + 1) {
                dist[nr][nc] = d + 1;
                pq.push({ dist[nr][nc], {nr, nc} });
                parent[nr][nc] = { r, c };
            }
        }
    }

    return path;
}

int main() {

    for (int i = 1; i <= canvasRow; i++) {
        for (int j = 1; j <= canvasCol; j++) {
            canvas[i][j] = '-';
        }
    }
    canvas[1][10] = '#';
    canvas[2][10] = '#';
    canvas[3][10] = '#';
    canvas[4][10] = '#';
    canvas[5][10] = '#';
    canvas[6][10] = '#';
    canvas[7][10] = '#';

    int rowA, colA, rowB, colB;

    do {
        cout << "Insert row and column position for A separated by space (example: 1 1): ";
        cin >> rowA >> colA;

        cout << "Insert row and column position for B separated by space (example: 1 40): ";
        cin >> rowB >> colB;

        if (rowA < 1 || rowA > canvasRow || colA < 1 || colA > canvasCol || rowB < 1 || rowB > canvasRow || colB < 1 || colB > canvasCol) {
            cout << "Invalid input" << endl;
        }
        else {
            break;
        }
    } while (true);

    vector<pair<int, int>> path = dijkstra(rowA, colA, rowB, colB);

    if (path.empty()) {
        cout << "No path found!" << endl;
        return 1;
    }

    bool finished = false;

    for (const auto& p : path) {
        int row = p.first;
        int col = p.second;
        draw(row, col, rowA, colA, rowB, colB, finished);
    }

    finished = true;
    draw(rowB, colB, rowA, colA, rowB, colB, finished);

    return 0;
}
