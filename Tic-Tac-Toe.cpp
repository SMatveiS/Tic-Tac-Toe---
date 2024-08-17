#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const char X = 'X';
const char O = 'O';
const char TIE = 'T';
const char NO_ONE = 'N';
const char EMPTY = ' ';

void instructions();
char askYesNo(string question);
char player_figure();
char change_figure(char figure);
void displayBoard(const vector<char>& board);
int askNumber(string question, int low, int high);
char winner(const vector<char>& board);
void announceWinner(char win, char computer, char player);
int isLegal(const vector<char>& board, int move);
int playerMove(const vector<char>& board);
int computerMove(vector<char> board, char computer,char player);

int main(){
	instructions();
	char player, computer;
	player = player_figure();
	computer = change_figure(player);
	const int NUM_SQUARES = 9;
	vector<char> board(NUM_SQUARES, EMPTY);
	displayBoard(board);

	char move = X;
	while (winner(board) == NO_ONE) {
		if (move == player) 
			board[playerMove(board)] = player;
		else
			board[computerMove(board, computer, player)] = computer;
		displayBoard(board);
		move = change_figure(move);
	}

	announceWinner(winner(board), computer, player);
	
	return 0;
}

void instructions() {
	cout << "Welcome to the ultimate man-machine showdown: Tic-Tac-Toe.\n";
	cout << "--where human brain is pit against silicon processor.\n\n";
	cout << "Make your move known by entering a number 1-9. The number\n";
	cout << "corresponds to the desired board position, as illustrated:\n\n";
	cout << "  1 | 2 | 3\n";
	cout << " -----------\n";
	cout << "  4 | 5 | 6\n";
	cout << " -----------\n";
	cout << "  7 | 8 | 9\n\n";
	cout << "Prepare yourself, human. The battle is about to begin.\n\n";
}

char askYesNo(string question) {
	cout << question << " (y/n)\n";
	char answer;
	cin >> answer;
	while (answer != 'y' && answer != 'n') {
		cout << "\nPrint 'y' - yes, or 'n' - no: ";
		cin >> answer;
	}
	return answer;
}

char player_figure() {
	char answer = askYesNo("Do you require the first move?");
	if (answer == 'y') {
		cout << "\nThen take the first move. You will need it.\n";
		return X;
	}
	cout << "\nYour bravery will be your undoing...I will go first.\n";
	return O;
}

char change_figure(char figure) {
	if (figure == X)
		return O;
	return X;
}

void displayBoard(const vector<char>& board) {
	cout << "\n  " << board[0] << " | " << board[1] << " | " << board[2];
	cout << "\n -----------";
	cout << "\n  " << board[3] << " | " << board[4] << " | " << board[5];
	cout << "\n -----------";
	cout << "\n  " << board[6] << " | " << board[7] << " | " << board[8] << "\n\n";
}

int askNumber(string question, int low, int high) {
	int num;
	cout << question << " (" << low << "-" << high << ")\n";
	cin >> num;
	while (num < low || num > high) {
		cout << "Write a number between " << low << " and " << high << " or equal them.\n";
		cin >> num;
	}
	return num;
}

char winner(const vector<char>& board) {
	const int WINNING_ROWS[8][3] = { {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6} };
	for (int i = 0; i < 8; ++i) {
		if (board[WINNING_ROWS[i][0]] == board[WINNING_ROWS[i][1]] && board[WINNING_ROWS[i][0]] == board[WINNING_ROWS[i][2]] && board[WINNING_ROWS[i][0]] != EMPTY) {
			return board[WINNING_ROWS[i][0]];
		}
	}
	for (int i = 0; i < 8; ++i) {
		if (board[i] == EMPTY)
			return NO_ONE;
	}
	return TIE;
}

int isLegal(const vector<char>& board, int move) {
	return (board[move] == EMPTY);
}

int playerMove(const vector<char>& board) {
	int move = askNumber("Where will you move?", 1, 9);
	while (isLegal(board, move - 1) == 0) {
		cout << "\nThat square is already occupied, foolish human.\n";
		move = askNumber("Where will you move?", 1, 9);
	}
	return move - 1;
}

int computerMove(vector<char> board, char computer, char player) {
	for (int i = 0; i < 8; ++i) {
		if (isLegal(board, i)) {
			board[i] = computer;
			if (winner(board) == computer)
				return i;
			board[i] = EMPTY;
		}
	}
	for (int i = 0; i < 8; ++i) {
		if (isLegal(board, i)) {
			board[i] = player;
			if (winner(board) == player)
				return i;
			board[i] = EMPTY;
		}
	}
	const int BEST_MOVES[9] = {4, 0, 2, 6, 8, 1, 3, 5, 7};
	for (int i = 0; i < 9; ++i) {
		if (isLegal(board, BEST_MOVES[i]))
			return BEST_MOVES[i];
	}
}

void announceWinner(char win, char computer, char player) {
	if (win == computer) {
		cout << win << "'s won!\n";
		cout << "As I predicted, human. I am triumphant once more -- proof\n";
		cout << "that computers are superior to humans in all regards.\n";
	}
	else if (win == player) {
		cout << win << "'s won!\n";
		cout << "No, no! It can not be! Somehow you tricked me, human.\n";
		cout << "But never again! I, the computer, so swear it!\n";
	}
	else {
		cout << "It's a tie.\n";
		cout << "You were most lucky, human, and somehow managed to tie me.\n";
		cout << "Celebrate...for this is the best you will ever achive.\n";
	}
}