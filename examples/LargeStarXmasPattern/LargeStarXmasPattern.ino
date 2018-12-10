#include <AckaStar.h>
DMAMEM StarDisplayBuffer dmaMemory;
LargeStar star(dmaMemory,CHANNEL1,CHANNEL2);

void setup() {
  star.init();
}

void loop() {
  for(uint8_t index = 0; index < TOTAL_PATTERNS*LARGE_STAR_PATTERN_LOOP; index++)
  {
    star.ChristmasPattern(index/LARGE_STAR_PATTERN_LOOP);
  }
}






