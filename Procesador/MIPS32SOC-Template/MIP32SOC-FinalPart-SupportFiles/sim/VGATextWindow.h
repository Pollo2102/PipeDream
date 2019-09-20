#ifndef _VGA_DISPLAY_H

#define _VGA_DISPLAY_H

#include <cstdint>
#include <vector>
#include <SDL.h>

#define PAL_COLORS      16
#define CHAR_WIDTH      8
#define CHAR_HEIGHT     16
#define CHAR_SIZE_BYTES ((BYTES_PER_ROW) * (CHAR_HEIGHT))
#define BYTES_PER_ROW   ((CHAR_WIDTH + 7) / 8)
#define ROW_MSB         7
#define VGA_COLS        80
#define VGA_ROWS        30
#define VGA_NUM_COLORS  16
#define VGA_NUM_SYMBOLS 256

enum class KeyState {
    Pressed,
    Released
};

class VGAFontSymbol {
public:
    using Point = std::pair<int, int>;
    
    VGAFontSymbol() {}
    VGAFontSymbol(const uint8_t *arr) { loadFromBitmap(arr); }

    void loadFromBitmap(const uint8_t *arr);
    void draw(SDL_Renderer *r, int x, int y, SDL_Color &fc, SDL_Color &bc) const;
    size_t getNumOfPoints() const { return points.size(); }

private:
    std::vector<Point> points;
};

struct Point: public SDL_Point {
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

using SymbPixels = std::vector<Point>;

class VGATextWindow {
public:
    VGATextWindow(int width, int height):
        width(width),
        height(height),
        window(nullptr),
        renderer(nullptr),
        vgafb(nullptr),
        keypadStateMap(0),
        resetKeyState(KeyState::Released),
        stopKeyState(KeyState::Released) {}

    ~VGATextWindow();

    bool initDisplay(uint32_t *vgafb, uint8_t *vgarom, uint8_t *vgapal);
    void saveScreenshot(const char *filename);
    void redraw();
    void run();
    int getWidth() { return width; }
    int getHeight() { return height; }
    uint32_t *getVgaFb() { return vgafb; }
    uint8_t getKeypadState() { return keypadStateMap; }
    bool stopKeyPressed() { return (stopKeyState == KeyState::Pressed); }
    bool resetKeyPressed() { return (resetKeyState == KeyState::Pressed); }

private:
    void loadColorPalette(const uint8_t *vgapal);
    void loadVGAFont(const uint8_t *vgafont);
    void drawVGAContent();
    void drawVGASymbol(int row, int col, uint16_t symb);
    SDL_Color getColorFromPalette(uint8_t index);

private:
    SDL_Window *window;
    SDL_Surface *surface;
    SDL_Renderer *renderer;
    SDL_Color pal[PAL_COLORS]; // Palette
    std::vector<VGAFontSymbol> vgaFontSymbs;
    uint8_t keypadStateMap;
    KeyState resetKeyState;
    KeyState stopKeyState;
    uint32_t *vgafb;
    int width, height;      // Screen resolution
};

#endif
