#include "frame.h"

inline void pg_lcd_fill() {
    for (int i = 0; i < 240*240; i++) {
        *(char *)(0x20000000 + i) = 0x05;
    }
}

int main () {
    int frame_cnt = 0;
    int i = 0;
    for (;;) {
        char color = 0x05;
        for (char y = 0; y < 240; y++) {
            for (char x = 0; x < 240; x++) {
                if (x == frame[i] && y == frame[i+1]) {
                    color = frame[i+2];
                    i+=3;
                }
                *(char *)(0x20000000 + y * 256 + x) = color;
            }
        }
        for (int i = 0; i < 2000000; i++) { 
            asm volatile ("nop");
        }
        if (frame_cnt++ == 15) {
            frame_cnt = 0;
            i = 0;
        }
    }
    return 0;
}
