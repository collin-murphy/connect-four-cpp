#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;

//recieve input from user
int getRow()
{
    int input;
    cin >> input;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore();
    }

    while (input > 7 || input < 1)
    {
        cout << "Invalid input. Please enter a number bewteen 1 and 7: ";
        cin >> input;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
        }
    }
    return input;
}

//fills board
void fillBoard(vector<vector<int>> &board)
{
    board = {
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0}};
}

//displays game board
void displayBoard(vector<vector<int>> board)
{
    for (int i = board[0].size() - 1; i >= 0; i--)
    {
        cout << "|";
        for (int j = 0; j < board.size(); j++)
        {
            if (board[j][i] == 1)
                cout << "x|";
            else if (board[j][i] == 2)
                cout << "o|";
            else
                cout << " |";
        }
        cout << endl
             << "|-|-|-|-|-|-|-|" << endl;
    }

    cout << ""
            "|1|2|3|4|5|6|7|"
         << endl << endl;
}

void place(int input, vector<vector<int>> &board, int player)
{
    bool failed = 0;
    for (int i = 0; i < board[0].size(); i++)
    {
        if (board[input - 1][i] == 0)
        {
            board[input - 1][i] = player;
            break;
        }
        else if (i >= board[0].size() - 1)
        {
            failed = 1;
        }
    }
    if (failed == 1)
    {
        cout << "Invalid input. Column is full. Enter desired row: ";

        int secondTry = getRow();
        place(secondTry, board, player);
    }
}

bool outOfBounds(int i, int j, vector<vector<int>> board)
{
    if (i > board[0].size() || i < 0)
        return true;
    else if (j > board.size() || i < 0)
        return true;

    return false;
}

bool checkWin(vector<vector<int>> board, int player)
{
    int count = 0;
    //check for vertical wins
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            if (board[i][j] == player)
                count++;
            else
                count = 0;

            if (count == 4)
            {
                cout << "Game Over! Player " << player << " wins." << endl;
                return true;
            }
        }
    }
    count = 0;
    //check for horizontal wins
    for (int i = 0; i < board[0].size(); i++)
    {
        for (int j = 0; j < board.size(); j++)
        {
            if (board[j][i] == player)
                count++;
            else
                count = 0;

            if (count == 4)
            {
                cout << "Game Over! Player " << player << " wins." << endl;
                return true;
            }
        }
    }

    //check for left to right diagonal up wins
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            if (board[i][j] == player)
            {
                if (!outOfBounds(i - 3, j - 3, board) && board[i - 1][j - 1] == player)
                {
                    if (!outOfBounds(i - 3, j - 3, board) && board[i - 2][j - 2] == player)
                    {
                        if (!outOfBounds(i - 3, j - 3, board) && board[i - 3][j - 3] == player)
                        {
                            cout << "Game Over! Player " << player << " wins." << endl;
                            return true;
                        }
                    }
                }
            }
        }
    }

    //check for left to right diagonal down wins
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            if (board[i][j] == player)
            {
                if (!outOfBounds(i - 3, j + 3, board) && board[i - 1][j + 1] == player)
                {
                    if (!outOfBounds(i - 3, j + 3, board) && board[i - 2][j + 2] == player)
                    {
                        if (!outOfBounds(i - 3, j + 3, board) && board[i - 3][j + 3] == player)
                        {
                            cout << "Game Over! Player " << player << " wins." << endl;
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}
int menu()
{
    cout << "Press 1 to play again, press 2 to close: ";
    int input;
    cin >> input;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore();
    }

    while (input != 1 && input != 2)
    {
        cout << "Invalid input. Try again: ";
        cin >> input;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
        }
    }
    return input;
}

//run the program
int main()
{
    bool gameOver = 0;
    int input;
    int repeat;
    vector<vector<int>> board;
    fillBoard(board);

    displayBoard(board);
    while (gameOver == 0 || gameOver == false)
    {
        cout << "Player one (x) please enter desired row: ";
        input = getRow();
        place(input, board, 1);
        system("clear");
        displayBoard(board);
        gameOver = checkWin(board, 1);
        if (gameOver == 1)
            break;
        cout << "Player two (o) please enter desired row: ";
        input = getRow();
        place(input, board, 2);
        system("clear");
        displayBoard(board);
        gameOver = checkWin(board, 2);
    }
    repeat = menu();
    if (repeat == 1)
        main();
    else
        cout << "Thanks for playing!" << endl;
    return 0;
}
