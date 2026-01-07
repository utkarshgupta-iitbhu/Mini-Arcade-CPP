#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <windows.h>

using namespace std;

struct PlayerScore
{
    string name;
    int score;
    int gamesPlayed;
    int wins;

    PlayerScore(const string &n = "", int s = 0, int gp = 1, int w = 0) : name(n), score(s), gamesPlayed(gp), wins(w) {}
};

bool compScores(PlayerScore a, PlayerScore b)
{
    if (a.score > b.score)
        return true;
    if (a.score < b.score)
        return false;
    if (a.wins > b.wins)
        return true;
    return false;
}

class ScoreManager
{
private:
    vector<PlayerScore> tttScores;
    vector<PlayerScore> ngScores;
    vector<PlayerScore> rpsScores;

    vector<PlayerScore> &getScoreVector(const string &gameName)
    {
        if (gameName == "TicTacToe")
            return tttScores;
        if (gameName == "NumberGuess")
            return ngScores;
        return rpsScores;
    }

    void sortScores(vector<PlayerScore> &scores)
    {
        sort(scores.begin(), scores.end(), compScores);
    }

public:
    void saveScore(const string &gameName, const string &playerName, int score, int wins = 1)
    {
        vector<PlayerScore> &scores = getScoreVector(gameName);

        bool flag = false;

        for (auto &it : scores)
        {
            if (it.name == playerName)
            {
                it.score += score;
                it.gamesPlayed++;
                it.wins++;

                flag = true;
                break;
            }
        }

        if (!flag)
        {
            scores.emplace_back(playerName, score, 1, wins);
        }

        sortScores(scores);
    }

    void displayScores(const string &title, const vector<PlayerScore> &scores) const
    {
        cout << "\n--- " << title << " ---\n";
        cout << left << setw(6) << "Rank" << setw(20) << "Player" << setw(10) << "Score" << setw(10) << "Games" << "Wins" << "\n";
        cout << string(56, '-') << "\n";

        if (scores.empty())
        {
            cout << "No scores yet!\n";
        }
        else
        {
            for (int i = 0; i < scores.size(); i++)
            {
                cout << left << setw(6) << (i + 1) << setw(20) << scores[i].name << setw(10) << scores[i].score << setw(10) << setw(10) << scores[i].gamesPlayed << setw(10) << scores[i].wins << "\n";
            }
        }
    }

    void showAllHighScores() const
    {
        system("cls");
        cout << "\n"
             << string(60, '=') << "\n";
        cout << "                    HIGH SCORES\n";
        cout << string(60, '=') << "\n";

        displayScores("TIC-TAC-TOE GAME", tttScores);
        displayScores("NUMBER GUESSING GAME", ngScores);
        displayScores("ROCK PAPER SCISSORS", rpsScores);

        cout << "\nPress Enter to return to menu...";
        cin.ignore();
        cin.get();
    }

    void resetAllScores()
    {
        tttScores.clear();
        ngScores.clear();
        rpsScores.clear();

        cout << "\nAll High Scores have been reset!\n";
        cout << "Press Enter to return to menu...\n";
        cin.ignore();
        cin.get();
    }
};

class TicTacToe
{
private:
    char board[9];
    string player1Name;
    string player2Name;
    bool vsComputer;
    int difficulty;

    void initialBoard()
    {
        for (int i = 0; i < 9; i++)
            board[i] = ' ';
    }

    void displayBoard() const
    {
        cout << "\n";
        for (int i = 0; i < 9; i++)
        {
            if (i % 3 == 0 && i != 0)
            {
                cout << "\n-----|-----|-----\n";
            }

            if (board[i] == 'X')
            {
                cout << "  X  ";
            }
            else if (board[i] == 'O')
            {
                cout << "  O  ";
            }
            else
            {
                cout << "  " << (i + 1) << "  ";
            }

            if ((i + 1) % 3 != 0)
                cout << "|";
        }
        cout << "\n\n";
    }

    bool checkWin(char mark) const
    {
        // Rows
        for (int i = 0; i < 9; i += 3)
        {
            if (board[i] == mark && board[i + 1] == mark && board[i + 2] == mark)
                return true;
        }

        // Columns
        for (int i = 0; i < 9; i++)
        {
            if (board[i] == mark && board[i + 3] == mark && board[i + 6] == mark)
                return true;
        }

        // Diagonals
        if (board[0] == mark && board[4] == mark && board[8] == mark)
            return true;
        if (board[2] == mark && board[4] == mark && board[6] == mark)
            return true;

        return false;
    }

    bool isBoardFull() const
    {
        for (int i = 0; i < 9; i++)
        {
            if (board[i] == ' ')
                return false;
        }
        return true;
    }

    int minimax(bool isMaximizing, int depth)
    {
        // Base case:
        if (checkWin('O'))
            return 10 - depth;
        if (checkWin('X'))
            return depth - 10;
        if (isBoardFull())
            return 0;

        if (isMaximizing)
        {
            int bestScore = -1000;

            for (int i = 0; i < 9; i++)
            {
                if (board[i] == ' ')
                {
                    board[i] = 'O';
                    int score = minimax(false, depth + 1);
                    board[i] = ' ';
                    bestScore = max(bestScore, score);
                }
            }
            return bestScore;
        }
        else
        {
            int bestScore = 1000;
            for (int i = 0; i < 9; i++)
            {
                if (board[i] == ' ')
                {
                    board[i] = 'X';
                    int score = minimax(true, depth + 1);
                    board[i] = ' ';
                    bestScore = min(bestScore, score);
                }
            }
            return bestScore;
        }
    }

    int getComputerMove()
    {
        if (difficulty == 1)
        {
            vector<int> emptySpots;
            for (int i = 0; i < 9; i++)
            {
                if (board[i] == ' ')
                    emptySpots.push_back(i);
            }
            return emptySpots[rand() % emptySpots.size()];
        }

        if (difficulty == 2)
        {
            int bestScore = -1000;
            int bestMove = -1;

            for (int i = 0; i < 9; i++)
            {
                if (board[i] == ' ')
                {
                    board[i] = 'O';
                    int score = minimax(false, 0);
                    board[i] = ' ';
                    if (score > bestScore)
                    {
                        bestScore = score;
                        bestMove = i;
                    }
                }
            }
            return bestMove;
        }
    }

public:
    void play(ScoreManager &scoreManager)
    {
        system("cls");
        initialBoard();

        cout << "\n"
             << string(50, '=') << "\n";
        cout << "              TIC TAC TOE\n";
        cout << string(50, '=') << "\n\n";

        cout << "Game Mode: \n";
        cout << "1. Player vs Player\n";
        cout << "2. Player vs Computer\n";
        cout << "Select Mode: ";
        int mode;
        cin >> mode;
        while (mode < 1 || mode > 2)
        {
            cout << "Invalid Input. Enter again: ";
            cin >> mode;
        }

        vsComputer = (mode == 2);

        if (vsComputer)
        {
            cout << "Enter your name (X): ";
            cin >> player1Name;

            player2Name = "Computer";

            cout << "\nDifficulty: \n";
            cout << "1. Easy (Score Multiplier: 1x)\n";
            cout << "2. Hard (Score Multiplier: 2x)\n";

            cout << "Select Difficulty: ";
            difficulty;
            cin >> difficulty;
            while (difficulty < 1 || difficulty > 2)
            {
                cout << "Invalid Input. Enter again: ";
                cin >> difficulty;
            }
        }
        else
        {
            cout << "Enter Player 1 (X) name: ";
            cin >> player1Name;
            cout << "Enter Player 2 (O) name: ";
            cin >> player2Name;
            difficulty = 1;
        }
        int currentPlayer = 0;
        bool gameOver = false;
        int moves = 0;
        int winner = -1;

        while (!gameOver)
        {
            system("cls");
            cout << "\n"
                 << string(50, '=') << "\n";
            cout << "              TIC TAC TOE\n";
            cout << string(50, '=') << "\n";
            cout << "\n"
                 << player1Name << " (X)  vs  " << player2Name << " (O)\n";

            displayBoard();

            int move;
            if (currentPlayer == 0 || !vsComputer)
            {
                cout << (currentPlayer == 0 ? player1Name : player2Name) << "'s turn. Enter your move (1-9): ";
                cin >> move;
                while (move < 1 || move > 9 || board[move - 1] != ' ')
                {
                    cout << "Invalid move. Enter again: ";
                    cin >> move;
                }
            }
            else
            {
                move = getComputerMove() + 1;
                cout << "Computer chooses position " << move << ".\n";
                Sleep(1000);
            }

            board[move - 1] = (currentPlayer == 0) ? 'X' : 'O';
            moves++;

            if (checkWin(board[move - 1]))
            {
                gameOver = true;
                winner = currentPlayer;
            }
            else if (isBoardFull())
            {
                gameOver = true;
                winner = 2;
            }
            else
            {
                currentPlayer = 1 - currentPlayer;
            }
        }
        system("cls");
        cout << "\n"
             << string(50, '=') << "\n";
        cout << "              GAME OVER!\n";
        cout << string(50, '=') << "\n";
        cout << "\n"
             << player1Name << " (X)  vs  " << player2Name << " (O)\n";
        displayBoard();

        int drawScore = 25;
        int winScore = 100;
        if (winner == 2)
        {
            cout << "It's a DRAW!\n";
            scoreManager.saveScore("TicTacToe", player1Name, drawScore, 0);
            if (!vsComputer)
            {
                scoreManager.saveScore("TicTacToe", player2Name, drawScore, 0);
            }
            cout << "Both players earn " << drawScore << " points.\n";
        }
        else
        {
            string winnerName = (winner == 0) ? player1Name : player2Name;
            string loserName = (winner == 0) ? player2Name : player1Name;

            cout << "*** " << winnerName << " WINS! ***\n";

            int totalScore = winScore * difficulty;

            cout << "Score breakdown:\n";
            cout << "  Base points: " << winScore << "\n";
            if (vsComputer && winner == 0)
            {
                cout << "  Difficulty multiplier: " << difficulty << "x\n";
            }
            cout << "Total: " << totalScore << " points!\n";

            scoreManager.saveScore("TicTacToe", winnerName, totalScore, 1);

            if (!vsComputer)
            {
                scoreManager.saveScore("TicTacToe", loserName, 10, 0);
            }
        }
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
};

class NumberGuessing
{
private:
    int secretNumber;
    string playerName;
    int maxAttempts;
    int difficulty;
    int maxNumber;

    void generateNumber()
    {
        secretNumber = rand() % maxNumber + 1;
    }

public:
    void play(ScoreManager &scoreManager)
    {
        system("cls");

        cout << "\n"
             << string(50, '=') << "\n";
        cout << "          NUMBER GUESSING GAME\n";
        cout << string(50, '=') << "\n\n";

        cout << "Enter your name: ";
        cin >> playerName;

        cout << "\nDifficulty:\n";
        cout << "1. Easy   (1-50,  10 attempts, 1x multiplier)\n";
        cout << "2. Medium (1-100, 10 attempts, 2x multiplier)\n";
        cout << "3. Hard   (1-200, 5 attempts,  3x multiplier)\n";
        cout << "4. Expert (1-500, 10 attempts, 5x multiplier)\n";
        cout << "Select difficulty: ";
        cin >> difficulty;
        while (difficulty < 1 || difficulty > 4)
        {
            cout << "Invalid input! Select difficulty: ";
            cin >> difficulty;
        }

        switch (difficulty)
        {
        case 1:
            maxNumber = 50;
            maxAttempts = 10;
            break;
        case 2:
            maxNumber = 100;
            maxAttempts = 10;
            break;
        case 3:
            maxNumber = 200;
            maxAttempts = 5;
            break;
        case 4:
            maxNumber = 500;
            maxAttempts = 10;
            break;
        }

        generateNumber();

        cout << "\nThe computer has chosen a number between 1 and " << maxNumber << ".\n";
        cout << "You have " << maxAttempts << " attempts to guess it!\n\n";

        int attempts = 0;
        bool won = false;
        vector<int> guessHistory;

        while (attempts < maxAttempts && !won)
        {
            attempts++;

            cout << "\n[Attempt " << attempts << "/" << maxAttempts << "] Enter your guess: ";
            int guess;
            cin >> guess;
            while (guess < 1 || guess > maxNumber)
            {
                cout << "Invalid input! Enter your guess: ";
                cin >> guess;
            }

            guessHistory.push_back(guess);

            if (guess == secretNumber)
            {
                won = true;
                cout << "\n*** CORRECT! ***\n";
            }
            else
            {
                if (!won)
                {
                    if (guess > secretNumber)
                    {
                        cout << "Try LOWER!\n";
                    }
                    else
                    {
                        cout << "Try HIGHER!\n";
                    }
                }
                cout << "Attempts remaining: " << (maxAttempts - attempts) << "\n";
            }
        }
        cout << "\n"
             << string(50, '=') << "\n";
        cout << "              GAME OVER!\n";
        cout << string(50, '=') << "\n";

        cout << "\nThe number was: " << secretNumber << "\n";
        cout << "Your guesses: ";
        for (int i = 0; i < guessHistory.size(); i++)
        {
            cout << guessHistory[i];
            if (i < guessHistory.size() - 1)
                cout << " -> ";
        }

        cout << "\n";

        if (won)
        {
            int baseScore = 100;
            int attemptBonus = (maxAttempts - attempts) * 20;
            int diffMultiplier = difficulty;
            int totalScore = (baseScore + attemptBonus) * diffMultiplier;

            cout << "\nCongratulations " << playerName << "! You found it in " << attempts << " attempt(s)!\n\n";
            cout << "Score breakdown:\n";
            cout << "  Base points: " << baseScore << "\n";
            cout << "  Attempt bonus: " << attemptBonus << " (" << (maxAttempts - attempts) << " attempts saved)\n";
            cout << "  Difficulty multiplier: " << diffMultiplier << "x\n";
            cout << "Total: " << totalScore << " points!\n";

            scoreManager.saveScore("NumberGuessing", playerName, totalScore, 1);
        }
        else
        {
            cout << "\nSorry " << playerName << ", you couldn't guess the number.\n";
            cout << "Score: 0 points\n";
            scoreManager.saveScore("NumberGuessing", playerName, 0, 0);
        }
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
};

class RockPaperScissors
{
private:
    string playerName;
    int playerScore = 0;
    int computerScore = 0;

    enum Choice
    {
        ROCK = 1,
        PAPER,
        SCISSORS
    };

    int determineWinner(int playerChoice, int computerChoice)
    {
        if (playerChoice == computerChoice)
            return 0; // Draw

        if ((playerChoice == 0 && computerChoice == 2) ||
            (playerChoice == 1 && computerChoice == 0) ||
            (playerChoice == 2 && computerChoice == 1))
        {
            return 1; // Player wins
        }

        return -1; // Computer wins
    }

    string choiceToString(int choice)
    {
        switch (choice)
        {
        case ROCK:
            return "Rock";
        case PAPER:
            return "Paper";
        case SCISSORS:
            return "Scissors";
        default:
            return "";
        }
    }

    string getWinDescription(int winner)
    {

        if (winner == ROCK)
            return "Rock crushes Scissors!";
        if (winner == PAPER)
            return "Paper covers Rock!";
        if (winner == SCISSORS)
            return "Scissors cuts Paper!";
        else
            return "";
    }

public:
    void play(ScoreManager &scoreManager)
    {
        system("cls");
        cout << "\n"
             << string(50, '=') << "\n";
        cout << "         ROCK PAPER SCISSORS\n";
        cout << string(50, '=') << "\n\n";

        cout << "Enter your name: ";
        cin >> playerName;

        cout << "\nWin Target:\n";
        cout << "1. First to 3 (Quick match)\n";
        cout << "2. First to 5 (Standard match)\n";
        cout << "3. First to 10 (Extended match)\n";
        cout << "Select target: ";
        int targetChoice;
        cin >> targetChoice;
        while (targetChoice < 1 || targetChoice > 3)
        {
            cout << "Invalid input! Select target: ";
            cin >> targetChoice;
        }

        int winTarget;

        switch (targetChoice)
        {
        case 1:
            winTarget = 3;
            break;
        case 2:
            winTarget = 5;
            break;
        case 3:
            winTarget = 10;
            break;
        }

        int round = 0;
        while (playerScore < winTarget && computerScore < winTarget)
        {
            round++;
            system("cls");
            cout << "\n"
                 << string(50, '=') << "\n";
            cout << "         ROCK PAPER SCISSORS\n";
            cout << string(50, '=') << "\n";

            cout << "\n--- Current Score ---\n";
            cout << playerName << ": " << playerScore << " | Computer: " << computerScore << "\n";

            cout << "\nChoices:\n";
            cout << "1. Rock\n2. Paper\n3. Scissors\n";
            cout << "Your choice: ";
            int playerChoice;
            cin >> playerChoice;
            while (playerChoice < 1 || playerChoice > 3)
            {
                cout << "Invalid input! Your choice: ";
                cin >> playerChoice;
            }

            int computerChoice = (rand() % 3) + 1;

            cout << "\n"
                 << playerName << " chose: " << choiceToString(playerChoice) << "\n";
            Sleep(500);
            cout << "Computer chose: " << choiceToString(computerChoice) << "\n";

            int result = determineWinner(playerChoice - 1, computerChoice - 1);

            if (result == 1)
            {
                cout << getWinDescription(playerChoice) << "\n";
                cout << "\n*** " << playerName << " WINS THIS ROUND! ***\n";
                playerScore++;
            }
            else if (result == -1)
            {
                cout << "\n*** COMPUTER WINS THIS ROUND! ***\n";
                computerScore++;
            }
            else
            {
                cout << "\n*** IT'S A DRAW! ***\n";
            }

            Sleep(1500);
        }

        system("cls");
        cout << "\n"
             << string(50, '=') << "\n";
        cout << "              GAME OVER!\n";
        cout << string(50, '=') << "\n";

        cout << "\nFinal Score: " << playerName << " " << playerScore
             << " - " << computerScore << " Computer\n";

        if (playerScore > computerScore)
        {
            cout << "\n*** Congratulations " << playerName << "! You WON! ***\n\n";

            int totalScore = playerScore * 20;

            cout << "  Score: " << totalScore << " points!\n";

            scoreManager.saveScore("RockPaperScissors", playerName, totalScore, 1);
        }
        else if (computerScore > playerScore)
        {
            cout << "\n*** Sorry " << playerName << ", you LOST. Better luck next time! ***\n\n";
            cout << "Score: 0 points\n";
            scoreManager.saveScore("RockPaperScissors", playerName, 0, 0);
        }
        else
        {
            cout << "\n*** It's a DRAW! ***\n\n";
            int consolation = playerScore * 5;
            cout << "Consolation points: " << consolation << "\n";
            scoreManager.saveScore("RockPaperScissors", playerName, consolation, 0);
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
};

int main()
{
    srand(time(0));
    ScoreManager scoreManager;
    RockPaperScissors rpsGame;
    TicTacToe tttGame;
    NumberGuessing ngGame;

    int choice = 0;

    while (choice != 6)
    {
        system("cls");
        cout << "  +----------------------------------+\n";
        cout << "  |     SELECT A GAME TO PLAY        |\n";
        cout << "  +----------------------------------+\n";
        cout << "  | 1. Rock-Paper-Scissors           |\n";
        cout << "  | 2. Tic-Tac-Toe                   |\n";
        cout << "  | 3. Number Guessing               |\n";
        cout << "  +----------------------------------+\n";
        cout << "  |     OTHER OPTIONS                |\n";
        cout << "  +----------------------------------+\n";
        cout << "  | 4. View High Scores              |\n";
        cout << "  | 5. Reset High Scores             |\n";
        cout << "  | 6. Exit                          |\n";
        cout << "  +----------------------------------+\n\n";

        cout << "  Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            rpsGame.play(scoreManager);
            break;
        case 2:
            tttGame.play(scoreManager);
            break;
        case 3:
            ngGame.play(scoreManager);
            break;
        case 4:
            scoreManager.showAllHighScores();
            break;
        case 5:
            scoreManager.resetAllScores();
            break;
        case 6:
            system("cls");
            cout << "\n"
                 << string(55, '=') << "\n";
            cout << "      Thanks for playing! Goodbye!\n";
            cout << string(55, '=') << "\n\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
            Sleep(1500);
            break;
        }
    }
}
