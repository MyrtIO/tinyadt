.PHONY: test-uno
test-uno:
	pio test -e uno --without-uploading

.PHONY: test-native
test-native:
	pio test -e native

.PHONY: test
test:
	make test-native
	make test-uno
