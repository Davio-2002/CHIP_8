// © Copyright Davio-2002

#pragma once

#include <SDL2/SDL.h>
#include <array>
#include <unordered_map>
#include <memory>
#include <stdexcept>
#include <type_aliases.hpp>

class Platform {
public:
    explicit Platform( ConstPtr<char> title,
                      const int windowWidth,
                      const int windowHeight,
                      const int textureWidth,
                      const int textureHeight)
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            throw std::runtime_error(SDL_GetError());
        }

        window.reset(SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                      windowWidth, windowHeight, SDL_WINDOW_SHOWN));
        if (!window) {
            throw std::runtime_error(SDL_GetError());
        }

        renderer.reset(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED));
        if (!renderer) {
            throw std::runtime_error(SDL_GetError());
        }

        texture.reset(SDL_CreateTexture(renderer.get(), SDL_PIXELFORMAT_RGBA8888,
                                        SDL_TEXTUREACCESS_STREAMING, textureWidth, textureHeight));
        if (!texture) {
            throw std::runtime_error(SDL_GetError());
        }
    }

    void Update(const void* buffer, int pitch) const {
        SDL_UpdateTexture(texture.get(), nullptr, buffer, pitch);
        SDL_RenderClear(renderer.get());
        SDL_RenderCopy(renderer.get(), texture.get(), nullptr, nullptr);
        SDL_RenderPresent(renderer.get());
    }

    [[nodiscard]]
    static bool ProcessInput(std::array<uint8_t, 16>& keys) {
        static const std::unordered_map<SDL_Keycode, int> keyMap{
            {SDLK_x, 0}, {SDLK_1, 1}, {SDLK_2, 2}, {SDLK_3, 3},
            {SDLK_q, 4}, {SDLK_w, 5}, {SDLK_e, 6}, {SDLK_a, 7},
            {SDLK_s, 8}, {SDLK_d, 9}, {SDLK_z, 0xA}, {SDLK_c, 0xB},
            {SDLK_4, 0xC}, {SDLK_r, 0xD}, {SDLK_f, 0xE}, {SDLK_v, 0xF}
        };

        bool quit = false;
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;

                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        quit = true;
                    else if (auto it = keyMap.find(event.key.keysym.sym); it != keyMap.end())
                        keys[it->second] = 1;
                    break;

                case SDL_KEYUP:
                    if (auto it = keyMap.find(event.key.keysym.sym); it != keyMap.end())
                        keys[it->second] = 0;
                    break;
                default: /* cappucina ballerina */;
            }
        }
        return quit;
    }

private:
    struct SDLWindowDeleter { void operator()(SDL_Window* w) const { SDL_DestroyWindow(w); } };
    struct SDLRendererDeleter { void operator()(SDL_Renderer* r) const { SDL_DestroyRenderer(r); } };
    struct SDLTextureDeleter { void operator()(SDL_Texture* t) const { SDL_DestroyTexture(t); } };

    std::unique_ptr<SDL_Window, SDLWindowDeleter> window{};
    std::unique_ptr<SDL_Renderer, SDLRendererDeleter> renderer{};
    std::unique_ptr<SDL_Texture, SDLTextureDeleter> texture{};
};
