#ifndef LARGESTAR_H
#define LARGESTAR_H
#include <stdint.h>
#include <AckaLED.h>
#include "largeHexagon.h"
#include "starDisplayBuffer.h"

enum largeStar_rings{
    INNER_RING=0,
    MIDDLE_RING,
    OUTER_RING
};
#ifndef STAR_H
enum basetee_channels{
    CHANNEL1=0,
    CHANNEL2,
    CHANNEL3,
    CHANNEL4,
    CHANNEL5,
    CHANNEL6,
    CHANNEL7,
    CHANNEL8,
    CHANNEL9,
    CHANNEL10,
    CHANNEL11,
    CHANNEL12,
    CHANNEL13,
    CHANNEL14,
    CHANNEL15,

    TOTAL_CHANNELS
};


enum Christmas_Pattern{
  ALTERNATE_RINGS=0,
  ALTERNATE_LEDS,
  GREEN_STAR_INWARDS,
  GREEN_RED_SPIRAL,
  SNOW_SPREAD,
  RED_GREEN_SPREAD,

  TOTAL_PATTERNS
};

#define TOTAL_LED_LARGE_STAR    162

#define GREEN_COLOR 0x0000FF00
#define RED_COLOR   0x00FF0000
#define WARM_WHITE_COLOR   0xFF000000
#define FULL_WHITE_COLOR   0xFFFFFFFF

#define ANIMATION_COMPLETE  0

#endif

#define LARGE_STAR_PATTERN_LOOP 5
#define LARGE_STAR_GREEN_RED_SPIRAL_SPEED    40
#define LARGE_STAR_GREEN_SPIRAL_LENGTH       3
#define LARGE_STAR_GREEN_RED_SPIRAL_SECTIONS 6

enum triangle_strip_type{
    TOP_TRIANGLE=0,
    BOTTOM_TRIANGLE
};


#define LARGE_OUTER_STAR_EDGE_LENGTH      7 
#define LARGE_MIDDLE_STAR_EDGE_LENGTH     6
#define LARGE_INNER_STAR_EDGE_LENGTH      5 




class LargeStar{
    public:

    LargeStar(StarDisplayBuffer& buff,uint8_t top_channel,uint8_t bot_channel);

    virtual ~LargeStar();
    
    uint16_t numPixels(uint16_t ring_type);

    void init();

    void show();

    uint32_t color(uint8_t r, uint8_t g, uint8_t b);
    uint32_t color(uint8_t r, uint8_t g, uint8_t b, uint8_t w);

    uint16_t Pixel(uint8_t ring_type,uint16_t pixel);
    //Patterns
    int8_t setAllBlack();
    int8_t colorWipe(uint8_t ring_type,uint32_t c, uint16_t wait); //Blocking
    int8_t colorStar(uint8_t ring_type,uint32_t c);
    int8_t colorStar(uint8_t ring_type,uint32_t c, uint8_t start_index, uint8_t skip);
    int8_t rainbowFade2White(uint8_t ring_type,uint8_t wait, int rainbowLoops, int whiteLoops);//Blocking
    int8_t colorFromEdge(uint32_t color,uint16_t wait);//Blocking
    int8_t colorFromEdgeFade(uint16_t wait,uint8_t speed);//Blocking
    int8_t rainbowAll(uint8_t wait, int rainbowLoops);
    int8_t RainbowEdgeRotate(uint16_t wait);
    int8_t GreenStarInwards(uint16_t wait);
    int8_t GreenRedSpiral(uint8_t wait, uint8_t colorSpeed, uint8_t colorLength , uint8_t sections);
    int8_t WhiteSpreadStarToHexagon(uint16_t wait,uint8_t speed);
    int8_t ChristmasPattern(uint8_t pattern_num);
    int8_t ChristmasPattern(uint8_t pattern_num,uint16_t wait);

    int8_t Hexagon_RainbowEdgeRotate(uint16_t wait);

    private:
    AckaLED star;
    LargeHexagon hexagon_strip;
    uint8_t m_brightness;
    uint8_t m_t_channel,m_b_channel;
    uint16_t m_t_channel_offset,m_b_channel_offset;

    uint8_t starEdgeLength[3]={LARGE_INNER_STAR_EDGE_LENGTH,
                            LARGE_MIDDLE_STAR_EDGE_LENGTH,
                            LARGE_OUTER_STAR_EDGE_LENGTH};
    uint8_t InnerStarInnerPoints[6]={1*LARGE_INNER_STAR_EDGE_LENGTH,
                                    3*LARGE_INNER_STAR_EDGE_LENGTH,
                                    5*LARGE_INNER_STAR_EDGE_LENGTH,
                                    7*LARGE_INNER_STAR_EDGE_LENGTH,
                                    9*LARGE_INNER_STAR_EDGE_LENGTH,
                                    11*LARGE_INNER_STAR_EDGE_LENGTH};

    uint8_t InnerStarOuterPoints[6]={0,
                                    2*LARGE_INNER_STAR_EDGE_LENGTH,
                                    4*LARGE_INNER_STAR_EDGE_LENGTH,
                                    6*LARGE_INNER_STAR_EDGE_LENGTH,
                                    8*LARGE_INNER_STAR_EDGE_LENGTH,
                                    10*LARGE_INNER_STAR_EDGE_LENGTH};

    uint8_t MiddleStarInnerPoints[6]={1*LARGE_MIDDLE_STAR_EDGE_LENGTH,
                                    3*LARGE_MIDDLE_STAR_EDGE_LENGTH,
                                    5*LARGE_MIDDLE_STAR_EDGE_LENGTH,
                                    7*LARGE_MIDDLE_STAR_EDGE_LENGTH,
                                    9*LARGE_MIDDLE_STAR_EDGE_LENGTH,
                                    11*LARGE_MIDDLE_STAR_EDGE_LENGTH};

    uint8_t MiddleStarOuterPoints[6]={0,
                                    2*LARGE_MIDDLE_STAR_EDGE_LENGTH,
                                    4*LARGE_MIDDLE_STAR_EDGE_LENGTH,
                                    6*LARGE_MIDDLE_STAR_EDGE_LENGTH,
                                    8*LARGE_MIDDLE_STAR_EDGE_LENGTH,
                                    10*LARGE_MIDDLE_STAR_EDGE_LENGTH};

    uint8_t OuterStarInnerPoints[6]={1*LARGE_OUTER_STAR_EDGE_LENGTH,
                                    3*LARGE_OUTER_STAR_EDGE_LENGTH,
                                    5*LARGE_OUTER_STAR_EDGE_LENGTH,
                                    7*LARGE_OUTER_STAR_EDGE_LENGTH,
                                    9*LARGE_OUTER_STAR_EDGE_LENGTH,
                                    11*LARGE_OUTER_STAR_EDGE_LENGTH};

    uint8_t OuterStarOuterPoints[6]={0,
                                    2*LARGE_OUTER_STAR_EDGE_LENGTH,
                                    4*LARGE_OUTER_STAR_EDGE_LENGTH,
                                    6*LARGE_OUTER_STAR_EDGE_LENGTH,
                                    8*LARGE_OUTER_STAR_EDGE_LENGTH,
                                    10*LARGE_OUTER_STAR_EDGE_LENGTH};
    


    uint8_t findTriangleStrip(uint8_t ring_type,uint16_t pixel);
    int32_t mapLEDs(uint8_t ring_type,uint16_t pixel);
    uint32_t Wheel(byte WheelPos);
    uint32_t WheelWhite(byte WheelPos);
    uint32_t WheelRedGreen(byte WheelPos);
    uint8_t white(uint32_t c);
    uint8_t red(uint32_t c);
    uint8_t green(uint32_t c);
    uint8_t blue(uint32_t c);
};
#endif/* LARGESTAR_H */