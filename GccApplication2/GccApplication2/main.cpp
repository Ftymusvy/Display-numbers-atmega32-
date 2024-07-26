#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 8000000UL  // Assuming an 8MHz clock frequency, adjust as needed

void displayNumber(uint8_t num) {
	// Assuming common cathode seven-segment display
	uint8_t seg[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
	PORTC = seg[num];
}

void displayAllSegments() {
	PORTC = 0xFF;  // Display all segments (0xFF)
	_delay_ms(1000);
}

void turnOffSegmentsOneByOne() {
	for (int i = 0; i < 8; i++) {
		PORTC &= ~(1 << i);
		_delay_ms(1000);
	}
}

int main() {
	DDRA &= ~(1 << PA0);  // Set PA0 as input
	DDRC = 0xFF;          // Set PORTC as output

	uint8_t a = 0;

	// Display zero initially
	displayNumber(a);

	while (1) {
		if (!(PINA & (1 << PA0))) { // Check if the button is pressed (low level)
			// Increment the number and wrap around if needed
			a = a + 1;
			if (a > 9) {
				a = 0;
				displayAllSegments();  // Display all segments when the number is 9
				turnOffSegmentsOneByOne();  // Turn off segments one by one after one second
			}

			// Display the updated number
			displayNumber(a);

			// Wait for a short time to avoid multiple increments
			_delay_ms(200);

			// Wait until the button is released to avoid multiple increments
			while (!(PINA & (1 << PA0))) {
				_delay_ms(50);
			}
		}
	}

	return 0;
}
