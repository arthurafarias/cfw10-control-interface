#ifndef CFW10_h_
#define CFW10_h_

#include <Arduino.h>

using namespace std;

typedef enum CFW10_DIRECTION_enum {
    CFW10_DIRECTION_COUNTERCLOCKWIZE = LOW,
    CFW10_DIRECTION_CLOCKWIZE = HIGH
} CFW10_DIRECTION;

typedef enum CFW10_OPMODE_enum {
    CFW10_OPMODE_REMOTE = LOW,
    CFW10_OPMODE_LOCAL = HIGH
} CFW10_OPMODE;

class CFW10
{

protected:
    uint8_t di1Pin;
    uint8_t di2Pin;
    uint8_t di3Pin;
    uint8_t di4Pin;
    uint8_t ai1Pin;
  public:

    CFW10(uint8_t di1Pin, uint8_t di2Pin, uint8_t di3Pin, uint8_t di4Pin, uint8_t ai1Pin );

    void enable();
    void disable();
    void start();
    void start(CFW10_DIRECTION dir);
    void stop();
    void setDirection(CFW10_DIRECTION dir);
    void setOpMode(CFW10_OPMODE mode);

    void setDuty( uint8_t duty );

};

#endif
