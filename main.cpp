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
    void start(){
        //To Do
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
    void switchPlayer(){
        //To Do
    }
    void handleHumanMove(Player* player){
        //To Do
    }
    void handleAIMove(AIPlayer* aiPlayer){
        //To Do
    }
    void checkGameEnd(){
        //To Do
    }
    void displayResult() const{
        //To Do
    }
    void reset(){
        //To Do
    }
};
int main(){
    Game ticTacToe;
    ticTacToe.start();
    return 0;
}