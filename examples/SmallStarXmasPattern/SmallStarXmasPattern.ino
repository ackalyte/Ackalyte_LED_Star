#include <AckaStar.h>
DMAMEM StarDisplayBuffer dmaMemory;
Star star(dmaMemory,STAR_SMALL,CHANNEL3);

void setup() {
  star.init();
}

void loop() {
  for(uint8_t index = 0; index < TOTAL_PATTERNS*PATTERN_LOOP; index++)
  {
    star.ChristmasPattern(index/PATTERN_LOOP);
  }
}
