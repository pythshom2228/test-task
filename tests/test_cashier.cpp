#include <gtest/gtest.h>
#include "../cashier.hpp"

class CashierSessionTest : public ::testing::Test {
protected:
    CashierSession session;
};

TEST_F(CashierSessionTest, OpensSessionCorrectly) {
    session.open("Петров", 1000.0);
    EXPECT_TRUE(session.isOpen);
    EXPECT_EQ(session.cashierName, "Петров");
    EXPECT_DOUBLE_EQ(session.cashInDrawer, 1000.0);
}


TEST_F(CashierSessionTest, UpdatesStatsCorrectly) {
    session.open("Сидоров", 500.0);
    session.updateStats("нал", 100.0);
    session.updateStats("нал", 150.0);
    session.updateStats("карта", 200.0);
    EXPECT_DOUBLE_EQ(session.paymentStats["нал"], 250.0);
    EXPECT_DOUBLE_EQ(session.paymentStats["карта"], 200.0);
}

TEST_F(CashierSessionTest, ClosesSessionAndResetsStats) {
    session.open("Иванов", 700.0);
    session.updateStats("нал", 100.0);
    session.close();
    EXPECT_FALSE(session.isOpen);
    EXPECT_TRUE(session.paymentStats.empty());
}
