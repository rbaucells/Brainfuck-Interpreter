#include <fstream>
#include <iostream>

using String = std::string;

// < and > to move memoryPointer
// + and - to modify memory.at(memoryPointer);
// . to print ASCI representation of memory.at(memoryPointer)
// , to write input's ASCI representation into memory.at(memoryPointer)
// [] to do while loop. when ], go back to [ if memory.at(memoryPointer) != 0

constexpr int MEMORY_SIZE = 30000;
unsigned char memory[MEMORY_SIZE] = {};
int memoryPointer = 0;

unsigned char& getCurrentMemory() {
    return memory[memoryPointer];
}

void incrementPointer() {
    if (memoryPointer == MEMORY_SIZE - 1)
        memoryPointer = 0;
    else
        memoryPointer++;
}

void decrementPointer() {
    if (memoryPointer == 0) // If the pointer reaches zero
        memoryPointer = MEMORY_SIZE - 1;
    else
        memoryPointer--;
}

bool isCharAcceptable(const char character) {
    return character == '>' || character == '<' || character == '+' || character == '-' || character == '[' || character == ']' || character == '.' || character == ',';
}

String getFileString() {
    std::printf("Path to file: \n");
    String filePath;
    getline(std::cin, filePath);

    std::ifstream fileInputStream(filePath, std::fstream::in);
    String fileString;

    while (fileInputStream.good() && fileInputStream.is_open()) {
        char currentCharacter = static_cast<char>(fileInputStream.get());

        if (isCharAcceptable(currentCharacter)) {
            fileString.push_back(currentCharacter);
        }
    }

    return fileString;
}


int main() {
    const String fileString = getFileString();
    const auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < fileString.size(); i++) {
        const char currentCharacter = fileString.at(i);
        const unsigned char curValue = getCurrentMemory();

        switch (currentCharacter) {
            case '>':
                incrementPointer();
                break;
            case '<':
                decrementPointer();
                break;
            case '+':
                getCurrentMemory()++;
                break;
            case '-':
                getCurrentMemory()--;
                break;
            case '.':
                std::cout << curValue;
                break;
            case ',':
                char inputChar;
                std::cin.get(inputChar);
                getCurrentMemory() = static_cast<unsigned char>(inputChar);
                break;
            case '[':
                if (curValue == 0) {
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
            default:
                break;
        }
    }

    const auto end = std::chrono::steady_clock::now();

    const auto difference = end - start;
    std::cout << '\n' << std::chrono::duration<double, std::milli>(difference).count() << " ms" << std::endl;
}