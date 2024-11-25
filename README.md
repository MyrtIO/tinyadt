# TinyADT [![Quality Assurance](https://github.com/MyrtIO/tinyadt/actions/workflows/qa.yaml/badge.svg)](https://github.com/MyrtIO/tinyadt/actions/workflows/qa.yaml)

Advanced data types for micro-controllers. The primary objective is to enhance the ease of data management, while addressing the limitations of micro-controllers. The library aims for an interface similar to stdlib.

## Types

- [`Deque`](https://github.com/MyrtIO/tinyadt/blob/main/src/TinyADT/deque.h) — a double ended queue.
- [`Vector`](https://github.com/MyrtIO/tinyadt/blob/main/src/TinyADT/vector.h) — a dynamic array with static capacity.
- [`RingBuffer`](https://github.com/MyrtIO/tinyadt/blob/main/src/TinyADT/ring_buffer.h) — a ring buffer compatible with Arduino's [`Stream`](https://docs.arduino.cc/language-reference/en/functions/communication/stream/) interface.

## Iterators

In list types, methods for getting iterators (such as `begin()` and `end()`) are available.

The use of iterators is similar to what you are used to:

```cpp
template <typename T>
int indexOfDequeItem(const T& item, const Deque<T>& list) {
	for (auto it = list.begin(); it != list.end(); it++) {
		if (*it == item) {
			return it - list.begin();
		}
	}
	return -1;
}
