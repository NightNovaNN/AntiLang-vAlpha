#include <windows.h>
#include <stdint.h>
#include <string.h>

static HWND hwnd;
static HDC hdc;
static int W = 800, H = 600;

static BITMAPINFO bmi;
static uint32_t *fb;

// ----------------------- Window proc -----------------------
LRESULT CALLBACK wndproc(HWND w, UINT msg, WPARAM wp, LPARAM lp) {
    if (msg == WM_DESTROY) PostQuitMessage(0);
    return DefWindowProc(w, msg, wp, lp);
}

// ----------------------- Init -------------------------------
__declspec(dllexport)
void ar_init(int w, int h, const char *title) {
    W = w; H = h;

    fb = malloc(W * H * 4);

    memset(&bmi, 0, sizeof(bmi));
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = W;
    bmi.bmiHeader.biHeight = -H;    // top-left origin
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    HINSTANCE hi = GetModuleHandle(0);

    WNDCLASS wc = {0};
    wc.lpfnWndProc = wndproc;
    wc.hInstance = hi;
    wc.lpszClassName = "ARClass";
    RegisterClass(&wc);

    hwnd = CreateWindowEx(
        0, "ARClass", title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        W + 16, H + 39,
        0, 0, hi, 0
    );

    hdc = GetDC(hwnd);
    ShowWindow(hwnd, 1);
}

// ----------------------- Clear ------------------------------
__declspec(dllexport)
void ar_clear(uint32_t color) {
    for (int i = 0; i < W * H; i++)
        fb[i] = color;
}

// ----------------------- Draw Rect ---------------------------
__declspec(dllexport)
void ar_draw_rect(int x, int y, int w, int h, uint32_t color) {
    for (int yy = 0; yy < h; yy++)
        for (int xx = 0; xx < w; xx++) {
            int px = x + xx;
            int py = y + yy;
            if (px >= 0 && px < W && py >= 0 && py < H)
                fb[py * W + px] = color;
        }
}

// ----------------------- Present -----------------------------
__declspec(dllexport)
void ar_present() {
    StretchDIBits(
        hdc, 0, 0, W, H,
        0, 0, W, H,
        fb,
        &bmi,
        DIB_RGB_COLORS,
        SRCCOPY
    );

    MSG msg;
    while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}
