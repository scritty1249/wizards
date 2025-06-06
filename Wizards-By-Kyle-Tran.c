/* File Name: Wizards.c

This program will play a game in which players
take the role of wizards and duel in an arena.

   Author: Kyle Tran
*/

/* Notes to Self:
1- Integrate action points
2- Custom player models/colors
3- Add more spells
4- Add stats/spell speeds
5- ADD TORCHES
*/
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <windows.h>

//#define checkFocus (GetForegroundWindow() == GetConsoleWindow()) 
// Virtual Key Macros
#define VK_0 0x30
#define VK_1 0x31
#define VK_2 0x32
#define VK_3 0x33
#define VK_4 0x34
#define VK_5 0x35
#define VK_6 0x36
#define VK_7 0x37
#define VK_8 0x38
#define VK_9 0x39
// Letters
#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A


//if(GetAsyncKeyState(*virtual key code*) & 0x8000) {}
void SetClr(int clrcode) {
    switch(clrcode) {
        case 0: // Foreground WHITE
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
        break;
        case 1: // Foreground GRAY
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN);
        break;
        case 2: // Foreground RED
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
        break;
        case 3: // Foreground BLUE
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE|FOREGROUND_INTENSITY);\
        break;
        case 4: // Foreground GREEN
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
        break;
        case 5: // Foreground BRIGHT RED
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_INTENSITY);
        break;
        case 6: // Foreground NAVY BLUE
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
        break;
        case 7: // Foreground NEON GREEN
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN|FOREGROUND_INTENSITY);
        break;
        case 8: // Foreground CYAN
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
        break;
        case 9: // Foreground PINK
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
        break;
        case 10: // Foreground PURPLE
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_BLUE);
        break;
        case 11: // Foreground YELLOW
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
        break;
    }
}
void wait() {
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);

    int spin = 0, loop = 1;
    printf("\nProgram has been paused, hold SPACEBAR to continue");
    while(loop) {
    if(GetAsyncKeyState(VK_SPACE) & 0x8000) {
        break;
        } else {
            switch(spin) {
                case 0:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (consoleInfo.wAttributes));
                printf("\rProgram has been paused, hold SPACEBAR to continue");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_RED | FOREGROUND_INTENSITY));
                printf(" | .");
                break;
                case 1:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (consoleInfo.wAttributes));
                printf("\rProgram has been paused, hold SPACEBAR to continue");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
                printf(" \\ ..");
                break;
                case 2:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (consoleInfo.wAttributes));
                printf("\rProgram has been paused, hold SPACEBAR to continue");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_GREEN | FOREGROUND_INTENSITY));
                printf(" - ...");
                break;
                case 3:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (consoleInfo.wAttributes));
                printf("\rProgram has been paused, hold SPACEBAR to continue");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY));
                printf(" / ....");
                break;
            }
            sleep(1);
            spin++;
            if(spin == 4) {
                spin = 0;
            } else if(GetAsyncKeyState(VK_SPACE) & 0x0001){
                loop = 0;
            }
            
        }
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (consoleInfo.wAttributes));
}

int main() {
    CONSOLE_SCREEN_BUFFER_INFO stdscrinfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &stdscrinfo);
    CONSOLE_FONT_INFOEX fontinfo, *ftinfo = &fontinfo;
    COORD gamefont = {6, 12};
    fontinfo.dwFontSize = gamefont;
    fontinfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    int ispellcasting[4], plyr[4][2], plyrc[4][2], abltyap[12], count, restart = 1, counter, loop, seccounter, quartersecs, dirupdate[4][2], x, y, scrmaxx, scrmaxy, plyrimv[4], brkloop, framerate, frameincs, plyrhp[4][2], plyrhpc[4][2], plyrap[4][2], plyrapc[4][2], isupdated, clrcode[4], mvbuffer, i, confrimclr, plyrclr[4][5], plyrdir[4], plyrdirc[4], wheel, gamepause, wheelh[2], wheelv[2], frame, plyrablty[4][3];
    COORD cursorDest;
    INPUT vrkeyout;
    vrkeyout.type = INPUT_KEYBOARD;
    vrkeyout.ki.wScan = 0; // hardware scan code for key
    vrkeyout.ki.time = 0;
    vrkeyout.ki.dwExtraInfo = 0;
    vrkeyout.ki.wVk = VK_F11;
    vrkeyout.ki.dwFlags = 0; // 0 for key press
    y = 0;
    x = 0;
    count = 0;
    counter = 0;
    gamepause = 0;
    seccounter = 0;
    quartersecs = 0;
    wheelh[1] = 0;
    wheelv[1] = 0;
    abltyap[0] = 30; // Fireball - 1
    abltyap[1] = 15; // Lightning - 2
    abltyap[2] = 40; // Shield - 3
    plyrdir[0] = 0;
    plyrdir[1] = 1;
    plyrdir[2] = 2;
    plyrdir[3] = 3;
    plyrablty[0][0] = 1;
    plyrablty[0][1] = 2;
    plyrablty[0][2] = 3;
    plyrablty[1][0] = 1;
    plyrablty[1][1] = 2;
    plyrablty[1][2] = 3;
    plyrablty[2][0] = 1;
    plyrablty[2][1] = 2;
    plyrablty[2][2] = 3;
    plyrablty[3][0] = 1;
    plyrablty[3][1] = 2;
    plyrablty[3][2] = 3;
    plyrhp[0][0] = 200; // Health
    plyrhp[0][1] = 200; // Max Health
    plyrhp[1][0] = 200;
    plyrhp[1][1] = 200;
    plyrhp[2][0] = 200;
    plyrhp[2][1] = 200;
    plyrhp[3][0] = 200;
    plyrhp[3][1] = 200;
    plyrap[0][0] = 25;
    plyrap[0][1] = 125;
    plyrap[1][0] = 25;
    plyrap[1][1] = 125;
    plyrap[2][0] = 25;
    plyrap[2][1] = 125;
    plyrap[3][0] = 25;
    plyrap[3][1] = 125;
    clrcode[0] = 3;
    clrcode[1] = 2;
    clrcode[2] = 4;
    clrcode[3] = 0;
    frameincs = 6; // Increments within a frame
    
    framerate = 70000 / frameincs; // *IMPORTANT* Framerate value (70000 MICROsecords = good movement speed)

    scrmaxy = 20;
    scrmaxx = 77;
    int internscrbuffer[20][77];
    int internscr[20][77];
// Initializing Array
    for(y = 0; y < scrmaxy; y++) {
        for(x = 0; x < scrmaxx; x++) {
            if(x == 1 || x == scrmaxx - 2 || y == 0 || y == scrmaxy - 1) {
                internscr[y][x] = 9;
            } else {
                internscr[y][x] = 0;
            }
        }
    }
internscr[7][32] = 9;
internscr[7][33] = 9;
internscr[7][35] = 9;
internscr[7][37] = 9;
internscr[7][38] = 9;
internscr[8][35] = 9;
internscr[9][33] = 9;
internscr[9][34] = 9;
internscr[9][35] = 9;
internscr[9][36] = 9;
internscr[9][37] = 9;
internscr[10][35] = 9;
internscr[11][32] = 9;
internscr[11][33] = 9;
internscr[11][35] = 9;
internscr[11][37] = 9;
internscr[11][38] = 9;

internscr[2][3] = 1;
internscr[2][scrmaxx - 4] = 2;
internscr[scrmaxy - 3][3] = 3;
internscr[scrmaxy - 3][scrmaxx - 4] = 4;

    char eptyspce[3][5] = {
        {"$$$$$"},
        {"$$$$$"},
        {"$$$$$"},
    };
    char wiz[4][3][5] = {
        { // Right
            {"$/\\$$"},
            {"('')/"},
            {"/__\\$"}
        },
        { // Down
            {"$/\\$$"},
            {"('')$"},
            {"/__\\|"}
        },
        { //  Left
            {"$$/\\$"},
            {"\\('')"},
            {"$/__\\"}
        },
        { //  Up
            {".$/\\$"},
            {"|('')"},
            {"$/__\\"}
        }
    };
    char gravestone[3][5] = {
        {"*$$$*"},
        {"I___I"},
        {"/XXX\\"}
    };
    char boundary[3][5] = {
        {"$$$$$"},
        {"0-0-0"},
        {"|___|"}
    };
    char boundaryRedge[3][5] = {
        {"$$$$"},
        {"--0-0"},
        {"____|"}
    };
    char boundaryLedge[3][5] = {
        {"$$$$$"},
        {"0-0--"},
        {"|____"}
    };
    char boundaryNOedge[3][5] = {
        {"$$$$$"},
        {"-0-0-"},
        {"_____"}
    };
    char unknown[3][5] = {
        {"\?\?\?\?\?"},
        {"\?\?\?\?\?"},
        {"\?\?\?\?\?"}
    };
    char fireball[4][3][5] = {
        { // Right
            {"$$$,$"},
            {"$~~>O"},
            {"$$$'$"}
        },
        { //  Down
            {"$$|$$"},
            {"$.|.$"},
            {"$$O$$"}
        },
        { // Left
            {"$,$$$"},
            {"O<~~$"},
            {"$'$$$"},
        },
        { //  Up
            {"$$O$$"},
            {"$'|'$"},
            {"$$|$$"}
        }
    };
    char lightning[4][3][5] = {
        { // NE
            {"$$$*$"},
            {"$$/$$"},
            {"$/$$$"}
        },
        { //  SE
            {"$\\$$$"},
            {"$$\\$$"},
            {"$$$*$"}
        },
        { // SW
            {"$$$/$"},
            {"$$/$$"},
            {"$*$$$"}
        },
        { //  NW
            {"$*$$$"},
            {"$$\\$$"},
            {"$$$\\$"}
        }
    };
    char shield[2][3][5] = {
        {
            {"$$#$$"},
            {"$$#$$"},
            {"$$#$$"}
        },
        {
            {"$$$$$"},
            {"#####"},
            {"$$$$$"}
        }
    };
    char redraw[3][5];
    char plyr1mdl[4][3][5], plyr2mdl[4][3][5], plyr3mdl[4][3][5], plyr4mdl[4][3][5];
    for(counter = 0; counter < 4; counter++) {
        for(count = 0; count < 3; count++) {
            for(i = 0; i < 5; i++) {
                plyr1mdl[counter][count][i] = wiz[counter][count][i];
                plyr2mdl[counter][count][i] = wiz[counter][count][i];
                plyr3mdl[counter][count][i] = wiz[counter][count][i];
                plyr4mdl[counter][count][i] = wiz[counter][count][i];
            }
        }
    }

for(y = 0; y < scrmaxy; y++) {
    for(x = 0; x < scrmaxx; x++) {
        internscrbuffer[y][x] = internscr[y][x];
    }
}

// Getting Player Positions Within Array
for(y = 0; y < scrmaxy; y++) {
    for(x = 0; x < scrmaxx; x++) {
        for(count = 0; count < 4; count++) {
            if(internscr[y][x] == (count + 1)) {
                plyr[count][0] = y;
                plyr[count][1] = x;
            }
        }
    }
}

isupdated = 0;
brkloop = 1;
frame = 0;
loop = 1;

///system("color 28");
printf("Wizards- By Kyle Tran\n");
printf("Version ~PRE-ALPHA~\n");
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (stdscrinfo.wAttributes));
printf("\tControls:\n");
printf("\t\tPause Menu: ESC Key to open | ARROWKEYS to navigate | Enter key to select\n");
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE|FOREGROUND_INTENSITY);
printf("\tPlayer 1: Movement - WASD | Ability 1 - 1 | Ability 2 - 2 | Ability 3 - 3\n");
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
printf("\tPlayer 2: Movement - ARROWKEYS | Ability 1 - ',' | Ability 2 - '.' | Ability 3 - '/'\n");
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
printf("\tPlayer 3: Movement - YGHJ | Ability 1 - X | Ability 2 - C | Ability 3 - V\n");
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED);
printf("\tPlayer 4: Movement - '=', '[', ']', '\\' | Ability 1 - 9 | Ability 2 - 0 | Ability 3 - '-'\n");
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
printf("(Note to my teacher: This entire program has been written in C, and you said we could play any games as long as we made them.)\n\n");
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (stdscrinfo.wAttributes));
//MoveWindow(GetStdHandle(STD_OUTPUT_HANDLE), -100, -100, 1410065408, 1874919424, TRUE);
wait();
sleep(0.5);

// Developer Notes Log
SetClr(9);
printf("\r\t\tDeveloper Bug Log ------------------------\n");
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (stdscrinfo.wAttributes));
printf("~Mana is implemented, however values onscreen do not update until the player's health is changed(Usually damage)\n");
SetClr(9);
printf("\tUpcoming Features\n");
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (stdscrinfo.wAttributes));
printf("~Mana is being worked on, hopefully will be fixed soon but I have a busy schedule, so not anytime soon\n");
printf("~More spells coming soon, either before or after mana is fixed\n");
printf("~Option to pick from additional player models is being considered, and the internal code has already been\n set up to accept new models, will be coming along for sure\n");
SetClr(9);
printf("\tNotes\n");
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (stdscrinfo.wAttributes));
printf("~If anyone would like to uggest or provide their own custom player models please let me know, note that all\n player models cannot be larger than 3 characters high and 5 characters wide\n");
printf("~Any suggestions for tweaks to total HP and mana amounts, as well as ideas for spells, are welcome");
printf("~Currently only 3 spells exist - Fireball, Lightning, and Shield, which are keyed in that order from ability slot 1 to 3\n");
SetClr(11);
printf("~There are quite a few graphics glitches that can occur, if one does, simply pause\nand resume the game to refresh the screen.If the glitch persists, please let me know");
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (stdscrinfo.wAttributes));
sleep(1.6);
printf("\n");
wait();

// Menu
system("cls");
printf("\t\tMenu\n"); // 1 Tab = 8 Spaces
printf("\t  Player 1 |  Player 2 |  Player 3 |  Player 4 |\n");
printf("\n\t");
for(count = 0; count < 4; count++) {
    SetClr(clrcode[count]);
    printf("   $/\\$$   ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (stdscrinfo.wAttributes));
    printf("|");
}
printf("\n\t");
for(count = 0; count < 4; count++) {
    SetClr(clrcode[count]);
    printf("   ('')/   ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (stdscrinfo.wAttributes));
    printf("|");
}
printf("\n\t");
for(count = 0; count < 4; count++) {
    SetClr(clrcode[count]);
    printf("   /__\\$   ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (stdscrinfo.wAttributes));
    printf("|");
}
printf("\n\n");
printf("Up/Down Arrowkeys - Change color\n");
printf("Left/Right Arrowkeys - Select different character\n");
printf("Enter - Confirm Colors\n");
wheelh[0] = 0;
wheelh[1] = 0;
while(loop) {
    if(GetAsyncKeyState(VK_RIGHT) & 0x8000) {
        wheelh[1]++;
        isupdated = 1;
    }
    if(GetAsyncKeyState(VK_LEFT) & 0x8000) {
        wheelh[1]--;
        isupdated = 1;
    }
    if(wheelh[1] < 0) {
        wheelh[1] = 3;
    }
    if(wheelh[1] > 3) {
        wheelh[1] = 0;
    }
    if(GetAsyncKeyState(VK_UP) & 0x8000) {
        switch(wheelh[1]) {
            case 0:
            clrcode[0]++;
            break;
            case 1:
            clrcode[1]++;
            break;
            case 2:
            clrcode[2]++;
            break;
            case 3:
            clrcode[3]++;
            break;
        }
        isupdated = 1;
    }
    if(GetAsyncKeyState(VK_DOWN) & 0x8000) {
        switch(wheelh[1]) {
            case 0:
            clrcode[0]--;
            break;
            case 1:
            clrcode[1]--;
            break;
            case 2:
            clrcode[2]--;
            break;
            case 3:
            clrcode[3]--;
            break;
        }
        isupdated = 1;
    }
    if(GetAsyncKeyState(VK_RETURN) & 0x8000) {
        loop = 0;
    }
    for(count  = 0; count < 4; count++) {
        if(clrcode[count] < 0) {
            clrcode[count] = 11;
        }
        if(clrcode[count] > 11) {
            clrcode[count] = 0;
        }
    }
    // Updating Display
    if(isupdated == 1) {
        if(wheelh[1] == 0) {
            SetClr(clrcode[0]);
            for(count = 0; count < 3; count ++) {
                cursorDest.Y = 3 + count;
                cursorDest.X = 8 + 8;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (cursorDest));
                printf("\b%c\b\b%c\b\b%c\b\b%c\b\b%c", plyr1mdl[0][count][4], plyr1mdl[0][count][3], plyr1mdl[0][count][2], plyr1mdl[0][count][1], plyr1mdl[0][count][0]);
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (stdscrinfo.wAttributes));
        } else if(wheelh[1] == 1) {
            SetClr(clrcode[1]);
            for(count = 0; count < 3; count ++) {
                cursorDest.Y = 3 + count;
                cursorDest.X = 20 + 8;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (cursorDest));
                printf("\b%c\b\b%c\b\b%c\b\b%c\b\b%c", plyr2mdl[0][count][4], plyr2mdl[0][count][3], plyr2mdl[0][count][2], plyr2mdl[0][count][1], plyr2mdl[0][count][0]);
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (stdscrinfo.wAttributes));
        } else if(wheelh[1] == 2) {
            SetClr(clrcode[2]);
            for(count = 0; count < 3; count ++) {
                cursorDest.Y = 3 + count;
                cursorDest.X = 32 + 8;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (cursorDest));
                printf("\b%c\b\b%c\b\b%c\b\b%c\b\b%c", plyr3mdl[0][count][4], plyr3mdl[0][count][3], plyr3mdl[0][count][2], plyr3mdl[0][count][1], plyr3mdl[0][count][0]);
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (stdscrinfo.wAttributes));
        } else if(wheelh[1] == 3) {
            SetClr(clrcode[3]);
            for(count = 0; count < 3; count ++) {
                cursorDest.Y = 3 + count;
                cursorDest.X = 44 + 8;
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (cursorDest));
                printf("\b%c\b\b%c\b\b%c\b\b%c\b\b%c", plyr4mdl[0][count][4], plyr4mdl[0][count][3], plyr4mdl[0][count][2], plyr4mdl[0][count][1], plyr4mdl[0][count][0]);
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (stdscrinfo.wAttributes));
        }
    }
    usleep(70000);
    isupdated = 0;
}

while(restart) {
    restart = 1;
// Display Game Screen
isupdated = 0;
system("cls");
SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE),TRUE,ftinfo);
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_INTENSITY);
SendInput(1, &vrkeyout, sizeof(INPUT)); // Fullscreen In/Out
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (stdscrinfo.wAttributes));
//system("color 28");
for(y = 0; y < scrmaxy; y++) {
        count = 0;
        x = 0;
    while(count < 3) {
        if(x != 0 && x != scrmaxx) {
        switch(internscr[y][x]) {
            case 0: // Empty Space
            for(i = 0; i < 5; i++) {
                if(eptyspce[count][i] == '$') {
                    printf(" ");
                } else {
                    printf("%c", eptyspce[count][i]);
                }
            }
            break;
            case 1: // Player 1
            SetClr(clrcode[0]);
            for(i = 0; i < 5; i++) {
                if(plyr1mdl[plyrdir[0]][count][i] == '$') {
                    printf(" ");
                } else {
                    printf("%c", plyr1mdl[plyrdir[0]][count][i]);
                }
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (stdscrinfo.wAttributes));
            break;
            case 2: // Player 2
            SetClr(clrcode[1]);
            for(i = 0; i < 5; i++) {
                if(plyr2mdl[plyrdir[1]][count][i] == '$') {
                    printf(" ");
                } else {
                    printf("%c", plyr1mdl[plyrdir[1]][count][i]);
                }
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (stdscrinfo.wAttributes));
            break;
            case 3: // Player 3
            SetClr(clrcode[2]);
            for(i = 0; i < 5; i++) {
                if(plyr3mdl[plyrdir[2]][count][i] == '$') {
                    printf(" ");
                } else {
                    printf("%c", plyr1mdl[plyrdir[2]][count][i]);
                }
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (stdscrinfo.wAttributes));
            break;
            case 4: // Player 4
            SetClr(clrcode[3]);
            for(i = 0; i < 5; i++) {
                if(plyr4mdl[plyrdir[3]][count][i] == '$') {
                    printf(" ");
                } else {
                    printf("%c", plyr1mdl[plyrdir[3]][count][i]);
                }
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (stdscrinfo.wAttributes));
            break;
            case 9: // Boundary
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED);
            if(internscr[y][x+1] == 9 && internscr[y][x-1] == 9) { // Boundary with no edges
                for(i = 0; i < 5; i++) {
                    if(boundaryNOedge[count][i] == '$') {
                        printf(" ");
                    } else {
                    printf("%c", boundaryNOedge[count][i]);
                    }
                }
            } else if(internscr[y][x+1] == 9 && internscr[y][x-1] != 9) { // Boundary with Left edge only
                for(i = 0; i < 5; i++) {
                    if(boundaryLedge[count][i] == '$') {
                        printf(" ");
                    } else {
                    printf("%c", boundaryLedge[count][i]);
                    }
                }
            } else if(internscr[y][x-1] == 9 && internscr[y][x+1] != 9) { // Boundary with Right edge only
                for(i = 0; i < 5; i++) {
                    if(boundaryRedge[count][i] == '$') {
                        printf(" ");
                    } else {
                    printf("%c", boundaryRedge[count][i]);
                    }
                }
            } else {
                for(i = 0; i < 5; i++) { // Boundary with both edges
                    if(boundary[count][i] == '$') {
                        printf(" ");
                    } else {
                    printf("%c", boundary[count][i]);
                    }
                }
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (stdscrinfo.wAttributes));
            break;
            default:
            for(i = 0; i < 5; i++) { // Unknown variable
                    printf("%c", unknown[count][i]);
                }
        } // Switch Statement
        } // If Statement
        x++;
        if(x == scrmaxx - 1) {
            printf("\n");
            count++;
            x = 0;
        }
    } // While Statement
 }

 printf("Controls: Player 1- WASD ... Player 2- ARWKEYS ... Player 3- YGHJ ... Player 4- '=','[',']', & '\\'\n");
 printf("Status:\n");

 // Getting ~CURRENT~ Player Positions in Array
 for(y = 0; y < scrmaxy; y++) {
     for(x = 0; x < scrmaxx; x++) {
        for(count = 0; count < 4; count++) {
            if(internscr[y][x] == (count + 1)) {
                plyrc[count][0] = y;
                plyrc[count][1] = x;
            }
          }
        }
      }
for(y = 0; y < scrmaxy; y++) { //  Initializing Screen Buffer
    for(x = 0; x < scrmaxx; x++) {
        internscrbuffer[y][x] = internscr[y][x];
        }
    }
sleep(1);
// Game
while(brkloop) {
// Game Display
        for(y = 0; y < scrmaxy; y++) {
            for(x = 0; x < scrmaxx; x++) {
                if(internscrbuffer[y][x] != internscr[y][x]) {
                    switch(internscr[y][x]) { // Not intended to redraw boundaries
                        case 0:
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(eptyspce[count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = eptyspce[count][i];
                                }
                            }
                        }
                        break;
                        case 1:
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(plyr1mdl[plyrdir[0]][count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = plyr1mdl[plyrdir[0]][count][i];
                                }
                            }
                        }
                        break;
                        case 2:
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(plyr2mdl[plyrdir[1]][count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = plyr2mdl[plyrdir[1]][count][i];
                                }
                            }
                        }
                        break;
                        case 3:
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(plyr3mdl[plyrdir[2]][count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = plyr3mdl[plyrdir[2]][count][i];
                                }
                            }
                        }
                        break;
                        case 4:
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(plyr4mdl[plyrdir[3]][count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = plyr4mdl[plyrdir[3]][count][i];
                                }
                            }
                        }
                        break;
                    // Gravestones
                        case -1:
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(gravestone[count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = gravestone[count][i];
                                }
                            }
                        }
                        break;
                        case -2:
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(gravestone[count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = gravestone[count][i];
                                }
                            }
                        }
                        break;
                        case -3:
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(gravestone[count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = gravestone[count][i];
                                }
                            }
                        }
                        break;
                        case -4:
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(gravestone[count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = gravestone[count][i];
                                }
                            }
                        }
                        break;
                    // Spells
                        case -10: // Fireball Right
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(fireball[0][count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = fireball[0][count][i];
                                }
                            }
                        }
                        break;
                        case -11: // Fireball Down
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(fireball[1][count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = fireball[1][count][i];
                                }
                            }
                        }
                        break;
                        case -12: // Fireball Left
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(fireball[2][count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = fireball[2][count][i];
                                }
                            }
                        }
                        break;
                        case -13: // Fireball Up
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(fireball[3][count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = fireball[3][count][i];
                                }
                            }
                        }
                        break;
                        case -20: // Lightning NE 1
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(lightning[0][count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = lightning[0][count][i];
                                }
                            }
                        }
                        break;
                        case -24: // Lightning NE 2
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(lightning[0][count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = lightning[0][count][i];
                                }
                            }
                        }
                        break;
                        case -28: // Lightning NE 3
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(lightning[0][count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = lightning[0][count][i];
                                }
                            }
                        }
                        break;
                        case -21: // Lightning SE 1
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(lightning[1][count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = lightning[1][count][i];
                                }
                            }
                        }
                        break;
                        case -25: // Lightning SE 2
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(lightning[1][count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = lightning[1][count][i];
                                }
                            }
                        }
                        break;
                        case -29: // Lightning SE 3
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(lightning[1][count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = lightning[1][count][i];
                                }
                            }
                        }
                        break;
                        case -22: // Lightning SW 1
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(lightning[2][count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = lightning[2][count][i];
                                }
                            }
                        }
                        break;
                        case -26: // Lightning SW 2
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(lightning[2][count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = lightning[2][count][i];
                                }
                            }
                        }
                        break;
                        case -18: // Lightning SW 3
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(lightning[2][count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = lightning[2][count][i];
                                }
                            }
                        }
                        break;
                        case -23: // Lightning NW 1
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(lightning[3][count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = lightning[3][count][i];
                                }
                            }
                        }
                        break;
                        case -27: // Lightning NW 2
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(lightning[3][count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = lightning[3][count][i];
                                }
                            }
                        }
                        break;
                        case -19: // Lightning NW 3
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(lightning[3][count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = lightning[3][count][i];
                                }
                            }
                        }
                        break;
                        case -33: // Horozontal Shield
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(shield[1][count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = shield[1][count][i];
                                }
                            }
                        }
                        break;
                        case -31: // Horozontal Shield
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(shield[1][count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = shield[1][count][i];
                                }
                            }
                        }
                        break;
                        case -30: // Vertical Shield
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(shield[0][count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = shield[0][count][i];
                                }
                            }
                        }
                        break;
                        case -32: // Vertical Shield
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(shield[0][count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = shield[0][count][i];
                                }
                            }
                        }
                        break;
                        case -34: // Horozontal Shield
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(shield[1][count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = shield[1][count][i];
                                }
                            }
                        }
                        break;
                        case -35: // Vertical Shield
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(shield[0][count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = shield[0][count][i];
                                }
                            }
                        }
                        break;
                        case -36: // Horozontal Shield
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(shield[1][count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = shield[1][count][i];
                                }
                            }
                        }
                        break;
                        case -37: // Vertical Shield
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(shield[0][count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = shield[0][count][i];
                                }
                            }
                        }
                        break;
                        case -38: // Horozontal Shield
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(shield[1][count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = shield[1][count][i];
                                }
                            }
                        }
                        break;
                        case -39: // Vertical Shield
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(shield[0][count][i] == '$') {
                                    redraw[count][i] = ' ';
                                } else {
                                redraw[count][i] = shield[0][count][i];
                                }
                            }
                        }
                        break;
                    }
                    cursorDest.Y = ((y + 1) * 3) - 1;
                    cursorDest.X = ((x + 1) * 5) - 5;
                    for(count = 2; count >= 0; count--) {
                        i = 6;
                        for(counter = 4; counter >= 0; counter--) {
                            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (cursorDest));
                            if(internscr[y][x] == 1) {
                                SetClr(clrcode[0]);
                            } else if(internscr[y][x] == 2) {
                                SetClr(clrcode[1]);
                            } else if(internscr[y][x] == 3) {
                                SetClr(clrcode[2]);
                            } else if(internscr[y][x] == 4) {
                                SetClr(clrcode[3]);
                            } else if(internscr[y][x] <= -10 && internscr[y][x] >= -13) {
                                SetClr(5);
                            } else if(internscr[y][x] <= -18 && internscr[y][x] >= -29) {
                                SetClr(8);
                            } else if(internscr[y][x] == -1) {
                                SetClr(clrcode[0]);
                            } else if(internscr[y][x] == -2) {
                                SetClr(clrcode[1]);
                            } else if(internscr[y][x] == -3) {
                                SetClr(clrcode[2]);
                            } else if(internscr[y][x] == -4) {
                                SetClr(clrcode[3]);
                            } else if(internscr[y][x] <= -30 && internscr[y][x] >= -33) {
                                SetClr(7);
                            }
                            printf("\b%c", redraw[count][counter]);
                            cursorDest.X = ((x + 1) * 5) - i;
                            i++;
                        }
                        if(count == 2) {
                            cursorDest.Y = ((y + 1) * 3) - 2;
                        } else if(count == 1) {
                            cursorDest.Y = ((y + 1) * 3) - 3;
                        } else if(count == 0) {
                            cursorDest.Y = ((y + 1) * 3) - 4;
                        }
                        cursorDest.X = ((x + 1) * 5) - 5;
                    }
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (stdscrinfo.wAttributes));
                    cursorDest.X = 1;
                    cursorDest.Y = y + (80 - y);
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (cursorDest));
                }
                internscrbuffer[y][x] = internscr[y][x];
            }
        }
    // Displaying Player Stats
    for(count  = 0; count < 4; count++) {
        if(plyrhp[count][1] == -1000) {
            plyrhp[count][0] = -1000;
        }
        if(plyrhp[count][0] != plyrhpc[count][0] || plyrhp[count][1] != plyrhpc[count][1]) {
            cursorDest.Y = 62 + count;
            cursorDest.X = 100;
            SetClr(clrcode[count]);
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (cursorDest));
            printf("\rPlayer %d |", count + 1);
            if(plyrhp[count][0] == -1000) {
                printf(" HP -  ..DEAD.. |");
                plyrhpc[count][0] = plyrhp[count][0];
                plyrhpc[count][1] = plyrhp[count][1];
            } else if(plyrhp[count][0] != plyrhpc[count][0] || plyrhp[count][1] != plyrhpc[count][1]) {
                if(plyrhp[count][0] < 100 && plyrhp[count][1] < 100) {
                printf(" HP -  %d /  %d |", plyrhp[count][0], plyrhp[count][1]);
                } else if(plyrhp[count][0] < 100) {
                printf(" HP -  %d / %d |", plyrhp[count][0], plyrhp[count][1]);
                } else if(plyrhp[count][1] < 100) {
                printf(" HP - %d /  %d |", plyrhp[count][0], plyrhp[count][1]);
                } else {
                printf(" HP - %d / %d |", plyrhp[count][0], plyrhp[count][1]);
                }
            }
            if(plyrap[count][0] != plyrapc[count][0] || plyrap[count][1] != plyrapc[count][1]) {
                if(plyrap[count][0] < 100 && plyrap[count][1] < 100) {
                printf(" MP -  %d /  %d |", plyrap[count][0], plyrap[count][1]);
                } else if(plyrap[count][0] < 100) {
                printf(" MP -  %d / %d |", plyrap[count][0], plyrap[count][1]);
                } else if(plyrap[count][1] < 100) {
                printf(" MP - %d /  %d |", plyrap[count][0], plyrap[count][1]);
                } else {
                printf(" MP - %d / %d |", plyrap[count][0], plyrap[count][1]);
                }
            plyrapc[count][0] = plyrap[count][0];
            plyrapc[count][1] = plyrap[count][1];
            }
            plyrapc[count][0] = plyrap[count][0];
            plyrapc[count][1] = plyrap[count][1];
            plyrhpc[count][0] = plyrhp[count][0];
            plyrhpc[count][1] = plyrhp[count][1];
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (stdscrinfo.wAttributes));
        }
    }

 // Getting ~CURRENT~ Player Positions in Array
 for(y = 0; y < scrmaxy; y++) {
     for(x = 0; x < scrmaxx; x++) {
        for(count = 0; count < 4; count++) {
            if(internscr[y][x] == (count + 1) || internscr[y][x] == -1 * (count + 1)) {
                plyrc[count][0] = y;
                plyrc[count][1] = x;
            }
          }
        }
      }
// Displaying Side Menu

// Pause
if(gamepause == 1) {
    SetClr(8);
    wheelh[1] = 0;
    wheelh[0] = 0;
    cursorDest.X = 22;
    cursorDest.Y = 10;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (cursorDest));
    printf("\r\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t__________________________________________________");
    cursorDest.X = 1;
    cursorDest.Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (cursorDest));
    printf("\r\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|            ->|Wizards - By Kyle Tran           |");
    cursorDest.X = 1;
    cursorDest.Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (cursorDest));
    printf("\r\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|..................   Paused   ..................|");
    cursorDest.X = 1;
    cursorDest.Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (cursorDest));
    printf("\r\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|...................  Exit    ...................|");
    cursorDest.X = 1;
    cursorDest.Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (cursorDest));
    printf("\r\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|..................   Resume   ..................|");
    cursorDest.X = 1;
    cursorDest.Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (cursorDest));
    printf("\r\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|..............  Fullscreen In/Out  .............|");
    cursorDest.X = 1;
    cursorDest.Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (cursorDest));
    printf("\r\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|..................   Restart   .................|");
    cursorDest.X = 1;
    cursorDest.Y++;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (cursorDest));
    printf("\r\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|________________________________________________|");

    while(gamepause) {
    if(GetAsyncKeyState(VK_UP) & 0x8000) {
        wheelh[1]--;
    }
    if(GetAsyncKeyState(VK_DOWN) & 0x8000) {
        wheelh[1]++;
    }
    if(wheelh[1] < 0) {
        wheelh[1] = 5;
    }
    if(wheelh[1] > 5) {
        wheelh[1] = 0;
     }
    if(wheelh[0] != wheelh[1]) {
        if(wheelh[0] == 0) {
            cursorDest.X = 16 + 144; // One Tab = 8 spaces
        } else if(wheelh[0] == 4) {
            cursorDest.X = 17 + 144;
        } else {
            cursorDest.X = 22 + 144;
        }
        cursorDest.Y = 11 + wheelh[0];
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (cursorDest));
        printf("\b \b\b \b\b ");
        if(wheelh[1] == 0) {
            cursorDest.X = 16 + 144;
        } else if(wheelh[1] == 4) {
            cursorDest.X = 17 + 144;
        } else {
            cursorDest.X = 22 + 144;
        }
        cursorDest.Y = 11 + wheelh[1];
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (cursorDest));
        printf("\b|\b\b>\b\b-");
        wheelh[0] = wheelh[1];
        }
    if(GetAsyncKeyState(VK_RETURN) & 0x8000) {
        switch(wheelh[1]) {
            case 0:
            wheelh[1]++;
            break;
            case 1:
            wheelh[1]++;
            break;
            case 2:
            return 0;
            break;
            case 3:
            gamepause = 0; // Resume
            break;
            case 4:
            SendInput(1, &vrkeyout, sizeof(INPUT)); // Fullscreen In/Out
            sleep(0.6);
            break;
            case 5:
            restart = 0;
            break;
        }
      }
        usleep(framerate * frameincs);
    } // Pause WHile Statement
    system("cls");
//system("color 28");
SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE),TRUE,ftinfo);
for(y = 0; y < scrmaxy; y++) {
        count = 0;
        x = 0;
    while(count < 3) {
        if(x != 0 && x != scrmaxx) {
        switch(internscr[y][x]) {
            case -1: // Player 1 Gravestone
            SetClr(clrcode[0]);
            for(i = 0; i < 5; i++) {
                if(gravestone[count][i] == '$') {
                    printf(" ");
                } else {
                    printf("%c", gravestone[count][i]);
                }
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (stdscrinfo.wAttributes));
            break;
            case -2: // Player 2 Gravestone
            SetClr(clrcode[1]);
            for(i = 0; i < 5; i++) {
                if(gravestone[count][i] == '$') {
                    printf(" ");
                } else {
                    printf("%c", gravestone[count][i]);
                }
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (stdscrinfo.wAttributes));
            break;
            case -3: // Player 3 Grvaestone
            SetClr(clrcode[2]);
            for(i = 0; i < 5; i++) {
                if(gravestone[count][i] == '$') {
                    printf(" ");
                } else {
                    printf("%c", gravestone[count][i]);
                }
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (stdscrinfo.wAttributes));
            break;
            case -4: // Player 4 Gravestone
            SetClr(clrcode[3]);
            for(i = 0; i < 5; i++) {
                if(gravestone[count][i] == '$') {
                    printf(" ");
                } else {
                    printf("%c", gravestone[count][i]);
                }
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (stdscrinfo.wAttributes));
            break;
            case 0: // Empty Space
            for(i = 0; i < 5; i++) {
                if(eptyspce[count][i] == '$') {
                    printf(" ");
                } else {
                    printf("%c", eptyspce[count][i]);
                }
            }
            break;
            case 1: // Player 1
            SetClr(clrcode[0]);
            for(i = 0; i < 5; i++) {
                if(plyr1mdl[plyrdir[0]][count][i] == '$') {
                    printf(" ");
                } else {
                    printf("%c", plyr1mdl[plyrdir[0]][count][i]);
                }
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (stdscrinfo.wAttributes));
            break;
            case 2: // Player 2
            SetClr(clrcode[1]);
            for(i = 0; i < 5; i++) {
                if(plyr2mdl[plyrdir[1]][count][i] == '$') {
                    printf(" ");
                } else {
                    printf("%c", plyr1mdl[plyrdir[1]][count][i]);
                }
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (stdscrinfo.wAttributes));
            break;
            case 3: // Player 3
            SetClr(clrcode[2]);
            for(i = 0; i < 5; i++) {
                if(plyr3mdl[plyrdir[2]][count][i] == '$') {
                    printf(" ");
                } else {
                    printf("%c", plyr1mdl[plyrdir[2]][count][i]);
                }
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (stdscrinfo.wAttributes));
            break;
            case 4: // Player 4
            SetClr(clrcode[3]);
            for(i = 0; i < 5; i++) {
                if(plyr4mdl[plyrdir[3]][count][i] == '$') {
                    printf(" ");
                } else {
                    printf("%c", plyr1mdl[plyrdir[3]][count][i]);
                }
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (stdscrinfo.wAttributes));
            break;
            case 9: // Boundary
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED);
            if(internscr[y][x+1] == 9 && internscr[y][x-1] == 9) { // Boundary with no edges
                for(i = 0; i < 5; i++) {
                    if(boundaryNOedge[count][i] == '$') {
                        printf(" ");
                    } else {
                    printf("%c", boundaryNOedge[count][i]);
                    }
                }
            } else if(internscr[y][x+1] == 9 && internscr[y][x-1] != 9) { // Boundary with Left edge only
                for(i = 0; i < 5; i++) {
                    if(boundaryLedge[count][i] == '$') {
                        printf(" ");
                    } else {
                    printf("%c", boundaryLedge[count][i]);
                    }
                }
            } else if(internscr[y][x-1] == 9 && internscr[y][x+1] != 9) { // Boundary with Right edge only
                for(i = 0; i < 5; i++) {
                    if(boundaryRedge[count][i] == '$') {
                        printf(" ");
                    } else {
                    printf("%c", boundaryRedge[count][i]);
                    }
                }
            } else {
                for(i = 0; i < 5; i++) { // Boundary with both edges
                    if(boundary[count][i] == '$') {
                        printf(" ");
                    } else {
                    printf("%c", boundary[count][i]);
                    }
                }
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (stdscrinfo.wAttributes));
            break;
            case -33: // Horozontal Shield
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(shield[1][count][i] == '$') {
                                    printf(" ");
                                } else {
                                printf("%c", shield[1][count][i]);
                                }
                            }
                        }
                        break;
                        case -31: // Horozontal Shield
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(shield[1][count][i] == '$') {
                                    printf(" ");
                                } else {
                                printf("%c", shield[1][count][i]);
                                }
                            }
                        }
                        break;
                        case -30: // Vertical Shield
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(shield[0][count][i] == '$') {
                                    printf(" ");
                                } else {
                                printf("%c", shield[0][count][i]);
                                }
                            }
                        }
                        break;
                        case -32: // Vertical Shield
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(shield[0][count][i] == '$') {
                                    printf(" ");
                                } else {
                                printf("%c", shield[0][count][i]);
                                }
                            }
                        }
                        break;
                        case -34: // Horozontal Shield
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(shield[1][count][i] == '$') {
                                    printf(" ");
                                } else {
                                printf("%c", shield[1][count][i]);
                                }
                            }
                        }
                        break;
                        case -35: // Vertical Shield
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(shield[0][count][i] == '$') {
                                    printf(" ");
                                } else {
                                printf("%c", shield[0][count][i]);
                                }
                            }
                        }
                        break;
                        case -36: // Horozontal Shield
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(shield[1][count][i] == '$') {
                                    printf(" ");
                                } else {
                                printf("%c", shield[1][count][i]);
                                }
                            }
                        }
                        break;
                        case -37: // Vertical Shield
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(shield[0][count][i] == '$') {
                                    printf(" ");
                                } else {
                                printf("%c", shield[0][count][i]);
                                }
                            }
                        }
                        break;
                        case -38: // Horozontal Shield
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(shield[1][count][i] == '$') {
                                    printf(" ");
                                } else {
                                printf("%c", shield[1][count][i]);
                                }
                            }
                        }
                        break;
                        case -39: // Vertical Shield
                        for(count = 0; count < 3; count++) {
                            for(i = 0; i < 5; i++) {
                                if(shield[0][count][i] == '$') {
                                    printf(" ");
                                } else {
                                printf("%c", shield[0][count][i]);
                                }
                            }
                        }
                        break;
            default:
            for(i = 0; i < 5; i++) { // Unknown variable
                    printf("%c", unknown[count][i]);
                }
        } // Switch Statement
        } // If Statement
        x++;
        if(x == scrmaxx) {
            printf("\n");
            count++;
            x = 0;
        }
    } // While Statement
 }
 printf("Wizards - By Kyle Tran - PREALPHA\n");
 printf("Status:\n");
 for(count = 0; count < 4; count++) {
            SetClr(clrcode[count]);
    if(plyrhp[count][0] == -1000) {
        printf("Player %d | HP - ..DEAD.. |  MP - %d / %d\n", count + 1, plyrap[count][0], plyrap[count][1]);
    } else {
        printf("Player %d | HP - %d / %d  |  MP - %d / %d\n", count + 1, plyrhp[count][0], plyrhp[count][1], plyrap[count][0], plyrap[count][1]);
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (stdscrinfo.wAttributes));
  }
  sleep(1);
} // Pause If Statement

for(count = 0; count < 4; count++) {
    plyrdirc[count] = plyrdir[count];
}

// Reading Input
isupdated = 0;
mvbuffer = 0;
for(y = 0; y < scrmaxy; y++) {
    for(x = 0; x < scrmaxx; x++) {
        internscrbuffer[y][x] = internscr[y][x];
        }
    }

if(frame == 0 || frame == 4) {
    if(internscr[plyrc[0][0]][plyrc[0][1]] != -1) { // Player 1
    if(GetAsyncKeyState(VK_W) & 0x8000) {
        if(plyrdir[0] == 3) {
            plyr[0][0]--;
        } else {
            plyrdir[0] = 3;
            internscrbuffer[plyr[0][0]][plyr[0][1]] = 1000;
        }
        isupdated = 1;
    }
    if(GetAsyncKeyState(VK_A) & 0x8000) {
        if(plyrdir[0] == 2) {
            plyr[0][1]--;
        } else {
            plyrdir[0] = 2;
            internscrbuffer[plyr[0][0]][plyr[0][1]] = 1000;
        }
        isupdated = 1;
    }
    if(GetAsyncKeyState(VK_S) & 0x8000) {
        if(plyrdir[0] == 1) {
            plyr[0][0]++;
        } else {
            plyrdir[0] = 1;
            internscrbuffer[plyr[0][0]][plyr[0][1]] = 1000;
        }
        isupdated = 1;
    }
    if(GetAsyncKeyState(VK_D) & 0x8000) {
        if(plyrdir[0] == 0) {
            plyr[0][1]++;
        } else {
            plyrdir[0] = 0;
            internscrbuffer[plyr[0][0]][plyr[0][1]] = 1000;
        }
        isupdated = 1;
    }
    if(GetAsyncKeyState(VK_1) & 0x8000) {
        ispellcasting[0] = 1;
        if(plyrap[0][0] - abltyap[plyrablty[0][0] - 1] > -1) {
        switch(plyrdir[0]) {
            case 0:
            if(internscr[plyrc[0][0]][plyrc[0][1] + 1] == 0) {
                internscr[plyrc[0][0]][plyrc[0][1] + 1] = (plyrablty[0][0] * -10) - plyrdir[0];
            }
            break;
            case 1:
            if(internscr[plyrc[0][0] + 1][plyrc[0][1]] == 0) {
                internscr[plyrc[0][0] + 1][plyrc[0][1]] = (plyrablty[0][0] * -10) - plyrdir[0];
            }
            break;
            case 2:
            if(internscr[plyrc[0][0]][plyrc[0][1] - 1] == 0) {
                internscr[plyrc[0][0]][plyrc[0][1] - 1] = (plyrablty[0][0] * -10) - plyrdir[0];
            }
            break;
            case 3:
            if(internscr[plyrc[0][0] - 1][plyrc[0][1]] == 0) {
                internscr[plyrc[0][0] - 1][plyrc[0][1]] = (plyrablty[0][0] * -10) - plyrdir[0];
            }
            break;
            
        }
        plyrap[0][0] = plyrap[0][0] - abltyap[plyrablty[0][0] - 1];
        isupdated = 1;
        }
    }
    if(GetAsyncKeyState(VK_2) & 0x8000) {
        ispellcasting[0] = 1;
        if(plyrap[0][0] - abltyap[plyrablty[0][1] - 1] > -1) {
        switch(plyrdir[0]) {
            case 0:
            if(internscr[plyrc[0][0]][plyrc[0][1] + 1] == 0) {
                internscr[plyrc[0][0]][plyrc[0][1] + 1] = (plyrablty[0][1] * -10) - plyrdir[0];
            }
            break;
            case 1:
            if(internscr[plyrc[0][0] + 1][plyrc[0][1]] == 0) {
                internscr[plyrc[0][0] + 1][plyrc[0][1]] = (plyrablty[0][1] * -10) - plyrdir[0];
            }
            break;
            case 2:
            if(internscr[plyrc[0][0]][plyrc[0][1] - 1] == 0) {
                internscr[plyrc[0][0]][plyrc[0][1] - 1] = (plyrablty[0][1] * -10) - plyrdir[0];
            }
            break;
            case 3:
            if(internscr[plyrc[0][0] - 1][plyrc[0][1]] == 0) {
                internscr[plyrc[0][0] - 1][plyrc[0][1]] = (plyrablty[0][1] * -10) - plyrdir[0];
            }
            break;

        }
        plyrap[0][0] = plyrap[0][0] - abltyap[plyrablty[0][1] - 1];
        isupdated = 1;
        }
    }
    if(GetAsyncKeyState(VK_3) & 0x8000) {
        ispellcasting[0] = 1;
        if(plyrap[0][0] - abltyap[plyrablty[0][2] - 1] > -1) {
        switch(plyrdir[0]) {
            case 0:
            if(internscr[plyrc[0][0]][plyrc[0][1] + 1] == 0) {
                internscr[plyrc[0][0]][plyrc[0][1] + 1] = (plyrablty[0][2] * -10) - plyrdir[0];
            }
            break;
            case 1:
            if(internscr[plyrc[0][0] + 1][plyrc[0][1]] == 0) {
                internscr[plyrc[0][0] + 1][plyrc[0][1]] = (plyrablty[0][2] * -10) - plyrdir[0];
            }
            break;
            case 2:
            if(internscr[plyrc[0][0]][plyrc[0][1] - 1] == 0) {
                internscr[plyrc[0][0]][plyrc[0][1] - 1] = (plyrablty[0][2] * -10) - plyrdir[0];
            }
            break;
            case 3:
            if(internscr[plyrc[0][0] - 1][plyrc[0][1]] == 0) {
                internscr[plyrc[0][0] - 1][plyrc[0][1]] = (plyrablty[0][2] * -10) - plyrdir[0];
            }
            break;

        }
        plyrap[0][0] = plyrap[0][0] - abltyap[plyrablty[0][2] - 1];
        isupdated = 1;
        }
    }
}
    if(internscr[plyrc[1][0]][plyrc[1][1]] != -2) { // Player 2
    if(GetAsyncKeyState(VK_UP) & 0x8000) {
        if(plyrdir[1] == 3) {
            plyr[1][0]--;
        } else {
            plyrdir[1] = 3;
            internscrbuffer[plyr[1][0]][plyr[1][1]] = 1000;
        }
        isupdated = 1;
    }
    if(GetAsyncKeyState(VK_LEFT) & 0x8000) {
        if(plyrdir[1] == 2) {
            plyr[1][1]--;
        } else {
            plyrdir[1] = 2;
            internscrbuffer[plyr[1][0]][plyr[1][1]] = 1000;
        }
        isupdated = 1;
    }
    if(GetAsyncKeyState(VK_DOWN) & 0x8000) {
        if(plyrdir[1] == 1) {
            plyr[1][0]++;
        } else {
            plyrdir[1] = 1;
            internscrbuffer[plyr[1][0]][plyr[1][1]] = 1000;
        }
        isupdated = 1;
    }
    if(GetAsyncKeyState(VK_RIGHT) & 0x8000) {
        if(plyrdir[1] == 0) {
            plyr[1][1]++;
        } else {
            plyrdir[1] = 0;
            internscrbuffer[plyr[1][0]][plyr[1][1]] = 1000;
        }
        isupdated = 1;
    }
    if(GetAsyncKeyState(VK_OEM_COMMA) & 0x8000) {
        ispellcasting[1] = 1;
    if(plyrap[1][0] - abltyap[plyrablty[0][0] - 1] > -1) {
        switch(plyrdir[1]) {
            case 0:
            if(internscr[plyrc[1][0]][plyrc[1][1] + 1] == 0) {
                internscr[plyrc[1][0]][plyrc[1][1] + 1] = (plyrablty[1][0] * -10) - plyrdir[1];
            }
            break;
            case 1:
            if(internscr[plyrc[1][0] + 1][plyrc[1][1]] == 0) {
                internscr[plyrc[1][0] + 1][plyrc[1][1]] = (plyrablty[1][0] * -10) - plyrdir[1];
            }
            break;
            case 2:
            if(internscr[plyrc[1][0]][plyrc[1][1] - 1] == 0) {
                internscr[plyrc[1][0]][plyrc[1][1] - 1] = (plyrablty[1][0] * -10) - plyrdir[1];
            }
            break;
            case 3:
            if(internscr[plyrc[1][0] - 1][plyrc[1][1]] == 0) {
                internscr[plyrc[1][0] - 1][plyrc[1][1]] = (plyrablty[1][0] * -10) - plyrdir[1];
            }
            break;
            
        }
        plyrap[1][0] = plyrap[1][0] - abltyap[plyrablty[1][0] - 1];
        isupdated = 1;
    }
}
    if(GetAsyncKeyState(VK_OEM_PERIOD) & 0x8000) {
        ispellcasting[1] = 1;
    if(plyrap[1][0] - abltyap[plyrablty[0][1] - 1] > -1) {
        switch(plyrdir[1]) {
            case 0:
            if(internscr[plyrc[1][0]][plyrc[1][1] + 1] == 0) {
                internscr[plyrc[1][0]][plyrc[1][1] + 1] = (plyrablty[1][1] * -10) - plyrdir[1];
            }
            break;
            case 1:
            if(internscr[plyrc[1][0] + 1][plyrc[1][1]] == 0) {
                internscr[plyrc[1][0] + 1][plyrc[1][1]] = (plyrablty[1][1] * -10) - plyrdir[1];
            }
            break;
            case 2:
            if(internscr[plyrc[1][0]][plyrc[1][1] - 1] == 0) {
                internscr[plyrc[1][0]][plyrc[1][1] - 1] = (plyrablty[1][1] * -10) - plyrdir[1];
            }
            break;
            case 3:
            if(internscr[plyrc[1][0] - 1][plyrc[1][1]] == 0) {
                internscr[plyrc[1][0] - 1][plyrc[1][1]] = (plyrablty[1][1] * -10) - plyrdir[1];
            }
            break;

        }
        plyrap[1][0] = plyrap[1][0] - abltyap[plyrablty[1][1] - 1];
        isupdated = 1;
    }
}
    if(GetAsyncKeyState(VK_OEM_2) & 0x8000) {
        ispellcasting[1] = 1;
    if(plyrap[1][0] - abltyap[plyrablty[0][2] - 1] > -1) {
        switch(plyrdir[1]) {
            case 0:
            if(internscr[plyrc[1][0]][plyrc[1][1] + 1] == 0) {
                internscr[plyrc[1][0]][plyrc[1][1] + 1] = (plyrablty[1][2] * -10) - plyrdir[1];
            }
            break;
            case 1:
            if(internscr[plyrc[1][0] + 1][plyrc[1][1]] == 0) {
                internscr[plyrc[1][0] + 1][plyrc[1][1]] = (plyrablty[1][2] * -10) - plyrdir[1];
            }
            break;
            case 2:
            if(internscr[plyrc[1][0]][plyrc[1][1] - 1] == 0) {
                internscr[plyrc[1][0]][plyrc[1][1] - 1] = (plyrablty[1][2] * -10) - plyrdir[1];
            }
            break;
            case 3:
            if(internscr[plyrc[1][0] - 1][plyrc[1][1]] == 0) {
                internscr[plyrc[1][0] - 1][plyrc[1][1]] = (plyrablty[1][2] * -10) - plyrdir[1];
            }
            break;

        }
        plyrap[1][0] = plyrap[1][0] - abltyap[plyrablty[1][2] - 1];
        isupdated = 1;
    }
}
}
    if(internscr[plyrc[2][0]][plyrc[2][1]] != -3) { // Player 3
    if(GetAsyncKeyState(VK_Y) & 0x8000) {
        if(plyrdir[2] == 3) {
            plyr[2][0]--;
        } else {
            plyrdir[2] = 3;
            internscrbuffer[plyr[2][0]][plyr[2][1]] = 1000;
        }
        isupdated = 1;
    }
    if(GetAsyncKeyState(VK_G) & 0x8000) {
        if(plyrdir[2] == 2) {
            plyr[2][1]--;
        } else {
            plyrdir[2] = 2;
            internscrbuffer[plyr[2][0]][plyr[2][1]] = 1000;
        }
        isupdated = 1;
    }
    if(GetAsyncKeyState(VK_H) & 0x8000) {
        if(plyrdir[2] == 1) {
            plyr[2][0]++;
        } else {
            plyrdir[2] = 1;
            internscrbuffer[plyr[2][0]][plyr[2][1]] = 1000;
        }
        isupdated = 1;
    }
    if(GetAsyncKeyState(VK_J) & 0x8000) {
        if(plyrdir[2] == 0) {
            plyr[2][1]++;
        } else {
            plyrdir[2] = 0;
            internscrbuffer[plyr[2][0]][plyr[2][1]] = 1000;
        }
        isupdated = 1;
    }
    if(GetAsyncKeyState(VK_X) & 0x8000) {
        ispellcasting[2] = 1;
    if(plyrap[2][0] - abltyap[plyrablty[0][0] - 1] > -1) {
        switch(plyrdir[2]) {
            case 0:
            if(internscr[plyrc[2][0]][plyrc[2][1] + 1] == 0) {
                internscr[plyrc[2][0]][plyrc[2][1] + 1] = (plyrablty[2][0] * -10) - plyrdir[2];
            }
            break;
            case 1:
            if(internscr[plyrc[2][0] + 1][plyrc[2][1]] == 0) {
                internscr[plyrc[2][0] + 1][plyrc[2][1]] = (plyrablty[2][0] * -10) - plyrdir[2];
            }
            break;
            case 2:
            if(internscr[plyrc[2][0]][plyrc[2][1] - 1] == 0) {
                internscr[plyrc[2][0]][plyrc[2][1] - 1] = (plyrablty[2][0] * -10) - plyrdir[2];
            }
            break;
            case 3:
            if(internscr[plyrc[2][0] - 1][plyrc[2][1]] == 0) {
                internscr[plyrc[2][0] - 1][plyrc[2][1]] = (plyrablty[2][0] * -10) - plyrdir[2];
            }
            break;
            
        }
        plyrap[2][0] = plyrap[2][0] - abltyap[plyrablty[2][0] - 1];
        isupdated = 1;
    }
}
    if(GetAsyncKeyState(VK_C) & 0x8000) {
        ispellcasting[2] = 1;
    if(plyrap[2][0] - abltyap[plyrablty[0][1] - 1] > -1) {
        switch(plyrdir[2]) {
            case 0:
            if(internscr[plyrc[2][0]][plyrc[2][1] + 1] == 0) {
                internscr[plyrc[2][0]][plyrc[2][1] + 1] = (plyrablty[2][1] * -10) - plyrdir[2];
            }
            break;
            case 1:
            if(internscr[plyrc[2][0] + 1][plyrc[2][1]] == 0) {
                internscr[plyrc[2][0] + 1][plyrc[2][1]] = (plyrablty[2][1] * -10) - plyrdir[2];
            }
            break;
            case 2:
            if(internscr[plyrc[2][0]][plyrc[2][1] - 1] == 0) {
                internscr[plyrc[2][0]][plyrc[2][1] - 1] = (plyrablty[2][1] * -10) - plyrdir[2];
            }
            break;
            case 3:
            if(internscr[plyrc[2][0] - 1][plyrc[2][1]] == 0) {
                internscr[plyrc[2][0] - 1][plyrc[2][1]] = (plyrablty[2][1] * -10) - plyrdir[2];
            }
            break;

        }
        plyrap[2][0] = plyrap[2][0] - abltyap[plyrablty[2][1] - 1];
        isupdated = 1;
    }
}
    if(GetAsyncKeyState(VK_V) & 0x8000) {
        ispellcasting[2] = 1;
    if(plyrap[2][0] - abltyap[plyrablty[0][2] - 1] > -1) {
        switch(plyrdir[2]) {
            case 0:
            if(internscr[plyrc[2][0]][plyrc[2][1] + 1] == 0) {
                internscr[plyrc[2][0]][plyrc[2][1] + 1] = (plyrablty[2][2] * -10) - plyrdir[2];
            }
            break;
            case 1:
            if(internscr[plyrc[2][0] + 1][plyrc[2][1]] == 0) {
                internscr[plyrc[2][0] + 1][plyrc[2][1]] = (plyrablty[2][2] * -10) - plyrdir[2];
            }
            break;
            case 2:
            if(internscr[plyrc[2][0]][plyrc[2][1] - 1] == 0) {
                internscr[plyrc[2][0]][plyrc[2][1] - 1] = (plyrablty[2][2] * -10) - plyrdir[2];
            }
            break;
            case 3:
            if(internscr[plyrc[2][0] - 1][plyrc[2][1]] == 0) {
                internscr[plyrc[2][0] - 1][plyrc[2][1]] = (plyrablty[2][2] * -10) - plyrdir[2];
            }
            break;

        }
        plyrap[2][0] = plyrap[2][0] - abltyap[plyrablty[2][2] - 1];
        isupdated = 1;
    }
}
}
    if(internscr[plyrc[3][0]][plyrc[3][1]] != -4) { // Player 4
    if(GetAsyncKeyState(VK_OEM_PLUS) & 0x8000) {
        if(plyrdir[3] == 3) {
            plyr[3][0]--;
        } else {
            plyrdir[3] = 3;
            internscrbuffer[plyr[3][0]][plyr[3][1]] = 1000;
        }
        isupdated = 1;
    }
    if(GetAsyncKeyState(VK_OEM_4) & 0x8000) {
        if(plyrdir[3] == 2) {
            plyr[3][1]--;
        } else {
            plyrdir[3] = 2;
            internscrbuffer[plyr[3][0]][plyr[3][1]] = 1000;
        }
        isupdated = 1;
    }
    if(GetAsyncKeyState(VK_OEM_6) & 0x8000) {
        if(plyrdir[3] == 1) {
            plyr[3][0]++;
        } else {
            plyrdir[3] = 1;
            internscrbuffer[plyr[3][0]][plyr[3][1]] = 1000;
        }
        isupdated = 1;
    }
    if(GetAsyncKeyState(VK_OEM_5) & 0x8000) {
        if(plyrdir[3] == 0) {
            plyr[3][1]++;
        } else {
            plyrdir[3] = 0;
            internscrbuffer[plyr[3][0]][plyr[3][1]] = 1000;
        }
        isupdated = 1;
    }
    if(GetAsyncKeyState(VK_8) & 0x8000) {
        ispellcasting[3] = 1;
    if(plyrap[3][0] - abltyap[plyrablty[0][0] - 1] > -1) {
        switch(plyrdir[3]) {
            case 0:
            if(internscr[plyrc[3][0]][plyrc[3][1] + 1] == 0) {
                internscr[plyrc[3][0]][plyrc[3][1] + 1] = (plyrablty[3][0] * -10) - plyrdir[3];
            }
            break;
            case 1:
            if(internscr[plyrc[3][0] + 1][plyrc[3][1]] == 0) {
                internscr[plyrc[3][0] + 1][plyrc[3][1]] = (plyrablty[3][0] * -10) - plyrdir[3];
            }
            break;
            case 2:
            if(internscr[plyrc[3][0]][plyrc[3][1] - 1] == 0) {
                internscr[plyrc[3][0]][plyrc[3][1] - 1] = (plyrablty[3][0] * -10) - plyrdir[3];
            }
            break;
            case 3:
            if(internscr[plyrc[3][0] - 1][plyrc[3][1]] == 0) {
                internscr[plyrc[3][0] - 1][plyrc[3][1]] = (plyrablty[3][0] * -10) - plyrdir[3];
            }
            break;
            
        }
        plyrap[3][0] = plyrap[3][0] - abltyap[plyrablty[3][0] - 1];
        isupdated = 1;
    }
}
    if(GetAsyncKeyState(VK_9) & 0x8000) {
        ispellcasting[3] = 1;
    if(plyrap[3][0] - abltyap[plyrablty[0][1] - 1] > -1) {
        switch(plyrdir[3]) {
            case 0:
            if(internscr[plyrc[3][0]][plyrc[3][1] + 1] == 0) {
                internscr[plyrc[3][0]][plyrc[3][1] + 1] = (plyrablty[3][1] * -10) - plyrdir[3];
            }
            break;
            case 1:
            if(internscr[plyrc[3][0] + 1][plyrc[3][1]] == 0) {
                internscr[plyrc[3][0] + 1][plyrc[3][1]] = (plyrablty[3][1] * -10) - plyrdir[3];
            }
            break;
            case 2:
            if(internscr[plyrc[3][0]][plyrc[3][1] - 1] == 0) {
                internscr[plyrc[3][0]][plyrc[3][1] - 1] = (plyrablty[3][1] * -10) - plyrdir[3];
            }
            break;
            case 3:
            if(internscr[plyrc[3][0] - 1][plyrc[3][1]] == 0) {
                internscr[plyrc[3][0] - 1][plyrc[3][1]] = (plyrablty[3][1] * -10) - plyrdir[3];
            }
            break;

        }
        plyrap[3][0] = plyrap[3][0] - abltyap[plyrablty[3][1] - 1];
        isupdated = 1;
    }
}
    if(GetAsyncKeyState(VK_0) & 0x8000) {
        ispellcasting[3] = 1;
    if(plyrap[3][0] - abltyap[plyrablty[0][3] - 1] > -1) {
        switch(plyrdir[3]) {
            case 0:
            if(internscr[plyrc[3][0]][plyrc[3][1] + 1] == 0) {
                internscr[plyrc[3][0]][plyrc[3][1] + 1] = (plyrablty[3][2] * -10) - plyrdir[3];
            }
            break;
            case 1:
            if(internscr[plyrc[3][0] + 1][plyrc[3][1]] == 0) {
                internscr[plyrc[3][0] + 1][plyrc[3][1]] = (plyrablty[3][2] * -10) - plyrdir[3];
            }
            break;
            case 2:
            if(internscr[plyrc[3][0]][plyrc[3][1] - 1] == 0) {
                internscr[plyrc[3][0]][plyrc[3][1] - 1] = (plyrablty[3][2] * -10) - plyrdir[3];
            }
            break;
            case 3:
            if(internscr[plyrc[3][0] - 1][plyrc[3][1]] == 0) {
                internscr[plyrc[3][0] - 1][plyrc[3][1]] = (plyrablty[3][2] * -10) - plyrdir[3];
            }
            break;

        }
        plyrap[3][0] = plyrap[3][0] - abltyap[plyrablty[3][2] - 1];
        isupdated = 1;
    }
}
}
    // Pause Programs
    if(GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
        gamepause = 1;
    }
// Checking for collisions
    for(count = 0; count < 4; count++) {
        if(ispellcasting[count] == 1) {
            plyr[count][0] = plyrc[count][0];
            plyr[count][1] = plyrc[count][1];
        } else if(internscr[plyr[count][0]][plyr[count][1]] >-39 && internscr[plyr[count][0]][plyr[count][1]] < -29) {
            plyr[count][0] = plyrc[count][0];
            plyr[count][1] = plyrc[count][1];
        } else if(internscr[plyr[count][0]][plyr[count][1]] < -4) {
            plyrhp[count][0] = plyrhp[count][0] - 30;
        } else if(internscr[plyr[count][0]][plyr[count][1]] != 0) {
            plyr[count][0] = plyrc[count][0];
            plyr[count][1] = plyrc[count][1];
        }
        ispellcasting[count] = 0; // Resetting Spellcast
    }
// Finalizing Player Movement
if(isupdated == 1) {
    for(count = 0; count < 4; count++) {
        if(internscr[plyrc[count][0]][plyrc[count][1]] != -1 * (count + 1)) {
            internscr[plyrc[count][0]][plyrc[count][1]] = 0;
            internscr[plyr[count][0]][plyr[count][1]] = count + 1;
        }
      }
    }
} //  Framerate If Statement

// Spell Movement
for(y = scrmaxy - 1; y >= 0; y--) { // Right & Down / SE Moving Spells
    for(x = scrmaxx - 1; x >= 0; x--) {
        switch(internscr[y][x]) {
            case -10: // Fireball Right
            if(frame == 4) {
            if(internscr[y][x + 1] >= 1 && internscr[y][x + 1] <= 5) {
                plyrhp[internscr[y][x + 1] - 1][0] = plyrhp[internscr[y][x + 1] - 1][0] - 30;
            } else if(internscr[y][x + 1] == 0) {
                internscr[y][x + 1] = -10;
            } else if (internscr[y][x + 1] == -30 || internscr[y][x + 1] == -32) {
                internscr[y][x + 1] = -35;
            } else if (internscr[y][x + 1] == -35) {
                internscr[y][x + 1] = -37;
            } else if (internscr[y][x + 1] == -37) {
                internscr[y][x + 1] = 0;
            } else if (internscr[y][x + 1] == -31 || internscr[y][x + 1] == -33) {
                internscr[y][x + 1] = -35;
            } else if (internscr[y][x + 1] == -34) {
                internscr[y][x + 1] = -37;
            } else if (internscr[y][x + 1] == -35) {
                internscr[y][x + 1] = 0;
            }
            internscr[y][x] = 0;
            }
            break;
            case -11: // Fireball Down
            if(frame == 4) {
            if(internscr[y + 1][x] >= 1 && internscr[y + 1][x] <= 4) {
                plyrhp[internscr[y + 1][x] - 1][0] = plyrhp[internscr[y + 1][x] - 1][0] - 30;
            } else if(internscr[y + 1][x] == 0) {
                internscr[y + 1][x] = -11;
            } else if (internscr[y + 1][x] == -30 || internscr[y + 1][x] == -32) {
                internscr[y + 1][x] = -35;
            } else if (internscr[y + 1][x] == -35) {
                internscr[y + 1][x] = -37;
            } else if (internscr[y + 1][x] == -37) {
                internscr[y + 1][x] = 0;
            } else if (internscr[y + 1][x] == -31 || internscr[y + 1][x] == -33) {
                internscr[y + 1][x] = -35;
            } else if (internscr[y + 1][x] == -34) {
                internscr[y + 1][x] = -37;
            } else if (internscr[y + 1][x] == -35) {
                internscr[y + 1][x] = 0;
            }
            internscr[y][x] = 0;
            }
            break;
            case -21: // Lightning SE 1
            if(frame == 4 || frame == 0) {
            if(internscr[y + 1][x + 1] >= 1 && internscr[y + 1][x + 1] <= 4) {
                plyrhp[internscr[y + 1][x + 1] - 1][0] = plyrhp[internscr[y + 1][x + 1] - 1][0] - 10;
            } else if(internscr[y + 1][x + 1] == 0) {
                internscr[y + 1][x + 1] = -21;
            } else if(internscr[y + 1][x + 1] == 9 && internscr[y][x + 1] == 0) {
                internscr[y][x + 1] = -24;
            } else if(internscr[y + 1][x + 1] == 9 && internscr[y + 1][x] == 0) {
                internscr[y + 1][x] = -27;
            } else if (internscr[y + 1][x + 1] == -30 || internscr[y + 1][x + 1] == -32) {
                internscr[y + 1][x + 1] = -35;
            } else if (internscr[y + 1][x + 1] == -35) {
                internscr[y + 1][x + 1] = -37;
            } else if (internscr[y + 1][x + 1] == -37) {
                internscr[y + 1][x + 1] = 0;
            } else if (internscr[y + 1][x + 1] == -31 || internscr[y + 1][x + 1] == -33) {
                internscr[y + 1][x + 1] = -35;
            } else if (internscr[y + 1][x + 1] == -34) {
                internscr[y + 1][x + 1] = -37;
            } else if (internscr[y + 1][x + 1] == -35) {
                internscr[y + 1][x + 1] = 0;
            }
            internscr[y][x] = 0;
            }
            break;
            case -25: // Lightning SE 2
            if(frame == 4 || frame == 0) {
            if(internscr[y + 1][x + 1] >= 1 && internscr[y + 1][x + 1] <= 4) {
                plyrhp[internscr[y + 1][x + 1] - 1][0] = plyrhp[internscr[y + 1][x + 1] - 1][0] - 10;
            } else if(internscr[y + 1][x + 1] == 0) {
                internscr[y + 1][x + 1] = -21;
            } else if(internscr[y + 1][x + 1] == 9 && internscr[y][x + 1] == 0) {
                internscr[y][x + 1] = -28;
            } else if(internscr[y + 1][x + 1] == 9 && internscr[y + 1][x] == 0) {
                internscr[y + 1][x] = -19;
            } else if (internscr[y + 1][x + 1] == -30 || internscr[y + 1][x + 1] == -32) {
                internscr[y + 1][x + 1] = -35;
            } else if (internscr[y + 1][x + 1] == -35) {
                internscr[y + 1][x + 1] = -37;
            } else if (internscr[y + 1][x + 1] == -37) {
                internscr[y + 1][x + 1] = 0;
            } else if (internscr[y + 1][x + 1] == -31 || internscr[y + 1][x + 1] == -33) {
                internscr[y + 1][x + 1] = -35;
            } else if (internscr[y + 1][x + 1] == -34) {
                internscr[y + 1][x + 1] = -37;
            } else if (internscr[y + 1][x + 1] == -35) {
                internscr[y + 1][x + 1] = 0;
            }
            internscr[y][x] = 0;
            }
            break;
            case -29: // Lightning SE 3
            if(frame == 4 || frame == 0) {
            if(internscr[y + 1][x + 1] >= 1 && internscr[y + 1][x + 1] <= 4) {
                plyrhp[internscr[y + 1][x + 1] - 1][0] = plyrhp[internscr[y + 1][x + 1] - 1][0] - 10;
            } else if(internscr[y + 1][x + 1] == 0) {
                internscr[y + 1][x + 1] = -29;
            } else if (internscr[y + 1][x + 1] == -30 || internscr[y + 1][x + 1] == -32) {
                internscr[y + 1][x + 1] = -35;
            } else if (internscr[y + 1][x + 1] == -35) {
                internscr[y + 1][x + 1] = -37;
            } else if (internscr[y + 1][x + 1] == -37) {
                internscr[y + 1][x + 1] = 0;
            } else if (internscr[y + 1][x + 1] == -31 || internscr[y + 1][x + 1] == -33) {
                internscr[y + 1][x + 1] = -35;
            } else if (internscr[y + 1][x + 1] == -34) {
                internscr[y + 1][x + 1] = -37;
            } else if (internscr[y + 1][x + 1] == -35) {
                internscr[y + 1][x + 1] = 0;
            }
            internscr[y][x] = 0;
            }
            break;
            case -22: // Lightning SW 1
            if(frame == 4 || frame == 0) {
            if(internscr[y + 1][x - 1] >= 1 && internscr[y + 1][x - 1] <= 4) {
                plyrhp[internscr[y + 1][x - 1] - 1][0] = plyrhp[internscr[y - 1][x + 1] - 1][0] - 10;
            } else if(internscr[y + 1][x - 1] == 0) {
                internscr[y + 1][x - 1] = -22;
            } else if(internscr[y + 1][x - 1] == 9 && internscr[y + 1][x] == 0) {
                internscr[y + 1][x] = -25;
            } else if(internscr[y + 1][x - 1] == 9 && internscr[y][x - 1] == 0) {
                internscr[y][x - 1] = -27;
            } else if (internscr[y + 1][x - 1] == -30 || internscr[y + 1][x - 1] == -32) {
                internscr[y + 1][x - 1] = -35;
            } else if (internscr[y + 1][x - 1] == -35) {
                internscr[y + 1][x - 1] = -37;
            } else if (internscr[y + 1][x - 1] == -37) {
                internscr[y + 1][x - 1] = 0;
            } else if (internscr[y + 1][x - 1] == -31 || internscr[y + 1][x - 1] == -33) {
                internscr[y + 1][x - 1] = -35;
            } else if (internscr[y + 1][x - 1] == -34) {
                internscr[y + 1][x - 1] = -37;
            } else if (internscr[y + 1][x - 1] == -35) {
                internscr[y + 1][x - 1] = 0;
            }
            internscr[y][x] = 0;
            }
            break;
            case -26: // Lightning SW 2
            if(frame == 4 || frame == 0) {
            if(internscr[y + 1][x - 1] >= 1 && internscr[y + 1][x - 1] <= 4) {
                plyrhp[internscr[y + 1][x - 1] - 1][0] = plyrhp[internscr[y - 1][x + 1] - 1][0] - 10;
            } else if(internscr[y + 1][x - 1] == 0) {
                internscr[y + 1][x - 1] = -26;
            } else if(internscr[y + 1][x - 1] == 9 && internscr[y + 1][x] == 0) {
                internscr[y + 1][x] = -29;
            } else if(internscr[y + 1][x - 1] == 9 && internscr[y][x - 1] == 0) {
                internscr[y][x - 1] = -19;
            } else if (internscr[y + 1][x - 1] == -30 || internscr[y + 1][x - 1] == -32) {
                internscr[y + 1][x - 1] = -35;
            } else if (internscr[y + 1][x - 1] == -35) {
                internscr[y + 1][x - 1] = -37;
            } else if (internscr[y + 1][x - 1] == -37) {
                internscr[y + 1][x - 1] = 0;
            } else if (internscr[y + 1][x - 1] == -31 || internscr[y + 1][x - 1] == -33) {
                internscr[y + 1][x - 1] = -35;
            } else if (internscr[y + 1][x - 1] == -34) {
                internscr[y + 1][x - 1] = -37;
            } else if (internscr[y + 1][x - 1] == -35) {
                internscr[y + 1][x - 1] = 0;
            }
            internscr[y][x] = 0;
            }
            break;
            case -18: // Lightning SW 3
            if(frame == 4 || frame == 0) {
            if(internscr[y + 1][x - 1] >= 1 && internscr[y + 1][x - 1] <= 4) {
                plyrhp[internscr[y + 1][x - 1] - 1][0] = plyrhp[internscr[y - 1][x + 1] - 1][0] - 10;
            } else if(internscr[y + 1][x - 1] == 0) {
                internscr[y + 1][x - 1] = -18;
            } else if (internscr[y + 1][x - 1] == -30 || internscr[y + 1][x - 1] == -32) {
                internscr[y + 1][x - 1] = -35;
            } else if (internscr[y + 1][x - 1] == -35) {
                internscr[y + 1][x - 1] = -37;
            } else if (internscr[y + 1][x - 1] == -37) {
                internscr[y + 1][x - 1] = 0;
            } else if (internscr[y + 1][x - 1] == -31 || internscr[y + 1][x - 1] == -33) {
                internscr[y + 1][x - 1] = -35;
            } else if (internscr[y + 1][x - 1] == -34) {
                internscr[y + 1][x - 1] = -37;
            } else if (internscr[y + 1][x - 1] == -35) {
                internscr[y + 1][x - 1] = 0;
            }
            internscr[y][x] = 0;
            }
            break;
        }
    }
}
for(y = 0; y < scrmaxy; y++) { // Left & Up / NE, SW, & NW Moving Spells
    for(x = 0; x < scrmaxx; x++) {
        
        switch(internscr[y][x]) {
            case -12: // Fireball Left
            if(frame == 4) {
            if(internscr[y][x - 1] >= 1 && internscr[y][x - 1] <= 4) {
                plyrhp[internscr[y][x - 1] - 1][0] = plyrhp[internscr[y][x - 1] - 1][0] - 30;
            } else if(internscr[y][x - 1] == 0) {
                internscr[y][x - 1] = -12;
            } else if (internscr[y][x - 1] == -30 || internscr[y][x - 1] == -32) {
                internscr[y][x - 1] = -35;
            } else if (internscr[y][x - 1] == -35) {
                internscr[y][x - 1] = -37;
            } else if (internscr[y][x - 1] == -37) {
                internscr[y][x - 1] = 0;
            } else if (internscr[y][x - 1] == -31 || internscr[y][x - 1] == -33) {
                internscr[y][x - 1] = -35;
            } else if (internscr[y][x - 1] == -34) {
                internscr[y][x - 1] = -37;
            } else if (internscr[y][x - 1] == -35) {
                internscr[y][x - 1] = 0;
            }
            internscr[y][x] = 0;
            }
            break;
            case -13: // Fireball Up
            if(frame == 4) {
            if(internscr[y - 1][x] >= 1 && internscr[y - 1][x] <= 4) {
                plyrhp[internscr[y - 1][x] - 1][0] = plyrhp[internscr[y - 1][x] - 1][0] - 30;
            } else if(internscr[y - 1][x] == 0) {
                internscr[y - 1][x] = -13;
            } else if (internscr[y - 1][x] == -30 || internscr[y - 1][x] == -32) {
                internscr[y - 1][x] = -35;
            } else if (internscr[y - 1][x] == -35) {
                internscr[y - 1][x] = -37;
            } else if (internscr[y - 1][x] == -37) {
                internscr[y - 1][x] = 0;
            } else if (internscr[y - 1][x] == -31 || internscr[y - 1][x] == -33) {
                internscr[y - 1][x] = -35;
            } else if (internscr[y - 1][x] == -34) {
                internscr[y - 1][x] = -37;
            } else if (internscr[y - 1][x] == -35) {
                internscr[y - 1][x] = 0;
            }
            internscr[y][x] = 0;
            }
            break;
            case -20: // Lightning NE 1
            if(frame == 4 || frame == 0) {
            if(internscr[y - 1][x + 1] >= 1 && internscr[y - 1][x + 1] <= 4) {
                plyrhp[internscr[y - 1][x + 1] - 1][0] = plyrhp[internscr[y - 1][x + 1] - 1][0] - 10;
            } else if(internscr[y - 1][x + 1] == 0) {
                internscr[y - 1][x + 1] = -20;
            } else if(internscr[y - 1][x + 1] == 9 && internscr[y][x + 1] == 0) {
                internscr[y][x + 1] = -25;
            } else if(internscr[y - 1][x + 1] == 9 && internscr[y - 1][x] == 0) {
                internscr[y - 1][x] = -27;
            } else if (internscr[y - 1][x + 1] == -30 || internscr[y - 1][x + 1] == -32) {
                internscr[y - 1][x + 1] = -35;
            } else if (internscr[y - 1][x + 1] == -35) {
                internscr[y - 1][x + 1] = -37;
            } else if (internscr[y - 1][x + 1] == -37) {
                internscr[y - 1][x + 1] = 0;
            } else if (internscr[y - 1][x + 1] == -31 || internscr[y - 1][x + 1] == -33) {
                internscr[y - 1][x + 1] = -35;
            } else if (internscr[y - 1][x + 1] == -34) {
                internscr[y - 1][x + 1] = -37;
            } else if (internscr[y - 1][x + 1] == -35) {
                internscr[y - 1][x + 1] = 0;
            }
            internscr[y][x] = 0;
            }
            break;
            case -24: // Lightning NE 2
            if(frame == 4 || frame == 0) {
            if(internscr[y - 1][x + 1] >= 1 && internscr[y - 1][x + 1] <= 4) {
                plyrhp[internscr[y - 1][x + 1] - 1][0] = plyrhp[internscr[y - 1][x + 1] - 1][0] - 10;
            } else if(internscr[y - 1][x + 1] == 0) {
                internscr[y - 1][x + 1] = -24;
            } else if(internscr[y - 1][x + 1] == 9 && internscr[y][x + 1] == 0) {
                internscr[y][x + 1] = -29;
            } else if(internscr[y - 1][x + 1] == 9 && internscr[y - 1][x] == 0) {
                internscr[y - 1][x] = -19;
            } else if (internscr[y - 1][x + 1] == -30 || internscr[y - 1][x + 1] == -32) {
                internscr[y - 1][x + 1] = -35;
            } else if (internscr[y - 1][x + 1] == -35) {
                internscr[y - 1][x + 1] = -37;
            } else if (internscr[y - 1][x + 1] == -37) {
                internscr[y - 1][x + 1] = 0;
            } else if (internscr[y - 1][x + 1] == -31 || internscr[y - 1][x + 1] == -33) {
                internscr[y - 1][x + 1] = -35;
            } else if (internscr[y - 1][x + 1] == -34) {
                internscr[y - 1][x + 1] = -37;
            } else if (internscr[y - 1][x + 1] == -35) {
                internscr[y - 1][x + 1] = 0;
            }
            internscr[y][x] = 0;
            }
            break;
            case -28: // Lightning NE 3
            if(frame == 4 || frame == 0) {
            if(internscr[y - 1][x + 1] >= 1 && internscr[y - 1][x + 1] <= 4) {
                plyrhp[internscr[y - 1][x + 1] - 1][0] = plyrhp[internscr[y - 1][x + 1] - 1][0] - 10;
            } else if(internscr[y - 1][x + 1] == 0) {
                internscr[y - 1][x + 1] = -28;
            } else if (internscr[y - 1][x + 1] == -30 || internscr[y - 1][x + 1] == -32) {
                internscr[y - 1][x + 1] = -35;
            } else if (internscr[y - 1][x + 1] == -35) {
                internscr[y - 1][x + 1] = -37;
            } else if (internscr[y - 1][x + 1] == -37) {
                internscr[y - 1][x + 1] = 0;
            } else if (internscr[y - 1][x + 1] == -31 || internscr[y - 1][x + 1] == -33) {
                internscr[y - 1][x + 1] = -35;
            } else if (internscr[y - 1][x + 1] == -34) {
                internscr[y - 1][x + 1] = -37;
            } else if (internscr[y - 1][x + 1] == -35) {
                internscr[y - 1][x + 1] = 0;
            }
            internscr[y][x] = 0;
            }
            break;
            case -23: // Lightning NW 1
            if(frame == 4 || frame == 0) {
            if(internscr[y - 1][x - 1] >= 1 && internscr[y - 1][x - 1] <= 4) {
                plyrhp[internscr[y - 1][x - 1] - 1][0] = plyrhp[internscr[y - 1][x + 1] - 1][0] - 10;
            } else if(internscr[y - 1][x - 1] == 0) {
                internscr[y - 1][x - 1] = -23;
            } else if(internscr[y - 1][x - 1] == 9 && internscr[y][x - 1] == 0) {
                internscr[y][x - 1] = -26;
            } else if(internscr[y - 1][x - 1] == 9 && internscr[y - 1][x] == 0) {
                internscr[y - 1][x] = -24;
            } else if (internscr[y - 1][x - 1] == -30 || internscr[y - 1][x - 1] == -32) {
                internscr[y - 1][x - 1] = -35;
            } else if (internscr[y - 1][x - 1] == -35) {
                internscr[y - 1][x - 1] = -37;
            } else if (internscr[y - 1][x - 1] == -37) {
                internscr[y - 1][x - 1] = 0;
            } else if (internscr[y - 1][x - 1] == -31 || internscr[y - 1][x - 1] == -33) {
                internscr[y - 1][x - 1] = -35;
            } else if (internscr[y - 1][x - 1] == -34) {
                internscr[y - 1][x - 1] = -37;
            } else if (internscr[y - 1][x - 1] == -35) {
                internscr[y - 1][x - 1] = 0;
            }
            internscr[y][x] = 0;
            }
            break;
            case -27: // Lightning NW 2
            if(frame == 4 || frame == 0) {
            if(internscr[y - 1][x - 1] >= 1 && internscr[y - 1][x - 1] <= 4) {
                plyrhp[internscr[y - 1][x - 1] - 1][0] = plyrhp[internscr[y - 1][x + 1] - 1][0] - 10;
            } else if(internscr[y - 1][x - 1] == 0) {
                internscr[y - 1][x - 1] = -27;
            } else if(internscr[y - 1][x - 1] == 9 && internscr[y][x - 1] == 0) {
                internscr[y][x - 1] = -18;
            } else if(internscr[y - 1][x - 1] == 9 && internscr[y - 1][x] == 0) {
                internscr[y - 1][x] = -28;
            } else if (internscr[y - 1][x - 1] == -30 || internscr[y - 1][x - 1] == -32) {
                internscr[y - 1][x - 1] = -35;
            } else if (internscr[y - 1][x - 1] == -35) {
                internscr[y - 1][x - 1] = -37;
            } else if (internscr[y - 1][x - 1] == -37) {
                internscr[y - 1][x - 1] = 0;
            } else if (internscr[y - 1][x - 1] == -31 || internscr[y - 1][x - 1] == -33) {
                internscr[y - 1][x - 1] = -35;
            } else if (internscr[y - 1][x - 1] == -34) {
                internscr[y - 1][x - 1] = -37;
            } else if (internscr[y - 1][x - 1] == -35) {
                internscr[y - 1][x - 1] = 0;
            }
            internscr[y][x] = 0;
            }
            break;
            case -19: // Lightning NW 3
            if(frame == 4 || frame == 0) {
            if(internscr[y - 1][x - 1] >= 1 && internscr[y - 1][x - 1] <= 4) {
                plyrhp[internscr[y - 1][x - 1] - 1][0] = plyrhp[internscr[y - 1][x + 1] - 1][0] - 10;
            } else if(internscr[y - 1][x - 1] == 0) {
                internscr[y - 1][x - 1] = -19;
            } else if (internscr[y - 1][x - 1] == -30 || internscr[y - 1][x - 1] == -32) {
                internscr[y - 1][x - 1] = -35;
            } else if (internscr[y - 1][x - 1] == -35) {
                internscr[y - 1][x - 1] = -37;
            } else if (internscr[y - 1][x - 1] == -37) {
                internscr[y - 1][x - 1] = 0;
            } else if (internscr[y - 1][x - 1] == -31 || internscr[y - 1][x - 1] == -33) {
                internscr[y - 1][x - 1] = -35;
            } else if (internscr[y - 1][x - 1] == -34) {
                internscr[y - 1][x - 1] = -37;
            } else if (internscr[y - 1][x - 1] == -35) {
                internscr[y - 1][x - 1] = 0;
            }
            internscr[y][x] = 0;
            }
            break;
        }
    }
}



for(count = 0; count < 4; count++) { // Player Death
    if(plyrhp[count][0] <= 0 && plyrhp[count][0] != -1000) {
        plyrhp[count][0] = -1000;
        plyrhp[count][1] = -1000;
        internscr[plyr[count][0]][plyr[count][1]] = -1 * (count + 1);
    }
}

usleep(framerate);
frame++;
if(frame > frameincs) { //  Frame Limit
    frame = 0;
    seccounter++;
}
if(seccounter > 300) {
    quartersecs++;
    seccounter = 0;
}
if(quartersecs > 32) { // Counter Limit at 8 seconds
    quartersecs = 0;
}
// Mana Regeneration
if(frame == 3 || frame == 0) {
for(count = 0; count < 4; count++) {
    if(plyrap[count][0] < plyrap[count][1]) {
       plyrap[count][0] = plyrap[count][0] + 5;
    }
    if(plyrap[count][0] > plyrap[count][1]) {
    plyrap[count][0] = plyrap[count][1];
    }
  }
}
} // Loop

} 

wait();
    return 0;
}

