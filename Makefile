.PHONY: test-arduino
test-arduino:
	pio test -e uno --without-uploading

.PHONY: test-native
test-native:
	pio test -e native
