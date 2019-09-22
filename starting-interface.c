#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<mmsystem.h>


void MoveCarTo0From1();         //Changes the position of car from 1st lane to 2nd lane
void MoveCarTo1From2();         //Changes the position of car from 2nd lane to 3rd lane
void MoveCarTo2From3();         //Changes the position of car from 3rd lane to 4th lane
void MoveCarTo1From0();         //Changes the position of car from 2nd lane to 1st lane
void MoveCarTo2From1();         //Changes the position of car from 3rd lane to 2nd lane
void MoveCarTo3From2();         //Changes the position of car from 4th lane to 3rd lane
void DisplayTrack();            //Displaying track
void MoveCarDown0();            //Moving car through 1st lane
void MoveCarDown1();            //Moving car through 2nd lane
void MoveCarDown2();            //Moving car through 3rd lane
void MoveCarDown3();            //Moving car through 4th lane
void RemoveLastRow();           //This function is used to hide the garbage characters at the lowermost row
void CarCrash();                //Checks if the car collided or not



int count=0;                    //Computer car moving one step down will result in increase of count
int row,column;
int collision=0;
int PositionOfCar;
int ChooseSide;
int pass=0,point=-2;


char track[16][15]=            //This is the array for the track consisting 16 columns and 15 rows
{
    "|            |",
    "|            |",
    "|            |",
    "|            |",
    "|            |",
    "|            |",
    "|            |",
    "|            |",
    "|            |",
    "|            |",
    "|            |",
    "|            |",
    "|o o         |",
    "| o          |",
    "|o o         |",
    "|            |"
};


int main()
{
    FILE *f1;

    char c;

    f1 = fopen("ASCII.txt", "r");           //For opening the "CAR GAME" text at the beginning
    if (f1 == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }

    c = fgetc(f1);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(f1);
    }

    int option;
    printf("\n\n\n                                                     1. PLAY\n                                                     2. CONTROLS\n                                                     3. EXIT\n");
    scanf("%d",&option);

    if(option==3)                                //This lets the player choose between play/controls/exit
    {
        return 0;
    }
    else if(option==2)
    {
        printf("\n                                     1. Move your car right or left to avoid collision\n");
        printf("                                     2. Press 'a' to move left\n");
        printf("                                     3. Press 'd' to move right\n");
        printf("\n\n                                                     1. PLAY\n                                                     2. CONTROLS\n                                                     3. EXIT\n");
        scanf("%d",&option);
    }

    if(option==1)
    {
        PositionOfCar=0;                           //Initially position of the player car is 0.
        char direction;

        DisplayTrack();                            //Display the track initially

        while(count<1000)                         //The total number of steps the computer car can move is set to 1000
        {
            if(collision==1)                                 //If the collision is true, the value becomes 1. That means the game is over
            {
                PlaySound(TEXT("carcrash.wav"),NULL,SND_SYNC);    //Plays the sound after car crash

                FILE *f2;

                char cc;

                f2 = fopen("GAMEOVER.txt", "r");          //Opens the text after the game is over
                if (f2 == NULL)
                {
                    printf("Cannot open file \n");
                    exit(0);
                }

                cc= fgetc(f2);

                while (cc != EOF)
                {
                    printf ("%c", cc);
                    cc = fgetc(f2);
                }

                PlaySound(TEXT("sound.wav"),NULL,SND_SYNC);     //Plays the game over sound

                Sleep(1000);
                return 0;
            }

            RemoveLastRow();                 //This function is used to hide the garbage characters at the lowermost row

            if(pass==0)
            {
                srand(time(0));              //srand() is used for generating random sequence of numbers
                ChooseSide=rand()%4;         //rand() is used for generating random numbers from the sequence
                row=0;
            }

            CarCrash();                     //This checks for collision of the car

            if(ChooseSide==0)
            {
                MoveCarDown0();
            }
            else if(ChooseSide==1)
            {
                MoveCarDown1();
            }
            else if(ChooseSide==2)
            {
                MoveCarDown2();
            }
            else if(ChooseSide==3)
            {
                MoveCarDown3();
            }


            if(kbhit())                       //This if(kbhit()) is used to check if any button from keyboard is pressed
            {
                switch(direction=getch())     //direction is the character variable which scans the button pressed with the help of getch() function
                {
                case 'a':                     //if a is pressed the car moves right
                {
                    if(PositionOfCar==1)
                    {
                        MoveCarTo0From1();
                        PositionOfCar=0;
                    }
                    else if(PositionOfCar==2)
                    {
                        MoveCarTo1From2();
                        PositionOfCar=1;
                    }
                    else if(PositionOfCar==3)
                    {
                        MoveCarTo2From3();
                        PositionOfCar=2;
                    }
                    break;
                }

                case 'd':                    //if a is pressed the car moves right
                {
                    if(PositionOfCar==0)
                    {
                        MoveCarTo1From0();
                        PositionOfCar=1;
                    }
                    else if(PositionOfCar==1)
                    {
                        MoveCarTo2From1();
                        PositionOfCar=2;
                    }
                    else if(PositionOfCar==2)
                    {
                        MoveCarTo3From2();
                        PositionOfCar=3;
                    }
                    break;
                }
                default:
                    ;
                }
            }

            system("cls");                               //This function is used for clearing the screen

            DisplayTrack();

            count++;

            if(count>=0 && count<=30)                       //Here as the count increases the difficulty of the game is increased
            {                                               // by increasing the speed of the computer cars
                Sleep(100);                                 // Sleep(milliseconds)
            }
            else if(count>=31 && count<=60)
            {
                Sleep(80);
            }
            else if(count>=61 && count<=90)
            {
                Sleep(60);
            }
            else if(count>=91 && count<=120)
            {
                Sleep(40);
            }
            else if(count>=121 && count<=150)
            {
                Sleep(20);
            }
            else if(count>=151)
            {
                Sleep(0);
            }
        }

        return 0;
    }
}


void MoveCarTo0From1()                //When this function is called every character of the car is erased and moved 3 units left
{
    track[12][4]=' ';
    track[12][6]=' ';
    track[13][5]=' ';
    track[14][4]=' ';
    track[14][6]=' ';

    track[12][1]='o';
    track[12][3]='o';
    track[13][2]='o';
    track[14][1]='o';
    track[14][3]='o';
}


void MoveCarTo1From2()                //When this function is called every character of the car is erased and moved 3 units left
{
    track[12][7]=' ';
    track[12][9]=' ';
    track[13][8]=' ';
    track[14][7]=' ';
    track[14][9]=' ';

    track[12][4]='o';
    track[12][6]='o';
    track[13][5]='o';
    track[14][4]='o';
    track[14][6]='o';
}


void MoveCarTo2From3()               //When this function is called every character of the car is erased and moved 3 units left
{
    track[12][10]=' ';
    track[12][12]=' ';
    track[13][11]=' ';
    track[14][10]=' ';
    track[14][12]=' ';

    track[12][7]='o';
    track[12][9]='o';
    track[13][8]='o';
    track[14][7]='o';
    track[14][9]='o';
}


void MoveCarTo1From0()                //When this function is called every character of the car is erased and moved 3 units right
{
    track[12][1]=' ';
    track[12][3]=' ';
    track[13][2]=' ';
    track[14][1]=' ';
    track[14][3]=' ';

    track[12][4]='o';
    track[12][6]='o';
    track[13][5]='o';
    track[14][4]='o';
    track[14][6]='o';
}


void MoveCarTo2From1()               //When this function is called every character of the car is erased and moved 3 units right
{
    track[12][4]=' ';
    track[12][6]=' ';
    track[13][5]=' ';
    track[14][4]=' ';
    track[14][6]=' ';

    track[12][7]='o';
    track[12][9]='o';
    track[13][8]='o';
    track[14][7]='o';
    track[14][9]='o';
}


void MoveCarTo3From2()              //When this function is called every character of the car is erased and moved 3 units right
{
    track[12][7]=' ';
    track[12][9]=' ';
    track[13][8]=' ';
    track[14][7]=' ';
    track[14][9]=' ';

    track[12][10]='o';
    track[12][12]='o';
    track[13][11]='o';
    track[14][10]='o';
    track[14][12]='o';
}


void DisplayTrack()                    //The track is displayed from row 3 so that the computer car looks coming from inside the boundary
{
    printf("\n\n\n\n\n\n\n");
    for(int i=3; i<16; i++)
    {
        printf("%65s\n",track[i]);
    }
    if(count%15==0)                                 //The points are showed using this algorithm
    {
        point++;
    }
    printf("\n                                                                            POINTS GAINED: %d",point);
}


void RemoveLastRow()                  //This function is used to hide the garbage characters at the lowermost row
{
    track[15][1]=' ';
    track[15][2]=' ';
    track[15][3]=' ';
    track[15][4]=' ';
    track[15][5]=' ';
    track[15][6]=' ';
    track[15][7]=' ';
    track[15][8]=' ';
    track[15][9]=' ';
    track[15][10]=' ';
    track[15][11]=' ';
    track[15][12]=' ';
}


void MoveCarDown0()                  //When this function is called the computer generated cars move one step downward
{
    track[row][1]=' ';
    track[row][3]=' ';
    track[row+1][2]=' ';
    track[row+2][1]=' ';
    track[row+2][3]=' ';

    row++;

    track[row][1]='o';
    track[row][3]='o';
    track[row+1][2]='o';
    track[row+2][1]='o';
    track[row+2][3]='o';

    pass++;

    if(pass==15)
    {
        pass=0;
    }
}


void MoveCarDown1()               //When this function is called the computer generated cars move one step downward
{
    track[row][4]=' ';
    track[row][6]=' ';
    track[row+1][5]=' ';
    track[row+2][4]=' ';
    track[row+2][6]=' ';

    row++;

    track[row][4]='o';
    track[row][6]='o';
    track[row+1][5]='o';
    track[row+2][4]='o';
    track[row+2][6]='o';

    pass++;

    if(pass==15)
    {
        pass=0;
    }
}


void MoveCarDown2()             //When this function is called the computer generated cars move one step downward
{
    track[row][7]=' ';
    track[row][9]=' ';
    track[row+1][8]=' ';
    track[row+2][7]=' ';
    track[row+2][9]=' ';

    row++;

    track[row][7]='o';
    track[row][9]='o';
    track[row+1][8]='o';
    track[row+2][7]='o';
    track[row+2][9]='o';

    pass++;

    if(pass==15)
    {
        pass=0;
    }
}


void MoveCarDown3()                //When this function is called the computer generated cars move one step downward
{
    track[row][10]=' ';
    track[row][12]=' ';
    track[row+1][11]=' ';
    track[row+2][10]=' ';
    track[row+2][12]=' ';

    row++;

    track[row][10]='o';
    track[row][12]='o';
    track[row+1][11]='o';
    track[row+2][10]='o';
    track[row+2][12]='o';

    pass++;

    if(pass==15)
    {
        pass=0;
    }
}


void CarCrash()                       //Detects collision
{
    if(PositionOfCar==0)              //When the position of the player car is on the left and simultaneously
    {                                 // there is a computer car at that particular position then the value of collision
        if(track[10][1]=='o')         // is assigned to 1 which means the game is over
        {
            collision=1;
        }
    }

    else if(PositionOfCar==1)         //When the position of the player car is on the right and simultaneously
    {                                 // there is a computer car at that particular position then the value of collision
        if(track[10][4]=='o')         // is assigned to 1 which means the game is over
        {
            collision=1;
        }
    }

    else if(PositionOfCar==2)         //When the position of the player car is on the right and simultaneously
    {                                 // there is a computer car at that particular position then the value of collision
        if(track[10][7]=='o')         // is assigned to 1 which means the game is over
        {
            collision=1;
        }
    }

    else if(PositionOfCar==3)         //When the position of the player car is on the right and simultaneously
    {                                 // there is a computer car at that particular position then the value of collision
        if(track[10][10]=='o')        // is assigned to 1 which means the game is over
        {
            collision=1;
        }
    }
}


