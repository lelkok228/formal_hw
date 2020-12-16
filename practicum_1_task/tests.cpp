#include "MaxCommonSuffix.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>

/*TEST(MaxCommonSuffixTest, test1) {
	EXPECT_EQ(solve("ab+c.aba.*.bac.+.+*", "babc"), 2);
}

TEST(MaxCommonSuffixTest, test2) {
	EXPECT_EQ(solve("acb..bab.c.*.ab.ba.+.+*a.", "cbaa"), 4);
}

TEST(MaxCommonSuffixTest, test3) {
	EXPECT_EQ(solve("ab.1+*c.", "abababc"), 7);
}*/

TEST(MaxCommonSuffixTest, equalityTests) {
	DerivedSubstring derivedSubstring1 = DerivedSubstring('a', "ba");
	DerivedSubstring derivedSubstring2 = DerivedSubstring('a', "ca");
	DerivedSubstring derivedSubstring3 = DerivedSubstring('b', "ba");

	EXPECT_TRUE(derivedSubstring1 == derivedSubstring2);
	EXPECT_FALSE(derivedSubstring1 == derivedSubstring3);

	// 15% coverage of MaxCommonSuffix.cpp
	// but constructor and operator== tested
}

TEST(MaxCommonSuffixTest, multiplicationTests) {
	DerivedSubstring derivedSubstring1 = DerivedSubstring('1', "bab");
	DerivedSubstring derivedSubstring2 = DerivedSubstring('a', "bab");
	DerivedSubstring derivedSubstring3 = DerivedSubstring('b', "bab");

	DerivedSubstring derivedSubstring4 = derivedSubstring3 * derivedSubstring2;
	EXPECT_EQ(derivedSubstring4, DerivedSubstring({{false, true, false}, {false, false, false}, {false, false, false}}, false, {0, 2, 0}));

	derivedSubstring4 *= derivedSubstring3;
	EXPECT_EQ(derivedSubstring4, DerivedSubstring({{false, false, true}, {false, false, false}, {false, false, false}}, false, {1, 0, 3}));
	
	derivedSubstring4 *= derivedSubstring1;
	EXPECT_EQ(derivedSubstring4, DerivedSubstring({{false, false, true}, {false, false, false}, {false, false, false}}, false, {1, 0, 3}));

	// 46% coverage of MaxCommonSuffix.cpp
}

TEST(MaxCommonSuffixTest, summaryTests) {
	DerivedSubstring derivedSubstring1 = DerivedSubstring({{false, true, false}, {false, false, false}, {false, false, false}}, false, {0, 2, 3});
	DerivedSubstring derivedSubstring2 = DerivedSubstring({{true, false, true}, {false, true, true}, {false, false, false}}, true, {1, 1, 1});
	DerivedSubstring derivedSubstring3 = DerivedSubstring({{true, true, false}, {false, true, false}, {false, false, true}}, false, {0, 0, 3});

	EXPECT_EQ(derivedSubstring1 + derivedSubstring2, DerivedSubstring({{true, true, true}, {false, true, true}, {false, false, false}}, true, {1, 2, 3}));
	EXPECT_EQ(derivedSubstring1 + derivedSubstring3, DerivedSubstring({{true, true, false}, {false, true, false}, {false, false, true}}, false, {0, 2, 3}));
	EXPECT_EQ(derivedSubstring2 + derivedSubstring3, DerivedSubstring({{true, true, true}, {false, true, true}, {false, false, true}}, true, {1, 1, 3}));

	// 19% coverage of MaxCommonSuffix.cpp
}

TEST(MaxCommonSuffixTest, KleeneStarTests) {
	DerivedSubstring derivedSubstring1 = DerivedSubstring({{false, false, false}, {false, true, false}, {false, false, true}}, false, {1, 0, 0});
	DerivedSubstring derivedSubstring2 = DerivedSubstring({{true, false, true}, {false, true, true}, {false, false, false}}, true, {0, 2, 3});

	EXPECT_EQ(derivedSubstring1.KleeneStar(), DerivedSubstring({{false, false, false}, {false, true, true}, {false, false, true}}, true, {1, 2, 3}));
	EXPECT_EQ(derivedSubstring2.KleeneStar(), DerivedSubstring({{true, true, true}, {false, true, true}, {false, false, false}}, true, {0, 2, 3}));

	// 71% coverage of MaxCommonSuffix.cpp
}

TEST(MaxCommonSuffixTest, sampleTests) {
	EXPECT_EQ(solve("ab+c.aba.*.bac.+.+*", "babc"), 2);
	EXPECT_EQ(solve("acb..bab.c.*.ab.ba.+.+*a.", "cbaa"), 4);
	EXPECT_EQ(solve("ab.1+*c.", "abababc"), 7);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}