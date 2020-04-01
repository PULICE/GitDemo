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
*                                             INCLUDE FILES
*********************************************************************************************************
*/

//#include <includes.h>
#include "..\app\includes.h"
#include "config.h"
                              

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
//任务栈数组定义
static  OS_STK App_TaskStartStk[APP_TASK_START_STK_SIZE];
static  OS_STK App_TaskUser1Stk[APP_TASK_User1_STK_SIZE];
static  OS_STK App_TaskUser2Stk[APP_TASK_User2_STK_SIZE];
static  OS_STK App_TaskUser3Stk[APP_TASK_User2_STK_SIZE];
static  OS_STK App_TaskUser4Stk[APP_TASK_User2_STK_SIZE];
static  OS_STK App_TaskUser5Stk[APP_TASK_User2_STK_SIZE];
static  OS_STK App_TaskUser6Stk[APP_TASK_User2_STK_SIZE];
static  OS_STK App_TaskUser7Stk[APP_TASK_User2_STK_SIZE];
static  OS_STK App_TaskUser8Stk[APP_TASK_User2_STK_SIZE];








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
static  void App_TaskUsre3(void* p_arg);
static  void App_TaskUsre4(void* p_arg);
static  void App_TaskUsre5(void* p_arg);
static  void App_TaskUsre6(void* p_arg);
static  void App_TaskUsre7(void* p_arg);
static  void App_TaskUsre8(void* p_arg);

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
   CPU_IntDis();                                                    //关闭了总中断
   
   OSInit();                                                   /* Initialize "uC/OS-II, The Real-Time Kernel".         */

   BSP_Init();                                                 /* Initialize BSP functions.  */
//   GPIOC->ODR = 0XFFFF;
//	 LED_LOCK
   LCD_DisplayStringLine(Line5,(uint8_t *)"     test one      ");
   App_DispScr_SignOn();


   printf("OS Init OK\r\n");
   os_err = OSTaskCreate((void (*) (void *)) App_TaskStart, /* Create the start task. */(void *) 0,(OS_STK *) &App_TaskStartStk[APP_TASK_START_STK_SIZE - 1],(INT8U) APP_TASK_START_PRIO);
																							
   printf("Creat App_TaskStart\r\n");
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
	CPU_INT08U os_err;


   (void) p_arg;
//第一，调整systick,如果ucos使用者想要调整tick周期，就在这里调整即可，虽然早在汇编就已实现，但并不
//妨碍在这里做出调整。
   OS_CPU_SysTickInit();                                       /* Initialize the SysTick.       */
//第二，初始化统计任务的全局变量
#if (OS_TASK_STAT_EN > 0)
   OSStatInit();                                               /* Determine CPU capacity.                              */
#endif

//第三，创建其他的任务
   //App_TaskCreate();
   /*---------------------------------自己创建的任务1----------------------------*/
	  os_err = OSTaskCreate((void (*) (void *)) App_TaskUsre1,
				  /* Create the start task. 							  */
							 (void *) 0,
				  (OS_STK *) &App_TaskUser1Stk[APP_TASK_User1_STK_SIZE - 1],
				  (INT8U) APP_TASK_User1_PRIO);
	  printf("Creat App_TaskUsre1\r\n");
#if (OS_TASK_NAME_SIZE >= 11)
	  OSTaskNameSet(APP_TASK_User1_PRIO, (CPU_INT08U *) "Start User1", &os_err);
#endif

    /*---------------------------------自己创建的任务2----------------------------*/
	  os_err = OSTaskCreate((void (*) (void *)) App_TaskUsre2,
				  /* Create the start task. 							  */
							 (void *) 0,
				  (OS_STK *) &App_TaskUser2Stk[APP_TASK_User2_STK_SIZE - 1],
				  (INT8U) APP_TASK_User2_PRIO);
	  printf("Creat App_TaskUsre2\r\n");
#if (OS_TASK_NAME_SIZE >= 11)
	  OSTaskNameSet(APP_TASK_User2_PRIO, (CPU_INT08U *) "Start User2", &os_err);
#endif
    /*---------------------------------自己创建的任务3----------------------------*/
	  os_err = OSTaskCreate((void (*) (void *)) App_TaskUsre3,
				  /* Create the start task. 							  */
							 (void *) 0,
				  (OS_STK *) &App_TaskUser3Stk[APP_TASK_User3_STK_SIZE - 1],
				  (INT8U) APP_TASK_User3_PRIO);
	  printf("Creat App_TaskUsre3\r\n");
#if (OS_TASK_NAME_SIZE >= 11)
	  OSTaskNameSet(APP_TASK_User3_PRIO, (CPU_INT08U *) "Start User3", &os_err);
#endif
    /*---------------------------------自己创建的任务4----------------------------*/
	  os_err = OSTaskCreate((void (*) (void *)) App_TaskUsre4,
				  /* Create the start task. 							  */
							 (void *) 0,
				  (OS_STK *) &App_TaskUser4Stk[APP_TASK_User4_STK_SIZE - 1],
				  (INT8U) APP_TASK_User4_PRIO);
	  printf("Creat App_TaskUsre4\r\n");
#if (OS_TASK_NAME_SIZE >= 11)
	  OSTaskNameSet(APP_TASK_User4_PRIO, (CPU_INT08U *) "Start User4", &os_err);
#endif
    /*---------------------------------自己创建的任务5----------------------------*/
	  os_err = OSTaskCreate((void (*) (void *)) App_TaskUsre5,
				  /* Create the start task. 							  */
							 (void *) 0,
				  (OS_STK *) &App_TaskUser5Stk[APP_TASK_User5_STK_SIZE - 1],
				  (INT8U) APP_TASK_User5_PRIO);
	  printf("Creat App_TaskUsre5\r\n");
#if (OS_TASK_NAME_SIZE >= 11)
	  OSTaskNameSet(APP_TASK_User5_PRIO, (CPU_INT08U *) "Start User5", &os_err);
#endif
    /*---------------------------------自己创建的任务6----------------------------*/
	  os_err = OSTaskCreate((void (*) (void *)) App_TaskUsre6,
				  /* Create the start task. 							  */
							 (void *) 0,
				  (OS_STK *) &App_TaskUser6Stk[APP_TASK_User6_STK_SIZE - 1],
				  (INT8U) APP_TASK_User6_PRIO);
	  printf("Creat App_TaskUsre6\r\n");
#if (OS_TASK_NAME_SIZE >= 11)
	  OSTaskNameSet(APP_TASK_User6_PRIO, (CPU_INT08U *) "Start User6", &os_err);
#endif
    /*---------------------------------自己创建的任务7----------------------------*/
	  os_err = OSTaskCreate((void (*) (void *)) App_TaskUsre7,
				  /* Create the start task. 							  */
							 (void *) 0,
				  (OS_STK *) &App_TaskUser7Stk[APP_TASK_User7_STK_SIZE - 1],
				  (INT8U) APP_TASK_User7_PRIO);
	  printf("Creat App_TaskUsre7\r\n");
#if (OS_TASK_NAME_SIZE >= 11)
	  OSTaskNameSet(APP_TASK_User7_PRIO, (CPU_INT08U *) "Start User7", &os_err);
#endif
    /*---------------------------------自己创建的任务8----------------------------*/
	  os_err = OSTaskCreate((void (*) (void *)) App_TaskUsre8,
				  /* Create the start task. 							  */
							 (void *) 0,
				  (OS_STK *) &App_TaskUser8Stk[APP_TASK_User8_STK_SIZE - 1],
				  (INT8U) APP_TASK_User8_PRIO);
	  printf("Creat App_TaskUsre8\r\n");
#if (OS_TASK_NAME_SIZE >= 11)
	  OSTaskNameSet(APP_TASK_User8_PRIO, (CPU_INT08U *) "Start User8", &os_err);
#endif


//	while(1);  这样while（1）会导致无线死循环占用cpu,其他任务被搞死
	while(1)
		{
			OSTimeDlyHMSM(0, 0, 0, 300);
	    }
//也就是说在App_TaskStart函数中只做创建任务，一般不符者像下文类似的注释部分具体任务实现

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

//建立自己的任务
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

//建立自己的任务
static  void App_TaskUsre2(void* p_arg)
{
     printf("App_TaskUsre2\r\n");
   while (1)
   {
      LED_2_ON();
      OSTimeDlyHMSM(0, 0, 1, 0);
    
      LED_2_OFF();
      OSTimeDlyHMSM(0, 0, 1, 0);
	  printf("App_Taskstart2\r\n");
   }
}

//建立自己的任务
static  void App_TaskUsre3(void* p_arg)
{
     printf("App_TaskUsre3\r\n");
   while (1)
   {
      LED_3_ON();
      OSTimeDlyHMSM(0, 0, 0, 100);
    
      LED_3_OFF();
      OSTimeDlyHMSM(0, 0, 0, 100);
	  printf("App_Taskstart3\r\n");
   }
}

//建立自己的任务
static  void App_TaskUsre4(void* p_arg)
{
     printf("App_TaskUsre4\r\n");
   while (1)
   {
      LED_4_ON();
      OSTimeDlyHMSM(0, 0, 0, 400);
    
      LED_4_OFF();
      OSTimeDlyHMSM(0, 0, 1, 400);
	  printf("App_Taskstart4\r\n");
   }
}

//建立自己的任务
static  void App_TaskUsre5(void* p_arg)
{
     printf("App_TaskUsre5\r\n");
   while (1)
   {
      LED_5_ON();
      OSTimeDlyHMSM(0, 0, 1, 0);
    
      LED_5_OFF();
      OSTimeDlyHMSM(0, 0, 1, 0);
	  printf("App_Taskstart5\r\n");
   }
}

//建立自己的任务
static  void App_TaskUsre6(void* p_arg)
{
     printf("App_TaskUsre6\r\n");
   while (1)
   {
      LED_6_ON();
      OSTimeDlyHMSM(0, 0, 0, 200);
    
      LED_6_OFF();
      OSTimeDlyHMSM(0, 0, 1, 200);
	  printf("App_Taskstart6\r\n");
   }
}

//建立自己的任务
static  void App_TaskUsre7(void* p_arg)
{
     printf("App_TaskUsre7\r\n");
   while (1)
   {
      LED_7_ON();
      OSTimeDlyHMSM(0, 0, 0, 700);
    
      LED_7_OFF();
      OSTimeDlyHMSM(0, 0, 2, 700);
	  printf("App_Taskstart7\r\n");
   }
}

//建立自己的任务
static  void App_TaskUsre8(void* p_arg)
{
     printf("App_TaskUsre8\r\n");
   while (1)
   {
      LED_8_ON();
      OSTimeDlyHMSM(0, 0, 0, 400);
    
      LED_8_OFF();
      OSTimeDlyHMSM(0, 0, 0, 900);
	  printf("App_Taskstart8\r\n");
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
