#include<dos.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<stdio.h>
FILE *fp;
struct snk
{
int cx,cy;
int d;
struct snk *l;
};
void menu();
void load();
//void inst();
union REGS i,o;
int s=0,ch,w=150;
int ck(struct snk *,int,int);
void start();
void mv(struct snk *,int,int,int);
void rec(int x1,int y1,int x2,int y2,int p)
{
int i;
for(i=x1;i<=x2;i++)
{
putpixel(i,y1,p);
putpixel(i,y2,p);
}
for(i=y1;i<=y2;i++)
{
putpixel(x1,i,p);
putpixel(x2,i,p);
}
}
void main()
{
int gdriver = DETECT,gmode,button,x,y,tx,ty,sz,image;
	initgraph(&gdriver,&gmode,"C:\\Turboc3\\BGI");
load();
menu();
}
void start()
{
struct snk *p,*t;
int gd=DETECT,gm;
int x,y,i=0;
char c;
struct snk *t1;
int n,f1,f2;
clrscr();
initgraph(&gd,&gm,"C:\\turboc3\\bgi");
setbkcolor(GREEN);
p=(struct snk *)malloc(sizeof(struct snk));
p->cx=20;
p->cy=20;
p->d=77;
p->l=NULL;
x=getmaxx();
y=getmaxy();
f1=random(32)*20;
f2=random(24)*20;
rec(f1,f2,f1+20,f2+20,BLUE);
rec(p->cx,p->cy,p->cx+20,p->cy+20,RED);
while(1)
{
rec(f1,f2,f1+20,f2+20,BLUE);
rec(p->cx,p->cy,p->cx+20,p->cy+20,RED);
delay(w);
if((p->l)!=NULL)
{
if((p->l->l)!=NULL)
{
if(ck(p->l->l,p->cx,p->cy))
goto finish;
}
}
t=p;
while((t->l)!=NULL)
t=t->l;
rec(t->cx,t->cy,t->cx+20,t->cy+20,BLACK);
if(((p->cx)==f1)&&((p->cy)==f2))
i=1;
if(kbhit())
{
c=getch();
n=c;
if(c=='x')
goto finish;
}
else
n=p->d;
if(i==1)
{
i=0;
s++;
w=w-2;
again: f1=random(32)*20;
f2=random(24)*20;
if(ck(p,f1,f2))
goto again;

t1=(struct snk *)malloc(sizeof(struct snk));
t=p;
while((t->l)!=NULL)
t=t->l;
t1->cx=t->cx;
t1->cy=t->cy;
t1->d=t->d;
t1->l=NULL;
mv(p,n,x,y);
t->l=t1;
}
else
mv(p,n,x,y);
}
finish:

fp=fopen("highscore.txt","r+");
fseek(fp,0L,0);
fscanf(fp,"%d",&ch);
    if(s>ch)
    {
      fseek(fp,0L,0);
      fp=fopen("highscore.txt","w");
fprintf(fp,"%d",s);
fclose(fp);
      }

fp=fopen("highscore.txt","r");
printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\n\n\n\t\t\t      HIGHSCORE=");
while((ch=fgetc(fp))!=EOF)
putchar(ch);
fclose(fp);

printf("\n\t\t\t\t\t\t\t\t\t\t    GAME OVER...........");
printf("\n\t\t\t\t\t\t\t\t\t\t    SCORE = %d",s);
//delay(5000);
if(kbhit())
{
menu();
}
getch();
getch();
}
void mv(struct snk *p,int c,int x,int y)
{
struct snk *t;
int x1,y1,x2,y2;
int d1,d2;
t=p->l;
x1=p->cx;
y1=p->cy;
d1=p->d;
while(t!=NULL)
{
x2=t->cx;
y2=t->cy;
d2=t->d;
t->cx=x1;
t->cy=y1;
t->d=d1;
x1=x2;
y1=y2;
d1=d2;
t=t->l;
}
if((c==77)&&((p->l->d)==75))
c=75;
if((c==75)&&((p->l->d)==77))
c=77;
if((c==80)&&((p->l->d)==72))
c=72;
if((c==72)&&((p->l->d)==80))
c=80;
if(c==77)
{
p->cx+=20;
if((p->cx)>=x)
p->cx=0;
}
else
if(c==75)
{
p->cx-=20;
if((p->cx)<0)
p->cx=x-x%20;
}
else
if(c==80)
{
p->cy+=20;
if((p->cy)>=y)
p->cy=0;
}
else
if(c==72)
{
p->cy-=20;
if((p->cy)<0)
p->cy=y-y%20;
}
p->d=c;
}
int ck(struct snk *p,int f1,int f2)
{
struct snk *t=p;
int f=0;
while((t!=NULL)&&(f==0))
{
if(((t->cx)==f1)&&((t->cy)==f2))
f=1;
t=t->l;
}
return(f);
}
void menu()
{
int gdriver = DETECT,gmode,button,x,y,tx,ty,sz,image;
initgraph(&gdriver,&gmode,"C:\\Turboc3\\BGI");
getmaxx();
getmaxy();
setbkcolor(RED);
setcolor(WHITE);
outtextxy(225,120,"!!!!!SNAKE GAME!!!!!");
outtextxy(220,460,"Copyrights AAC GRIET");
rectangle(480,380,640,478);
outtextxy(490,390,"DEVELOPERS:");
rectangle(240,200,360,240);
outtextxy(500,400,"1)HARSHA");
outtextxy(500,410,"2)PRANEETH");
outtextxy(500,420,"3)VENKAT");
outtextxy(500,430,"4)VEDANT");
outtextxy(480,440,"Mentor:Dr.Vijaylatha");
outtextxy(560,450,"(HOD)");
fp=fopen("highscore.txt","r");
printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\n\n\n\t\t\t       highscore is");
while((ch=fgetc(fp))!=EOF)
putchar(ch);
fclose(fp);
outtextxy(285,220,"PLAY");    /*playoption*/
rectangle(230,260,370,300);
rectangle(240,320,360,360);
outtextxy(285,340,"Quit");
rectangle(240,320,360,360);    /*quitoption*/
showmouseptr();
while(1)
{
getmousepos(&button,&tx,&ty);
if(((button&1)==1) && (tx>=240 && tx<=360 && ty>=200 && ty<=240))
 {
  start();
 }
else
     {
       if(((button&1)==1) && (tx>=240 && tx<=360 && ty>=320 && ty<=360))
       {
	exit(0);
       }
       else
	  {
	   continue;
	  }

   }
}
getch();
closegraph();
restorecrtmode();
}
void load()
{
 int x,y,i,e,c=150;
 int gdriver=DETECT,gmode,d;
 initgraph(&gdriver,&gmode,"C:\\Turboc3\\BGI");
 cleardevice();
 x=getmaxx()/2;
 y=getmaxy()/2;
 settextstyle(TRIPLEX_FONT,HORIZ_DIR,3);
 setbkcolor(RED);
 setcolor(BLUE);
for(e=0;e<6;e++) //Give ur desired value in conditional statement->value=time
 {
  for(i=50;i<100;i++)
  {
    setcolor(BLUE);
    settextstyle(SMALL_FONT, HORIZ_DIR,8);
    outtextxy(x-60,y-10,"Loading...");
    settextstyle(SMALL_FONT, HORIZ_DIR, 5);
    outtextxy(x-60,y-20,"  >Please Wait<  ");
    circle(x,y,i);
    circle(x,y,c);
    c--;
    cleardevice();
  }
  }
  menu();
  getch();
 closegraph();
 restorecrtmode();
 }


/*mouse pointer*/
showmouseptr()
{
 i.x.ax=1;
 int86(0x33,&i,&o);
return;
}
/*mouse position & button*/
getmousepos(int *button,int *x,int *y)
{
i.x.ax=3;
int86(0x33,&i,&o);
*button=o.x.bx;
*x=o.x.cx;
*y=o.x.dx;
return;
}
