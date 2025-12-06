#include "anm.h"

extern "C" {
    void ar_init(int, int, const char *);
    void ar_clear(unsigned int);
    void ar_draw_rect(int, int, int, int, unsigned int);
    void ar_present();
}

class Renderer {
public:
    Renderer(int w, int h, const char *title) {
        ar_init(w, h, title);
    }
    void clear(uint32_t c) { ar_clear(c); }
    void rect(int x, int y, int w, int h, uint32_t c) { ar_draw_rect(x,y,w,h,c); }
    void present() { ar_present(); }
};
