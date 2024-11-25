#include "test.h"
#include <unity.h>

int main() {
	UNITY_BEGIN();
	testDeque();
	testRingBuffer();
	testVector();
	return UNITY_END();
}
