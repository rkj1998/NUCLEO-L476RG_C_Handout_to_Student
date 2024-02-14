#include "stm32l476xx.h"
#include "SysClock.h"

// PA.5  <--> Green LED
// PC.13 <--> Blue user button
#define LED_PIN    5

void configure_LED_pin(){
	// Enable the clock to GPIO Port A
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

	// Set GPIO Mode, using the defined macro LED_PIN
	GPIOA->MODER &= ~(3U << (2 * LED_PIN)); // Clear bits
	GPIOA->MODER |= (1U << (2 * LED_PIN));  // Set as output mode (01)

	// Set GPIO Speed to Low speed (00)
	GPIOA->OSPEEDR &= ~(3U << (2 * LED_PIN));

	// Set GPIO Output Type to Push-Pull
	GPIOA->OTYPER &= ~(1U << LED_PIN); // 0 for push-pull

	// Set GPIO Push-Pull: No pull-up, pull-down (00)
	GPIOA->PUPDR &= ~(3U << (2 * LED_PIN));

	// Finally, set the output of the GPIO pin to have a value of 1 (corresponding to 3.3V)
	GPIOA->ODR |= (1U << LED_PIN);
}

void turn_on_LED(){
	// Set the corresponding output pin of GPIO port A to turn on the LED
	GPIOA->BSRR = (1U << LED_PIN); // Set bit to turn on the LED
}

void toggle_LED(){
	// Toggle the state of the LED
	GPIOA->ODR ^= (1U << LED_PIN); // XOR to toggle the state
}

void delay(int milliseconds) {
    int i, j;
    for (i = 0; i < milliseconds; i++)
        for (j = 0; j < 8000; j++); // Adjust this delay based on your system clock frequency
}

int main(void){
	System_Clock_Init(); // Switch System Clock = 80 MHz

	// Configure the LED pin
	configure_LED_pin();

	while(1){
		// Toggle the LED state
		toggle_LED();

		// Add delay between consecutive toggling (e.g., 500 ms)
		delay(500);

		// Optionally, you can add more functionality here
	}
}
