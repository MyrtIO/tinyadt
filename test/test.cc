#include "test.h"
#include <unity.h>

int main() {
	UNITY_BEGIN();
	testVector();
	testRingBuffer();
	return UNITY_END();
}
