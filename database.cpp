#include "database.hpp"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;



bool ProductDatabase::loadFromFile(const std::string& filename) {
    std::ifstream file(filename + ".json");
    if (!file.is_open()) {
        std::cout << "Файл не найден либо формат файла не поддерживается\n";
        return false;
    }

    json data;

    try {
        file >> data;
    } catch(...) {
        std::cerr << "Ошибка чтения файла, либо файл пуст\n";
        return false;
    }
    

    for (const auto& item : data) {
        
        if (!item.contains("name") || !item.contains("price") || !item.contains("barcode")) {
            std::cout << "Некорректная запись в JSON\n";
            continue;
        }
        
        const std::string name = item["name"];
        const size_t barcode = item["barcode"];
        const double price = item["price"]; 

        if (price <= 0) {
            std::cout << "Некорректная цена товара: " << name << "\n";
            continue;
        }        
        if(item["barcode"] < 0) {
            std::cout <<  "Некорректный штрихкод товара: " << name << "\n";
            continue;
        }

        nameIndex.emplace(
           name,
           Product{name,barcode,price} 
        );

        barcodeIndex.emplace(
            barcode,
            Product{name,barcode,price}
        );
    }
    return true;
}

const Product* ProductDatabase::findByBarcode(size_t barcode) const {
    if(barcodeIndex.count(barcode)) {
        return &barcodeIndex.at(barcode);
    }
    return nullptr;
}

const Product* ProductDatabase::findByName(const std::string& name) const {
    if(nameIndex.count(name)) {
        return &nameIndex.at(name);
    }
    return nullptr;
}
