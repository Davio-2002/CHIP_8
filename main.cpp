// © Copyright Davio-2002

#include <iostream>
#include <platform.hpp>
#include <chrono>
#include <chip-8.hpp>

int main(const int argc, char **argv) {
    if (argc != 4)
    {
        std::cerr << "Usage: " << argv[0] << " <Scale> <Delay> <ROM>\n";
        std::exit(EXIT_FAILURE);
    }

    const int videoScale = std::stoi(argv[1]);
    const int cycleDelay = std::stoi(argv[2]);
    char const* romFilename = argv[3];

    const Platform platform( TITLE,
                  SCREEN_WIDTH * videoScale,
                 SCREEN_HEIGHT * videoScale,
                  SCREEN_WIDTH,
                 SCREEN_HEIGHT);

    EMULATOR::Chip8 chip8;
    chip8.load_rom(romFilename);

    int videoPitch = sizeof(chip8.get_video()[0]) * SCREEN_WIDTH;

    auto lastCycleTime = std::chrono::high_resolution_clock::now();
    bool quit = false;

    while (!quit)
    {
        quit = platform.ProcessInput(chip8.get_keyboard());

        auto currentTime = std::chrono::high_resolution_clock::now();
        const float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastCycleTime).count();

        if (dt > cycleDelay)
        {
            lastCycleTime = currentTime;

            chip8.emulate_cycle();

            platform.Update(&chip8.get_video(), videoPitch);
        }
    }

    return 0;
}