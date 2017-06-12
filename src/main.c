#include <stdio.h>
#include <unicore-mx/stm32/rcc.h>
#include <unicore-mx/stm32/gpio.h>
#include <unicore-mx/cm3/nvic.h>

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <timers.h>
#include <semphr.h>

#define SytemCLK 216000000 //Hz

uint32_t SystemCoreClock = SytemCLK;

static void clock_setup(void)
{
	/* Base board frequency, set to 216MHz */
	rcc_clock_setup_hse_3v3(&rcc_hse_25mhz_3v3);

	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOB);
	rcc_periph_clock_enable(RCC_GPIOC);
	rcc_periph_clock_enable(RCC_GPIOH);
	rcc_periph_clock_enable(RCC_GPIOI);
	rcc_periph_clock_enable(RCC_GPIOJ);
	rcc_periph_clock_enable(RCC_USART6);
	rcc_periph_clock_enable(RCC_OTGHS);
	rcc_periph_clock_enable(RCC_OTGHSULPI);
	rcc_periph_clock_enable(RCC_TIM6);
}

static void green_led_task(void *params)
{
        int j,i = 0;

        for(;;)
        {
                for (int j = 0; j < 100000; j++);
                printf("green! -- %i\n", i++);
                gpio_toggle(GPIOI,GPIO15);
		taskYIELD();
        }
}

static void orange_led_task(void *params)
{
        int j,i = 0;

        for(;;)
        {
                for (int j = 0; j < 1000000; j++);
                //printf("orange! -- %i\n", i++);
                gpio_toggle(GPIOJ,GPIO1);
        }
}

int main(void)
{

        clock_setup();

#define IRQ2NVIC_PRIOR(x)	((x)<<4)
        nvic_set_priority(NVIC_SYSTICK_IRQ, IRQ2NVIC_PRIOR(1));

        gpio_mode_setup(GPIOI, GPIO_MODE_OUTPUT,GPIO_PUPD_NONE, GPIO15);
        gpio_mode_setup(GPIOJ, GPIO_MODE_OUTPUT,GPIO_PUPD_NONE, GPIO1);

        xTaskCreate(green_led_task,"green",configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY + 1, NULL);
        xTaskCreate(orange_led_task,"orange",configMINIMAL_STACK_SIZE,NULL,tskIDLE_PRIORITY + 1, NULL);

        vTaskStartScheduler();

        while(1) {
		//
	}

        return 0;
}
