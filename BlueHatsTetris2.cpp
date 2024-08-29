#include <bits/stdc++.h>
#include <conio.h>  //Getch and Kbhit
#include <windows.h>//coloring and cursor position
#include <fstream>  //Working with files
#include <chrono>   //Timer and Durations
#include <time.h>   //using clocks and timers
#define KeyUp 72
#define KeyDown 80
#define KeyRight 75
#define KeyLeft 77
#define Space 32

using namespace std;

//ALL FUNCTIONS IN ORDER.......................................................................
//Main Menu Options
void MakeMenu();
void NewGame();
    void PlayGame();//Playing Process
void Instruction();
void LeaderBoard();

//Fix And Dispaying LeaderBoard
void displayLeaderboard();
void sortArray(int numberOfPlayers, int i);

//Dispaying GameTable
void MakeTable();
void BlockUpdate();
void RightUpdate();
void LeftUpdate();
void DownUpdate();
void UpdateGameTab();
void ShowNextBlock();
void ShowTime_Score(clock_t start, int d);

//Game Movements
void Clockwise();
void CounterClockwise();
void MoveDown();
    bool CheckDown();
void MoveRight();
    bool CheckRight();
void MoveLeft();
    bool CheckLeft();

//Scoring
void LineClearing(clock_t start);

//Pause Menu
void pauseMenu(clock_t start);

//When The Game Ends
bool CheckLosing();
void EndGame(clock_t start);

//Special Effects
void Continue();
void SandClock(int n);
void Tetris();
void GameOver();
//.............................................................................................

//Global Datas \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
struct Player
{
    string name;
    int score;
    int time;
    int lvl;
};
struct Blocks
{
    string isFull;
    int row;
    int column;
    int color;
};
vector <Player> player[5];
//Game Datas
Blocks block[25];
Blocks fallingBlock, nextBlock;
int height, width, GameTable[22][22], nextType, type;
//Player Datas
int score;
int difficulty;     //duration of blocks automatically falling
int duration;       //Game Duration
string ID;
char level;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
COORD p = {0, 0};
CONSOLE_CURSOR_INFO csrOn;//is used to hide the cursor
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    //Hides The Cursor
    GetConsoleCursorInfo(hConsole, &csrOn);
    csrOn.bVisible = false;
    SetConsoleCursorInfo(hConsole, &csrOn);
    //BLOCK number 1
    block[0].isFull = "100111000";
    //0
    //000
    block[1].isFull = "011010010";
    // 00
    // 0
    // 0
    block[2].isFull = "000111001";
    //000
    //  0
    block[3].isFull = "010010110";
    // 0
    // 0
    //00

    //BLOCK number 2
    block[4].isFull = "001111000";
    //  0
    //000
    block[5].isFull = "010010011";
    // 0
    // 0
    // 00
    block[6].isFull = "000111100";
    //000
    //0
    block[7].isFull = "110010010";
    //00
    // 0
    // 0

    //BLOCK number 3
    block[8].isFull = "011110000";
    // 00
    //00
    block[9].isFull = "010011001";
    // 0
    // 00
    //  0
    block[10].isFull = "000011110";
    // 00
    //00
    block[11].isFull = "100110010";
    //0
    //00
    // 0

    //BLOCK number 4
    block[12].isFull = "010111000";
    // 0
    //000
    block[13].isFull = "010011010";
    // 0
    // 00
    // 0
    block[14].isFull = "000111010";
    //000
    // 0
    block[15].isFull = "010110010";
    // 0
    //00
    // 0

    //BLOCK number 5
    block[16].isFull = "110011000";
    //00
    // 00
    block[17].isFull = "001011010";
    //  0
    // 00
    // 0
    block[18].isFull = "000110011";
    //00
    // 00
    block[19].isFull = "010110100";
    // 0
    //00
    //0

    //BLOCK number 6
    block[20].isFull = "0000111100000000";
    //
    //0000
    //
    //
    block[21].isFull = "0010001000100010";
    //  0
    //  0
    //  0
    //  0
    block[22].isFull = "0000000011110000";
    //
    //
    //0000
    //
    block[23].isFull = "0100010001000100";
    // 0
    // 0
    // 0
    // 0

    //BLOCK number 7
    block[24].isFull = "1111";
    //00
    //00
    Tetris();
    SetConsoleTextAttribute(hConsole, 15);
    MakeMenu();

    return 0;
}

//Managing menu Options=======================================================================
void MakeMenu()
{
    system("cls");
    cout << "\n                      ";
    cout << "\u250F";
    for (int k = 0; k < 30; k++)
        cout << "\u2501";
    cout << "\u2513\n";
    cout << "                      ";
    cout << "\u2503";
    cout << "             MENU             \u2503\n";
    cout << "                      ";
    cout << "\u2503   \u250F";
    for (int k = 0; k < 22; k++)
        cout << "\u2501";
        cout << "\u2513   \u2503\n";

    cout << "                      \u2503   \u2503 ";
    SetConsoleTextAttribute(hConsole, 240);
    cout << "     \u25BANEW GAME      ";
    SetConsoleTextAttribute(hConsole, 7);
    cout << " \u2503   \u2503\n";
    cout << "                      ";
    cout << "\u2503   \u2517";
    for (int k = 0; k < 22; k++)
        cout << "\u2501";
    cout << "\u251B   \u2503\n";
    cout << "                      ";
    cout << "\u2503   \u250F";
    for (int k = 0; k < 22; k++)
        cout << "\u2501";
    cout << "\u2513   \u2503\n";
    cout << "                      ";
    cout << "\u2503   \u2503       CONTINUE       \u2503   \u2503\n";
    cout << "                      ";
    cout << "\u2503   \u2517";
    for (int k = 0; k < 22; k++)
        cout << "\u2501";
    cout << "\u251B   \u2503\n";
    cout << "                      ";
    cout << "\u2503   \u250F";
    for (int k = 0; k < 22; k++)
        cout << "\u2501";
    cout << "\u2513   \u2503\n";
    cout << "                      ";
    cout << "\u2503   \u2503      HOW TO PLAY     \u2503   \u2503\n";
    cout << "                      ";
    cout << "\u2503   \u2517";
    for (int k = 0; k < 22; k++)
        cout << "\u2501";
    cout << "\u251B   \u2503\n";
    cout << "                      ";
    cout << "\u2503   \u250F";
    for (int k = 0; k < 22; k++)
        cout << "\u2501";
    cout << "\u2513   \u2503\n";
    cout << "                      ";
    cout << "\u2503   \u2503      LEADERBOARD     \u2503   \u2503\n";
    cout << "                      ";
    cout << "\u2503   \u2517";
    for (int k = 0; k < 22; k++)
        cout << "\u2501";
    cout << "\u251B   \u2503\n";
    cout << "                      ";
    cout << "\u2503   \u250F";
    for (int k = 0; k < 22; k++)
        cout << "\u2501";
    cout << "\u2513   \u2503\n";
    cout << "                      ";
    cout << "\u2503   \u2503         EXIT         \u2503   \u2503\n";
    cout << "                      ";
    cout << "\u2503   \u2517";
    for (int k = 0; k < 22; k++)
        cout << "\u2501";
    cout << "\u251B   \u2503\n";
    cout << "                      ";
    cout << "\u2517";
    for (int k = 0; k < 30; k++)
        cout << "\u2501";
    cout << "\u251B";
    int n = 0;
    int arrowPos = 0;
    while(1)
    {
        n = getch();
        if((n == KeyUp && arrowPos > 0) || (n == KeyDown && arrowPos < 4))
        {
            SetConsoleTextAttribute(hConsole, 7);
            p = {28, (short)((3*arrowPos) + 4)};
            SetConsoleCursorPosition(hConsole, p);
            switch (arrowPos)
            {
                case 0:
                    cout << "      NEW GAME      "; break;
                case 1:
                    cout << "      CONTINUE      "; break;
                case 2:
                    cout << "     HOW TO PLAY    "; break;
                case 3:
                    cout << "     LEADERBOARD    "; break;
                case 4:
                    cout << "        EXIT        "; break;
            }
            SetConsoleTextAttribute(hConsole, 240);
            (n == KeyDown)? arrowPos++: arrowPos--;
            p = {28, (short)((3*arrowPos) + 4)};
            SetConsoleCursorPosition(hConsole, p);
            switch (arrowPos)
            {
                case 0:
                    cout << "     \u25BANEW GAME      "; break;
                case 1:
                    cout << "     \u25BACONTINUE      "; break;
                case 2:
                    cout << "    \u25BAHOW TO PLAY    "; break;
                case 3:
                    cout << "    \u25BALEADERBOARD    "; break;
                case 4:
                    cout << "       \u25BAEXIT        "; break;
            }

        }
        else if(n == Space)
        {
            SetConsoleTextAttribute(hConsole, 7);
            switch(arrowPos)
            {
                case 0:
                    NewGame(); break;
                case 1:
                {
                    if(duration > 0)
                        Continue(); break;
                }
                case 2:
                    Instruction(); break;
                case 3:
                    LeaderBoard(); break;
                case 4:
                {
                    system("cls");
                    cout << "Thank You For Playing:)";
                    Tetris();
                }
            }
        }

    }
}

void NewGame()//Inputs Player Info
{
    //Shows The Cursor
    GetConsoleCursorInfo(hConsole, &csrOn);
    csrOn.bVisible = true;
    SetConsoleCursorInfo(hConsole, &csrOn);
    level = 0;
    score = 0;
    duration = 0;
    string mode;

    system("cls");
    cout << "Enter Your Player ID And Press Enter: ";
    cout << "\nChoose Your Level:\n";
    cout << "1-Easy\n";
    cout << "2-Medium\n";
    cout << "3-Hard\n";
    cout << "4-Extreme\n";
    cout << "\nEnter Table's Height And Width(Enter a Number Between 5 & 20): ";
    p = {38, 0};
    SetConsoleCursorPosition(hConsole, p);
    cin >> ID;
    p = {0, 6};
    SetConsoleCursorPosition(hConsole, p);
    while(level != '1' && level != '2' && level != '3' && level != '4')
    {
        level = getch();
        switch (level)
        {
            case '1':
                difficulty = 1000; mode = "Easy"; break;
            case '2':
                difficulty = 500; mode = "Medium"; break;
            case '3':
                difficulty = 250; mode = "Hard"; break;
            case '4':
                difficulty = 100; mode = "Extreme"; break;
        }
    }
    cout << mode << " Mode Selected.";
    p = {63, 7};
    SetConsoleCursorPosition(hConsole, p);
    cin >> height >> width;
    while(height < 5 || height > 20 || width < 5 || width > 20)
    {
        p = {63, 7};
        SetConsoleCursorPosition(hConsole, p);
        cout << "                 \n             ";
        SetConsoleCursorPosition(hConsole, p);
        cin >> height >> width;
    }
    for(int i = 0; i <= height + 1; i++)
    {
        for(int j = 0; j <= width + 1; j++)
        {
            if(i == 0 || i == height + 1 || j == 0 || j == width + 1)
                GameTable[i][j] = 16;
            else
                GameTable[i][j] = 0;
        }
    }
    //Generating Two Primary Blocks
    type = rand()%7;
    fallingBlock.isFull = block[type*4].isFull;
    fallingBlock.color = rand()%14 + 1;
    fallingBlock.row = 0;
    if(type < 5)
        fallingBlock.column = (width + 1)/2 - 1;
    else if(type == 5)
        fallingBlock.column = width/2 - 1;
    else
        fallingBlock.column = (width + 1)/2;
    char movement;
    //Checks if the next block is the same as falling block in shape and color
    nextType = rand()%6;
    if(nextType == type)
        nextType++;
    nextBlock.isFull = block[nextType*4].isFull;
    nextBlock.color = rand()%13 + 1;
    if(nextBlock.color == fallingBlock.color)
        nextBlock.color++;
    nextBlock.isFull = block[nextType*4].isFull;
    type *= 4;
    //Displaying The Primary Table^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    GetConsoleCursorInfo(hConsole, &csrOn);
    csrOn.bVisible = false;
    SetConsoleCursorInfo(hConsole, &csrOn);
    MakeTable();
    p = {static_cast<short> ((width + 3) * 2), 8};
    SetConsoleCursorPosition(hConsole, p);
    cout << "time: 0s";
    p = {static_cast<short>((width + 3)*2), 7};
    SetConsoleCursorPosition(hConsole, p);
    cout << "score: 0";
    PlayGame();
}

void PlayGame()//Playing Process
{
    clock_t start = clock();
    while(!CheckLosing())
    {
        BlockUpdate();
        ShowNextBlock();
        while(CheckDown())
        {
            for(int cnt = 0; cnt <= difficulty/16; cnt++)
            {
                ShowTime_Score(start, duration);
                if(_kbhit())
                {
                    switch (getch())
                    {//inputing movements
                        case 80:
                            MoveDown(); break;
                        case 75:
                            MoveLeft(); break;
                        case 77:
                            MoveRight(); break;
                        case 'a':
                            CounterClockwise(); break;
                        case 72:
                            Clockwise(); break;
                        case 's':
                            Clockwise(); break;
                        case ' ':
                            pauseMenu(start); break;
                    }
                }
                this_thread::sleep_for(10ms);
            }
            MoveDown();
        }
        UpdateGameTab();
        LineClearing(start);
        //Changing The NextBlock To A FallingBlock
        type = nextType;
        fallingBlock.isFull = block[type*4].isFull;
        fallingBlock.color = nextBlock.color;
        fallingBlock.row = 0;
        if(type < 5)
            fallingBlock.column = (width + 1)/2 - 1;
        else if(type == 5)
            fallingBlock.column = width/2 - 1;
        else
            fallingBlock.column = (width + 1)/2;
        //Prevents the Random Function To Generate The same Color and Type
        nextType = rand()%6;
        if(nextType == type)
            nextType++;
        type *= 4;
        nextBlock.isFull = block[nextType*4].isFull;
        nextBlock.color = rand()%13 + 1;
        if(nextBlock.color == fallingBlock.color)
            nextBlock.color++;
    }
    EndGame(start);
    return;
}

void Instruction()
{
    system("cls");
    cout << "\u250F";
    for (int k = 0; k < 61; k++)
        cout << "\u2501";
    cout << "\u2513\n\u2503";
    cout << "                       How To Play                           \u2503" << endl;
    cout << "\u2503";
    cout << " \u250F";
    for (int k = 0; k < 57; k++)
        cout << "\u2501";
    cout << "\u2513 \u2503\n\u2503 ";
    cout << "\u2503 Moves                                                   \u2503 \u2503" << endl;
    cout << "\u2503 \u2503 Press the right or left arrow key to move the falling   \u2503 \u2503\n\u2503 \u2503 Tetrimino in the corresponding direction.               \u2503 \u2503 \n\u2503 \u2517";
    for (int k = 0; k < 57; k++)
        cout << "\u2501";
    cout << "\u251B \u2503\n";
    cout << "\u2503";
    cout << " \u250F";
    for (int k = 0; k < 57; k++)
        cout << "\u2501";
    cout << "\u2513 \u2503\n\u2503 ";
    cout << "\u2503 Rotate                                                  \u2503 \u2503" << endl;
    cout << "\u2503 \u2503 The Tetrimino will rotate based on the pressed key      \u2503 \u2503\n\u2503 \u2503 (Up arrow and 's' key for clockwise and                 \u2503 \u2503\n\u2503 \u2503 'a' button for counterclockwise).                       \u2503 \u2503 \n\u2503 \u2517";
    for (int k = 0; k < 57; k++)
        cout << "\u2501";
    cout << "\u251B \u2503\n";
    cout << "\u2503";
    cout << " \u250F";
    for (int k = 0; k < 57; k++)
        cout << "\u2501";
    cout << "\u2513 \u2503\n\u2503 ";
    cout << "\u2503 Drop                                                    \u2503 \u2503" << endl;
    cout << "\u2503 \u2503 Press the down arow key to Hard Drop the Tetrimino      \u2503 \u2503\n\u2503 \u2503 into place.                                             \u2503 \u2503 \n\u2503 \u2517";
    for (int k = 0; k < 57; k++)
        cout << "\u2501";
    cout << "\u251B \u2503\n";
    cout << "\u2503";
    cout << " \u250F";
    for (int k = 0; k < 57; k++)
        cout << "\u2501";
    cout << "\u2513 \u2503\n\u2503 ";
    cout << "\u2503 Pause                                                   \u2503 \u2503" << endl;
    cout << "\u2503 \u2503 Press the \"space\" button to pause the game.             \u2503 \u2503 \n\u2503 \u2517";
    for (int k = 0; k < 57; k++)
        cout << "\u2501";
    cout << "\u251B \u2503\n";
    cout << "\u2517";
    for (int k = 0; k < 61; k++)
        cout << "\u2501";
    cout << "\u251B\n";
    cout << "Press any key to continue...";
    getch();
    system("cls");
    cout << "\u250F";
    for (int k = 0; k < 85; k++)
        cout << "\u2501";
    cout << "\u2513\n\u2503                               ";
    cout << "GENERAL GAMEPLAY INFO                                 \u2503" << endl;
    cout << "\u2503 GOAL: ";
    cout << "Clearing as many lines as possible.                                           \u2503" << endl;
    cout << "\u2503-CLEAR LINES: ";
    cout << "Maneuver the falling Tetriminos to fit them together within the Matrix \u2503\n\u2503 To clear a line,fill every square within a single row.                              \u2503" << endl;
    cout << "\u2503-SCORE POINTS: ";
    cout << "Earn points by clearing lines at once to increase your scoring        \u2503\n\u2503 opportunities.                                                                      \u2503" << endl;
    cout << "\u2503-NEXT QUEUE: ";
    cout << "Preview the upcoming Tetrimino in the next queue to plan ahead.         \u2503" << endl;
    cout << "\u2503-GAME OVER: ";
    cout << "Stack the Tetriminos too high and the game is over!                      \u2503\n\u2517";
    for (int k = 0; k < 85; k++)
        cout << "\u2501";
    cout << "\u251B\n";
    cout << "Press any key to continue...";
    getch();
    system("cls");
    cout << "\u250F";
    for (int k = 0; k < 27; k++)
        cout << "\u2501";
    cout << "\u2513\n";
    cout << "\u2503       SCORE VALUES        \u2503\n\u2523";
    for (int k = 0; k < 27; k++)
        cout << "\u2501";
    cout << "\u252B\n";
    cout << "\u2503 Single Line Clear     100 \u2503\n\u2523";
    for (int k = 0; k < 27; k++)
        cout << "\u2501";
    cout << "\u252B\n";
    cout << "\u2503 Double Line Clear     300 \u2503\n\u2523";
    for (int k = 0; k < 27; k++)
        cout << "\u2501";
    cout << "\u252B\n";
    cout << "\u2503 Triple Line Clear     500 \u2503\n\u2523";
    for (int k = 0; k < 27; k++)
        cout << "\u2501";
    cout << "\u252B\n";
    cout << "\u2503 Quadruple Line Clear  700 \u2503\n";
    cout << "\u2517";
    for (int k = 0; k < 27; k++)
        cout << "\u2501";
    cout << "\u251B\n";
    cout << "Press any key to continue...";
    _getch();
    MakeMenu();
}

void LeaderBoard()
{
    system("cls");
    ifstream File("leaderBoard.txt");
    Player plr;
    while (File >> plr.lvl >> plr.name >> plr.score >> plr.time) {
        player[plr.lvl].push_back(plr);
    }
    cout << "File Closed";
    File.close();
    for (int i = 1; i <= 4; i++) {
        for (int j = 0; j < player[i].size(); j++) {
            for (int k = j + 1; k < player[i].size(); k++) {
                if (player[i][j].name == player[i][k].name) {
                    if (player[i][j].score < player[i][k].score)
                        swap(player[i][j], player[i][k]);
                    if (player[i][j].score == player[i][k].score) {
                        if (player[i][j].time < player[i][k].time)
                            swap(player[i][j], player[i][k]);
                    }
                    player[i].erase(player[i].begin() + k, player[i].begin() + k + 1);
                    k--;
                }
            }
        }
    }
    cout << "NOrepeat";
    sortArray(player[1].size(),1);
    sortArray(player[2].size(),2);
    sortArray(player[3].size(),3);
    sortArray(player[4].size(),4);
    displayLeaderboard();

}
//=============================================================================================

//Fixing The LeaderBoard-----------------------------------------------------------------------
void displayLeaderboard()//Displays the leaderboard
{
    system("cls");
    for (int j = 1; j <= 4; j++) {
        cout << "\u250F";
        for (int k = 0; k < 40; k++) {
            cout << "\u2501";
        }
        cout << "\u2513\n";
        cout << "\u2503";
        cout << "                Level " << j << "                 ";
        cout << "\u2503\n";
        cout << "\u2523";
        for (int k = 0; k < 40; k++) {
            cout << "\u2501";
        }
        cout << "\u252B\n";
        cout << "\u2503 " << setw(17) << left  << "Name" << " \u2503 " << setw(9) << left << "Score" << "\u2503" << setw(8) << left << "Time" << " \u2503\n";
        if (player[j].size() == 0) {
            cout << "\u2517";
            for (int k = 0; k < 40; k++)
                cout << "\u2501";
            cout <<  "\u251B\n";
            continue;
        }
        cout << "\u2523";
        for (int j = 0; j < 40; j++) {
            cout << "\u2501";
        }
        cout << "\u252B\n";
        for (int x = 0; x < player[j].size(); x++) {
            cout << "\u2503 " << setw(17) << left  << player[j][x].name;
            cout << " \u2503 " << setw(9) << left << player[j][x].score;
            cout << "\u2503" << setw(8) << left << player[j][x].time << " \u2503\n";
            if (x != player[j].size() - 1) {
                cout << "\u2523";
                for (int j = 0; j < 40; j++) {
                    cout << "\u2501";
                }
                cout << "\u252B\n";
            }
        }
        cout << "\u2517";
        for (int k = 0; k < 40; k++) {
            cout << "\u2501";
        }
        cout << "\u251B\n";
    }
    cout << "Press Any Key To Continue...";
    _getch();
    MakeMenu();
}

void sortArray(int numberOfPlayers, int i)//Sorts the Player array
{
    for (int x = 0; x < numberOfPlayers - 1; x++) {
        for (int y = 0; y < numberOfPlayers-x-1; y++) {
            if (player[i][y].score < player[i][y + 1].score)
                    swap(player[i][y], player[i][y + 1]);
            else if (player[i][y].score == player[i][y + 1].score) {
                if (player[i][y].time > player[i][y+1].time)
                    swap(player[i][y], player[i][y + 1]);
            }
        }
    }
}
//---------------------------------------------------------------------------------------------

//Dispaying GameTable--------------------------------------------------------------------------
void MakeTable()
{
    system("cls");
    cout << "  ";
    for(int i = 0; i < 2*width; i++)
    {
        SetConsoleTextAttribute(hConsole, (i/2)%15 + 1);
        cout << ((i%2 == 0)? "\u25BA": "\u25C4");
        SetConsoleTextAttribute(hConsole, 15);
    }
    cout << "\n";
    for(int i = 1; i <= height; i++)
    {
        SetConsoleTextAttribute(hConsole, i%15+1);
        cout << " \u2573";
        for(int j = 1; j <= width; j++)
        {
            SetConsoleTextAttribute(hConsole, GameTable[i][j]*16);
            cout << "  ";
        }
        SetConsoleTextAttribute(hConsole, i%15+1);
        cout << "\u2573";
        cout << "\n";
    }
    SetConsoleTextAttribute(hConsole, 15);
    cout << "  ";
    for(int i = 0; i < 2*width; i++)
    {
        SetConsoleTextAttribute(hConsole, (i/2)%15+1);
        cout << ((i%2 == 0)? "\u25BA": "\u25C4");
    }
    cout << "\n";
    SetConsoleTextAttribute(hConsole, 15);
}

void BlockUpdate()//Update FallingBlock Position
{
    int d;
    if(type < 20)
        d = 3;
    else if(type < 24)
        d = 4;
    else
        d = 2;
    int row = fallingBlock.row, col = fallingBlock.column;
    for(int i = row; i < row + d; i++)
    {
        for(int j = col; j < col + d; j++)
        {
            p = {static_cast<short>(j * 2), static_cast<short>(i)};
            SetConsoleCursorPosition(hConsole, p);
            if(fallingBlock.isFull[(i - row)*d + j - col] == '1')
            {
                SetConsoleTextAttribute(hConsole, fallingBlock.color*16);
                cout << "  ";
            }
            else if(GameTable[i][j] != 16)
            {
                SetConsoleTextAttribute(hConsole, GameTable[i][j]*16);
                cout << "  ";
            }
        }
    }
    if(row == 0)
    {
        p = {0};
        SetConsoleCursorPosition(hConsole, p);
        cout << "  ";
        for(int i = 0; i < 2*width; i++)
        {
            SetConsoleTextAttribute(hConsole, (i/2)%15 + 1);
            cout << ((i%2 == 0)? "\u25BA": "\u25C4");
        }
    }
    SetConsoleTextAttribute(hConsole, 15);
}

void RightUpdate()
{
    int d;
    if(type < 20)
        d = 3;
    else if(type < 24)
        d = 4;
    else
        d = 2;
    int row = fallingBlock.row, col = fallingBlock.column;
    for(int i = row; i < row + d; i++)
    {
        if(GameTable[i][col - 1] != 16)
        {
            p = {static_cast<short>((col - 1) * 2), static_cast<short>(i)};
            SetConsoleCursorPosition(hConsole, p);
            SetConsoleTextAttribute(hConsole, GameTable[i][col - 1]* 16);
            cout << "  ";
        }
    }
    SetConsoleTextAttribute(hConsole, 15);
    BlockUpdate();
}

void LeftUpdate()
{
    int d;
    if(type < 20)
        d = 3;
    else if(type < 24)
        d = 4;
    else
        d = 2;
    int row = fallingBlock.row, col = fallingBlock.column;
    for(int i = fallingBlock.row; i < fallingBlock.row + d; i++)
    {
        if(GameTable[i][col + d] != 16)
        {
            p = {static_cast<short>((col + d) * 2), static_cast<short>(i)};
            SetConsoleCursorPosition(hConsole, p);
            SetConsoleTextAttribute(hConsole, GameTable[i][col+d]*16);
            cout << "  ";
        }
    }
    SetConsoleTextAttribute(hConsole, 15);
    BlockUpdate();
}

void DownUpdate()
{
    int d;
    if(type < 20)
        d = 3;
    else if(type < 24)
        d = 4;
    else
        d = 2;
    int row = fallingBlock.row, col = fallingBlock.column;
    p = {static_cast<short>(col * 2), static_cast<short>(row - 1)};
    SetConsoleCursorPosition(hConsole, p);
    for(int i = 0; i < d; i++)
    {
        if(GameTable[row - 1][col + i] != 16)
        {
            p = {static_cast<short>((col + i) * 2), static_cast<short>(row - 1)};
            SetConsoleCursorPosition(hConsole, p);
            SetConsoleTextAttribute(hConsole, GameTable[row - 1][col + i]*16);
            cout << "  ";
            SetConsoleTextAttribute(hConsole, 15);
        }
    }
    BlockUpdate();
}

void UpdateGameTab()//After A Block Reaches The Bottom Adds
                    //The Block To the GameTable and Displays it
{
    int d;
    if(type < 20)
        d = 3;
    else if(type < 24)
        d = 4;
    else
        d = 2;
    for(int i = fallingBlock.row; i < fallingBlock.row + d; i++)
    {
        for(int j = fallingBlock.column; j < fallingBlock.column + d; j++)
        {
            if(fallingBlock.isFull[(i - fallingBlock.row) * d + j - fallingBlock.column] == '1' && i <= height)
            {
                GameTable[i][j] = fallingBlock.color;
                p = {static_cast<short>(j * 2), static_cast<short>(i)};
                SetConsoleCursorPosition(hConsole, p);
                SetConsoleTextAttribute(hConsole, GameTable[i][j]*16);
                cout << "  ";
            }
        }
    }
    SetConsoleTextAttribute(hConsole, 15);
}

void ShowNextBlock()
{
    p = {static_cast<short>((width+3)*2), 1};
    SetConsoleCursorPosition(hConsole, p);
    SetConsoleTextAttribute(hConsole, 15);
    cout << "\u250F\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2513";
    p = {static_cast<short>((width+3)*2), 2};
    SetConsoleCursorPosition(hConsole, p);
    cout << "\u2503 NEXT:      \u2503";
    for (int i = 3; i <= 5; i++)
    {
        p = {static_cast<short>((width+3)*2), static_cast<short>(i)};
        SetConsoleCursorPosition(hConsole, p);
        cout << "\u2503            \u2503";
    }
    p = {static_cast<short>((width+3)*2), 6};
    SetConsoleCursorPosition(hConsole, p);
    cout << "\u2517\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u251B";
    int d;
    if(nextType < 5)
        d = 3;
    else if(nextType == 5)
        d = 4;
    else
        d = 2;
    int col = width + 5;
    for(int i = 4; i < 6; i++)
    {
        p = {static_cast<short>(col * 2), static_cast<short>(i)};
        SetConsoleCursorPosition(hConsole, p);
        for(int j = col; j < col + d; j++)
        {
            if(nextBlock.isFull[(i - 4)*d + j - col] == '1')
                SetConsoleTextAttribute(hConsole, nextBlock.color*16);
            else
                SetConsoleTextAttribute(hConsole, 15);
            cout << "  ";
            SetConsoleTextAttribute(hConsole, 15);
        }
    }
}

void ShowTime_Score(clock_t start, int d)
{
    SetConsoleTextAttribute(hConsole, 15);
    clock_t now = clock();
    p = {static_cast<short> ((width + 3) * 2), 8};
    SetConsoleCursorPosition(hConsole, p);
    cout << "time: " << d + ((int)now - (int)start)/CLOCKS_PER_SEC << "s";
    p = {static_cast<short>((width + 3)*2), 7};
    SetConsoleCursorPosition(hConsole, p);
    cout << "score: " << score;
}
//---------------------------------------------------------------------------------------------

//Movements 88888888888888888888888888888888888888888888888888888888888888888888888888888888888
void Clockwise()//Checks if The Block Can Rotate And Rotates It
{
    int t = (type%4 == 3)? type - 3: type + 1;
    int d;
    if(t < 20)
        d = 3;
    else if(t < 24)
        d = 4;
    else
        return;
    for(int i = fallingBlock.row; i < fallingBlock.row + d; i++)
    {
        int row = i - fallingBlock.row;
        for(int j = fallingBlock.column; j < fallingBlock.column + d; j++)
        {
            int column = j - fallingBlock.column;
            if(GameTable[i][j] > 0 && block[t].isFull[row*d + column] == '1')
                return;
        }
    }
    type = t;
    fallingBlock.isFull = block[type].isFull;
    BlockUpdate();
}

void CounterClockwise()//Checks if The Block Can Rotate And Rotates It
{
    int t = (type%4 == 0)? type + 3: type - 1;
    int d;
    if(t < 20)
        d = 3;
    else if(t < 24)
        d = 4;
    else
        return;
    for(int i = fallingBlock.row; i < fallingBlock.row + d; i++)
    {
        int row = i - fallingBlock.row;
        for(int j = fallingBlock.column; j < fallingBlock.column + d; j++)
        {
            int column = j - fallingBlock.column;
            if(GameTable[i][j] > 0 && block[t].isFull[row*d + column] == '1')
                return;
        }
    }
    type = t;
    fallingBlock.isFull = block[type].isFull;
    BlockUpdate();
}

void MoveDown()//Checks if The Block Can Move Down
{
    if(CheckDown())
    {
        fallingBlock.row++;
        DownUpdate();
    }
}

bool CheckDown()
{
    int d;
    if(type < 20)
        d = 3;
    else if(type < 24)
        d = 4;
    else
        d = 2;
    for(int i = fallingBlock.row; i < fallingBlock.row + d; i++)
    {
        int row = i - fallingBlock.row;
        for(int j = fallingBlock.column; j < fallingBlock.column + d; j++)
        {
            int column = j - fallingBlock.column;
            if(GameTable[i+1][j] > 0 && fallingBlock.isFull[row*d + column] == '1')
                return false;
        }
    }
    return true;
}

void MoveRight()
{
    if (CheckRight())
    {
        fallingBlock.column++;
        RightUpdate();
    }
}

bool CheckRight()//Checks if The Block Can Move to right
{
    int d;
    if(type < 20)
        d = 3;
    else if(type < 24)
        d = 4;
    else
        d = 2;
    for(int i = fallingBlock.row; i < fallingBlock.row + d; i++)
    {
        int row = i - fallingBlock.row;
        for(int j = fallingBlock.column; j < fallingBlock.column + d; j++)
        {
            int column = j - fallingBlock.column;
            if(GameTable[i][j+1] > 0 && fallingBlock.isFull[row*d + column] == '1')
                return false;
        }
    }
    return true;
}

void MoveLeft()
{
    if(CheckLeft())
    {
        fallingBlock.column--;
        LeftUpdate();
    }
}

bool CheckLeft()//Checks if The Block Can Move to Left
{
    int d;
    if(type < 20)
        d = 3;
    else if(type < 24)
        d = 4;
    else
        d = 2;
    for(int i = fallingBlock.row; i < fallingBlock.row + d; i++)
    {
        int row = i - fallingBlock.row;
        for(int j = fallingBlock.column; j < fallingBlock.column + d; j++)
        {
            int column = j - fallingBlock.column;
            if(GameTable[i][j-1] > 0 && fallingBlock.isFull[row*d + column] == '1')
                return false;
        }
    }
    return true;
}
//888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888888

//Deleting lines That Are Already Full><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
void LineClearing(clock_t start)
{
    int fullLine = 0, d;
    if(type < 20)
        d = 3;
    else if(type < 24)
        d = 4;
    else
        d = 2;
    for (int i = fallingBlock.row + d; i >= fallingBlock.row; i--) {
        bool isFull = true;
        if(i == height + 1 || i == 0)
            continue;
        for (int j = 1; j <= width; j++)
        {
            if (GameTable[i][j] == 0) {
                isFull = false;
                break;
            }
        }
        if (isFull) {
            for (int k = i; k > 1; k--) {
                for (int j = 1; j <= width; j++) {
                    GameTable[k][j] = GameTable[k-1][j];
                }
            }
            for (int k = 1; k <= width; k++)
                GameTable[1][k] = 0;
            fullLine++;
            p = {2, static_cast<short>(i)};
            SetConsoleCursorPosition(hConsole, p);
            for(int j = 1; j <= width; j++)
            {
                p = {(short)(j*2), static_cast<short>(i)};
                SetConsoleCursorPosition(hConsole, p);
                cout << "**";
                ShowTime_Score(start, duration);
                this_thread::sleep_for(50ms);
            }

            SetConsoleTextAttribute(hConsole, 15);
            MakeTable();
            ShowNextBlock();
            i++;
        }
    }
    switch(fullLine){
        case 1:
            score += 100;
            break;
        case 2:
            score += 300;
            break;
        case 3:
            score += 500;
            break;
        case 4:
            score += 700;
            break;
    }
}
// <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//Pause Menue<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
void pauseMenu(clock_t start)
{
    system("cls");
    clock_t timer = clock();
    duration += ((int)timer - (int)start)/CLOCKS_PER_SEC;
    cout << "\u250F";
    for (int k = 0; k < 30; k++)
        cout << "\u2501";
    cout << "\u2513\n\u2503";
    cout << "            PAUSED            \u2503\n";
    cout << "\u2503   \u250F";
    for (int k = 0; k < 22; k++)
        cout << "\u2501";
        cout << "\u2513   \u2503\n";
    cout << "\u2503   \u2503       CONTINUE       \u2503   \u2503\n";
    cout << "\u2503   \u2517";
    for (int k = 0; k < 22; k++)
        cout << "\u2501";
    cout << "\u251B   \u2503\n";
    cout << "\u2503   \u250F";
    for (int k = 0; k < 22; k++)
        cout << "\u2501";
        cout << "\u2513   \u2503\n";
        cout << "\u2503   \u2503        RESTART       \u2503   \u2503\n";
        cout << "\u2503   \u2517";
    for (int k = 0; k < 22; k++)
        cout << "\u2501";
    cout << "\u251B   \u2503\n";
    cout << "\u2503   \u250F";
    for (int k = 0; k < 22; k++)
        cout << "\u2501";
    cout << "\u2513   \u2503\n";
    cout << "\u2503   \u2503     SAVE & EXIT      \u2503   \u2503\n";
    cout << "\u2503   \u2517";
    for (int k = 0; k < 22; k++)
        cout << "\u2501";
    cout << "\u251B   \u2503\n";
    cout << "\u2517";
    for (int k = 0; k < 30; k++)
        cout << "\u2501";
    cout << "\u251B";
    while(1)
    {
        switch(getch())
        {
            case '1':
                Continue(); break;
            case '2':
                SandClock(9); NewGame(); break;
            case '3':
                SandClock(9); MakeMenu();
        }

    }
}

// <><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>

//When The Game Ends***************************************************************************
bool CheckLosing()
{
    for(int i = 1; i <= width; i++)
    {
        if(GameTable[1][i] > 0 && GameTable[1][i] < 16)
            return 1;
    }
    return 0;
}

void EndGame(clock_t start)
{
    clock_t t = clock();
    ofstream File("LeaderBoard.txt", ios::app);
    File << level << " " << ID << " " << score << " " << duration + ((int)t - (int)start)/CLOCKS_PER_SEC << "\n";
    File.close();
    p = {0, 9};
    SetConsoleCursorPosition(hConsole, p);
    GameOver();
    SetConsoleTextAttribute(hConsole, 7);
    _getch();
    SandClock(9);
    MakeMenu();
}

//*********************************************************************************************

//Special Effects------------------------------------------------------------------------------
void Continue()//Shows A CountDown From 3 And Displays The Game
{
    system("cls");
    cout << "READY...\n";
    cout << "       \u250F\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2513\n";
    cout << "       \u2517\u2501\u2501\u2501\u2501\u2501\u2513 \u2503\n";
    cout << "             \u2503 \u2503\n";
    cout << "        \u250F\u2501\u2501\u2501\u2501\u251B \u2503\n";
    cout << "        \u2517\u2501\u2501\u2501\u2501\u2513 \u2503\n";
    cout << "             \u2503 \u2503\n";
    cout << "       \u250F\u2501\u2501\u2501\u2501\u2501\u251B \u2503\n";
    cout << "       \u2517\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u251B\n";
    this_thread::sleep_for(1000ms);
    system("cls");
    cout << "READY...\n";
    cout << "       \u250F\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u2513\n";
    cout << "       \u2517\u2501\u2501\u2501\u2501\u2501\u2513 \u2503\n";
    cout << "             \u2503 \u2503\n";
    cout << "       \u250F\u2501\u2501\u2501\u2501\u2501\u251B \u2503\n";
    cout << "       \u2503 \u250F\u2501\u2501\u2501\u2501\u2501\u251B\n";
    cout << "       \u2503 \u2503\n";
    cout << "       \u2503 \u2517\u2501\u2501\u2501\u2501\u2501\u2513\n";
    cout << "       \u2517\u2501\u2501\u2501\u2501\u2501\u2501\u2501\u251B";
    this_thread::sleep_for(1000ms);
    system("cls");
    cout << "READY...\n";
    cout << "          \u250F\u2501\u2513\n";
    cout << "          \u2503 \u2503\n";
    cout << "          \u2503 \u2503\n";
    cout << "          \u2503 \u2503\n";
    cout << "          \u2503 \u2503\n";
    cout << "          \u2503 \u2503\n";
    cout << "          \u2503 \u2503\n";
    cout << "          \u2517\u2501\u251B\n";
    this_thread::sleep_for(1000ms);
    system("cls");
    MakeTable();
    PlayGame();
}

void SandClock(int n)//Shows a Sandclock Before Entering The Menu
{
    system("cls");
    cout << "Processing Your Data...\n";
    COORD p = {0, 1};
    int sand = n/2 - 1;
    for(int i = 0; i <= sand; i++)
    {
        if(i > 0)
            this_thread::sleep_for(chrono::milliseconds(800));
        SetConsoleCursorPosition(hConsole, p);
        cout << "\n   ";
        for(int j = 0; j < n; j++)
            cout << "*";
        cout << "\n   ";
        for(int j = 0; j < n; j++)
            cout << "*";
        cout << "\n";
        for(int j = 0; j < sand; j++)
        {
            for(int k = 0; k <= j + 3; k++)
                cout << " ";
            cout << "*";
            if(j < i)
                for(int k = (sand-j)*2 - 1; k > 0; k--)
                    cout << " ";
            else
                for(int k = (sand-j)*2 - 1; k > 0; k--)
                    cout << ".";
            cout << "*\n";
        }
        for(int j = 0; j <= sand + 3; j++)
            cout << " ";
        cout << "*\n";
        for(int j = sand - 1; j >= 0; j--)
        {
            for(int k = 0; k <= j + 3; k++)
                cout << " ";
            cout << "*";
            if(j >= i)
                for(int k = (sand-j)*2 - 1; k > 0; k--)
                    cout << " ";
            else
                for(int k = (sand - j)*2 - 1; k > 0; k--)
                    cout << ".";
            cout << "*\n";
        }
        cout << "   ";
        for(int j = 0; j < n; j++)
            cout << "*";
        cout << "\n   ";
        for(int j = 0; j < n; j++)
            cout << "*";
    }
}

void Tetris()
{
    SetConsoleTextAttribute(hConsole, 1);//T1---------------------
    cout << "\n\n   \u250F";
    for(int i = 0; i < 11; i++)
        cout << "\u2501";
    cout << "\u2513";
    SetConsoleTextAttribute(hConsole, 2);//E1
    cout << "\u250F";
    for(int i = 0; i < 11; i++)
        cout << "\u2501";
    cout << "\u2513";
    SetConsoleTextAttribute(hConsole, 4);//T1
    cout << "\u250F";
    for(int i = 0; i < 11; i++)
        cout << "\u2501";
    cout << "\u2513";
    SetConsoleTextAttribute(hConsole, 5);//R1
    cout << "\u250F";
    for(int i = 0; i < 11; i++)
        cout << "\u2501";
    cout << "\u2513";
    SetConsoleTextAttribute(hConsole, 7);//I1
    cout << "\u250F\u2501\u2501\u2501\u2513";
    SetConsoleTextAttribute(hConsole, 6);//S1
    cout << "\u250F";
    for(int i = 0; i < 10; i++)
        cout << "\u2501";
    cout << "\u2513";
    SetConsoleTextAttribute(hConsole, 1);//T2---------------------
    cout << "\n   \u2503";
    for(int i = 0; i < 11; i++)
        cout << " ";
    cout << "\u2503";
    SetConsoleTextAttribute(hConsole, 2);//E2
    cout << "\u2503";
    for(int i = 0; i < 11; i++)
        cout << " ";
    cout << "\u2503";
    SetConsoleTextAttribute(hConsole, 4);//T2
    cout << "\u2503";
    for(int i = 0; i < 11; i++)
        cout << " ";
    cout << "\u2503";
    SetConsoleTextAttribute(hConsole, 5);//R2
    cout << "\u2503";
    for(int i = 0; i < 11; i++)
        cout << " ";
    cout << "\u2503";
    SetConsoleTextAttribute(hConsole, 7);//I2
    cout << "\u2503   \u2503";
    SetConsoleTextAttribute(hConsole, 6);//S2
    cout << "\u2503";
    for(int i = 0; i < 10; i++)
        cout << " ";
    cout << "\u2503";
    SetConsoleTextAttribute(hConsole, 1);//T3---------------------
    cout << "\n   \u2517\u2501\u2501\u2501\u2513   \u250F\u2501\u2501\u2501\u251B";
    SetConsoleTextAttribute(hConsole, 2);//E3
    cout << "\u2503    \u250F";
    for(int i = 0; i < 6; i++)
        cout << "\u2501";
    cout << "\u251B";
    SetConsoleTextAttribute(hConsole, 4);//T3
    cout << "\u2517\u2501\u2501\u2501\u2513   \u250F\u2501\u2501\u2501\u251B";
    SetConsoleTextAttribute(hConsole, 5);//R3
    cout << "\u2503";
    cout << "   \u250F\u2501\u2501\u2501\u2513   \u2503";
    SetConsoleTextAttribute(hConsole, 7);//I3
    cout << "\u2503   \u2503";
    SetConsoleTextAttribute(hConsole, 6);//S3
    cout << "\u2503   \u250F\u2501\u2501\u2501\u2501\u2501\u2501\u251B";
    SetConsoleTextAttribute(hConsole, 1);//T4---------------------
    cout << "\n       \u2503   \u2503    ";
    SetConsoleTextAttribute(hConsole, 2);//E4
    cout << "\u2503    \u2503";
    for(int i = 0; i < 7; i++)
        cout << " ";
    SetConsoleTextAttribute(hConsole, 4);//T4
    cout << "    \u2503   \u2503    ";
    SetConsoleTextAttribute(hConsole, 5);//R4
    cout << "\u2503";
    cout << "   \u2517\u2501\u2501\u2501\u251B   \u2503";
    SetConsoleTextAttribute(hConsole, 7);//I4
    cout << "\u2503   \u2503";
    SetConsoleTextAttribute(hConsole, 6);//S4
    cout << "\u2503   \u2503";
    for(int i = 0; i < 7; i++)
        cout << " ";
    SetConsoleTextAttribute(hConsole, 1);//T5---------------------
    cout << "\n       \u2503   \u2503    ";
    SetConsoleTextAttribute(hConsole, 2);//E5
    cout << "\u2503    \u2517";
    for(int i = 0; i < 5; i++)
        cout << "\u2501";
    cout << "\u2513 ";
    SetConsoleTextAttribute(hConsole, 4);//T5
    cout << "    \u2503   \u2503    ";
    SetConsoleTextAttribute(hConsole, 5);//R5
    cout << "\u2503   \u250F\u2501\u2501\u2513   \u250F\u251B";
    SetConsoleTextAttribute(hConsole, 7);//I5
    cout << "\u2503   \u2503";
    SetConsoleTextAttribute(hConsole, 6);//S5
    cout << "\u2503   \u2517";
    for(int i = 0; i < 6; i++)
        cout << "\u2501";
    cout << "\u2513";
    SetConsoleTextAttribute(hConsole, 1);//T6---------------------
    cout << "\n       \u2503   \u2503    ";
    SetConsoleTextAttribute(hConsole, 2);//E6
    cout << "\u2503    \u250F";
    for(int i = 0; i < 5; i++)
        cout << "\u2501";
    cout << "\u251B ";
    SetConsoleTextAttribute(hConsole, 4);//T6
    cout << "    \u2503   \u2503    ";
    SetConsoleTextAttribute(hConsole, 5);//R6
    cout << "\u2503   \u2503  \u2517\u2513  \u2517\u2513";
    SetConsoleTextAttribute(hConsole, 7);//I6
    cout << "\u2503   \u2503";
    SetConsoleTextAttribute(hConsole, 6);//S6
    cout << "\u2517";
    for(int i = 0; i < 6; i++)
        cout << "\u2501";
    cout << "\u2513   \u2503";
    SetConsoleTextAttribute(hConsole, 1);//T7---------------------
    cout << "\n       \u2503   \u2503    ";
    SetConsoleTextAttribute(hConsole, 2);//E7
    cout << "\u2503    \u2503";
    for(int i = 0; i < 7; i++)
        cout << " ";
    SetConsoleTextAttribute(hConsole, 4);//T7
    cout << "    \u2503   \u2503    ";
    SetConsoleTextAttribute(hConsole, 5);//R7
    cout << "\u2503   \u2503   \u2517\u2513  \u2503";
    SetConsoleTextAttribute(hConsole, 7);//I7
    cout << "\u2503   \u2503";
    SetConsoleTextAttribute(hConsole, 6);//S7
    for(int i = 0; i < 7; i++)
        cout << " ";
    cout << "\u2503   \u2503";
    SetConsoleTextAttribute(hConsole, 1);//T8---------------------
    cout << "\n       \u2503   \u2503    ";
    SetConsoleTextAttribute(hConsole, 2);//E8
    cout << "\u2503    \u2517";
    for(int i = 0; i < 6; i++)
        cout << "\u2501";
    cout << "\u2513";
    SetConsoleTextAttribute(hConsole, 4);//T8
    cout << "    \u2503   \u2503    ";
    SetConsoleTextAttribute(hConsole, 5);//R8
    cout << "\u2503   \u2503    \u2503  \u2503";
    SetConsoleTextAttribute(hConsole, 7);//I8
    cout << "\u2503   \u2503";
    SetConsoleTextAttribute(hConsole, 6);//S8
    cout << "\u250F";
    for(int i = 0; i < 6; i++)
        cout << "\u2501";
    cout << "\u251B   \u2503";
    SetConsoleTextAttribute(hConsole, 1);//T9---------------------
    cout << "\n       \u2503   \u2503    ";
    SetConsoleTextAttribute(hConsole, 2);//E9
    cout << "\u2503";
    for(int i = 0; i < 11; i++)
        cout << " ";
    cout << "\u2503";
    SetConsoleTextAttribute(hConsole, 4);//T9
    cout << "    \u2503   \u2503    ";
    SetConsoleTextAttribute(hConsole, 5);//R9
    cout << "\u2503   \u2503    \u2503  \u2503";
    SetConsoleTextAttribute(hConsole, 7);//I9
    cout << "\u2503   \u2503";
    SetConsoleTextAttribute(hConsole, 6);//S9
    cout << "\u2503";
    for(int i = 0; i < 10; i++)
        cout << " ";
    cout << "\u2503";
    SetConsoleTextAttribute(hConsole, 1);//T10---------------------
    cout << "\n       \u2517\u2501\u2501\u2501\u251B    ";
    SetConsoleTextAttribute(hConsole, 2);//E10
    cout << "\u2517";
    for(int i = 0; i < 11; i++)
        cout << "\u2501";
    cout << "\u251B";
    SetConsoleTextAttribute(hConsole, 4);//T10
    cout << "    \u2517\u2501\u2501\u2501\u251B    ";
    SetConsoleTextAttribute(hConsole, 5);//R10
    cout << "\u2517\u2501\u2501\u2501\u251B    \u2517\u2501\u2501\u251B";
    SetConsoleTextAttribute(hConsole, 7);//I10
    cout << "\u2517\u2501\u2501\u2501\u251B";
    SetConsoleTextAttribute(hConsole, 6);//S10
    cout << "\u2517";
    for(int i = 0; i < 10; i++)
        cout << "\u2501";
    cout << "\u251B\n";

    SetConsoleTextAttribute(hConsole, 1);
    cout << "        MADE BY BlueHats";

    this_thread::sleep_for(3s);
}

void GameOver()
{
    SetConsoleTextAttribute(hConsole, 4);
    cout << "\u250F";
    for(int i = 0; i < 39; i++)
        cout << "\u2501";
    cout << "\u2513\n\u2503 ";
    SetConsoleTextAttribute(hConsole, 64);
    cout << " \u250F\u2501\u2501\u2501\u2501\u2501\u2501\u2513";//G1------------------
    cout << " \u250F\u2501\u2501\u2501\u2501\u2513 ";//A1
    cout << "\u250F\u2501\u2501\u2513    \u250F\u2501\u2501\u2513";//M1
    cout << "\u250F\u2501\u2501\u2501\u2501\u2501\u2501\u2513";//E1
    SetConsoleTextAttribute(hConsole, 4);
    cout << " \u2503";
    this_thread::sleep_for(200ms);
    cout << "\n\u2503 ";
    cout << "\u250F\u251B \u250F\u2501\u2501\u2501\u2501\u251B";//G2-------------
    cout << "\u250F\u251B \u250F\u2513 \u2517\u2513";//A2
    cout << "\u2503  \u2517\u2513  \u250F\u251B  \u2503";//M2
    cout << "\u2503 \u250F\u2501\u2501\u2501\u2501\u251B";//E2
    cout << " \u2503\n";
    this_thread::sleep_for(200ms);
    cout << "\u2503 ";
    SetConsoleTextAttribute(hConsole, 64);
    cout << "\u2503 \u250F\u251B \u250F\u2501\u2501\u2513";//G3-------------
    cout << "\u2503 \u250F\u251B\u2517\u2513 \u2503";//A3
    cout << "\u2503   \u2517\u2513\u250F\u251B   \u2503";//M3
    cout << "\u2503 \u2517\u2501\u2501\u2501\u2513 ";//E3
    SetConsoleTextAttribute(hConsole, 4);
    cout << " \u2503\n";
    this_thread::sleep_for(200ms);
    cout << "\u2503 ";
    cout << "\u2503 \u2517\u2513 \u2517\u2513 \u2503";//G4-----------------------
    cout << "\u2503 \u2517\u2501\u2501\u251B \u2503";//A4
    cout << "\u2503 \u250F\u2513 \u2517\u251B \u250F\u2513 \u2503";//M4
    cout << "\u2503 \u250F\u2501\u2501\u2501\u251B ";//E4
    cout << " \u2503\n";
    this_thread::sleep_for(200ms);
    cout << "\u2503 ";
    SetConsoleTextAttribute(hConsole, 64);
    cout << "\u2517\u2513 \u2517\u2501\u2501\u251B \u2503";//G5------------------
    cout << "\u2503 \u250F\u2501\u2501\u2513 \u2503";//A5
    cout << "\u2503 \u2503\u2517\u2513  \u250F\u251B\u2503 \u2503";//M5
    cout << "\u2503 \u2517\u2501\u2501\u2501\u2501\u2513";//E5
    SetConsoleTextAttribute(hConsole, 4);
    cout << " \u2503\n";
    this_thread::sleep_for(200ms);
    cout << "\u2503 ";
    cout << " \u2517\u2501\u2501\u2501\u2501\u2501\u2501\u251B";//G6-------------
    cout << "\u2517\u2501\u251B  \u2517\u2501\u251B";//A6
    cout << "\u2517\u2501\u251B \u2517\u2501\u2501\u251B \u2517\u2501\u251B";//M6
    cout << "\u2517\u2501\u2501\u2501\u2501\u2501\u2501\u251B";//E6
    cout << " \u2503\n";
    this_thread::sleep_for(200ms);
    cout << "\u2503 ";
    SetConsoleTextAttribute(hConsole, 64);
    cout << "  \u250F\u2501\u2501\u2501\u2501\u2501\u2513 ";//O1------------------
    cout << "\u250F\u2501\u2501\u2513  \u250F\u2501\u2501\u2513";//V1
    cout << "\u250F\u2501\u2501\u2501\u2501\u2501\u2501\u2513";//E1
    cout << "\u250F\u2501\u2501\u2501\u2501\u2501\u2501\u2513 ";//R1
    SetConsoleTextAttribute(hConsole, 4);
    cout << " \u2503\n";
    this_thread::sleep_for(200ms);
    cout << "\u2503 ";
    cout << " \u250F\u251B \u250F\u2501\u2513 \u2517\u2513";//O2-------------
    cout << "\u2517\u2513 \u2503  \u2503 \u250F\u251B";//V2
    cout << "\u2503 \u250F\u2501\u2501\u2501\u2501\u251B";//E2
    cout << "\u2503 \u250F\u2501\u2501\u2513 \u2503 ";//R2
    cout << " \u2503\n";
    this_thread::sleep_for(200ms);
    cout << "\u2503 ";
    SetConsoleTextAttribute(hConsole, 64);
    cout << " \u2503 \u250F\u251B \u2517\u2513 \u2503";//O3-------------
    cout << " \u2503 \u2517\u2513\u250F\u251B \u2503 ";//V3
    cout << "\u2503 \u2517\u2501\u2501\u2501\u2513 ";//E3
    cout << "\u2503 \u2517\u2501\u2501\u251B \u2503 ";//R3
    SetConsoleTextAttribute(hConsole, 4);
    cout << " \u2503\n";
    this_thread::sleep_for(200ms);
    cout << "\u2503 ";
    cout << " \u2503 \u2517\u2513 \u250F\u251B \u2503";//O4-----------------------
    cout << " \u2517\u2513 \u2517\u251B \u250F\u251B ";//V4
    cout << "\u2503 \u250F\u2501\u2501\u2501\u251B ";//E4
    cout << "\u2503 \u250F\u2501\u2513 \u250F\u251B ";//R4
    cout << " \u2503\n";
    this_thread::sleep_for(200ms);
    cout << "\u2503 ";
    SetConsoleTextAttribute(hConsole, 64);
    cout << " \u2517\u2513 \u2517\u2501\u251B \u250F\u251B";//O5------------------
    cout << "  \u2517\u2513  \u250F\u251B  ";//V5
    cout << "\u2503 \u2517\u2501\u2501\u2501\u2501\u2513";//E5
    cout << "\u2503 \u2503 \u2503 \u2517\u2513 ";//R5
    SetConsoleTextAttribute(hConsole, 4);
    cout << " \u2503\n";
    this_thread::sleep_for(200ms);
    cout << "\u2503 ";
    cout << "  \u2517\u2501\u2501\u2501\u2501\u2501\u251B ";//O6-------------
    cout << "   \u2517\u2501\u2501\u251B   ";//V6
    cout << "\u2517\u2501\u2501\u2501\u2501\u2501\u2501\u251B";//E6
    cout << "\u2517\u2501\u251B \u2517\u2501\u2501\u251B ";//R6
    cout << " \u2503\n";
    this_thread::sleep_for(200ms);
    cout << "\u2517";
    for(int i = 0; i < 39; i++)
        cout << "\u2501";
    cout << "\u251B";
    this_thread::sleep_for(200ms);
    cout << "\nPress Any Key To Continue...";
}
