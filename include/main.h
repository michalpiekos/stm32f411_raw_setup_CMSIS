/**
 * @file main.h
 * @author Michal Piekos (michal.public@wp.pl)
 * @brief Header file for drilling down BlackPill
 * @version 0.1
 * @date 2023-05-07
 * 
 * MIT License. Copyright (c) 2023.
 * 
 */

/*****************************************************************
 * Includes
******************************************************************/

#include <stdint.h>
#include <stm32f4xx.h>
#include <system_stm32f4xx.h>

/*****************************************************************/


/*****************************************************************
 * Function declarations
******************************************************************/

static inline void system_clock_init(void);
static inline void timer3_init(void);
static inline void gpioc13_init(void);
static inline void delay_us(uint16_t us);
static inline void delay_ms(uint16_t ms);

/*****************************************************************/