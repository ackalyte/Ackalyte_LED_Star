/*!
* @file        LargeHexagon.cpp
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
#include "largeHexagon.h"

LargeHexagon::LargeHexagon(uint16_t top_channel_offset, uint16_t bot_channel_offset):m_t_channel_offset(top_channel_offset),m_b_channel_offset(bot_channel_offset){

}

LargeHexagon::~LargeHexagon(){
    this->m_t_channel_offset=0;
    this->m_b_channel_offset=0;
}

uint16_t LargeHexagon::numPixels(uint16_t ring_type){
    if (ring_type==INNER_HEX_RING) {
        return LARGE_INNER_HEXAGON_EDGE_LENGTH*6;
    }else if(ring_type==MIDDLE_HEX_RING) {
        return LARGE_MIDDLE_HEXAGON_EDGE_LENGTH*6;
    }else if(ring_type==OUTER_HEX_RING){
        return LARGE_OUTER_HEXAGON_EDGE_LENGTH*6;
    }
    return 0;
}


uint16_t LargeHexagon::Pixel(uint8_t ring_type,uint16_t pixel){
    uint8_t triangleStrip = findTriangleStrip(ring_type,pixel);
    if(triangleStrip==HEX_TOP_TRIANGLE){
        return mapLEDs(ring_type,pixel)+this->m_t_channel_offset;
    }else if(triangleStrip==HEX_BOTTOM_TRIANGLE){
        return mapLEDs(ring_type,pixel)+this->m_b_channel_offset;
    }
    else{
        return -1;
    }
}


uint8_t LargeHexagon::findTriangleStrip(uint8_t ring_type,uint16_t pixel){
    uint8_t edge_length=0;
    uint8_t led_ring_edge_offset=0;
    
    if (ring_type==OUTER_HEX_RING) {
        edge_length=LARGE_OUTER_HEXAGON_EDGE_LENGTH;
        led_ring_edge_offset=2;
    }else if (ring_type==MIDDLE_HEX_RING) {
        edge_length=LARGE_MIDDLE_HEXAGON_EDGE_LENGTH;
        led_ring_edge_offset=1;
    }if (ring_type==INNER_HEX_RING) {
        edge_length=LARGE_INNER_HEXAGON_EDGE_LENGTH;
        led_ring_edge_offset=0;
    }
    
    if (pixel<=edge_length+led_ring_edge_offset) {
        return HEX_TOP_TRIANGLE;
    }else if (pixel>edge_length+led_ring_edge_offset && pixel<edge_length*2-led_ring_edge_offset){
        return HEX_BOTTOM_TRIANGLE;
    } else if (pixel>=edge_length*2-led_ring_edge_offset && pixel<=edge_length*3+led_ring_edge_offset){
        return HEX_TOP_TRIANGLE;
    }else if (pixel>edge_length*3+led_ring_edge_offset && pixel<edge_length*4-led_ring_edge_offset){
        return HEX_BOTTOM_TRIANGLE;
    }else if (pixel>=edge_length*4-led_ring_edge_offset && pixel<=edge_length*5+led_ring_edge_offset){
        return HEX_TOP_TRIANGLE;
    }else if (pixel>edge_length*5+led_ring_edge_offset && pixel<edge_length*6-led_ring_edge_offset){
        return HEX_BOTTOM_TRIANGLE;
    }else if (pixel>=edge_length*6-led_ring_edge_offset && pixel<edge_length*6){
        return HEX_TOP_TRIANGLE;
    }

    return 2;
}

int32_t LargeHexagon::mapLEDs(uint8_t ring_type,uint16_t pixel){
    uint8_t edge_length=0;
    uint8_t offset=0;
    uint8_t led_ring_edge_offset=0;
    if (ring_type==OUTER_HEX_RING) {
        edge_length=LARGE_OUTER_HEXAGON_EDGE_LENGTH;
        led_ring_edge_offset=2;
        if (pixel<=edge_length) {
            return pixel+edge_length+offset;
        }
        else if (pixel==edge_length+led_ring_edge_offset-1){
            return pixel+edge_length+offset+LARGE_OUTER_HEXAGON_EDGE_LENGTH*9-2;
        }
        else if (pixel==edge_length+led_ring_edge_offset){
            return pixel+edge_length+offset+(LARGE_MIDDLE_HEXAGON_EDGE_LENGTH+LARGE_OUTER_HEXAGON_EDGE_LENGTH)*9-4;
        }
        else if (pixel>edge_length+led_ring_edge_offset && pixel<edge_length*2-led_ring_edge_offset){
            return pixel+offset;
        }
        else if (pixel==edge_length*2-led_ring_edge_offset){
            return pixel+edge_length*2+offset+(LARGE_MIDDLE_HEXAGON_EDGE_LENGTH+LARGE_OUTER_HEXAGON_EDGE_LENGTH)*9-8;
        }else if (pixel==edge_length*2-led_ring_edge_offset+1){
            return pixel+edge_length*2+offset+LARGE_OUTER_HEXAGON_EDGE_LENGTH*9-4;
        }
         else if (pixel>=edge_length*2 && pixel<=edge_length*3){
            return pixel+offset+edge_length*2;
        }
        else if (pixel==edge_length*3+led_ring_edge_offset-1){
            return pixel+edge_length*2+offset+LARGE_OUTER_HEXAGON_EDGE_LENGTH*9-5;
        }
        else if (pixel==edge_length*3+led_ring_edge_offset){
            return pixel+edge_length*2+offset+(LARGE_MIDDLE_HEXAGON_EDGE_LENGTH+LARGE_OUTER_HEXAGON_EDGE_LENGTH)*9-10;
        }

        else if (pixel>edge_length*3+led_ring_edge_offset && pixel<edge_length*4-led_ring_edge_offset){
            return pixel+offset+edge_length;
        }
        else if (pixel==edge_length*4-led_ring_edge_offset){
            return pixel+edge_length*3+offset+(LARGE_MIDDLE_HEXAGON_EDGE_LENGTH+LARGE_OUTER_HEXAGON_EDGE_LENGTH)*9-14;
        } 
        else if (pixel==edge_length*4-led_ring_edge_offset+1){
            return pixel+edge_length*3+offset+LARGE_OUTER_HEXAGON_EDGE_LENGTH*9-7;
        } 
        else if (pixel>=edge_length*4 && pixel<=edge_length*5){
            return pixel+offset+edge_length*3;
        }
        else if (pixel==edge_length*5+led_ring_edge_offset-1){
            return pixel+edge_length*3+offset+LARGE_OUTER_HEXAGON_EDGE_LENGTH*9-8;
        }
        else if (pixel==edge_length*5+led_ring_edge_offset){
            return pixel+edge_length*3+offset+(LARGE_MIDDLE_HEXAGON_EDGE_LENGTH+LARGE_OUTER_HEXAGON_EDGE_LENGTH)*9-16;
        }
        
        else if (pixel>edge_length*5+led_ring_edge_offset && pixel<edge_length*6-led_ring_edge_offset){
            return pixel+offset+edge_length*2;
        }
        else if (pixel==edge_length*6-led_ring_edge_offset){
            return pixel+offset-edge_length*5+(LARGE_MIDDLE_HEXAGON_EDGE_LENGTH+LARGE_OUTER_HEXAGON_EDGE_LENGTH)*9-2;
        }
        else if (pixel==edge_length*6-led_ring_edge_offset+1){
            return pixel+offset-edge_length*5+LARGE_OUTER_HEXAGON_EDGE_LENGTH*9-1;
        }

    }else if (ring_type==MIDDLE_HEX_RING) {
        edge_length=LARGE_MIDDLE_HEXAGON_EDGE_LENGTH;
        offset=LARGE_OUTER_HEXAGON_EDGE_LENGTH*9;
        led_ring_edge_offset=1;

        if (pixel<=edge_length) {
            return pixel+edge_length+offset;
        }
        else if (pixel==edge_length+led_ring_edge_offset){
            return pixel+edge_length+offset+LARGE_MIDDLE_HEXAGON_EDGE_LENGTH*9-2;
        }

        else if (pixel>edge_length+led_ring_edge_offset && pixel<edge_length*2-led_ring_edge_offset){
            return pixel+offset;
        }
        else if (pixel==edge_length*2-led_ring_edge_offset){
            return pixel+edge_length*2+offset+LARGE_MIDDLE_HEXAGON_EDGE_LENGTH*9-4;
        } else if (pixel>edge_length*2-led_ring_edge_offset && pixel<edge_length*3+led_ring_edge_offset){
            return pixel+offset+edge_length*2;
        }else if (pixel==edge_length*3+led_ring_edge_offset){
            return pixel+edge_length*2+offset+LARGE_MIDDLE_HEXAGON_EDGE_LENGTH*9-5;
        }
        else if (pixel>edge_length*3+led_ring_edge_offset && pixel<edge_length*4-led_ring_edge_offset){
            return pixel+offset+edge_length;
        }
        else if (pixel==edge_length*4-led_ring_edge_offset){
            return pixel+edge_length*3+offset+LARGE_MIDDLE_HEXAGON_EDGE_LENGTH*9-7;
        } else if (pixel>edge_length*4-led_ring_edge_offset && pixel<edge_length*5+led_ring_edge_offset){
            return pixel+offset+edge_length*3;
        }else if (pixel==edge_length*5+led_ring_edge_offset){
            return pixel+edge_length*3+offset+LARGE_MIDDLE_HEXAGON_EDGE_LENGTH*9-8;
        }
        else if (pixel>edge_length*5+led_ring_edge_offset && pixel<edge_length*6-led_ring_edge_offset){
            return pixel+offset+edge_length*2;
        }else if (pixel==edge_length*6-led_ring_edge_offset){
            return pixel+offset-edge_length*5+LARGE_MIDDLE_HEXAGON_EDGE_LENGTH*9-1;
        }
    }else if (ring_type==INNER_HEX_RING) {
        edge_length=LARGE_INNER_HEXAGON_EDGE_LENGTH; 
        offset=LARGE_OUTER_HEXAGON_EDGE_LENGTH*9+LARGE_MIDDLE_HEXAGON_EDGE_LENGTH*9;

        if (pixel<=edge_length) {
            return pixel+edge_length+offset;
        }else if (pixel>edge_length && pixel<edge_length*2){
            return pixel+offset;
        } else if (pixel>=edge_length*2 && pixel<=edge_length*3){
            return pixel+offset+edge_length*2;
        }else if (pixel>edge_length*3 && pixel<edge_length*4){
            return pixel+offset+edge_length;
        }else if (pixel>=edge_length*4 && pixel<=edge_length*5){
            return pixel+offset+edge_length*3;
        }else if (pixel>edge_length*5 && pixel<edge_length*6){
            return pixel+offset+edge_length*2;
        }
    }

    return -1;
}
