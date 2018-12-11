/*!
* @file        star.cpp
*
* @copyright   Copyright (c) 2018 Ackalyte
*
*              Permission is hereby granted, free of charge, to any person obtaining a copy
*              of this software and associated documentation files (the "Software"), to deal
*              in the Software without restriction, including without limitation the rights
*              to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*              copies of the Software, and to permit persons to whom the Software is
*              furnished to do so, subject to the following conditions:
*
*              The above copyright notice and this permission notice shall be included in all
*              copies or substantial portions of the Software.
*
*              THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*              IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*              FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*              AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*              LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*              OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*              SOFTWARE.
*
*
*
* @author      Sahil Khanna <s.khanna@tektindustries.com>
* @date        17 OCT 2018
* @details      Parts of code taken from Adafruit NeoPixel Library examples (https://github.com/adafruit/Adafruit_NeoPixel/blob/master/examples/RGBWstrandtest/RGBWstrandtest.ino)
*/
#include "star.h"

const int config = SK6812_GRBW | SK6812_800kHz;
DMAMEM StarDisplayBuffer buff;
byte star_gamma[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
    10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
    17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
    25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
    37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
    51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
    69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
    90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
    115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
    144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
    177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
    215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };

Star::Star(StarDisplayBuffer& buff,uint8_t StarType, uint8_t channel):star(TOTAL_LED_LARGE_STAR, buff.displayMemory, buff.drawingMemory, config),hexagon_strip(StarType),_starType(StarType),m_channel(channel){
    
    if (StarType==STAR_SMALL) {
        this->starEdgeLength=SMALL_STAR_EDGE_LENGTH;
        this->hexagonEdgeLength=SMALL_HEXAGON_EDGE_LENGTH;
        
        for(uint8_t i = 0; i < 6; i++)
        {
            this->StarInnerPoints[i]=((2*i)+1)*SMALL_STAR_EDGE_LENGTH;
            this->StarOuterPoints[i]=((2*i))*SMALL_STAR_EDGE_LENGTH;
            this->hexagonPoints[i]=i*SMALL_HEXAGON_EDGE_LENGTH;
        }
    }
    else if(StarType==STAR_MEDIUM)
    {
        this->starEdgeLength=MEDIUM_STAR_EDGE_LENGTH;
        this->hexagonEdgeLength=SMALL_HEXAGON_EDGE_LENGTH;

        for(uint8_t i = 0; i < 6; i++)
        {
            this->StarInnerPoints[i]=((2*i)+1)*MEDIUM_STAR_EDGE_LENGTH;
            this->StarOuterPoints[i]=((2*i))*MEDIUM_STAR_EDGE_LENGTH;
            this->hexagonPoints[i]=i*MEDIUM_HEXAGON_EDGE_LENGTH;
        }
    }
     this->m_channel_offset=channel*TOTAL_LED_LARGE_STAR;
}


Star::~Star()
{
  this->starEdgeLength=0;
  this->hexagonEdgeLength=0;
  
  for(uint8_t i = 0; i < 6; i++)
  {
      this->StarInnerPoints[i]=0;
      this->StarOuterPoints[i]=0;
      this->hexagonPoints[i]=0;
  }
}

void Star::init(){
    star.begin();
}

void Star::show(){
    star.show();
}

int16_t Star::mapLEDs(uint16_t led_num){
    uint8_t edge_length;
    uint8_t total_led;
    if(this->_starType==STAR_SMALL){
        edge_length=SMALL_STAR_EDGE_LENGTH;
        total_led=TOTAL_LED_SMALL_STAR;
    }else if(this->_starType==STAR_MEDIUM){
        edge_length=MEDIUM_STAR_EDGE_LENGTH;
        total_led=TOTAL_LED_MEDIUM_STAR;
    }
        if(led_num<=edge_length){
            return led_num;
        } else if (led_num>edge_length && led_num<edge_length*2){
            return led_num+total_led+edge_length*7;
        } else if (led_num>=edge_length*2 && led_num<edge_length*3){
            return led_num+total_led-edge_length*2;
        }else if (led_num>=edge_length*3 && led_num<=edge_length*5){
            return led_num-edge_length;
        }else if (led_num>edge_length*5 && led_num<edge_length*7){
            return led_num+total_led-edge_length*3;
        }else if (led_num>=edge_length*7 && led_num<=edge_length*9){
            return led_num-edge_length*2;
        }else if (led_num>edge_length*9 && led_num<edge_length*11){
            return led_num+total_led-edge_length*4;
        }else if (led_num>=edge_length*11 && led_num<=edge_length*12){
            return led_num-edge_length*3;
        }
    
        return -1;
}

uint16_t Star::Pixel(uint16_t pixel){
 return mapLEDs(pixel)+this->m_channel_offset;
}
uint16_t Star::HexPixel(uint16_t pixel){
 return hexagon_strip.Pixel(pixel)+this->m_channel_offset;
}

uint16_t Star::numPixels(){
    
    if (this->_starType==STAR_SMALL) {
        return SMALL_STAR_EDGE_LENGTH*12;
    }
    else if(this->_starType==STAR_MEDIUM){
        return MEDIUM_STAR_EDGE_LENGTH*12;
    }
        return 0;
}

uint16_t Star::totalLEDs(){
    if (this->_starType==STAR_SMALL) {
        return TOTAL_LED_SMALL_STAR*2;
    }
    else if(this->_starType==STAR_MEDIUM){
        return TOTAL_LED_MEDIUM_STAR*2;
    }
        return 0;
}

uint32_t Star::color(uint8_t r, uint8_t g, uint8_t b) {
  return (r << 16) | (g << 8) | b;
}

// Convert separate R,G,B,W into packed 32-bit WRGB color.
// Packed format is always WRGB, regardless of LED strand color order.
uint32_t Star::color(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
  return (w << 24) | (r << 16) | (g << 8) | b;
}


//Hexagon Stuff
int8_t Star::setHexagonBlack() {
  for(uint16_t i=0; i<hexagon_strip.numPixels(); i++) {
    star.setPixel(this->HexPixel(i), 0);
  }
    star.show();
    return ANIMATION_COMPLETE;
}

int8_t Star::colorWipeHexagon(uint32_t c, uint16_t wait) {
  for(uint16_t i=0; i<hexagon_strip.numPixels(); i++) {
    star.setPixel(this->HexPixel(i), c);
    star.show();
    delay(wait);
  }
    return ANIMATION_COMPLETE;
}

int8_t Star::setAllBlack() {
  for(uint16_t i=0; i<this->totalLEDs(); i++) {
    star.setPixel(i, 0);
  }
    star.show();
    return ANIMATION_COMPLETE;
}

int8_t Star::setStarBlack() {
  for(uint16_t i=0; i<this->numPixels(); i++) {
    star.setPixel(this->Pixel(i), 0);
  }
    star.show();
    return ANIMATION_COMPLETE;
}



// Fill the dots one after the other with a color
int8_t Star::colorWipe(uint32_t c, uint16_t wait) {
  for(uint16_t i=0; i<this->numPixels(); i++) {
    star.setPixel(this->Pixel(i), c);
    star.show();
    delay(wait);
  }
    return ANIMATION_COMPLETE;
}

int8_t Star::colorStar(uint32_t c) {
  for(uint16_t i=0; i<this->numPixels(); i++) {
    star.setPixel(this->Pixel(i), c);
  }
    return ANIMATION_COMPLETE;
}

int8_t Star::colorStar(uint32_t c, uint8_t start_index, uint8_t skip) {
  for(uint16_t i=start_index; i<this->numPixels(); i=i+skip+1) {
    star.setPixel(this->Pixel(i), c);
  }
    return ANIMATION_COMPLETE;
}


int8_t Star::pulseWhite(uint8_t wait) {
  for(int j = 0; j < 256 ; j++){
      for(uint16_t i=0; i<this->numPixels(); i++) {
          star.setPixel(this->Pixel(i), this->color(0,0,0, star_gamma[j] ) );
        }
        delay(wait);
        star.show();
      }

  for(int j = 255; j >= 0 ; j--){
      for(uint16_t i=0; i<this->numPixels(); i++) {
          star.setPixel(this->Pixel(i), this->color(0,0,0, star_gamma[j] ) );
        }
        delay(wait);
        star.show();
      }
    return ANIMATION_COMPLETE;
}

int8_t Star::rainbowFade2White(uint8_t wait, int rainbowLoops, int whiteLoops) {
    float fadeMax = 100.0;
    int fadeVal = 0;
    uint32_t wheelVal;
    int redVal, greenVal, blueVal;

    for(int k = 0 ; k < rainbowLoops ; k ++){

    for(int j=0; j<256; j++) { // 5 cycles of all colors on wheel

        for(int i=0; i< this->numPixels(); i++) {

        wheelVal =this->Wheel(((i * 256 / this->numPixels()) + j) & 255);

        redVal = red(wheelVal) * float(fadeVal/fadeMax);
        greenVal = green(wheelVal) * float(fadeVal/fadeMax);
        blueVal = blue(wheelVal) * float(fadeVal/fadeMax);
        star.setPixel( this->Pixel(i), this->color( redVal, greenVal, blueVal ) );

        }
        //First loop, fade in!
        if(k == 0 && fadeVal < fadeMax-1) {
            fadeVal++;
        }

        //Last loop, fade out!
        else if(k == rainbowLoops - 1 && j > 255 - fadeMax ){
            fadeVal--;
        }

        star.show();
        delay(wait);
    }

    }

    delay(500);


    for(int k = 0 ; k < whiteLoops ; k ++){

    for(int j = 0; j < 256 ; j++){

        for(uint16_t i=0; i < this->numPixels(); i++) {
            star.setPixel(this->Pixel(i), this->color(0,0,0, star_gamma[j] ) );
            }
            star.show();
        }

        delay(2000);
    for(int j = 255; j >= 0 ; j--){

        for(uint16_t i=0; i < this->numPixels(); i++) {
            star.setPixel(this->Pixel(i), this->color(0,0,0, star_gamma[j] ) );
            }
            star.show();
        }
    }

    delay(500);
    return ANIMATION_COMPLETE;


}

int8_t Star::whiteOverRainbow(uint8_t wait, uint8_t whiteSpeed, uint8_t whiteLength ) {

    if(whiteLength >= this->numPixels()) whiteLength = this->numPixels() - 1;

    int head = whiteLength - 1;
    int tail = 0;

    int loops = 3;
    int loopNum = 0;

    static unsigned long lastTime = 0;


    while(true){
    for(int j=0; j<256; j++) {
        for(uint16_t i=0; i<this->numPixels(); i++) {
        if((i >= tail && i <= head) || (tail > head && i >= tail) || (tail > head && i <= head) ){
            star.setPixel(this->Pixel(i), this->color(0,0,0, 255 ) );
        }
        else{
            star.setPixel(this->Pixel(i), this->Wheel(((i * 256 / this->numPixels()) + j) & 255));
        }
        
        }
        
    }
        if(millis() - lastTime > whiteSpeed) {
        head++;
        tail++;
        if(head == this->numPixels()){
            loopNum++;
        }
        lastTime = millis();
        }

        if(loopNum == loops) break;

        head%=this->numPixels();
        tail%=this->numPixels();
        star.show();
        delay(wait);
    }

    return ANIMATION_COMPLETE;
}

int8_t Star::fullWhite() {
  
    for(uint16_t i=0; i<this->numPixels(); i++) {
        star.setPixel(this->Pixel(i), this->color(0,0,0, 255 ) );
    }
      star.show();
    return ANIMATION_COMPLETE;
}

// Slightly different, this makes the rainbow equally distributed throughout
int8_t Star::rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256 * 5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< this->numPixels(); i++) {
      star.setPixel(this->Pixel(i),this->Wheel(((i * 256 / this->numPixels()) + j) & 255));
    }
    star.show();
    delay(wait);
  }
    return ANIMATION_COMPLETE;
}

int8_t Star::rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<this->numPixels(); i++) {
      star.setPixel(this->Pixel(i),this->Wheel((i+j) & 255));
    }
    star.show();
    delay(wait);
  }
    return ANIMATION_COMPLETE;
}

// Input a value 0 to 255 to get a color value.
// The colors are a transition r - g - b - back to r.
uint32_t Star::Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return this->color(255 - WheelPos * 3, 0, WheelPos * 3,0);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return this->color(0, WheelPos * 3, 255 - WheelPos * 3,0);
  }
  WheelPos -= 170;
  return this->color(WheelPos * 3, 255 - WheelPos * 3, 0,0);
}

uint32_t Star::WheelRedGreen(byte WheelPos) {

  WheelPos = 255 - WheelPos;
  if(WheelPos < 64) {
    return this->color(255 - WheelPos * 4, WheelPos * 4, 0 ,0);
  }
  if(WheelPos < 128) {
    WheelPos -= 64;
    return this->color(WheelPos * 4, 255 - WheelPos * 4, 0,0);
  }
  if(WheelPos < 192) {
    WheelPos -= 64;
    return this->color(255 - WheelPos * 4, WheelPos * 4, 0,0);
  }
  WheelPos -= 192;
  return this->color(WheelPos * 4, 255 - WheelPos * 4, 0,0);
}

uint32_t Star::WheelWhite(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return this->color(0, 0, 0 ,255 - WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return this->color(0, 0, 0,0);
  }
  WheelPos -= 170;
  return this->color(0, 0, 0,WheelPos * 3);
}

uint8_t Star::white(uint32_t c) {
  return (c >>24);
}
uint8_t Star::red(uint32_t c) {
  return (c >> 16);
}
uint8_t Star::green(uint32_t c) {
  return (c >> 8);
}
uint8_t Star::blue(uint32_t c) {
  return (c);
}

int8_t Star::colorFromEdge(uint32_t color,uint16_t wait){
  
  for(uint8_t index = 0; index <= this->starEdgeLength; index++)
  {
    for(uint8_t i = 0; i < 6; i++)
    {
      star.setPixel(this->Pixel(this->StarInnerPoints[i]-index), color);
      star.setPixel(this->Pixel(this->StarInnerPoints[i]+index), color);
    }
      star.show();
      delay(wait);
  }
    return ANIMATION_COMPLETE;
}

int8_t Star::colorFromEdgeFade(uint16_t wait){
  uint32_t wheelVal;
  int redVal, greenVal,blueVal=0;
  uint16_t wheel_const= (256/(this->starEdgeLength*3));
  // uint16_t wheel_const= 17;
  
  for(int j=0; j<256; j++) {
    for(uint8_t ledIndex = 0; ledIndex <= this->starEdgeLength; ledIndex++)
    {
      wheelVal = this->WheelRedGreen(((ledIndex * wheel_const) + j) & 255);
      redVal = red(wheelVal);
      greenVal = green(wheelVal);
      for(uint8_t side = 0; side < 6; side++)
      {
        star.setPixel(this->Pixel(this->StarInnerPoints[side]-ledIndex), this->color(redVal,greenVal,blueVal));
        star.setPixel(this->Pixel(this->StarInnerPoints[side]+ledIndex), this->color(redVal,greenVal,blueVal));
      }
      star.show();
      delayMicroseconds(wait);
    }
  }
    return ANIMATION_COMPLETE;
}

int8_t Star::colorSpreadStarToHexagon(uint16_t wait){
  uint32_t wheelVal;
  int redVal, greenVal, blueVal=0;
  uint16_t wheel_const= (256/(this->starEdgeLength*6));
  // uint16_t wheel_const= 17;
  
  for(int j=0; j<256; j++) {
    for(uint8_t ledIndex = 0; ledIndex <= this->starEdgeLength; ledIndex++)
    {
      wheelVal =this->WheelRedGreen(((ledIndex * wheel_const) + j) & 255);
      redVal = red(wheelVal);
      greenVal = green(wheelVal);
      for(uint8_t side = 0; side < 6; side++)
      {
        star.setPixel(this->Pixel(this->StarInnerPoints[side]-ledIndex), this->color(redVal,greenVal,blueVal));
        star.setPixel(this->Pixel(this->StarInnerPoints[side]+ledIndex), this->color(redVal,greenVal,blueVal));
      }
      
      if (ledIndex!=this->starEdgeLength) {
        wheelVal =this->WheelRedGreen((((ledIndex) * wheel_const) + (256-j)) & 255);
        redVal = red(wheelVal);
        greenVal = green(wheelVal);
        for(uint8_t side = 0; side < 6; side++)
        {
          star.setPixel(this->HexPixel(this->hexagonPoints[side]+ledIndex), this->color(redVal,greenVal,blueVal));
        }
      }
      star.show();
    }
  delayMicroseconds(wait);
  }
    return ANIMATION_COMPLETE;
}

int8_t Star::WhiteSpreadStarToHexagon(uint16_t wait){
  uint32_t wheelVal;
  int redVal=0, greenVal=0,whiteVal, blueVal=0;
  uint16_t wheel_const= (256/(this->starEdgeLength*3));
  
  for(int j=0; j<256; j++) {
    for(uint8_t ledIndex = 0; ledIndex <= this->starEdgeLength; ledIndex++)
    {
      wheelVal =this->WheelWhite(((ledIndex * wheel_const) + j) & 255);
      whiteVal =white(wheelVal);
      for(uint8_t side = 0; side < 6; side++)
      {
        star.setPixel(this->Pixel(this->StarInnerPoints[side]-ledIndex), this->color(redVal,greenVal,blueVal,whiteVal));
        star.setPixel(this->Pixel(this->StarInnerPoints[side]+ledIndex), this->color(redVal,greenVal,blueVal,whiteVal));
      }
      if (ledIndex!=this->starEdgeLength) {
        wheelVal =this->WheelWhite((((ledIndex) * wheel_const) + (256-j)) & 255);
        redVal = 0;
        greenVal = 0;
        whiteVal =white(wheelVal);
        for(uint8_t side = 0; side < 6; side++)
        {
          star.setPixel(this->HexPixel(this->hexagonPoints[side]+ledIndex), this->color(redVal,greenVal,blueVal,whiteVal));
        }
      }
      star.show();
    }
   delayMicroseconds(wait);
  }
    return ANIMATION_COMPLETE;
}

int8_t Star::RainbowEdgeRotate(uint16_t wait){
  uint32_t wheelVal;
  int redVal, greenVal, blueVal;
  uint16_t wheel_const= (256/(6));

  for(int j=0; j<256; j++) {
    for(uint8_t side = 0; side < 6; side++)
    {
      wheelVal =this->Wheel(((side * wheel_const) + j) & 255); //Full Rainbow 
      redVal = red(wheelVal);
      greenVal = green(wheelVal);
      blueVal= blue(wheelVal);
      for(uint8_t ledIndex = 0; ledIndex < this->starEdgeLength; ledIndex++)
      {
        star.setPixel(this->Pixel(this->StarOuterPoints[side]+ledIndex), this->color(redVal,greenVal,blueVal));
        if(side==0){
          star.setPixel(this->Pixel((this->starEdgeLength*12)-1-ledIndex), this->color(redVal,greenVal,blueVal));
        }else{
          star.setPixel(this->Pixel(this->StarOuterPoints[side]-ledIndex), this->color(redVal,greenVal,blueVal));
        }
      }
      star.show();
    }
  delay(wait);
  }
    return ANIMATION_COMPLETE;
}

int8_t Star::GreenRedSpiral(uint8_t wait, uint16_t colorSpeed, uint8_t colorLength , uint8_t sections) {
  
  if(colorLength >= this->numPixels()) colorLength = this->numPixels() - 1;

  int head = colorLength - 1;
  int tail = 0;

  int loops = 3;
  int loopNum = 0;

  static unsigned long lastTime = 0;

  while(true){
      for(uint16_t i=0; i<this->numPixels()/sections; i++) {
        if((i >= tail && i <= head) || (tail > head && i >= tail) || (tail > head && i <= head) ){
          for(uint8_t j = 0; j < sections; j++)
          {
            star.setPixel(this->Pixel(i+j*(this->starEdgeLength*12/sections)), GREEN_COLOR );
          }
        }
        else{
          for(uint8_t j = 0; j < sections; j++)
          {
            star.setPixel(this->Pixel(i+j*(this->starEdgeLength*12/sections)), RED_COLOR );
          }
        }
        
      }

      if(millis() - lastTime > colorSpeed) {
        head++;
        tail++;
        if(head == this->numPixels()/sections){
          loopNum++;
        }
        lastTime = millis();
      }

      if(loopNum == loops && tail>this->numPixels()/sections-(colorLength/2)) break;

      head%=this->numPixels()/sections;
      tail%=this->numPixels()/sections;
      star.show();
      delayMicroseconds(wait);
    }
    return ANIMATION_COMPLETE;
}

int8_t previous_pattern=-1;
int8_t Star::ChristmasPattern(uint8_t pattern_num){
  return ChristmasPattern(pattern_num, 1000);
}
int8_t Star::ChristmasPattern(uint8_t pattern_num,uint16_t wait){
  
    switch (pattern_num)
    {
        case ALTERNATE_LEDS:
            for(uint8_t i = 0; i < PATTERN_LOOP; i++)
            {
                for(uint8_t j = 0; j < 255; j++)
                {
                    this->colorStar(this->color(255-j,j,0),0,1);
                    this->colorStar(this->color(j,255-j,0),1,1);
                    star.show();
                }
                    delay(wait);
                for(uint8_t j = 0; j < 255; j++)
                {
                    this->colorStar(this->color(j,255-j,0),0,1);
                    this->colorStar(this->color(255-j,j,0),1,1);
                    star.show();
                }
                    delay(wait);
            }
            previous_pattern=ALTERNATE_LEDS;
            return ANIMATION_COMPLETE;

        case GREEN_RED_SPIRAL:
            this->GreenRedSpiral(wait,GREEN_RED_SPIRAL_SPEED,GREEN_SPIRAL_LENGTH,GREEN_RED_SPIRAL_SECTIONS);
            previous_pattern=GREEN_RED_SPIRAL;
            return ANIMATION_COMPLETE;

        case GREEN_STAR_INWARDS:
            this->colorSpreadStarToHexagon(wait);
            previous_pattern=GREEN_STAR_INWARDS;
            return ANIMATION_COMPLETE;

        case SNOW_SPREAD:
            this->WhiteSpreadStarToHexagon(wait);
            previous_pattern=SNOW_SPREAD;
            return ANIMATION_COMPLETE;

        case RED_GREEN_SPREAD: 
            if (previous_pattern==SNOW_SPREAD) {
                setHexagonBlack();
            }
            this->colorFromEdgeFade(wait);
            previous_pattern=RED_GREEN_SPREAD;
            return ANIMATION_COMPLETE;

        default:
            break;
    }
    return -1;
}