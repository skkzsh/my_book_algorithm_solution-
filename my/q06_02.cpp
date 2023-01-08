#include "gtest/gtest.h"
#include <algorithm>
#include <ranges>

using std::vector;
using std::tuple;
using std::get;

using Trio = tuple<vector<int>, vector<int>, vector<int>>;

// O(N ^ 3)
int festival_simple(const Trio z) {
    int count = 0;

    for (const int a : get<0>(z)) {
        for (const int b : get<1>(z)) {
            if (a < b) {
                for (int c : get<2>(z)) {
                    if (b < c) {
                        count++;
                    }
                }
                // count += std::ranges::count_if(z[2], [b](int c){ return b < c; });
            }
        }
    }

    return count;
}

// O(N log N)
int festival_binary(Trio z) {
    using namespace std::ranges;

//    for (const int i : std::views::iota(0, 3)) {
//        sort(get<i>(z));
//    }

    sort(get<0>(z));
    sort(get<1>(z));
    sort(get<2>(z));

    int count = 0;

    for (const int b : get<1>(z)) {
        count += (lower_bound(get<0>(z), b) - get<0>(z).begin()) // a[i] >= b となる最小のi <=> a[i - 1] < b <= a[i] => 数は (i - 1) - 0 + 1 = iコ
                    * (get<2>(z).end() - upper_bound(get<2>(z), b)); // c[i] > b となる最小のi => 数は N - i + 1 => c.end() - i
        // count += (lower_bound(get<0>(z), b) - get<0>(z).begin())
        //             * (N - (upper_bound(get<2>(z), b) - get<2>(z).begin()));
    }

    return count;
}


TEST(TestCase, Ex1) {
    const Trio z {
        {1, 5},
        {2, 4},
        {3, 6},
    };

    EXPECT_EQ(festival_simple(z), 3);
    EXPECT_EQ(festival_binary(z), 3);
}

TEST(TestCase, Ex2) {
    const Trio z {
        {1, 1, 1},
        {2, 2, 2},
        {3, 3, 3},
    };

    EXPECT_EQ(festival_simple(z), 27);
    EXPECT_EQ(festival_binary(z), 27);
}

TEST(TestCase, Ex3) {
    const Trio z {
        {3, 14, 159, 2, 6, 53},
        {58, 9, 79, 323, 84, 6},
        {2643, 383, 2, 79, 50, 288},
    };

    EXPECT_EQ(festival_simple(z), 87);
    EXPECT_EQ(festival_binary(z), 87);
}

TEST(TestCase, Ex0ab) {
    const Trio z {
        {1, 1},
        {1, 1},
        {2, 2},
    };

    EXPECT_EQ(festival_simple(z), 0);
    EXPECT_EQ(festival_binary(z), 0);
}

TEST(TestCase, Ex0bc) {
    const Trio z {
        {1, 1},
        {2, 2},
        {2, 2},
    };

    EXPECT_EQ(festival_simple(z), 0);
    EXPECT_EQ(festival_binary(z), 0);
}
