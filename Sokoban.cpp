#include <iostream>
#include <fstream>
#include <cctype>
#include <conio.h>
#include <iomanip>
#include <windows.h>
#include <vector>
#include <algorithm>

using namespace std;
#define AIR ' '
#define BOX 'O'
#define GOAL '+'
#define Wall '\xB2'
#define BOX_GOAL 'X'
#define Character  '\x01'

int getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

int getConsoleHeight() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}


char playerName[100];

class Sokoban {
private:
    int esc = 1;
    int choice;
    void clearScreen() {
        system("cls");
    }

public:	
	void setesc (int set)
	{
		esc = set;
	}
	int getchoice()
	{
		return choice;
	}
	int getesc()
	{
		return esc;
	}
	void PrintSokoban() {
		
	system("cls");
	//getchar();
	choice =0;
		
	std::string Beauty[] = {
	"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n",
	"\xB2   \xB2   \xB2\n",
	"\xB2   \xB2   \xB2\n",
	"\xB2   \xB2   \xB2\n",
	"\xB2SOKOBAN\xB2\n",
	"\xB2   \x01   \xB2\n",
	"\xB2   \xB2   \xB2\n",
	"\xB2   \xB2   \xB2\n",
	"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n"
	};
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
		int consoleWidth = getConsoleWidth();
    	int consoleHeight = getConsoleHeight();
    	// Calculate starting position for drawing the matrix to center it
    	int padding = (consoleWidth - 12) / 2;
    	int startX = (consoleWidth - 9) / 2;
    	int startY = (consoleHeight - 30) / 2;
    	// Draw the matrix with padding to center it
    	for (int i = 0; i < 9; ++i) {
        	// Set cursor position for current row
        	COORD coord;//cursor ki possition 
        	coord.X = startX;
        	coord.Y = startY + i;
        	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
			std::cout<<Beauty[i];	    
		}
		cout << "\n\n\n\n" << setw(padding - 35) << "" << "Welcome to SOKOBAN! A puzzle game that will test your logic and spatial reasoning skills." << setw(padding - 20) << "";
		cout << "\n" << setw(padding - 27) << "" << "The objective is to push all the boxes onto the targets to complete each level.";		
		cout << "\n\n\n\n\n - ENTER YOUR NAME: ";

        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        cin.getline(playerName, 100);
        
        esc++;
    }

	void records(int playermove) {
    system("CLS"); // Clear screen

   	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    int padding = (consoleWidth - 12) / 2;

    for (int i = 0; i < consoleWidth; i++) {
        cout << "=";
    }

    cout << "\n\n" << setw(padding) << "" << "GAME RECORDS" << setw(padding) << "";

    cout << "\n\n";
    for (int i = 0; i < consoleWidth; i++) {
        cout << "=";
    }
	   
	ifstream file("Sokoban.txt");
    vector<pair<int, string>> scores;
    // Read the existing scores from the file
    if (file) {
        string line;
        string currentName;
        int currentMoves;

        while (getline(file, line)) {
            if (line.find("Name: ") == 0) {
                currentName = line.substr(6);  // Extract the player name
            } else if (line.find("Moves: ") == 0) {
                currentMoves = stoi(line.substr(7));  // Extract the moves
                // Avoid adding the current player's score from the file
                if (currentName != playerName || currentMoves != playermove) {
                    scores.push_back(make_pair(currentMoves, currentName));
                }
            }
        }
        file.close();
    }
    // Add the current player's score
    scores.push_back({playermove, playerName});
    // Sort the scores by moves in ascending order
    sort(scores.begin(), scores.end());

    // Rewrite the file with sorted scores
    ofstream outfile("Sokoban.txt");
    for (const auto& score : scores) {
        outfile << "Name: " << score.second << "\n";
        outfile << "Moves: " << score.first << "\n";
    }
    outfile.close();

    // Display the sorted high scores
    for (auto& score : scores) {
        if(score.second=="" && score.first==0 )
   	 	continue;
   	 	
   	 	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
		cout << "\n - ";
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << score.second << " with ";
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
		cout << score.first ;
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << " moves." << endl;
    }
    
    
    while (esc != 1) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
        cout << "\n\n\n\n" << setw(padding - 20) << "" << "PRESS '1' TO RETURN TO MENU: ";
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        cin >> esc;
        if (esc != 1) {
            cout << "\n\n" << setw(padding) << "" << "INVALID CHOICE!!!" << setw(padding) << "";
        }
    }
    
    choice = 0;
	

    cin.ignore();
	}

	 void menu() {
        clearScreen();
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);

        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

        int padding = (consoleWidth - 12) / 2;

        for (int i = 0; i < consoleWidth; i++) {
            cout << "=";
        }

        cout << "\n\n" << setw(padding) << "" << "MAIN MENU\n\n";

        for (int i = 0; i < consoleWidth; i++) {
            cout << "=";
        }

        cout << "\n\n\n  1.";
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << "  START GAME";
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
        cout << "\n\n  2.";
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);  
		cout << "  RESTART GAME";
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
        cout << "\n\n  3.";
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);  
		cout << "  RECORDS";
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
        cout << "\n\n 4.";
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);  
		cout << "  QUIT GAME";
		    while (true) {
        try {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
            cout << "\n\n  - ENTER YOUR CHOICE (ONLY INTEGER): ";
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            cin >> choice;
            if (cin.fail()) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                throw invalid_argument("Invalid input. Please enter an integer.");
            }
            if (choice < 1 || choice > 4) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
                cout << "\n\n  \"INVALID CHOICE!!!\"";
            } else {
                break; // Exit loop if input is valid
            }
        } catch (const exception &e) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
            cout << "\n\n  " << e.what(); // Display error message
        }
    }
		

        if (choice == 1) {
        	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
            cout << "\n\n  - LOADING...";
            Sleep(2);
        } else if (choice == 2) {
        	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
            cout << "\n\n  - Rebooting...";
            Sleep(2);
        } else if (choice == 3) {
        	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
            cout << "\n\n  - Acessing Records...";
            Sleep(2);
        } else if (choice == 4) {
        	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
            cout << "\n\n  - Quitting...";
            Sleep(2);
        }

        esc++;
    }
    friend class Player;
    
    void instructions() {
        clearScreen();
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);

        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int padding = (consoleWidth - 12) / 2;

        for (int i = 0; i < consoleWidth; i++) {
            cout << "=";
        }

        cout << "\n\n" << setw(padding) << "" << "INSTRUCTIONS\n\n";

        for (int i = 0; i < consoleWidth; i++) {
            cout << "=";
        }

        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
        cout << "\n\n- Objective:\n";

        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        cout << "   Move the boxes represented by 'O' to their designated locations marked with a 'X'.\n";
        cout << "   Use the player character 'P' to push the boxes around the maze.\n";
        cout << "   Complete all 15 levels to finish the game.\n\n";

        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
        cout << "- Controls:\n";

        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        cout << "   Use keyboard keys to move the player character 'P'.\n";
        cout << "   Press 'W' to move up.\n";
        cout << "   Press 'A' to move left.\n";
        cout << "   Press 'S' to move down.\n";
        cout << "   Press 'D' to move right.\n\n";

        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
        cout << "\n\n - Now that you have the instructions, it's time to start playing the Sokoban game!\n";
        cout << "Good luck and have fun solving the puzzles!\n";

        cout << "\n\n\n - PRESS ANY KEY TO START THE GAME:";
        getch();
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
};
class Player {
    char icon = Character;
    char up = 'w';
    char down = 's';
    char left = 'a';
    char right = 'd';
    
	
	public:
	int playermove;
	
    void saveToFile();
	Player(){ playermove=0;} 
};
void Player::saveToFile() {
    ofstream file("Sokoban.txt", ios::app);
    file << "Name: " << playerName << endl;
    file << "Moves: " << playermove << endl;
    file.close();
}

// Define the Floor class
class Floor :public Player{
private:
    char **body;
    int sizeX;
    int sizeY;
    int posX;
    int posY;
    int currLevel;
	const char* levels[15];

public:
    Floor();
    ~Floor();
    bool isWin();
    void play();
    bool openFile();
    void rawToGood(const char* raw, const int length);
    void draw();
    void move(const signed y, const signed x);
    void end ()
	{
		system("cls");
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
		int consoleWidth = getConsoleWidth();
    	int consoleHeight = getConsoleHeight();
    	// Calculate starting position for drawing the matrix to center it
    	int padding = (consoleWidth - 12) / 2;
    	int startX = (consoleWidth - 9) / 2;
    	int startY = (consoleHeight - 30) / 2;
    	
    	cout << "\n\n\n\n\n\n\n\n\n";
    	
    	for (int i = 0; i < consoleWidth; i++) {
            cout << "=";
        }
    	
    	cout << "\n\n\n" << setw(padding - 27) << "" << "CONGRATULATIONS " << playerName << "! YOU HAVE SUCCESSFULLY COMPLETED ALL THE LEVELS." << setw(padding - 20) << "";
		cout << "\n\n" << setw(padding - 8) << "" << "THANK YOU FOR PLAYING\n\n\n";
		
		for (int i = 0; i < consoleWidth; i++) {
            cout << "=";
        }	
        
	}
};


// Constructor definition
Floor::Floor() {
    sizeX = 9; // Assuming the width of each row and column is constant
    sizeY = 9;  
    posX = 0;
    posY = 0;
     currLevel=0;
    // Dynamically allocate memory for the 2D array
    body = new char*[sizeY];
    for (int i = 0; i < sizeY; ++i) {
        body[i] = new char[sizeX+1];
    }

    // Populate the 2D array
	const char* intialLayout[]={
//Level 1
"  \xB2\xB2\xB2    \n"
"  \xB2+\xB2    \n"
"  \xB2O\xB2\xB2\xB2\xB2 \n"
"\xB2\xB2\xB2 \x01O+\xB2 \n"
"\xB2+O  \xB2\xB2\xB2 \n"
"\xB2\xB2\xB2\xB2O\xB2   \n"
"   \xB2+\xB2   \n"
"    \xB2    \n"
"         \n",

//Level 2
"\xB2\xB2\xB2\xB2\xB2    \n"
"\xB2   \xB2    \n"
"\xB2 O \xB2 \xB2\xB2\xB2\n"
"\xB2 O \xB2 \xB2+\xB2\n"
"\xB2\xB2\xB2 \xB2\xB2\xB2+\xB2\n"
" \xB2\xB2    +\xB2\n"
" \xB2  O\xB2  \xB2\n"
" \xB2  \x01\xB2\xB2\xB2\xB2\n"
" \xB2\xB2\xB2\xB2\xB2   \n",

//Level 3
" \xB2\xB2\xB2\xB2    \n"
"\xB2\xB2  \xB2    \n"
"\xB2 \x01O\xB2    \n"
"\xB2\xB2O \xB2\xB2   \n"
"\xB2\xB2 O\xB2\xB2   \n"
"\xB2+O  \xB2   \n"
"\xB2+++ \xB2   \n"
"\xB2\xB2\xB2\xB2\xB2\xB2   \n"
"         \n",

//Level 4
" \xB2\xB2\xB2\xB2    \n"
" \xB2\x01 \xB2\xB2\xB2  \n"
" \xB2 O  \xB2  \n"
"\xB2\xB2\xB2 \xB2 \xB2\xB2 \n"
"\xB2+\xB2 \xB2  \xB2 \n"
"\xB2+O  \xB2 \xB2 \n"
"\xB2+   O \xB2 \n"
"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 \n"
"         \n",

//Level 5

"  \xB2\xB2\xB2\xB2\xB2\xB2 \n"
"  \xB2    \xB2 \n"
"\xB2\xB2\xB2OOO \xB2 \n"
"\xB2\x01 O++ \xB2 \n"
"\xB2 O+++\xB2\xB2 \n"
"\xB2\xB2\xB2\xB2  \xB2  \n"
"   \xB2\xB2\xB2\xB2  \n"
"         \n"
"         \n",

//level 6
"  \xB2\xB2\xB2\xB2\xB2  \n"
"\xB2\xB2\xB2  \x01\xB2  \n"
"\xB2  O+ \xB2\xB2 \n"
"\xB2  +O+ \xB2 \n"
"\xB2\xB2\xB2 XO \xB2 \n"
"  \xB2   \xB2\xB2 \n"
"  \xB2\xB2\xB2\xB2\xB2  \n"
"         \n"
"         \n",
//level 7
"  \xB2\xB2\xB2\xB2   \n"
"  \xB2++\xB2   \n"
" \xB2\xB2 +\xB2\xB2  \n"
" \xB2  O+\xB2  \n"
"\xB2\xB2 O  \xB2\xB2 \n"
"\xB2  \xB2OO \xB2 \n"
"\xB2  \x01   \xB2 \n"
"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 \n"
"         \n",
//level 8
"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 \n"
"\xB2  \xB2   \xB2 \n"
"\xB2\x01O++O \xB2 \n"
"\xB2 O+X \xB2\xB2 \n"
"\xB2 O++O \xB2 \n"
"\xB2  \xB2   \xB2 \n"
"\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 \n"
"         \n"
"         \n",

//level 9
"\xB2\xB2\xB2\xB2\xB2\xB2   \n"
"\xB2    \xB2   \n"
"\xB2 OOO\xB2\xB2  \n"
"\xB2  \xB2++\xB2\xB2\xB2\n"
"\xB2\xB2  ++O \xB2\n"
" \xB2 \x01    \xB2\n"
" \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\n"
"         \n"
"         \n",

//level 10
"\xB2\xB2\xB2\xB2\xB2\xB2\xB2  \n"
"\xB2++O++\xB2  \n"
"\xB2++\xB2++\xB2  \n"
"\xB2 OOO \xB2  \n"
"\xB2  O  \xB2  \n"
"\xB2 OOO \xB2  \n"
"\xB2  \xB2\x01 \xB2  \n"
"\xB2\xB2\xB2\xB2\xB2\xB2\xB2  \n"
"         \n",

//level 11
" \xB2\xB2\xB2\xB2\xB2   \n"
" \xB2 \x01 \xB2\xB2\xB2 \n"
"\xB2\xB2 \xB2O  \xB2 \n"
"\xB2 X+ + \xB2 \n"
"\xB2  OO \xB2\xB2 \n"
"\xB2\xB2\xB2 \xB2O\xB2  \n"
"  \xB2   \xB2  \n"
"  \xB2\xB2\xB2\xB2\xB2  \n"
"         \n",
//level 12
"\xB2\xB2\xB2\xB2\xB2\xB2   \n"
"\xB2    \xB2   \n"
"\xB2 O \x01\xB2   \n"
"\xB2\xB2X  \xB2   \n"
"\xB2 X \xB2\xB2   \n"
"\xB2 X \xB2    \n"
"\xB2 X \xB2    \n"
"\xB2 + \xB2    \n"
"\xB2\xB2\xB2\xB2\xB2    \n",
//level 13
"  \xB2\xB2\xB2\xB2   \n"
"  \xB2  \xB2   \n"
"\xB2\xB2\xB2O \xB2\xB2  \n"
"\xB2  X \x01\xB2  \n"
"\xB2  X  \xB2  \n"
"\xB2  X \xB2\xB2  \n"
"\xB2\xB2\xB2X \xB2   \n"
"  \xB2+\xB2\xB2   \n"
"  \xB2\xB2\xB2    \n",
//level 14
"\xB2\xB2\xB2\xB2\xB2    \n"
"\xB2   \xB2\xB2\xB2\xB2\xB2\n"
"\xB2 \xB2 \xB2   \xB2\n"
"\xB2 O   O \xB2\n"
"\xB2++\xB2O\xB2O\xB2\xB2\n"
"\xB2+\x01O   \xB2 \n"
"\xB2++  \xB2\xB2\xB2 \n"
"\xB2\xB2\xB2\xB2\xB2\xB2   \n"
"         \n",
//level 15
" \xB2\xB2\xB2\xB2\xB2\xB2  \n"
" \xB2    \xB2\xB2 \n"
"\xB2\xB2+\xB2\xB2O \xB2 \n"
"\xB2 ++O  \xB2 \n"
"\xB2  \xB2O  \xB2 \n"
"\xB2  \x01 \xB2\xB2\xB2 \n"
"\xB2\xB2\xB2\xB2\xB2\xB2   \n"
"         \n"
"         \n"};


for (int i = 0; i < 15; ++i) {
        levels[i] = intialLayout[i];
    }

    rawToGood(levels[currLevel],(sizeX*sizeY)+sizeY);
}


// Destructor definition
Floor::~Floor() {
    for (int i = 0; i < sizeY; ++i)
        delete[] body[i];
    delete[] body;
}

// Method to play the game

void Floor::play() {
  char nav;
    while (currLevel < 2) {
		draw();
        nav = tolower(char(_getch()));

        if (nav == 'w') move(-1, 0);
        else if (nav == 's') move(1, 0);
        else if (nav == 'a') move(0, -1);
        else if (nav == 'd') move(0, 1);

        if (isWin()) {
        	draw();
            currLevel++;
            if (currLevel < 2) {
                rawToGood(levels[currLevel], (sizeX * sizeY) + sizeY);
            }
            else{
            	saveToFile();            	
            	end();
            	break;}
        }
    }
}
// Method to convert raw level data to a playable format
void Floor::rawToGood(const char* raw, const int length) {
 int index = 0;
    int line = 0, column = 0;
    for (int i = 0; i < length; i++) {
        if (raw[i] == '\n') {
            body[line][column] = '\0';  // null-terminate the string
            line++;
            column = 0;
        } else {
            body[line][column++] = raw[i];
            if (raw[i] == Character) {
                posY = line;
                posX = column - 1;
                body[line][column - 1] = AIR;
            }
        }
    }
}

bool Floor:: isWin() {
  // Iterate through the game board and count the number of boxes and goals
  int numGoal = 0;
  for (int y = 0; y < sizeY; ++y) {
    for (int x = 0; x < sizeX; ++x) {
      if (body[y][x] == GOAL) {
        numGoal++;
      }
      }
    }

  if(numGoal==0)
  return true;
  else
  return false;
}


void Floor::draw() {
    system("cls");


    // Get console width and height
    int consoleWidth = getConsoleWidth();
    int consoleHeight = getConsoleHeight();

    // Calculate starting position for drawing the matrix to center it
    int startX = (consoleWidth - sizeX) / 2;
    int startY = (consoleHeight - sizeY) / 2;
    //int padding = (consoleWidth - 50) / 2;
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
    
    
    cout << "\n\n\n" << setw((consoleWidth - 12)/2) << "" << " LEVEL: ";
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << currLevel+1 << " /15 \n\n";
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
    
    

    // Draw the matrix with padding to center it
    for (int i = 0; i < sizeY; ++i) {
        // Set cursor position for current row
        COORD coord;
        coord.X = startX;
        coord.Y = startY + i;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

	for (int j = 0; j < sizeX; ++j) {
    // Print the elements of the matrix
    char currentChar = body[i][j];
    if (i == posY && j == posX && (currentChar == AIR || currentChar == GOAL))
        std::cout << Character;
    else {
        if (currentChar == Wall) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
            std::cout << currentChar;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
        } else if (currentChar == BOX) {
            // Print the character for BOX
            std::cout << BOX;
        } else if (currentChar == BOX_GOAL) {
            // Print the character for BOX_GOAL
            std::cout << BOX_GOAL;
        } else {
            // Handle other characters if necessary
            std::cout << currentChar;
        }
    }
}
}
    
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
	cout << "\n\n\n" << " - PLAYER NAME: ";
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout << playerName;
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
    cout<< "\n\n" << " - Moves : ";
	
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	cout <<playermove;

}
// Method to handle Character movement

void Floor::move(const signed y, const signed x) {
	switch (body[posY + y][posX + x])
	{
	case AIR:
	caseAIR:
	case GOAL:
		posY += y;
		posX += x;
		playermove++;
		break;

	case BOX:
		if (body[posY + y + y][posX + x + x] == AIR)
		{
			body[posY + y][posX + x] = AIR;
			body[posY + y + y][posX + x + x] = BOX;
			goto caseAIR;
		playermove++;

		}
		else if (body[posY + y + y][posX + x + x] == GOAL)
		{
			body[posY + y][posX + x] = AIR;
			body[posY + y + y][posX + x + x] = BOX_GOAL;
			goto caseAIR;
			playermove++;

		}
		break;

	case BOX_GOAL:
		if (body[posY + y + y][posX + x + x] == AIR)
		{
			body[posY + y][posX + x] = GOAL;
			body[posY + y + y][posX + x + x] = BOX;
			goto caseAIR;
		playermove++;

		}
		if (body[posY + y + y][posX + x + x] == GOAL)
		{
			body[posY + y][posX + x] = GOAL;
			body[posY + y + y][posX + x + x] = BOX_GOAL;

			goto caseAIR;
		playermove++;

		}
		break;
		
	}

}
// Main function
int main() 
{
	getch();
	
	Sokoban game;
    Player pp;
	Floor map;

    
	while(game.getesc()==1)
	{
		game.PrintSokoban();
		while (game.getesc()==2)
		{
			if(game.getchoice()==0)
			{
			    game.menu();
			}
			if(game.getchoice()==1 && game.getesc()==3)
			{
				game.instructions();
    			map.play();
			}
			else if(game.getchoice()==2)
			{
				game.setesc(1);
				
			}
			else if (game.getchoice()==3)
			{
				game.records(pp.playermove);
				if(game.getesc()==1)
				{
					game.setesc(2);
				}
			}
			else if (game.getchoice()==4)
			{
				exit(0);
			}
		}
	}   
	exit(0);
    
    return 0;
}
