#include "main.h"
 

//Quick hack, approximately 1ms delay
void ms_delay(int ms)
{
   while (ms-- > 0) {
      volatile int x=5971;
      while (x-- > 0)
         __asm("nop");
   }
}

void ButtonPressed_action(void)
{
    STM_EVAL_LEDOn(LED_Red);
}

void ButtonReleased_action(void) { // nothing to do }

int main(void)
{
    // Enable clock to GPIOD
    /*RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;  */

    // Set pin 13 to be general purpose output
    GPIOD->MODER = (1 << 26);             

    // Initialize LEDs
    STM_EVAL_LEDInit(LED_Green);
    STM_EVAL_LEDInit(LED_Orange);
    STM_EVAL_LEDInit(LED_Red);
    STM_EVAL_LEDInit(LED_Blue);

    // Initialize buttons
    STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);

    //Set up a timer for ms interrupts
    set_sys_tick();

    // Get ready to make sound
    synth_init();
    audio_init();


    for (;;) {
       ms_delay(500);
       GPIOD->ODR ^= (1 << 13);           // Toggle the pin 
    }
}
