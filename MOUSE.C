#include<dos.h>
#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
union REGS i,o;
 int gd=DETECT,gm, maxx,maxy,x,y,button,x1,y1,a,b;
void showmouseptr()
  {
  i.x.ax=1;
  int86(0x33,&i,&o);
  return;
  }
void getmousepos(int *button, int *x, int*y)
  {
  i.x.ax=3;
  int86(0x33,&i,&o);
  *button=o.x.bx;
  *x=o.x.cx;
  *y=o.x.dx;
  return;
  }
void hide()
{
i.x.ax=2;
int86(0x33,&i,&o);
return;
}
void restrictmouse(int x1,int y1,int x2,int y2)
 {
 i.x.ax=7;
 i.x.cx=x1;
 i.x.dx=x2;
 int86(0x33,&i,&o);

 i.x.ax=8;
 i.x.cx=y1;
 i.x.dx=y2;
 int86(0x33,&i,&o);
 return;
 }
/*initialize mouse pointer*/
int initmouse()
 {
 i.x.ax=0;
 int86(0x33,&i,&o);
 return(o.x.ax);
}
void draw()
{
 x1=x; y1=y;//x1 y1 should start from new coordinate x and y
		while(button==1)
		{
		hide();
		//to draw free hand line
		setcolor(RED);
		line(x,y,x1,y1);
		x=x1; y=y1; //trick the previous point of the line
		//is following the next point to be drawn
		getmousepos(&button,&x1,&y1);
		showmouseptr();
		}
return;
}
void cir()
{
	/*to draw free hand circle*/
		while(button==2)
		{
		hide();
		setcolor(BLUE);
		circle(x,y,20);
		getmousepos(&button,&x,&y);
		showmouseptr();
		}
	       return;
}
void main()
{
 initgraph(&gd,&gm,"c:\\tc\\bgi");
 maxx=getmaxx();
 maxy=getmaxy();
 rectangle(0,56,maxx,maxy);
 gotoxy(26,1);
 printf("Mouse Demonstration Program");
   if(initmouse()==0)
   {
   closegraph();
   restorecrtmode();
   printf("\nMouse driver not loaded");
   exit(1);
   }
 restrictmouse(0,0,maxx-1,maxy-1);
 showmouseptr();
 gotoxy(1,2);
 printf("Left Button");
 gotoxy(2,3);
 printf("Draw");
 gotoxy(15,2);
 printf("Right Button");
 gotoxy(16,3);
 printf("Circle");
 rectangle(118,32,168,55);
 gotoxy(30,3);
 printf("Exit");
 rectangle(220,32,270,55);
 gotoxy(55,3);
 printf("Press any key to exit...");
 rectangle(0,32,50,55);

     while(!kbhit())
	{
	getmousepos(&button,&x,&y);
	gotoxy(65,2);
	printf("X =%3d Y=%3d",x,y);
	getmousepos(&button,&x,&y);
	for(a=0;a<=maxx;a++)
	{
	for(b=70;b<=maxy;b++)
	{
	if(a==x&&b==y)
	{
	while(button==2)
	{
	cir();

	}
	while(button==1)
	{
	draw();
	showmouseptr();
	}
	}}}
	if(x>=220&&x<=270&&y>=32&&y<=55)
	{
	while(button==1)
	exit(1);
	}}
getch();
}
