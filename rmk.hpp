#pragma once
#include "product.hpp"
#include "database.hpp"
#include "receipt.hpp"
#include "cashier.hpp"
#include <iostream>

namespace RMK {

    void run(const ProductDatabase& db, CashierSession& session);

    void handleCash(CashierSession& session);

    void handleReceipt(const Receipt& receipt, CashierSession& session);

    std::string promptPaymentType();
}