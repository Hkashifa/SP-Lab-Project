#include<graphics.h>
int main()
{
    int gd=DETECT,gm;
    initgraph(&gd,&gm,"c:\\tc\\bgi");
    //for background
    setcolor(GREEN);
    rectangle(0,0,1000,1000);
    setfillstyle(1,GREEN);
    floodfill(1,1,GREEN);
    //creating track
    setcolor(WHITE);
    rectangle(100,-1,500,500);
    setfillstyle(1,8);
    floodfill(201,0,WHITE);
    //line in roads
    for(int i=0;i<500;i+=65)
    {
        rectangle(185,10+i,205,50+i);
        rectangle(290,10+i,310,50+i);
        rectangle(395,10+i,415,50+i);
        setfillstyle(1,WHITE);
        floodfill(186,11+i,WHITE);
        floodfill(291,11+i,WHITE);
        floodfill(396,11+i,WHITE);
    }
    //points
    settextstyle(10,0,2);
    outtextxy(10,40,"POINTS:");


    outtextxy(100,40,"0");
    getch();

}
