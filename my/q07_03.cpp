#include "gtest/gtest.h"
#include <algorithm>
#include "template.hpp"

// 例で考える
// {P(10, 30), Q(40, 50)} => P -> Qの順が必須
// {P(10, 30), Q(20, 40)} => どの順でもOK

// 定義
// P(d[i], t[i]), Q(d[j], t[j])
// t[i] < t[j]
// 命題
// Q -> P の順 <=> d[j] < t[j] かつ d[j] + d[i] < t[i]
// を
// P -> Q の順 <=> d[i] < t[i] かつ d[i] + d[j] < t[j]
// にできるか
// 導出
// d[i] < t[i] - d[i] < t[i] => d[i] < t[i]
// d[i] + d[j] < t[i] < t[j] => d[i] + d[j] < t[j]
// => 交換可能

bool can_done(Pairs<int> tasks) { // {d, t}
    std::ranges::sort(tasks, [](const auto p, const auto q) {
        return p.second < q.second;
    });

    int now = 0;

    for (const auto& task : tasks) {
        now += task.first;
        if (now > task.second) {
            return false;
        }
    }

    return true;
}


TEST(TestCase, Ex1) {
    const Pairs<int> tasks {
        {2, 4},
        {1, 9},
        {1, 8},
        {4, 9},
        {3, 12},
    };

    EXPECT_EQ(can_done(tasks), true);
}

TEST(TestCase, Ex2) {
    const Pairs<int> tasks {
        {334, 1000},
        {334, 1000},
        {334, 1000},
    };

    EXPECT_EQ(can_done(tasks), false);
}

TEST(TestCase, Ex3) {
    const Pairs<int> tasks {
        { 384,  8895  },
        { 1725, 9791  },
        { 170,  1024  },
        { 4,    11105 },
        { 2,    6     },
        { 578,  1815  },
        { 702,  3352  },
        { 143,  5141  },
        { 1420, 6980  },
        { 24,   1602  },
        { 849,  999   },
        { 76,   7586  },
        { 85,   5570  },
        { 444,  4991  },
        { 719,  11090 },
        { 470,  10708 },
        { 1137, 4547  },
        { 455,  9003  },
        { 110,  9901  },
        { 15,   8578  },
        { 368,  3692  },
        { 104,  1286  },
        { 3,    4     },
        { 366,  12143 },
        { 7,    6649  },
        { 610,  2374  },
        { 152,  7324  },
        { 4,    7042  },
        { 292,  11386 },
        { 334,  5720  },
    };

    EXPECT_EQ(can_done(tasks), true);
}
