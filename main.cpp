#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
using namespace std;

class Board{
    private:
    vector<vector<char>> grid;
    const int size;

    public:

    Board(int size = 3) : size(size) {
        grid.assign(size, vector<char>(size, ' '));
    }


    void display() const {
        cout << "\n  ";
        for (int c = 0; c < size; c++)
            cout << " " << c + 1;
        cout << "\n";

        for (int r = 0; r < size; r++) {
            cout << r + 1 << " ";
            for (int c = 0; c < size; c++) {
                cout << " " << grid[r][c];
                if (c < size - 1) cout << "|";
            }
            cout << "\n";
            if (r < size - 1) {
                cout << "  ";
                for (int c = 0; c < size; c++) {
                    cout << "---";
                    if (c < size - 1) cout << "+";
                }
                cout << "\n";
            }
        }
        cout << "\n";
    }


    bool makeMove(int row, int col, char symbol) {
        if (!isValidMove(row, col)) return false;
        grid[row][col] = symbol;
        return true;
    }


    bool isValidMove(int row, int col) {
        if (row < 0 || row >= size || col < 0 || col >= size)
            return false;
        return grid[row][col] == ' ';
    }


    bool checkWin(char symbol) {
        for (int i = 0; i < size; i++) {
            bool rowWin = true, colWin = true;
            for (int j = 0; j < size; j++) {
                if (grid[i][j] != symbol) rowWin = false;
                if (grid[j][i] != symbol) colWin = false;
            }
            if (rowWin || colWin) return true;
        }
        bool mainDiag = true;
        for (int i = 0; i < size; i++)
            if (grid[i][i] != symbol) { mainDiag = false; break; }
        if (mainDiag) return true;
        bool antiDiag = true;
        for (int i = 0; i < size; i++)
            if (grid[i][size - 1 - i] != symbol) { antiDiag = false; break; }
        return antiDiag;
    }


    bool isFull() {
        for (int r = 0; r < size; r++)
            for (int c = 0; c < size; c++)
                if (grid[r][c] == ' ') return false;
        return true;
    }


    char getCell(int row, int col) const {
        if (row < 0 || row >= size || col < 0 || col >= size)
            return '\0';
        return grid[row][col];
    }


    void reset() {
        for (int r = 0; r < size; r++)
            for (int c = 0; c < size; c++)
                grid[r][c] = ' ';
    }


    int getSize() const {
        return size;
    }
};

class Player{
    private:
    string name;
    char symbol;
    public:
    Player(const string& name , char symbol ){
        //To Do
    }
    virtual void getMove(int& row , int& col) = 0;
    string getName() const{
        //To Do
    }
    char getSymbol() const{
        //To Do
    }
    void setName(const string& name){
        //To Do
    }
    void setSymbol(char symbol){
        //To Do
    }
};

class HumanPlayer : public Player {
public:
    HumanPlayer(const string& name, char symbol) : Player(name, symbol) {
        //To Do
    }

    void getMove(int& row, int& col) override {
        //To Do
    }
};

class AIPlayer: public Player{
    public:
    enum Difficulty{EASY,HARD};
    Difficulty difficulty;

    public:
    AIPlayer(const string& name , char symbol , Difficulty difficulty ) : Player(name,symbol){
        //To Do
    }
    void getMove(int& row , int& col) override{
        //To Do
    }
    void setDifficulty(Difficulty difficulty){
        //To Do
    }
    void getRandomMove(int& row , int& col){
        //To Do
    }
    void getBestMove(int& row , int& col){
        //To Do
    }
    int evaluateBoard(const Board& board) const{
        //To Do
    }
};

class Game{

    private:

    Board board;
    Player* currentPlayer;
    Player* player1;
    Player* player2;
    bool isComputerTurn;


    public:

    Game() : board(3){
        //To Do
    }

    void start() {
        showMenu();
        while (!gameOver) {
            board.display();
            cout << currentPlayer->getName() << "'s turn (" << currentPlayer->getSymbol() << ")\n";
            if (isComputerTurn)
                handleAIMove((AIPlayer*)player2);
            else
                handleHumanMove(currentPlayer);
            checkGameEnd();
            if (!gameOver)
                switchPlayer();
        }
        displayResult();
        char again;
        cout << "Play again? (y/n): ";
        cin >> again;
        if (again == 'y' || again == 'Y') {
            reset();
            start();
        }
    }

    void showMenu(){
        //To Do
    }

    void setupPvP(){
        //To Do
    }

    void setupPvC(){
        //To Do
    }

    void switchPlayer() {
        if (currentPlayer == player1) {
            currentPlayer = player2;
            isComputerTurn = true;
        }
        else {
            currentPlayer = player1;
            isComputerTurn = false;
        }
    }

    void handleHumanMove(Player* player) {
        int row, col;
        player->getMove(row, col);
        while (!board.isValidMove(row, col)) {
            cout << "Invalid move, try again.\n";
            player->getMove(row, col);
        }
        board.makeMove(row, col, player->getSymbol());
    }

    void handleAIMove(AIPlayer* aiPlayer) {
        int row, col;
        cout << aiPlayer->getName() << " is thinking...\n";
        aiPlayer->getMove(row, col);
        board.makeMove(row, col, aiPlayer->getSymbol());
        cout << aiPlayer->getName() << " played at (" << row + 1 << ", " << col + 1 << ")\n";
    }

    void checkGameEnd() {
        if (board.checkWin(player1->getSymbol())) {
            gameOver = true;
        }
        else if (board.checkWin(player2->getSymbol())) {
            gameOver = true;
        }
        else if (board.isFull()) {
            gameOver = true;
        }
    }

    void displayResult() const {
        board.display();
        if (board.checkWin(player1->getSymbol()))
            cout << player1->getName() << " wins!\n";
        else if (board.checkWin(player2->getSymbol()))
            cout << player2->getName() << " wins!\n";
        else
            cout << "It's a draw!\n";
    }

    void reset() {
        board.reset();
        currentPlayer = player1;
        isComputerTurn = false;
        gameOver = false;
    }
};

int main(){
    Game ticTacToe;
    ticTacToe.start();
    return 0;
}
