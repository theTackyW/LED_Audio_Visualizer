#include <Adafruit_NeoPixel.h>
#define NUMPIXELS 56
#define PIN 6
#define STROBE 9
#define RESET 13
#define OUTPIN A1
#define AUDIO A0
#define Vknob A3
#define Bknob A4
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int level[7]; 

//SET GLOBAL VARIABLES
double volSen; //volume sensitivity
double brightControl; //global brightness
  
void setup() {
  // put your setup code here, to run once:
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif
  pixels.begin();
  Serial.begin(9600);
  pixels.clear();
  //mic test

  //pinMode(MIC, INPUT);
  //pinMode(4, INPUT);
    // Define our pin modes
  pinMode(STROBE, OUTPUT);
  pinMode(RESET,  OUTPUT);
  pinMode(OUTPIN,    INPUT);
 
  // Create an initial state for our pins
  digitalWrite (RESET,  LOW);
  digitalWrite (STROBE, LOW);
  delay        (1);
 
  // Reset the MSGEQ7 as per the datasheet timing diagram
  digitalWrite (RESET,  HIGH);
  delay        (1);
  digitalWrite (RESET,  LOW);
  digitalWrite (STROBE, HIGH); 
  delay        (5);


}

void loop() {
 int s = 0;
 volSen = analogRead(Vknob)/1024.0;
 brightControl = analogRead(Bknob)/1024.0;

 for (int i = 0; i < 7; i++) {
    digitalWrite       (STROBE, LOW);
    delayMicroseconds  (5);                  // Delay necessary due to timing diagram
    int x = analogRead(OUTPIN);
    level[i] = x;
    digitalWrite       (STROBE, HIGH);
    delayMicroseconds  (5);                    // Delay necessary due to timing diagram
    s = s+x; 
  }
 Serial.println("  ");
  SingleLED(level[0],0);
  SingleLED(level[1],1);
  SingleLED(level[2],2);
  SingleLED(level[3],3);
  SingleLED(level[4],4);
  SingleLED(level[5],5);
  SingleLED(level[6],6);

  //moved pixels.show() here to reduce blinking issue
  pixels.show();   // Send the updated pixel colors to the hardware.
}



void SingleLED(int v,int band){
 //v = v-90;
 //Serial.println(v);
  int t0=149*volSen;
  int t1=150*volSen;
  int t2=250*volSen;
  int t3=400*volSen;
  int t4=500*volSen;
  int t5=600*volSen;
  int t6=700*volSen;
  int t7=800*volSen;
  int t8=980*volSen;
  if (v<=t0){
    clearAll(band);
    }
  if (v>t1){
    setLEDnum(1,band,v-t1);
  }
  if (v>=t2){
    setLEDnum(2,band,v-t2);
  }
  if (v>=t3){
    setLEDnum(3,band,v-t3);
  }
  if (v>=t4){
    setLEDnum(4,band,v-t4);
  }
  if (v>=t5){
    setLEDnum(5,band,v-t5);
  }
  if (v>=t6){
    setLEDnum(6,band,v-t6);
  }
  if (v>=t7){
    setLEDnum(7,band,v-t7);
  }
  if (v>=t8){
    setLEDnum(8,band,v-t8);
  }
}

void setLEDnum(int n,int band,double bright){
 double maxBright = (255/255)*brightControl;
 bright = (bright/255)*brightControl;
 if (band%2==0){
   for(int i=band*8; i<band*8+8; i++) { // For each pixel...
        if(i<n+band*8-1){
        pixels.setPixelColor(i, pixels.Color(153*maxBright, 0*maxBright, 153*maxBright));
        }
        else if(i == n+band*8-1){
        pixels.setPixelColor(i, pixels.Color(153*bright, 0*bright, 153*bright));
        }
        else{
        pixels.setPixelColor(i, pixels.Color(0,0,0));
        }
   }
   //pixels.show();   // Send the updated pixel colors to the hardware.
  }
 else{
   for(int i=(band+1)*8-1; i>(band+1)*8-1-8; i--) { // For each pixel...
        if (i > (band+1)*8-1-n+1){
        pixels.setPixelColor(i, pixels.Color(153*maxBright, 0*maxBright, 153*maxBright));
        }
        else if (i == (band+1)*8-1-n+1){
        pixels.setPixelColor(i, pixels.Color(153*bright, 0*bright, 153*bright));
        }
        else{
        pixels.setPixelColor(i, pixels.Color(0,0,0));
        }
   }
   //pixels.show();   // Send the updated pixel colors to the hardware.
   }
}
  
void clearAll(int band){
  for(int i=band*8; i<band*8+8; i++) { // For each pixel...

      // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
      // Here we're using a moderately bright green color:
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      //delay(5); // Pause before next pass through loop
      }
      pixels.show();   // Send the updated pixel colors to the hardware.
  }
