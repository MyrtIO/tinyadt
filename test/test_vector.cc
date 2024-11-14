#include <unity.h>
#include <TinyADT/Vector.h>

void testShouldCreateEmptyVector() {
    Vector<int> vec;
    TEST_ASSERT_EQUAL(0, vec.size());
}

void testShouldResizeManually() {
	Vector<int> vec;
	vec.reserve(10);
	TEST_ASSERT_EQUAL(0, vec.size());
	TEST_ASSERT_EQUAL(10, vec.capacity());
}

void testShouldResizeAutomatically() {
	Vector<int> vec;
	for (int i = 0; i < 10; i++) {
		vec.insert(i+1);
	}
	TEST_ASSERT_EQUAL(10, vec.size());
	TEST_ASSERT_GREATER_OR_EQUAL(10, vec.capacity());
	for (int i = 0; i < 290; i++) {
		vec.insert(i+1);
	}
	TEST_ASSERT_EQUAL(300, vec.size());
	TEST_ASSERT_GREATER_OR_EQUAL(300, vec.capacity());
}

void testShouldProvideAccessToElements() {
	Vector<int> vec;
	for (int i = 0; i < 10; i++) {
		vec.insert(i+1);
	}
	for (int i = 0; i < 10; i++) {
		TEST_ASSERT_EQUAL(i+1, vec[i]);
	}
}

void testVector() {
	RUN_TEST(testShouldCreateEmptyVector);
	RUN_TEST(testShouldResizeManually);
	RUN_TEST(testShouldResizeAutomatically);
	RUN_TEST(testShouldProvideAccessToElements);
}
