// #include <fstream>
// #include <iostream>
//
// using string = std::string;
//
// int loop(const string& code, int code_index, unsigned char *memory, int memory_index);
//
// int execute_code(const string& code, int code_index, unsigned char *memory, int& memory_index) {
//     // process chars
//     switch (code.at(code_index)) {
//         case '+':
//             // increment value
//             memory[memory_index]++;
//             break;
//         case '-':
//             // increment value
//             memory[memory_index]--;
//             break;
//         case '.':
//             // print
//             std::cout << memory[memory_index];
//             break;
//         case '[':
//             // loop
//             return loop(code, code_index, memory, memory_index);
//         case '<':
//             memory_index--;
//             break;
//         case '>':
//             memory_index++;
//             break;
//         case ',':
//             char inputChar;
//             std::cin.get(inputChar);
//             memory[memory_index] = static_cast<unsigned char>(inputChar);
//             break;
//     }
//     return code_index;
// }
//
// // code_index => '['
// int loop(const string& code, int code_index, unsigned char *memory, int memory_index) {
//     // evaluate stack
//     while (true) {
//         // evaluate current memory value
//         unsigned char value = memory[memory_index];
//         // loop until ']'
//         for (int i = code_index + 1; i < code.size(); i++) {
//             // current char
//             auto current = code.at(i);
//             // check ']'
//             if (current == ']') {
//                 // check we need to do another loop
//                 if (memory[memory_index] != 0)
//                     break;
//                 // exit
//                 return i;
//             }
//             // '['
//             if (current == '[') {
//                 // process loop
//                 i = loop(code, i, memory, memory_index);
//                 // next
//                 continue;
//             }
//             // check we need to execute code within the loop
//             if (value != 0) {
//                 // execute code
//                 i = execute_code(code, i, memory, memory_index);
//             }
//         }
//     }
//     return -1;
// }
//
// void execute(const string& code) {
//     // memory
//     unsigned char memory[255] = {};
//     int memory_index = 0;
//     // loop chars
//     for (int i = 0; i < code.size(); i++) {
//         // execute code at
//         i = execute_code(code, i, memory, memory_index);
//     }
// }
//
// string getFileString() {
//     std::printf("Path to file: \n");
//     string filePath;
//     getline(std::cin, filePath);
//
//     std::ifstream fileInputStream(filePath, std::fstream::in);
//
//     string fileString;
//
//     while (fileInputStream.good() && fileInputStream.is_open()) {
//         char currentCharacter = static_cast<char>(fileInputStream.get());
//         fileString.push_back(currentCharacter);
//     }
//
//     return fileString;
// }
//
//
// int main() {
//     const auto code = getFileString();
//
//     const auto start = std::chrono::steady_clock::now();
//     execute(code);
//     const auto end = std::chrono::steady_clock::now();
//
//     const auto difference = end - start;
//     std::cout << '\n' << std::chrono::duration<double, std::milli>(difference).count() << " ms" << std::endl;
// }