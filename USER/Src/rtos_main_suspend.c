//#include "sys.h"
//#include "delay.h"
//#include "usart.h"
//#include "led.h"
//#include "lcd.h"
//#include "sdram.h"
//#include "key.h"
//#include "exti.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "lcd.h"

typedef struct
{
    int32_t     key_task;
    int32_t     task1_task;
    int32_t     task2_task;
    int32_t     task3_task;
} run_count_t;

run_count_t     task_count;

//任务优先级
#define START_TASK_PRIO     1
//任务堆栈大小
#define START_STK_SIZE      128
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void start_task(void *pvParameters);

//任务优先级
#define KEY_TASK_PRIO       2
//任务堆栈大小
#define KEY_STK_SIZE        128
//任务句柄
TaskHandle_t KeyTask_Handler;
//任务函数
void key_task(void *pvParameters);

//任务优先级
#define TASK1_TASK_PRIO     3
//任务堆栈大小
#define TASK1_STK_SIZE      128
//任务句柄
TaskHandle_t Task1Task_Handler;
//任务函数
void task1_task(void *pvParameters);

//任务优先级
#define TASK2_TASK_PRIO     4
//任务堆栈大小
#define TASK2_STK_SIZE      128
//任务句柄
TaskHandle_t Task2Task_Handler;
//任务函数
void task2_task(void *pvParameters);

//任务优先级
#define TASK3_TASK_PRIO     5
//任务堆栈大小
#define TASK3_STK_SIZE      128
//任务句柄
TaskHandle_t Task3Task_Handler;
//任务函数
void task3_task(void *pvParameters);


//任务优先级
#define TASK4_TASK_PRIO     6
//任务堆栈大小
#define TASK4_STK_SIZE      128
//任务句柄
TaskHandle_t Task4Task_Handler;
//任务函数
void task4_task(void *pvParameters);


////LCD刷屏时使用的颜色
int lcd_discolor[14] = {  LCD_COLOR_BLUE, LCD_COLOR_GREEN, LCD_COLOR_RED,  LCD_COLOR_CYAN,
                          LCD_COLOR_YELLOW,  LCD_COLOR_LIGHTBLUE, LCD_COLOR_LIGHTGREEN,   LCD_COLOR_LIGHTRED,
                          LCD_COLOR_LIGHTCYAN, LCD_COLOR_LIGHTMAGENTA,  LCD_COLOR_LIGHTYELLOW, LCD_COLOR_DARKBLUE,
                          LCD_COLOR_DARKGREEN, LCD_COLOR_DARKRED
                       };
//void BSP_LCD_DisplayStringAt(uint16_t Xpos, uint16_t Ypos, uint8_t *Text, Text_AlignModeTypdef Mode)

int rtos_main_suspend(void)
{
    //    Cache_Enable();                 //打开L1-Cache
    //    HAL_Init();                     //初始化HAL库
    //    Stm32_Clock_Init(432,25,2,9);   //设置时钟,216Mhz
    //    delay_init(216);                //延时初始化
    //    uart_init(115200);              //串口初始化
    //    LED_Init();                     //初始化LED
    //    KEY_Init();                     //初始化按键
    //    EXTI_Init();                    //初始化外部中断
    //    SDRAM_Init();                   //初始化SDRAM
    //    LCD_Init();                     //初始化LCD

    //    POINT_COLOR = RED;
    BSP_LCD_FillRect(0, 0, BSP_LCD_GetXSize(), 80);
    /* Clear the LCD */
    BSP_LCD_Clear(LCD_COLOR_WHITE);

    /* Set LCD Demo description */
    BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
    BSP_LCD_FillRect(0, 0, BSP_LCD_GetXSize(), 80);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
    BSP_LCD_SetFont(&Font12);


    LCD_ShowString(30, 10, 200, 16, 16, "Apollo STM32F4/F7");
    LCD_ShowString(30, 30, 200, 16, 16, "FreeRTOS Examp 6-3");
    LCD_ShowString(30, 50, 200, 16, 16, "Task Susp and Resum");
    LCD_ShowString(30, 70, 200, 16, 16, "ATOM@ALIENTEK");
    LCD_ShowString(30, 90, 200, 16, 16, "2016/9/24");
    //创建开始任务
    xTaskCreate((TaskFunction_t)start_task,             //任务函数
                (const char *)"start_task",             //任务名称
                (uint16_t)START_STK_SIZE,               //任务堆栈大小
                (void *)NULL,                           //传递给任务函数的参数
                (UBaseType_t)START_TASK_PRIO,           //任务优先级
                (TaskHandle_t *)&StartTask_Handler);    //任务句柄
    vTaskStartScheduler();          //开启任务调度
    return 00;
}

//开始任务任务函数
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区
    //    //创建KEY任务
    xTaskCreate((TaskFunction_t)key_task,
                (const char *)"key_task",
                (uint16_t)KEY_STK_SIZE,
                (void *)NULL,
                (UBaseType_t)KEY_TASK_PRIO,
                (TaskHandle_t *)&KeyTask_Handler);
    //创建TASK1任务
    xTaskCreate((TaskFunction_t)task1_task,
                (const char *)"task1_task",
                (uint16_t)TASK1_STK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK1_TASK_PRIO,
                (TaskHandle_t *)&Task1Task_Handler);
    //创建TASK2任务
    xTaskCreate((TaskFunction_t)task2_task,
                (const char *)"task2_task",
                (uint16_t)TASK2_STK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK2_TASK_PRIO,
                (TaskHandle_t *)&Task2Task_Handler);

    //创建TASK3任务
    xTaskCreate((TaskFunction_t)task3_task,
                (const char *)"task3_task",
                (uint16_t)TASK3_STK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK3_TASK_PRIO,
                (TaskHandle_t *)&Task3Task_Handler);

        //创建TASK4任务
    xTaskCreate((TaskFunction_t)task4_task,
                (const char *)"task4_task",
                (uint16_t)TASK4_STK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK4_TASK_PRIO,
                (TaskHandle_t *)&Task4Task_Handler);            
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}

//key任务函数
void key_task(void *pvParameters)
{
    int8_t key = 0, start = 0;
    int8_t runcount = 0;
    while (1)
    {
        if (BSP_PB_GetState(BUTTON_KEY) != RESET)
        {
            //start = 0x1;
            key = task_count.key_task % 4;
            switch (key)
            {
            case 1:
                vTaskSuspend(Task1Task_Handler);//挂起任务1
                printf("suspend  task1 running!\r\n");
                break;
            case 2:
                vTaskResume(Task1Task_Handler); //恢复任务1
                printf("Resume  task1 running!\r\n");
                break;
            case 3:
                vTaskSuspend(Task2Task_Handler);//挂起任务2
                printf("suspend  task2 running\r\n");
                break;
            }
        }
        else
        {
            //start = 0;
        }

        task_count.key_task++;

        vTaskDelay(10);         //延时10ms
    }
}
#define A_X1    (5)
#define A_Y1    (110)
#define A_X2    (5)
#define A_Y2    (110)
#define Y4      (150)    //131
//task1任务函数
void task1_task(void *pvParameters)
{
    uint8_t task1_num = 0;

    //    POINT_COLOR = BLACK;
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    //BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
    LCD_DrawRectangle(5, 110, 115, 314); //画一个矩形
    LCD_DrawLine(5, 130, 115, 130);     //画线
    // POINT_COLOR = BLUE;
    //BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    LCD_ShowString(6, 111, 110, 16, 16, "Task1 Run:");
    while (1)
    {
        task1_num++;    //任务执1行次数加1 注意task1_num1加到255的时候会清零！！
        task_count.task1_task++;
        //        LED0_Toggle;
        printf("任务1已经执行：%d次\r\n", task1_num);
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        LCD_ShowxNum(86, 111, task1_num, 3, 16, 0x80); //显示任务执行次数
        LCD_Fill(6, Y4, 114, 313, lcd_discolor[task1_num % 14]); //填充区域
        vTaskDelay(1000);                           //延时1s，也就是1000个时钟节拍
    }
}

//task2任务函数
void task2_task(void *pvParameters)
{
    uint8_t task2_num = 0;

    //    POINT_COLOR = BLACK;
    //
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    LCD_DrawRectangle(125, 110, 234, 314); //画一个矩形
    LCD_DrawLine(125, 130, 234, 130);   //画线
    //BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    LCD_ShowString(126, 111, 110, 16, 16, "Task2 Run:");
    while (1)
    {
        task2_num++;    //任务2执行次数加1 注意task1_num2加到255的时候会清零！！
        task_count.task2_task++;
        //      LED1_Toggle;
        printf("任务2已经执行：%d次\r\n", task2_num);
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        LCD_ShowxNum(206, 111, task2_num, 3, 16, 0x80); //显示任务执行次数
        LCD_Fill(126, Y4, 233, 313, lcd_discolor[13 - task2_num % 14]); //填充区域
        vTaskDelay(1000);                           //延时1s，也就是1000个时钟节拍
    }
}

#define B_X1        (125)
#define B_Y1        (110)

#define C_X1        (B_X1 +120)
#define D_X1        (C_X1 +0)
#define D_Y1        (B_Y1 +20)

//task2任务函数
void task3_task(void *pvParameters)
{
    uint8_t task3_num = 0;
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    LCD_ShowString(C_X1, 111, 110, 16, 16, "Task3 Run:");
    while (1)
    {
        task3_num++;
        task_count.task2_task++;
        printf("任务3已经执行：%d次\r\n", task3_num);
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        LCD_ShowxNum(C_X1 + 80, 111, task3_num, 3, 16, 0x80);
        vTaskDelay(1000);
    }
}



//task2任务函数
void task4_task(void *pvParameters)
{
    uint8_t task4_num = 0;
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    LCD_ShowString(D_X1, D_Y1, 110, 16, 16, "Task4 Run:");
    while (1)
    {
        task4_num++;
        task_count.task2_task++;
        printf("任务4已经执行：%d次\r\n", task4_num);
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        LCD_ShowxNum(D_X1 + 80, D_Y1, task4_num, 3, 16, 0x80);
        vTaskDelay(1000);
    }
}

