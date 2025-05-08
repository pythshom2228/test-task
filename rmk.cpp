#include "rmk.hpp"
#include <limits>

void RMK::run(const ProductDatabase& db, CashierSession& session) {
    while (true) {
        std::string input;
        
        // Если сессия не открыта открываем
        if (!session.isOpen) {
            std::cout << "Открыть смену? (да/нет): ";
            std::cin >> input; 

            if (input == "да")  {
            std::cout << "Введите имя кассира: ";
            std::cin >> session.cashierName;

            RMK::handleCash(session);
            }
            else if(input == "нет") {
                break;
            }
            else {

                std::cout << "Введите да/нет\n";
                continue; 
            }
        }

        std::cout << "Создать новый чек? (да/нет): ";
        std::cin >> input;

        if (input == "да") {
            Receipt receipt;
            receipt.generate(input, db);

            if(receipt.getTotal() != 0) RMK::handleReceipt(receipt, session);
            else std::cout << "Чек не пробит\n";

        }
        else if(input == "нет") {
            std::cout << "Закрыть смену? (да/нет): ";
            std::cin >> input;
            if (input == "да") session.close();

            continue;
        }
        else {
            std::cout << "Введите да/нет\n";
            continue;
        }

    }
}

void RMK::handleCash(CashierSession& session) {
    bool isCashCorrect = false;

    while(!isCashCorrect) {
        std::cout << "Введите стартовую сумму наличности: ";
        std::cin >> session.cashInDrawer;
        
        if(std::cin.fail()) {
            std::cout << "Некорректный ввод\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        else if(session.cashInDrawer < 100) {
            std::cout << "Сумма наличности должна быть не меньше 100\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        isCashCorrect = true;
    }
    session.isOpen = true;
}

void RMK::handleReceipt(const Receipt& receipt, CashierSession& session) {
    double paid;
    double numberToPay = receipt.getTotal();
    std::string payType;
    while(true) {
        payType = RMK::promptPaymentType();

        if (payType == "нал") {
            std::cout << "Введите внесенную сумму: ";
            std::cin >> paid;
            
            if(std::cin.fail() || paid < 0) {
                std::cout << "Некорректный ввод\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                continue;
            }

            // Если внесено меньше чем нужно
            if (paid < numberToPay) {
                std::cout << "Недостаточно средств! Нужно внести не менее " << numberToPay << "\n";
                continue;
            }

            // Иначе если внесено больше чем нужно
            else if(paid > numberToPay) {
                double change = paid - numberToPay;
                if(session.cashInDrawer < change) {
                    std::cout << "Не хватает сдачи " << change - session.cashInDrawer << ". Оплата возможна картой\n";
                    continue;
                }
                session.cashInDrawer -= change;
                session.cashInDrawer += numberToPay;
                break;
            }
            // Если внесено сколько нужно                 
            else {
                break;
            }
        }
        else {
            paid = numberToPay;  // карта, ровно сумма чека
            break;
        }
    }

    receipt.print(payType, paid);
    session.updateStats(payType, numberToPay);
}

std::string RMK::promptPaymentType() {
    std::string type;
    while (true) {
        std::cout << "Введите способ оплаты (нал/карта): ";
        std::cin >> type;
        if (type == "нал" || type == "карта") return type;
        std::cout << "Некорректный ввод\n";
    }
}