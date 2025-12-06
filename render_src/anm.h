#ifndef ANM_H
#define ANM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// ======================================================
// Antimonic Renderer Public API
// ======================================================

// Initialize renderer window + framebuffer
// Example: ar_init(800, 600, "My Game");
__declspec(dllexport)
void ar_init(int width, int height, const char *title);

// Clear framebuffer to a solid color (0xRRGGBB)
__declspec(dllexport)
void ar_clear(uint32_t color);

// Draw a filled rectangle
__declspec(dllexport)
void ar_draw_rect(int x, int y, int w, int h, uint32_t color);

// Present framebuffer to screen
__declspec(dllexport)
void ar_present(void);

// Shutdown renderer and free memory
__declspec(dllexport)
void ar_shutdown(void);


// ======================================================
// Sprite Structure + API
// (future texture support, animation, etc.)
// ======================================================

typedef struct {
    int x, y;
    int w, h;
    uint32_t color;
} AR_Sprite;

// Draw simple sprite (rectangle until textures added)
__declspec(dllexport)
void ar_draw_sprite(const AR_Sprite *s);


// ======================================================
// Fortran Math Bindings
// ======================================================

// Linear interpolation (mix)
float ar_mix(float a, float b, float t);

// Rotate a 2D point using angle (radians)
void ar_rotate(float px, float py, float angle, float *outx, float *outy);


// ======================================================
// C++ Friendly Region
// ======================================================

#ifdef __cplusplus
} // extern "C"
#endif

#endif // ANM_H
