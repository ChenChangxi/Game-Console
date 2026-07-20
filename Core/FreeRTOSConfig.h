/* FreeRTOS配置 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include "sys.h"

#define vPortSVCHandler        SVC_Handler        /* 任务启动 */
#define xPortPendSVHandler     PendSV_Handler     /* 任务切换 */
#define xPortSysTickHandler    SysTick_Handler    /* 产生节拍 */

/********************************** 基础配置项 **********************************/

#define configCPU_CLOCK_HZ                         SystemCoreClock            /* 内核主频率 */
#define configTICK_RATE_HZ                         ( 1000U )                  /* 任务切换频率 */
#define configUSE_PREEMPTION                       1                          /* 抢占式调度 */
#define configUSE_TIME_SLICING                     1                          /* 时间片调度 */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION    1                          /* 硬件计算下个任务 */
#define configUSE_TICKLESS_IDLE                    1
#define configMAX_PRIORITIES                       32U                        /* 任务优先级数 */
#define configMINIMAL_STACK_SIZE                   128U
#define configMAX_TASK_NAME_LEN                    16U                        /* 任务名最大字符数 */
#define configTICK_TYPE_WIDTH_IN_BITS              TICK_TYPE_WIDTH_64_BITS
#define configIDLE_SHOULD_YIELD                    1
#define configTASK_NOTIFICATION_ARRAY_ENTRIES      1U
#define configQUEUE_REGISTRY_SIZE                  0U
#define configENABLE_BACKWARD_COMPATIBILITY        1
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS    0
#define configSTACK_DEPTH_TYPE                     size_t
#define configMESSAGE_BUFFER_LENGTH_TYPE           size_t
#define configUSE_NEWLIB_REENTRANT                 0

/********************************** 软件定时器 **********************************/

#define configUSE_TIMERS                1
#define configTIMER_TASK_PRIORITY       ( configMAX_PRIORITIES - 1U )
#define configTIMER_TASK_STACK_DEPTH    configMINIMAL_STACK_SIZE
#define configTIMER_QUEUE_LENGTH        10U

/********************************** 内存分配项 **********************************/

#define configSUPPORT_STATIC_ALLOCATION              0                       /* 静态内存分配 */
#define configSUPPORT_DYNAMIC_ALLOCATION             1                       /* 动态内存分配 */
#define configTOTAL_HEAP_SIZE                        4096U                   /* 可用堆总大小 */
#define configAPPLICATION_ALLOCATED_HEAP             1
#define configSTACK_ALLOCATION_FROM_SEPARATE_HEAP    0
#define configUSE_MINI_LIST_ITEM                     0

/******************************************************************************/
/* Interrupt nesting behaviour configuration. *********************************/
/******************************************************************************/

#define configKERNEL_INTERRUPT_PRIORITY          0U
#define configMAX_SYSCALL_INTERRUPT_PRIORITY     0U
#define configMAX_API_CALL_INTERRUPT_PRIORITY    0U

/******************************************************************************/
/* Hook and callback function related definitions. ****************************/
/******************************************************************************/

#define configUSE_IDLE_HOOK                   0
#define configUSE_TICK_HOOK                   0
#define configUSE_MALLOC_FAILED_HOOK          0
#define configUSE_DAEMON_TASK_STARTUP_HOOK    0
#define configCHECK_FOR_STACK_OVERFLOW        0

/******************************************************************************/
/* Run time and task stats gathering related definitions. *********************/
/******************************************************************************/

#define configGENERATE_RUN_TIME_STATS           0
#define configUSE_TRACE_FACILITY                0
#define configUSE_STATS_FORMATTING_FUNCTIONS    0
#define configKERNEL_PROVIDED_STATIC_MEMORY     1

/******************************************************************************/
/* Definitions that include or exclude functionality. *************************/
/******************************************************************************/

#define configUSE_TASK_NOTIFICATIONS           1               /* 任务间消息传递 */
#define configUSE_MUTEXES                      1               /* 互斥信号量 */
#define configUSE_RECURSIVE_MUTEXES            1               /* 递归互斥信号量 */
#define configUSE_COUNTING_SEMAPHORES          1               /* 计数信号量 */
#define configUSE_QUEUE_SETS                   1               /* 队列集 */
#define configUSE_APPLICATION_TASK_TAG         1
#define INCLUDE_vTaskPrioritySet               1               /* 任务优先级设置 */
#define INCLUDE_uxTaskPriorityGet              1               /* 任务优先级获取 */
#define INCLUDE_vTaskDelete                    1               /* 任务删除 */
#define INCLUDE_vTaskSuspend                   1               /* 任务挂起 */
#define INCLUDE_xResumeFromISR                 1
#define INCLUDE_vTaskDelayUntil                1
#define INCLUDE_vTaskDelay                     1               /* 任务延时 */
#define INCLUDE_xTaskGetSchedulerState         1               /* 任务调度器状态 */
#define INCLUDE_xTaskGetCurrentTaskHandle      1
#define INCLUDE_uxTaskGetStackHighWaterMark    1
#define INCLUDE_xTaskGetIdleTaskHandle         1
#define INCLUDE_eTaskGetState                  1               /* 任务状态 */
#define INCLUDE_xEventGroupSetBitFromISR       1
#define INCLUDE_xTimerPendFunctionCall         1
#define INCLUDE_xTaskAbortDelay                1
#define INCLUDE_xTaskGetHandle                 1
#define INCLUDE_xTaskResumeFromISR             1

#endif /* FREERTOS_CONFIG_H */