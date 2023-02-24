#include "gtest/gtest.h"

long long tribo(const int N) {
    if (N < 0) {
        throw std::invalid_argument("argument must not be negative");
    }

    // ベースケース
    switch(N) {
        case 0:
        case 1:
            return 0;
        case 2:
            return 1;
        default:
            // 再帰呼び出し
            return tribo(N - 1) + tribo(N - 2) + tribo(N - 3);
    }
}


TEST(TestSuite, Test20) {
    EXPECT_EQ(tribo(20), 35890);
}

TEST(TestSuite, Negative) {
    EXPECT_THROW(tribo(-1), std::invalid_argument);
}

