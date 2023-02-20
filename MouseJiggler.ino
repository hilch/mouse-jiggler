// https://github.com/hilch/mouse-jiggler

//  Pin 5 ---o
//  Pin 4 ---o
//  Pin 3 ---o              ^^ (LED)
//  Pin 2 ---o----[ 1k ]---|<----o---- VCC
//  Pin 1 ---o
//  Pin 0 ---o


#include <DigiMouse.h>

#define LED_TIME  1000
#define LED_FLASH  100
#define MOUSE_TIME 20000

bool direction;
signed long led_timer;
signed long mouse_timer;



void setup() {
  DigiMouse.begin(); 
  pinMode(2, OUTPUT);    
  led_timer = millis();
  mouse_timer = millis();
  direction = false;
}

void loop() {
  signed long time = millis();

  if( (time - led_timer) > (LED_TIME+LED_FLASH) ){
    digitalWrite(2,HIGH); // switch LED off
    led_timer = time;
  }
  else if( (time - led_timer) > LED_TIME ){
    digitalWrite(2,LOW); // switch LED on 
  }

  if( (time - mouse_timer) > MOUSE_TIME ){
    if( direction ){
      DigiMouse.moveX(1); // one pixel to the right
    }
    else {  // one pixel to the left
      DigiMouse.moveX(-1); // one pixel to the left
    }
    direction = !direction;
    for( int n = 0; n < 4; ++n ){
      digitalWrite(2,LOW); // switch LED on
      DigiMouse.delay(LED_FLASH);    
      digitalWrite(2,HIGH); // switch LED off
      DigiMouse.delay(LED_FLASH);        
    }
    mouse_timer = time;
  }

  DigiMouse.update(); 

}
