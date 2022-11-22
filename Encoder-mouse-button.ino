 // This program is free software: you can redistribute it and/or modify
 // it under the terms of the GNU General Public License as published by
 // the Free Software Foundation, either version 3 of the License, or
 // (at your option) any later version.
 //
 // This program is distributed in the hope that it will be useful,
 // but WITHOUT ANY WARRANTY; without even the implied warranty of
 // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 // GNU General Public License for more details.
 //
 // You should have received a copy of the GNU General Public License
 // along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <Mouse.h>
#include <Encoder.h>

static unsigned encA=2, encB=3, encBTN=4;

//scaling:
static unsigned hFactor=10, vFactor=5, scrollFactor=4;
unsigned h=0, v=255;

Encoder myEnc(encA, encB);

long oldPosition  = -999;

const int mouseButtonLeft = 6;
const int mouseButtonRight = 8;


int buttonState = 0;   

void setup(){
  
  pinMode(mouseButtonLeft, INPUT);
  pinMode(mouseButtonRight, INPUT);  
  pinMode(encBTN,INPUT);
  Serial.begin(9600);
  Mouse.begin();   
}

int change=0;
int hChange=0;
int vChange=0;


void loop(){

int clickStateLeft = digitalRead(mouseButtonLeft);
int clickStateRight = digitalRead(mouseButtonRight);

  // if the mouse button is pressed:
  if (clickStateLeft == HIGH) {
    // if the mouse is not pressed, press it:
    if (!Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.press(MOUSE_LEFT);
      Serial.println("mouseButton_Left");  
      delay(200);
    }
  }
  // else the mouse button is not pressed:
  else {
    // if the mouse is pressed, release it:
    if (Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.release(MOUSE_LEFT);
    }
  }
    if (clickStateRight == HIGH) {
    // if the mouse is not pressed, press it:
    if (!Mouse.isPressed(MOUSE_RIGHT)) {
      Mouse.press(MOUSE_RIGHT);
      Serial.println("mouseButton_Right");
    delay(200);
    }
  }
  // else the mouse button is not pressed:
  else {
    // if the mouse is pressed, release it:
    if (Mouse.isPressed(MOUSE_RIGHT)) {
      Mouse.release(MOUSE_RIGHT);
    }
  }

 unsigned long newPosition = myEnc.read();

    if (newPosition != oldPosition)
    {
      change += newPosition-oldPosition;
    oldPosition = newPosition;
    }
    
  if(change<-3 || change>3) 

      if(digitalRead(encBTN))  //VALUE
      {
        vChange=change*vFactor;
        if((signed)v+vChange<0) v=0; //prevent int underflow
        else if(v+vChange>255) v=255; //prevent int overflow
        else v+=vChange;
      }

      else //HUE
      {
        hChange=change*hFactor;
        if((signed)h+hChange<0) h=1541; //prevent int underflow
            else if(h+hChange>1541) h=0; //prevent int overflow
        else h+=hChange;
  
  {      Mouse.move(0,0,+change/scrollFactor);
    
      }
      Serial.print("pos: ");
      Serial.println(newPosition);
      Serial.print("change: ");
      Serial.println(change);

      Serial.print("Scroll: ");
      Serial.println(-change/scrollFactor);
      Serial.println();

      change=0;
  }
   }

