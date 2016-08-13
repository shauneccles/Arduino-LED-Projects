#include "Arduino.h"
#include "FastLED.h"
#include "Button.h"                      // Button library. Includes press, long press, double press detection.
#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif
void rainbow();
void rainbowWithGlitter();
void confetti();
void rainbowconfetti();
void pride();
void sinelon();
void juggle();
void ClearLEDs();
void softtwinkles();
void ColourWaveLoop();
void readbutton();
void addGlitter(fract8 chanceOfGlitter);
void Fire2012WithPalette();
void Ice2012WithPalette();
void fillnoise8();
void inoise8();
// Pushbutton pin definition
const int buttonPin = 11;                   // Digital pin used for debounced pushbutton
Button myBtn(buttonPin, true, true, 50);           // Declare the button
#define DATA_PIN  9
#define LED_TYPE  WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS  94
CRGB leds[NUM_LEDS];
#define MAX_BRIGHTNESS 255   // Thats full on, watch the power!
#define MIN_BRIGHTNESS 120    // set to a minimum of 25%
#define DENSITY   20 // For SoftTwinkles
// For ColourWave
CRGBPalette16 gPal;


extern const TProgmemRGBGradientPalettePtr gGradientPalettes[];
extern const uint8_t gGradientPaletteCount;
uint8_t gCurrentPaletteNumber = 0;
CRGBPalette16 gCurrentPalette( CRGB::Black);
CRGBPalette16 gTargetPalette( gGradientPalettes[0] );
// Gradient Color Palette definitions for 33 different cpt-city color palettes.
DEFINE_GRADIENT_PALETTE( ib_jul01_gp ) {
								0, 194, 1, 1,
								94,  1, 29, 18,
								132, 57,131, 28,
								255, 113, 1, 1
};
DEFINE_GRADIENT_PALETTE( es_vintage_57_gp ) {
								0,  2, 1, 1,
								53, 18, 1, 0,
								104, 69, 29, 1,
								153, 167,135, 10,
								255, 46, 56, 4
};
DEFINE_GRADIENT_PALETTE( es_vintage_01_gp ) {
								0,  4, 1, 1,
								51, 16, 0, 1,
								76, 97,104, 3,
								101, 255,131, 19,
								127, 67, 9, 4,
								153, 16, 0, 1,
								229,  4, 1, 1,
								255,  4, 1, 1
};
DEFINE_GRADIENT_PALETTE( es_rivendell_15_gp ) {
								0,  1, 14, 5,
								101, 16, 36, 14,
								165, 56, 68, 30,
								242, 150,156, 99,
								255, 150,156, 99
};
DEFINE_GRADIENT_PALETTE( rgi_15_gp ) {
								0,  4, 1, 31,
								31, 55, 1, 16,
								63, 197, 3, 7,
								95, 59, 2, 17,
								127,  6, 2, 34,
								159, 39, 6, 33,
								191, 112, 13, 32,
								223, 56, 9, 35,
								255, 22, 6, 38
};
DEFINE_GRADIENT_PALETTE( retro2_16_gp ) {
								0, 188,135, 1,
								255, 46, 7, 1
};
DEFINE_GRADIENT_PALETTE( Analogous_1_gp ) {
								0,  3, 0,255,
								63, 23, 0,255,
								127, 67, 0,255,
								191, 142, 0, 45,
								255, 255, 0, 0
};
DEFINE_GRADIENT_PALETTE( es_pinksplash_08_gp ) {
								0, 126, 11,255,
								127, 197, 1, 22,
								175, 210,157,172,
								221, 157, 3,112,
								255, 157, 3,112
};
DEFINE_GRADIENT_PALETTE( es_pinksplash_07_gp ) {
								0, 229, 1, 1,
								61, 242, 4, 63,
								101, 255, 12,255,
								127, 249, 81,252,
								153, 255, 11,235,
								193, 244, 5, 68,
								255, 232, 1, 5
};
DEFINE_GRADIENT_PALETTE( Coral_reef_gp ) {
								0, 40,199,197,
								50, 10,152,155,
								96,  1,111,120,
								96, 43,127,162,
								139, 10, 73,111,
								255,  1, 34, 71
};
DEFINE_GRADIENT_PALETTE( es_ocean_breeze_068_gp ) {
								0, 100,156,153,
								51,  1, 99,137,
								101,  1, 68, 84,
								104, 35,142,168,
								178,  0, 63,117,
								255,  1, 10, 10
};
DEFINE_GRADIENT_PALETTE( es_ocean_breeze_036_gp ) {
								0,  1, 6, 7,
								89,  1, 99,111,
								153, 144,209,255,
								255,  0, 73, 82
};
DEFINE_GRADIENT_PALETTE( departure_gp ) {
								0,  8, 3, 0,
								42, 23, 7, 0,
								63, 75, 38, 6,
								84, 169, 99, 38,
								106, 213,169,119,
								116, 255,255,255,
								138, 135,255,138,
								148, 22,255, 24,
								170,  0,255, 0,
								191,  0,136, 0,
								212,  0, 55, 0,
								255,  0, 55, 0
};
DEFINE_GRADIENT_PALETTE( es_landscape_64_gp ) {
								0,  0, 0, 0,
								37,  2, 25, 1,
								76, 15,115, 5,
								127, 79,213, 1,
								128, 126,211, 47,
								130, 188,209,247,
								153, 144,182,205,
								204, 59,117,250,
								255,  1, 37,192
};
DEFINE_GRADIENT_PALETTE( es_landscape_33_gp ) {
								0,  1, 5, 0,
								19, 32, 23, 1,
								38, 161, 55, 1,
								63, 229,144, 1,
								66, 39,142, 74,
								255,  1, 4, 1
};
DEFINE_GRADIENT_PALETTE( rainbowsherbet_gp ) {
								0, 255, 33, 4,
								43, 255, 68, 25,
								86, 255, 7, 25,
								127, 255, 82,103,
								170, 255,255,242,
								209, 42,255, 22,
								255, 87,255, 65
};
DEFINE_GRADIENT_PALETTE( gr65_hult_gp ) {
								0, 247,176,247,
								48, 255,136,255,
								89, 220, 29,226,
								160,  7, 82,178,
								216,  1,124,109,
								255,  1,124,109
};
DEFINE_GRADIENT_PALETTE( gr64_hult_gp ) {
								0,  1,124,109,
								66,  1, 93, 79,
								104, 52, 65, 1,
								130, 115,127, 1,
								150, 52, 65, 1,
								201,  1, 86, 72,
								239,  0, 55, 45,
								255,  0, 55, 45
};
DEFINE_GRADIENT_PALETTE( GMT_drywet_gp ) {
								0, 47, 30, 2,
								42, 213,147, 24,
								84, 103,219, 52,
								127,  3,219,207,
								170,  1, 48,214,
								212,  1, 1,111,
								255,  1, 7, 33
};
DEFINE_GRADIENT_PALETTE( ib15_gp ) {
								0, 113, 91,147,
								72, 157, 88, 78,
								89, 208, 85, 33,
								107, 255, 29, 11,
								141, 137, 31, 39,
								255, 59, 33, 89
};
DEFINE_GRADIENT_PALETTE( Fuschia_7_gp ) {
								0, 43, 3,153,
								63, 100, 4,103,
								127, 188, 5, 66,
								191, 161, 11,115,
								255, 135, 20,182
};
DEFINE_GRADIENT_PALETTE( es_emerald_dragon_08_gp ) {
								0, 97,255, 1,
								101, 47,133, 1,
								178, 13, 43, 1,
								255,  2, 10, 1
};
DEFINE_GRADIENT_PALETTE( lava_gp ) {
								0,  0, 0, 0,
								46, 18, 0, 0,
								96, 113, 0, 0,
								108, 142, 3, 1,
								119, 175, 17, 1,
								146, 213, 44, 2,
								174, 255, 82, 4,
								188, 255,115, 4,
								202, 255,156, 4,
								218, 255,203, 4,
								234, 255,255, 4,
								244, 255,255, 71,
								255, 255,255,255
};
DEFINE_GRADIENT_PALETTE( fire_gp ) {
								0,  1, 1, 0,
								76, 32, 5, 0,
								146, 192, 24, 0,
								197, 220,105, 5,
								240, 252,255, 31,
								250, 252,255,111,
								255, 255,255,255
};
DEFINE_GRADIENT_PALETTE( Colorfull_gp ) {
								0, 10, 85, 5,
								25, 29,109, 18,
								60, 59,138, 42,
								93, 83, 99, 52,
								106, 110, 66, 64,
								109, 123, 49, 65,
								113, 139, 35, 66,
								116, 192,117, 98,
								124, 255,255,137,
								168, 100,180,155,
								255, 22,121,174
};
DEFINE_GRADIENT_PALETTE( Magenta_Evening_gp ) {
								0, 71, 27, 39,
								31, 130, 11, 51,
								63, 213, 2, 64,
								70, 232, 1, 66,
								76, 252, 1, 69,
								108, 123, 2, 51,
								255, 46, 9, 35
};
DEFINE_GRADIENT_PALETTE( Pink_Purple_gp ) {
								0, 19, 2, 39,
								25, 26, 4, 45,
								51, 33, 6, 52,
								76, 68, 62,125,
								102, 118,187,240,
								109, 163,215,247,
								114, 217,244,255,
								122, 159,149,221,
								149, 113, 78,188,
								183, 128, 57,155,
								255, 146, 40,123
};
DEFINE_GRADIENT_PALETTE( Sunset_Real_gp ) {
								0, 120, 0, 0,
								22, 179, 22, 0,
								51, 255,104, 0,
								85, 167, 22, 18,
								135, 100, 0,103,
								198, 16, 0,130,
								255,  0, 0,160
};
DEFINE_GRADIENT_PALETTE( es_autumn_19_gp ) {
								0, 26, 1, 1,
								51, 67, 4, 1,
								84, 118, 14, 1,
								104, 137,152, 52,
								112, 113, 65, 1,
								122, 133,149, 59,
								124, 137,152, 52,
								135, 113, 65, 1,
								142, 139,154, 46,
								163, 113, 13, 1,
								204, 55, 3, 1,
								249, 17, 1, 1,
								255, 17, 1, 1
};
DEFINE_GRADIENT_PALETTE( BlacK_Blue_Magenta_White_gp ) {
								0,  0, 0, 0,
								42,  0, 0, 45,
								84,  0, 0,255,
								127, 42, 0,255,
								170, 255, 0,255,
								212, 255, 55,255,
								255, 255,255,255
};
DEFINE_GRADIENT_PALETTE( BlacK_Magenta_Red_gp ) {
								0,  0, 0, 0,
								63, 42, 0, 45,
								127, 255, 0,255,
								191, 255, 0, 45,
								255, 255, 0, 0
};
DEFINE_GRADIENT_PALETTE( BlacK_Red_Magenta_Yellow_gp ) {
								0,  0, 0, 0,
								42, 42, 0, 0,
								84, 255, 0, 0,
								127, 255, 0, 45,
								170, 255, 0,255,
								212, 255, 55, 45,
								255, 255,255, 0
};
DEFINE_GRADIENT_PALETTE( Blue_Cyan_Yellow_gp ) {
								0,  0, 0,255,
								63,  0, 55,255,
								127,  0,255,255,
								191, 42,255, 45,
								255, 255,255, 0
};
// Gradient palette "ib64_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ing/general2/tn/ib64.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 44 bytes of program space.

DEFINE_GRADIENT_PALETTE( ib64_gp ) {
    0,  61, 11, 45,
    0,  61, 11, 45,
    0, 121, 12, 33,
   35,  72,  9, 27,
   43,  61, 11, 45,
   58, 104,  5, 27,
  132, 117, 10, 35,
  150, 110, 13, 45,
  152, 121, 15, 46,
  173, 133, 17, 46,
  255, 107,  7, 23};
	// Gradient palette "temp_19lev_gp", originally from
	// http://soliton.vm.bytemark.co.uk/pub/cpt-city/ncl/tn/temp_19lev.png.index.html
	// converted for FastLED with gammas (2.6, 2.2, 2.5)
	// Size: 160 bytes of program space.

	DEFINE_GRADIENT_PALETTE( temp_19lev_gp ) {
	    0,   1,  2, 10,
	   12,   1,  2, 10,
	   12,   1,  6, 29,
	   25,   1,  6, 29,
	   25,   1, 21, 74,
	   38,   1, 21, 74,
	   38,   1, 42,108,
	   51,   1, 42,108,
	   51,   7, 74,137,
	   63,   7, 74,137,
	   63,  17, 91,147,
	   76,  17, 91,147,
	   76,  35,135,164,
	   89,  35,135,164,
	   89,  88,184,197,
	  102,  88,184,197,
	  102, 171,233,255,
	  114, 171,233,255,
	  114, 217,248,255,
	  127, 217,248,255,
	  127, 255,223,230,
	  140, 255,223,230,
	  140, 255,191,184,
	  153, 255,191,184,
	  153, 247,128, 92,
	  165, 247,128, 92,
	  165, 247, 74, 34,
	  178, 247, 74, 34,
	  178, 244, 36, 11,
	  191, 244, 36, 11,
	  191, 217, 10,  2,
	  204, 217, 10,  2,
	  204, 142,  1,  1,
	  216, 142,  1,  1,
	  216,  83,  1,  1,
	  229,  83,  1,  1,
	  229,  35,  1,  1,
	  242,  35,  1,  1,
	  242,  19,  0,  0,
	  255,  19,  0,  0};


// Single array of defined cpt-city color palettes.
// This will let us programmatically choose one based on
// a number, rather than having to activate each explicitly
// by name every time.
// Since it is const, this array could also be moved
// into PROGMEM to save SRAM, but for simplicity of illustration
// we'll keep it in a regular SRAM array.
//
// This list of color palettes acts as a "playlist"; you can
// add or delete, or re-arrange as you wish.
const TProgmemRGBGradientPalettePtr gGradientPalettes[] = {
								Sunset_Real_gp,
								Rainbow_gp,
								es_rivendell_15_gp,
								es_ocean_breeze_036_gp,
								rgi_15_gp,
								retro2_16_gp,
								Analogous_1_gp,
								es_pinksplash_08_gp,
								Coral_reef_gp,
								es_ocean_breeze_068_gp,
								es_pinksplash_07_gp,
								es_vintage_01_gp,
								ib64_gp,
								departure_gp,
								es_landscape_64_gp,
								es_landscape_33_gp,
								rainbowsherbet_gp,
								gr65_hult_gp,
								gr64_hult_gp,
								GMT_drywet_gp,
								ib_jul01_gp,
								es_vintage_57_gp,
								temp_19lev_gp,
								ib15_gp,
								Fuschia_7_gp,
								es_emerald_dragon_08_gp,
								lava_gp,
								fire_gp,
								Colorfull_gp,
								Magenta_Evening_gp,
								Pink_Purple_gp,
								es_autumn_19_gp,
								BlacK_Blue_Magenta_White_gp,
								BlacK_Magenta_Red_gp,
								BlacK_Red_Magenta_Yellow_gp,
								Blue_Cyan_Yellow_gp
};


// Count of how many cpt-city gradients are defined:
const uint8_t gGradientPaletteCount =
								sizeof( gGradientPalettes) / sizeof( TProgmemRGBGradientPalettePtr );
// End For ColourWave

// A0 is log
// A2 is linear
const int brightnessInPin = A0;
const int speedInPin = A2;


const CRGB lightcolor(8,7,1);

//
//
// ******** SETUP ********
//
//
void setup() {

								Serial.begin(57600);
								delay(3000); // 3 second delay for recovery
								FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
}


// List of patterns to cycle through.	Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = {sinelon,rainbow, rainbowWithGlitter, confetti,rainbowconfetti,Fire2012WithPalette,pride, juggle, ClearLEDs, softtwinkles, ClearLEDs, ColourWaveLoop, Ice2012WithPalette};

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns

void loop()
{
								// Call the current pattern function once, updating the 'leds' array
								gPatterns[gCurrentPatternNumber]();
								uint8_t mappedValue = map(analogRead(brightnessInPin), 0, 1023, 50, 255);


								// send the 'leds' array out to the actual LED strip
								FastLED.setBrightness(mappedValue);
								FastLED.show();

								readbutton();// Button press increases the ledMode up to last contiguous mode and then starts over at 0.

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

								EVERY_N_MILLISECONDS_I(RainbowDelayValue,125) {

																RainbowDelayValue.setPeriod( map(analogRead(speedInPin), 0, 1023, 50, 1));
																fill_rainbow( leds, NUM_LEDS, gHue, 7);
																gHue++;

								}
}

void rainbowWithGlitter()
{
								// built-in FastLED rainbow, plus some random sparkly glitter
								rainbow();
								addGlitter(10);
}

void addGlitter( fract8 chanceOfGlitter)
{
								if( random8() < chanceOfGlitter) {
																leds[ random16(NUM_LEDS) ] += CRGB::White;
								}
}

void confetti()
{
								// random colored speckles that blink in and fade smoothly
								EVERY_N_MILLISECONDS_I(confettiDelayValue,125) {
																confettiDelayValue.setPeriod( map(analogRead(speedInPin), 0, 1023, 50, 10));
																fadeToBlackBy( leds, NUM_LEDS, 10);
																int pos = random16(NUM_LEDS);
																leds[pos] += CHSV( gHue + random8(64), 200, 255);
																gHue++;
								}

}

void rainbowconfetti()
{
								EVERY_N_MILLISECONDS_I(rainbowconfettiDelayValue,125) {
																rainbowconfettiDelayValue.setPeriod( map(analogRead(speedInPin), 0, 1023, 50, 10));
																fadeToBlackBy( leds, NUM_LEDS, 10);
																int pos = random16(NUM_LEDS);
																leds[pos] += CHSV(random8(), 200, 255);
								}
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
								EVERY_N_MILLISECONDS_I(sinelonDelayValue,10) {
																sinelonDelayValue.setPeriod( map(analogRead(speedInPin), 0, 1023, 50, 1));
																if(sinelonDelayValue == 1) {
																	gHue = gHue + 5;

																}
																	else
																	{
																	gHue++;
								}
}
}

void juggle() {
								// four colored dots, weaving in and out of sync with each other
								int NumDots = map(analogRead(speedInPin), 0, 1023, 1, 10);
								fadeToBlackBy( leds, NUM_LEDS, 20);
								byte dothue = 0;
								for( int i = 0; i < NumDots; i++) {
																leds[beatsin16(i+7,0,NUM_LEDS)] |= CHSV(dothue, 200, 255);
																dothue += 32;
								}
								FastLED.delay(8);
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

void softtwinkles() {

								for( int stwinkleloop = 0; stwinkleloop < NUM_LEDS; stwinkleloop++) {
																if( !leds[stwinkleloop]) continue; // skip black pixels
																if( leds[stwinkleloop].r & 1) { // is red odd?
																								leds[stwinkleloop] -= lightcolor; // darken if red is odd
																} else {
																								leds[stwinkleloop] += lightcolor; // brighten if red is even
																}
								}

								// Randomly choose a pixel, and if it's black, 'bump' it up a little.
								// Since it will now have an EVEN red component, it will start getting
								// brighter over time.
								if( random8() < DENSITY) {
																int j = random16(NUM_LEDS);
																if( !leds[j] ) leds[j] = lightcolor;
								}
								FastLED.delay(8);
}

void ClearLEDs(){
								FastLED.delay(125);
								fill_solid(leds, NUM_LEDS, CRGB::Black);
								FastLED.delay(125);
								nextPattern();
}

void readbutton() {                      // Read the button and increase the mode
								myBtn.read();
								if(myBtn.wasReleased()) {
																nextPattern();
								}
}
// Start of ColourWave

void colorwaves( CRGB* ledarray, uint16_t numleds, CRGBPalette16& palette)
{
								static uint16_t sPseudotime = 0;
								static uint16_t sLastMillis = 0;
								static uint16_t sHue16 = 0;
								uint8_t brightdepth = beatsin88( 341, 96, 224);
								uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
								uint8_t msmultiplier = beatsin88(147, 23, 60);

								uint16_t hue16 = sHue16;//gHue * 256;
								uint16_t hueinc16 = beatsin88(113, 300, 1500);

								uint16_t ms = millis();
								uint16_t deltams = ms - sLastMillis;
								sLastMillis = ms;
								sPseudotime += deltams * msmultiplier;
								sHue16 += deltams * beatsin88( 400, 5,9);
								uint16_t brightnesstheta16 = sPseudotime;

								for( uint16_t i = 0; i < numleds; i++) {
																hue16 += hueinc16;
																uint8_t hue8 = hue16 / 256;
																uint16_t h16_128 = hue16 >> 7;
																if( h16_128 & 0x100) {
																								hue8 = 255 - (h16_128 >> 1);
																} else {
																								hue8 = h16_128 >> 1;
																}

																brightnesstheta16 += brightnessthetainc16;
																uint16_t b16 = sin16( brightnesstheta16 ) + 32768;

																uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
																uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
																bri8 += (255 - brightdepth);

																uint8_t index = hue8;
																//index = triwave8( index);
																index = scale8( index, 240);

																CRGB newcolor = ColorFromPalette( palette, index, bri8);

																uint16_t pixelnumber = i;
																pixelnumber = (numleds-1) - pixelnumber;

																nblend( ledarray[pixelnumber], newcolor, 128);
								}
}

void ColourWaveLoop() {

								EVERY_N_SECONDS_I(SECONDS_PER_PALETTE,10) {
								SECONDS_PER_PALETTE.setPeriod(map(analogRead(speedInPin),0,1023,30,5));
																gCurrentPaletteNumber = addmod8( gCurrentPaletteNumber, 1, gGradientPaletteCount);
																gTargetPalette = gGradientPalettes[ gCurrentPaletteNumber ];
								}

								EVERY_N_MILLISECONDS_I(ColourWaveLoopDelayValue,40) {
																ColourWaveLoopDelayValue.setPeriod( map(analogRead(speedInPin), 0, 1023, 50, 1));
																nblendPaletteTowardPalette( gCurrentPalette, gTargetPalette, 16);
								}

								colorwaves( leds, NUM_LEDS, gCurrentPalette);
								// End of ColourWaves
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
