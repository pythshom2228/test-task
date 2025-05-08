#include <gtest/gtest.h>
#include "../database.hpp"

class ProductDatabaseTest : public ::testing::Test {
protected:
    ProductDatabase db;

    void SetUp() override {
        ASSERT_TRUE(db.loadFromFile("products"));
    }
};

TEST_F(ProductDatabaseTest, FindsByBarcode) {
    const Product* p = db.findByBarcode(111);
    ASSERT_NE(p, nullptr);
    EXPECT_EQ(p->name, "Хлеб");
    EXPECT_DOUBLE_EQ(p->price, 30.0);
}

TEST_F(ProductDatabaseTest, FindsByName) {
    const Product* p = db.findByName("Молоко");
    ASSERT_NE(p, nullptr);
    EXPECT_EQ(p->barcode, 222);
    EXPECT_DOUBLE_EQ(p->price, 60.0);
}

TEST_F(ProductDatabaseTest, HandlesUnknownBarcodeAndName) {
    EXPECT_EQ(db.findByBarcode(9999), nullptr);
    EXPECT_EQ(db.findByName("Неизвестный товар"), nullptr);
}
