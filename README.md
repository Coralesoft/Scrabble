# Scrabble - C++ Console Game

A Scrabble game I wrote back in 2001 as a uni assignment using Visual Studio 2002. Recently dusted it off, got it compiling under C++17 with Code::Blocks/MinGW, and fixed a few bugs that had been lurking since the original version.

## What it does

- 2-4 player local Scrabble on a 15x15 board
- 100-tile bag with proper letter distribution
- Scoring with connected word detection
- Tile exchange, skip turns, 50-point bonus for using all 7 tiles
- Custom console library (`concol`) for coloured text and screen positioning

## Building

Needs Windows (uses Windows Console API) and a C++17 compiler. Run from **cmd.exe** — Windows Terminal has console buffer issues with the classic API.

**Code::Blocks:** Open `Scarble.cbp`, hit F9.

**Command line:**
```
g++ -Wall -std=c++17 -c Main.cpp Scrabble.cpp Board.cpp Player.cpp Rack.cpp Tile.cpp TileBag.cpp square.cpp concol.cpp
g++ -o Scarble.exe *.o
```

Make sure `letfil.bin` is in the same directory as the executable.

## What changed from the 2001 version

- Fixed an off-by-one in the bubble sort that skipped the last comparison pass
- Fixed buffer size for 7-letter words (C++17 size-safe extraction needs room for null terminator)
- Fixed scoring at board edges (row/col 0 and 14 were being skipped)
- Fixed boundary checks in tile touching detection
- Fixed tile recovery when invalid moves are entered (was losing tiles)
- Game now ends automatically when tile bag and all racks are empty
- Switched from `rand()`/`srand()` to `<random>`
- Replaced the old C arrays with `std::array` for the board
- General cleanup: `std::optional` for the tile bag grab, range-based loops where it made sense, made members private that should have been private
- Fixed all the compiler warnings (there were a lot)
- Resolved `std::byte` vs Windows `byte` namespace clash

## License

MIT License — (c) C.Brown 2001-2026
