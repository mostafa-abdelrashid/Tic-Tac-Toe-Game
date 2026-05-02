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
    Board(int size =3){
        //To Do
    }
    void display() const{
        //To Do
    }
    bool makeMove(int row , int col, char symbol){
        //To Do
    }
    bool isValidMove(int row , int col){
        //To Do
    }
    bool checkWin(char symbol){
        //To Do
    }
    bool isFull(){
        //To Do
    }
    char getCell(int row , int col) const{
        //To Do
    }
    void reset(){
        //To Do
    }
    int getSize() const{
        //To Do
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
        bool running = true;

        while (running) {
            board.display();

            if (isComputerTurn) {
                handleAIMove((AIPlayer*)currentPlayer);
            }
            else {
                handleHumanMove(currentPlayer);
            }

            if (board.checkWin(currentPlayer->getSymbol()) || board.isFull()) {
                displayResult();

                cout << "Play again? (y/n): ";
                char choice;
                cin >> choice;
                if (choice == 'y' || choice == 'Y') {
                    reset();
                }
                else {
                    running = false;
                    cout << "Goodbye!" << endl;
                }
            }
            else {
                switchPlayer();
            }
        }
    }


    void showMenu() {
        int choice;
        cout << "===== Tic Tac Toe =====\n";
        cout << "1. Player vs Player\n";
        cout << "2. Player vs Computer\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
            setupPvP();
        else
            setupPvC();
    }

    void setupPvP() {
       //TO DO
    }

    void setupPvC() {
        //TO DO
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
    }

    void checkGameEnd() {
        if (board.checkWin(player1->getSymbol())) {
            cout << player1->getName() << " wins!" << endl;
        }
        else if (board.checkWin(player2->getSymbol())) {
            cout << player2->getName() << " wins!" << endl;
        }
        else if (board.isFull()) {
            cout << "It's a draw!" << endl;
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
        cout << "\n--- Game Reset ---\n" << endl;
    }
};
int main(){
    Game ticTacToe;
    ticTacToe.start();
    return 0;
}