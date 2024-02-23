#include <stdint.h>

//PERIPHERAL & BUS BASE ADDRESS
#define PERIPHERAL_BASE_ADDRESS  0x40000000U
#define AHB_BASE_ADDRESS         (PERIPHERAL_BASE_ADDRESS + 0x00020000U)

//RCC BASE ADDRESS
#define RCC_BASE_ADDRESS         (AHB_BASE_ADDRESS + 0x00001000U)
#define RCC_IOPENR_ADDRESS       (RCC_BASE_ADDRESS + 0x0000002CU)

//IOPORT BASE ADDRESS
#define IOPORT_ADDRESS           (PERIPHERAL_BASE_ADDRESS + 0x10000000U)
//GPIO BASE & SPECIFIC ADDRESS
#define GPIOA_BASE_ADDRESS       (IOPORT_ADDRESS + 0x00000000U)
#define GPIOA_MODER_REG          (GPIOA_BASE_ADDRESS + 0x00000000U)
#define GPIOA_ODR_REG            (GPIOA_BASE_ADDRESS + 0x00000014U)

#define GPIOC_BASE_ADDRESS       (IOPORT_ADDRESS + 0X00000800U)
#define GPIOC_MODER_REG          (GPIOC_BASE_ADDRESS + 0X00000000U)
#define GPIOC_ODR_REG            (GPIOC_BASE_ADDRESS + 0X00000014U)
#define GPIOC_IDR_REG            (GPIOC_BASE_ADDRESS + 0X00000010U)
#define GPIOC_PUPD_REG           (GPIOC_BASE_ADDRESS + 0X0000000CU)
#define BIT13                    (1<<13)

void delay_ms(uint16_t n);

int main(void)
{
  uint32_t *ptr_rcc_iopenr   =   RCC_IOPENR_ADDRESS; //POINTER VARIABLE TO RCC, IOPENR REGISTER
  uint32_t *ptr_gpioa_moder  =   GPIOA_MODER_REG;    //POINTER VARIABLE TO GPIOA, MODERR REGISTER
  uint32_t *ptr_gpioa_odr    =   GPIOA_ODR_REG;      //POINTER VARIABLE TO GPIOA, ODR REGISTER

  uint32_t *ptr_gpioc_moder  =   GPIOC_MODER_REG;      //POINTER VARIABLE TO GPIOC, MODER REGISTER
  uint32_t *ptr_gpioc_odr    =   GPIOC_ODR_REG;        //POINTER VARIABLE TO GPIOC, ODR   REGISTER
  uint32_t *ptr_gpioc_idr    =   GPIOC_IDR_REG;        //
  uint32_t *ptr_gpioc_pupd   =   GPIOC_PUPD_REG;       //
  uint8_t contador = 0;
  //ENABLE CLK
      //GPIOA
  *ptr_rcc_iopenr  |= 1<<0;
      //GPIOC
  *ptr_rcc_iopenr  |= 1<<2;

  //GPIOA
     //PA5
  *ptr_gpioa_moder &= ~(1<<11);

  //GPIOC
     //PC13 as input
  *ptr_gpioc_moder &= ~(1<<26);
  *ptr_gpioc_moder &= ~(1<<27);
     //PC0 as input
  *ptr_gpioc_moder &= ~(1<<0);
  *ptr_gpioc_moder &= ~(1<<1);

  //PUPD
     //PC0 PU
  *ptr_gpioc_pupd |= 1<<0; //pullldown

while(1)
{
		if(*ptr_gpioc_idr == 0x01){ //detectar boton presionado
			*ptr_gpioa_odr &= ~(1<<5);
			//delay_ms(200);
			*ptr_gpioa_odr  |= 1<<5;
			//delay_ms(200);
		}else if(*ptr_gpioc_idr == 0x2001){ //nada esta presionado
		*ptr_gpioa_odr &= ~(1<<5);
		//delay_ms(500);
		*ptr_gpioa_odr  |= 1<<5;
		//delay_ms(500);
		}else if(*ptr_gpioc_idr == 0x2000){// pc0 presionado
		 contador++;
		 //delay_ms(15);
		}
		//*ptr_gpioa_odr &= ~(1<<5);
		 //delay_ms(200);
		//*ptr_gpioa_odr  |= 1<<5;
		 //delay_ms(200);
  }
}

void delay_ms(uint16_t n){
	uint16_t i;
	for(; n>0; n--)
		for(i=0; i<140; i++);
}
