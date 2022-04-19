# LED_Audio_Visualizer
### Light DJ project

- This personal project utilizes MSGEQ7 to divide incoming audio signal into seven frequency bands and represents them as spectrum on 7 corresponding NeoPixel Sticks
Audio signal can be recieved by either a 3.5mm headphone jack or a microphone.

## Arduino Program and Functions
### LED_Audio_Visualizer.ino

> void loop()
> 
> main function that read outputs of MSGEQ7, volume sensitivity nobe(volSen), and brightness nobe(brightControl); Update NeoPixel Sticks status.

> void SingleLED(int v, int band)
> 
> Reads the output from MSGEQ7 for one specific band. Compare value with threadholds to determine how many LEDs need to be light up for each band

> void setLEDnum(int n, int band, double bright)
> 
> function that uses .setPixelColor() function in the included <Adafruit_NeoPixel.h>. Considers brightness and color.
> calls the colorFade functions for color fade from [r1,g1,b1] to [r2,g2,b2] based on band level

> void clearAll(int band)
> 
> set all LEDs on one band to OFF

> double colorFadeR(int r1, int r2, int n)

> double colorFadeG(int g1, int g2, int n)

> double colorFadeB(int b1, int b2, int n)
