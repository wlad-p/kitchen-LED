#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define SOUND_VELOCITY 0.034
#define NUMPIXELS 120 

#define PIN        D7 
#define TRIGPIN  D1
#define ECHOPIN  D2

bool ledTurnedOn = false;
bool isActivated = false;

long duration;
float distanceCm;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  Serial.begin(9600); // Starts the serial communication
  pinMode(TRIGPIN, OUTPUT); // Sets the trigPin as an Output
  pinMode(ECHOPIN, INPUT); // Sets the echoPin as an Input

  pixels.begin(); 
  pixels.clear();
  pixels.show();

 
}

void loop() {

// Clears the trigPin
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(ECHOPIN, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_VELOCITY/2;
  
  // Convert to inches
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);

 

  if(distanceCm < 25 && !isActivated)
  {
    isActivated = true;
  }
  else if(distanceCm < 25 && isActivated)
  {
    if(ledTurnedOn){
      turnOffLED();
    }
    else{
      turnOnLED();
    }

    isActivated = false;
  }
  
  
  delay(500);
}
  


 void turnOnLED(){

   pixels.clear();
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels.setPixelColor(i, pixels.Color(200, 90, 16)); // beste: 50 20 4 

    pixels.show();   // Send the updated pixel colors to the hardware.

    ledTurnedOn = true;

  }
}

void turnOffLED(){

  pixels.clear();
  pixels.show();

  ledTurnedOn = false;
}
