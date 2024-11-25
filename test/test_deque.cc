#include <unity.h>
#include <TinyADT/deque.h>
#include <Arduino.h>

void test_DequeShouldPushToBack() {
    StaticDeque<int, 2> deque;

    TEST_ASSERT_EQUAL(true, deque.push_back(1));
    TEST_ASSERT_EQUAL(true, deque.push_back(2));
    TEST_ASSERT_EQUAL(false, deque.push_back(3));

	TEST_ASSERT_EQUAL(1, deque[0]);
	TEST_ASSERT_EQUAL(2, deque[1]);
}

void test_DequeShouldPushToFront() {
    StaticDeque<int, 2> deque;

    TEST_ASSERT_EQUAL(true, deque.push_front(1));
    TEST_ASSERT_EQUAL(true, deque.push_front(2));
    TEST_ASSERT_EQUAL(false, deque.push_front(3));

	TEST_ASSERT_EQUAL(2, deque[0]);
	TEST_ASSERT_EQUAL(1, deque[1]);
}

void test_DequeShouldPopBack() {
	StaticDeque<int, 2> deque;

	deque.push_back(1, 2);

	TEST_ASSERT_EQUAL(2, deque.pop_back());
	TEST_ASSERT_EQUAL(1, deque.pop_back());
}

void test_DequeShouldPopFront() {
	StaticDeque<int, 2> deque;

	deque.push_back(1, 2);

	TEST_ASSERT_EQUAL(1, deque.pop_front());
	TEST_ASSERT_EQUAL(2, deque.pop_front());
}

void test_DequeShouldReportSize() {
	StaticDeque<int, 2> deque;

	TEST_ASSERT_EQUAL(2, deque.capacity());
	TEST_ASSERT_EQUAL(0, deque.size());

	deque.push_back(1);
	TEST_ASSERT_EQUAL(1, deque.size());
	deque.push_back(2);
	TEST_ASSERT_EQUAL(2, deque.size());

	deque.pop_back();
	TEST_ASSERT_EQUAL(1, deque.size());
	deque.pop_front();
	TEST_ASSERT_EQUAL(0, deque.size());
}

void test_DequeShouldWriteDataContinuously() {
	StaticDeque<int, 2> deque;

	TEST_ASSERT_EQUAL(true, deque.push_back(1));
	TEST_ASSERT_EQUAL(true, deque.push_back(2));
	TEST_ASSERT_EQUAL(false, deque.push_back(3));

	TEST_ASSERT_EQUAL(1, deque.pop_front());
	TEST_ASSERT_EQUAL(2, deque.pop_front());

	TEST_ASSERT_EQUAL(true, deque.push_front(3));
	TEST_ASSERT_EQUAL(true, deque.push_front(4));
	TEST_ASSERT_EQUAL(false, deque.push_front(5));

	TEST_ASSERT_EQUAL(4, deque.pop_back());
	TEST_ASSERT_EQUAL(3, deque.pop_back());
}

void test_DequeShouldIterate() {
	StaticDeque<int, 3> deque;

	deque.push_back(0, 1, 2);

	Deque<int>::iterator it;
	uint8_t i;

	// Forward
	i = 0;
	for (it = deque.begin(); it != deque.end(); ++it) {
		TEST_ASSERT_EQUAL(i++, *it);
	}

	// Backward
	i = 2;
	for (it = deque.end(); it != deque.begin(); --it) {
		TEST_ASSERT_EQUAL(i--, *it);
	}
}

void testDeque() {
	RUN_TEST(test_DequeShouldPushToBack);
	RUN_TEST(test_DequeShouldPushToFront);
	RUN_TEST(test_DequeShouldPopBack);
	RUN_TEST(test_DequeShouldPopFront);
	RUN_TEST(test_DequeShouldReportSize);
	RUN_TEST(test_DequeShouldWriteDataContinuously);
	RUN_TEST(test_DequeShouldIterate);
}
