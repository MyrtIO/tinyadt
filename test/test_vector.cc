#include <unity.h>
#include <TinyADT/vector.h>

void test_VectorShouldPushToBack() {
    StaticVector<int, 2> numbers;

    TEST_ASSERT_EQUAL(true, numbers.push_back(1));
    TEST_ASSERT_EQUAL(true, numbers.push_back(2));
    TEST_ASSERT_EQUAL(false, numbers.push_back(3));

	TEST_ASSERT_EQUAL(1, numbers[0]);
	TEST_ASSERT_EQUAL(2, numbers[1]);
}

void test_VectorShouldReportSize() {
	StaticVector<int, 2> numbers;

	TEST_ASSERT_EQUAL(2, numbers.capacity());
	TEST_ASSERT_EQUAL(0, numbers.size());

	numbers.push_back(1);
	TEST_ASSERT_EQUAL(1, numbers.size());
	numbers.push_back(2);
	TEST_ASSERT_EQUAL(2, numbers.size());

	numbers.pop_back();
	TEST_ASSERT_EQUAL(1, numbers.size());
	numbers.pop_back();
	TEST_ASSERT_EQUAL(0, numbers.size());
}

void test_VectorShouldIterate() {
	StaticVector<int, 3> numbers;

	numbers.push_back(0);
	numbers.push_back(1);
	numbers.push_back(2);

	uint8_t expected;

	// Forward
	expected = 0;
	for (auto it = numbers.begin(); it != numbers.end(); ++it) {
		TEST_ASSERT_EQUAL(expected++, *it);
	}

	// Backward
	expected = 2;
	for (auto it = numbers.end(); it != numbers.begin(); --it) {
		TEST_ASSERT_EQUAL(expected--, *it);
	}
}

void test_VectorShouldClear() {
	StaticVector<int, 3> numbers;

	numbers.push_back(0, 1, 2);
	numbers.clear();

	TEST_ASSERT_EQUAL(0, numbers.size());
	TEST_ASSERT_EQUAL(0, numbers[1]);
}

void test_VectorShouldSafeAccess() {
	StaticVector<int, 2> numbers;
	numbers.push_back(1, 3);

	TEST_ASSERT_EQUAL(1, numbers.at(0));
	TEST_ASSERT_EQUAL(3, numbers.at(1));
	// Should not panic
	numbers.at(99);
}

void testVector() {
	RUN_TEST(test_VectorShouldPushToBack);
	RUN_TEST(test_VectorShouldReportSize);
	RUN_TEST(test_VectorShouldIterate);
	RUN_TEST(test_VectorShouldClear);
	RUN_TEST(test_VectorShouldSafeAccess);
}
