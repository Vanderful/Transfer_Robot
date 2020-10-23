//#include "common.h"
//#include "My_Math.h"
//#include "Parameter.h"
//#include "LPC546XX_uart.h"
//#include "Lab1349_TFmini_Plus.h"
//#include "ANO_TC_CP.h"
//#include "Car_Ctrl.h"
#include "Lab1349_Ops9.h"
//#include "LPC546XX_systick.h"
//#include "LPC546XX_gpio.h"

Ops_Struct Ops9;



void Ops9_uart_init()
{
    uart_init(Ops9_COF_UART,115200,Ops9_COF_TX,Ops9_COF_RX);
    uart_rx_irq(Ops9_COF_UART,1); 
}

//void Ops9_Command(char data)////X(X�����޸�),Y(Y�����޸�),D(X��Y�����޸�),J(�Ƕ��޸�),A(ȫ���޸�)
//{
//   Correction_X = - Correction_X;
//   switch(data)
//   {
//   case 'X':
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,0x41);       // A
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,0x43);       // C
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,0x54);       // T
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,0x58);       // X
//     
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,BYTE0(Correction_X));       
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,BYTE1(Correction_X));       
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,BYTE2(Correction_X));       
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,BYTE3(Correction_X));  
//     break;
//     ///////////////////////////////////////////////////////////////////////////////////
//   case 'Y':
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,0x41);       // A
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,0x43);       // C
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,0x54);       // T
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,0x59);       // Y
//     
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,BYTE0(Correction_Y));       
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,BYTE1(Correction_Y));       
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,BYTE2(Correction_Y));       
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,BYTE3(Correction_Y));  
//     break;
//     ///////////////////////////////////////////////////////////////////////////////////
//   case 'D':
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,0x41);       // A
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,0x43);       // C
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,0x54);       // T
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,0X44);       // D
//     
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,BYTE0(Correction_X));       
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,BYTE1(Correction_X));       
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,BYTE2(Correction_X));       
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,BYTE3(Correction_X));  
//     
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,BYTE0(Correction_Y));       
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,BYTE1(Correction_Y));       
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,BYTE2(Correction_Y));       
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,BYTE3(Correction_Y));
//     break;
//     ///////////////////////////////////////////////////////////////////////////////////
//   case 'J':
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,0x41);       // A
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,0x43);       // C
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,0x54);       // T
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,0X4A);       // J
//     
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,BYTE0(Correction_W));       
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,BYTE1(Correction_W));       
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,BYTE2(Correction_W));       
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,BYTE3(Correction_W));  
//     break;
//     ///////////////////////////////////////////////////////////////////////////////////
//   case 'A':
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,0x41);       // A
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,0x43);       // C
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,0x54);       // T
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,0x41);       // A
//     
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,BYTE0(Correction_W));       
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,BYTE1(Correction_W));       
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,BYTE2(Correction_W));       
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,BYTE3(Correction_W));       
//     
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,BYTE0(Correction_X));       
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,BYTE1(Correction_X));       
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,BYTE2(Correction_X));       
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,BYTE3(Correction_X));       
//     
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,BYTE0(Correction_Y));       
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,BYTE1(Correction_Y));       
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,BYTE2(Correction_Y));       
//     systick_delay_ms(1);   uart_putchar(Ops9_COF_UART,BYTE3(Correction_Y)); 
//     break;
//   }
//}

void Ops9_uart_interrupt()
{
    static union
    {
        uint8 data[24];
        float ActVal[6];
    }posture;
    
    uart_query(Ops9_COF_UART,&Ops9.Ops9_rec[Ops9.Ops9_recnum]);
//    uart_getchar(Ops9_COF_UART,&Ops9.Ops9_rec[Ops9.Ops9_recnum]);
    
    if(Ops9.Ops9_rec[0] != 0x0D)                           Ops9.Ops9_recnum = 0;
        
    else if(Ops9.Ops9_recnum == 1 && Ops9.Ops9_rec[1] != 0x0A)   Ops9.Ops9_recnum = 0;
       
    else if(Ops9.Ops9_recnum == 27) 
    {
        Ops9.Ops9_recnum = 0;  
        
        if((Ops9.Ops9_rec[26] == 0X0A)&&(Ops9.Ops9_rec[27] == 0X0D))
        {  
                for(uint8 i=0;i<24;i++)
                {
                    posture.data[i]= Ops9.Ops9_rec[i+2];  
                }
                
                Ops9.Angle_Z=posture.ActVal[0];
                Ops9.Angle_X=posture.ActVal[1];
                Ops9.Angle_Y=posture.ActVal[2];
                Ops9.Pos_X=-posture.ActVal[3];
                Ops9.Pos_Y=posture.ActVal[4];
                Ops9.Palstance_Z=posture.ActVal[5] / 0.01745f;
                
//                tfmini_X.distance= Ops9.Pos_X/10.0f;
//                tfmini_Y.distance= Ops9.Pos_Y/10.0f;
                
                Ops9.receiveComplete = 1;
                gpio_set(A8,0);
        }
    } 
    else 
    {  
        Ops9.Ops9_recnum++;    
        if(Ops9.Ops9_recnum == 28)   Ops9.Ops9_recnum = 0; 
    }
}

void FLEXCOMM0_DriverIRQHandler(void)
{
    vuint32 flag;
    flag = UART0_FIFO_FLAG;   
    if(flag & USART_FIFOINTSTAT_RXLVL_MASK)//����FIFO�ﵽ�趨ˮƽ����Ĭ���趨ˮƽ ������FIFO��һ�����ݵ�ʱ�򴥷��жϣ�
    {
        Ops9_uart_interrupt();//uart_query(USART_2,&ddf[fg]);��ȡ����
    }
    
    if(flag & USART_FIFOINTSTAT_TXLVL_MASK)//����FIFO�ﵽ�趨ˮƽ����Ĭ���趨ˮƽ ������FIFOΪ�յ�ʱ�򴥷��жϣ�
    {
        
    }
    
    if(flag & USART_FIFOINTSTAT_RXERR_MASK)//����FIFO����
    {
        USART0->FIFOSTAT |= USART_FIFOSTAT_RXERR_MASK;
        USART0->FIFOCFG  |= USART_FIFOCFG_EMPTYRX_MASK;//���RX FIFO
    }
}