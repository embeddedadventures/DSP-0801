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

#include "Arduino.h"
#include "DSP0801.h"

void DSP0801Class::pulseLAT() {
	digitalWrite(_LAT, HIGH);
	digitalWrite(_LAT, LOW);
}

uns16 DSP0801Class::translate(uns8 my_char) {
	uns16 result = 0;

	switch (my_char) {
		case ' ': result = 0b0000000000000000; break;
		case '0': result = 0b0010010000111111; break;
		case '1': result = 0b0000000000000110; break;
		case '2': result = 0b0000000011011011; break;
		case '3': result = 0b0000000010001111; break;
		case '4': result = 0b0001001011100000; break;
		case '5': result = 0b0000000011101101; break;
		case '6': result = 0b0000000011111101; break;
		case '7': result = 0b0000000000000111; break;
		case '8': result = 0b0000000011111111; break;
		case '9': result = 0b0000000011101111; break;
		case 'a':
		case 'A': result = 0b0000000011110111; break;
		case 'b':
		case 'B': result = 0b0001001010001111; break;
		case 'c':
		case 'C': result = 0b0000000000111001; break;
		case 'd':
		case 'D': result = 0b0001001000001111; break;
		case 'e':
		case 'E': result = 0b0000000001111001; break;
		case 'f':
		case 'F': result = 0b0000000001110001; break;
		case 'g':
		case 'G': result = 0b0000000010111101; break;
		case 'h':
		case 'H': result = 0b0000000011110110; break;
		case 'i':
		case 'I': result = 0b0001001000001001; break;
		case 'j':
		case 'J': result = 0b0000000000011110; break;
		case 'k':
		case 'K': result = 0b0000110001110000; break;
		case 'l':
		case 'L': result = 0b0000000000111000; break;
		case 'm':
		case 'M': result = 0b0000010100110110; break;
		case 'n':
		case 'N': result = 0b0000100100110110; break;
		case 'o':
		case 'O': result = 0b0000000000111111; break;
		case 'p':
		case 'P': result = 0b0000000011110011; break;
		case 'q':
		case 'Q': result = 0b0000100000111111; break;
		case 'r':
		case 'R': result = 0b0000100011110011; break;
		case 's':
		case 'S': result = 0b0000000011101101; break;
		case 't':
		case 'T': result = 0b0001001000000001; break;
		case 'u':
		case 'U': result = 0b0000000000111110; break;
		case 'v':
		case 'V': result = 0b0010010000110000; break;
		case 'w':
		case 'W': result = 0b0010100000110110; break;
		case 'x':
		case 'X': result = 0b0010110100000000; break;
		case 'y':
		case 'Y': result = 0b0001010100000000; break;
		case 'z':
		case 'Z': result = 0b0010010000001001; break;
		case '*': result = 0b0011111111000000; break;
		case '.': result = 0x4000; break;
	}
	return result;
}

void DSP0801Class::init(int CLK, int MOSI, int LAT, int PWM, int num_dsp) {
	_LAT = LAT;
	_CLK = CLK;
	_MOSI = MOSI;
	_BLK = PWM;
	MAX_CURSOR = (8 * num_dsp);
	cursor = 0;

	pinMode(_CLK, OUTPUT);
	pinMode(_MOSI, OUTPUT);
	pinMode(_LAT, OUTPUT);
	pinMode(_BLK, OUTPUT);
	digitalWrite(_LAT, LOW);
	analogWrite(_BLK, 100);

	data_array = new uns16 [MAX_CURSOR];
}

void DSP0801Class::print(char *str) {
	while ((*str != 0) && (cursor < MAX_CURSOR)) {
		if ((*str == '.') && (cursor != 0)) {
			data_array[cursor - 1] = data_array[cursor - 1] | 0x4000;
		}
		else {
			data_array[cursor] = translate(*str);
			cursor++;
		}
		str++;
	}
	
	if (cursor == MAX_CURSOR) {
		cursor = 0;
	}
}

void DSP0801Class::test() {
	for (int i = 0; i < MAX_CURSOR; i++) {
		Serial.print(data_array[i]);
		Serial.print("\t");
		Serial.println((char)data_array[i]);
	}
}

void DSP0801Class::print(uns8 n) {
	if (cursor < MAX_CURSOR) {
		data_array[cursor] = translate(n + '0');
	}
	else {
		cursor = 0;
		data_array[cursor] = translate(n + '0');
	}
	cursor++;
}

void DSP0801Class::display() {
	for (int i = 0; i < MAX_CURSOR; i++) {
		shiftOut(_MOSI, _CLK, MSBFIRST, highByte(data_array[i]));
		shiftOut(_MOSI, _CLK, MSBFIRST, lowByte(data_array[i]));
	}
	pulseLAT();
}

void DSP0801Class::fillDisplay() {
	for (int i = 0; i < MAX_CURSOR; i++) {
		data_array[i] = 0xFFFF;
	}
	cursor = 0;
	display();
}

void DSP0801Class::clearDisplay() {
	for (int i = 0; i < MAX_CURSOR; i++) {
		data_array[i] = 0x0000;
	}
	cursor = 0;
	display();
}

void DSP0801Class::setCursor(uns8 pos) {
	if (pos > MAX_CURSOR)
		cursor = 0;
	else
		cursor = pos;
}

void DSP0801Class::setRaw(uns8 pos, uns16 raw) {
	data_array[pos - 1] = raw;
}

void DSP0801Class::setDot(uns8 pos) {
	data_array[pos - 1] = data_array[pos - 1] | 0x4000;
}

void DSP0801Class::clearDot(uns8 pos) {
	data_array[pos - 1] = data_array[pos - 1] & 0x30;
}

void DSP0801Class::setBrightness(int level) {
	if (level == 0)
		level = 99;
	else
		level = 100 - level;
	analogWrite(_BLK, STEP*level);
}

DSP0801Class dsp0801;