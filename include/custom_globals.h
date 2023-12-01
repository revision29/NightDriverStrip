#pragma once
#define BRIGHTNESS_MIN uint8_t(0)
#if DEMO

    // This is a simple demo configuration.  To build, simply connect the data lead from a WS2812B
    // strip to pin 5 or other pin marked PIN0 below.  This does not use the OLED, LCD, or anything fancy, it simply drives the
    // LEDs with a simple rainbow effect as specified in effects.cpp for DEMO.
    //
    // Please ensure you supply sufficent power to your strip, as even the DEMO of 144 LEDs, if set
    // to white, would overload a USB port.
    #ifndef PROJECT_NAME
    #define PROJECT_NAME            "Joe Devkit"
    #endif
    #define DEFAULT_EFFECT_INTERVAL 0 //to disable the effect rotation
    //#define MATRIX_WIDTH            32
    //#define MATRIX_HEIGHT           8
    #define MATRIX_WIDTH            10
    #define MATRIX_HEIGHT           8

    #define NUM_LEDS                (MATRIX_WIDTH*MATRIX_HEIGHT)
    #define NUM_CHANNELS            1
    #define ENABLE_AUDIO            0

    //#define POWER_LIMIT_MW       12 * 10 * 1000   // 10 amp supply at 5 volts assumed
    #define POWER_LIMIT_MW       12 * 3 * 1000   // 3 amp supply at 5 volts assumed

    // Once you have a working project, selectively enable various additional features by setting
    // them to 1 in the list below.  This DEMO config assumes no audio (mic), or screen, etc.

    #ifndef ENABLE_WIFI
        #define ENABLE_WIFI             1   // Connect to WiFi
    #endif

    #define INCOMING_WIFI_ENABLED   0   // Accepting incoming color data and commands
    #define TIME_BEFORE_LOCAL       1   // How many seconds before the lamp times out and shows local content
    #define ENABLE_NTP              1   // Set the clock from the web
    #define ENABLE_OTA              0   // Accept over the air flash updates

    #if M5STICKC || M5STICKCPLUS || M5STACKCORE2
        #define LED_PIN0 32
    #elif LILYGOTDISPLAYS3
        #define LED_PIN0 21
    #else
        #define LED_PIN0 5//heltec
        //#define LED_PIN0 26//esp
    #endif
    
    // The webserver serves files that are baked into the device firmware. When running you should be able to
    // see/select the list of effects by visiting the chip's IP in a browser.  You can get the chip's IP by
    // watching the serial output or checking your router for the DHCP given to a new device; often they're
    // named "esp32-" followed by a seemingly random 6-digit hexadecimal number.

    #ifndef ENABLE_WEBSERVER
        #define ENABLE_WEBSERVER        1   // Turn on the internal webserver
    #endif

    #define ENABLE_REMOTE           1   // IR Remote 
    #define IR_REMOTE_PIN   48//heltec
    //#define IR_REMOTE_PIN   14 //esp
    

#elif CROSS

    // Wall Mounted Cross. 3 sets of 8 leds and one set of 15

    #ifndef PROJECT_NAME
    #define PROJECT_NAME            "Cross"
    #endif

    //#define NUM_RINGS               4
    //#define RING_SIZE_0             15
    //#define RING_SIZE_1             7
    //#define RING_SIZE_2             7
    //#define RING_SIZE_3             7
    //#define MATRIX_WIDTH            36
    //#define MATRIX_HEIGHT           1
    #define MATRIX_WIDTH            6
    #define MATRIX_HEIGHT           8

    #define NUM_LEDS                (MATRIX_WIDTH * MATRIX_HEIGHT)
    //#define NUM_LEDS                (RING_SIZE_0 + RING_SIZE_1 + RING_SIZE_2 + RING_SIZE_3)
    #define NUM_CHANNELS            1
    #define DEFAULT_EFFECT_INTERVAL 0 //to disable the effect rotation


    #define POWER_LIMIT_MW       5000   // 1 amp supply at 5 volts assumed

    // Once you have a working project, selectively enable various additional features by setting
    // them to 1 in the list below.  This DEMO config assumes no audio (mic), or screen, etc.


    #define ENABLE_AUDIO            0

    #define ENABLE_WIFI             1   // Connect to WiFi
    #define INCOMING_WIFI_ENABLED   1   // Accepting incoming color data and commands
    #define TIME_BEFORE_LOCAL       0   // How many seconds before the lamp times out and shows local contexnt
    #define ENABLE_NTP              1   // Set the clock from the web
    #define ENABLE_OTA              1   // Accept over the air flash updates

    #define LED_PIN0 5

    // The webserver serves files from its SPIFFS filesystem, such as index.html, and those files must be
    // uploaded to SPIFFS with the "Upload Filesystem Image" command before it can work.  When running
    // you should be able to see/select the list of effects by visiting the chip's IP in a browser.  You can
    // get the chip's IP by watching the serial output or checking your router for the DHCP given to 'LEDWifi'

    #ifndef ENABLE_WEBSERVER
        #define ENABLE_WEBSERVER        1   // Turn on the internal webserver
    #endif


    #define ENABLE_REMOTE           1   // IR Remote 
    #define IR_REMOTE_PIN   48
    
#elif WINDOW

    // Wall Mounted Cross. 3 sets of 8 leds and one set of 15

    #ifndef PROJECT_NAME
    #define PROJECT_NAME            "Window"
    #endif

    //#define NUM_RINGS               4
    //#define RING_SIZE_0             15
    //#define RING_SIZE_1             7
    //#define RING_SIZE_2             7
    //#define RING_SIZE_3             7
    #define MATRIX_WIDTH            600
    #define MATRIX_HEIGHT           1
    #define NUM_LEDS                (MATRIX_WIDTH * MATRIX_HEIGHT)
    //#define NUM_LEDS                (RING_SIZE_0 + RING_SIZE_1 + RING_SIZE_2 + RING_SIZE_3)
    #define NUM_CHANNELS            1
    #define DEFAULT_EFFECT_INTERVAL 0 //to disable the effect rotation


    #define POWER_LIMIT_MW       5 * 20 * 1000   // 20 amp supply at 5 volts

    // Once you have a working project, selectively enable various additional features by setting
    // them to 1 in the list below.  This DEMO config assumes no audio (mic), or screen, etc.


    #define ENABLE_AUDIO            0

    #define ENABLE_WIFI             1   // Connect to WiFi
    #define INCOMING_WIFI_ENABLED   1   // Accepting incoming color data and commands
    #define TIME_BEFORE_LOCAL       0   // How many seconds before the lamp times out and shows local contexnt
    #define ENABLE_NTP              1   // Set the clock from the web
    #define ENABLE_OTA              1   // Accept over the air flash updates

    #define LED_PIN0 5

    // The webserver serves files from its SPIFFS filesystem, such as index.html, and those files must be
    // uploaded to SPIFFS with the "Upload Filesystem Image" command before it can work.  When running
    // you should be able to see/select the list of effects by visiting the chip's IP in a browser.  You can
    // get the chip's IP by watching the serial output or checking your router for the DHCP given to 'LEDWifi'

    #ifndef ENABLE_WEBSERVER
        #define ENABLE_WEBSERVER        1   // Turn on the internal webserver
    #endif


    #define ENABLE_REMOTE           1   // IR Remote 
    #define IR_REMOTE_PIN   48


#elif ESPCROSS

    // Wall Mounted Cross. 3 sets of 7 leds and one set of 15
    #define ATOFFICE        1
    #ifndef PROJECT_NAME
    #define PROJECT_NAME            "ESP Cross"
    #endif

    #define NUM_RINGS               4
    #define RING_SIZE_0             15
    #define RING_SIZE_1             7
    #define RING_SIZE_2             7
    #define RING_SIZE_3             7
    #define MATRIX_WIDTH            36
    #define MATRIX_HEIGHT           1
    //#define NUM_LEDS                (RING_SIZE_0 + RING_SIZE_1 + RING_SIZE_2 + RING_SIZE_3)
    #define NUM_LEDS                (MATRIX_WIDTH * MATRIX_HEIGHT)
    #define NUM_CHANNELS            1
    #define ENABLE_AUDIO            0
    #define DEFAULT_EFFECT_INTERVAL 0 //to disable the effect rotation
    #define POWER_LIMIT_MW  (5 * 2.4 * 1000)         // 2.4 amps at 5V

    #define ENABLE_WIFI             1   // Connect to WiFi
    #define INCOMING_WIFI_ENABLED   1   // Accepting incoming color data and commands
    #define TIME_BEFORE_LOCAL       0   // How many seconds before the lamp times out and shows local contexnt
    #define ENABLE_NTP              1   // Set the clock from the web
    #define ENABLE_OTA              0   // Accept over the air flash updates
    #define LED_PIN0                14

    // The webserver serves files from its SPIFFS filesystem, such as index.html, and those files must be
    // uploaded to SPIFFS with the "Upload Filesystem Image" command before it can work.  When running
    // you should be able to see/select the list of effects by visiting the chip's IP in a browser.  You can
    // get the chip's IP by watching the serial output or checking your router for the DHCP given to 'LEDWifi'

    #ifndef ENABLE_WEBSERVER
        #define ENABLE_WEBSERVER        1   // Turn on the internal webserver
    #endif
    #define ENABLE_REMOTE           1   // IR Remote 
    #define IR_REMOTE_PIN           26


#elif ESPCONE

    // Wall Mounted Cross. 3 sets of 8 leds and one set of 15

    #ifndef PROJECT_NAME
    #define PROJECT_NAME            "ESP Cone"
    #endif

    #define MATRIX_WIDTH            100
    #define MATRIX_HEIGHT           1
    #define NUM_LEDS                (MATRIX_WIDTH * MATRIX_HEIGHT)
    #define NUM_CHANNELS            1
    #define ENABLE_AUDIO            0
    #define DEFAULT_EFFECT_INTERVAL 0 //to disable the effect rotation

    #define POWER_LIMIT_MW       5 * 10 * 1000   // 10 amp supply at 5 volts

    #define ENABLE_WIFI             0   // Connect to WiFi
    #define INCOMING_WIFI_ENABLED   0   // Accepting incoming color data and commands
    #define TIME_BEFORE_LOCAL       0   // How many seconds before the lamp times out and shows local contexnt
    #define ENABLE_NTP              1   // Set the clock from the web
    #define ENABLE_OTA              0   // Accept over the air flash updates
    #define LED_PIN0                14
    #define RING_SIZE_0 18
    #define RING_SIZE_1 30
    #define RING_SIZE_2 24
    #define RING_SIZE_3 28

    // The webserver serves files from its SPIFFS filesystem, such as index.html, and those files must be
    // uploaded to SPIFFS with the "Upload Filesystem Image" command before it can work.  When running
    // you should be able to see/select the list of effects by visiting the chip's IP in a browser.  You can
    // get the chip's IP by watching the serial output or checking your router for the DHCP given to 'LEDWifi'

    #ifndef ENABLE_WEBSERVER
        #define ENABLE_WEBSERVER        0   // Turn on the internal webserver
    #endif
    #define ENABLE_REMOTE           1   // IR Remote 
    #define IR_REMOTE_PIN           26
#endif