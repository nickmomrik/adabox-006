// ---------------------------------------------------------------------------
// Circuit Playground Light Paintbrush
// John Park for Adafruit Industries
//
// Modified by Nick Momrik
//
// Use the Circuit Playground as a long exposure photography light paintbrush
// tilt to change color adjust brightness with the buttons
//
 /*      +X 
 *       __
 *      /  \  
 * +Y  |    |  -Y
 *      \__/
 *      
 *       -X
 */
//
// MIT license, check LICENSE for more information
//
// ---------------------------------------------------------------------------

#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>

int brightness = 21;
int brightChange = 10;
int X;
int Y;
int tilt = 0;
int newTilt = 0;
uint32_t colors[] = {
  CircuitPlayground.strip.Color( 255, 0, 0 ),
  CircuitPlayground.strip.Color( 0, 255, 0 ),
  CircuitPlayground.strip.Color( 0, 0, 255 ),
  CircuitPlayground.strip.Color( 255, 255, 0 )
};

void setup() {
  CircuitPlayground.begin();
  changeColor();
  CircuitPlayground.setBrightness( brightness );
}

void loop() {
  if ( CircuitPlayground.leftButton() ) {
    if ( brightness > ( brightChange + 1 ) ) {
      brightness -= brightChange;
    }
    CircuitPlayground.setBrightness( brightness );
    CircuitPlayground.strip.show();

    while ( CircuitPlayground.leftButton() ) ;
  } else if ( CircuitPlayground.rightButton() ) {
    if ( brightness <= ( 255 - brightChange ) ) {
      brightness += brightChange;
    }
    CircuitPlayground.setBrightness( brightness );
    CircuitPlayground.strip.show();

    while ( CircuitPlayground.rightButton() ) ;
  }

  X = CircuitPlayground.motionX();
  Y = CircuitPlayground.motionY();

  if ( ( X >= 1 ) && ( Y < 1 ) ) {
    newTilt = 0;
  } else if ( ( X < 1 ) && ( Y < 1 ) ) {
    newTilt = 1;
  } else if ( ( X >= 1 ) && ( Y >= 1 ) ) {
    newTilt = 2;
  } else if ( ( X < 1 ) && ( Y >= 1 ) ) {
    newTilt = 3;
  }

  if ( newTilt != tilt ) {
    tilt = newTilt;
    changeColor();
  }
}

void changeColor() {
  for ( int i = 0; i < 10; ++i ) {
    CircuitPlayground.strip.setPixelColor( i, colors[ tilt ] );
  }

  CircuitPlayground.strip.show();
}

