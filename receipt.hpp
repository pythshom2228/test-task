#pragma once
#include "product.hpp"
#include <vector>
#include <string>

class ProductDatabase;

struct ReceiptItem {
    Product product;
    int quantity;
};

class Receipt {
public:
    Receipt() = default;

    void generate(std::string& input, const ProductDatabase& db);
    void addItem(const Product& product, int quantity);
    void print(const std::string& paymentType, double paidAmount) const;
    
    double getTotal() const;

private:
    double total = 0.0;

    std::vector<ReceiptItem> items;
};
