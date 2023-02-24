#include<iostream>
#include<algorithm>
#include<math.h>

#include <chrono>
using namespace std::chrono;
using namespace std;

struct Move {
    int row, col;
};


class BOT {
public:
    char AI = 'O', PL = 'X'; //define character for the moves of COM. and Player
    char board[10][10];
    int check() { //check if the game is end or not

        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (board[i][j] == '_') continue;

                //row check
                if (i < 7 && j < 10) {
                    if (board[i][j] == board[i + 1][j] && board[i][j] == board[i + 2][j] && board[i][j] == board[i + 3][j]) {
                        return board[i][j] == AI ? 10 : -10;
                    }
                }

                //colum check
                if (i < 10 && j < 7) {
                    if (board[i][j] == board[i][j + 1] && board[i][j] == board[i][j + 2] && board[i][j] == board[i][j + 3]) {
                        return board[i][j] == AI ? 10 : -10;
                    }
                }

                //diagnol
                if (i < 7 && j < 7) {
                    if (board[i][j] == board[i + 1][j + 1] && board[i][j] == board[i + 2][j + 2] && board[i][j] == board[i + 3][j + 3]) {
                        return board[i][j] == AI ? 10 : -10;
                    }
                }

                if (i > 3 && j < 7) {
                    if (board[i][j] == board[i - 1][j + 1] && board[i][j] == board[i - 2][j + 2] && board[i][j] == board[i - 3][j + 3]) {
                        return board[i][j] == AI ? 10 : -10;
                    }
                }
                return 0;
            }
            return 1;
        }


        for (int i = 0; i < 10; i++) { //check remaining moves on the board
            for (int j = 0; j < 10; j++) {
                if (board[i][j] == '_')
                    return 0; //if the game is not end
            }
        }
        return 1; //no remaining moves, game tie
    }

    int minimax(int depth, bool isMax, int choose) { //MiniMax function

        if (depth > choose) return 1;
        int score = check();

        if (score == 100) return score - depth; //check how many points COM will have when win the game with this depth
        if (score == -100)  return score + depth; //check how many points COM will have when lose the game with this depth
        if (score == 1) return 0; //game tie

        if (isMax) { // COM.'s turn
            int best = -1000;
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {

                    if (board[i][j] == '_') {// Check if cell is empty
                        board[i][j] = AI; // Make the move
                        best = max(best, minimax(depth + 1, !isMax, choose)); //Call minimax recursively
                        board[i][j] = '_';// Undo the move
                    }

                }
            }
            return best;
        }
        else { //Player's turn
            int best = 1000;

            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    if (board[i][j] == '_') { // Check if cell is empty
                        board[i][j] = PL; // Make the move
                        best = min(best, minimax(depth + 1, !isMax, choose)); //Call minimax recursively
                        board[i][j] = '_'; // Undo the move
                    }
                }
            }
            return best;
        }
    }

    void showBoard() {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                cout << board[i][j] << "  "; //show the cell
            }
            cout << endl;
        }
        cout << endl;
    }

    Move findBestMove(int choose) { // return the best possible move
        int bestVal = -1000;
        Move bestMove;
        bestMove.row = -1;
        bestMove.col = -1;

        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (board[i][j] == '_') { // Check if cell is empty
                    board[i][j] = AI; // Make the move
                    int moveVal = minimax(0, false, choose); //calculate the point of this move
                    //cout << "i " << i << " j " << j << " " << moveVal << endl;
                    board[i][j] = '_'; // Undo the move
                    if (moveVal > bestVal) { //update if new value is bigger than best value
                        bestMove.row = i;
                        bestMove.col = j;
                        bestVal = moveVal;
                    }
                }
            }
        }
        board[bestMove.row][bestMove.col] = AI; // input the move
        showBoard();
        return bestMove;
    }

    void play() {
        int choose;

        cout << "Choose the level of the game:" << endl;
        cout << "Press 1: Beginner" << endl;
        cout << "Press 2: Intermediate" << endl;
        cout << "Press 3: Expert" << endl;
        cout << "____________________" << endl;
        cin >> choose;

        while (choose < 1 && choose > 3) {
            cout << "Invalid. Again: "; //re-input if the cooperate has had a value
            cin >> choose;
        }

        int x, y;

        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                board[i][j] = '_'; //assign the board
            }
        }
        showBoard();
        while (check() == 0) {
            cin >> x >> y; //input the cooperate of player's move
            while (board[x][y] != '_') {
                cout << "Invalid. Again: "; //re-input if the cooperate has had a value
                cin >> x >> y;
            }
            board[x][y] = PL;
            showBoard();
            if (check() != 0) {
                switch (check()) {
                case 1: {
                    cout << "GAME TIE." << endl;
                    break;
                }
                case 10: {
                    cout << "COMPUTER WON!" << endl;
                    break;
                }
                case -10: {
                    cout << "YOU WON!" << endl;
                    break;
                }
                }
                break;
            }
            cout << endl;
            cout << "COMPUTER's turn:" << endl;
            auto start = high_resolution_clock::now();
            Move bestMove = findBestMove(choose); // COM.'s move
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start);
            cout << "Time level " << choose << " " << duration.count() << "ms" << endl;
            if (check() != 0) {
                switch (check()) {
                case 1: {
                    cout << "GAME TIE." << endl;
                    break;
                }
                case 10: {
                    cout << "COMPUTER WON!" << endl;
                    break;
                }
                case -10: {
                    cout << "YOU WON!" << endl;
                    break;
                }
                }
                break;
            }
        }
    }
};
    

/*int main()
{
    int choose, MAXdepth;
    while (1) {
        cout << "____________________" << endl;
        cout << "Press 1 to play versus AI" << endl;
        cout << "Press 2 to exit" << endl;
        cout << "____________________" << endl;
        cin >> choose;
        while ((choose != 1) && (choose != 2)) {
            cout << "Invalid. Again: ";
            cin >> choose;
        }
        switch (choose) {
        case 1: {
            play();
            break;
        }
        case 2: exit(0);
        }
    }
    return 0;
}*/
