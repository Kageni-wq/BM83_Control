#include "bt_hardware_profile.h"
#include "main.c"
#include "stm32f4xx_hal_uart.h"
#include <stdbool.h>
#include <stdint.h>


bool UartTxIntrStatus;

void bt_issueUartTransfer( void )
{
   __HAL_UART_ENABLE_IT(&huart1, UART_IT_TXE);
    UartTxIntrStatus = true;
}

/*void bt_enableUartTransferIntr( void )
{
    SYS_INT_SourceEnable(INT_SOURCE_USART_1_TRANSMIT);
    UartTxIntrStatus = true;
    
}*/

void bt_disableUartTransferIntr( void )
{
    __HAL_UART_DISABLE_IT(&huart1, UART_IT_TXE);
    UartTxIntrStatus = false;
}

void bt_temporaryDisableUartTransferIntr( void )
{
    __HAL_UART_DISABLE_IT(&huart1, UART_IT_TXE);
}

void bt_restoreUartTransferIntr( void )
{
    if(UartTxIntrStatus)
        __HAL_UART_ENABLE_IT(&huart1, UART_IT_TXE);
}

// Define UART handle
UART_HandleTypeDef huart1;

//Function to write one byte over UART
void HM_UART_WriteOneByte(uint8_t byte) {
    //Transmit the bute usuing HAL_UART_Transmit
    HAL_UART_Transmit_IT(&huart1, &byte, 1, HAL_MAX_DELAY);
}