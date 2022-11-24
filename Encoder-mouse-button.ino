
// **  Trying to make a mouse encoder scroll wheel with 4 buttons.

#include <Mouse.h>
#include <Encoder.h>

static unsigned encA=2, encB=3, encBTN=4;
static unsigned scrollFactor=4;


Encoder myEnc(encA, encB);

long oldPosition  = -999;

const int mouseButtonLeft = 6;
const int mouseButtonRight = 8;
int buttonState = 0;   

void setup(){
  
  pinMode(mouseButtonLeft,INPUT_PULLUP);
  pinMode(mouseButtonRight,INPUT_PULLUP);  
  //pinMode(encBTN,INPUT);
  Serial.begin(9600);
  Mouse.begin();   
}

int change=0;

void loop(){

int clickStateLeft = digitalRead(mouseButtonLeft);
int clickStateRight = digitalRead(mouseButtonRight);

  
  if (clickStateLeft == HIGH) {
    if (!Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.press(MOUSE_LEFT);
      Serial.println("mouseButton_Left");  
      delay(200);
    }
  }
  else {   
    if (Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.release(MOUSE_LEFT);
    }
  }
    if (clickStateRight == HIGH) {
    if (!Mouse.isPressed(MOUSE_RIGHT)) {
      Mouse.press(MOUSE_RIGHT);
      Serial.println("mouseButton_Right");
    delay(200);
    }
  }
  else {
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
    
  if(change<-3 || change>3) {
    Mouse.move(0,0,+change/scrollFactor);
    change=0;
      }
      }  
