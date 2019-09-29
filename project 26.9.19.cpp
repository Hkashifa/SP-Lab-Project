#include<graphics.h>
int main()
{
    int gd=DETECT,gm;
    initgraph(&gd,&gm,"c:\\tc\\bgi");
    int page=0,t_y=-300;
    //car variables
    int C_x=0,M_Speed=5;
    int C_y=0;
    while(1)
    {
    setactivepage(page);
    setvisualpage(1-page);
    cleardevice();


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
        rectangle(185,10+i+t_y,205,50+i+t_y);
        rectangle(290,10+i+t_y,310,50+i+t_y);
        rectangle(395,10+i+t_y,415,50+i+t_y);
        setfillstyle(1,WHITE);
        floodfill(186,11+i+t_y,WHITE);
        floodfill(291,11+i+t_y,WHITE);
        floodfill(396,11+i+t_y,WHITE);
    }
    t_y+=15;
    if(t_y>500)
    {
        t_y=-500;
    }
    //for life and points
    settextstyle(10,0,2);

    outtextxy(10,40,"POINTS:");

    setfillstyle(1,WHITE);


    outtextxy(100,40,"0");


     //CAr
    setcolor(BLACK);
    setfillstyle(1,RED);
    rectangle(300+C_x,400+C_y,340+C_x,460+C_y);
    floodfill(301+C_x,401+C_y,BLACK);

    //Front
    setfillstyle(1,BROWN);
    rectangle(305+C_x,385+C_y,335+C_x,400+C_y);
    floodfill(306+C_x,386+C_y,BLACK);

    setfillstyle(1,BLACK);
    rectangle(305+C_x,405+C_y,335+C_x,455+C_y);
    floodfill(306+C_x,406+C_y,BLACK);

    //wheels
    setfillstyle(1,BLACK);
    pieslice(305+C_x,392+C_y,90,270,6);
    pieslice(337+C_x,392+C_y,270,90,5);

    if(GetAsyncKeyState(VK_LEFT))
        C_x-=M_Speed;
    else if(GetAsyncKeyState(VK_RIGHT))
        C_x+=M_Speed;
    if(GetAsyncKeyState(VK_UP))
        C_y-=M_Speed;
        else if(GetAsyncKeyState(VK_DOWN))
        C_y+=M_Speed;
    page=1-page;
    delay(20);
    }

    getch();

}
