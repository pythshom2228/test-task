#pragma once
#include "product.hpp"
#include <vector>
#include <string>
#include <unordered_map>

class ProductDatabase {
public:

    ProductDatabase() = default;

    bool loadFromFile(const std::string& filename);

    const Product* findByBarcode(size_t barcode) const;
    const Product* findByName(const std::string& name) const; 

private:

    std::unordered_map<size_t, Product> barcodeIndex;
    std::unordered_map<std::string, Product> nameIndex;
};
