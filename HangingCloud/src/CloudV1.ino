#include "FastLED.h"

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few
// of the kinds of animation patterns you can quickly and easily
// compose using FastLED.
//
// This example also shows one easy way to define multiple
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014
void rainbow();
void rainbowWithGlitter();
void confetti();
void sinelon();
void juggle();
void bpm();
void nextPattern();
void addGlitter(fract8 chanceOfGlitter);
void thunderburst();
void rolling();
void crack();
void acid_cloud();
void reset();
void fillnoise8();
void Fire2012WithPalette();
void Ice2012WithPalette();
void inoise8_pallet();
void pride();

#define DATA_PIN    9
//#define CLK_PIN   4
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS    288
CRGB leds[NUM_LEDS];
CRGBPalette16 gPal;
#define BRIGHTNESS          255
#define FRAMES_PER_SECOND  30

void setup() {
  delay(3000); // 3 second delay for recovery

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = {rainbow,Ice2012WithPalette,rolling, confetti, sinelon, pride, thunderburst, acid_cloud,  Fire2012WithPalette,inoise8_pallet };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

void loop()
{
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND);

  // do some periodic updates
  EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
//   EVERY_N_SECONDS_I(RotatePatterTime, 10 ){
//     RotatePatterTime.setPeriod(random(15,45));
//     nextPattern();  // change patterns periodically
// }
EVERY_N_SECONDS(30){
  nextPattern();
}

}
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void rainbow()
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}
void pride()
{
								static uint16_t sPseudotime = 0;
								static uint16_t sLastMillis = 0;
								static uint16_t sHue16 = 0;

								uint8_t sat8 = beatsin88( 87, 220, 250);
								uint8_t brightdepth = beatsin88( 341, 96, 224);
								uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
								uint8_t msmultiplier = beatsin88(147, 23, 60);

								uint16_t hue16 = sHue16;//gHue * 256;
								uint16_t hueinc16 = beatsin88(113, 1, 3000);

								uint16_t ms = millis();
								uint16_t deltams = ms - sLastMillis;
								sLastMillis = ms;
								sPseudotime += deltams * msmultiplier;
								sHue16 += deltams * beatsin88( 400, 5,9);
								uint16_t brightnesstheta16 = sPseudotime;

								for( uint16_t i = 0; i < NUM_LEDS; i++) {
																hue16 += hueinc16;
																uint8_t hue8 = hue16 / 256;

																brightnesstheta16 += brightnessthetainc16;
																uint16_t b16 = sin16( brightnesstheta16 ) + 32768;

																uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
																uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
																bri8 += (255 - brightdepth);

																CRGB newcolor = CHSV( hue8, sat8, bri8);

																uint16_t pixelnumber = i;
																pixelnumber = (NUM_LEDS-1) - pixelnumber;

																nblend( leds[pixelnumber], newcolor, 64);
								}
}
void confetti()
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
								// a colored dot sweeping
								// back and forth, with
								// fading trails

								fadeToBlackBy( leds, NUM_LEDS, 20);
								int pos = beatsin16(13,0,NUM_LEDS);
								static int prevpos = 0;
								if( pos < prevpos ) {
																fill_solid( leds+pos, (prevpos-pos)+1, CHSV(gHue,255,255));
								} else {
																fill_solid( leds+prevpos, (pos-prevpos)+1, CHSV( gHue,255,255));
								}
								prevpos = pos;
																								gHue++;
								}


void acid_cloud(){
        // a modification of the rolling lightning which adds random colour. trippy.
        //iterate through every LED
        for(int i=0; i<NUM_LEDS; i++) {
                if(random(0,100)>95) {
                        leds[i] = CHSV(random8(), 255, 255);

                }
                else{
                        leds[i] = CHSV(0,0,0);
                }
        }
        FastLED.delay(random(150,1000));
        reset();

        //}
}

void rolling(){
        // a simple method where we go through every LED with 1/10 chance
        // of being turned on, up to 10 times, with a random delay wbetween each time
        for(int r=0; r<random(2,10); r++) {
                //iterate through every LED
                for(int i=0; i<NUM_LEDS; i++) {
                        if(random(0,100)>90) {
                                leds[i] = CHSV( 0, 0, 255);

                        }
                        else{
                                //dont need reset as we're blacking out other LEDs her
                                leds[i] = CHSV(0,0,0);
                        }
                }
                FastLED.show();
                FastLED.delay(random(150,500));
                reset();

        }
}

void crack(){
        //turn everything white briefly
        fill_solid(leds, NUM_LEDS, CRGB::White);
        FastLED.delay(random(1,5));
        reset();
        FastLED.delay(random(250,1000));
}

void reset(){
        fadeToBlackBy( leds, NUM_LEDS, 10);
}
void thunderburst(){

        // this thunder works by lighting two random lengths
        // of the strand from 10-20 pixels.
        int rs1 = random(0,NUM_LEDS/2);
        int rl1 = random(10,20);
        int rs2 = random(rs1+rl1,NUM_LEDS);
        int rl2 = random(10,20);

        //repeat this chosen strands a few times, adds a bit of realism
        for(int r = 0; r<random(3,6); r++) {

                for(int i=0; i< rl1; i++) {
                        leds[i+rs1] = CHSV( 0, 0, 255);
                }

                if(rs2+rl2 < NUM_LEDS) {
                        for(int i=0; i< rl2; i++) {
                                leds[i+rs2] = CHSV( 0, 0, 255);
                        }
                }

                //stay illuminated for a set time
                FastLED.delay(random(10,50));

                reset();
                FastLED.delay(random(100,500));
        }

}
void Fire2012WithPalette()
{
// Array of temperature readings at each simulation cell
        uint8_t COOLING = 55;
        uint8_t SPARKING = 120;
        static byte heat[NUM_LEDS];
				gPal = HeatColors_p;
        random16_add_entropy( random());
        // Step 1.  Cool down every cell a little
        for( int i = 0; i < NUM_LEDS; i++) {
                heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
        }

        // Step 2.  Heat from each cell drifts 'up' and diffuses a little
        for( int k= NUM_LEDS - 1; k >= 2; k--) {
                heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
        }

        // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
        if( random8() < SPARKING ) {
                int y = random8(7);
                heat[y] = qadd8( heat[y], random8(160,255) );
        }

        // Step 4.  Map from heat cells to LED colors
        for( int j = 0; j < NUM_LEDS; j++) {
                // Scale the heat value from 0-255 down to 0-240
                // for best results with color palettes.
                byte colorindex = scale8( heat[j], 240);
                leds[j] = ColorFromPalette( gPal, colorindex);
        }
				FastLED.delay(17);
}
void Ice2012WithPalette()
{
// Array of temperature readings at each simulation cell
        uint8_t COOLING = 55;
        uint8_t SPARKING = 120;

        static byte heat[NUM_LEDS];
				gPal = gPal = CRGBPalette16( CRGB::Black, CRGB::Blue, CRGB::Aqua,  CRGB::White);
        random16_add_entropy( random());
        // Step 1.  Cool down every cell a little
        for( int i = 0; i < NUM_LEDS; i++) {
                heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
        }

        // Step 2.  Heat from each cell drifts 'up' and diffuses a little
        for( int k= NUM_LEDS - 1; k >= 2; k--) {
                heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
        }

        // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
        if( random8() < SPARKING ) {
                int y = random8(7);
                heat[y] = qadd8( heat[y], random8(160,255) );
        }

        // Step 4.  Map from heat cells to LED colors
        for( int j = 0; j < NUM_LEDS; j++) {
                // Scale the heat value from 0-255 down to 0-240
                // for best results with color palettes.
                byte colorindex = scale8( heat[j], 240);
                leds[j] = ColorFromPalette( gPal, colorindex);
        }
				FastLED.delay(17);
}

CRGBPalette16 inoise8currentPalette(CRGB::Black);
CRGBPalette16 inoise8targetPalette(OceanColors_p);
void inoise8_pallet()
{
	uint8_t maxChanges = 48;


	EVERY_N_MILLISECONDS(10) {
	 nblendPaletteTowardPalette(inoise8currentPalette, inoise8targetPalette, maxChanges);  // Blend towards the target palette
	 fillnoise8();                                                           // Update the LED array with noise at the new location
 }

 EVERY_N_SECONDS(5) {             // Change the target palette to a random one every 5 seconds.
	 inoise8targetPalette = CRGBPalette16(CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 255, random8(128,255)), CHSV(random8(), 192, random8(128,255)), CHSV(random8(), 255, random8(128,255)));
}
}

void fillnoise8()
 {
	 uint16_t dist = random16(12345);
	 uint16_t scale = 30;
  for(int i = 0; i < NUM_LEDS; i++) {                                      // Just ONE loop to fill up the LED array as all of the pixels change.
    uint8_t index = inoise8(i*scale, dist+i*scale) % 255;                  // Get a value from the noise function. I'm using both x and y axis.
    leds[i] = ColorFromPalette(inoise8currentPalette, index, 255, LINEARBLEND);   // With that value, look up the 8 bit colour palette value and assign it to the current LED.
  }
  dist += beatsin8(10,1, 4);                                               // Moving along the distance (that random number we started out with). Vary it a bit with a sine wave.
                                                                           // In some sketches, I've used millis() instead of an incremented counter. Works a treat.
} // fillnoise8()
