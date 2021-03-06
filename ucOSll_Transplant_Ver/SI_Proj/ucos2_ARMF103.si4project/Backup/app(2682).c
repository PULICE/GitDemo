/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                           Copyright 2003-2006; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
目前只移植基本功能：
1.通过串口1能看到打印信息：串口波特率57600
2.使用串口调试助手接收STM32发送的信息

编译器版本：MDK3.5
硬件平台：HC6800-EM3--->
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

//#include <includes.h>
#include "..\APP\includes.h"
#include "config.h"
#define LED_LOCK 	   {    \
											 GPIOD->ODR |=(1<<2);\
											 GPIOD->ODR &=~(1<<2);\
										 }                                

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/



/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/
//浠诲姟鏍堟暟缁勫畾涔�
static  OS_STK App_TaskStartStk[APP_TASK_START_STK_SIZE];
static  OS_STK App_TaskUser1Stk[APP_TASK_User1_STK_SIZE];
static  OS_STK App_TaskUser2Stk[APP_TASK_User2_STK_SIZE];


//static  OS_EVENT* InfoSem;                      
//static  OS_EVENT* Disp_Box;                  
//static  char* dp;
/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/
//static  void App_TaskCreate(void);
static  void App_DispScr_SignOn(void);

static  void App_TaskStart(void* p_arg);
static  void App_TaskUsre1(void* p_arg);
static  void App_TaskUsre2(void* p_arg);


//static  void App_TaskLCD(void* p_arg);
//static  void App_TaskKbd(void* p_arg);
//static  void App_TaskJoystick(void* p_arg);

/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Argument : none.
*
* Return   : none.
*********************************************************************************************************
*/

int main(void)
{
   CPU_INT08U os_err;

   //BSP_IntDisAll();                                            /* Disable all ints until we are ready to accept them.  */
   CPU_IntDis();
   
   OSInit();                                                   /* Initialize "uC/OS-II, The Real-Time Kernel".         */

   BSP_Init();                                                 /* Initialize BSP functions.  */
   
   
   App_DispScr_SignOn();

	 GPIOC->ODR = 0X0FFF;
//	 LED_LOCK;
   printf("OS Init OK！\r\n");
   os_err = OSTaskCreate((void (*) (void *)) App_TaskStart,
               /* Create the start task.                               */
                          (void *) 0,
               (OS_STK *) &App_TaskStartStk[APP_TASK_START_STK_SIZE - 1],
               (INT8U) APP_TASK_START_PRIO);
   printf("Creat App_TaskStart！\r\n");
#if (OS_TASK_NAME_SIZE >= 11)
   OSTaskNameSet(APP_TASK_START_PRIO, (CPU_INT08U *) "Start Task", &os_err);
#endif

/*---------------------------------------------------------------------------*/
//   InfoSem = OSSemCreate(0); 
//   Disp_Box = OSMboxCreate((void *) 0);               
   OSTimeSet(0);
//   printf("before osstart\r\n");
   OSStart();                                                  /* Start multitasking (i.e. give control to uC/OS-II).  */

   return (0);
}

/*
*********************************************************************************************************
*                                          App_TaskStart()
*
* Description : The startup task.  The uC/OS-II ticker should only be initialize once multitasking starts.
*
* Argument : p_arg       Argument passed to 'App_TaskStart()' by 'OSTaskCreate()'.
*
* Return   : none.
*
* Caller   : This is a task.
*
* Note     : none.
*********************************************************************************************************
*/

static  void App_TaskStart(void* p_arg)
{
//   CPU_INT32U i;
//   CPU_INT32U j;
   //CPU_INT32U dly;
	CPU_INT08U os_err;


   (void) p_arg;
//绗竴锛岃皟鏁磗ystick,濡傛灉ucos浣跨敤鑰呮兂瑕佽皟鏁磘ick鍛ㄦ湡锛屽氨鍦ㄨ繖閲岃皟鏁村嵆鍙紝铏界劧鏃╁湪姹囩紪灏卞凡瀹炵幇锛屼絾骞朵笉
//濡ㄧ鍦ㄨ繖閲屽仛鍑鸿皟鏁淬��
   OS_CPU_SysTickInit();                                       /* Initialize the SysTick.       */
//绗簩锛屽垵濮嬪寲缁熻浠诲姟鐨勫叏灞�鍙橀噺
#if (OS_TASK_STAT_EN > 0)
   OSStatInit();                                               /* Determine CPU capacity.                              */
#endif

//绗笁锛屽垱寤哄叾浠栫殑浠诲姟
   //App_TaskCreate();
   /*---------------------------------鑷繁鍒涘缓鐨勪换鍔�----------------------------*/
	  os_err = OSTaskCreate((void (*) (void *)) App_TaskUsre1,
				  /* Create the start task. 							  */
							 (void *) 0,
				  (OS_STK *) &App_TaskUser1Stk[APP_TASK_User1_STK_SIZE - 1],
				  (INT8U) APP_TASK_User1_PRIO);
	  printf("Creat App_TaskUsre1\r\n");
#if (OS_TASK_NAME_SIZE >= 11)
	  OSTaskNameSet(APP_TASK_User1_PRIO, (CPU_INT08U *) "Start User1", &os_err);
#endif

    /*---------------------------------鑷繁鍒涘缓鐨勪换鍔�----------------------------*/
	  os_err = OSTaskCreate((void (*) (void *)) App_TaskUsre2,
				  /* Create the start task. 							  */
							 (void *) 0,
				  (OS_STK *) &App_TaskUser2Stk[APP_TASK_User2_STK_SIZE - 1],
				  (INT8U) APP_TASK_User2_PRIO);
	  printf("Creat App_TaskUsre2\r\n");
#if (OS_TASK_NAME_SIZE >= 11)
	  OSTaskNameSet(APP_TASK_User2_PRIO, (CPU_INT08U *) "Start User2", &os_err);
#endif
//涔熷氨鏄鍦ˋpp_TaskStart鍑芥暟涓彧鍋氬垱寤轰换鍔★紝涓�鑸笉绗﹁�呭儚涓嬫枃绫讳技鐨勬敞閲婇儴鍒嗗叿浣撲换鍔″疄鐜�
/*
   while (DEF_TRUE)
   {
      LED_1_ON();
      OSTimeDlyHMSM(0, 0, 0, 300);
      
      LED_1_OFF();
      OSTimeDlyHMSM(0, 0, 0, 300);
	  //App_DispScr_SignOn();
	  printf("App_Taskstart\r\n");
   }
   */
}

//寤虹珛鑷繁鐨勪换鍔�
static  void App_TaskUsre1(void* p_arg)
{
     printf("App_TaskUsre1\r\n");
   while (1)
   {
      LED_1_ON();
      OSTimeDlyHMSM(0, 0, 0, 300);
    
      LED_1_OFF();
      OSTimeDlyHMSM(0, 0, 0, 300);
	  printf("App_Taskstart1\r\n");
   }
}

//寤虹珛鑷繁鐨勪换鍔�
static  void App_TaskUsre2(void* p_arg)
{
     printf("App_TaskUsre1\r\n");
   while (1)
   {
      LED_2_ON();
      OSTimeDlyHMSM(0, 0, 0, 100);
    
      LED_2_OFF();
      OSTimeDlyHMSM(0, 0, 0, 100);
	  printf("App_Taskstart2\r\n");
   }
}


/*
*********************************************************************************************************
*                                            App_TaskCreate()
*
* Description : Create the application tasks.
*
* Argument : none.
*
* Return   : none.
*
* Caller   : App_TaskStart().
*
* Note     : none.
*********************************************************************************************************
*/

//static  void App_TaskCreate(void)
//{
//   CPU_INT08U os_err;

//   os_err = OSTaskCreate((void (*) (void *)) App_TaskLCD, (void *) 0,
//               (OS_STK *) &App_TaskLCDStk[APP_TASK_LCD_STK_SIZE - 1],
//               (INT8U) APP_TASK_LCD_PRIO);
//   printf("Creat App_TaskLCD！\r\n");
//#if (OS_TASK_NAME_SIZE >= 9)
//   OSTaskNameSet(APP_TASK_LCD_PRIO, "LCD", &os_err);
//#endif

//   os_err = OSTaskCreate((void (*) (void *)) App_TaskKbd, (void *) 0,
//               (OS_STK *) &App_TaskKbdStk[APP_TASK_KBD_STK_SIZE - 1],
//               (INT8U) APP_TASK_KBD_PRIO);
//   printf("Creat App_TaskKbd！\r\n");
//#if (OS_TASK_NAME_SIZE >= 9)
//   OSTaskNameSet(APP_TASK_KBD_PRIO, "KeyBoard", &os_err);
//#endif

//   os_err = OSTaskCreate((void (*) (void *))
//               App_TaskJoystick, (void *)
//               0,
//               (OS_STK *) &App_TaskJoystickStk[APP_TASK_Joystick_STK_SIZE - 1],
//               (INT8U)
//               APP_TASK_Joystick_PRIO);
//   printf("Creat App_TaskJoystick！\r\n");
//#if (OS_TASK_NAME_SIZE >= 9)
//   OSTaskNameSet(APP_TASK_Joystick_PRIO, "Joystick", &os_err);
//#endif
//}




/*
*********************************************************************************************************
*                                          App_DispScr_SignOn()
*
* Description : Display uC/OS-II system information on the USART.
*
* Argument: none.
*
* Return   : none.
*
* Caller   : App_TaskKbd().
*
* Note    : none.
*********************************************************************************************************
*/

static void App_DispScr_SignOn(void)
{
   printf("\r\n  Micrium uC/OS-II  \r\n");
   printf("  ST STM32 (Cortex-M3)\r\n\r\n");

   printf("  uC/OS-II:  V%ld.%ld%ld\r\n",(long) OSVersion() / 100,
      (long)(OSVersion() % 100) / 10, (long)(OSVersion() % 10));
   printf("  TickRate: %ld  \r\n", (long)OS_TICKS_PER_SEC);
   printf("  CPU Usage: %ld% \r\n",(long)OSCPUUsage);
   printf("  CPU Speed:%ld MHz  \r\n", BSP_CPU_ClkFreq() / 1000000L);
   printf("  #Ticks: %ld  \r\n", (long)OSTime);
   printf("  #CtxSw: %ld  \r\n\r\n", (long)OSCtxSwCtr);
}

























/*
*********************************************************************************************************
*********************************************************************************************************
*                                          uC/OS-II APP HOOKS
*********************************************************************************************************
*********************************************************************************************************
*/

#if (OS_APP_HOOKS_EN > 0)
/*
*********************************************************************************************************
*                                      TASK CREATION HOOK (APPLICATION)
*
* Description : This function is called when a task is created.
*
* Argument : ptcb   is a pointer to the task control block of the task being created.
*
* Note     : (1) Interrupts are disabled during this call.
*********************************************************************************************************
*/

void App_TaskCreateHook(OS_TCB* ptcb)
{
}

/*
*********************************************************************************************************
*                                    TASK DELETION HOOK (APPLICATION)
*
* Description : This function is called when a task is deleted.
*
* Argument : ptcb   is a pointer to the task control block of the task being deleted.
*
* Note     : (1) Interrupts are disabled during this call.
*********************************************************************************************************
*/

void App_TaskDelHook(OS_TCB* ptcb)
{
   (void) ptcb;
}

/*
*********************************************************************************************************
*                                      IDLE TASK HOOK (APPLICATION)
*
* Description : This function is called by OSTaskIdleHook(), which is called by the idle task.  This hook
*               has been added to allow you to do such things as STOP the CPU to conserve power.
*
* Argument : none.
*
* Note     : (1) Interrupts are enabled during this call.
*********************************************************************************************************
*/

#if OS_VERSION >= 251
void App_TaskIdleHook(void)
{
}
#endif

/*
*********************************************************************************************************
*                                        STATISTIC TASK HOOK (APPLICATION)
*
* Description : This function is called by OSTaskStatHook(), which is called every second by uC/OS-II's
*               statistics task.  This allows your application to add functionality to the statistics task.
*
* Argument : none.
*********************************************************************************************************
*/

void App_TaskStatHook(void)
{
}

/*
*********************************************************************************************************
*                                        TASK SWITCH HOOK (APPLICATION)
*
* Description : This function is called when a task switch is performed.  This allows you to perform other
*               operations during a context switch.
*
* Argument : none.
*
* Note     : 1 Interrupts are disabled during this call.
*
*            2  It is assumed that the global pointer 'OSTCBHighRdy' points to the TCB of the task that
*                   will be 'switched in' (i.e. the highest priority task) and, 'OSTCBCur' points to the
*                  task being switched out (i.e. the preempted task).
*********************************************************************************************************
*/

#if OS_TASK_SW_HOOK_EN > 0
void App_TaskSwHook(void)
{
}
#endif

/*
*********************************************************************************************************
*                                     OS_TCBInit() HOOK (APPLICATION)
*
* Description : This function is called by OSTCBInitHook(), which is called by OS_TCBInit() after setting
*               up most of the TCB.
*
* Argument : ptcb    is a pointer to the TCB of the task being created.
*
* Note     : (1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/

#if OS_VERSION >= 204
void App_TCBInitHook(OS_TCB* ptcb)
{
   (void) ptcb;
}
#endif

#endif
