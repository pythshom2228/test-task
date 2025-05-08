#include "receipt.hpp"
#include "database.hpp"
#include <iostream>
#include <limits>
#include <iomanip>

void Receipt::generate(std::string& input, const ProductDatabase& db) {
    while (true) {
        std::cout << "Введите название или штрих-код товара (или 'конец'): ";
        std::cin >> input;
        if (input == "конец") break;

        const Product* p = nullptr;
        try {
            size_t barcode = std::stoull(input);
            p = db.findByBarcode(barcode);
        } catch (...) {
            p = db.findByName(input);
        }
        

        if (!p) {
            std::cout << "Товар не найден\n";
            continue;
        }

        std::cout << "Введите количество: ";
        int quantity;
        std::cin >> quantity;
        if(std::cin.fail() || quantity < 1) {
            std::cout << "Некорректный ввод\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            this->addItem(*p, quantity);
        }

    }
}

void Receipt::addItem(const Product& product, int quantity) {
    total += product.price * quantity;
    items.push_back({product, quantity});
}

double Receipt::getTotal() const {
    return total;
}

void Receipt::print(const std::string& paymentType, double paidAmount) const {
    std::cout << "\n======== Чек ========\n";
    for (const auto& item : items) {
        std::cout << item.product.name << " x" << item.quantity
                  << " по " << item.product.price << "\n";
    }
    std::cout << "Итого: " << total << "\n";
    std::cout << "Оплата: " << paymentType << "\n";
    std::cout << "Внесено: " << paidAmount << "\n";
    std::cout << "Сдача: " << paidAmount - total << "\n";
    std::cout << "=====================\n\n";
}
