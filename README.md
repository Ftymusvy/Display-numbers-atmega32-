# شمارنده نمایشگر سون سگمنت با ATmega32

این پروژه یک شمارنده دیجیتالی ساده با استفاده از میکروکنترلر ATmega32 و نمایشگر سون سگمنت را نشان می‌دهد. شمارنده اعداد 0 تا 9 را نمایش می‌دهد و هر بار با فشار دکمه، عدد افزایش می‌یابد. پس از رسیدن به عدد 9، شمارنده به 0 بازنشانی می‌شود.

## توضیحات مدار

مدار شامل اجزای زیر است:

- **میکروکنترلر ATmega32:** وظیفه کنترل نمایشگر سون سگمنت را دارد و سیگنال‌های لازم برای روشن کردن بخش‌های درست جهت نمایش هر عدد را ارسال می‌کند.

- **نمایشگر سون سگمنت:** یک نمایشگر کاتد مشترک است که برای نمایش اعداد 0 تا 9 استفاده می‌شود.

- **مقاومت‌ها (10kΩ):** به عنوان مقاومت‌های کششی (Pull-up) برای تضمین سیگنال‌های ورودی پایدار از دکمه به کار می‌روند.

- **خازن (10µF):** برای پایدارسازی و فیلتر کردن توان استفاده می‌شود.

- **دکمه فشاری:** برای افزایش شمارش استفاده می‌شود. هر بار فشار، سیگنالی به میکروکنترلر ارسال می‌کند تا عدد نمایش داده شده افزایش یابد.

## نقشه مدار

نقشه مدار به صورت زیر است:

![نقشه مدار](https://github.com/Ftymusvy/Display-numbers-atmega32-/blob/main/Screenshot%202024-07-26%20180738.png)

## توضیح کد

برنامه به زبان C نوشته شده و از AVR-GCC برای کامپایل و بارگذاری بر روی میکروکنترلر ATmega32 استفاده می‌کند. ویژگی‌های اصلی کد شامل موارد زیر است:

- **راه‌اندازی اولیه:** پورت‌های I/O متصل به نمایشگر سون سگمنت را به عنوان خروجی تنظیم می‌کند و ورودی دکمه را با مقاومت کششی (Pull-up) پیکربندی می‌کند.

- **حلقه اصلی:** به صورت مداوم بررسی می‌کند که آیا دکمه فشار داده شده است. در هر بار فشار، شمارنده افزایش می‌یابد و مقدار جدید روی نمایشگر سون سگمنت نمایش داده می‌شود. اگر شمارنده بیش از 9 شد، به 0 بازنشانی می‌شود.

## نمونه کد

```c

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
			}	}
	}

	return 0;}
            
            // نمایش عدد
            PORTC = segment_map[number];
        }
    }
    return 0;
}
