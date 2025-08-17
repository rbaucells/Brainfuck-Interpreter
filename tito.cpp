#include <fstream>
#include <iostream>
#include <sstream>

using String = std::string;

// < and > to move memoryPointer
// + and - to modify memory.at(memoryPointer);
// . to print ASCI representation of memory.at(memoryPointer)
// , to write input's ASCI representation into memory.at(memoryPointer)
// [] to do while loop. when ], go back to [ if memory.at(memoryPointer) != 0

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
constexpr CellSize cellSize = _8bit;
constexpr bool wrappingMemory = true;
constexpr bool wrappingCells = true;
constexpr bool processInputNewLines = true;
constexpr bool processOutputNewLines = true;
constexpr EOFBehavior eofBehavior = Zero;

// basically CellType is char8_t, char16_t or char32_t depending on cellSize
using CellType = std::conditional_t<cellSize == _8bit, char8_t, std::conditional_t<cellSize == _16bit, char16_t, char32_t>>;

CellType memory[MEMORY_SIZE] = {};
int memoryPointer = 0;

// for predefined input with !
std::stringstream inputStream {};

CellType& getCurrentMemory() {
    return memory[memoryPointer];
}

void incrementPointer() {
    if (wrappingMemory) {
        // if the pointer reaches the end of memory, wrap back to zero, else increment normally
        if (memoryPointer == MEMORY_SIZE - 1)
            memoryPointer = 0;
        else
            memoryPointer++;
    }
    else {
        // if the pointer isn't at the end of memory, increment normally, else don't increment
        if (memoryPointer < MEMORY_SIZE - 1)
            memoryPointer++;
    }
}

void decrementPointer() {
    if (wrappingMemory) {
        // if the pointer reaches the start of memory, wrap back to the end, else decrement normally
        if (memoryPointer == 0)
            memoryPointer = MEMORY_SIZE - 1;
        else
            memoryPointer--;
    }
    else {
        // if the pointer isn't at the start of memory, decrement normally, else don't decrement
        if (memoryPointer > 0)
            memoryPointer--;
    }
}

void incrementCurrentMemory() {
    if (wrappingCells) {
        // if the cell reaches the max value, wrap back to zero, else increment normally
        if (getCurrentMemory() == std::numeric_limits<CellType>::max())
            getCurrentMemory() = 0;
        else
            getCurrentMemory()++;
    }
    else {
        // if the cell isn't at the max value, increment normally, else don't increment
        if (getCurrentMemory() < std::numeric_limits<CellType>::max())
            getCurrentMemory()++;
    }
}

void decrementCurrentMemory() {
    if (wrappingCells) {
        // if the cell reaches zero, wrap back to max value, else decrement normally
        if (getCurrentMemory() == 0)
            getCurrentMemory() = std::numeric_limits<CellType>::max();
        else
            getCurrentMemory()--;
    }
    else {
        // if the cell isn't at zero, decrement normally, else don't decrement
        if (getCurrentMemory() > 0)
            getCurrentMemory()--;
    }
}

bool isCharAcceptable(const char character) {
    // only accept characters that are part of BrainFuck
    return character == '>' || character == '<' || character == '+' || character == '-' || character == '[' || character == ']' || character == '.' || character == ',' || character == '#' || character == '!';
}

String getFileString() {
    std::printf("Path to file: ");
    String filePath;
    getline(std::cin, filePath);

    // open input file stream
    std::ifstream fileInputStream(filePath, std::fstream::in);
    String fileString;
    bool isRestOfFileInput = false;

    // read char by char and put them in fileString
    while (fileInputStream.good() && fileInputStream.is_open()) {
        const char currentCharacter = static_cast<char>(fileInputStream.get());

        if (isRestOfFileInput) {
            inputStream.put(currentCharacter);
        }
        else if (isCharAcceptable(currentCharacter)) {
            if (currentCharacter == '!') {
                isRestOfFileInput = true;
            }
            fileString.push_back(currentCharacter);
        }
    }

    std::printf("\n");

    return fileString;
}

int main() {
    const String fileString = getFileString();
    const auto start = std::chrono::steady_clock::now();

    // main loop
    for (int i = 0; i < fileString.size(); i++) {
        const char currentCharacter = fileString.at(i);
        const CellType curValue = getCurrentMemory();\

        switch (currentCharacter) {
            case '>':
                incrementPointer();
                break;
            case '<':
                decrementPointer();
                break;
            case '+':
                incrementCurrentMemory();
                break;
            case '-':
                decrementCurrentMemory();
                break;
            case '.': {
                if ((curValue == 10 || curValue == 13) && processOutputNewLines) {
                    // if you're on windows, print \r\n, else print \n
                    #if defined(_WIN32) || defined(_WIN64)
                                        std::cout << "\r\n";
                    #elif defined(__APPLE__) || defined(__linux__)
                                        std::cout << "\n";
                    #endif
                }
                else {
                    std::cout << static_cast<char>(curValue);
                }
            }
                break;
            case ',': {
                int inputChar;

                if (!inputStream.str().empty()) {
                    inputChar = inputStream.get();
                    std::cout << static_cast<char>(inputChar); // optional, if the input is predefined, lets user see it in console
                }
                else
                    inputChar = getchar();

                if (inputChar == 13 && processInputNewLines) {
                    inputChar = 10;
                }
                else if (inputChar == EOF) {
                    switch (eofBehavior) {
                        case Zero:
                            inputChar = 0;
                            break;
                        case MinusOne:
                            inputChar = std::numeric_limits<CellType>::max();
                            break;
                        case Ignore:
                            inputChar = getCurrentMemory();
                            break;
                    }
                }

                getCurrentMemory() = static_cast<CellType>(inputChar);
            }
                break;
            case '[':
                if (curValue == 0) {
                    // loop to find matching ']'
                    int openLoops = 1;
                    while (openLoops > 0) {
                        if (i > fileString.size() || i < 0) {
                            throw std::runtime_error(R"(A loop is missing a "[" or "]" somewhere)");
                        }
                        char curLoopChar = fileString.at(++i);

                        if (curLoopChar == '[')
                            openLoops++;
                        else if (curLoopChar == ']')
                            openLoops--;
                    }
                }
                break;
            case ']':
                if (curValue != 0) {
                    // loop backwards to find matching '['
                    int openLoops = 1;
                    while (openLoops > 0) {
                        if (i > fileString.size() || i < 0) {
                            throw std::runtime_error(R"(A loop is missing a "[" or "]" somewhere)");
                        }

                        char curLoopChar = fileString.at(--i);

                        if (curLoopChar == '[')
                            openLoops--;
                        else if (curLoopChar == ']')
                            openLoops++;
                    }
                }
                break;
            case '#':
                std::printf("Current memory pointer %d, Current cell value %c, Current cell int value %d", memoryPointer, getCurrentMemory(), static_cast<int>(getCurrentMemory()));
                break;
            default:
                break;
        }
    }

    const auto end = std::chrono::steady_clock::now();

    const auto difference = end - start;
    std::cout << '\n' << std::chrono::duration<double, std::milli>(difference).count() << " ms" << std::endl;
}