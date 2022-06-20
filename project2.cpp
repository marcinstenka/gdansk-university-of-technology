#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#define SCREEN_WIDTH    2400
#define SCREEN_HEIGHT   3200
#define CAMERA_WIDTH    600
#define CAMERA_HEIGHT   800
#define PLAYER_SPEED 400
#define PLAYER_WIDTH 25
#define PLAYER_HEIGHT 35
#define PROJECTILE_QUANTITY 10
#define PROJECTILE_SPEED 400
#define PROJECTILE_SIZE 15
#define PROJECTILE_SPACE 50
#define GAME_TITLE "Czolgi - Marcin Stenka"

struct projectile{
        int x;
        int y;
        projectile(int argX, int argY) {
                this->x = argX;
                this->y = argY;
        }
};
// narysowanie napisu txt na powierzchni screen, zaczynając od punktu (x, y)
// charset to bitmapa 128x128 zawierająca znaki
void DrawString(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset);
// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt środka obrazka sprite na ekranie
void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y);
// rysowanie pojedynczego pixela
void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color);
// rysowanie linii o długości l w pionie (gdy dx = 0, dy = 1) 
// bądź poziomie (gdy dx = 1, dy = 0)
void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color);
// rysowanie prostokąta o długości boków l i k
void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);
void shoot(SDL_Surface* screen, projectile** projectiles, double delta);
void loadImage(SDL_Surface* screen, SDL_Texture* scrtex, SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface);
void movePlayer(double* playerX, double* playerY, double delta, SDL_Rect* camera);
void print(double worldTime, double delta, SDL_Surface* screen, SDL_Surface* charset, SDL_Surface* tank, SDL_Surface* enemyTank, SDL_Surface* bg, SDL_Rect* camera, SDL_Rect gameScreen, SDL_Texture* scrtex, SDL_Renderer* renderer, double* playerX, double* playerY, projectile** projectiles);
void initializeGame(SDL_Surface*& screen, SDL_Surface*& charset, SDL_Surface*& bg, SDL_Surface*& tank, SDL_Surface*& enemyTank, SDL_Texture*& scrtex, SDL_Window*& window, SDL_Renderer*& renderer, int rc);
void endGame(SDL_Surface* screen, SDL_Surface* charset, SDL_Surface* bg, SDL_Surface* tank, SDL_Surface* enemyTank, SDL_Texture* scrtex, SDL_Renderer* renderer, SDL_Window* window, projectile* projectiles);
int game();

// main
#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char **argv) {
        while (true) {
                if (game()) {
                        break;
                }
        }
        return 0;
        };

void DrawString(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset) {
        int px, py, c;
        SDL_Rect s, d;
        s.w = 8;
        s.h = 8;
        d.w = 8;
        d.h = 8;
        while (*text) {
                c = *text & 255;
                px = (c % 16) * 8;
                py = (c / 16) * 8;
                s.x = px;
                s.y = py;
                d.x = x;
                d.y = y;
                SDL_BlitSurface(charset, &s, screen, &d);
                x += 8;
                text++;
        };
};

void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y) {
        SDL_Rect dest;
        dest.x = x - sprite->w / 2;
        dest.y = y - sprite->h / 2;
        dest.w = sprite->w;
        dest.h = sprite->h;
        SDL_BlitSurface(sprite, NULL, screen, &dest);
};

void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color) {
        int bpp = surface->format->BytesPerPixel;
        Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
        *(Uint32*)p = color;
};

void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color) {
        for (int i = 0; i < l; i++) {
                DrawPixel(screen, x, y, color);
                x += dx;
                y += dy;
        };
};

void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor) {
        int i;
        DrawLine(screen, x, y, k, 0, 1, outlineColor);
        DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
        DrawLine(screen, x, y, l, 1, 0, outlineColor);
        DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
        for (i = y + 1; i < y + k - 1; i++)
                DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
};

void shoot(SDL_Surface* screen, projectile** projectiles, double delta) {
        for (int i = 0; i < PROJECTILE_QUANTITY; i++) {
                projectiles[i]->x = SCREEN_WIDTH / 2 + i * PROJECTILE_SPACE - PROJECTILE_SPACE * PROJECTILE_QUANTITY / 2 + PROJECTILE_SIZE;
                projectiles[i]->y += PROJECTILE_SPEED * delta;
        }
        for (int i = 0; i < PROJECTILE_QUANTITY; i++) {
                if ((projectiles[i]->y >= SCREEN_HEIGHT - PROJECTILE_SIZE) || (projectiles[i]->y <= 0) || (projectiles[i]->x >= SCREEN_WIDTH - PROJECTILE_SIZE) || (projectiles[i]->x <= 0)) {
                        projectiles[i]->y = SCREEN_HEIGHT / 5;
                }
                else {
                        DrawRectangle(screen, projectiles[i]->x, projectiles[i]->y, 15, 15, SDL_MapRGB(screen->format, 0xff, 0xff, 0x00), SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00));
                }
        }
}

void loadImage(SDL_Surface* screen, SDL_Texture* scrtex, SDL_Window* window, SDL_Renderer* renderer, SDL_Surface* surface) {
        if (surface == NULL) {
                printf("Error - image loading");
                SDL_FreeSurface(screen);
                SDL_DestroyTexture(scrtex);
                SDL_DestroyWindow(window);
                SDL_DestroyRenderer(renderer);
                SDL_Quit();
        };
}

void movePlayer(double* playerX, double* playerY, double delta, SDL_Rect* camera) {
        const Uint8* keys = SDL_GetKeyboardState(NULL);
        if (keys[SDL_SCANCODE_UP]) {
                *playerY -= PLAYER_SPEED * delta;
                if (*playerY < PLAYER_HEIGHT) {
                        *playerY = PLAYER_WIDTH;
                }
                camera->y = *playerY - CAMERA_HEIGHT / 2;
        }
        if (keys[SDL_SCANCODE_DOWN]) {
                *playerY += PLAYER_SPEED * delta;
                if (*playerY > SCREEN_HEIGHT - PLAYER_HEIGHT) {
                        *playerY = SCREEN_HEIGHT - PLAYER_HEIGHT;
                }
                camera->y = *playerY - CAMERA_HEIGHT / 2;
        }
        if (keys[SDL_SCANCODE_RIGHT]) {
                *playerX += PLAYER_SPEED * delta;
                if (*playerX > SCREEN_WIDTH - PLAYER_WIDTH) {
                        *playerX = SCREEN_WIDTH - PLAYER_WIDTH;
                }
                camera->x = *playerX - CAMERA_WIDTH / 2;
        }
        if (keys[SDL_SCANCODE_LEFT]) {
                *playerX -= PLAYER_SPEED * delta;
                if (*playerX < PLAYER_WIDTH) {
                        *playerX = PLAYER_WIDTH;
                }
                camera->x = *playerX - CAMERA_WIDTH / 2;
        }
        if (camera->x < 0) {
                camera->x = 0;
        }
        if (camera->x >= SCREEN_WIDTH - CAMERA_WIDTH) {
                camera->x = SCREEN_WIDTH - CAMERA_WIDTH;
        }
        if (camera->y < 0) {
                camera->y = 0;
        }
        if (camera->y >= SCREEN_HEIGHT - CAMERA_HEIGHT) {
                camera->y = SCREEN_HEIGHT - CAMERA_HEIGHT;
        }
}

void print(double worldTime, double delta, SDL_Surface* screen, SDL_Surface* charset, SDL_Surface* tank, SDL_Surface* enemyTank, SDL_Surface* bg, SDL_Rect* camera, SDL_Rect gameScreen, SDL_Texture* scrtex, SDL_Renderer* renderer, double* playerX, double* playerY, projectile** projectiles) {
        char text[128];
        sprintf_s(text, "Czas trwania = %.1lf s", worldTime);
        DrawString(screen, camera->x + 10, camera->y + 10, text, charset);
        SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);

        DrawSurface(screen, bg, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        DrawSurface(screen, enemyTank, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5);
        DrawSurface(screen, tank, *playerX, *playerY);

        shoot(screen, projectiles, delta);

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, scrtex, camera, &gameScreen);
        SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
        SDL_RenderPresent(renderer);
}

void initializeGame(SDL_Surface*& screen, SDL_Surface*& charset, SDL_Surface*& bg, SDL_Surface*& tank, SDL_Surface*& enemyTank, SDL_Texture*& scrtex, SDL_Window*& window, SDL_Renderer*& renderer, int rc) {
        // wczytanie obrazkow

        charset = SDL_LoadBMP("./cs8x8.bmp");
        bg = SDL_LoadBMP("./bg.bmp");
        tank = SDL_LoadBMP("./tank.bmp");
        enemyTank = SDL_LoadBMP("./enemyTank.bmp");
        loadImage(screen, scrtex, window, renderer, charset);
        loadImage(screen, scrtex, window, renderer, bg);
        loadImage(screen, scrtex, window, renderer, tank);
        loadImage(screen, scrtex, window, renderer, enemyTank);
        SDL_SetColorKey(charset, true, 0x000000);

        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
                printf("SDL_Init error: %s\n", SDL_GetError());
        }
        // tryb pełnoekranowy
        rc = SDL_CreateWindowAndRenderer(CAMERA_WIDTH, CAMERA_HEIGHT, 0, &window, &renderer);
        if (rc != 0) {
                SDL_Quit();
                printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
        };

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, CAMERA_WIDTH, CAMERA_HEIGHT);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_SetWindowTitle(window, GAME_TITLE);

        screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

        scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

        // wyłączenie widoczności kursora myszy
        SDL_ShowCursor(SDL_DISABLE);
}

void endGame(SDL_Surface* screen, SDL_Surface* charset, SDL_Surface* bg, SDL_Surface* tank, SDL_Surface* enemyTank, SDL_Texture* scrtex, SDL_Renderer* renderer, SDL_Window* window, projectile* projectiles) {
        delete projectiles;
        // zwolnienie powierzchni
        SDL_FreeSurface(charset);
        SDL_FreeSurface(screen);
        SDL_FreeSurface(bg);
        SDL_FreeSurface(tank);
        SDL_FreeSurface(enemyTank);
        SDL_DestroyTexture(scrtex);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
}

int game() {
        int t1 = SDL_GetTicks(), t2 = 0, quit = 0, frames = 0, rc = 0, vertical, horizontal;
        double delta, worldTime = 0, fpsTimer = 0, fps = 0, playerPostionX = SCREEN_WIDTH / 2, playerPostionY = SCREEN_HEIGHT / 2;
        double* playerX, * playerY;
        SDL_Event event;
        SDL_Surface* screen, * charset, * bg, * tank, * enemyTank;
        SDL_Texture* scrtex;
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Rect gameCamera = { 0, 0, CAMERA_WIDTH, CAMERA_HEIGHT };
        SDL_Rect gameScreen = { 0, 0, CAMERA_WIDTH, CAMERA_HEIGHT };
        SDL_Rect* camera = &gameCamera;

        playerX = &playerPostionX;
        playerY = &playerPostionY;
        camera->x = *playerX - CAMERA_WIDTH / 2;
        camera->y = *playerY - CAMERA_HEIGHT / 2;

        projectile* projectiles[PROJECTILE_QUANTITY];
        for (int i = 0; i < PROJECTILE_QUANTITY; i++) {
                projectiles[i] = new projectile(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5);
        }

        initializeGame(screen, charset, bg, tank, enemyTank, scrtex, window, renderer, rc);

        while (!quit) {
                t2 = SDL_GetTicks();
                delta = (t2 - t1) * 0.001;
                t1 = t2;
                worldTime += delta;
                fpsTimer += delta;
                if (fpsTimer > 0.5) {
                        fps = frames * 2;
                        frames = 0;
                        fpsTimer -= 0.5;
                };

                // rysowanie
                print(worldTime, delta, screen, charset, tank, enemyTank, bg, camera, gameScreen, scrtex, renderer, playerX, playerY, projectiles);

                // obsługa zdarzeń (o ile jakieś zaszły) 
                while (SDL_PollEvent(&event)) {
                        switch (event.type) {
                        case SDL_KEYDOWN:
                                if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
                                if (event.key.keysym.sym == SDLK_n) {
                                        endGame(screen, charset, bg, tank, enemyTank, scrtex, renderer, window, *projectiles);
                                        return 0;
                                }
                                break;
                        case SDL_KEYUP:
                                break;
                        case SDL_QUIT:
                                quit = 1;
                                break;
                        };
                };
                frames++;
                movePlayer(playerX, playerY, delta, camera);
        };
        endGame(screen, charset, bg, tank, enemyTank, scrtex, renderer, window, *projectiles);
        return 1;
}