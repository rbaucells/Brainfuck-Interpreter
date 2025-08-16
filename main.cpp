#include <fstream>
#include <iostream>
using String = std::string;

// < and > to move memoryPointer
// + and - to modify memory.at(memoryPointer);
// . to print ASCI representation of memory.at(memoryPointer)
// , to write input's ASCI representation into memory.at(memoryPointer)
// [] to do while loop. when ], go back to [ if memory.at(memoryPointer) != 0

std::vector<unsigned char> memory = {0};
int memoryPointer = 0;

std::vector<int> loopStarts = {};

void incrementMemoryPointer() {
    if (memory.at(memoryPointer) == UCHAR_MAX)
        memory.at(memoryPointer) = 0;
    else
        memory.at(memoryPointer)++;
}

void decrementMemoryPointer() {
    if (memory.at(memoryPointer) == 0)
        memory.at(memoryPointer) = UCHAR_MAX;
    else
        memory.at(memoryPointer)--;
}

void processChar(const char& currentCharacter) {
    switch (currentCharacter) {
        case '>':
            memoryPointer++;
            memory.push_back(0);
            break;

        case '<':
            memoryPointer--;
            break;

        case '+':
            incrementMemoryPointer();
            break;

        case '-':
            decrementMemoryPointer();
            break;

        case '.':
            std::printf("integer value = %d, char value = %c \n", static_cast<int>(memory.at(memoryPointer)), memory.at(memoryPointer));
            break;

        case ',':
            std::cin >> memory.at(memoryPointer);
            break;

        default:;
    }
}

int main() {
    std::ifstream fileInputStream("text.txt", std::fstream::in);

    std::string fileString;

    while (fileInputStream.good() && fileInputStream.is_open()) {
        char currentCharacter = fileInputStream.get();

        fileString.push_back(currentCharacter);
    }

    for (int i = 0; i < fileString.size(); i++) {
        char currentCharacter = fileString.at(i);

        if (!isascii(currentCharacter)) {
            fileInputStream.close();
            break;
        }

        if (currentCharacter == '[') {
            unsigned char curValue = memory.at(memoryPointer);

            if (curValue == 0) {
                int index = i;
                int openLoops = 1;

                while (openLoops != 0) {
                    if (index > fileString.size()) {
                        throw std::runtime_error("A loop is missing a \"[\" or \"]\" somewhere");
                    }

                    char curLoopChar = fileString.at(index);

                    if (curLoopChar == '[')
                        openLoops++;
                    else if (curLoopChar == ']')
                        openLoops--;

                    index++;
                }

                i = index;
            }

            loopStarts.push_back(i);
            continue;
        }

        if (currentCharacter == ']') {
            unsigned char curValue = memory.at(memoryPointer);

            if (curValue != 0) {
                i = loopStarts.back();
            }
            else {
                loopStarts.pop_back();
            }

            continue;
        }

        processChar(currentCharacter);
    }

    return 0;
}