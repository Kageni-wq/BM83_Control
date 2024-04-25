#ifndef BT_HARDWARE_PROFILE_H
#define BT_HARDWARE_PROFILE_H

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include "main.h"

//build option for code included - MBA Support
#define _BLE_ADV_CTRL_BY_MCU
#define _CODE_FOR_APP

//#define _UNSUPPORT_3A_EVENT     //3A event is used to return link mode, it is supported by MSPK but not support by 104 ROM
//#define _SUPPORT_SIMPLE_33_EVENT //33 event is to report multi speaker status. For MSPK, it return connected status with peer address. But for 104 ROM, there is no address, so need to define this macro

//define command size, command buffer size for command in and out
#define     UR_TX_BUF_SIZE              500         //maximum buffer size for command sending
#define     UR_RX_BUF_SIZE              500         //maximum buffer size for command receiving
#define     BT_CMD_SIZE_MAX				200         //maximum size for a single command
#define     QUEQUED_CMD_MAX                 30      //maximum number of command in buffer to be sending 
#define     QUEQUED_ACK_MAX                 30      //maximum number of ack command in buffer to be sending
#define     ACK_TIME_OUT_MS                 800     //number of ms to be waiting for ack
#define     INTERVAL_AFTER_CMD_ACK_NG          10   //interval(ms) before re-transmit this command in case of no ack and ack with error
#define     INTERVAL_AFTER_CMD_ACK_OK          10   //interval(ms) before send next command

//BM6X BT configuration
#define BM6X_MFB_SetHigh()      HAL_GPI0_WritePin(GPIOB, GPIO_PIN_8, GPIO_SET_PIN_HIGH)
#define BM6X_MFB_SetLow()       HAL_GPI0_WritePin(GPIOB, GPIO_PIN_8, GPIO_SET_PIN_LOW)

#define BM6X_RESET_SetHigh()    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_SET_PIN_HIGH)
#define BM6X_RESET_SetLow()     HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_SET_PIN_LOW)

//LINE_IN_D PD3
//P3_7 PD4
#ifdef BM83_EVB_VERSION_1_0
#define BT_P3_7_STATUS_GET()      (PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_1))

#define LINE_IN_DETECT_STATUS_GET()   (PLIB_PORTS_PinGet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_0))
#else
#define BT_P3_7_STATUS_GET()      HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_4)

#define LINE_IN_DETECT_STATUS_GET()   HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_3)
#endif

//P2_0 PD7
#define BT_P2_0_SetOutput()         //PLIB_PORTS_PinDirectionOutputSet( PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_1)
#define BT_P2_0_SetHigh()           //PLIB_PORTS_PinSet( PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_1)
#define BT_P2_0_SetLow()            //PLIB_PORTS_PinClear( PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_1)

//EAN PD5
#define BT_EAN_SetOutput()          //PLIB_PORTS_PinDirectionOutputSet( PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_3)
#define BT_EAN_SetHigh()            //PLIB_PORTS_PinSet( PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_3)
#define BT_EAN_SetLow()             //PLIB_PORTS_PinClear( PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_3)

//P2_4 PD6
#define BT_P2_4_SetOutput()         //PLIB_PORTS_PinDirectionOutputSet( PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_2)
#define BT_P2_4_SetHigh()           //PLIB_PORTS_PinSet( PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_2)
#define BT_P2_4_SetLow()            //PLIB_PORTS_PinClear( PORTS_ID_0, PORT_CHANNEL_C, PORTS_BIT_POS_2)

// UART RX
#define UART_RX_SetInput()         HAL_GPIO_WritePin(GPIOF, GPIO_PIN_4, GPIO_PIN_RESET); \
                                    GPIO_InitStruct.Pin = GPIO_PIN_4; \
                                    GPIO_InitStruct.Mode = GPIO_MODE_INPUT; \
                                    GPIO_InitStruct.Pull = GPIO_NOPULL; \
                                    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct)

// UART TX
#define UART_UR_TX_SetInput()      HAL_GPIO_WritePin(GPIOF, GPIO_PIN_5, GPIO_PIN_RESET); \
                                    GPIO_InitStruct.Pin = GPIO_PIN_5; \
                                    GPIO_InitStruct.Mode = GPIO_MODE_INPUT; \
                                    GPIO_InitStruct.Pull = GPIO_NOPULL; \
                                    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct)
//LED configuration
#define LED0_ON()       HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_SET_PIN_HIGH)
#define LED0_OFF()      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_SET_PIN_LOW)
#define LED0_TOGGLE()   HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6)
#define LED0_STATUS_GET()   HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)

#define LED1_ON()       HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_SET_PIN_HIGH)
#define LED1_OFF()      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_SET_PIN_LOW)
#define LED1_TOGGLE()      HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_7)
#define LED1_STATUS_GET()   HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7)

//P0_0 PB7
#define BT_P0_0_STATUS_GET()      HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7)

//P2_7 PD2
#define BT_P2_7_STATUS_GET()      HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2)

#define BT_UART_RX_BYTE_MODEL
#define BT_UART_TX_BYTE_MODEL

#ifdef BT_UART_RX_BYTE_MODEL
#define BT_UART_RX_ISR      BT_CommandDecode_AddByteToBuffer
#endif

#ifdef BT_UART_TX_BYTE_MODEL
void HM_UART_WriteOneByte(uint8_t byte);
#define BT_UART_TX_ISR      BT_CommandSend_SendByte
#define UART_WriteOneByte   HM_UART_WriteOneByte
#endif

void bt_issueUartTransfer( void );
void bt_disableUartTransferIntr( void );
void bt_temporaryDisableUartTransferIntr( void );
void bt_restoreUartTransferIntr( void );

#endif