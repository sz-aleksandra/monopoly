//
// Created by jakub on 06.06.23.
//

#include "consoleview.h"

void clear_screen() {
#ifdef dummy
    for (int i=0; i<100; i++)
        std::cout << "\n";
#elif unix
    std::system("clear");
#else
    std::system ("cls");
#endif
}

void wait_for_key() {
    std::cin.get();
    std::cin.get();     // sometimes will lag but anyway
}