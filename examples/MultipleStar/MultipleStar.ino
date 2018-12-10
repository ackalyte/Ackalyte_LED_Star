#include <AckaStar.h>
DMAMEM StarDisplayBuffer dmaMemory;
Star smallStar(dmaMemory,STAR_SMALL,CHANNEL3);
LargeStar largeStar(dmaMemory,CHANNEL1,CHANNEL2);

void setup() {
  smallStar.init();
  largeStar.init();
}

void loop() {
    
    for(uint8_t i = 0; i < 255; i++)
    {
        largeStar.colorStar(OUTER_RING,largeStar.color(i, 255-i, 0, 0)); 
        largeStar.colorStar(MIDDLE_RING,largeStar.color(i, 255-i, 0, 0)); 
        largeStar.colorStar(INNER_RING,largeStar.color(i, 255-i, 0, 0)); 
        smallStar.colorStar(smallStar.color(255-i, i, 0, 0)); 
        largeStar.show();
        smallStar.show();
    }
    for(uint8_t i = 0; i < 255; i++)
    {
        largeStar.colorStar(OUTER_RING,largeStar.color(255-i, i, 0, 0)); 
        largeStar.colorStar(MIDDLE_RING,largeStar.color(255-i, i, 0, 0)); 
        largeStar.colorStar(INNER_RING,largeStar.color(255-i, i, 0, 0)); 
        smallStar.colorStar(smallStar.color(i, 255-i, 0, 0)); 
        largeStar.show();
        smallStar.show();
    }
}
