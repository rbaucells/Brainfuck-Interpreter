#ifndef UNTITLED_COMMON_H
#define UNTITLED_COMMON_H

enum CellSize {
    _8bit,
    _16bit,
    _32bit,
};

enum EOFBehavior {
    Zero,
    MinusOne,
    Ignore
};

// settings
constexpr int MEMORY_SIZE = 30000;
constexpr bool wrappingMemory = true;
constexpr bool wrappingCells = true;
constexpr bool processInputNewLines = true;
constexpr bool processOutputNewLines = true;
constexpr EOFBehavior eofBehavior = Zero;
constexpr CellSize cellSize = _8bit;

// basically CellType is char8_t, char16_t or char32_t depending on cellSize
using CellType = std::conditional_t<cellSize == _8bit, char8_t, std::conditional_t<cellSize == _16bit, char16_t, char32_t>>;

CellType memory[MEMORY_SIZE] = {};
int memoryPointer = 0;

int curProgramIndex = 0;

class Display {
private:
    std::string bfProgram;
public:
    Display(const std::string& bfProgram);
    void update();
    ~Display();
};

#endif //UNTITLED_COMMON_H