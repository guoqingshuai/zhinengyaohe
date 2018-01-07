#ifndef _HAL_STEP_OTOR_H
#define _HAL_STEP_OTOR_H

#include <stdio.h>
#include <stm32f10x.h>

#define GPIO_A1_CLK    RCC_APB2Periph_GPIOA//B∏ƒ≥…A
#define GPIO_A1_PORT   GPIOA
#define GPIO_A1_PIN    GPIO_Pin_12

#define GPIO_B1_CLK    RCC_APB2Periph_GPIOA
#define GPIO_B1_PORT   GPIOA
#define GPIO_B1_PIN    GPIO_Pin_11

#define GPIO_C1_CLK    RCC_APB2Periph_GPIOB
#define GPIO_C1_PORT   GPIOB
#define GPIO_C1_PIN    GPIO_Pin_15

#define GPIO_D1_CLK    RCC_APB2Periph_GPIOB
#define GPIO_D1_PORT   GPIOB
#define GPIO_D1_PIN    GPIO_Pin_14

#define GPIO_A2_CLK    RCC_APB2Periph_GPIOB
#define GPIO_A2_PORT   GPIOB
#define GPIO_A2_PIN    GPIO_Pin_10

#define GPIO_B2_CLK    RCC_APB2Periph_GPIOB
#define GPIO_B2_PORT   GPIOB
#define GPIO_B2_PIN    GPIO_Pin_11

#define GPIO_C2_CLK    RCC_APB2Periph_GPIOB
#define GPIO_C2_PORT   GPIOB
#define GPIO_C2_PIN    GPIO_Pin_12

#define GPIO_D2_CLK    RCC_APB2Periph_GPIOB
#define GPIO_D2_PORT   GPIOB
#define GPIO_D2_PIN    GPIO_Pin_13

//œ¬√Ê «…˘“Ù“˝Ω≈
#define GPIO_WT588DA_CLK    RCC_APB2Periph_GPIOB
#define GPIO_WT588DA_PORT   GPIOB
#define GPIO_WT588DA_PIN    GPIO_Pin_0

#define GPIO_WT588BY_CLK    RCC_APB2Periph_GPIOB
#define GPIO_WT588BY_PORT   GPIOB
#define GPIO_WT588BY_PIN    GPIO_Pin_1

//#define GPIO_BEIYONG1_CLK    RCC_APB2Periph_GPIOB
//#define GPIO_BEIYONG1_PORT   GPIOB
//#define GPIO_BEIYONG1_PIN    GPIO_Pin_7






#define Coil_A1 {GPIO_SetBits(GPIO_A1_PORT,GPIO_A1_PIN);\
								GPIO_ResetBits(GPIO_B1_PORT,GPIO_B1_PIN);\
								GPIO_ResetBits(GPIO_C1_PORT,GPIO_C1_PIN);\
								GPIO_ResetBits(GPIO_D1_PORT,GPIO_D1_PIN);\
							}//Aœ‡Õ®µÁ£¨∆‰À˚œ‡∂œµÁ
#define Coil_B1 {GPIO_ResetBits(GPIO_A1_PORT,GPIO_A1_PIN);\
								GPIO_SetBits(GPIO_B1_PORT,GPIO_B1_PIN);\
								GPIO_ResetBits(GPIO_C1_PORT,GPIO_C1_PIN);\
								GPIO_ResetBits(GPIO_D1_PORT,GPIO_D1_PIN);\
								}//Bœ‡Õ®µÁ£¨∆‰À˚œ‡∂œµÁ
#define Coil_C1 {GPIO_ResetBits(GPIO_A1_PORT,GPIO_A1_PIN);\
								GPIO_ResetBits(GPIO_B1_PORT,GPIO_B1_PIN);\
								GPIO_SetBits(GPIO_C1_PORT,GPIO_C1_PIN);\
								GPIO_ResetBits(GPIO_D1_PORT,GPIO_D1_PIN);\
								}//Cœ‡Õ®µÁ£¨∆‰À˚œ‡∂œµÁ
#define Coil_D1 {GPIO_ResetBits(GPIO_A1_PORT,GPIO_A1_PIN);\
								GPIO_ResetBits(GPIO_B1_PORT,GPIO_B1_PIN);\
								GPIO_ResetBits(GPIO_C1_PORT,GPIO_C1_PIN);\
								GPIO_SetBits(GPIO_D1_PORT,GPIO_D1_PIN);\
								}//Dœ‡Õ®µÁ£¨∆‰À˚œ‡∂œµÁ
#define Coil_AB1 {GPIO_SetBits(GPIO_A1_PORT,GPIO_A1_PIN);\
								GPIO_SetBits(GPIO_B1_PORT,GPIO_B1_PIN);\
								GPIO_ResetBits(GPIO_C1_PORT,GPIO_C1_PIN);\
								GPIO_ResetBits(GPIO_D1_PORT,GPIO_D1_PIN);\
								}//ABœ‡Õ®µÁ£¨∆‰À˚œ‡∂œµÁ
#define Coil_BC1 {GPIO_ResetBits(GPIO_A1_PORT,GPIO_A1_PIN);\
								GPIO_SetBits(GPIO_B1_PORT,GPIO_B1_PIN);\
								GPIO_SetBits(GPIO_C1_PORT,GPIO_C1_PIN);\
								GPIO_ResetBits(GPIO_D1_PORT,GPIO_D1_PIN);\
								}//BCœ‡Õ®µÁ£¨∆‰À˚œ‡∂œµÁ
							
#define Coil_CD1 {GPIO_ResetBits(GPIO_A1_PORT,GPIO_A1_PIN);\
								GPIO_ResetBits(GPIO_B1_PORT,GPIO_B1_PIN);\
								GPIO_SetBits(GPIO_C1_PORT,GPIO_C1_PIN);\
								GPIO_SetBits(GPIO_D1_PORT,GPIO_D1_PIN);\
								}//CDœ‡Õ®µÁ£¨∆‰À˚œ‡∂œµÁ
#define Coil_DA1 {GPIO_SetBits(GPIO_A1_PORT,GPIO_A1_PIN);\
	              GPIO_ResetBits(GPIO_B1_PORT,GPIO_B1_PIN);\
								GPIO_ResetBits(GPIO_C1_PORT,GPIO_C1_PIN);\
								GPIO_SetBits(GPIO_D1_PORT,GPIO_D1_PIN);\
}
								//Dœ‡Õ®µÁ£¨∆‰À˚œ‡∂œµÁ
#define Coil_OFF {GPIO_ResetBits(GPIO_A1_PORT,GPIO_A1_PIN);\
									GPIO_ResetBits(GPIO_B1_PORT,GPIO_B1_PIN);\
									GPIO_ResetBits(GPIO_C1_PORT,GPIO_C1_PIN);\
					 				GPIO_ResetBits(GPIO_D1_PORT,GPIO_D1_PIN);\
									}//»´≤ø∂œµÁ

#define Coil_A2 {GPIO_SetBits(GPIO_A2_PORT,GPIO_A2_PIN);\
								GPIO_ResetBits(GPIO_B2_PORT,GPIO_B2_PIN);\
								GPIO_ResetBits(GPIO_C2_PORT,GPIO_C2_PIN);\
								GPIO_ResetBits(GPIO_D2_PORT,GPIO_D2_PIN);\
							}//Aœ‡Õ®µÁ£¨∆‰À˚œ‡∂œµÁ
#define Coil_B2 {GPIO_ResetBits(GPIO_A2_PORT,GPIO_A2_PIN);\
								GPIO_SetBits(GPIO_B2_PORT,GPIO_B2_PIN);\
								GPIO_ResetBits(GPIO_C2_PORT,GPIO_C2_PIN);\
								GPIO_ResetBits(GPIO_D2_PORT,GPIO_D2_PIN);\
								}//Bœ‡Õ®µÁ£¨∆‰À˚œ‡∂œµÁ
#define Coil_C2 {GPIO_ResetBits(GPIO_A2_PORT,GPIO_A2_PIN);\
								GPIO_ResetBits(GPIO_B2_PORT,GPIO_B2_PIN);\
								GPIO_SetBits(GPIO_C2_PORT,GPIO_C2_PIN);\
								GPIO_ResetBits(GPIO_D2_PORT,GPIO_D2_PIN);\
								}//Cœ‡Õ®µÁ£¨∆‰À˚œ‡∂œµÁ
#define Coil_D2 {GPIO_ResetBits(GPIO_A2_PORT,GPIO_A2_PIN);\
								GPIO_ResetBits(GPIO_B2_PORT,GPIO_B2_PIN);\
								GPIO_ResetBits(GPIO_C2_PORT,GPIO_C2_PIN);\
								GPIO_SetBits(GPIO_D2_PORT,GPIO_D2_PIN);\
								}//Dœ‡Õ®µÁ£¨∆‰À˚œ‡∂œµÁ
#define Coil_AB2 {GPIO_SetBits(GPIO_A2_PORT,GPIO_A2_PIN);\
								GPIO_SetBits(GPIO_B2_PORT,GPIO_B2_PIN);\
								GPIO_ResetBits(GPIO_C2_PORT,GPIO_C2_PIN);\
								GPIO_ResetBits(GPIO_D2_PORT,GPIO_D2_PIN);\
								}//ABœ‡Õ®µÁ£¨∆‰À˚œ‡∂œµÁ
#define Coil_BC2 {GPIO_ResetBits(GPIO_A2_PORT,GPIO_A2_PIN);\
								GPIO_SetBits(GPIO_B2_PORT,GPIO_B2_PIN);\
								GPIO_SetBits(GPIO_C2_PORT,GPIO_C2_PIN);\
								GPIO_ResetBits(GPIO_D2_PORT,GPIO_D2_PIN);\
								}//BCœ‡Õ®µÁ£¨∆‰À˚œ‡∂œµÁ
							
#define Coil_CD2 {GPIO_ResetBits(GPIO_A2_PORT,GPIO_A2_PIN);\
								GPIO_ResetBits(GPIO_B2_PORT,GPIO_B2_PIN);\
								GPIO_SetBits(GPIO_C2_PORT,GPIO_C2_PIN);\
								GPIO_SetBits(GPIO_D2_PORT,GPIO_D2_PIN);\
								}//CDœ‡Õ®µÁ£¨∆‰À˚œ‡∂œµÁ
#define Coil_DA2 {GPIO_SetBits(GPIO_A2_PORT,GPIO_A2_PIN);\
	              GPIO_ResetBits(GPIO_B2_PORT,GPIO_B2_PIN);\
								GPIO_ResetBits(GPIO_C2_PORT,GPIO_C2_PIN);\
								GPIO_SetBits(GPIO_D2_PORT,GPIO_D2_PIN);\
}
								//Dœ‡Õ®µÁ£¨∆‰À˚œ‡∂œµÁ
#define Coil_OFF2 {GPIO_ResetBits(GPIO_A2_PORT,GPIO_A2_PIN);\
									GPIO_ResetBits(GPIO_B2_PORT,GPIO_B2_PIN);\
									GPIO_ResetBits(GPIO_C2_PORT,GPIO_C2_PIN);\
					 				GPIO_ResetBits(GPIO_D2_PORT,GPIO_D2_PIN);\
									}//»´≤ø∂œµÁ



void STEP_GPIO_Init(void);							//≥ı ºªØ“˝Ω

void Send_oneline(unsigned char addr);
#endif /*_HAL_STEP_OTOR_H*/
