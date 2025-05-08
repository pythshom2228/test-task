#include "rmk.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cout << "Укажите 1 параметр: название файла\n";
        return 1;
    }

    ProductDatabase db;
    if (!db.loadFromFile(argv[1]))
        return 1;

    CashierSession session;

    RMK::run(db,session);

    return 0;
 
}

