#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;

const int WIDTH = 10;
const int HEIGHT = 20;
const int COLORS[7] = {9, 14, 13, 12, 10, 6, 11}; // Blue, Yellow, Pink, Red, Green, Orange, Cyan

class Tetromino {
public:
    int x, y;
    int type;
    vector<vector<int>> shape;

    Tetromino() {
        x = WIDTH / 2 - 2;
        y = 0;
        type = rand() % 7;
        initialize();
    }

    void initialize() {
        switch (type) {
            case 0: shape = {{1, 1, 1, 1}}; break;           // I
            case 1: shape = {{1, 1}, {1, 1}}; break;         // O
            case 2: shape = {{0, 1, 0}, {1, 1, 1}}; break;   // T
            case 3: shape = {{1, 1, 0}, {0, 1, 1}}; break;   // Z
            case 4: shape = {{0, 1, 1}, {1, 1, 0}}; break;   // S
            case 5: shape = {{1, 0, 0}, {1, 1, 1}}; break;   // J
            case 6: shape = {{0, 0, 1}, {1, 1, 1}}; break;   // L
        }
    }

    void reset() {
        x = WIDTH / 2 - 2;  //coloumn
        y = 0;              //row
        type = rand() % 7;
        initialize();
    }
};

class Tetris {
private:
    vector<vector<int>> board;
    Tetromino current;
    int score;
    HANDLE hConsole;

public:
    Tetris() {
        board = vector<vector<int>>(HEIGHT, vector<int>(WIDTH, 0));
        score = 0;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    void gotoxy(int x, int y) {
        COORD coord = {(SHORT)x, (SHORT)y};
        SetConsoleCursorPosition(hConsole, coord);
    }

    bool isCollision() {
        for (int i = 0; i < current.shape.size(); i++) {
            for (int j = 0; j < current.shape[i].size(); j++) {
                if (current.shape[i][j]) {
                    int newX = current.x + j;
                    int newY = current.y + i;
                    if (newX < 0 || newX >= WIDTH || newY >= HEIGHT || (newY >= 0 && board[newY][newX])) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    void mergePiece() {
        for (int i = 0; i < current.shape.size(); i++) {
            for (int j = 0; j < current.shape[i].size(); j++) {
                if (current.shape[i][j] && current.y + i >= 0) {
                    board[current.y + i][current.x + j] = current.type + 1;
                }
            }
        }
    }

    void clearLines() {
        int lines = 0;
        for (int i = HEIGHT - 1; i >= 0; i--) {
            bool full = true;
            for (int j = 0; j < WIDTH; j++) {
                if (!board[i][j]) {
                    full = false;
                    break;
                }
            }
            if (full) {
                board.erase(board.begin() + i);
                board.insert(board.begin(), vector<int>(WIDTH, 0));
                lines++;
                i++;
            }
        }
        score += lines * 100;
    }

    void rotatePiece() {
        vector<vector<int>> rotated(current.shape[0].size(), vector<int>(current.shape.size()));
        for (int i = 0; i < current.shape.size(); i++) {
            for (int j = 0; j < current.shape[i].size(); j++) {
                rotated[j][current.shape.size() - 1 - i] = current.shape[i][j];
            }
        }
        auto original = current.shape;
        current.shape = rotated;
        if (isCollision()) {
            current.shape = original;
        }
    }

    void draw() {
        gotoxy(0, 0);
        SetConsoleTextAttribute(hConsole, 7);
        //cout << "Score: " << score << "\n";
        cout << "+" << string(WIDTH * 2, '-') << "+"<<endl;

        for (int i = 0; i < HEIGHT; i++) {
            cout << "|";
            for (int j = 0; j < WIDTH; j++) {
                bool isCurrent = false;
                int color = 7;

                for (int pi = 0; pi < current.shape.size(); pi++) {
                    for (int pj = 0; pj < current.shape[pi].size(); pj++) {
                        if (current.shape[pi][pj] && i == current.y + pi && j == current.x + pj) {
                            isCurrent = true;
                            color = COLORS[current.type];
                        }
                    }
                }

                if (isCurrent) {
                    SetConsoleTextAttribute(hConsole, color);
                    cout << "[]";
                } 
                else if (board[i][j]) {
                    SetConsoleTextAttribute(hConsole, COLORS[board[i][j] - 1]);
                    cout << "##";
                } 
                else {
                    SetConsoleTextAttribute(hConsole, 7);
                    cout << "  ";
                }
            }
            SetConsoleTextAttribute(hConsole, 7);
            cout << "|"<<endl;
        }
        cout << "+" << string(WIDTH * 2, '-') << "+"<<endl;
        cout << "Score: " << score << endl;
    }

    void play() {
        auto lastFall = chrono::steady_clock::now();
        while (true) {
            draw();

            if (_kbhit()) {
                char key = _getch();
                if (key == 'a') {
                    current.x--;
                    if (isCollision()) current.x++;
                } 
                else if (key == 'd') {
                    current.x++;
                    if (isCollision()) current.x--;
                } 
                else if (key == 's') {
                    current.y++;
                    if (isCollision()) {
                        current.y--;
                        mergePiece();
                        clearLines();
                        current.reset();
                        if (isCollision()) {
                            gotoxy(0, HEIGHT + 3);
                            cout << "GAME OVER! Final Score: " << score << "\n";
                            break;
                        }
                    }
                } 
                else if (key == 'w') {
                    rotatePiece();
                } 
                else if (key == 'q') {
                    gotoxy(0, HEIGHT + 3);
                    cout << "GAME OVER! Final Score: " << score << "\n";
                    break;
                }
            }

            auto now = chrono::steady_clock::now();
            if (chrono::duration_cast<chrono::milliseconds>(now - lastFall).count() > 500) {
                current.y++;
                if (isCollision()) {
                    current.y--;
                    mergePiece();
                    clearLines();
                    current.reset();
                    if (isCollision()) {
                        gotoxy(0, HEIGHT + 3);
                        cout << "GAME OVER! Final Score: " << score << "\n";
                        break;
                    }
                }
                lastFall = now;
            }
            Sleep(50);
        }
    }
};

int main() {
    srand((unsigned)time(0));
    Tetris game;
    game.play();
    return 0;
}
