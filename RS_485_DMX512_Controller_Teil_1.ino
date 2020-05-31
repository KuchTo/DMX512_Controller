#include <DmxSimple.h>

unsigned int r, g, b;

int i;
void setup() {
  DmxSimple.usePin(3);
  DmxSimple.maxChannel(512);
  DmxSimple.write(7, 255);
  DmxSimple.write(4, 0);
  DmxSimple.write(5, 0);
  DmxSimple.write(6, 0);
}


void HSBToRGB(
    unsigned int inHue, unsigned int inSaturation, unsigned int inBrightness,
    unsigned int *oR, unsigned int *oG, unsigned int *oB )
{
    if (inSaturation == 0)
    {
        // achromatic (grey)
        *oR = *oG = *oB = inBrightness;
    }
    else
    {
        unsigned int scaledHue = (inHue * 6);
        unsigned int sector = scaledHue >> 8; // sector 0 to 5 around the color wheel
        unsigned int offsetInSector = scaledHue - (sector << 8);  // position within the sector         
        unsigned int p = (inBrightness * ( 255 - inSaturation )) >> 8;
        unsigned int q = (inBrightness * ( 255 - ((inSaturation * offsetInSector) >> 8) )) >> 8;
        unsigned int t = (inBrightness * ( 255 - ((inSaturation * ( 255 - offsetInSector )) >> 8) )) >> 8;
        switch( sector ) {
        case 0:
            *oR = inBrightness;
            *oG = t;
            *oB = p;
            break;
        case 1:
            *oR = q;
            *oG = inBrightness;
            *oB = p;
            break;
        case 2:
            *oR = p;
            *oG = inBrightness;
            *oB = t;
            break;
        case 3:
            *oR = p;
            *oG = q;
            *oB = inBrightness;
            break;
        case 4:
            *oR = t;
            *oG = p;
            *oB = inBrightness;
            break;
        default:    // case 5:
            *oR = inBrightness;
            *oG = p;
            *oB = q;
            break;
        }
    }
}

void loop() {
for (i=0; i < 180; i++) 
  {  
  HSBToRGB(i, 255, 255, &r, &g, &b); 
  DmxSimple.write(1, r); // Rot
  DmxSimple.write(2, g);  // Grün
  DmxSimple.write(3, b); // Blau 
  delay(50);
  }

i = 180;
do{  
  HSBToRGB(i, 255, 255, &r, &g, &b); 
  DmxSimple.write(1, r); // Rot
  DmxSimple.write(2, g);  // Grün
  DmxSimple.write(3, b); // Blau
  delay(50);
  i--;
} while (i > 1);

}
