#ifndef KEYPAD_h_
#define KEYPAD_h_

#include <stdint.h>

class Keypad
{
private:
protected:

    uint8_t col_curr;
    uint8_t row_curr;

    uint8_t col_pressed;
    uint8_t row_pressed;

    uint8_t col[4];
    uint8_t row[4];

    void (*callback) ( uint8_t col, uint8_t row );

public:
    Keypad( uint8_t col1, uint8_t col2, uint8_t col3, uint8_t col4, uint8_t row1, uint8_t row2, uint8_t row3, uint8_t row4 );
    //Keypad( uint8_t * cols, uint8_t rows );
    static char decode (uint8_t col, uint8_t row );
    void itkernel ( void );
    void attachCallback ( void (* callback) ( uint8_t col, uint8_t row ) );
    void detachCallback ( void );
};

#endif
