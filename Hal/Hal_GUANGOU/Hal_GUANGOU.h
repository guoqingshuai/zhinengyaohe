#define GPIO_G1_CLK    RCC_APB2Periph_GPIOA//����
#define GPIO_G1_PORT   GPIOA
#define GPIO_G1_PIN    GPIO_Pin_0

#define GPIO_G2_CLK    RCC_APB2Periph_GPIOA//����
#define GPIO_G2_PORT   GPIOA
#define GPIO_G2_PIN    GPIO_Pin_1


#define GPIO_Y1_CLK    RCC_APB2Periph_GPIOB//����
#define GPIO_Y1_PORT   GPIOB
#define GPIO_Y1_PIN    GPIO_Pin_5

#define GPIO_Y2_CLK    RCC_APB2Periph_GPIOB//����
#define GPIO_Y2_PORT   GPIOB
#define GPIO_Y2_PIN    GPIO_Pin_6
//���ð���  ����  ke2
#define GPIO_BEIYONG3_CLK    RCC_APB2Periph_GPIOC//������
#define GPIO_BEIYONG3_PORT   GPIOC
#define GPIO_BEIYONG3_PIN    GPIO_Pin_15

#define GPIO_BEIYONG4_CLK    RCC_APB2Periph_GPIOC//����4
#define GPIO_BEIYONG4_PORT   GPIOC
#define GPIO_BEIYONG4_PIN    GPIO_Pin_15



void STEP_GPIO_GInit(void);	
void STEP_GPIO_HUOER(void);
void EXTIX_Init(void);

