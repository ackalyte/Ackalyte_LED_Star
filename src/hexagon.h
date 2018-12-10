#ifndef HEXAGON_H
#define HEXAGON_H
#include <stdint.h>

enum hexagon_types{
    HEXAGON_SMALL=0,
    HEXAGON_MEDIUM,
    HEXAGON_LARGE
};

#define TOTAL_LED_SMALL_HEXAGON    27
#define TOTAL_LED_MEDIUM_HEXAGON   45

#define SMALL_HEXAGON_EDGE_LENGTH      3
#define MEDIUM_HEXAGON_EDGE_LENGTH     5

class Hexagon{
 public:
    /**
     * @brief Construct a new hexagon LED strip
     * 
     * @param hexagonType 
     */
    Hexagon(uint8_t hexagonType);

    /**
     * @brief Destroy the hexagon object
     * 
     */
    virtual ~Hexagon();

    /**
     * @brief  Return actual led number mapped to the pixel of the strip 
     * 
     * @param pixel 
     * @return uint16_t 
     */
    uint16_t Pixel(uint16_t pixel);

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
 private:
    uint8_t _hexagonType=0;
    int16_t mapLEDs(uint16_t led_num);
};
#endif/*HEXAGON_H*/