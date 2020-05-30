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
void placeMove(short* intMove, short mark, struct Game* game);
bool aiTurn(struct Game* game);
short* convertMoveToInt(string move);

int main()
{
    struct Game game;
    bool run = true;
    printBoard(&game);
    while (run) {
        playerTurn(&game);
        printBoard(&game);
        aiTurn(&game);
        run = false;
    }

    return 0;
}

void printBoard(struct Game *game) {
    for (short i = 0; i < 3; i++) {
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
    short *intMove = convertMoveToInt(move);
    placeMove(intMove, 1, game);
    return false;
}

void placeMove(short* intMove, short mark, struct Game* game) {
    short row_val = intMove[0];
    short col_val = intMove[1];

    if (row_val > 0 && row_val <= 3 && col_val > 0 && col_val <= 3) {
        short cur_val = game->board[row_val - 1][col_val - 1];
        if (cur_val == 0) {
            game->board[row_val - 1][col_val - 1] = mark;
        }
    }
}

/*void placeMove(string move, short mark, struct Game* game) {
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

    if (row_val > 0 && row_val <= 3 && col_val > 0 && col_val <= 3) {
        short cur_val = game->board[row_val - 1][col_val - 1];
        if (cur_val == 0) {
            game->board[row_val - 1][col_val - 1] = mark;
        }
    }
}*/

bool aiTurn(struct Game* game) {
    short freeSpots[9][2];
    short fpIndex = 0;
    for (short i = 0; i < 3; i++) {
        for (short j = 0; j < 3; j++) {
            if (game->board[i][j] == 0) {
                freeSpots[fpIndex][0] = i;
                freeSpots[fpIndex][1] = j;
                fpIndex++;
            }
        }
    }

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
