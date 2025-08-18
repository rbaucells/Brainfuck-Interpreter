// #include <iostream>
//
// unsigned char tape[30000] = {0};
// unsigned char* ptr = tape;
//
// void interpret(char* input)
// {
//     char current_char;
//     unsigned int i, loop;
//
//     for (i = 0; input[i] != 0; ++i)
//     {
//         current_char = input[i];
//
//         switch (current_char)
//         {
//             case '>':
//                 ++ptr;
//                 break;
//             case '<':
//                 --ptr;
//                 break;
//             case '+':
//                 ++*ptr;
//                 break;
//             case '-':
//                 --*ptr;
//                 break;
//             case '.':
//                 putchar(*ptr);
//                 break;
//             case ',':
//                 *ptr = getchar();
//                 break;
//             case '[':
//                 if (*ptr == 0)
//                 {
//                     loop = 1;
//                     while (loop > 0)
//                     {
//                         current_char = input[++i];
//                         if (current_char == '[')
//                             loop++;
//                         else if (current_char == ']')
//                             loop--;
//                     }
//                 }
//                 break;
//             case ']':
//                 if (*ptr)
//                 {
//                     loop = 1;
//                     while (loop > 0)
//                     {
//                         current_char = input[--i];
//                         if (current_char == '[')
//                             loop--;
//                         else if (current_char == ']')
//                             loop++;
//                     }
//                 }
//         }
//     }
// }
//
// int main()
// {
//     char str[1024];
//     std::cin.get(str, 1024);
//
//     const auto start = std::chrono::steady_clock::now();
//     interpret(str);
//     const auto end = std::chrono::steady_clock::now();
//
//     const auto difference = end - start;
//     std::cout << '\n' << std::chrono::duration<double, std::milli>(difference).count() << " ms" << std::endl;
//
//     putchar('\n');
//
//     return 0;
// }