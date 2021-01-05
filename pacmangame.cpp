#include "iGraphics.h"
#include<iostream>
#include<glut.h>


#define mazeX 0
#define mazeY 725
#define MazeSizeX 30
#define MazeSizeY 28
#define screen_width 1000
#define screen_height 800
#define PocmanInitialX  mazeX+pacInitialY*25+25
#define PocmanInitialY  mazeY-22*25+25
#define pacInitialX 22
#define pacInitialY 13
#define pinkyInitialX 14
#define pinkyInitialPixelX mazeX+pinkyInitialY*25+25
#define pinkyInitialY 12
#define pinkyInitialPixelY mazeY-pinkyInitialX*25+25
#define blinkyInitialX 14
#define blinkyInitialPixelX  mazeX+blinkyInitialY*25+25
#define blinkyInitialY 13
#define blinkyInitialPixelY mazeY-blinkyInitialX*25+25
#define inkyInitialX 14
#define inkyInitialPixelX  mazeX+inkyInitialY*25+25
#define inkyInitialY 14
#define inkyInitialPixelY mazeY-inkyInitialX*25+25
#define ClydeInitialX 14
#define clydeInitialPixelX  mazeX+ClydeInitialY*25+25
#define ClydeInitialY 11
#define clydeInitialPixelY mazeY-ClydeInitialX*25+25
#define MAX 10000

int PocmanX = pacInitialX , PocmanY = pacInitialY;
int pacPixelX=PocmanInitialX,pacPixelY=PocmanInitialY;
int pinkyPixelX=pinkyInitialPixelX,pinkyPixelY=pinkyInitialPixelY;
int blinkyPixelX=blinkyInitialPixelX , blinkyPixelY=blinkyInitialPixelY;
int inkyPixelX=inkyInitialPixelX ,inkyPixelY=inkyInitialPixelY;
int clydePixelX=clydeInitialPixelX,clydePixelY=clydeInitialPixelY;
int gamestage=0;
int PacImag=0;
int Score=0;
int start=0,start1=0;
int  PacDieImage=0,PacDieCount=0,Paclife=3;
int chasemode=1,frightenmode=0,frightentime=0,frightendirection=0;
int flag=0;
int musicOn=1;

char ss[20];
char ss1[20];
char paclife[20];
char Name[20];
int index=0;


//score=Score

void MakeMaze();
void goLeft();
void goRight();
void goUp();
void goDown();
void pacWay();
void PointBall();
void ClydeWay();
void InkyWay();
void PinkyWay();
void BlinkyWay();
void GHOST();
void ChaseMode();
void frighten();
void Restart();
void update();
void sorting();
void swaping();



int  checkAvailablePath(int ,int ,int);
int  distance(int x, int y, int x2, int y2);

int helpPinkyX[5]={0,-4,4,0,0};
int helpPinkyY[5]={0,0,0,4,-4};




struct MazeWall{
    double X;
    double Y;
    double dx;
    double dy;
}mazeZ[MazeSizeX][MazeSizeY];


struct HighScore{
   char name[20];
   int gscore;
}RANK[10];
int RankIndex=9;


struct point{
    int x;
    int y;
    int check;

} Ball[MazeSizeX][MazeSizeY];

FILE *fp;
FILE * highScore;

struct Ghost{
    int X;
    int Y;
    int direction;
    int predirection;
    int targetX;
    int targetY;
    int collision;



}Blinky,Pinky,Inky,Clyde;

int maze[MazeSizeX][MazeSizeY]={{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                                {1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
                                {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
                                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                {1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1},
                                {1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1},
                                {1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1},
                                {1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1},
                                {1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1},
                                {1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1},
                                {1,1,1,1,1,1,0,1,1,0,1,1,1,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1},
                                {1,1,1,1,1,1,0,1,1,0,1,0,0,0,0,0,0,1,0,1,1,0,1,1,1,1,1,1},
                                {0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0},
                                {1,1,1,1,1,1,0,1,1,0,1,0,0,0,0,0,0,1,0,1,1,0,1,1,1,1,1,1},
                                {1,1,1,1,1,1,0,1,1,0,1,1,1,1,0,1,1,1,0,1,1,0,1,1,1,1,1,1},
                                {1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1},
                                {1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1},
                                {1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1},
                                {1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
                                {1,0,1,1,1,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,1,0,1},
                                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                {1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1},
                                {1,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1,1},
                                {1,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1},
                                {1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1},
                                {1,0,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1},
                                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
                                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
                                };


char  PacmanUp[3][20]={"pac.bmp" , "pacUp2.bmp" , "pacUp3.bmp" };
char  PacmanDown[3][20]={"pac.bmp" , "pacDown2.bmp" , "pacDown3.bmp"};
char  PacmanLeft[3][20]={"pac.bmp" , "PacLeft2.bmp" , "PacLeft3.bmp"};
char  PacmanRight[3][20]={"pac.bmp" , "pac2.bmp" , "pac3.bmp" };
char PinkyImg[5][20]={"PinkyUp.bmp","PinkyDown.bmp","PinkyRight.bmp","PinkyLeft.bmp"};
char BlinkyImg[5][20]={"BlinkyUp.bmp","BlinkyDown.bmp","BlinkyRight.bmp","BlinkyLeft.bmp"};
char InkyImg[5][20]={"InkyUp.bmp","InkyDown.bmp","InkyRight.bmp","InkyLeft.bmp"};
char ClydeImg[5][20]={"ClydeUp.bmp","ClydeDown.bmp","ClydeRight.bmp","ClydeLeft.bmp"};
char PacDieImg[13][20]={"PacDie1.bmp","PacDie2.bmp","PacDie3.bmp","PacDie4.bmp","PacDie5.bmp","PacDie6.bmp","PacDie7.bmp","PacDie8.bmp","PacDie9.bmp","PacDie10.bmp","PacDie11.bmp","PacDie12.bmp"};
char caught[5][20]={"caughtUp.bmp","caughtDown.bmp","caughtRight.bmp","caughtLeft.bmp"};
char gamestage0[5][20]={"restart.bmp","resume.bmp","highscore.bmp","settings.bmp","credit.bmp"};
char gamestage6[2][20]={"resume.bmp","menu.bmp"};
char   (*pacman)[20];





void iDraw()
{
    iClear();
    if(gamestage==0){
        iShowBMP(0,0,"pacbackground.bmp");
        for(int i=0;i<5;i++){
            iShowBMP2(500,650-i*150,gamestage0[i],0xFFFFFF);
        }
        iSetColor(0,0,0);
        iShowBMP2(20,20,"help.bmp",0xFFFFFF);
        if(flag==1){
        iFilledRectangle(25,25,400,400);
        iSetColor(255,255,255);
        iText(30,400,"Use keyboard array to control pacman",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(30,370,"Use 'q' or 'Q'  to go back",GLUT_BITMAP_TIMES_ROMAN_24);

        }

    }

    else if(gamestage==1){
        if(Paclife==0){
            gamestage=7;
        }
        iShowBMP(0,0,"pacbackground.bmp");
        iSetColor(0,0,0);
        iFilledRectangle(25,25,700,750);

        iSetColor(255 , 255 , 255 );

        int ballCount=0;
        for(int i = 0 ; i < MazeSizeX ; i++){
            for(int j = 0 ; j < MazeSizeY ; j++ ){


                if(Ball[i][j].check == 0 && maze[i][j] == 0){
                    iSetColor(255,0,255);
                    iPoint(Ball[i][j].x + 10 , Ball[i][j].y + 10 , 2);
                    ballCount++;
                }


                if(maze[i][j] == 1){

                    iSetColor(14 , 22 , 185);

                    iFilledRectangle(mazeZ[i][j].X , mazeZ[i][j].Y ,25,25);
                }

            }
        }
        if(ballCount==0){
            gamestage=7;
        }
        ballCount=0;
        if(Ball[1][1].check==0)                  iFilledCircle(Ball[1][1].x + 10 , Ball[1][1].y + 10 , 6);
        if(Ball[1][MazeSizeY-2].check==0)        iFilledCircle(Ball[1][MazeSizeY-2].x + 10 , Ball[1][MazeSizeY-2].y + 10 , 6);
        if(Ball[MazeSizeX-2][1].check==0)        iFilledCircle(Ball[MazeSizeX-2][1].x + 10 , Ball[MazeSizeX-2][1].y + 10 , 6);
        if(Ball[MazeSizeX-2][MazeSizeY-2].check==0)     iFilledCircle(Ball[MazeSizeX-2][MazeSizeY-2].x + 10 , Ball[MazeSizeX-2][MazeSizeY-2].y + 10 , 6);

        if(start!=0 && PacDieImage==0 ){
            iShowBMP2( pacPixelX,pacPixelY, pacman[PacImag] , 0 );
        }
        else if(start==0 && PacDieImage==0){
            iShowBMP2(pacPixelX,pacPixelY , "pac.bmp" , 0 );
        }
        else if(PacDieImage==1){
            iShowBMP2(pacPixelX,pacPixelY , PacDieImg[PacDieCount] , 0 );
        }

        if (chasemode){
            if(Blinky.collision==0)      iShowBMP2(mazeZ[Blinky.X][Blinky.Y].X,mazeZ[Blinky.X][Blinky.Y].Y, BlinkyImg[Blinky.direction-1], 0);
            else if(Blinky.collision==1)    iShowBMP2(mazeZ[Blinky.X][Blinky.Y].X,mazeZ[Blinky.X][Blinky.Y].Y, caught[Blinky.direction-1], 0);
            if(Pinky.collision==0)     iShowBMP2(mazeZ[Pinky.X][Pinky.Y].X,mazeZ[Pinky.X][Pinky.Y].Y, PinkyImg[Pinky.direction-1], 0);
            else if(Pinky.collision==1)     iShowBMP2(mazeZ[Pinky.X][Pinky.Y].X,mazeZ[Pinky.X][Pinky.Y].Y, caught[Pinky.direction-1], 0);
            if(Inky.collision==0)       iShowBMP2(mazeZ[Inky.X][Inky.Y].X,mazeZ[Inky.X][Inky.Y].Y,InkyImg[Inky.direction-1], 0);
            else if(Inky.collision==1)       iShowBMP2(mazeZ[Inky.X][Inky.Y].X,mazeZ[Inky.X][Inky.Y].Y,caught[Inky.direction-1], 0);
            if(Clyde.collision==0)      iShowBMP2(mazeZ[Clyde.X][Clyde.Y].X,mazeZ[Clyde.X][Clyde.Y].Y, ClydeImg[Clyde.direction-1], 0);
            else if(Clyde.collision==1)      iShowBMP2(mazeZ[Clyde.X][Clyde.Y].X,mazeZ[Clyde.X][Clyde.Y].Y, caught[Clyde.direction-1], 0);


        }
        else if(frightenmode==1){

            if(Blinky.collision==0)     iShowBMP2(mazeZ[Blinky.X][Blinky.Y].X,mazeZ[Blinky.X][Blinky.Y].Y, "scatter.bmp", 0);
            else if(Blinky.collision==1)    iShowBMP2(mazeZ[Blinky.X][Blinky.Y].X,mazeZ[Blinky.X][Blinky.Y].Y, caught[Blinky.direction-1], 0);
            if(Pinky.collision==0)     iShowBMP2(mazeZ[Pinky.X][Pinky.Y].X,mazeZ[Pinky.X][Pinky.Y].Y, "scatter.bmp", 0);
             else if(Pinky.collision==1)     iShowBMP2(mazeZ[Pinky.X][Pinky.Y].X,mazeZ[Pinky.X][Pinky.Y].Y, caught[Pinky.direction-1], 0);
           if(Inky.collision==0)     iShowBMP2(mazeZ[Inky.X][Inky.Y].X,mazeZ[Inky.X][Inky.Y].Y,"scatter.bmp", 0);
            else if(Inky.collision==1)       iShowBMP2(mazeZ[Inky.X][Inky.Y].X,mazeZ[Inky.X][Inky.Y].Y,caught[Inky.direction-1], 0);
            if(Clyde.collision==0)     iShowBMP2(mazeZ[Clyde.X][Clyde.Y].X,mazeZ[Clyde.X][Clyde.Y].Y,"scatter.bmp", 0);
            else if(Clyde.collision==1)      iShowBMP2(mazeZ[Clyde.X][Clyde.Y].X,mazeZ[Clyde.X][Clyde.Y].Y, caught[Clyde.direction-1], 0);

        }
        iSetColor(0,0,0);
        iFilledRectangle(740,630,110,120);
        iSetColor(255,255,255);
        iText(750,720,"Score",GLUT_BITMAP_HELVETICA_18);
        iText(750,700,itoa(Score,ss,10),GLUT_BITMAP_HELVETICA_18);
        iText(750,670,"PACLIFE",GLUT_BITMAP_HELVETICA_18);
        iText(750,640,itoa(Paclife,paclife,10),GLUT_BITMAP_HELVETICA_18);



    }
    else if(gamestage==2){

    }
    else if(gamestage==3){
        iShowBMP(0,0,"pacbackground.bmp");
        iSetColor(0,0,0);
        iFilledRectangle(100,100,750,600);
        iSetColor(255,255,255);
        for(int i=0;i<10;i++){
            iText(200,600-i*50,RANK[i].name,GLUT_BITMAP_TIMES_ROMAN_24);
           iText(600,600-i*50,itoa(RANK[i].gscore,ss1,10),GLUT_BITMAP_TIMES_ROMAN_24);
        }


    }
    else if(gamestage==6){
       iShowBMP(0,0,"pacbackground.bmp");
       for(int i=0;i<2;i++){
            iShowBMP2(300,500-i*150,gamestage6[i],0xFFFFFF);
       }

    }
    else if(gamestage==7){
        iShowBMP(0,0,"pacbackground.bmp");
        iSetColor(0,0,0);

        iFilledRectangle(440,440,200,40);
        iSetColor(255,255,255);
        iText(450,500,"Your score is",GLUT_BITMAP_HELVETICA_18);
        iText(580,500,itoa(Score,ss,10),GLUT_BITMAP_HELVETICA_18);
        iText(450,450,Name,GLUT_BITMAP_TIMES_ROMAN_24);

    }
}


void sorting()
{
    for(int i=0;i<10;i++){
        for(int j=i+1;j<10;j++){
            if(RANK[i].gscore<RANK[j].gscore){
                int a;
                a=RANK[i].gscore;
                RANK[i].gscore=RANK[j].gscore;
                RANK[j].gscore=a;

                char s[20];
                strcpy(s,RANK[i].name);
                strcpy(RANK[i].name,RANK[j].name);
                strcpy(RANK[j].name,s);

            }
        }
    }
}

void MakeMaze()
{
    for(int i=0;i<MazeSizeX;i++){
        for(int j=0;j<MazeSizeY;j++){
            {
                mazeZ[i][j].Y=mazeY-i*25+25;
                mazeZ[i][j].X=mazeX+j*25+25;

            }
        }
    }

}


void PointBall()
{
    for(int i=0;i<MazeSizeX;i++){
        for(int j = 0; j<MazeSizeY ; j++){
            if(maze[i][j]==0){
                Ball[i][j].check=0;
                Ball[i][j].x=mazeZ[i][j].X;
                Ball[i][j].y=mazeZ[i][j].Y;
            }
        }
    }
}

void PacImageChange()
{
    if(PacImag<2){
        PacImag++;
    }
    else{
        PacImag=0;
    }

}

void iMouseMove(int mx,int my)
{
    if(gamestage==0){
        if(mx>=20 && mx<=55 && my>=20 && my<=55){
            flag=1; //help
        }
        else {
            flag=0;
        }
    }
}

void iMouse(int button,int state,int mx,int my)
{
    if(gamestage==0){
                highScore=fopen("hs.txt","r");
                for(int i=0;i<10;i++){
                    fgets(RANK[i].name,20,highScore);

                }
                for(int i=0;i<10;i++){
                    fscanf(highScore,"%d",&RANK[i].gscore);
                }
                fclose(highScore);
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
            if(mx>=500 && mx<=900 && my>=650 && my<=775){
                Restart();
                for(int i=0;i<MazeSizeX;i++){
                    for(int j=0;j<MazeSizeY;j++){
                        Ball[i][j].check=0;
                    }
                }
                Score=0;
                Paclife=3;
                Pinky.collision=0;
                Blinky.collision=0;
                Inky.collision=0;
                Clyde.collision=0;
                gamestage=1;//restart
            }
            else if(mx>=500 && mx<=900 && my>=500 && my<=625){
                fp=fopen("resume.txt","r");
                fscanf(fp,"%d%d%d%d%d%d%d%d%d%d%d%d",&Pinky.X,&Pinky.Y,&Blinky.X,&Blinky.Y,&Inky.X,&Inky.Y,&Clyde.X,&Clyde.Y,&pacPixelX,&pacPixelY,&Score,&Paclife);
                printf("%d %d %d %d %d %d %d %d %d %d %d",Pinky.X,Pinky.Y,Blinky.X,Blinky.Y,Inky.X,Inky.Y,Clyde.X,Clyde.Y,PocmanX,PocmanY);
                for(int i=0;i<MazeSizeX;i++){
                    for(int j=0;j<MazeSizeY;j++){
                        fscanf(fp,"%d",&Ball[i][j].check);
                    }
                }
                fclose(fp);
                gamestage=1;
               //resume
            }
            else if(mx>=500 && mx<=900 && my>=350 && my<=475){
                highScore=fopen("hs.txt","r");
                for(int i=0;i<10;i++){
                    fgets(RANK[i].name,20,highScore);

                }
                for(int i=0;i<10;i++){
                    fscanf(highScore,"%d",&RANK[i].gscore);
                }
                fclose(highScore);
                gamestage=3;//highscore
            }
            else if(mx>=500 && mx<=900 && my>=200 && my<=325){
                gamestage=4;//setting
            }
            else if(mx>=500 && mx<=900 && my>=50 && my<=175){
                gamestage=5;//credit
            }
            else if(mx>=20 && mx<=55 && my>=20 && my<=55){
                flag=1; //help
            }
        }

    }
    else if(gamestage==6){
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
            if(mx>=300 && mx<=700 && my>=500 && my<=625){
                gamestage=1;
            }
            else if(mx>=300 && mx<=700 && my>=350 && my<=475){

                fp=fopen("resume.txt","w");
                fprintf(fp,"%d %d %d %d %d %d %d %d %d %d %d %d ",Pinky.X,Pinky.Y,Blinky.X,Blinky.Y,Inky.X,Inky.Y,Clyde.X,Clyde.Y,pacPixelX,pacPixelY,Score,Paclife);
                int one=1,zero=0;
                for(int i=0;i<MazeSizeX;i++){
                    for(int j=0;j<MazeSizeY;j++){
                            fprintf(fp,"%d ",Ball[i][j].check);

                    }
                }
                fclose(fp);
                gamestage=0;
            }
        }

    }

}

void iKeyboard(unsigned char key)
{
    if(gamestage==1){
        if(key=='Q' || key=='q'){
            if(gamestage==1){
                gamestage=6;
            }
        }
    }
    if(gamestage==3){
        if(key=='Q'|| key=='q'){
            gamestage=0;
        }
    }
    if(gamestage==5){
        if(key=='Q'|| key=='q'){
            gamestage=0;
        }
    }
    if(gamestage==4){
        if(key=='Q'|| key=='q'){
            gamestage=0;
        }
    }
    if(gamestage==7){
        if(key=='\b'){
            if(index>0){
                Name[index-1]='\0';
                index--;
            }
            else{
                Name[0]='\0';
                index=0;
            }


        }
        else if(key=='\r'){
            if(Score>=RANK[RankIndex].gscore){
                int i=strlen(Name);
                Name[i]='\n';
                Name[i+1]='\0';
                strcpy(RANK[RankIndex].name,Name) ;
                //strcpy(RANK[RankIndex].name,'\0');
                RANK[RankIndex].gscore=Score;
            }
            sorting();
            highScore=fopen("Hs.txt","w");
            for(int i=0;i<10;i++){
                fputs(RANK[i].name,highScore);

            }
            for(int i=0;i<10;i++){
                fprintf(highScore,"\n%d",RANK[i].gscore);
            }
            fclose(highScore);

            gamestage=0;

            index=0;
        }
        else if(key!='\b'){
            Name[index]=key;
            Name[index+1]='\0';
            index++;
        }
    }
}

void iSpecialKeyboard(unsigned char key)
{

    if(key==GLUT_KEY_UP){
       start=1;

    }
    if(key==GLUT_KEY_DOWN){
         start=2;

    }
    if(key==GLUT_KEY_RIGHT){
        start=3;

    }
    if(key==GLUT_KEY_LEFT){
       start=4;

    }

}
void frighten()
{
    if(frightenmode==1){
        frightentime++;

        if(frightendirection<=1){
            frightendirection++;
          if(Inky.direction==1)Inky.direction=2;
          else if(Inky.direction==2)Inky.direction=1;
          else if(Inky.direction==3)Inky.direction=4;
          else if(Inky.direction==4)Inky.direction=3;

          if(Blinky.direction==1)Blinky.direction=2;
          else if(Blinky.direction==2)Blinky.direction=1;
          else if(Blinky.direction==3)Blinky.direction=4;
          else if(Blinky.direction==4)Blinky.direction=3;

          if(Pinky.direction==1)Pinky.direction=2;
          else if(Pinky.direction==2)Pinky.direction=1;
          else if(Pinky.direction==3)Pinky.direction=4;
          else if(Pinky.direction==4)Pinky.direction=3;

          if(Clyde.direction==1)Clyde.direction=2;
          else if(Clyde.direction==2)Clyde.direction=1;
          else if(Clyde.direction==3)Clyde.direction=4;
          else if(Clyde.direction==4)Clyde.direction=3;
      }
      if(abs(pacPixelX-Blinky.Y*25-25)<=20 && abs(pacPixelY-(mazeY-Blinky.X*25+25))<=20)  Blinky.collision=1;
      if(abs(pacPixelX-Inky.Y*25-25)<=20 && abs(pacPixelY-(mazeY-Inky.X*25+25))<=20)      Inky.collision=1;
      if(abs(pacPixelX-Pinky.Y*25-25)<=20 && abs(pacPixelY-(mazeY-Pinky.X*25+25))<=20)    Pinky.collision=1;
      if(abs(pacPixelX-Clyde.Y*25-25)<=20 && abs(pacPixelY-(mazeY-Clyde.X*25+25))<=20)    Clyde.collision=1;


    }
    if(frightentime==15){
        frightenmode=0;
        frightentime=0;
        chasemode=1;
        frightendirection=0;
    }


}

void pacWay()
{

    PocmanY=(pacPixelX-25)/25;
    PocmanX=(mazeY+25-pacPixelY)/25;
    if(((PocmanX==1 && PocmanY==1)||(PocmanX==1 && PocmanY==MazeSizeY-2)||(PocmanX==MazeSizeX-2 && PocmanY==1)||(PocmanX==MazeSizeX-2 && PocmanY==MazeSizeY-2) )&& Ball[PocmanX][PocmanY].check==0){
        frightenmode=1;
        chasemode=0;
    }

    if(PacDieImage==1) {
        if(PacDieCount>=11){
            PacDieCount++;
        }
        else
        Restart();

    }
    else

    if(start==1 ){
        if(maze[PocmanX-1][PocmanY]==1 && pacPixelX%25!=0){
            start=start1;

        }
        else if(pacPixelX%25==0){
            goUp();
            start1=start;
        }

    }
    else if(start == 2 ){
        if(maze[PocmanX+1][PocmanY]==1 && pacPixelX%25!=0){
            start=start1;

        }
        else if(pacPixelX%25==0){
            goDown();
            start1=start;
        }
    }
    else if(start ==3 ){
        if(maze[PocmanX][PocmanY+1]==1 && pacPixelY%25!=0 ){
            start=start1;

        }
        else if(pacPixelY%25==0){
            goRight();
            start1=start;
        }
    }
    else if(start ==4 ){
        if(maze[PocmanX][PocmanY-1]==1 && pacPixelY%25!=0){
            start=start1;


        }
        else if(pacPixelY%25==0){
            goLeft();
            start1=start;
        }
    }



  //  if((PocmanX==1&& PocmanY==1)||(PocmanX==MazeSizeX-2&&PocmanY==1)||(PocmanX==MazeSizeX-2&& PocmanY==MazeSizeY-2)||(PocmanX==1&&PocmanY==MazeSizeY-2)){
  //      ScatterMode();
  //  }
}

int distance(int x,int y,int  x2,int y2)
{
    return (x-x2)*(x-x2)+(y-y2)*(y-y2);
}

int checkAvailablePath( int x ,int y,int z)
{
    if(x == 1){
        if(maze[y-1][z]==1||(maze[y][z+1]==0||maze[y][z-1]==0)||(maze[y][z+1]==0&&maze[y][z-1]==0&&maze[y-1][z]) ){
            return 1;
        }
        else{
            return 0;
        }
    }
    else if(x == 2){
        if(maze[y+1][z]==1||(maze[y][z+1]==0||maze[y][z-1]==0)||(maze[y][z+1]==0&&maze[y][z-1]==0&&maze[y+1][z]) ){
            return 1;
        }
        else{
            return 0;
        }
    }
    else if(x == 3 ){
        if(maze[y][z+1]==1||(maze[y+1][z]==0||maze[y-1][z]==0)||(maze[y+1][z]==0&&maze[y-1][z]==0&&maze[y][z+1]) ){
            return 1;
        }
        else{
            return 0;
        }

    }
    else if(x == 4){
        if(maze[y][z-1]==1||(maze[y+1][z]==0&&maze[y-1][z]==0)||(maze[y+1][z]==0&&maze[y-1][z]==0&&maze[y-1][z-1]) ){
            return 1;
        }
        else{
            return 0;
        }
    }

}

void Restart()
{
    pacPixelX=PocmanInitialX;
    pacPixelY=PocmanInitialY;
    Blinky.X=blinkyInitialX;
    Blinky.Y=blinkyInitialY;
    Pinky.X=pinkyInitialX;
    Pinky.Y=pinkyInitialY;
    Inky.X=inkyInitialX;
    Inky.Y=inkyInitialY;
    Clyde.X=ClydeInitialX;
    Clyde.Y=ClydeInitialY;
    PacDieImage=0;
    PacDieCount=0;
    start=0;
    start1=0;
}
void update()
{
    if((Inky.X==PocmanX && Inky.Y==PocmanY) || (Blinky.X==PocmanX && Blinky.Y==PocmanY) || (Pinky.X==PocmanX && Pinky.Y==PocmanY) || (Clyde.X==PocmanX && Clyde.Y==PocmanY)){
        Restart();
    }
}

void PinkyWay()
{
    printf("check Pinky\n");
    int minimum=MAX;
    if(Pinky.collision==0){
        Pinky.targetX=PocmanX+helpPinkyX[start];
        Pinky.targetY=PocmanY+helpPinkyY[start];
    }
    else if(Pinky.collision==1){
        Pinky.targetX=12;
        Pinky.targetY=13;
    }
//    Pinky.X=pinky
    if(checkAvailablePath(Pinky.direction,Pinky.X,Pinky.Y)==1){
            printf("check available pinky\n");
        if(maze[Pinky.X-1][Pinky.Y]==0)   minimum = std::min(minimum,distance(Pinky.X-1,Pinky.Y,Pinky.targetX,Pinky.targetY));
            printf("%d ",minimum);
        if(maze[Pinky.X+1][Pinky.Y]==0)   minimum = std::min(minimum,distance(Pinky.X+1,Pinky.Y,Pinky.targetX,Pinky.targetY));
            printf("%d ",minimum);
        if(maze[Pinky.X][Pinky.Y+1]==0)   minimum = std::min(minimum,distance(Pinky.X,Pinky.Y+1,Pinky.targetX,Pinky.targetY));
            printf("%d ",minimum);
        if(maze[Pinky.X][Pinky.Y-1]==0)   minimum = std::min(minimum,distance(Pinky.X,Pinky.Y-1,Pinky.targetX,Pinky.targetY));
            printf("%d ",minimum);
        if(distance(Pinky.X-1,Pinky.Y,Pinky.targetX,Pinky.targetY)==minimum && maze[Pinky.X-1][Pinky.Y]==0){
            Pinky.direction=1;
            Pinky.X--;
            printf("%d ",Pinky.X);
        }
        else if(distance(Pinky.X+1,Pinky.Y,Pinky.targetX,Pinky.targetY)==minimum && maze[Pinky.X+1][Pinky.Y]==0){
            Pinky.direction=2;
            Pinky.X++;
            printf("%d ",Pinky.X);
        }
        else if(distance(Pinky.X,Pinky.Y+1,Pinky.targetX,Pinky.targetY)==minimum && maze[Pinky.X][Pinky.Y+1]==0){
            Pinky.direction=3;
            Pinky.Y++;
            printf("%d ",Pinky.Y);
        }
        else if(distance(Pinky.X,Pinky.Y-1,Pinky.targetX,Pinky.targetY)==minimum && maze[Pinky.X][Pinky.Y-1]==0){
            Pinky.direction=4;
            Pinky.Y--;
            printf("%d ",Pinky.Y);
        }
    }
    else if(checkAvailablePath(Pinky.direction,Pinky.X,Pinky.Y)==0){

        if(Pinky.direction == 1){
            Pinky.X--;
        }
        else if(Pinky.direction == 2){
            Pinky.X++;
        }
        else if(Pinky.direction == 3){
            Pinky.Y++;
        }
        else if(Pinky.direction == 4){
            Pinky.Y--;
        }
    }

    if(abs(pacPixelX-Pinky.Y*25-25)<=20 && abs(pacPixelY-(mazeY-Pinky.X*25+25))<=20){
        if(chasemode && Pinky.collision==0){
            PacDieImage=1;
            if(Paclife>0){
                Paclife--;
            }
        }
    }
    if(Pinky.X==12 && Pinky.Y== 13 && Pinky.collision==1){
        Pinky.collision=0;
    }

}



void ClydeWay()
{
    printf("check clyde\n");
    int minimum=MAX;

    if(Clyde.collision==1){
        Clyde.targetX=12;
        Clyde.targetY=13;
    }

    if(checkAvailablePath(Clyde.direction,Clyde.X,Clyde.Y)==1){
        if(maze[Clyde.X-1][Clyde.Y]==0)   minimum = std::min(minimum,distance(Clyde.X-1,Clyde.Y,Clyde.targetX,Clyde.targetY));

        if(maze[Clyde.X+1][Clyde.Y]==0)   minimum = std::min(minimum,distance(Clyde.X+1,Clyde.Y,Clyde.targetX,Clyde.targetY));

        if(maze[Clyde.X][Clyde.Y+1]==0)   minimum = std::min(minimum,distance(Clyde.X,Clyde.Y+1,Clyde.targetX,Clyde.targetY));

        if(maze[Clyde.X][Clyde.Y-1]==0)   minimum = std::min(minimum,distance(Clyde.X,Clyde.Y-1,Clyde.targetX,Clyde.targetY));

        if(distance(Clyde.X-1,Clyde.Y,Clyde.targetX,Clyde.targetY)==minimum && maze[Clyde.X-1][Clyde.Y]==0){
            Clyde.direction=1;
            Clyde.X--;
        }
        else if(distance(Clyde.X+1,Clyde.Y,Clyde.targetX,Clyde.targetY)==minimum && maze[Clyde.X+1][Clyde.Y]==0){
            Clyde.direction=2;
            Clyde.X++;
        }
        else if(distance(Clyde.X,Clyde.Y+1,Clyde.targetX,Clyde.targetY)==minimum && maze[Clyde.X][Clyde.Y+1]==0){
            Clyde.direction=3;
            Clyde.Y++;
        }
        else if(distance(Clyde.X,Clyde.Y-1,Clyde.targetX,Clyde.targetY)==minimum && maze[Clyde.X][Clyde.Y-1]==0){
            Clyde.direction=4;
            Clyde.Y--;
        }
    }
    else if(checkAvailablePath(Clyde.direction,Clyde.X,Clyde.Y)==0){

        if(Clyde.direction == 1){
            Clyde.X--;
        }
        else if(Clyde.direction == 2){
            Clyde.X++;
        }
        else if(Clyde.direction == 3){
            Clyde.Y++;
        }
        else if(Clyde.direction == 4){
            Clyde.Y--;
        }
    }
    if(Clyde.X == 12 && Clyde.Y ==13 && Clyde.collision==1){
        Clyde.collision=0;
        Clyde.targetX=PocmanX;
        Clyde.targetY=PocmanY;
    }
    else if(Clyde.collision==0){
        if( abs(Clyde.X-PocmanX)<4 && abs(Clyde.Y-PocmanY)<4 ){
            Clyde.targetX=MazeSizeX/2;
            Clyde.targetY=1;
        }
        else{
            Clyde.targetX=PocmanX;
            Clyde.targetY=PocmanY;
        }
    }

    if(abs(pacPixelX-Clyde.Y*25-25)<=20 && abs(pacPixelY-(mazeY-Clyde.X*25+25))<=20){
        if(chasemode && Clyde.collision==0){
            PacDieImage=1;
            if(Paclife>0){
                Paclife--;
            }
        }
    }


}

void BlinkyWay()
{

    printf("check Blinky\n");
    int minimum=MAX;
    if(Blinky.collision==0){
            Blinky.targetX=PocmanX;
            Blinky.targetY=PocmanY;
    }
    else if(Blinky.collision==1){
        Blinky.targetX=12;
        Blinky.targetY=13;
    }

    if(checkAvailablePath(Blinky.direction,Blinky.X,Blinky.Y)==1){
        if(maze[Blinky.X-1][Blinky.Y]==0)   minimum = std::min(minimum,distance(Blinky.X-1,Blinky.Y,Blinky.targetX,Blinky.targetY));

        if(maze[Blinky.X+1][Blinky.Y]==0)   minimum = std::min(minimum,distance(Blinky.X+1,Blinky.Y,Blinky.targetX,Blinky.targetY));

        if(maze[Blinky.X][Blinky.Y+1]==0)   minimum = std::min(minimum,distance(Blinky.X,Blinky.Y+1,Blinky.targetX,Blinky.targetY));

        if(maze[Blinky.X][Blinky.Y-1]==0)   minimum = std::min(minimum,distance(Blinky.X,Blinky.Y-1,Blinky.targetX,Blinky.targetY));

        if(distance(Blinky.X-1,Blinky.Y,Blinky.targetX,Blinky.targetY)==minimum && maze[Blinky.X-1][Blinky.Y]==0){
            Blinky.direction=1;
            Blinky.X--;
        }
        else if(distance(Blinky.X+1,Blinky.Y,Blinky.targetX,Blinky.targetY)==minimum && maze[Blinky.X+1][Blinky.Y]==0){
            Blinky.direction=2;
            Blinky.X++;
        }
        else if(distance(Blinky.X,Blinky.Y+1,Blinky.targetX,Blinky.targetY)==minimum && maze[Blinky.X][Blinky.Y+1]==0){
            Blinky.direction=3;
            Blinky.Y++;
        }
        else if(distance(Blinky.X,Blinky.Y-1,Blinky.targetX,Blinky.targetY)==minimum && maze[Blinky.X][Blinky.Y-1]==0){
            Blinky.direction=4;
            Blinky.Y--;
        }
    }
    else if(checkAvailablePath(Blinky.direction,Blinky.X,Blinky.Y)==0){

        if(Blinky.direction == 1){
            Blinky.X--;
        }
        else if(Blinky.direction == 2){
            Blinky.X++;
        }
        else if(Blinky.direction == 3){
            Blinky.Y++;
        }
        else if(Blinky.direction == 4){
            Blinky.Y--;
        }
    }
    if(abs(pacPixelX-Blinky.Y*25-25)<=20 && abs(pacPixelY-(mazeY-Blinky.X*25+25))<=20){
        if(chasemode && Blinky.collision==0){
            PacDieImage=1;
            if(Paclife>0){
                Paclife--;
            }
        }
    }
    if(Blinky.X==12 && Blinky.Y==13 && Blinky.collision==1){
        Blinky.collision=0;
    }


}

void InkyWay()
{

    printf("check inky\n%d %d",Inky.targetX,Inky.targetY);
    int minimumInky=MAX;
    if(Inky.collision==1){
        Inky.targetX=12;
        Inky.targetY=13;
    }


    if(checkAvailablePath(Inky.direction,Inky.X,Inky.Y)==1){
        if(maze[Inky.X-1][Inky.Y]==0)   minimumInky = std::min(minimumInky,distance(Inky.X-1,Inky.Y,Inky.targetX,Inky.targetY));

        if(maze[Inky.X+1][Inky.Y]==0)   minimumInky = std::min(minimumInky,distance(Inky.X+1,Inky.Y,Inky.targetX,Inky.targetY));

        if(maze[Inky.X][Inky.Y+1]==0)   minimumInky = std::min(minimumInky,distance(Inky.X,Inky.Y+1,Inky.targetX,Inky.targetY));

        if(maze[Inky.X][Inky.Y-1]==0)   minimumInky = std::min(minimumInky,distance(Inky.X,Inky.Y-1,Inky.targetX,Inky.targetY));

        if(distance(Inky.X-1,Inky.Y,Inky.targetX,Inky.targetY)==minimumInky && maze[Inky.X-1][Inky.Y]==0){
            Inky.direction=1;
            Inky.X--;
        }
        else if(distance(Inky.X+1,Inky.Y,Inky.targetX,Inky.targetY)==minimumInky && maze[Inky.X+1][Inky.Y]==0){
            Inky.direction=2;
            Inky.X++;
        }
        else if(distance(Inky.X,Inky.Y+1,Inky.targetX,Inky.targetY)==minimumInky && maze[Inky.X][Inky.Y+1]==0){
            Inky.direction=3;
            Inky.Y++;
        }
        else if(distance(Inky.X,Inky.Y-1,Inky.targetX,Inky.targetY)==minimumInky && maze[Inky.X][Inky.Y-1]==0){
            Inky.direction=4;
            Inky.Y--;
        }
    }
    else if(checkAvailablePath(Inky.direction,Inky.X,Inky.Y)==0){

        if(Inky.direction == 1){
            Inky.X--;
        }
        else if(Inky.direction == 2){
            Inky.X++;
        }
        else if(Inky.direction == 3){
            Inky.Y++;
        }
        else if(Inky.direction == 4){
            Inky.Y--;
        }
    }
    if(Inky.collision==1){
        if(Inky.X==12 && Inky.Y==13){
            Inky.collision=0;
            Inky.targetX=1;
            Inky.targetY=(MazeSizeY-1)/2-1;
        }
    }
    else{
        if(Inky.X==1 && Inky.Y==(MazeSizeY-1)/2-1){
            Inky.targetX=1;
            Inky.targetY=1;
        }

        else if(Inky.X==1 && Inky.Y==1){
            Inky.targetY=1;
            Inky.targetX=MazeSizeX-2;
        }
        else if(Inky.X==inkyInitialX && Inky.Y==inkyInitialY ){
            Inky.targetX=1;
            Inky.targetY=(MazeSizeY-1)/2-1;
        }
        else if(Inky.X==MazeSizeX-2 && Inky.Y==1){
            Inky.targetY=MazeSizeY-2;
            Inky.targetX=MazeSizeX-2;
        }
        else if(Inky.X==MazeSizeX-2 && Inky.Y==MazeSizeY-2){
            Inky.targetX=1;
            Inky.targetY=MazeSizeY-2;
        }
        else if(Inky.X==1 && Inky.Y==MazeSizeY-2){
            Inky.targetY=1;
            Inky.targetX=1;
        }
    }
    if(abs(pacPixelX-Inky.Y*25-25)<=20 && abs(pacPixelY-(mazeY-Inky.X*25+25))<=20){
        if(chasemode && Inky.collision==0){
            PacDieImage=1;
             if(Paclife>0){
                Paclife--;
            }
        }
    }

}

void GHOST()
{
    if(gamestage==1){
        InkyWay();
        PinkyWay();
        ClydeWay();
        BlinkyWay();
    }

}




void goUp()
{
        pacman= PacmanUp;
       if(PocmanX>0){
         if(maze[PocmanX-1][PocmanY]==1 && pacPixelY%25>=5){
            pacPixelY+=5;
         }
         if(maze[PocmanX-1][PocmanY]==0){
            pacPixelY+=5;
         }

       }


       if(Ball[PocmanX][PocmanY].check == 0 && maze[PocmanX][PocmanY]==0){
            Score++;
            Ball[PocmanX][PocmanY].check = 1 ;
        //    maze[PocmanX][PocmanY]==2;
            PlaySound("music\\pacman_chomp.wav",NULL,SND_ASYNC);

        }

}
void goDown()
{

        pacman = PacmanDown ;

        if(PocmanX<29){
            if(maze[PocmanX+1][PocmanY]==0){
                pacPixelY-=5;
            }
            else if(maze[PocmanX+1][PocmanY]==1 && pacPixelY%25>=5){
                pacPixelY-=5;
            }
        }


       if(Ball[PocmanX][PocmanY].check == 0 && maze[PocmanX][PocmanY]==0){


            Score++;
            Ball[PocmanX][PocmanY].check = 1 ;
            PlaySound("music\\pacman_chomp.wav",NULL,SND_ASYNC);

          //  maze[PocmanX][PocmanY]==2;

        }

}
void goRight()
{
        pacman = PacmanRight ;

        if(PocmanY==MazeSizeY-1){
            if(maze[PocmanX][0]==0 ){
                pacPixelX=25;
            }
        }
        else if(PocmanY<27){

            if(maze[PocmanX][PocmanY+1]==0){
                    pacPixelX+=5;
            }
        }
       if(Ball[PocmanX][PocmanY].check == 0 && maze[PocmanX][PocmanY]==0){

                Score++;
             Ball[PocmanX][PocmanY].check = 1 ;
            PlaySound("music\\pacman_chomp.wav",NULL,SND_ASYNC);

          //   maze[PocmanX][PocmanY]==2;

        }


}

void goLeft()
{
        pacman = PacmanLeft;
        if(PocmanY==0){

            if(maze[PocmanX][MazeSizeY-1]==0 && pacPixelX%25==0){

                pacPixelX=PocmanInitialX;
            }
            else{
                pacPixelX=MazeSizeY*25+25;
            }

        }
        else if(PocmanY>0){

            if(maze[PocmanX][PocmanY-1]==0){
                pacPixelX-=5;
            }
            if(maze[PocmanX][PocmanY-1]==1&& pacPixelX%25>=5){
                pacPixelX-=5;
            }
        }
       if(Ball[PocmanX][PocmanY].check == 0 && maze[PocmanX][PocmanY]==0){

            Score++;

            Ball[PocmanX][PocmanY].check = 1 ;
            PlaySound("music\\pacman_chomp.wav",NULL,SND_ASYNC);
          //  maze[PocmanX][PocmanY]==2;
        }
}


int main()
{
    Pinky.X  = pinkyInitialX , Pinky.Y = pinkyInitialY , Pinky.direction =1 ,Pinky.collision=0;
    Clyde.X = ClydeInitialX  , Clyde.Y = ClydeInitialY , Clyde.direction =1 ,Clyde.targetX=PocmanX,Clyde.targetY=PocmanY, Clyde.collision=0 ;
    Blinky.X= blinkyInitialX ,Blinky.Y = blinkyInitialY, Blinky.direction=1 ,Blinky.collision=0;
    Inky.X  = inkyInitialX   ,  Inky.Y = inkyInitialY  , Inky.direction  =1 , Inky.predirection = -1, Inky.targetX=1, Inky.targetY=(MazeSizeY-1)/2,Blinky.collision=0;

    MakeMaze();
    start1=0;
    PacImageChange();
    PointBall();
    goRight();
    pacWay();

    if(musicOn){
        if(gamestage==0){
            PlaySound("music\\pacman_beginning.wav",NULL,SND_ASYNC);
        }
    }



    iSetTimer(100,PacImageChange);
    iSetTimer(50,pacWay);
    iSetTimer(400,GHOST);
    iSetTimer(1000,frighten);
    iInitialize(screen_width,screen_height,"pacman");

}
