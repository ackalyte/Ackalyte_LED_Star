#ifndef LARGEHEXAGON_H
#define LARGEHEXAGON_H
#include <stdint.h>
enum largeHexagon_rings{
    INNER_HEX_RING=0,
    MIDDLE_HEX_RING,
    OUTER_HEX_RING
};

enum hexa_triangle_strip_type{
    HEX_TOP_TRIANGLE=0,
    HEX_BOTTOM_TRIANGLE
};

#define TOTAL_LED_LARGE_STAR    162

#define LARGE_OUTER_HEXAGON_EDGE_LENGTH      7 
#define LARGE_MIDDLE_HEXAGON_EDGE_LENGTH     6
#define LARGE_INNER_HEXAGON_EDGE_LENGTH      5 

class LargeHexagon{
    public:

    LargeHexagon(uint16_t top_channel_offset, uint16_t bot_channel_offset);

    virtual ~LargeHexagon();

    uint16_t numPixels(uint16_t ring_type);

    uint16_t Pixel(uint8_t ring_type,uint16_t pixel);

    private:
    uint16_t m_t_channel_offset,m_b_channel_offset;
    uint8_t findTriangleStrip(uint8_t ring_type,uint16_t pixel);
    int32_t mapLEDs(uint8_t ring_type,uint16_t pixel);
};
#endif