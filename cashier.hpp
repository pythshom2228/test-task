#pragma once
#include <string>
#include <map>

class CashierSession {
public:
    bool isOpen = false;
    std::string cashierName;
    double cashInDrawer = 0.0;
    std::map<std::string, double> paymentStats;

    void open(const std::string& name, double initialCash);
    void close();
    void updateStats(const std::string& paymentType, double amount);
};
