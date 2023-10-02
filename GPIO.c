/**
 * Include required libraries
 * Define some macros
 * Implement some functions
 * ... etc.
 **/

#include <stdio.h>
#include "sdkconfig.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define BUILTIN_LED 2
#define BUTTON 16
#define TIMER_CYCLE 50

void aSimpleTask(void *pvParameter)
{
    gpio_set_direction(BUILTIN_LED, GPIO_MODE_OUTPUT);
    uint8_t counter = 20;
    uint8_t ledCurrentState = 0;

    while (1)
    {
        if (counter == 0)
        {
            counter = 20;
            printf("2014156\n");
            if (ledCurrentState == 0)
            {
                // /* Blink on (output high) */
                gpio_set_level(BUILTIN_LED, 1);
                ledCurrentState = 1;
            }
            else
            {
                // /* Blink off (output low) */
                gpio_set_level(BUILTIN_LED, 0);
                ledCurrentState = 0;
            }
        }

        vTaskDelay(TIMER_CYCLE / portTICK_PERIOD_MS);
        counter--;
    }
}

void anotherSimpleTask(void *pvParameter)
{

    gpio_set_direction(BUTTON, GPIO_MODE_INPUT);
    uint8_t currentState = 0;
    uint8_t readingSignal = 0;
    uint8_t counter = 0;
    uint8_t debounce_count = 1;

    while (1)
    {
        readingSignal = gpio_get_level(BUTTON);

        if (readingSignal == currentState && counter > 0)
        {
            counter--;
        }
        if (readingSignal != currentState)
        {
            counter++;
        }

        if (counter >= debounce_count)
        {
            counter = 0;
            currentState = readingSignal;
            if (currentState == 0)
            {
                printf("ESP32\n");
            }
        }

        vTaskDelay(TIMER_CYCLE / portTICK_PERIOD_MS);
    }
}

// entry function
void app_main(void)
{
    // this is the entry point of the program
    // your code goes here
    xTaskCreate(&aSimpleTask, "aSimpleTask", 2048, NULL, 5, NULL);
    xTaskCreate(&anotherSimpleTask, "anotherSimpleTask", 2048, NULL, 5, NULL);
}

