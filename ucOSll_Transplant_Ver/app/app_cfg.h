/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2003-2006; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                      APPLICATION CONFIGURATION
*
*                                     ST Microelectronics STM32
*                                              with the
*                                   STM3210B-LK1 Evaluation Board
*
* Filename      : app_cfg.h
* Version       : V1.10
* Programmer(s) : BH3NVN
*********************************************************************************************************
*/

#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__

/*
*********************************************************************************************************
*                                       MODULE ENABLE / DISABLE
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                              TASKS NAMES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/
//任务优先级定义处
#define  APP_TASK_START_PRIO                               2
#define  APP_TASK_User1_PRIO                               3
#define  APP_TASK_User2_PRIO                               4
#define  APP_TASK_User3_PRIO                               5
#define  APP_TASK_User4_PRIO                               6
#define  APP_TASK_User5_PRIO                               7
#define  APP_TASK_User6_PRIO                               8
#define  APP_TASK_User7_PRIO                               9
#define  APP_TASK_User8_PRIO                               10









//#define  APP_TASK_LCD_PRIO                                 5
//#define  APP_TASK_KBD_PRIO                                 4
//#define  APP_TASK_Joystick_PRIO                            3




/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*                             Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/
//任务栈大小
#define  APP_TASK_START_STK_SIZE                         128
#define  APP_TASK_User1_STK_SIZE                         128
#define  APP_TASK_User2_STK_SIZE                         128
#define  APP_TASK_User3_STK_SIZE                         128
#define  APP_TASK_User4_STK_SIZE                         128
#define  APP_TASK_User5_STK_SIZE                         128
#define  APP_TASK_User6_STK_SIZE                         128
#define  APP_TASK_User7_STK_SIZE                         128
#define  APP_TASK_User8_STK_SIZE                         128







/*
*********************************************************************************************************
*                                                  LIB
*********************************************************************************************************
*/

#define  uC_CFG_OPTIMIZE_ASM_EN                 DEF_ENABLED
#define  LIB_STR_CFG_FP_EN                      DEF_DISABLED

#endif