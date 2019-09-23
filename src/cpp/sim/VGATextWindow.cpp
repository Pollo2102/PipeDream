#include <cstdio>
#include <iostream>
#include <verilated.h>
#include "VGATextWindow.h"

#ifdef USE_ACTIVE_LOW_KEYS

inline void setKey(uint8_t& keyst, uint8_t pos) {
    keyst &= ~(1u << pos);
}

inline void unsetKey(uint8_t& keyst, uint8_t pos) {
    keyst |= (1u << pos);
}

#else

inline void setKey(uint8_t& keyst, uint8_t pos) {
    keyst |= (1u << pos);
}

inline void unsetKey(uint8_t& keyst, uint8_t pos) {
    keyst &= (~(1u << pos));
}

#endif

void VGAFontSymbol::loadFromBitmap(const uint8_t *arr) {
    int point_y = 0;

    for (int i = 0; i < CHAR_HEIGHT; i++) {
        uint8_t line_data = *arr;
        uint8_t mask = 1 << ROW_MSB;

        int point_x = 0;
        for (int j = 0; j < CHAR_WIDTH; j++) {
            if ((line_data & mask) != 0) {
                points.emplace_back(point_x, point_y);
            }            
            point_x ++;
            mask >>= 1;
        }
        arr += BYTES_PER_ROW;
        point_y++;
    }    
}

void VGAFontSymbol::draw(SDL_Renderer *renderer, int x, int y, SDL_Color &fc, SDL_Color &bc) const {
    SDL_Rect r;

    r.x = x; r.y = y; r.w = CHAR_WIDTH; r.h = CHAR_HEIGHT;
    SDL_SetRenderDrawColor(renderer, bc.r, bc.g, bc.b, bc.a);
    SDL_RenderFillRect(renderer, &r);
    if (points.size() > 0) {
        std::vector<SDL_Point> spoints(points.size());

        for (int i = 0; i < points.size(); i++) {
            spoints[i].x = x + points[i].first;
            spoints[i].y = y + points[i].second;
        }
        SDL_SetRenderDrawColor(renderer, fc.r, fc.g, fc.b, fc.a);
        SDL_RenderDrawPoints(renderer, spoints.data(), points.size());
    }
}

VGATextWindow::~VGATextWindow() {
    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
    }
    if (window != nullptr) {
        SDL_DestroyWindow(window);
    }
}

void VGATextWindow::loadColorPalette(const uint8_t *vgapal) {
    for (int i = 0; i < VGA_NUM_COLORS; i++) {
        uint8_t color = vgapal[i];
        pal[i].a = 255;
        pal[i].r = color & 0xe0;
        pal[i].g = (color & 0x1c) * 8;
        pal[i].b = (color & 0x03) * 64;
    }
}

void VGATextWindow::loadVGAFont(const uint8_t *vgafont) {
    for (int i = 0; i < VGA_NUM_SYMBOLS; i++) {
        const uint8_t *symbBmp = &vgafont[i * CHAR_SIZE_BYTES];
        vgaFontSymbs.emplace_back(symbBmp); // call the VGAFontSymbol constructor
    }
}

bool VGATextWindow::initDisplay(uint32_t *vgafb, uint8_t *vgarom, uint8_t *vgapal) {

    int res = SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_SHOWN, &window, &renderer);
    if (res < 0) {
        std::cerr << "Could not create window: '" << SDL_GetError() << "\n";
        return false;        
    }
    SDL_SetWindowTitle(window, "VGA Display 80x30");

    this->vgafb = vgafb;

    loadColorPalette(vgapal);
    loadVGAFont(vgarom);

    return true;
}

SDL_Color VGATextWindow::getColorFromPalette(uint8_t index) {
    if (index >= 0 && index < PAL_COLORS) {
        return pal[index];
    } else {
        std::cerr << "Invalid color index '" << index << "'\n";
        SDL_Color color;
        color.a = 255;
        color.r = 0;
        color.g = 0;
        color.b = 0;

        return color;
      }
}

void VGATextWindow::drawVGASymbol(int row, int col, uint16_t symb) {
    int index = (uint8_t)(symb & 0xff);
    uint8_t fgi = (symb & 0x0f00) >> 8;
    uint8_t bgi = (symb & 0xf000) >> 12;

    SDL_Color fc = getColorFromPalette(fgi);
    SDL_Color bc = getColorFromPalette(bgi);
    const VGAFontSymbol& s = vgaFontSymbs[index];

    s.draw(renderer, col * CHAR_WIDTH, row * CHAR_HEIGHT, fc, bc);
}

void VGATextWindow::drawVGAContent() {
    if (vgaFontSymbs.size() == 0 || vgafb == nullptr) {
        return;
    }

    uint32_t *pvga = vgafb;
    
    for (int row = 0; row < VGA_ROWS; row++) {
        int col = 0;

        while (col < VGA_COLS) {
            drawVGASymbol(row, col, *pvga >> 16);
            col++;
            drawVGASymbol(row, col, *pvga & 0xffff);
            col++;
            pvga++;
        }
    }
}

void VGATextWindow::redraw() {
    drawVGAContent();
    SDL_RenderPresent(renderer);
}

void VGATextWindow::saveScreenshot(const char *filename) {
    SDL_Surface *pScreenShot;

    pScreenShot = SDL_CreateRGBSurface(0, width, height, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

    if(pScreenShot != nullptr) {
        SDL_RenderReadPixels(renderer, nullptr, SDL_GetWindowPixelFormat(window), pScreenShot->pixels, pScreenShot->pitch);
        SDL_SaveBMP(pScreenShot, filename);
        SDL_FreeSurface(pScreenShot);
    }
}

void VGATextWindow::run() {
    bool running = true;
    SDL_Event e;

    while (running) {
        SDL_WaitEvent(&e);

        switch (e.type) {
            case SDL_QUIT:
                Verilated::gotFinish(true);
                running = false;
                break;
            case SDL_WINDOWEVENT:
                if (e.window.event == SDL_WINDOWEVENT_EXPOSED) {
                    redraw();
                }
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT: setKey(keypadStateMap, 0); break;
                    case SDLK_RIGHT:setKey(keypadStateMap, 1); break;
                    case SDLK_DOWN: setKey(keypadStateMap, 2); break;
                    case SDLK_UP: setKey(keypadStateMap, 3); break;
                    case SDLK_p: setKey(keypadStateMap, 5); break;
                    case SDLK_q: setKey(keypadStateMap, 4); break;
                    case SDLK_r: resetKeyState = KeyState::Pressed; break;
                    case SDLK_s: stopKeyState = KeyState::Pressed; break;
                    case SDLK_b: setKey(keypadStateMap, 6); break;
                    case SDLK_SPACE:setKey(keypadStateMap, 7); break;
                }
                break;
            case SDL_KEYUP:
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT: unsetKey(keypadStateMap, 0); break;
                    case SDLK_RIGHT:unsetKey(keypadStateMap, 1); break;
                    case SDLK_DOWN: unsetKey(keypadStateMap, 2); break;
                    case SDLK_UP: unsetKey(keypadStateMap, 3); break;
                    case SDLK_p: unsetKey(keypadStateMap, 5); break;
                    case SDLK_q: unsetKey(keypadStateMap, 4); break;
                    case SDLK_r: resetKeyState = KeyState::Released; break;
                    case SDLK_s: stopKeyState = KeyState::Released; break;
                    case SDLK_b: unsetKey(keypadStateMap, 6); break;
                    case SDLK_SPACE: unsetKey(keypadStateMap, 7); break;
                }
                break;
        }
    }
}