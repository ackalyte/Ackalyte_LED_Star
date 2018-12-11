/*!
* @file        hexagon.cpp
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
*/
#include "hexagon.h"


Hexagon::Hexagon(uint8_t HexagonType):_hexagonType(HexagonType){
}


Hexagon::~Hexagon()
{
}

int16_t Hexagon::mapLEDs(uint16_t led_num){
    uint8_t edge_length;
    uint16_t total_led;
    if(this->_hexagonType==HEXAGON_SMALL){
        edge_length=SMALL_HEXAGON_EDGE_LENGTH;
        total_led=TOTAL_LED_SMALL_HEXAGON;
    }else if(this->_hexagonType==HEXAGON_MEDIUM){
        edge_length=MEDIUM_HEXAGON_EDGE_LENGTH;
        total_led=TOTAL_LED_MEDIUM_HEXAGON;
    }
    if(led_num<=edge_length){
        return led_num+edge_length;
    } else if (led_num>edge_length && led_num<edge_length*2){
        return led_num+total_led;
    } else if (led_num>=edge_length*2 && led_num<=edge_length*3){
        return led_num+edge_length*2;
    }else if (led_num>edge_length*3 && led_num<edge_length*4){
        return led_num+total_led+edge_length;
    }else if (led_num>=edge_length*4 && led_num<=edge_length*5){
        return led_num+edge_length*3;
    }else if (led_num>edge_length*5 && led_num<edge_length*6){
        return led_num+total_led+edge_length*2;
    }
    return -1;
}

/**
 * @brief 
 * 
 * @param pixel 
 * @return uint16_t 
 */
uint16_t Hexagon::Pixel(uint16_t pixel){
 return mapLEDs(pixel);
}

uint16_t Hexagon::numPixels(){
    
    if (this->_hexagonType==HEXAGON_SMALL) {
        return SMALL_HEXAGON_EDGE_LENGTH*6;
    }
    else if(this->_hexagonType==HEXAGON_MEDIUM){
        return MEDIUM_HEXAGON_EDGE_LENGTH*6;
    }
        return 0;
}
uint16_t Hexagon::totalLEDs(){
    if (this->_hexagonType==HEXAGON_SMALL) {
        return TOTAL_LED_SMALL_HEXAGON*2;
    }
    else if(this->_hexagonType==HEXAGON_MEDIUM){
        return TOTAL_LED_MEDIUM_HEXAGON*2;
    }
    else if(this->_hexagonType==HEXAGON_LARGE){
        return 120;
    }
        return 0;
}