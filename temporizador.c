#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LED_PIN_RED 11
#define LED_PIN_YELLOW 12
#define LED_PIN_GREEN 13

// Variável de estado para controlar qual LED está aceso
static int led_state = 0;

bool repeating_timer_callback(struct repeating_timer *t){
    
    gpio_put(LED_PIN_RED, 0);
    gpio_put(LED_PIN_YELLOW, 0);
    gpio_put(LED_PIN_GREEN, 0);

    // Alterna o estado do LED
    switch (led_state) {
        case 0:
            gpio_put(LED_PIN_RED, 1);  // Liga o LED1
            break;
        case 1:
            gpio_put(LED_PIN_YELLOW, 1);  // Liga o LED2
            break;
        case 2:
            gpio_put(LED_PIN_GREEN, 1);  // Liga o LED3
            break;
    }

    led_state = (led_state + 1) % 3;

    // Atualiza o estado para o próximo LED
    return true;
}

int main(){
    // Inicializa os leds
    gpio_init(LED_PIN_YELLOW);
    gpio_set_dir(LED_PIN_YELLOW, GPIO_OUT);
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);

    stdio_init_all();
    
    struct repeating_timer timer;

    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    while (true) {
        printf("1 segundo passou \n");
        sleep_ms(1000);
    }
}