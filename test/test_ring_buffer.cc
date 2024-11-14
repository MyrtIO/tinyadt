#include <unity.h>
#include <TinyADT/RingBuffer.h>

void test_RingBufferShouldWrite() {
    RingBuffer<2> buffer;
    TEST_ASSERT_EQUAL(1, buffer.write(1));
    TEST_ASSERT_EQUAL(1, buffer.write(2));
    TEST_ASSERT_EQUAL(0, buffer.write(3));
}

void test_RingBufferShouldRead() {
    RingBuffer<2> buffer;
    buffer.write(1);
    buffer.write(2);
    TEST_ASSERT_EQUAL(1, buffer.read());
    TEST_ASSERT_EQUAL(2, buffer.read());
}

void test_RingBufferShouldReadAndWriteSequentially() {
    RingBuffer<2> buffer;
    buffer.write(1);
    buffer.write(2);
    TEST_ASSERT_EQUAL(1, buffer.read());
    TEST_ASSERT_EQUAL(2, buffer.read());
    TEST_ASSERT_EQUAL(-1, buffer.read());
    buffer.write(3);
    TEST_ASSERT_EQUAL(3, buffer.read());
}

void test_RingBufferShouldReportAvailable() {
    RingBuffer<2> buffer;
    TEST_ASSERT_EQUAL(0, buffer.available());
    buffer.write(1);
    TEST_ASSERT_EQUAL(1, buffer.available());
    buffer.write(2);
    TEST_ASSERT_EQUAL(2, buffer.available());
    buffer.read();
    TEST_ASSERT_EQUAL(1, buffer.available());
    buffer.read();
    TEST_ASSERT_EQUAL(0, buffer.available());
}

void test_RingBufferShouldReportAvailableForWrite() {
    RingBuffer<2> buffer;
    TEST_ASSERT_EQUAL(2, buffer.availableForWrite());
    buffer.write(1);
    TEST_ASSERT_EQUAL(1, buffer.availableForWrite());
    buffer.write(2);
    TEST_ASSERT_EQUAL(0, buffer.availableForWrite());
}

void testRingBuffer() {
  RUN_TEST(test_RingBufferShouldWrite);
  RUN_TEST(test_RingBufferShouldRead);
  RUN_TEST(test_RingBufferShouldReadAndWriteSequentially);
  RUN_TEST(test_RingBufferShouldReportAvailable);
  RUN_TEST(test_RingBufferShouldReportAvailableForWrite);
}
