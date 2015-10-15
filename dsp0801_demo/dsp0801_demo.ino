/*

Copyright (c) 2015, Embedded Adventures
All rights reserved.

Contact us at source [at] embeddedadventures.com
www.embeddedadventures.com

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.

- Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.

- Neither the name of Embedded Adventures nor the names of its contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
THE POSSIBILITY OF SUCH DAMAGE.

*/

//  DSP0801 14-Segment Alphanumeric Display Arduino test sketch
//  Written originally by Embedded Adventures


#include <DSP0801.h>

#define SIN 8
#define CLK 9
#define BLK 10
#define LAT 11

#define NUM_DSP 1

void setup() {
  Serial.begin(115200);
  dsp0801.init(CLK, SIN, LAT, BLK, NUM_DSP);
  Serial.println("Welcome to the DSP-0801 14-segment LED display test sketch");
  Serial.println("Embedded Adventures (www.embeddedadventures.com)");
  dsp0801.clearDisplay();
  dsp0801.setBrightness(100);
}

void loop() {
  Serial.println("Turn on all segments");
  dsp0801.fillDisplay();
  delay(1000);
  dsp0801.clearDisplay();
  delay(500);

  Serial.println("Show brightness of display from 1 to 100");
  brightness_test();
  dsp0801.clearDisplay();
  delay(500);

  Serial.println("Print alphabet");
  alphabet();
  dsp0801.clearDisplay();
  delay(500);

  Serial.println("Turn on all dots");
  dots();
  dsp0801.clearDisplay();
  delay(500);
}

//Turn on all dots in the display
void dots() {
  dsp0801.clearDisplay();
  for (int i = 0; i < (NUM_DSP*8); i++) {
    dsp0801.setDot(i+1);
    dsp0801.display();
    delay(200);
  }
}

//Print the alphabet onto the display
void alphabet() {
  dsp0801.clearDisplay();
  for (int i = 0; i < 26; i++) {
    dsp0801.print((char)0x31+i);
    dsp0801.display();
    delay(200);
  }
}

//Simple demo of the brightness of the display, from 1-100
void brightness_test() {
  dsp0801.clearDisplay();
  
  for (int i = 0; i <= 100; i+=5) {
    Serial.print("Setting brightness to - ");
    Serial.println(i);
    dsp0801.setBrightness(i);
    dsp0801.print("LVL-");
    
    if ((i >= 10) && (i < 100)) {
      dsp0801.print(i/10);
      dsp0801.print(i%10);
    }
    else if (i == 100)
      dsp0801.print("MAX");
    else
      dsp0801.print(i);
      
    dsp0801.display();
    delay(400);
    dsp0801.setCursor(0);
  }
}

