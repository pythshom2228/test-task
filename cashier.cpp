#include "cashier.hpp"
#include <iostream>

void CashierSession::open(const std::string& name, double initialCash) {
    cashierName = name;
    cashInDrawer = initialCash;
    isOpen = true;
}

void CashierSession::close() {
    std::cout << "\n=== Смена закрыта ===\n";
    std::cout << "Кассир: " << cashierName << "\n";
    for (auto it = paymentStats.begin(); it != paymentStats.end(); ++it) {
        std::cout << it->first << ": " << it->second << "\n";
    }
    std::cout << "=====================\n\n";

    isOpen = false;
    paymentStats.clear();
}


void CashierSession::updateStats(const std::string& paymentType, double amount) {
    paymentStats[paymentType] += amount;
}
