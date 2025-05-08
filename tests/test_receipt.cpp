#include <gtest/gtest.h>
#include "../receipt.hpp"

class ReceiptTest : public ::testing::Test {
protected:
    Receipt receipt;
    Product хлеб = {"Хлеб", 111, 30.0};
    Product молоко = {"Молоко", 222, 60.0};
};

TEST_F(ReceiptTest, CalculatesCorrectTotal) {
    receipt.addItem(хлеб, 2);   // 60
    receipt.addItem(молоко, 1); // 60
    EXPECT_DOUBLE_EQ(receipt.getTotal(), 120.0);
}

TEST_F(ReceiptTest, HandlesZeroItems) {
    EXPECT_DOUBLE_EQ(receipt.getTotal(), 0.0);
}

TEST_F(ReceiptTest, AddsMultipleIdenticalItems) {
    receipt.addItem(хлеб, 1);
    receipt.addItem(хлеб, 2);
    EXPECT_DOUBLE_EQ(receipt.getTotal(), 30.0 * 3);
}
