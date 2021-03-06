// tictactoe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

using namespace std;

struct Game {
    short board[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    string player[9];
    short playerMoves = 0;
    int ai[9];
};

void printBoard(struct Game *game);
bool playerTurn(struct Game *game);
void placeMove(short intMove[], short mark, struct Game* game);
bool aiTurn(struct Game* game);
short* convertMoveToInt(string move);
bool checkStatus(Game* game);
short determineWinner(Game* game, bool* emptySpots);

int main()
{
    struct Game game;
    bool run = true;
    printBoard(&game);
    while (run) {
        playerTurn(&game);
        run = checkStatus(&game);
        if (run) {
            aiTurn(&game);
        }
        
        printBoard(&game);
        run = checkStatus(&game);
    }

    return 0;
}

void printBoard(struct Game *game) {
    cout << "       1    2    3  " << endl;
    for (short i = 0; i < 3; i++) {
        switch (i) {
            case 0:
                cout << "  A  ";
                break;
            case 1:
                cout << "  B  ";
                break;
            case 2:
                cout << "  C  ";
                break;
        }
        for (short j = 0; j < 3; j++) {
            switch (game->board[i][j]) {
                case 0:
                    cout << " [ ] ";
                    break;
                case 1:
                    cout << " [O] ";
                    break;
                case 2:
                    cout << " [X] ";
                    break;
            }
        }
        cout << endl;
    }
}

bool playerTurn(struct Game *game) {
    string move;
    cout << "Your next move: ";
    cin >> move;
    game->player[game->playerMoves] = move;
    game->playerMoves++;
    short *intMove_p = convertMoveToInt(move);;
    short intMove[2] = { intMove_p[0], intMove_p[1] };
    placeMove(intMove, 1, game);
    return false;
}

void placeMove(short intMove[], short mark, struct Game* game) {
    short row_val = intMove[0];
    short col_val = intMove[1];

    if (row_val > 0 && row_val <= 3 && col_val > 0 && col_val <= 3) {
        short cur_val = game->board[row_val - 1][col_val - 1];
        if (cur_val == 0) {
            game->board[row_val - 1][col_val - 1] = mark;
        }
    }
}

bool aiTurn(struct Game* game) {
    short freeSpots[9][2];
    short fpIndex = 0;
    for (short i = 0; i < 3; i++) {
        for (short j = 0; j < 3; j++) {
            if (game->board[i][j] == 0) {
                freeSpots[fpIndex][0] = i + 1;
                freeSpots[fpIndex][1] = j + 1;
                fpIndex++;
            }
        }
    }

    placeMove(freeSpots[0], 2, game);

    return false;
}

short* convertMoveToInt(string move) {
    char first = move.at(0);
    short row_val;
    if (first == 'a') {
        row_val = 1;
    }
    else if (first == 'b') {
        row_val = 2;
    }
    else {
        row_val = 3;
    }
    char second = move.at(1);
    short col_val = second - 48;
    short intMove[2];
    intMove[0] = row_val;
    intMove[1] = col_val;

    return intMove;
}

bool checkStatus(Game* game) {
    bool emptySpots = false;
    short winner = determineWinner(game, &emptySpots);
    bool canContinue = true;

    switch (winner) {
        case 1:
            cout << "Player wins!" << endl;
            canContinue = false;
            break;
        case 2:
            cout << "AI wins!" << endl;
            canContinue = false;
            break;
    }

    if (!emptySpots) {
        cout << "Draw" << endl;
        canContinue = false;
    }

    return canContinue;
}

short determineWinner(Game* game, bool* emptySpots) {
    short winner = 0;
    short status[8][3];
    for (short i = 0; i < 3; i++) {
        status[0][i] = game->board[0][i];
        status[1][i] = game->board[1][i];
        status[2][i] = game->board[2][i];

        status[3][i] = game->board[i][0];
        status[4][i] = game->board[i][1];
        status[5][i] = game->board[i][2];

        status[6][i] = game->board[i][i];
        status[7][i] = game->board[2 - i][i];
    }

    for (int i = 0; i < 8; i++) {
        if (winner > 0) {
            break;
        }

        for (int j = 1; j < 3; j++) {
            if (status[i][j] == 0) {
                *emptySpots = true;
                break;
            }

            if (status[i][j - 1] != status[i][j]) {
                break;
            }

            if (j == 2) {
                winner = status[i][j];
                break;
            }
            
        }
    }

    return winner;
}
