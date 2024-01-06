#include<iostream>
#include<conio.h>
#include<windows.h>//includes functions for manipulating the console window
#include<time.h>//include functions for manipulating the time
#define SCREEN_WIDTH 90//to define the dimensions of the game screen
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70// to define the width of the game window
using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);//Handle the console window, change and set the cursor position
COORD CursorPosition;//Structure representing the cursor position.
class game
{
public:
    double asteroidY[3];//Arrays to store the positions and flags of enemies
    int asteroidX[3];
    int asteroidFlag[3];
    char ship[4][4] = { ' ',' ','*',' ',
                       ' ', ' ','+',' ',
                       ' ',' ','+',' ',
                       ' ','+','+','+'
                     }; //Array representing the ship shape

    int shipPos = WIN_WIDTH/2;//variable to store the ships position
    int score = 0; //variable to store the players score

    void gotoxy(int x, int y)//To move the cursor to the specified coordinates on th console
    {
        CursorPosition.X = x;
        CursorPosition.Y = y;
        SetConsoleCursorPosition(console, CursorPosition);//functions to set the cursor positions on the specified axis point
    }
    void setcursor(bool visible, DWORD size)//Sets the cursor visibility and size
    {
        if(size == 0)
            size = 20;

        CONSOLE_CURSOR_INFO lpCursor;	//is a structure which holds information of a cursor
        lpCursor.bVisible = visible;
        lpCursor.dwSize = size;
        SetConsoleCursorInfo(console,&lpCursor); //updates the cursor information of the console window
    }
    void drawBorder()//Draws the borders of the game screen
    {
        for(int i=0; i<SCREEN_HEIGHT; i++)
        {
            for(int j=0; j<17; j++)
            {
                gotoxy(0+j,i);
                cout<<"+";
                gotoxy(WIN_WIDTH-j,i);
                cout<<"+";
            }
        }
        for(int i=0; i<SCREEN_HEIGHT; i++)
        {
            gotoxy(SCREEN_WIDTH,i);
            cout<<"+";
        }
    }
    void genasteroid(int ind)//Generates a new asteroid at a random position using the rand function
    {
        asteroidX[ind] = 17 + rand()%(33);  //+17 so that it generates inside the game play

    }
    void drawasteroid(int ind)//Draws the asteroid at the specified index
    {
        if( asteroidFlag[ind] == true )
        {
            gotoxy(asteroidX[ind], asteroidY[ind]);
            cout<<"****";
            gotoxy(asteroidX[ind], asteroidY[ind]+1);
            cout<<" ** ";
            gotoxy(asteroidX[ind], asteroidY[ind]+2);
            cout<<"****";
            gotoxy(asteroidX[ind], asteroidY[ind]+3);
            cout<<" ** ";
        }
    }
    void eraseAsteroid(int ind)//Erases the asteroid at the specified index
    {
        if( asteroidFlag[ind] == true )
        {
            gotoxy(asteroidX[ind], asteroidY[ind]);
            cout<<"    ";
            gotoxy(asteroidX[ind], asteroidY[ind]+1);
            cout<<"    ";
            gotoxy(asteroidX[ind], asteroidY[ind]+2);
            cout<<"    ";
            gotoxy(asteroidX[ind], asteroidY[ind]+3);
            cout<<"    ";
        }
    }
    void resetasteroid(int ind)//Resets the asteroid at the specified index to its initial position
    {
        eraseAsteroid(ind);
        asteroidY[ind] = 1;
        genasteroid(ind);
    }

    void drawShip()//Draws the ship at its current position
    {
        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
            {
                gotoxy(j+shipPos, i+22);
                cout<<ship[i][j];
            }
        }
    }
    void eraseShip()//Erases the ship from its current position
    {
        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++) //running the loop so that the whole ship can be erased
            {
                gotoxy(j+shipPos, i+22);
                cout<<" ";
            }
        }
    }

    int collision()//Checks if there is a collision between the ship and an asteroid
    {
        if( asteroidY[0]+4 >= 23 )//This condition checks if the asteroid has reached or crossed the row where the player's ship is located.
        {
            if( asteroidX[0] + 4 - shipPos >= 0 && asteroidX[0] + 4 - shipPos < 9  )//if the subtraction lies between 0 and 9
            {
                //Above condition checks if there is an overlap between the asteroid and the player's ship within a certain range of X-coordinates.
                return 1;
            }
        }
        return 0;
    }
    void gameover()//Displays the game over screen
    {
        system("cls");
        cout<<endl;
        cout<<"\t\t--------------------------"<<endl;
        cout<<"\t\t-------- Game Over -------"<<endl;
        cout<<"\t\t--------------------------"<<endl<<endl;
        cout<<"\t\tFinal Score: "<<score<<endl;
        cout<<"\t\tPress any key to go back to menu.";
        getch();
        getch();
    }
    void updateScore()//Updates and displays the player's score
    {
        gotoxy(WIN_WIDTH + 7, 5);
        cout<<"Score: "<<score<<endl;
    }
};
class game1:public game
{
public:
    void instructions() //The instructions window that appears on pressing 2
    {
        system("cls");
        cout<<"Instructions";
        cout<<"\n----------------";
        cout<<"\n Avoid Asteroids by moving left or right. ";
        cout<<"\n\n Press 'a' to move left";
        cout<<"\n Press 'd' to move right";
        cout<<"\n Press 'escape' to exit";
        cout<<"\n\nPress any key to go back to menu";
        getch();
    }

    void play()//Implements the main game play logic.
    {
        shipPos = -1 + WIN_WIDTH/2;//Represents position of the players ship
        score = 0;
        asteroidFlag[0] = 1; //determines if an asteroid is active
        asteroidFlag[1] = 0;
        asteroidY[0] = asteroidY[1] = 1;//stores the vertical position of the asteroid

        system("cls");
        drawBorder();
        updateScore();
        genasteroid(0);//generates initial position for 2 asteroids
        genasteroid(1);

        gotoxy(WIN_WIDTH + 7, 2);
        cout<<"Asteroids-";
        gotoxy(WIN_WIDTH + 6, 4);
        cout<<"----------";
        gotoxy(WIN_WIDTH + 6, 6);
        cout<<"----------";
        gotoxy(WIN_WIDTH + 7, 12);
        cout<<"Control ";
        gotoxy(WIN_WIDTH + 7, 13);
        cout<<"-------- ";
        gotoxy(WIN_WIDTH + 2, 14);
        cout<<" A Key - Left";
        gotoxy(WIN_WIDTH + 2, 15);
        cout<<" D Key - Right";

        gotoxy(18, 5);
        cout<<"Press any key to start";
        getch();
        gotoxy(18, 5);
        cout<<"                      ";

        while(1)
        {
            if(kbhit())//checking the user input using khbit() and getch()
            {
                char ch = getch();
                if( ch=='a' || ch=='A' )
                {
                    if( shipPos > 18 )//if ship is not at the leftmost position then ship is shifted to left
                        shipPos -= 4;
                }
                if( ch=='d' || ch=='D' )
                {
                    if( shipPos < 48 )//if ship is not at the rightmost position then draw ship is shifted to right
                        shipPos += 4;
                }
                if(ch==27)//ascii value of the esc key
                {
                    //if esc is pressed by th user, then we are exited from the game.
                    break;
                }
            }

            drawShip(); //in each game loop, it first draws the player's ship
            drawasteroid(0); //then draws the asteroids
            drawasteroid(1);
            if( collision() == 1  )//then it checks for a collision
            {
                gameover();//if a collision is detected then the game over() function ends the game.
                return;
            }
            Sleep(50);
            eraseShip();       //erasing the ship and the asteroid from its previous position
            eraseAsteroid(0);  //So that the ship and asteroid can be printed on the new position
            eraseAsteroid(1);

            //functions to increment the vertical position of the asteroid
            if( asteroidY[0] == 10 )
                if( asteroidFlag[1] == 0 )
                    asteroidFlag[1] = 1;

            if( asteroidFlag[0] == 1 )  //increasing the difficulties according tot he scores of the player
            {
                if(score<10)
                {
                    asteroidY[0] += 0.5;
                }
                else if(score>=10 && score<30)
                {
                    asteroidY[0] += 1;
                }
                else
                {
                    asteroidY[0] += 1.5;
                }
            }

            if( asteroidFlag[1] == 1 )
            {
                if(score<10)
                {
                    asteroidY[1] += 0.5;
                }
                else if(score>=10 && score<30)
                {
                    asteroidY[1] += 1;
                }
                else
                {
                    asteroidY[1] += 1.5;
                }

            }

            if( asteroidY[0] > SCREEN_HEIGHT-4 )//after reaching a particular position erase the asteroid
            {
                resetasteroid(0);
                score++; //updating the scorecard
                updateScore();
            }
            if( asteroidY[1] > SCREEN_HEIGHT-4 )
            {
                resetasteroid(1);
                score++;
                updateScore();
            }
        }
    }
};
int main()
{
    game1 g;
    int setcursor{0};
    srand((unsigned)time(NULL));
    do
    {
        //displaying a menu with multiple options
        system("cls");
        g.gotoxy(10,5);
        cout<<" -------------------------- ";
        g.gotoxy(10,6);
        cout<<" |        Ship Game        | ";
        g.gotoxy(10,7);
        cout<<" --------------------------";
        g.gotoxy(10,9);
        cout<<"1. Start Game";
        g.gotoxy(10,10);
        cout<<"2. Instructions";
        g.gotoxy(10,11);
        cout<<"3. Quit";
        g.gotoxy(10,13);
        cout<<"Select option: ";
        char op = getch();

        //calling corresponding functions based on the users input.
        if( op=='1')
        {
            g.play();
        }
        else if( op=='2')
        {
            g.instructions();
        }
        else if( op=='3')
        {
            exit(0);
        }

    }
    while(1);
    return 0;
}