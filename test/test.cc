#include "test.h"
#include <unity.h>

int main() {
	UNITY_BEGIN();
	testDeque();
	testRingBuffer();
	return UNITY_END();
}
