#include <bits/stdc++.h>

using namespace std;

class Robot
{
public:
    char **board;
    int round;
    int width;
    int height;
    int aScore;
    int bScore;
    char player;
    pair<int, int> aLocation, bLocation;
    Robot(int robot, int width, int height);
    ~Robot();
    void init();
    void showBoard();
    bool validatePosition(int x, int y, int control = 100);
    string makeChoice(int x, int y);
    int calculateScore(int nowI, int nowJ, int score);
    int bfs(int i, int j);
};

Robot::Robot(int _round, int _width, int _height)
{
    round = _round;
    width = _width;
    height = _height;
}

Robot::~Robot()
{
    for (int i = 0; i < height; i++)
    {
        delete[] board[i];
    }
    delete[] board;
}

void Robot::init()
{
    board = new char *[height];
    for (int i = 0; i < height; i++)
    {
        board[i] = new char[width];
        for (int j = 0; j < width; j++)
        {
            cin >> board[i][j];
            if (board[i][j] == 'A')
                aLocation = make_pair(i, j);
            if (board[i][j] == 'B')
                bLocation = make_pair(i, j);
        }
    }

    cin >> aScore >> bScore >> player;
}

void Robot::showBoard()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cout << board[i][j];
        }
        cout << endl;
    }
}

bool Robot::validatePosition(int x, int y, int control)
{
    // int score = (player == 'A') ? aScore : bScore;
    // if (score <= 5 || control == 0)
    // {
    //     return (
    //         x >= 0 && x < width && y >= 0 && y < height &&
    //         board[x][y] != 'x' &&
    //         board[x][y] != 'A' && board[x][y] != 'B');
    // }
    // else
    // {
    return (
        x >= 0 && x < width && y >= 0 && y < height &&
        board[x][y] != 'x' &&
        board[x][y] != 'A' && board[x][y] != 'B' && board[x][y] != 't');
    // }
}

string Robot::makeChoice(int x, int y)
{

    vector<pair<int, string>> rank;
    if (validatePosition(x - 1, y, 0))
    {
        int score = bfs(x - 1, y);
        if (board[x - 1][y] == 't')
        {
            score = 0.1;
        }
        rank.push_back(make_pair(score, "UP"));
    }
    if (validatePosition(x + 1, y, 0))
    {
        int score = bfs(x + 1, y);
        if (board[x + 1][y] == 't')
        {
            score = 0.1;
        }
        rank.push_back(make_pair(score, "DOWN"));
    }
    if (validatePosition(x, y - 1, 0))
    {
        int score = bfs(x, y - 1);
        if (board[x][y - 1] == 't')
        {
            score = 0.1;
        }
        rank.push_back(make_pair(score, "LEFT"));
    }
    if (validatePosition(x, y + 1, 0))
    {
        int score = bfs(x, y + 1);
        if (board[x][y + 1] == 't')
        {
            score = 0.1;
        }
        rank.push_back(make_pair(score, "RIGHT"));
    }
    if (rank.size() > 0)
    {
        mt19937 gen(random_device{}());
        vector<int> weight;
        sort(rank.begin(), rank.end());
        for (int i = 0; i < rank.size(); i++)
        {
            weight.push_back(rank[i].first);
        }
        discrete_distribution<size_t> d{weight.begin(), weight.end()};
        return rank[d(gen)].second;
    }
    else
    {
        return "RIGHT";
    }
}

int Robot::calculateScore(int nowI, int nowJ, int score)
{
    if (board[nowI][nowJ] == 'm')
    {
        score++;
    }
    else if (board[nowI][nowJ] == 's')
    {
        score *= 2;
    }
    else if (board[nowI][nowJ] == 'n')
    {
        score--;
    }

    else if (board[nowI][nowJ] == 'b')
    {
        score -= 2;
    }
    return score;
}

int Robot::bfs(int i, int j)
{
    int boardDfs[height][width];
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            boardDfs[x][y] = 0;
        }
    }
    int score = (player == 'A') ? aScore : bScore;
    int limit = 25;
    int steps = 0;
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
    queue<pair<int, int>> Q;
    Q.push(make_pair(i, j));
    while (Q.size())
    {
        int nowI = Q.front().first;
        int nowJ = Q.front().second;
        Q.pop();
        score = calculateScore(nowI, nowJ, score);
        boardDfs[nowI][nowJ] = 2;
        steps++;

        if (steps >= limit)
        {
            return score;
        }

        for (int k = 0; k < 4; k++)
        {
            int nexI = nowI + dx[k];
            int nexJ = nowJ + dy[k];
            if (validatePosition(nexI, nexJ) && boardDfs[nexI][nexJ] == 0)
            {
                Q.push(make_pair(nexI, nexJ));
            }
        }
    }
    return (score > 1) ? score : 0;
}

int main(void)
{
    int round, M, N;
    cin >> round >> M >> N;
    Robot robot(round, N, M);

    robot.init();
    if (robot.player == 'A')
    {
        cout << robot.makeChoice(robot.aLocation.first, robot.aLocation.second) << endl;
    }
    else
    {
        cout << robot.makeChoice(robot.bLocation.first, robot.bLocation.second) << endl;
    }
}

//./a.out < ../sample/sampleA.in