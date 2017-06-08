#include <stdio.h>
#include <unicore-mx/stm32/rcc.h>
#include <unicore-mx/stm32/gpio.h>

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

int main(void)
{
        int j,i = 0;

        clock_setup();
        gpio_mode_setup(GPIOI, GPIO_MODE_OUTPUT,GPIO_PUPD_NONE, GPIO15);

        for(;;)
        {
                for (int j = 0; j < 1000000; j++);
                printf("Hello, world! -- %i\n", i++);
                gpio_toggle(GPIOI,GPIO15);
        }
        return 0;
}
