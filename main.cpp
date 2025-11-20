#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

// @Author: Kargin Stepan
// Ported to Linux/SDL2 for Endeavour OS (Arch Linux)

// Global SDL objects
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
TTF_Font* font = nullptr;

// Initialize SDL2 and create window
bool initSDL(int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "SDL initialization failed: " << SDL_GetError() << endl;
        return false;
    }
    
    if (TTF_Init() < 0) {
        cerr << "SDL_ttf initialization failed: " << TTF_GetError() << endl;
        return false;
    }
    
    window = SDL_CreateWindow("Particle Simulation",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               width, height,
                               SDL_WINDOW_SHOWN);
    
    if (!window) {
        cerr << "Window creation failed: " << SDL_GetError() << endl;
        return false;
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        cerr << "Renderer creation failed: " << SDL_GetError() << endl;
        return false;
    }
    
    // Try to load a default font
    font = TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSans.ttf", 16);
    if (!font) {
        // Fallback fonts for Arch Linux
        font = TTF_OpenFont("/usr/share/fonts/liberation/LiberationSans-Regular.ttf", 16);
    }
    if (!font) {
        cerr << "Warning: Could not load font: " << TTF_GetError() << endl;
    }
    
    return true;
}

// Clean up SDL resources
void cleanupSDL() {
    if (font) TTF_CloseFont(font);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

// Set drawing color (replacement for txSetColour)
void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

// Clear screen (replacement for txClear)
void clearScreen() {
    setColor(0, 0, 0);
    SDL_RenderClear(renderer);
}

// Draw circle (replacement for txCircle) - Optimized with scanline algorithm
void drawCircle(int x, int y, int radius, Uint8 r, Uint8 g, Uint8 b) {
    setColor(r, g, b);
    
    // Optimized filled circle using horizontal scanlines
    int radiusSq = radius * radius;
    for (int dy = -radius; dy <= radius; dy++) {
        int dx = (int)sqrt(radiusSq - dy * dy);
        SDL_RenderDrawLine(renderer, x - dx, y + dy, x + dx, y + dy);
    }
}

// Draw line (replacement for txLine)
void drawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b) {
    setColor(r, g, b);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

// Draw rectangle (replacement for txRectangle)
void drawRectangle(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b, bool filled = false) {
    setColor(r, g, b);
    SDL_Rect rect = {x, y, w, h};
    if (filled) {
        SDL_RenderFillRect(renderer, &rect);
    } else {
        SDL_RenderDrawRect(renderer, &rect);
    }
}

// Draw text (replacement for txTextOut)
void drawText(int x, int y, const string& text, Uint8 r, Uint8 g, Uint8 b) {
    if (!font) return;
    
    SDL_Color color = {r, g, b, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (surface) {
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture) {
            SDL_Rect rect = {x, y, surface->w, surface->h};
            SDL_RenderCopy(renderer, texture, nullptr, &rect);
            SDL_DestroyTexture(texture);
        }
        SDL_FreeSurface(surface);
    }
}

// Present renderer (flip buffers)
void present() {
    SDL_RenderPresent(renderer);
}

// Check for keyboard input (replacement for _kbhit)
bool checkKeyPressed() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || 
            (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
            return true;
        }
    }
    return false;
}

// Sleep function (cross-platform replacement for Sleep)
void sleepMs(int milliseconds) {
    SDL_Delay(milliseconds);
}

void Initialization(int xk, int yk, vector<vector<int>>& p, vector<vector<int>>& pp, int situation, int procent) {
    int k;
    for (int i = 0; i <= yk + 1; i++) {
        for (int j = 0; j <= xk + 1; j++) {
            pp[i][j] = p[i][j] = 0;
        }
    }
    if (situation == 0) {
        for (int i = 1; i <= yk; i++) {
            for (int j = 1; j <= xk; j++) {
                if (1 + rand() % 100 > 100 - procent) {
                    k = rand() % 8;
                    pp[i][j] |= (1 << k);
                }
            }
        }
    }
    if (situation == 1) {
        for (int i = 50; i <= 189; i++) {
            for (int j = 161; j <= 300; j++) {
                k = rand() % 8;
                pp[i][j] |= (1 << k);
            }
        }
    }
    if (situation == 2) {
        for (int i = 0; i < 5; i++) {
            for (int j = 1; j <= 275; j++) {
                pp[i + 1][j] |= (1 << 8);
                if (j <= 175) {
                    pp[i + 50][j] |= (1 << 8);
                }
            }
        }
        for (int j = 0; j < 5; j++) {
            for (int i = 50; i <= yk; i++) pp[i][j + 171] |= (1 << 8);
            for (int i = 0; i <= yk - 70; i++) pp[i][j + 271] |= (1 << 8);
        }
        for (int i = 0; i < 5; i++) {
            for (int j = 171; j <= xk; j++) pp[yk - i][j] |= (1 << 8);
            for (int j = 271; j <= xk; j++) pp[yk - 70 - i][j] |= (1 << 8);
        }
        for (int j = 1; j <= 230; j++) {
            for (int i = 6; i < 50; i++) pp[i][j] |= (1 << 0);
        }
    }
    if (situation == 3) {
        for (int i = 0; i < 5; i++) {
            for (int j = 1; j <= xk; j++) {
                pp[34 - i][j] |= (1 << 8);
                if (j <= xk - 76) {
                    pp[116 + i][j] |= (1 << 8);
                }
            }
        }
        for (int j = 0; j < 5; j++) {
            for (int i = 35; i <= yk; i++) {
                pp[i][xk - j] |= (1 << 8);
                if (i >= 121) {
                    pp[i][xk - 76 - j] |= (1 << 8);
                }
            }
        }
        for (int i = 35; i <= 115; i++) {
            for (int j = 1; j <= 380; j++) {
                pp[i][j] |= (1 << 0);
            }
        }
    }
    if (situation == 4) {
        for (int i = 0; i < 5; i++) {
            for (int j = 1; j <= xk; j++) {
                pp[34 - i][j] |= (1 << 8);
                pp[204 + i][j] |= (1 << 8);
            }
        }
        int left = 231, right = 231;
        for (int i = 90; i <= 119; i++) {
            for (int j = left; j <= right; j++) {
                pp[i][j] |= (1 << 8);
            }
            left--;
            right++;
        }
        int q = 120;
        while (left != right) {
            for (int j = left; j <= right; j++) {
                pp[q][j] |= (1 << 8);
            }
            left++;
            right--;
            q++;
        }
        for (int j = left; j <= right; j++) {
            pp[q][j] |= (1 << 8);
        }
        for (int i = 35; i <= 203; i++) {
            for (int j = 1; j <= 150; j++) {
                pp[i][j] |= (1 << 0);
            }
        }
    }
    if (situation == 5) {
        for (int i = 0; i < 5; i++) {
            for (int j = 1; j <= xk; j++) {
                pp[34 - i][j] |= (1 << 8);
                pp[204 + i][j] |= (1 << 8);
                if (j <= xk - 116) {
                    pp[116 + i][j] |= (1 << 8);
                }
            }
        }
        for (int j = xk - 4; j <= xk; j++) {
            for (int i = 35; i <= 203; i++) {
                pp[i][j] |= (1 << 8);
            }
        }
        for (int i = 35; i <= 115; i++) {
            for (int j = 1; j <= 370; j++) {
                pp[i][j] |= (1 << 0);
            }
        }
    }
    if (situation == 6) {
        for (int i = 0; i < 5; i++) {
            for (int j = 1; j <= xk; j++) {
                pp[34 - i][j] |= (1 << 8);
                pp[204 + i][j] |= (1 << 8);
            }
        }
        for (int j = 0; j < 5; j++) {
            for (int i = 34; i <= 139; i++) {
                pp[i][154 + j] |= (1 << 8);
            }
            for (int i = 99; i <= 204; i++) {
                pp[i][308 - j] |= (1 << 8);
            }
        }
        for (int i = 35; i <= 203; i++) {
            for (int j = 1; j <= 150; j++) {
                pp[i][j] |= (1 << 0);
            }
        }
    }
    if (situation == 7) {
        for (int i = 0; i < 5; i++) {
            for (int j = 1; j <= xk - 62; j++) {
                pp[34 - i][j] |= (1 << 8);
                if (j <= xk - 70) pp[204 + i][j] |= (1 << 8);
                if (j <= xk - 110) {
                    pp[116 + i][j] |= (1 << 8);
                }
            }
        }
        for (int i = 116; i <= 120; i++) {
            for (int j = xk - 4; j <= xk; j++) pp[i][j] |= (1 << 8);
        }
        int minus = 0, cnt = 0;
        for (int i = 116; i <= 203; i++) {
            for (int j = xk - 4 - minus; j <= xk - minus; j++) pp[i][j] |= (1 << 8);
            cnt++;
            if (cnt == 5) {
                minus += 4;
                cnt = 0;
            }
        }
        minus = 0, cnt = 0;
        for (int j = xk - 4; j <= xk; j++) pp[115][j] |= (1 << 8);
        for (int i = 114; i >= 35; i--) {
            for (int j = xk - 4 - minus; j <= xk - minus; j++) pp[i][j] |= (1 << 8);
            cnt++;
            if (cnt == 5) {
                minus += 4;
                cnt = 0;
            }
        }
        for (int i = 35; i <= 115; i++) {
            for (int j = 1; j <= 370; j++) {
                pp[i][j] |= (1 << 0);
            }
        }
    }
    if (situation == 8) {
        for (int i = 0; i < 5; i++) {
            for (int j = 1; j <= xk; j++) {
                pp[34 - i][j] |= (1 << 8);
                pp[204 + i][j] |= (1 << 8);
            }
        }
        for (int i = 90; i <= 150; i++) {
            for (int j = 220; j <= 260; j++) {
                pp[i][j] |= (1 << 8);
            }
        }
        for (int i = 90; i <= 150; i++) pp[i][219] |= (1 << 8);
        for (int i = 90; i <= 150; i++) pp[i][218] |= (1 << 8);
        for (int i = 88; i <= 152; i++) pp[i][217] |= (1 << 8);
        for (int i = 88; i <= 152; i++) pp[i][216] |= (1 << 8);
        for (int i = 88; i <= 152; i++) pp[i][215] |= (1 << 8);
        for (int i = 86; i <= 154; i++) pp[i][214] |= (1 << 8);
        for (int i = 86; i <= 154; i++) pp[i][213] |= (1 << 8);
        for (int i = 86; i <= 154; i++) pp[i][212] |= (1 << 8);
        for (int i = 86; i <= 154; i++) pp[i][211] |= (1 << 8);
        for (int i = 85; i <= 155; i++) pp[i][210] |= (1 << 8);
        for (int i = 85; i <= 155; i++) pp[i][209] |= (1 << 8);
        for (int i = 85; i <= 155; i++) pp[i][208] |= (1 << 8);
        for (int i = 85; i <= 155; i++) pp[i][207] |= (1 << 8);
        for (int i = 85; i <= 155; i++) pp[i][206] |= (1 << 8);
        for (int i = 85; i <= 155; i++) pp[i][205] |= (1 << 8);
        for (int i = 85; i <= 155; i++) pp[i][204] |= (1 << 8);
        for (int i = 85; i <= 155; i++) pp[i][203] |= (1 << 8);
        for (int i = 85; i <= 155; i++) pp[i][202] |= (1 << 8);
        for (int i = 85; i <= 155; i++) pp[i][201] |= (1 << 8);
        for (int i = 86; i <= 154; i++) pp[i][200] |= (1 << 8);
        for (int i = 86; i <= 154; i++) pp[i][199] |= (1 << 8);
        for (int i = 86; i <= 154; i++) pp[i][198] |= (1 << 8);
        for (int i = 86; i <= 154; i++) pp[i][197] |= (1 << 8);
        for (int i = 88; i <= 152; i++) pp[i][196] |= (1 << 8);
        for (int i = 88; i <= 152; i++) pp[i][195] |= (1 << 8);
        for (int i = 88; i <= 152; i++) pp[i][194] |= (1 << 8);
        for (int i = 90; i <= 150; i++) pp[i][193] |= (1 << 8);
        for (int i = 90; i <= 150; i++) pp[i][192] |= (1 << 8);
        for (int i = 92; i <= 148; i++) pp[i][191] |= (1 << 8);
        for (int i = 94; i <= 146; i++) pp[i][190] |= (1 << 8);
        for (int i = 98; i <= 142; i++) pp[i][189] |= (1 << 8);
        for (int i = 102; i <= 138; i++) pp[i][188] |= (1 << 8);
        for (int i = 107; i <= 133; i++) pp[i][187] |= (1 << 8);
        for (int i = 112; i <= 128; i++) pp[i][186] |= (1 << 8);
        for (int i = 35; i <= 203; i++) {
            for (int j = 1; j <= 150; j++) {
                pp[i][j] |= (1 << 0);
            }
        }
    }
}

void Infinity(int xk, int yk, vector<vector<int>>& p, vector<vector<int>>& pp, int situation) {
    if (situation == 0) return;
    
    for (int i = 1; i <= yk; i++) {
        if (p[i][1] != 0) pp[i][xk] = p[i][1];
        if (p[i][xk] != 0) pp[i][1] = p[i][xk];
    }
    for (int j = 1; j <= xk; j++) {
        if (p[1][j] != 0) pp[yk][j] = p[1][j];
        if (p[yk][j] != 0) pp[1][j] = p[yk][j];
    }
}

void Drawing(int xsize, int ysize, int xk, int yk, int cell, float r, 
             vector<vector<int>>& p, bool lines, bool masscnt, int msum) {
    clearScreen();
    
    // Pre-calculate radius once
    int radius = static_cast<int>(r);
    
    // Draw particles - optimized to check barrier first
    for (int i = 1; i <= yk; i++) {
        for (int j = 1; j <= xk; j++) {
            int cellValue = p[i][j];
            if (cellValue == 0) continue;
            
            int x = j * cell - cell / 2;
            int y = i * cell - cell / 2;
            
            // Draw barrier particles in red (bit 8)
            if ((cellValue & (1 << 8)) != 0) {
                drawCircle(x, y, radius, 255, 0, 0);
            }
            // Draw regular particles in white (bits 0-7)
            else if (cellValue & 0xFF) {  // Check if any of the first 8 bits are set
                drawCircle(x, y, radius, 255, 255, 255);
            }
        }
    }
    
    // Draw grid lines if enabled
    if (lines) {
        setColor(100, 100, 100);
        for (int i = 0; i <= yk; i++) {
            SDL_RenderDrawLine(renderer, 0, i * cell, xsize, i * cell);
        }
        for (int j = 0; j <= xk; j++) {
            SDL_RenderDrawLine(renderer, j * cell, 0, j * cell, ysize);
        }
    }
    
    // Draw particle count if enabled
    if (masscnt) {
        string text = "Particles: " + to_string(msum);
        drawText(10, 10, text, 255, 255, 0);
    }
    
    present();
}

void Change(int xk, int yk, vector<vector<int>>& p, vector<vector<int>>& pp) {
    // Optimized: copy entire rows at once instead of individual elements
    for (int i = 1; i <= yk; i++) {
        p[i] = pp[i];  // Vector assignment is optimized by the STL
    }
}

void Stuck(int xk, int yk, vector<vector<int>>& p, vector<vector<int>>& pp) {
    for (int i = 1; i <= yk; i++) {
        for (int j = 1; j <= xk; j++) {
            if ((p[i][j] & (1 << 8)) == 0) continue;
            
            // Check all 8 directions for stuck particles
            for (int k = 0; k < 8; k++) {
                int di = (k == 1 || k == 2 || k == 3) ? -1 : (k == 5 || k == 6 || k == 7) ? 1 : 0;
                int dj = (k == 7 || k == 0 || k == 1) ? 1 : (k == 3 || k == 4 || k == 5) ? -1 : 0;
                
                int ni = i + di;
                int nj = j + dj;
                
                if (ni < 1 || ni > yk || nj < 1 || nj > xk) continue;
                
                if ((p[ni][nj] & (1 << ((k + 4) % 8))) != 0) {
                    pp[ni][nj] &= ~(1 << ((k + 4) % 8));
                    
                    // Redistribute in perpendicular directions
                    int k1 = (k + 2) % 8;
                    int k2 = (k + 6) % 8;
                    
                    if (rand() % 2 == 0) {
                        pp[ni][nj] |= (1 << k1);
                    } else {
                        pp[ni][nj] |= (1 << k2);
                    }
                }
            }
        }
    }
}

void Rotation180(int& k) {
    k = (k + 4) % 8;
}

void Rotation90(int& k) {
    k = (k + 2) % 8;
}

void Rotation270(int& k) {
    k = (k + 6) % 8;
}

void Move(int xk, int yk, vector<vector<int>>& p, vector<vector<int>>& pp) {
    vector<int> xspeed = {1, 1, 0, -1, -1, -1, 0, 1};
    vector<int> yspeed = {0, -1, -1, -1, 0, 1, 1, 1};
    
    for (int i = 1; i <= yk; i++) {
        for (int j = 1; j <= xk; j++) {
            if (p[i][j] == 0 || (p[i][j] & (1 << 8)) != 0) continue;
            
            for (int k = 0; k < 8; k++) {
                if ((p[i][j] & (1 << k)) == 0) continue;
                
                int ni = i + yspeed[k];
                int nj = j + xspeed[k];
                
                if (ni >= 1 && ni <= yk && nj >= 1 && nj <= xk) {
                    pp[ni][nj] |= (1 << k);
                    pp[i][j] &= ~(1 << k);
                }
            }
        }
    }
}

void Rebound(int xk, int yk, vector<vector<int>>& p, vector<vector<int>>& pp, bool borders, int& k) {
    if (!borders) return;
    
    // Handle rebounds from walls
    for (int i = 1; i <= yk; i++) {
        for (int j = 1; j <= xk; j++) {
            if ((p[i][j] & (1 << 8)) != 0) continue;
            
            // Check boundaries
            for (int dir = 0; dir < 8; dir++) {
                if ((p[i][j] & (1 << dir)) == 0) continue;
                
                int di = (dir == 1 || dir == 2 || dir == 3) ? -1 : (dir == 5 || dir == 6 || dir == 7) ? 1 : 0;
                int dj = (dir == 7 || dir == 0 || dir == 1) ? 1 : (dir == 3 || dir == 4 || dir == 5) ? -1 : 0;
                
                int ni = i + di;
                int nj = j + dj;
                
                // Bounce off walls
                if (ni < 1 || ni > yk || nj < 1 || nj > xk) {
                    pp[i][j] &= ~(1 << dir);
                    int newdir = dir;
                    Rotation180(newdir);
                    pp[i][j] |= (1 << newdir);
                }
                
                // Bounce off barriers
                if (ni >= 1 && ni <= yk && nj >= 1 && nj <= xk && (p[ni][nj] & (1 << 8)) != 0) {
                    pp[i][j] &= ~(1 << dir);
                    int newdir = dir;
                    Rotation180(newdir);
                    pp[i][j] |= (1 << newdir);
                }
            }
        }
    }
}

void Collision(int xk, int yk, vector<vector<int>>& p, vector<vector<int>>& pp,
               vector<int>& xspeed, vector<int>& yspeed, bool abscollision) {
    
    for (int i = 1; i <= yk; i++) {
        for (int j = 1; j <= xk; j++) {
            if (p[i][j] == 0 || (p[i][j] & (1 << 8)) != 0) continue;
            
            int count = 0;
            for (int k = 0; k < 8; k++) {
                if ((p[i][j] & (1 << k)) != 0) count++;
            }
            
            // Handle collisions
            if (count == 2) {
                int dir1 = -1, dir2 = -1;
                for (int k = 0; k < 8; k++) {
                    if ((p[i][j] & (1 << k)) != 0) {
                        if (dir1 == -1) dir1 = k;
                        else dir2 = k;
                    }
                }
                
                if (dir1 != -1 && dir2 != -1) {
                    int diff = abs(dir1 - dir2);
                    
                    // Head-on collision
                    if (diff == 4) {
                        pp[i][j] &= ~(1 << dir1);
                        pp[i][j] &= ~(1 << dir2);
                        
                        int newdir1 = dir1;
                        int newdir2 = dir2;
                        Rotation90(newdir1);
                        Rotation90(newdir2);
                        
                        pp[i][j] |= (1 << newdir1);
                        pp[i][j] |= (1 << newdir2);
                    }
                    // Other collision types can be added here
                }
            }
        }
    }
}

void MassCount(int& msum, int xk, int yk, vector<vector<int>>& p) {
    msum = 0;
    for (int i = 1; i <= yk; i++) {
        for (int j = 1; j <= xk; j++) {
            if (p[i][j] != 0 && (p[i][j] & (1 << 8)) == 0) {
                for (int k = 0; k < 8; k++) {
                    if ((p[i][j] & (1 << k)) != 0) {
                        msum++;
                        break;
                    }
                }
            }
        }
    }
}

int main() {
    srand(time(nullptr));
    
    int xsize = 1850;
    int ysize = 950;
    int cell = 4;
    int procent = 20;
    int sleeptime = 5;
    int situation = 9;
    bool lines = false;
    bool masscnt = false;
    bool abscollision = false;
    bool borders = false;
    bool infinity = true;
    bool readfile = true;
    
    // Read parameters from file
    if (readfile) {
        ifstream fin("Parameters.txt");
        if (!fin.is_open()) {
            cerr << "Warning: Could not open Parameters.txt, using defaults\n";
        } else {
            int z = 1;
            while (fin) {
                string sub;
                fin >> sub;
                if (!sub.empty() && isdigit(sub[0])) {
                    if (z == 1) procent = stoi(sub);
                    if (z == 2) sleeptime = stoi(sub);
                    if (z == 3) situation = stoi(sub);
                    if (z == 4) lines = (bool)stoi(sub);
                    if (z == 5) masscnt = (bool)stoi(sub);
                    if (z == 6) abscollision = (bool)stoi(sub);
                    if (z == 7) borders = (bool)stoi(sub);
                    if (z == 8) infinity = (bool)stoi(sub);
                    z++;
                    if (z > 8) break;
                }
            }
            fin.close();
        }
    }
    
    int xk = xsize / cell;
    int yk = ysize / cell;
    int msum = 0, k = 0;
    
    vector<vector<int>> p(yk + 2, vector<int>(xk + 2));
    vector<vector<int>> pp(yk + 2, vector<int>(xk + 2));
    vector<int> xspeed = {1, 1, 0, -1, -1, -1, 0, 1};
    vector<int> yspeed = {0, -1, -1, -1, 0, 1, 1, 1};
    float r = cell / 2.0;
    
    // Initialize SDL
    if (!initSDL(xsize, ysize)) {
        cerr << "Failed to initialize SDL\n";
        return 1;
    }
    
    cout << "Particle Simulation started\n";
    cout << "Press ESC to exit\n";
    
    Initialization(xk, yk, p, pp, situation, procent);
    Rebound(xk, yk, p, pp, borders, k);
    Change(xk, yk, p, pp);
    
    // Main loop
    bool running = true;
    while (running) {
        if (checkKeyPressed()) {
            running = false;
        }
        
        if (infinity) Infinity(xk, yk, p, pp, situation);
        MassCount(msum, xk, yk, p);
        Drawing(xsize, ysize, xk, yk, cell, r, p, lines, masscnt, msum);
        Move(xk, yk, p, pp);
        Collision(xk, yk, p, pp, xspeed, yspeed, abscollision);
        Rebound(xk, yk, p, pp, borders, k);
        if (borders) Stuck(xk, yk, p, pp);
        Change(xk, yk, p, pp);
        sleepMs(sleeptime);
    }
    
    cleanupSDL();
    return 0;
}
