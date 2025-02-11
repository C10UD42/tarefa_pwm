#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define servo 12 //pino do servomotor conectado a GPIO como PWM

//rotina principal
int main()
{
    stdio_init_all(); //inicializa o sistema padrão de I/O

    gpio_set_function(servo, GPIO_FUNC_PWM); //habilitar o pino GPIO como PWM

    uint slice = pwm_gpio_to_slice_num(servo); //obter o canal PWM da GPIO

    pwm_set_clkdiv(slice, 125.0); //define o divisor de clock do PWM para 125, para obter a frequência correta

    pwm_set_wrap(slice, 19999); //define o valor de wrap para a frequência de 50 Hz (aproximadamente 20ms)

    pwm_set_gpio_level(servo, 2400); //definir o ciclo de trabalho (duty cycle) de 2400 µs

    pwm_set_enabled(slice, true); //habilita o pwm no slice correspondente

    sleep_ms(5000);

    pwm_set_gpio_level(servo, 1470); //definir o ciclo de trabalho (duty cycle) de 1470 µs

    sleep_ms(5000);

    pwm_set_gpio_level(servo, 500); //definir o ciclo de trabalho (duty cycle) de 500 µs

    sleep_ms(5000);

    //loop principal
    while (true) {
        // Movimentação suave entre 0° e 180° com incrementos de ±5µs a cada 10ms
        for (int level = 500; level <= 2400; level += 5) { // incremento de 5µs
            pwm_set_gpio_level(servo, level);
            sleep_ms(10); // atraso de 10ms
        }

        // Movimentação suave entre 180° e 0° com incrementos de ±5µs a cada 10ms
        for (int level = 2400; level >= 500; level -= 5) { // decremento de 5µs
            pwm_set_gpio_level(servo, level);
            sleep_ms(10); // atraso de 10ms
        }
    }
}
