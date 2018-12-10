/*!
* @file        largeStar.cpp
*
* @copyright   Copyright (C) 2018 Tekt Industries - All Rights Reserved,
*              unauthorized copying of this file is strictly prohibited
*
*
* @author      Sahil Khanna <s.khanna@tektindustries.com>
* @date        17 OCT 2018
* @details      Parts of code taken from Adafruit NeoPixel Library examples (https://github.com/adafruit/Adafruit_NeoPixel/blob/master/examples/RGBWstrandtest/RGBWstrandtest.ino)
*/
#include "largeStar.h"

const int ledsPerStrip = TOTAL_LED_LARGE_STAR;
const int config = SK6812_GRBW | SK6812_800kHz;
byte largeStar_gamma[] = {
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


LargeStar::LargeStar(StarDisplayBuffer& buff, uint8_t top_channel,uint8_t bot_channel):star(ledsPerStrip, buff.displayMemory, buff.drawingMemory, config),hexagon_strip(top_channel*TOTAL_LED_LARGE_STAR,bot_channel*TOTAL_LED_LARGE_STAR){
     this->m_t_channel=top_channel;
     this->m_b_channel=bot_channel;
     this->m_t_channel_offset=top_channel*TOTAL_LED_LARGE_STAR;
     this->m_b_channel_offset=bot_channel*TOTAL_LED_LARGE_STAR;
}

LargeStar::~LargeStar(){}

uint16_t LargeStar::numPixels(uint16_t ring_type){
    if (ring_type==INNER_RING) {
        return LARGE_INNER_STAR_EDGE_LENGTH*12;
    }else if(ring_type==MIDDLE_RING) {
        return LARGE_MIDDLE_STAR_EDGE_LENGTH*12;
    }else if(ring_type==OUTER_RING){
        return LARGE_OUTER_STAR_EDGE_LENGTH*12;
    }
    return 0;
}

void LargeStar::init(){
    star.begin();
}

void LargeStar::show(){
    star.show();
}

uint32_t LargeStar::color(uint8_t r, uint8_t g, uint8_t b) {
  return (r << 16) | (g << 8) | b;
}

// Convert separate R,G,B,W into packed 32-bit WRGB color.
// Packed format is always WRGB, regardless of LED strand color order.
uint32_t LargeStar::color(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
  return (w << 24) | (r << 16) | (g << 8) | b;
}

uint16_t LargeStar::Pixel(uint8_t ring_type,uint16_t pixel){
    uint8_t triangleStrip = findTriangleStrip(ring_type,pixel);
    if(triangleStrip==TOP_TRIANGLE){
        return mapLEDs(ring_type,pixel)+this->m_t_channel_offset;
    }else if(triangleStrip==BOTTOM_TRIANGLE){
        return mapLEDs(ring_type,pixel)+this->m_b_channel_offset;
    }
    else{
        return -1;
    }
}
uint8_t LargeStar::findTriangleStrip(uint8_t ring_type,uint16_t pixel){
    uint8_t edge_length=0;
    uint8_t led_ring_edge_offset=0;
    
    if (ring_type==OUTER_RING) {
        edge_length=LARGE_OUTER_STAR_EDGE_LENGTH;
        led_ring_edge_offset=0;
    }else if (ring_type==MIDDLE_RING) {
        edge_length=LARGE_MIDDLE_STAR_EDGE_LENGTH;
        led_ring_edge_offset=1;
    }if (ring_type==INNER_RING) {
        edge_length=LARGE_INNER_STAR_EDGE_LENGTH;
        led_ring_edge_offset=2;
    }
    
    if (pixel<=edge_length+led_ring_edge_offset) {
        return TOP_TRIANGLE;
    }
    else if (pixel>edge_length+led_ring_edge_offset && pixel<edge_length*2){
        return BOTTOM_TRIANGLE;
    } else if (pixel>=edge_length*2 && pixel<edge_length*3-led_ring_edge_offset){
        return BOTTOM_TRIANGLE;
    }
    else if (pixel>=edge_length*3-led_ring_edge_offset && pixel<=edge_length*5+led_ring_edge_offset){
        return TOP_TRIANGLE;
    }else if (pixel>edge_length*5+led_ring_edge_offset && pixel<edge_length*7-led_ring_edge_offset){
        return BOTTOM_TRIANGLE;
    }
    else if (pixel>=edge_length*7-led_ring_edge_offset && pixel<=edge_length*9+led_ring_edge_offset){
        return TOP_TRIANGLE;
    }else if (pixel>edge_length*9+led_ring_edge_offset && pixel<edge_length*11-led_ring_edge_offset){
        return BOTTOM_TRIANGLE;
    }else if (pixel>=edge_length*11-led_ring_edge_offset && pixel<=edge_length*12+led_ring_edge_offset){
        return TOP_TRIANGLE;
    }

    return 2;
}

int32_t LargeStar::mapLEDs(uint8_t ring_type,uint16_t pixel){
    uint8_t edge_length=0;
    uint8_t offset=0;
    uint8_t led_ring_edge_offset=0;
    if (ring_type==OUTER_RING) {
        edge_length=LARGE_OUTER_STAR_EDGE_LENGTH;
        offset=0;
        if (pixel<=edge_length) {
            return pixel+offset;
        }else if (pixel>edge_length && pixel<edge_length*2){
            return pixel+offset+edge_length*7;
        } else if (pixel>=edge_length*2 && pixel<edge_length*3){
            return pixel+offset-edge_length*2;
        }else if (pixel>=edge_length*3 && pixel<=edge_length*5){
            return pixel+offset-edge_length;
        }else if (pixel>edge_length*5 && pixel<edge_length*7){
            return pixel+offset-edge_length*3;
        }else if (pixel>=edge_length*7 && pixel<=edge_length*9){
            return pixel+offset-edge_length*2;
        }else if (pixel>edge_length*9 && pixel<edge_length*11){
            return pixel+offset-edge_length*4;
        }else if (pixel>=edge_length*11 && pixel<edge_length*12){
            return pixel+offset-edge_length*3;
        }

    }else if (ring_type==MIDDLE_RING) {
        edge_length=LARGE_MIDDLE_STAR_EDGE_LENGTH;
        offset=LARGE_OUTER_STAR_EDGE_LENGTH*9;
        led_ring_edge_offset=1;

        if (pixel<=edge_length) {
            return pixel+offset;
        }

        else if (pixel==edge_length+led_ring_edge_offset){
            return pixel+1;
        }
        else if (pixel>edge_length+led_ring_edge_offset && pixel<edge_length*2){
            return pixel+offset+edge_length*7;
        } else if (pixel>=edge_length*2 && pixel<edge_length*3-led_ring_edge_offset){
            return pixel+offset-edge_length*2;
        }

        else if (pixel==edge_length*3-led_ring_edge_offset){
            return pixel-edge_length+2;
        }
        else if (pixel>=edge_length*3 && pixel<=edge_length*5){
            return pixel+offset-edge_length;
        }

        else if (pixel==edge_length*5+led_ring_edge_offset){
            return pixel-edge_length+4;
        }
        else if (pixel>edge_length*5 && pixel<edge_length*7-led_ring_edge_offset){
            return pixel+offset-edge_length*3;
        }

        else if (pixel==edge_length*7-led_ring_edge_offset){
            return pixel-2*edge_length+5;
        }
        else if (pixel>=edge_length*7 && pixel<=edge_length*9){
            return pixel+offset-edge_length*2;
        }
        else if (pixel==edge_length*9+led_ring_edge_offset){
            return pixel-2*edge_length+7;
        }

        else if (pixel>edge_length*9 && pixel<edge_length*11-led_ring_edge_offset){
            return pixel+offset-edge_length*4;
        }
        else if (pixel==edge_length*11-led_ring_edge_offset){
            return pixel-3*edge_length+8;
        }

        else if (pixel>=edge_length*11 && pixel<edge_length*12){
            return pixel+offset-edge_length*3;
        }

    }else if (ring_type==INNER_RING) {
        edge_length=LARGE_INNER_STAR_EDGE_LENGTH; 
        offset=LARGE_OUTER_STAR_EDGE_LENGTH*9+LARGE_MIDDLE_STAR_EDGE_LENGTH*9;
        led_ring_edge_offset=2;

        if (pixel<=edge_length) {
            return pixel+offset;
        }

        else if (pixel>edge_length && pixel<=edge_length+led_ring_edge_offset){
            return pixel+(LARGE_OUTER_STAR_EDGE_LENGTH*9)*(-1)*(pixel-edge_length-led_ring_edge_offset)+(pixel-edge_length);
        }

        else if (pixel>edge_length+led_ring_edge_offset && pixel<edge_length*2){
            return pixel+offset+edge_length*7;
        } else if (pixel>=edge_length*2 && pixel<edge_length*3-led_ring_edge_offset){
            return pixel+offset-edge_length*2;
        }
        else if (pixel==edge_length*3-led_ring_edge_offset){
            return pixel+(LARGE_OUTER_STAR_EDGE_LENGTH*9)*(pixel-(edge_length*3-led_ring_edge_offset))+(pixel-(edge_length*3)+1);
        }
        else if (pixel==edge_length*3-led_ring_edge_offset+1){
            return pixel+(LARGE_OUTER_STAR_EDGE_LENGTH*9)*(pixel-(edge_length*3-led_ring_edge_offset))+(pixel-(edge_length*3)-2);
        }

        else if (pixel>=edge_length*3 && pixel<=edge_length*5){
            return pixel+offset-edge_length;
        }

        else if (pixel==edge_length*5+led_ring_edge_offset-1){
            return pixel+(LARGE_OUTER_STAR_EDGE_LENGTH*9)*(-1)*(pixel-edge_length*5-led_ring_edge_offset)-1;
        }

        else if (pixel==edge_length*5+led_ring_edge_offset){
            return pixel+(LARGE_OUTER_STAR_EDGE_LENGTH*9)*(-1)*(pixel-edge_length*5-led_ring_edge_offset)+3;
        }

        else if (pixel>edge_length*5+led_ring_edge_offset && pixel<edge_length*7-led_ring_edge_offset){
            return pixel+offset-edge_length*3;
        }
        
        else if (pixel==edge_length*7-led_ring_edge_offset){
            return pixel+(LARGE_OUTER_STAR_EDGE_LENGTH*9)*(pixel-(edge_length*7-led_ring_edge_offset))+(pixel-(edge_length*7)+2);
        }
        else if (pixel==edge_length*7-led_ring_edge_offset+1){
            return pixel+(LARGE_OUTER_STAR_EDGE_LENGTH*9)*(pixel-(edge_length*7-led_ring_edge_offset))+(pixel-(edge_length*7)-4);
        }

        else if (pixel>=edge_length*7 && pixel<=edge_length*9){
            return pixel+offset-edge_length*2;
        }

        else if (pixel==edge_length*9+led_ring_edge_offset-1){
            return pixel+(LARGE_OUTER_STAR_EDGE_LENGTH*9)*(-1)*(pixel-edge_length*9-led_ring_edge_offset)-3;
        }

        else if (pixel==edge_length*9+led_ring_edge_offset){
            return pixel+(LARGE_OUTER_STAR_EDGE_LENGTH*9)*(-1)*(pixel-edge_length*9-led_ring_edge_offset)+4;
        }

        else if (pixel>edge_length*9+led_ring_edge_offset && pixel<edge_length*11-led_ring_edge_offset){
            return pixel+offset-edge_length*4;
        }

        else if (pixel==edge_length*11-led_ring_edge_offset){
            return pixel+(LARGE_OUTER_STAR_EDGE_LENGTH*9)*(pixel-(edge_length*11-led_ring_edge_offset))+(pixel-(edge_length*11)+3);
        }
        else if (pixel==edge_length*11-led_ring_edge_offset+1){
            return pixel+(LARGE_OUTER_STAR_EDGE_LENGTH*9)*(pixel-(edge_length*11-led_ring_edge_offset))+(pixel-(edge_length*11)-6);
        }

        else if (pixel>=edge_length*11 && pixel<edge_length*12){
            return pixel+offset-edge_length*3;
        }
    }

    return -1;
}

// Patterns
int8_t LargeStar::setAllBlack() {
  for(uint16_t i=0; i<TOTAL_LED_LARGE_STAR; i++) {
    star.setPixel(i+this->m_t_channel_offset, 0);
    star.setPixel(i+this->m_b_channel_offset, 0);
  }
    star.show();
  return ANIMATION_COMPLETE;
}

// Fill the dots one after the other with a color
int8_t LargeStar::colorWipe(uint8_t ring_type,uint32_t c, uint16_t wait) {
  for(uint16_t i=0; i<this->numPixels(ring_type); i++) {
    star.setPixel(this->Pixel(ring_type, i), c);
    star.show();
    delay(wait);
  }
  return ANIMATION_COMPLETE;
}


int8_t LargeStar::colorStar(uint8_t ring_type,uint32_t c) {
  for(uint16_t i=0; i<this->numPixels(ring_type); i++) {
    star.setPixel(this->Pixel(ring_type, i), c);
  }
  return 0;
}

int8_t LargeStar::colorStar(uint8_t ring_type, uint32_t c, uint8_t start_index, uint8_t skip) {
  for(uint16_t i=start_index; i<this->numPixels(ring_type); i=i+skip+1) {
    star.setPixel(this->Pixel(ring_type, i), c);
  }
  return 0;
}

int8_t LargeStar::rainbowFade2White(uint8_t ring_type,uint8_t wait, int rainbowLoops, int whiteLoops) {
  float fadeMax = 100.0;
  int fadeVal = 0;
  uint32_t wheelVal;
  int redVal, greenVal, blueVal;

  for(int k = 0 ; k < rainbowLoops ; k ++){
    
    for(int j=0; j<256; j++) { // 5 cycles of all colors on wheel

      for(int i=0; i< this->numPixels(ring_type); i++) {

        wheelVal = Wheel(((i * 256 / this->numPixels(ring_type)) + j) & 255);

        redVal = red(wheelVal) * float(fadeVal/fadeMax);
        greenVal = green(wheelVal) * float(fadeVal/fadeMax);
        blueVal = blue(wheelVal) * float(fadeVal/fadeMax);
        star.setPixel(this->Pixel(ring_type, i), color( redVal, greenVal, blueVal ) );

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

        for(uint16_t i=0; i < this->numPixels(ring_type); i++) {
            star.setPixel(this->Pixel(ring_type, i), this->color(0,0,0, largeStar_gamma[j] ) );
          }
          star.show();
        }

        delay(2000);
    for(int j = 255; j >= 0 ; j--){

        for(uint16_t i=0; i < this->numPixels(ring_type); i++) {
            star.setPixel(this->Pixel(ring_type, i), this->color(0,0,0, largeStar_gamma[j] ) );
          }
          star.show();
        }
  }
  delay(500);
  return 0;
}

uint32_t LargeStar::Wheel(byte WheelPos) {
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

uint32_t LargeStar::WheelWhite(byte WheelPos) {
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

uint32_t LargeStar::WheelRedGreen(byte WheelPos) {

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

uint8_t LargeStar::white(uint32_t c) {
  return (c >>24);
}
uint8_t LargeStar::red(uint32_t c) {
  return (c >> 16);
}
uint8_t LargeStar::green(uint32_t c) {
  return (c >> 8);
}
uint8_t LargeStar::blue(uint32_t c) {
  return (c);
}

int8_t LargeStar::colorFromEdge(uint32_t color,uint16_t wait){
  
  for(uint8_t index = 0; index <= starEdgeLength[INNER_RING]; index++)
  {
    for(uint8_t side = 0; side < 6; side++)
    {
      star.setPixel(this->Pixel(INNER_RING,InnerStarInnerPoints[side]-index), color);
      star.setPixel(this->Pixel(INNER_RING,InnerStarInnerPoints[side]+index), color);
    }
      delay(wait);
      star.show();
  }
  for(uint8_t index = 0; index <= starEdgeLength[MIDDLE_RING]; index++)
  {
    for(uint8_t side = 0; side < 6; side++)
    {
      star.setPixel(this->Pixel(MIDDLE_RING,MiddleStarInnerPoints[side]-index), color);
      star.setPixel(this->Pixel(MIDDLE_RING,MiddleStarInnerPoints[side]+index), color);
    }
      delay(wait);
      star.show();
  }
  for(uint8_t index = 0; index <= starEdgeLength[OUTER_RING]; index++)
  {
    for(uint8_t side = 0; side < 6; side++)
    {
      star.setPixel(this->Pixel(OUTER_RING,OuterStarInnerPoints[side]-index), color);
      star.setPixel(this->Pixel(OUTER_RING,OuterStarInnerPoints[side]+index), color);
    }
      delay(wait);
      star.show();
  }
  return ANIMATION_COMPLETE;
}

int8_t LargeStar::colorFromEdgeFade(uint16_t wait,uint8_t speed){
  uint32_t wheelVal;
  int redVal, greenVal,blueVal=0;
  uint16_t wheel_const_outer= (256/(starEdgeLength[OUTER_RING]*3));
  
  for(int j=0; j<256; j++) {
    for(uint8_t ledIndex = 0; ledIndex <= starEdgeLength[OUTER_RING]; ledIndex++){
      wheelVal = WheelRedGreen(((ledIndex * wheel_const_outer) + j) & 255);
      redVal = red(wheelVal);
      greenVal = green(wheelVal);
      for(uint8_t side = 0; side < 6; side++)
      {
        star.setPixel(this->Pixel(OUTER_RING,OuterStarInnerPoints[side]-ledIndex), this->color(redVal,greenVal,blueVal));
        star.setPixel(this->Pixel(OUTER_RING,OuterStarInnerPoints[side]+ledIndex), this->color(redVal,greenVal,blueVal));
      
        if (ledIndex<=starEdgeLength[MIDDLE_RING]) {
          star.setPixel(this->Pixel(MIDDLE_RING,MiddleStarInnerPoints[side]-ledIndex), this->color(redVal,greenVal,blueVal));
          star.setPixel(this->Pixel(MIDDLE_RING,MiddleStarInnerPoints[side]+ledIndex), this->color(redVal,greenVal,blueVal));
        }
        
        if (ledIndex<=starEdgeLength[INNER_RING]) {
          star.setPixel(this->Pixel(INNER_RING,InnerStarInnerPoints[side]-ledIndex), this->color(redVal,greenVal,blueVal));
          star.setPixel(this->Pixel(INNER_RING,InnerStarInnerPoints[side]+ledIndex), this->color(redVal,greenVal,blueVal));
        }
      }
      //Updates Faster
      if(ledIndex%speed==0){
        star.show();
      }
    }
    delayMicroseconds(wait);
  }
  return ANIMATION_COMPLETE;
}


int8_t LargeStar::rainbowAll(uint8_t wait, int rainbowLoops) {
  float fadeMax = 100.0;
  int fadeVal = 0;
  uint32_t wheelVal;
  int redVal, greenVal, blueVal;

  for(int k = 0 ; k < rainbowLoops ; k ++){
    
    for(int j=0; j<256; j++) { // 5 cycles of all colors on wheel

      for(int i=0; i< this->numPixels(INNER_RING); i++) {

        wheelVal = Wheel(((i * 256 / this->numPixels(INNER_RING)) + j) & 255);

        redVal = red(wheelVal) * float(fadeVal/fadeMax);
        greenVal = green(wheelVal) * float(fadeVal/fadeMax);
        blueVal = blue(wheelVal) * float(fadeVal/fadeMax);
        star.setPixel( this->Pixel(INNER_RING,i), this->color( redVal, greenVal, blueVal ) );

      }
      for(int i=0; i< this->numPixels(MIDDLE_RING); i++) {

        wheelVal = Wheel(((i * 256 / this->numPixels(MIDDLE_RING)) + j) & 255);

        redVal = red(wheelVal) * float(fadeVal/fadeMax);
        greenVal = green(wheelVal) * float(fadeVal/fadeMax);
        blueVal = blue(wheelVal) * float(fadeVal/fadeMax);
        star.setPixel( this->Pixel(MIDDLE_RING,i), this->color( redVal, greenVal, blueVal ) );

      }
      for(int i=0; i< this->numPixels(OUTER_RING); i++) {

        wheelVal = Wheel(((i * 256 / this->numPixels(OUTER_RING)) + j) & 255);

        redVal = red(wheelVal) * float(fadeVal/fadeMax);
        greenVal = green(wheelVal) * float(fadeVal/fadeMax);
        blueVal = blue(wheelVal) * float(fadeVal/fadeMax);
        star.setPixel( this->Pixel(OUTER_RING,i), this->color( redVal, greenVal, blueVal ) );

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
  return ANIMATION_COMPLETE;
}

int8_t LargeStar::RainbowEdgeRotate(uint16_t wait){
  uint32_t wheelVal;
  int redVal, greenVal, blueVal;
  uint16_t wheel_const= (256/(6));

  for(int j=0; j<256; j++) {
    for(uint8_t side = 0; side < 6; side++)
    {
      wheelVal = Wheel(((side * wheel_const) + j) & 255); //Full Rainbow 
      redVal = red(wheelVal);
      greenVal = green(wheelVal);
      blueVal= blue(wheelVal);
      for(uint8_t ledIndex = 0; ledIndex <= starEdgeLength[OUTER_RING]; ledIndex++)
      {
        star.setPixel(this->Pixel(OUTER_RING,OuterStarOuterPoints[side]+ledIndex), this->color(redVal,greenVal,blueVal));
        if(side==0 && ledIndex<starEdgeLength[OUTER_RING]-1){
          star.setPixel(this->Pixel(OUTER_RING,(starEdgeLength[OUTER_RING]*12)-1-ledIndex), this->color(redVal,greenVal,blueVal));
        }else if(ledIndex<starEdgeLength[OUTER_RING]){
          star.setPixel(this->Pixel(OUTER_RING,OuterStarOuterPoints[side]-ledIndex), this->color(redVal,greenVal,blueVal));
        }
        if (ledIndex <= starEdgeLength[MIDDLE_RING]) {
          star.setPixel(this->Pixel(MIDDLE_RING,MiddleStarOuterPoints[side]+ledIndex), this->color(redVal,greenVal,blueVal));
          if(side==0 && ledIndex<starEdgeLength[MIDDLE_RING]-1){
            star.setPixel(this->Pixel(MIDDLE_RING,(starEdgeLength[MIDDLE_RING]*12)-1-ledIndex), this->color(redVal,greenVal,blueVal));
          }else if(ledIndex<starEdgeLength[MIDDLE_RING]){
            star.setPixel(this->Pixel(MIDDLE_RING,MiddleStarOuterPoints[side]-ledIndex), this->color(redVal,greenVal,blueVal));
          }
        }
        if (ledIndex <= starEdgeLength[INNER_RING]) {
          star.setPixel(this->Pixel(INNER_RING,InnerStarOuterPoints[side]+ledIndex), this->color(redVal,greenVal,blueVal));
          if(side==0 && ledIndex<starEdgeLength[INNER_RING]-1){
            star.setPixel(this->Pixel(INNER_RING,(starEdgeLength[INNER_RING]*12)-1-ledIndex), this->color(redVal,greenVal,blueVal));
          }else if(ledIndex<starEdgeLength[INNER_RING]){
            star.setPixel(this->Pixel(INNER_RING,InnerStarOuterPoints[side]-ledIndex), this->color(redVal,greenVal,blueVal));
          }
        }
      }
      star.show();
    }
  delay(wait);
  }
  return ANIMATION_COMPLETE;
}


int8_t LargeStar::GreenStarInwards(uint16_t wait){
  this->colorStar(OUTER_RING,GREEN_COLOR);
  this->colorStar(MIDDLE_RING,RED_COLOR);
  this->colorStar(INNER_RING,RED_COLOR);
  star.show();
  delay(wait);
  this->colorStar(OUTER_RING,RED_COLOR);
  this->colorStar(MIDDLE_RING,GREEN_COLOR);
  star.show();
  delay(wait);
  this->colorStar(OUTER_RING,RED_COLOR);
  this->colorStar(MIDDLE_RING,RED_COLOR);
  this->colorStar(INNER_RING,GREEN_COLOR);
  star.show();
  delay(wait);
  return ANIMATION_COMPLETE;
}


int8_t LargeStar::WhiteSpreadStarToHexagon(uint16_t wait,uint8_t speed){
  uint32_t wheelVal;
  int redVal=0, greenVal=0,whiteVal, blueVal=0;
  uint16_t wheel_const_outer= (256/(starEdgeLength[OUTER_RING]*3));
  
  for(int j=0; j<256; j++) {
    for(uint8_t ledIndex = 0; ledIndex <= starEdgeLength[OUTER_RING]; ledIndex++){
      wheelVal = WheelWhite(((ledIndex * wheel_const_outer) + j) & 255);
      whiteVal =white(wheelVal);
      for(uint8_t side = 0; side < 6; side++)
      {
        star.setPixel(this->Pixel(OUTER_RING,OuterStarInnerPoints[side]-ledIndex), this->color(redVal,greenVal,blueVal,whiteVal));
        star.setPixel(this->Pixel(OUTER_RING,OuterStarInnerPoints[side]+ledIndex), this->color(redVal,greenVal,blueVal,whiteVal));
      
        if (ledIndex<=starEdgeLength[MIDDLE_RING]) {
          star.setPixel(this->Pixel(MIDDLE_RING,MiddleStarInnerPoints[side]-ledIndex), this->color(redVal,greenVal,blueVal,whiteVal));
          star.setPixel(this->Pixel(MIDDLE_RING,MiddleStarInnerPoints[side]+ledIndex), this->color(redVal,greenVal,blueVal,whiteVal));
        }
        
        if (ledIndex<=starEdgeLength[INNER_RING]) {
          star.setPixel(this->Pixel(INNER_RING,InnerStarInnerPoints[side]-ledIndex), this->color(redVal,greenVal,blueVal,whiteVal));
          star.setPixel(this->Pixel(INNER_RING,InnerStarInnerPoints[side]+ledIndex), this->color(redVal,greenVal,blueVal,whiteVal));
        }
      }
      //Updates Faster
      if(ledIndex%speed==0){
        star.show();
      }
    }
    delayMicroseconds(wait);
  }
  return ANIMATION_COMPLETE;
}

int8_t LargeStar::GreenRedSpiral(uint8_t wait, uint8_t colorSpeed, uint8_t colorLength , uint8_t sections) {
  if(colorLength >= this->numPixels(OUTER_RING)) {
      colorLength = this->numPixels(OUTER_RING) - 1;
    }

  int head_outer = colorLength -1;
  int tail_outer = 0;
  int head_middle = colorLength -1;
  int tail_middle = 0;
  int head_inner = colorLength - 1;
  int tail_inner = 0;

  int loops = 10;
  int loopNum = 0;

  static unsigned long lastTime = 0;
  while(true){
    for(uint16_t i=0; i<this->numPixels(OUTER_RING)/sections; i++) {
      if((i >= tail_outer && i <= head_outer) || (tail_outer > head_outer && i >= tail_outer) || (tail_outer > head_outer && i <= head_outer) ){
        for(uint8_t j = 0; j < sections; j++)
        {
          star.setPixel(this->Pixel(OUTER_RING,i+j*(LARGE_OUTER_STAR_EDGE_LENGTH*12/sections)), GREEN_COLOR );
        }
      }
      else{
        for(uint8_t j = 0; j < sections; j++)
        {
          star.setPixel(this->Pixel(OUTER_RING,i+j*(LARGE_OUTER_STAR_EDGE_LENGTH*12/sections)), RED_COLOR );
        }
      }
    }
    for(uint16_t i=0; i<this->numPixels(MIDDLE_RING)/sections; i++) {
      if((i >= tail_middle && i <= head_middle) || (tail_middle > head_middle && i >= tail_middle) || (tail_middle > head_middle && i <= head_middle) ){
        
        for(uint8_t j = 0; j < sections; j++)
        {
          star.setPixel(this->Pixel(MIDDLE_RING,i+j*(LARGE_MIDDLE_STAR_EDGE_LENGTH*12/sections)), GREEN_COLOR );
        }
      }
      else{
        for(uint8_t j = 0; j < sections; j++)
        {
          star.setPixel(this->Pixel(MIDDLE_RING,i+j*(LARGE_MIDDLE_STAR_EDGE_LENGTH*12/sections)), RED_COLOR);
        }
      }
    }
    for(uint16_t i=0; i<this->numPixels(INNER_RING)/sections; i++) {
      if((i >= tail_inner && i <= head_inner) || (tail_inner > head_inner && i >= tail_inner) || (tail_inner > head_inner && i <= head_inner) ){
        
        for(uint8_t j = 0; j < sections; j++)
        {
          star.setPixel(this->Pixel(INNER_RING,i+j*(LARGE_INNER_STAR_EDGE_LENGTH*12/sections)), GREEN_COLOR );
        }
      }
      else{
        for(uint8_t j = 0; j < sections; j++)
        {
        star.setPixel(this->Pixel(INNER_RING,i+j*(LARGE_INNER_STAR_EDGE_LENGTH*12/sections)), RED_COLOR);
        }
      }
    }


    if(millis() - lastTime > colorSpeed) {
      head_outer++;
      tail_outer++;
      head_middle++;
      tail_middle++;
      head_inner++;
      tail_inner++;
      
      if(head_outer == this->numPixels(OUTER_RING)/sections){
        loopNum++;
      }
      lastTime = millis();
    }
    

    if(loopNum == loops) break;
    //Speed compensation
    if (head_outer%LARGE_OUTER_STAR_EDGE_LENGTH==0) {
      head_outer++;
      tail_outer++;
      head_outer++;
      tail_outer++;
    }
    if (head_middle%LARGE_MIDDLE_STAR_EDGE_LENGTH==0) {
      head_middle++;
      tail_middle++;
    }
    
    head_outer%=this->numPixels(OUTER_RING)/sections;
    tail_outer%=this->numPixels(OUTER_RING)/sections;
    head_middle%=this->numPixels(MIDDLE_RING)/sections;
    tail_middle%=this->numPixels(MIDDLE_RING)/sections;
    head_inner%=this->numPixels(INNER_RING)/sections;
    tail_inner%=this->numPixels(INNER_RING)/sections;
    star.show();
    delayMicroseconds(wait);
  }
  return ANIMATION_COMPLETE;
}

int8_t LargeStar::ChristmasPattern(uint8_t pattern_num){
  return ChristmasPattern(pattern_num, 1000);
}
int8_t LargeStar::ChristmasPattern(uint8_t pattern_num,uint16_t wait){
  
  switch (pattern_num)
  {
    case ALTERNATE_RINGS:
      this->colorStar(INNER_RING,RED_COLOR);
      this->colorStar(MIDDLE_RING,GREEN_COLOR);
      this->colorStar(OUTER_RING,RED_COLOR);
      star.show();
      delay(wait);
      this->colorStar(INNER_RING,GREEN_COLOR);
      this->colorStar(MIDDLE_RING,RED_COLOR);
      this->colorStar(OUTER_RING,GREEN_COLOR);
      star.show();
      delay(wait);
      break;

    case ALTERNATE_LEDS:
      this->colorStar(INNER_RING,RED_COLOR,0,1);
      this->colorStar(INNER_RING,GREEN_COLOR,1,1);
      this->colorStar(MIDDLE_RING,GREEN_COLOR,0,1);
      this->colorStar(MIDDLE_RING,RED_COLOR,1,1);
      this->colorStar(OUTER_RING,RED_COLOR,0,1);
      this->colorStar(OUTER_RING,GREEN_COLOR,1,1);
      star.show();
      delay(wait);
      this->colorStar(INNER_RING,GREEN_COLOR,0,1);
      this->colorStar(INNER_RING,RED_COLOR,1,1);
      this->colorStar(MIDDLE_RING,RED_COLOR,0,1);
      this->colorStar(MIDDLE_RING,GREEN_COLOR,1,1);
      this->colorStar(OUTER_RING,GREEN_COLOR,0,1);
      this->colorStar(OUTER_RING,RED_COLOR,1,1);
      star.show();
      delay(wait);
      break;

    case GREEN_RED_SPIRAL:
      this->GreenRedSpiral(wait,LARGE_STAR_GREEN_RED_SPIRAL_SPEED,LARGE_STAR_GREEN_SPIRAL_LENGTH,LARGE_STAR_GREEN_RED_SPIRAL_SECTIONS);
      break;

    case GREEN_STAR_INWARDS:
      this->GreenStarInwards(wait);
      break;

    case SNOW_SPREAD:
      this->WhiteSpreadStarToHexagon(wait,5);
      break;

    case RED_GREEN_SPREAD: 
      this->colorFromEdgeFade(wait,5);
      break;

    default:
      break;
  }
  return ANIMATION_COMPLETE;
}


//Hexagon Patterns
int8_t LargeStar::Hexagon_RainbowEdgeRotate(uint16_t wait){
  uint32_t wheelVal;
  int redVal, greenVal, blueVal;
  uint16_t wheel_const= (256/(6));

  for(int j=0; j<256; j++) {
    for(uint8_t side = 0; side < 6; side++)
    {
      wheelVal = Wheel(((side * wheel_const) + j) & 255); //Full Rainbow 
      redVal = red(wheelVal);
      greenVal = green(wheelVal);
      blueVal= blue(wheelVal);
      for(uint8_t ledIndex = 0; ledIndex <= starEdgeLength[OUTER_RING]; ledIndex++)
      {
        star.setPixel(hexagon_strip.Pixel(OUTER_RING,OuterStarOuterPoints[side]+ledIndex), this->color(redVal,greenVal,blueVal));
        if(side==0 && ledIndex<starEdgeLength[OUTER_RING]-1){
          star.setPixel(hexagon_strip.Pixel(OUTER_RING,(starEdgeLength[OUTER_RING]*12)-1-ledIndex), this->color(redVal,greenVal,blueVal));
        }else if(ledIndex<starEdgeLength[OUTER_RING]){
          star.setPixel(hexagon_strip.Pixel(OUTER_RING,OuterStarOuterPoints[side]-ledIndex), this->color(redVal,greenVal,blueVal));
        }
        if (ledIndex <= starEdgeLength[MIDDLE_RING]) {
          star.setPixel(hexagon_strip.Pixel(MIDDLE_RING,MiddleStarOuterPoints[side]+ledIndex), this->color(redVal,greenVal,blueVal));
          if(side==0 && ledIndex<starEdgeLength[MIDDLE_RING]-1){
            star.setPixel(hexagon_strip.Pixel(MIDDLE_RING,(starEdgeLength[MIDDLE_RING]*12)-1-ledIndex), this->color(redVal,greenVal,blueVal));
          }else if(ledIndex<starEdgeLength[MIDDLE_RING]){
            star.setPixel(hexagon_strip.Pixel(MIDDLE_RING,MiddleStarOuterPoints[side]-ledIndex), this->color(redVal,greenVal,blueVal));
          }
        }
        if (ledIndex <= starEdgeLength[INNER_RING]) {
          star.setPixel(hexagon_strip.Pixel(INNER_RING,InnerStarOuterPoints[side]+ledIndex), this->color(redVal,greenVal,blueVal));
          if(side==0 && ledIndex<starEdgeLength[INNER_RING]-1){
            star.setPixel(hexagon_strip.Pixel(INNER_RING,(starEdgeLength[INNER_RING]*12)-1-ledIndex), this->color(redVal,greenVal,blueVal));
          }else if(ledIndex<starEdgeLength[INNER_RING]){
            star.setPixel(hexagon_strip.Pixel(INNER_RING,InnerStarOuterPoints[side]-ledIndex), this->color(redVal,greenVal,blueVal));
          }
        }
      }
      star.show();
    }
  delay(wait);
  }
  return ANIMATION_COMPLETE;
}