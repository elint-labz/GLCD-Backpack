
#include <EEPROM.h>

#include "glcd.h"
/*
*
* GLCD
* 
* Firmware For Controlling GLCD using URAT Communication
* version 1.0
*Elint labz
*
*/
 // include glcd library
#include <fonts/allFonts.h> //library for font selection
int mat[20][3]={  {'s','t','d'},//command for setting dot
                  {'d','v','l'},//command for drawing vertical line
                  {'d','h','l'},//command for drawing horizontal line
                  {'d','r','t'},//command for drawing  rect
                  {'f','r','t'},//command for filling the rectangle
                  {'i','r','t'},//command for inverting the rectangle
                  {'d','c','l'},//command for drawing the circle
                  {'f','c','l'},//command for filling the circle
                  {'s','c','t'},// command for setting the cursor to perticular location
                  {'t','x','t'},//command for displaying text
                  {'c','l','r'},// command for clearing entire screen
                  {'b','u','d'},// command for selecting baud rate
                  {'s','f','t'}, //command to select different font
                  {'s','f','c'}, //command for selecting font colour
               };
char c[20],d[20],e[50];
int i,j,z,b,l,k,x,y,q,v,value;
int pos[4];
char a[5]={'b','a','u','d','='};
String s1,s2,s3;
void(* resetFunc) (void) = 0;         //reset function
void setup()
{
  pinMode(3,OUTPUT);
  digitalWrite(3,HIGH);
  GLCD.Init();// start the GLCD code
  GLCD.SelectFont(System5x7);//selecting the font
  value =EEPROM.read(0);
  
  switch(value)
  {
    case 0:
          Serial.begin(1200);
          GLCD.print("baudrate=1200");
          delay(1000);
          break;
    case 1:
          Serial.begin(2400);
          GLCD.print("baudrate=2400");
          delay(1000);
          break;
    case 2:
          Serial.begin(4800);
          GLCD.print("baudrate=4800");
          delay(1000);
          break;
    case 3:
          Serial.begin(9600);
          GLCD.print("baudrate=9600");
          
          delay(1000);
          break;

    case 4:
          Serial.begin(19200);
          GLCD.print("baudrate=19200");
          delay(1000);
          break;
    case 5:
          Serial.begin(28800);
          GLCD.print("baudrate=28800");
          delay(1000);
          break;
   case 6:
          Serial.begin(38400);
          GLCD.print("baudrate=38400");
          delay(1000);
          break;
   case 7:
          Serial.begin(57600);
          GLCD.print("baudrate=57600");
          delay(1000);
          break;
   case 8:
          Serial.begin(115200);
          GLCD.print("baudrate=115200");
          delay(1000);
          break;
   default :
          Serial.begin(9600);
          GLCD.print("baudrate=9600");
          delay(1000);
          break;
  }
  GLCD.ClearScreen();//clearing glcd screen
  Clear();
  GLCD.CursorToXY(0,30);
  GLCD.print("welcome to Elint labz"); // displaying the text on screen
  delay(2000);
  GLCD.ClearScreen();
  GLCD.CursorToXY(0,30);
  GLCD.print("firmware version 0.5");
  delay(2000);
  GLCD.ClearScreen();
  Clear();
}
void loop()
{
  if (Serial.available())
  {
    for(i=0;i<20;i++)
    {
      delay(100);
      d[i]=Serial.read();
     // Serial.print(d[i]);
    }
  }
  for(l=0;l<20;l++)
  {
    z=0;
    for(k=0;k<3;k++)
    {
      if(d[k]==mat[l][k])
      {
        z++;
        if(z==3)
        {
          switch(l)
          {
            case 0:
            dot();
            break;
            case 1:
            verticalline();
            break;
            case 2:
            horizontalline();
            break;
            case 3:
            rectangle();
            break;
            case 4:
            fillrectangle();
            break;
            case 5:
            invertrectangle();
            break;
            case 6:
            circle();
            break;
            case 7:
            fillcircle();
            break;
            case 8:
            setcursor();
            break;
            case 9:
            text();
            break;
            case 10:
            clr();
            break;
            case 11:
            bud();
            break;
            case 12:
            setfont();
            break;
            case 13:
            fontcolor();
            break;
          }
        }
      }
    }
  }
}
// function used to set a dot
void dot()
{
  Serial.println("OK");
  xy();
  v=d[(pos[1])+1]-'0';
  if(v==0)
  {
    GLCD.SetDot(x,y,WHITE);
  }
  else if(v==1)
  {
    GLCD.SetDot(x,y,BLACK);
  }
  Clear();
}
//function used to draw vertical line
void verticalline()
{
  Serial.println("OK");
  xy();
  twocomma();
  v=d[(pos[2]+1)]-'0';
  if(v==0)
  {
    GLCD.DrawVLine(x,y,b,WHITE);
  }
  else if(v==1)
  {
    GLCD.DrawVLine(x,y,b,BLACK);
  }
  Clear();
}
//function used to draw horizontal line
void horizontalline()
{
  Serial.println("OK");
  xy();
  if((pos[2]-pos[1])==2)
  {
    b=d[(pos[1]+1)]-'0';
  }
  else if((pos[2]-pos[1])==3)
  {
  b=d[(pos[1]+1)]-'0';
  v=d[(pos[1]+2)]-'0';
  b=b*10+v;
  }
  else if((pos[2]-pos[1]==4))
  {
      b=d[(pos[1]+1)]-'0';
      v=d[(pos[1]+2)]-'0';
      q=d[(pos[1]+3)]-'0';
      b=b*100+v*10+q;
  }
  v=d[(pos[2]+1)]-'0';
  if(v==0)
  {
    GLCD.DrawHLine(x,y,b,WHITE);
  }                       
  else if(v==1)
  {
    GLCD.DrawHLine(x,y,b,BLACK);
  }
  Clear();
}
//function used to draw rectangle
void rectangle()
{
  Serial.println("OK");
  xy();
  threecomma();
  
  v=d[(pos[3]+1)]-'0';
  if(v==0)
  {
    GLCD.DrawRect(x,y,b,q,WHITE);
  }
  else if(v==1)
  {
    GLCD.DrawRect(x,y,b,q,BLACK);
  }
  Clear();
}
//function used to draw rectangle and fill it
void fillrectangle()
{
  Serial.println("OK");
  xy();
  threecomma();
  v=d[(pos[3]+1)]-'0';
  if(v==0)
  {
    GLCD.FillRect(x,y,b,q,WHITE);
  }
  else if(v==1)
  {
    GLCD.FillRect(x,y,b,q,BLACK);
  }
  Clear();
}
//function used to draw rectangle and keeps on inverting it
void invertrectangle()
{
  Serial.println("OK");
  xy();
  threecomma();
  GLCD.InvertRect(x,y,b,q);
  delay(100);
  Clear();
}
//function used to draw circle
void circle()
{
  Serial.println("OK");
  xy();
  twocomma();
  v=d[(pos[2]+1)]-'0';
  if(v==0)
  {
    GLCD.DrawCircle(x,y,b,WHITE);
  }
  else if(v==1)
  {
    GLCD.DrawCircle(x,y,b,BLACK);
  }
  Clear();
}
//function used to draw circle and fill it
void fillcircle()
{
  Serial.println("OK");
  xy();
  twocomma();
  v=d[(pos[2]+1)]-'0';
  if(v==0)
  {
    GLCD.FillCircle(x,y,b,WHITE);
  }
  else if(v==1)
  {
    GLCD.FillCircle(x,y,b,BLACK);
  }
  Clear();
}
////function used to set cursor to the coordinate
void setcursor()
{
  Serial.println("OK");
  xy();
  GLCD.CursorToXY(x,y);
  delay(100);
  Clear();
}
//function used to display text
void text()
{
  Serial.println("Enter the text");
  while(1)
  {
    if (Serial.available()>1)
    {
      for(i=0;i<30;i++)
      {
        e[i]=Serial.read();
        if(e[i]==';')
        {
          Clear();
          Serial.println("Text terminated successfully");
          return;
        }
        GLCD.print(e[i]);
      }
      
    }  
}
Clear();
}

void fontcolor()
{
  Serial.println("OK");
  d[4]=d[4]-'0';
   if(d[4]==0)
   {
     GLCD.SetFontColor(WHITE);
   }
   else if(d[4]==1)
   {
     GLCD.SetFontColor(BLACK);
   }
   Clear();   
}

void xy()
{
  j=0;
  for(i=5;i<18;i++)
  {
    if(d[i]==',')
    {
      pos[j]=i;
      j++;
    }  
  }
  if(pos[0]==5 && pos[1]==7)
  {
    x=d[4]-'0';
    y=d[6]-'0';
  }
  else if(pos[0]==6 && pos[1]==8)
  {
    x=d[4]-'0';
    q=d[5]-'0';
    x= x*10+q;
    y=d[7]-'0';
  }
  else if(pos[0]==7 && pos[1]==9)
  {
     x=d[4]-'0';
    q=d[5]-'0';
    v=d[6]-'0';
    x= x*100+q*10+v;
     y=d[8]-'0';
  }
  else if(pos[0]==5 && pos[1]==8)
  {
   x=d[4]-'0';
   y=d[6]-'0';
   q=d[7]-'0';
   y=y*10+q;
  }
  else if(pos[0]==6 && pos[1]==9)
  {
    x=d[4]-'0';
    q=d[5]-'0';
    x= x*10+q;
    y=d[7]-'0';
   q=d[8]-'0';
   y=y*10+q;
  }
  else if(pos[0]==7 && pos[1]==10)
  {
    x=d[4]-'0';
    q=d[5]-'0';
    v=d[6]-'0';
    x= x*100+q*10+v;
    y=d[8]-'0';
    q=d[9]-'0';
    y=y*10+q;
  }
    
}
//function is used to clear the screen
void clr()
{
  Serial.println("OK");
  GLCD.ClearScreen();
  Clear();
}

void Clear()
{
  for(i=0;i<20;i++)
  {
    c[i]=' ';
    d[i]=' ';
    e[i]=' ';
    z=0;
  }
}

void setfont()
{ 
  Serial.println("OK");
  q=d[4]-'0';
  v=d[6]-'0';
  switch(q)
  {
    case 0:
    if(v==1)
    {
      GLCD.SelectFont( Arial_bold_14, BLACK);
    }
    else if(v==0)
    {
      GLCD.SelectFont( Arial_bold_14, WHITE);
    }
    break;
    
    case 1:
    if(v==1)
    {
      GLCD.SelectFont( Arial14, BLACK);
    }
    else if(v==0)
    {
      GLCD.SelectFont( Arial14, WHITE);
    }
    break;
    
    case 2:
    if(v==1)
    {
      GLCD.SelectFont( Corsiva_12, BLACK);
    }
    else if(v==0)
    {
      GLCD.SelectFont(Corsiva_12, WHITE);
    }
    break;
    
    case 3:
    if(v==1)
    {
      GLCD.SelectFont(fixednums7x15, BLACK);
    }
    else if(v==0)
    {
      GLCD.SelectFont(fixednums7x15, WHITE);
    }
     break;
     
    case 4:
    if(v==1)
    {
      GLCD.SelectFont( fixednums8x16, BLACK);
    }
    else if(v==0)
    {
      GLCD.SelectFont(fixednums8x16, WHITE);
    }
     break;
     
    case 5:
    if(v==1)
    {
      GLCD.SelectFont( fixednums15x31, BLACK);
    }
    else if(v==0)
    {
      GLCD.SelectFont(fixednums15x31, WHITE);
    }
     break;
     
    case 6:
    if(v==1)
    {
      GLCD.SelectFont( SystemFont5x7, BLACK);
    }
    else if(v==0)
    {
      GLCD.SelectFont(SystemFont5x7, WHITE);
    }
     break;
  }
  Clear();
}

void bud()
{
  
  Serial.println("OK");
  q=d[4]-'0';
  EEPROM.write(0,q);
  delay(50);
  resetFunc();
}

void twocomma()
{
  if((pos[2]-pos[1])==2)
  {
    b=d[(pos[1]+1)]-'0';
  }
  else if((pos[2]-pos[1])==3)
  {
  b=d[(pos[1]+1)]-'0';
  v=d[(pos[1]+2)]-'0';
  b=b*10+v;
  }
}

void threecomma()
{
  if((pos[2]-pos[1])==2)
  {
    b=d[(pos[1]+1)]-'0';
  }
  else if((pos[2]-pos[1])==3)
  {
  b=d[(pos[1]+1)]-'0';
  v=d[(pos[1]+2)]-'0';
  b=b*10+v;
  }
  else if((pos[2]-pos[1]==4))
  {
      b=d[(pos[1]+1)]-'0';
      v=d[(pos[1]+2)]-'0';
      q=d[(pos[1]+3)]-'0';
      b=b*100+v*10+q;
  }
  
  if((pos[3]-pos[2])==2)
  {
    q=d[(pos[1]+1)]-'0';
  }
  else if((pos[3]-pos[2])==3)
  {
  q=d[(pos[1]+1)]-'0';
  v=d[(pos[1]+2)]-'0';
  q=q*10+v;
  }
}
