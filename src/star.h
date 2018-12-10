#ifndef STAR_H
#define STAR_H
#include <stdint.h>
#include <AckaLED.h>
#include "hexagon.h"
#include "starDisplayBuffer.h"

enum star_types{
    STAR_SMALL=0,
    STAR_MEDIUM,
    STAR_LARGE
};

#define TOTAL_LED_SMALL_STAR    27
#define TOTAL_LED_MEDIUM_STAR   45
#define TOTAL_LED_LARGE_STAR    162  

#define SMALL_STAR_EDGE_LENGTH      3
#define MEDIUM_STAR_EDGE_LENGTH     5

#ifndef LARGESTAR_H
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

#define GREEN_COLOR 0x0000FF00
#define RED_COLOR   0x00FF0000
#define WARM_WHITE_COLOR   0xFF000000
#define FULL_WHITE_COLOR   0xFFFFFFFF
#define PATTERN_LOOP 2
#define GREEN_RED_SPIRAL_SPEED    90
#define GREEN_SPIRAL_LENGTH       3
#define GREEN_RED_SPIRAL_SECTIONS 6

#define ANIMATION_COMPLETE  0

enum Christmas_Pattern{
  ALTERNATE_LEDS=0,
  GREEN_RED_SPIRAL,
  GREEN_STAR_INWARDS,
  SNOW_SPREAD,
  RED_GREEN_SPREAD,

  TOTAL_PATTERNS
};

#endif

class Star{
 public:
    /**
     * @brief Construct a new Star LED strip
     * 
     * @param StarType 
     */
    Star(StarDisplayBuffer& buff,uint8_t StarType, uint8_t channel);

    /**
     * @brief Destroy the Star object
     * 
     */
    virtual ~Star();
    
    /**
     * @brief Initialise star
     * 
     */
    void init();

    /**
     * @brief Display Star Pixel Data
     * 
     */
    void show();

    /**
     * @brief  Return actual led number mapped to the pixel of the star 
     * 
     * @param pixel 
     * @return uint16_t 
     */
    uint16_t Pixel(uint16_t pixel);

    /**
     * @brief  Return actual led number mapped to the pixel of the hexagon
     * 
     * @param pixel 
     * @return uint16_t 
     */
    uint16_t HexPixel(uint16_t pixel);
    /**
     * @brief Total number of visible pixel on the strip
     * 
     * @return uint16_t 
     */
    uint16_t numPixels();

    /**
     * @brief Total number of LEDs on the strip
     * 
     * @return uint16_t 
     */
    uint16_t totalLEDs();

    uint32_t color(uint8_t r, uint8_t g, uint8_t b);
    uint32_t color(uint8_t r, uint8_t g, uint8_t b, uint8_t w);


    //PATTERNS
    int8_t setAllBlack();
    int8_t setStarBlack();
    int8_t setHexagonBlack();
    
    int8_t colorWipe(uint32_t c, uint16_t wait);

    int8_t colorStar(uint32_t c);

    int8_t colorStar(uint32_t c, uint8_t start_index, uint8_t skip);

    int8_t colorWipeHexagon(uint32_t c, uint16_t wait);

    int8_t pulseWhite(uint8_t wait);

    int8_t rainbowFade2White(uint8_t wait, int rainbowLoops, int whiteLoops);

    int8_t whiteOverRainbow(uint8_t wait, uint8_t whiteSpeed, uint8_t whiteLength );
    int8_t fullWhite();

    // Slightly different, this makes the rainbow equally distributed throughout
    int8_t rainbowCycle(uint8_t wait);
    int8_t rainbow(uint8_t wait) ;

    // Input a value 0 to 255 to get a color value.
    // The colors are a transition r - g - b - back to r.
    uint32_t Wheel(byte WheelPos);
    uint32_t WheelRedGreen(byte WheelPos);
    uint32_t WheelWhite(byte WheelPos);

    uint8_t white(uint32_t c);
    uint8_t red(uint32_t c);
    uint8_t green(uint32_t c) ;
    uint8_t blue(uint32_t c);

    int8_t colorFromEdge(uint32_t color,uint16_t wait);

    int8_t colorFromEdgeFade(uint16_t wait);

    int8_t colorSpreadStarToHexagon(uint16_t wait);

    int8_t WhiteSpreadStarToHexagon(uint16_t wait);

    int8_t RainbowEdgeRotate(uint16_t wait);

    int8_t GreenRedSpiral(uint8_t wait, uint16_t colorSpeed, uint8_t colorLength , uint8_t sections);

    int8_t ChristmasPattern(uint8_t pattern_num);
    int8_t ChristmasPattern(uint8_t pattern_num,uint16_t wait);
 private:
    AckaLED star;
    Hexagon hexagon_strip;
    uint8_t _starType;
    uint8_t starEdgeLength=0;
    uint8_t StarInnerPoints[6];
    uint8_t StarOuterPoints[6];

    uint8_t m_channel;
    uint16_t m_channel_offset;
    uint8_t hexagonEdgeLength=0;
    uint8_t hexagonPoints[6];


    int16_t mapLEDs(uint16_t led_num);
};
#endif /*STAR_H*/