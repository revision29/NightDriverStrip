#pragma once
#include "effectsupport.h"

// Include the effect classes we'll need later

#include "soundanalyzer.h"
#include "effects/strip/fireeffect.h"          // fire effects
#include "effects/strip/misceffects.h"
#include "effects/strip/paletteeffect.h"       // palette effects
#include "effects/strip/doublepaletteeffect.h" // double palette effect
#include "effects/strip/meteoreffect.h"        // meteor blend effect
#include "effects/strip/stareffect.h"          // star effects
#include "effects/strip/bouncingballeffect.h"  // bouincing ball effectsenable+
#include "effects/strip/tempeffect.h"
#include "effects/strip/stareffect.h"
#include "effects/strip/laserline.h"
#include "effects/matrix/PatternClock.h"       // No matrix dependencies

#if ENABLE_AUDIO
    #include "effects/matrix/spectrumeffects.h"    // Musis spectrum effects
    #include "effects/strip/musiceffect.h"         // Music based effects
#endif

#if FAN_SIZE
    #include "effects/strip/faneffects.h" // Fan-based effects
#endif

//
// Externals
//

#if USE_HUB75
    #include "ledmatrixgfx.h"
    #include "effects/strip/misceffects.h"

    #include "effects/matrix/PatternSMStrobeDiffusion.h"
    #include "effects/matrix/PatternSM2DDPR.h"

    #include "effects/matrix/PatternSMStarDeep.h"
    #include "effects/matrix/PatternSMAmberRain.h"
    #include "effects/matrix/PatternSMBlurringColors.h"
    #include "effects/matrix/PatternSMFire2021.h"
    #include "effects/matrix/PatternSMNoise.h"
    #include "effects/matrix/PatternSMPicasso3in1.h"
    #include "effects/matrix/PatternSMSpiroPulse.h"
    #include "effects/matrix/PatternSMTwister.h"
    #include "effects/matrix/PatternSMMetaBalls.h"
    #include "effects/matrix/PatternSMHolidayLights.h"
    #include "effects/matrix/PatternSMGamma.h"
    #include "effects/matrix/PatternSMFlowFields.h"
    #include "effects/matrix/PatternSMSupernova.h"
    #include "effects/matrix/PatternSMWalkingMachine.h"
    #include "effects/matrix/PatternSMHypnosis.h"
    #include "effects/matrix/PatternSMRainbowTunnel.h"
    #include "effects/matrix/PatternSMRadialWave.h"
    #include "effects/matrix/PatternSMRadialFire.h"
    #include "effects/matrix/PatternSMSmoke.h"
    #include "effects/matrix/PatternSerendipity.h"
    #include "effects/matrix/PatternSwirl.h"
    #include "effects/matrix/PatternPulse.h"
    #include "effects/matrix/PatternWave.h"
    #include "effects/matrix/PatternMaze.h"
    #include "effects/matrix/PatternLife.h"
    #include "effects/matrix/PatternSpiro.h"
    #include "effects/matrix/PatternCube.h"
    #include "effects/matrix/PatternCircuit.h"
#if ENABLE_WIFI
    #include "effects/matrix/PatternSubscribers.h"
#endif
    #include "effects/matrix/PatternAlienText.h"
    #include "effects/matrix/PatternRadar.h"
    #include "effects/matrix/PatternPongClock.h"
    #include "effects/matrix/PatternBounce.h"
    #include "effects/matrix/PatternMandala.h"
    #include "effects/matrix/PatternSpin.h"
    #include "effects/matrix/PatternMisc.h"
    #include "effects/matrix/PatternNoiseSmearing.h"
    #include "effects/matrix/PatternQR.h"
#if ENABLE_WIFI
    #include "effects/matrix/PatternWeather.h"
#endif
#endif  // USE_HUB75

#ifdef USE_WS281X
    #include "ledstripgfx.h"
#endif

// Static initializers for effects that need them

#if USE_HUB75 && ENABLE_WIFI
    std::vector<SettingSpec, psram_allocator<SettingSpec>> PatternSubscribers::mySettingSpecs = {};
#endif

#if DEMO
    ADD_EFFECT(EFFECT_STRIP_RAINBOW_FILL, RainbowFillEffect, 15, 10);
    ADD_EFFECT(EFFECT_STRIP_RAINBOW_FILL, RainbowFillEffect, 6, 2);
    ADD_EFFECT(EFFECT_STRIP_PALETTE, PaletteEffect, MagentaColors_p, 256 / 16, .1, 0,1,0);
    ADD_EFFECT(EFFECT_STRIP_PALETTE, PaletteEffect, LavaColors_p, 256 / 16, .1, 0,1,0);
    ADD_EFFECT(EFFECT_STRIP_PALETTE, PaletteEffect, PurpleColors_p, 256 / 16, .1, 0,1,0);
    ADD_EFFECT(EFFECT_STRIP_PALETTE, PaletteEffect, PartyColors_p, 256 / 16, .1, 0,1,0);

    ADD_EFFECT(EFFECT_STRIP_PALETTE, PaletteEffect, BlueHeatColors_p, 256 / 16, .1, 0,1,0);
    ADD_EFFECT(EFFECT_STRIP_METEOR, MeteorEffect, 4, 4, 10, 2.0, 2.0);
    ADD_EFFECT(EFFECT_STRIP_COLOR_FILL, ColorFillEffect, CRGB::Magenta, 1);
    ADD_EFFECT(EFFECT_STRIP_FIRE, FireEffect, "Calm Fire", NUM_LEDS, 3, 10, 100, 3, 15, false, false); //t(const String & strName, int ledCount = NUM_LEDS, int cellsPerLED = 1, int cooling = 20, int sparking = 100, int sparks = 3, int sparkHeight = 4,  bool breversed = false, bool bmirrored = false)

# elif CROSS
    //debugI("NUmber of leds %i",NUM_LEDS);
    //ADD_EFFECT(EFFECT_STRIP_FIRE, FireEffect, "Calm Fire", NUM_LEDS, 255, 255, 50, 6, 200, false, false);
    //ADD_EFFECT(EFFECT_STRIP_PALETTE_FLAME, PaletteFlameEffect, "Pallette Fire", CRGBPalette16(CRGB::Black, CRGB::Orange, CRGB::Yellow, CRGB::White), NUM_LEDS, 4, 5, 50, 3, 15, true, false);
    ADD_EFFECT(EFFECT_STRIP_RAINBOW_FILL, RainbowFillEffect, 15, 10);
    ADD_EFFECT(EFFECT_STRIP_PALETTE, PaletteEffect, LavaColors_p, 256 / 16, .1, 0,1,0);
    ADD_EFFECT(EFFECT_STRIP_PALETTE, PaletteEffect, ForestColors_p, 256 / 16, .1, 0,1,0);
    ADD_EFFECT(EFFECT_STRIP_PALETTE, PaletteEffect, PartyColors_p, 256 / 16, .1, 0,1,0);
    ADD_EFFECT(EFFECT_STRIP_COLOR_FILL, ColorFillEffect, CRGB::Blue, 1);
    ADD_EFFECT(EFFECT_STRIP_PALETTE, PaletteEffect, BlueHeatColors_p, 256 / 16, .1, 0,1,0);
    //t(const String & strName, int ledCount = NUM_LEDS, int cellsPerLED = 1, int cooling = 20, int sparking = 100, int sparks = 3, int sparkHeight = 4,  bool breversed = false, bool bmirrored = false)
    ADD_EFFECT(EFFECT_STRIP_FIRE, FireEffect, "Calm Fire", NUM_LEDS, 3, 10, 100, 3, 15, false, false); //t(const String & strName, int ledCount = NUM_LEDS, int cellsPerLED = 1, int cooling = 20, int sparking = 100, int sparks = 3, int sparkHeight = 4,  bool breversed = false, bool bmirrored = false)
    ADD_EFFECT(EFFECT_STRIP_PALETTE, PaletteEffect, RedColors_p, 256 / 16, .1, 0,1,0);
    //ADD_EFFECT(EFFECT_STRIP_MUSICAL_PALETTE_FIRE, MusicalPaletteFire, "Musical Red Fire", HeatColors_p, NUM_LEDS, 1, 8, 50, 1, 15, true, false);
    #if ENABLE_AUDIO
    //ADD_EFFECT(EFFECT_STRIP_MUSICAL_PALETTE_FIRE, MusicalPaletteFire, "Musical Red Fire", HeatColors_p, NUM_LEDS, 1, 8, 50, 1, 15, true, false);
    //ADD_STARRY_NIGHT_EFFECT(QuietStar, "Rainbow Twinkle Stars", RainbowColors_p, STARRYNIGHT_PROBABILITY, 1, LINEARBLEND, 2.0, 0.0, STARRYNIGHT_MUSICFACTOR);       // Rainbow Twinkle
    #endif
    #define EFFECT_SET_VERSION  1.3

# elif ESPCROSS
    //ADD_EFFECT(EFFECT_STRIP_FIRE, FireEffect, "Calm Fire", NUM_LEDS, 2, 3, 150, 3, 10, false, false);
    ADD_EFFECT(EFFECT_STRIP_COLOR_FILL, ColorFillEffect, CRGB::Blue, 1);
    ADD_EFFECT(EFFECT_STRIP_RAINBOW_FILL, RainbowFillEffect, 15, 10);
    ADD_EFFECT(EFFECT_STRIP_PALETTE_FLAME, PaletteFlameEffect, "Pallette Fire", CRGBPalette16(CRGB::Black, CRGB::Orange, CRGB::Yellow, CRGB::White), NUM_LEDS, 4, 5, 50, 3, 15, true, false);
    ADD_EFFECT(EFFECT_STRIP_FIRE, FireEffect, "Calm Fire", NUM_LEDS, 4, 5, 50, 3, 15, false, false); //t(const String & strName, int ledCount = NUM_LEDS, int cellsPerLED = 1, int cooling = 20, int sparking = 100, int sparks = 3, int sparkHeight = 4,  bool breversed = false, bool bmirrored = false)
    ADD_EFFECT(EFFECT_STRIP_PALETTE, PaletteEffect, ForestColors_p, 256 / 16, .1, 0,1,0);
    ADD_EFFECT(EFFECT_STRIP_PALETTE, PaletteEffect, PartyColors_p, 256 / 16, .1, 0,1,0);
    
    ADD_EFFECT(EFFECT_STRIP_PALETTE, PaletteEffect, BlueHeatColors_p, 256 / 16, .1, 0,1,0);
    //t(const String & strName, int ledCount = NUM_LEDS, int cellsPerLED = 1, int cooling = 20, int sparking = 100, int sparks = 3, int sparkHeight = 4,  bool breversed = false, bool bmirrored = false)
    
    ADD_EFFECT(EFFECT_STRIP_PALETTE, PaletteEffect, RedColors_p, 256 / 16, .1, 0,1,0);
    ADD_EFFECT(EFFECT_STRIP_PALETTE, PaletteEffect, LavaColors_p, 256 / 16, .1, 0,1,0);
    ADD_EFFECT(EFFECT_STRIP_PALETTE, PaletteEffect, CRGBPalette16(CRGB(224, 108, 111), CRGB(224, 108, 111), CRGB(224, 108, 111), CRGB(224, 108, 111), CRGB(224, 108, 111), CRGB(45, 136, 57), CRGB(45, 136, 57), CRGB(45, 136, 57), CRGB(45, 136, 57), CRGB(45, 136, 57), CRGB(99, 92, 63), CRGB(99, 92, 63), CRGB(99, 92, 63), CRGB(99, 92, 63), CRGB(99, 92, 63), CRGB(99, 92, 63)), 256 / 32, .3, 0,4,0); // pallete, denisty, speed, ledspersecond, lightsizee, gapsize
    
    //EFFECT_STRIP_PALETTE_FLAME
    //effect = make_shared_psram<PaletteFlameEffect>("Custom Fire", CRGBPalette16(CRGB::Black, color, CRGB::Yellow, CRGB::White), NUM_LEDS, 1, 8, 50, 1, 24, true, false);
    #define EFFECT_SET_VERSION  2.1

#elif ESPCONE
    ADD_EFFECT(EFFECT_STRIP_PALETTE, PaletteEffect, CRGBPalette16(CRGB(224, 108, 111), CRGB(224, 108, 111), CRGB(224, 108, 111), CRGB(224, 108, 111), CRGB(224, 108, 111), CRGB(45, 136, 57), CRGB(45, 136, 57), CRGB(45, 136, 57), CRGB(45, 136, 57), CRGB(45, 136, 57), CRGB(99, 92, 63), CRGB(99, 92, 63), CRGB(99, 92, 63), CRGB(99, 92, 63), CRGB(99, 92, 63), CRGB(99, 92, 63)), 256 / 32, .3, 0,4,0); // pallete, denisty, speed, ledspersecond, lightsizee, gapsize
    ADD_EFFECT(EFFECT_STRIP_COLOR_CYCLE, ColorCycleEffect, BottomUp, 3);
    ADD_EFFECT(EFFECT_STRIP_PALETTE, PaletteEffect, MagentaColors_p, 256 / 16, .1, 0,1,0);
    ADD_EFFECT(EFFECT_STRIP_PALETTE, PaletteEffect, LavaColors_p, 256 / 16, .1, 0,1,0);
    ADD_EFFECT(EFFECT_STRIP_PALETTE, PaletteEffect, PartyColors_p, 256 / 16, .1, 0,1,0);
    ADD_EFFECT(EFFECT_STRIP_COLOR_FILL, ColorFillEffect, CRGB::Magenta, 1);
    ADD_EFFECT(EFFECT_STRIP_PALETTE, PaletteEffect, PurpleColors_p, 256 / 16, .1, 0,1,0);
    ADD_EFFECT(EFFECT_STRIP_RAINBOW_FILL, RainbowFillEffect, 6, 2);
    ADD_EFFECT(EFFECT_STRIP_PALETTE, PaletteEffect, BlueHeatColors_p, 256 / 16, .1, 0,1,0);
    ADD_EFFECT(EFFECT_STRIP_METEOR, MeteorEffect, 4, 4, 10, 2.0, 2.0);
    ADD_EFFECT(EFFECT_STRIP_RAINBOW_FILL, RainbowFillEffect, 15, 10);
    #define EFFECT_SET_VERSION  1.7
#elif WINDOW
    ADD_EFFECT(EFFECT_STRIP_PALETTE, PaletteEffect, CRGBPalette16(CRGB(224, 108, 111), CRGB(224, 108, 111), CRGB(224, 108, 111), CRGB(224, 108, 111), CRGB(224, 108, 111), CRGB(45, 136, 57), CRGB(45, 136, 57), CRGB(45, 136, 57), CRGB(45, 136, 57), CRGB(45, 136, 57), CRGB(99, 92, 63), CRGB(99, 92, 63), CRGB(99, 92, 63), CRGB(99, 92, 63), CRGB(99, 92, 63), CRGB(99, 92, 63)), 256 / 32, .3, 0,4,0); // pallete, denisty, speed, ledspersecond, lightsizee, gapsize
    ADD_EFFECT(EFFECT_STRIP_COLOR_CYCLE, ColorCycleEffect, BottomUp, 3);
    ADD_EFFECT(EFFECT_STRIP_PALETTE, PaletteEffect, MagentaColors_p, 256 / 16, .1, 0,1,0);
    ADD_EFFECT(EFFECT_STRIP_PALETTE, PaletteEffect, LavaColors_p, 256 / 16, .1, 0,1,0);
    ADD_EFFECT(EFFECT_STRIP_PALETTE, PaletteEffect, PartyColors_p, 256 / 16, .1, 0,1,0);
    ADD_EFFECT(EFFECT_STRIP_COLOR_FILL, ColorFillEffect, CRGB::Magenta, 1);
    ADD_EFFECT(EFFECT_STRIP_PALETTE, PaletteEffect, PurpleColors_p, 256 / 16, .1, 0,1,0);
    ADD_EFFECT(EFFECT_STRIP_RAINBOW_FILL, RainbowFillEffect, 6, 2);
    ADD_EFFECT(EFFECT_STRIP_PALETTE, PaletteEffect, BlueHeatColors_p, 256 / 16, .1, 0,1,0);
    ADD_EFFECT(EFFECT_STRIP_METEOR, MeteorEffect, 4, 4, 10, 2.0, 2.0);
    ADD_EFFECT(EFFECT_STRIP_RAINBOW_FILL, RainbowFillEffect, 15, 10);
    ADD_EFFECT(EFFECT_STRIP_PALETTE, PaletteEffect, CRGBPalette16(CRGB::Red, CRGB::Red, CRGB::Green, CRGB::Green), 256 / 32, .3, 0,4,0); // pallete, denisty, speed, ledspersecond, lightsizee, gapsize
    ADD_EFFECT(EFFECT_STRIP_FIRE, FireEffect, "Calm Fire", NUM_LEDS, 4, 5, 50, 3, 100, false, false); //t(const String & strName, int ledCount = NUM_LEDS, int cellsPerLED = 1, int cooling = 20, int sparking = 100, int sparks = 3, int sparkHeight = 4,  bool breversed = false, bool bmirrored = false)
    #define EFFECT_SET_VERSION  1.7
#endif