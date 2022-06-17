#include <bits/stdc++.h>

using namespace std;

class Robot {
    char** board;
    int round;
    int width, height;
    pair<int, int> ALocation, BLocation;
    public:
        Robot(int robot, int width,int height);
        void init(); 
        bool validatePosition(int x, int y);
    
    
};

void Robot::init() {
    board = new char*[height];
    for (int i = 0; i < height; i++) {
        board[i] = new char[width];
        for (int j = 0; j < width; j++) {
            cin >> board[i][j];
            if (board[i][j] == 'A') ALocation = make_pair(j, i);
            if (board[i][j] == 'B') BLocation = make_pair(j, i);
        }
    }
}


Robot::Robot(int _round, int _width, int _height) {
        round = _round;
        width = _width;
        height = _height;
}

Robot::~Robot() {
    for (int i = 0; i < height; i++) {
        delete[] board[i];
    }
    delete[] board;
}

int main(void) {
    int round, M, N;
    cin >> round >> M >> N;
    Robot robot(round, N, M);
}