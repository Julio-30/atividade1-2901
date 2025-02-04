#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

// Defina os pinos dos LEDs
#define Led_vermelho 11
#define Led_amarelo 12
#define Led_verde 13

// Variável para controlar o estado do semáforo
typedef enum {
    Vermelho,
    Amarelo,
    Verde
} Semaforo;

Semaforo Estado = Vermelho;

// Função de callback do temporizador
bool repeating_timer_callback(struct repeating_timer *t) {
    // Desliga todos os LEDs
    gpio_put(Led_vermelho, 0);
    gpio_put(Led_amarelo, 0);
    gpio_put(Led_verde, 0);

    // Muda o estado do semáforo
    switch (Estado) {
        case Vermelho:
            gpio_put(Led_vermelho, 1);
            Estado = Amarelo;
            break;
        case Amarelo:
            gpio_put(Led_amarelo, 1);
            Estado = Verde;
            break;
        case Verde:
            gpio_put(Led_verde, 1);
            Estado = Vermelho;
            break;
    }

    return true; // Continua o temporizador
}

int main() {
    // Inicializa a comunicação serial
    stdio_init_all();

    // Configura os pinos dos LEDs como saída
    gpio_init(Led_vermelho);
    gpio_init(Led_amarelo);
    gpio_init(Led_verde);
    gpio_set_dir(Led_vermelho, GPIO_OUT);
    gpio_set_dir(Led_amarelo, GPIO_OUT);
    gpio_set_dir(Led_verde, GPIO_OUT);

    // Inicializa o LED vermelho
    gpio_put(Led_vermelho, 1);

    // Configura o temporizador para 3 segundos
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Loop principal
    while (true) {
        printf("Semáforo funcionando\n");
        sleep_ms(1000); // Espera 1 segundo
    }

    return 0;
}
