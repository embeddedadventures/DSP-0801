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

//	DSP0801 14-Segment Alphanumeric Display Arduino library
//	Written originally by Embedded Adventures

#ifndef __DSP0801_h
#define __DSP0801_h

#define uns8 unsigned char
#define uns16 unsigned int
#define DSP_0801_TOTAL_CHARS 8
#define CMD_OFF 0x0000
#define CMD_ON 0x3FFF
#define CMD_DOT 0x4000
#define STEP 2.56

class DSP0801Class
{
private:
	void pulseLAT();
	void test();
	uns16 translate(uns8 my_char);
	int _CLK;
	int _MOSI;
	int _LAT;
	int _BLK;
	int MAX_CURSOR;
	uns8 cursor;

	uns16 *data_array;

public:
	void init(int CLK, int MOSI, int LAT, int PWM, int num_dsp);
	void print(char *str);
	/*Add 1 digit to data buffer*/
	void print(uns8 n);
	void fillDisplay();
	void clearDisplay();
	void display();
	void setCursor(uns8 pos);
	void setRaw(uns8 pos, uns16 raw);
	void setDot(uns8 pos);
	void clearDot(uns8 pos);
	
	/*Brightness values 1-100. Passing a 0 will automatically change it to 1*/
	void setBrightness(int level);		
};

extern DSP0801Class dsp0801;

#endif