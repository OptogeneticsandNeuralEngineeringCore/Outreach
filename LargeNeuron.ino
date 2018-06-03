/*
   Large Neuron for Outreach
   Optogenetics and Neural Engineering Core ONE Core
   University of Colorado School of Medicine
   6/3/18
   See optogenetic.ucdenver.edu for more information, including a detailed write up
   Special thanks to Samantha Lewis for coding

   Here is the code for the LARGE NEURON. It is an interactive display with lots of hidden teaching oppertunities. The main focus is to show information flow (and summation) through a single neuron, but there's flashing lights, giant (smashable) buttons, and bubbles!!! Kids love bubbles!!! Encourage everyone, all ages, all levels of education to learn something about these 80 billion little cells that somehow makes a human brain.

  It is a simple and fun project for students, teachers, and research assistances to undertake and teaches simple engineering along the way.  Play with microcontrollers (Arduino), do some simple soldering, hack a bubble machine.

  Two big (smashable) buttons sit at the input of two dendrites. Smash one (stimulate) and 'information' is propegated to the cell body as shown by 'moving' lights. Kind of cool. Smash the other and it does the same. OK. Smash BOTH within 2.5 seconds, and they both send lights down, but now the neuron sums, and decides to send out an action potential down the axon (more moving lights). But there are glial cells which speed it up. At the axon end, the neuron need to send out neurotransmitter, which is of course BUBBLES!!!

  The neuron itself can be made from tubing, a simple painting, or paper mache.
*/
   
// First we include the libraries for the LEDs and Serial Peripheral Interface
#include "LPD8806.h"
#include "SPI.h"

// Here's the number of RGB LEDs in each strand.
int nLEDs = 20;
int nLEDs2 = 20;
int nLEDs3 = 48;

// Here's where we define the connections with the arduino.
int dataPin  = 2;
int clockPin = 3;
int dataPin2 = 6;
int clockPin2 = 7;
int dataPin3 = 8;
int clockPin3 = 9;
int button1 = 4;
int button2 = 5;
int bubblePin = 10;

// Here we set up the LED strips.
// First parameter is the number of LEDs in the strand.  The LED strips
// are 32 LEDs per meter but you can extend or cut the strip.  Next two
// parameters are SPI data and clock pins:
LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);
LPD8806 strip2 = LPD8806(nLEDs2, dataPin2, clockPin2);
LPD8806 strip3 = LPD8806(nLEDs3, dataPin3, clockPin3);

//Timing Parameters
int Button1_time = 0;
int Button2_time = 23000;

// Da set up loop. Define our inputs/outputs and start the LEDs up
void setup() {
  pinMode(button1,INPUT);
  pinMode(button2,INPUT);
  pinMode(bubblePin,OUTPUT);
  strip.begin();
  strip2.begin();
  strip3.begin();
  strip.show();
  strip2.show();
  strip3.show();
}

// The main loop. Runs continusouly when the arduino is powered
void loop() {
 if(digitalRead(button1)==HIGH)  // If the first button is pushed
 {
 colorChase(strip.Color(0,127,127),(0,0,127),(127,0,127),50); // Show some moving LEDS (code below)
 Button1_time = millis();  // Start a timer
 }
 if(digitalRead(button2)==LOW)
 {
 colorChase2(strip2.Color(0,127,127),(0,0,127),(127,0,127),50);  // Show some moving LEDS (code below)
 Button2_time = millis();  // Start a timer
 }
 if(abs(Button1_time-Button2_time)<=2500) // Compare the times, if less than 2.5 sec
 {
  colorChase3(strip3.Color(0,127,127),(0,0,127),(127,0,127),50);  // Show some moving LEDS and do the bubble thing (code below)
 }
}

// Chase one dot down the full strip. Note that this is the same code as the next block (the dendrites do the same thing)
void colorChase(uint32_t c,uint32_t c1,uint32_t c2, uint8_t wait) {
  int i;

  // Start by turning all pixels off:
  for(i=0; i<strip.numPixels(); i++) strip.setPixelColor(i, 0);

  for(i=0; i<strip.numPixels()/nLEDs; i++) {
  strip.setPixelColor(i, c); // Set new pixel 'on'
  strip.show();              // Refresh LED states
  strip.setPixelColor(i, 0); // Erase pixel, but don't refresh!
  delay(wait);
  }
  for(i=strip.numPixels()/nLEDs; i<2*strip.numPixels()/nLEDs; i++) {
  strip.setPixelColor(i, c1,i-nLEDs,c); // Set new pixel 'on'
  strip.show();              // Refresh LED states
  strip.setPixelColor(i, 0,i-nLEDs,0); // Erase pixel, but don't refresh!
  delay(wait);
  }
  for(i=2*strip.numPixels()/nLEDs; i<3*strip.numPixels()/nLEDs; i++) {
  strip.setPixelColor(i, c2,i-nLEDs,c1); // Set new pixel 'on'
  strip.setPixelColor(i-nLEDs*2,c2);
  strip.show();              // Refresh LED states
  strip.setPixelColor(i, 0,i-nLEDs,0); // Erase pixel, but don't refresh!
  strip.setPixelColor(i-nLEDs*2,0);
  delay(wait);
  }

  for(i=3*strip.numPixels()/nLEDs; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c,i-1,c1); // Set new pixel 'on'
    strip.setPixelColor(i-2,c2);
    strip.show();              // Refresh LED states
    strip.setPixelColor(i, 0,i-1,0); // Erase pixel, but don't refresh!
    strip.setPixelColor(i-2, 0);
    delay(wait);
  }
  for(i=0;i<strip.numPixels();i++)
  {
    strip.setPixelColor(i,0);
  }

  strip.show(); // Refresh to turn off last pixel
}

Same as above
void colorChase2(uint32_t c,uint32_t c1,uint32_t c2, uint8_t wait) {
  int i;

  // Start by turning all pixels off:
  for(i=0; i<strip2.numPixels(); i++) strip2.setPixelColor(i, 0);

  for(i=0; i<strip.numPixels()/nLEDs2; i++) {
  strip2.setPixelColor(i, c); // Set new pixel 'on'
  strip2.show();              // Refresh LED states
  strip2.setPixelColor(i, 0); // Erase pixel, but don't refresh!
  delay(wait);
  }
  for(i=strip2.numPixels()/nLEDs2; i<2*strip2.numPixels()/nLEDs2; i++) {
  strip2.setPixelColor(i, c1,i-nLEDs2,c); // Set new pixel 'on'
  strip2.show();              // Refresh LED states
  strip2.setPixelColor(i, 0,i-nLEDs2,0); // Erase pixel, but don't refresh!
  delay(wait);
  }
  for(i=2*strip2.numPixels()/nLEDs2; i<3*strip2.numPixels()/nLEDs2; i++) {
  strip2.setPixelColor(i, c2,i-nLEDs2,c1); // Set new pixel 'on'
  strip2.setPixelColor(i-nLEDs2*2,c2);
  strip2.show();              // Refresh LED states
  strip2.setPixelColor(i, 0,i-nLEDs2,0); // Erase pixel, but don't refresh!
  strip2.setPixelColor(i-nLEDs2*2,0);
  delay(wait);
  }

  for(i=3*strip2.numPixels()/nLEDs2; i<strip2.numPixels(); i++) {
    strip2.setPixelColor(i, c,i-1,c1); // Set new pixel 'on'
    strip2.setPixelColor(i-2,c2);
    strip2.show();              // Refresh LED states
    strip2.setPixelColor(i, 0,i-1,0); // Erase pixel, but don't refresh!
    strip2.setPixelColor(i-2, 0);
    delay(wait);
  }
  for(i=0;i<strip2.numPixels();i++)
  {
    strip2.setPixelColor(i,0);
  }

  strip2.show(); // Refresh to turn off last pixel
}

// Really simular as the first two, but do the bubble thing
void colorChase3(uint32_t c,uint32_t c1,uint32_t c2, uint8_t wait) {
  int i;

  // Start by turning all pixels off:
  for(i=0; i<strip3.numPixels(); i++) strip3.setPixelColor(i, 0);

  for(i=0; i<strip3.numPixels()/nLEDs3; i++) {
  strip3.setPixelColor(i, c); // Set new pixel 'on'
  strip3.show();              // Refresh LED states
  strip3.setPixelColor(i, 0); // Erase pixel, but don't refresh!
  delay(wait);
  }
  for(i=strip3.numPixels()/nLEDs3; i<2*strip3.numPixels()/nLEDs3; i++) {
  strip3.setPixelColor(i, c1,i-nLEDs3,c); // Set new pixel 'on'
  strip3.show();              // Refresh LED states
  strip3.setPixelColor(i, 0,i-nLEDs3,0); // Erase pixel, but don't refresh!
  delay(wait);
  }
  for(i=2*strip3.numPixels()/nLEDs3; i<3*strip3.numPixels()/nLEDs3; i++) {
  strip3.setPixelColor(i, c2,i-nLEDs3,c1); // Set new pixel 'on'
  strip3.setPixelColor(i-nLEDs3*2,c2);
  strip3.show();              // Refresh LED states
  strip3.setPixelColor(i, 0,i-nLEDs3,0); // Erase pixel, but don't refresh!
  strip3.setPixelColor(i-nLEDs3*2,0);
  delay(wait);
  }

  for(i=3*strip3.numPixels()/nLEDs3; i<strip3.numPixels(); i++) {
    strip3.setPixelColor(i, c,i-1,c1); // Set new pixel 'on'
    strip3.setPixelColor(i-2,c2);
    strip3.show();              // Refresh LED states
    strip3.setPixelColor(i, 0,i-1,0); // Erase pixel, but don't refresh!
    strip3.setPixelColor(i-2, 0);
    delay(wait);
  }
  for(i=0;i<strip3.numPixels();i++)
  {
    strip3.setPixelColor(i,0);
  }

  strip3.show(); // Refresh to turn off last pixel

  //
  digitalWrite(bubblePin,HIGH);
  delay(3000);
  digitalWrite(bubblePin,LOW);

  // I don't think this does anything, but it was in the origional code, and I'm not by the neuron to test functionality if I remove it, so imma just let it ride.
  Button1_time = 0;
  Button2_time = 23000;
}
