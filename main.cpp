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
        this->name = name;
        this->symbol = symbol;
    }

    virtual void getMove( int& row , int& col, const Board& board) = 0;
    string getName() const{
        return name;
    }
    char getSymbol() const{
        return symbol;
    }
    void setName(const string& name){
        this->name = name;
    }
    void setSymbol(char symbol){
        this->symbol = symbol;
    }
};

class HumanPlayer : public Player {
public:
   HumanPlayer(const string& name, char symbol)
    : Player(name, symbol) {}

   void getMove(int& row, int& col,const Board& board) override {
    cout << "Enter row and column (1-3): ";
    cin >> row >> col;

    row--; 
    col--;
}
};

class AIPlayer: public Player{
    private:
    enum Difficulty{EASY,HARD};
    Difficulty difficulty;

    public:
    AIPlayer(const string& name , char symbol , Difficulty difficulty ) : Player(name,symbol){
        this->difficulty = difficulty;
    }
    void getMove(int& row , int& col, const Board& board) override{
        if(difficulty == EASY) getRandomMove(row,col,board);
        else getBestMove(row,col,board);
    }
    void setDifficulty(Difficulty difficulty){
        this->difficulty = difficulty;
    }
    void getRandomMove(int& row , int& col, const Board& board){
        srand(time(0));
        do{
            row = rand() % board.getSize();
            col = rand() % board.getSize();
        }while(!board.isValidMove(row,col));
    }
    int minimax(Board tempBoard, bool isMaximizing){
        char aiSymbol = getSymbol();
        char oppSymbol = (aiSymbol == 'X') ? 'O' : 'X';

        if(tempBoard.checkWin(aiSymbol)) return 10;
        if(tempBoard.checkWin(oppSymbol)) return -10;
        if(tempBoard.isFull()) return 0;

        if(isMaximizing){
            int bestScore = INT_MIN;
            for(int i=0;i<tempBoard.getSize();i++){
                for(int j=0;j<tempBoard.getSize();j++){
                    if(tempBoard.isValidMove(i,j)){
                        Board nextBoard = tempBoard;
                        nextBoard.makeMove(i,j,aiSymbol);
                        int score = minimax(nextBoard, false);
                        if(score>bestScore){
                            bestScore = score;
                        }
                    }
                }
            }
            return bestScore;
        }
        else{
            int bestScore = INT_MAX;
            for(int i=0;i<tempBoard.getSize();i++){
                for(int j=0;j<tempBoard.getSize();j++){
                    if(tempBoard.isValidMove(i,j)){
                        Board nextBoard = tempBoard;
                        nextBoard.makeMove(i,j,oppSymbol);
                        int score = minimax(nextBoard, true);
                        if(score<bestScore){
                            bestScore = score;
                        }
                    }
                }
            }
            return bestScore;
        }
    }
    void getBestMove(int& row , int& col, const Board& board){
        char aiSymbol = getSymbol();
        int bestScore = INT_MIN;
        int bestRow = -1, bestCol = -1;
        for(int i=0;i<board.getSize();i++){
            for(int j=0;j<board.getSize();j++){
                if(board.isValidMove(i,j)){
                    Board temp = board;
                    temp.makeMove(i,j,aiSymbol);
                    int score = minimax(temp, false);
                    if(score>bestScore){
                        bestScore = score;
                        bestRow = i;
                        bestCol = j;
                    }
                }
            }
        }
        row = bestRow;
        col = bestCol;
    }
    int evaluateBoard(const Board& board) const{
        char aiSymbol = getSymbol();
        char oppSymbol = (aiSymbol == 'X') ? 'O' : 'X';
        if(board.checkWin(aiSymbol)) return 10;
        if(board.checkWin(oppSymbol)) return -10;
        return 0;
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
    player1 = nullptr;
    player2 = nullptr;
    currentPlayer = nullptr;
    isComputerTurn = false;
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


    void setupPvP(){
        string name1, name2;

    cout << "Enter Player 1 name: ";
    cin >> name1;

    cout << "Enter Player 2 name: ";
    cin >> name2;

    player1 = new HumanPlayer(name1, 'X');
    player2 = new HumanPlayer(name2, 'O');

    currentPlayer = player1;
    isComputerTurn = false;
    }

    void setupPvC(){
         string name;
    int choice;

    cout << "Enter your name: ";
    cin >> name;

    cout << "Choose difficulty:\n";
    cout << "1. Easy\n2. Hard\n";
    cin >> choice;

    AIPlayer::Difficulty diff =
        (choice == 1) ? AIPlayer::EASY : AIPlayer::HARD;

    player1 = new HumanPlayer(name, 'X');
    player2 = new AIPlayer("Computer", 'O', diff);

    currentPlayer = player1;
    isComputerTurn = false;
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
        player->getMove(row, col,board);
        while (!board.isValidMove(row, col)) {
            cout << "Invalid move, try again.\n";
            player->getMove(row, col,board);
        }
        board.makeMove(row, col, player->getSymbol());
    }

 

    void handleAIMove(AIPlayer* aiPlayer) {
        int row, col;
        cout << aiPlayer->getName() << " is thinking...\n";
        aiPlayer->getMove(row, col,board);
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
