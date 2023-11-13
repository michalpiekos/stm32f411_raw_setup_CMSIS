#include "main.h"


int main(void)
{    
  system_clock_init();
  timer3_init();
  gpioc13_init();

  while (1) {
      GPIOC->BSRR |= GPIO_BSRR_BS13;      // * (volatile uint32_t *) (0x40020800 + 0x18) |= (1 << 13);
      delay_ms(250);
      GPIOC->BSRR |= GPIO_BSRR_BR13;      // * (volatile uint32_t *) (0x40020800 + 0x18) |= (1 << (13 + 16));
      delay_ms(250);
  }
}


/**
 * @brief Classic delay function by miliseconds
 * 
 * @param ms miliseconds
 */
static inline void delay_ms(uint16_t ms)
{
  for (uint16_t i=0; i<ms; i++) {
    delay_us(1000);
  }
}

/**
 * @brief Classic delay funtion by microseconds
 * 
 * @param us microseconds
 */
static inline void delay_us(uint16_t us)
{
  TIM3->CNT = 0;                                          // Reset timer
  while (TIM3->CNT < us) ;                                // Blocking wait for value
}


/**
 * @brief Initialize GPIOC Pin 13 to output
 * 
 */
static inline void gpioc13_init(void)
{
  SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN);
  CLEAR_BIT(GPIOC->MODER, GPIO_MODER_MODER13);
  SET_BIT(GPIOC->MODER, GPIO_MODER_MODER13_0);            // General output mode
  CLEAR_BIT(GPIOC->OTYPER, GPIO_OTYPER_OT13);             // Set output type to push pull
  SET_BIT(GPIOC->OSPEEDR, GPIO_OSPEEDR_OSPEED13_1);       // Set Fast Speed
  GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPD13);                   // no pull up nor pull down
}


/**
 * @brief Initialize timer 3
 * 
 */
static inline void timer3_init(void)
{
  SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM3EN);    // Enable timer 3 clock
  TIM3->PSC = 95;                               // Prescaler to set timer to 1MHz
  TIM3->ARR = 0xFFFF;                           // Max autoreload value
  SET_BIT(TIM3->CR1, TIM_CR1_CEN);              // Enable timer 3
  while (!(TIM3->SR & TIM_SR_UIF)) ;            // Wait for the flag
}

/**
 * @brief System initialization covering system clock and flash
 * 
 */
static inline void system_clock_init(void)
{
  SET_BIT(RCC->CR, RCC_CR_HSEON);               // Enable HSE
  while(!(RCC->CR & RCC_CR_HSERDY)) ;           // Wait for HSE Ready
  SET_BIT(RCC->APB1ENR, RCC_APB1ENR_PWREN);     // Power enable
  SET_BIT(PWR->CR, PWR_CR_VOS);                 // Voltage regulator
  MODIFY_REG(FLASH->ACR, 
              FLASH_ACR_DCEN | FLASH_ACR_ICEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY,
              FLASH_ACR_DCEN | FLASH_ACR_ICEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_3WS);
  MODIFY_REG(RCC->CFGR,
              RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2,
              RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV2 | RCC_CFGR_PPRE2_DIV1);
  MODIFY_REG(RCC->PLLCFGR,
              RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN | RCC_PLLCFGR_PLLP | RCC_PLLCFGR_PLLQ | RCC_PLLCFGR_PLLSRC,
              (25U << RCC_PLLCFGR_PLLM_Pos) | (192U << RCC_PLLCFGR_PLLN_Pos) | (0U << RCC_PLLCFGR_PLLP_Pos) | (4U << RCC_PLLCFGR_PLLQ_Pos) | RCC_PLLCFGR_PLLSRC_HSE);
  SET_BIT(RCC->CR, RCC_CR_PLLON);               // Enable PLL
  while(!(RCC->CR & RCC_CR_PLLRDY)) ;           // Wait for PLL Ready
  MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL);
  while(!(RCC->CFGR & RCC_CFGR_SWS_PLL)) ;
  SystemCoreClockUpdate();
}