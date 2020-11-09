#include "MaxCommonSuffix.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>

TEST(MaxCommonSuffixTest, test1) {
	EXPECT_EQ(solve("ab+c.aba.*.bac.+.+*", "babc"), 2);
}

TEST(MaxCommonSuffixTest, test2) {
	EXPECT_EQ(solve("acb..bab.c.*.ab.ba.+.+*a.", "cbaa"), 4);
}

TEST(MaxCommonSuffixTest, test3) {
	EXPECT_EQ(solve("ab.1+*c.", "abababc"), 7);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}