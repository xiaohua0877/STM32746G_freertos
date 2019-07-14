/**
  ******************************************************************************
  * @file    BSP/Src/lcd.c
  * @author  MCD Application Team
  * @brief   This example code shows how to use LCD drawing features.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "lcd.h"
/** @addtogroup STM32F7xx_HAL_Examples
  * @{
  */

/** @addtogroup BSP
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define LCD_FEATURES_NUM                3
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint8_t LCD_Feature = 0;
/* Private function prototypes -----------------------------------------------*/
static void LCD_SetHint(void);
static void LCD_Show_Feature(uint8_t feature);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  LCD demo
  * @param  None
  * @retval None
  */
void LCD_demo(void)
{
    LCD_SetHint();
    LCD_Feature = 0;
    LCD_Show_Feature(LCD_Feature);

    while (1)
    {

        if (CheckForUserInput() > 0)
        {
            if (++LCD_Feature < LCD_FEATURES_NUM)
            {
                LCD_Show_Feature(LCD_Feature);
            }
            else
            {
                return;
            }
        }
        HAL_Delay(100);
    }
}

/**
  * @brief  Display LCD demo hint
  * @param  None
  * @retval None
  */
static void LCD_SetHint(void)
{
    /* Clear the LCD */
    BSP_LCD_Clear(LCD_COLOR_WHITE);

    /* Set LCD Demo description */
    BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
    BSP_LCD_FillRect(0, 0, BSP_LCD_GetXSize(), 80);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
    BSP_LCD_SetFont(&Font24);
    BSP_LCD_DisplayStringAt(0, 0, (uint8_t *)"LCD", CENTER_MODE);
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_DisplayStringAt(0, 30, (uint8_t *)"This example shows the different", CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, 45, (uint8_t *)"LCD Features, use BUTTON to display", CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, 60, (uint8_t *)"next page", CENTER_MODE);

    /* Set the LCD Text Color */
    BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
    BSP_LCD_DrawRect(10, 90, BSP_LCD_GetXSize() - 20, BSP_LCD_GetYSize() - 100);
    BSP_LCD_DrawRect(11, 91, BSP_LCD_GetXSize() - 22, BSP_LCD_GetYSize() - 102);
}

/**
  * @brief  Show LCD Features
  * @param  feature : feature index
  * @retval None
  */
static void LCD_Show_Feature(uint8_t feature)
{
    Point Points[] = {{20, 150}, {80, 150}, {80, 200}};
    Point Points2[] = {{100, 150}, {160, 150}, {160, 200}};

    BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_FillRect(12, 92, BSP_LCD_GetXSize() - 24, BSP_LCD_GetYSize() - 104);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);

    switch (feature)
    {
    case 0:
        /* Text Feature */

        BSP_LCD_DisplayStringAt(14, 100, (uint8_t *)"Left aligned Text", LEFT_MODE);
        BSP_LCD_DisplayStringAt(0, 115, (uint8_t *)"Center aligned Text", CENTER_MODE);
        BSP_LCD_DisplayStringAt(14, 130, (uint8_t *)"Right aligned Text", RIGHT_MODE);
        BSP_LCD_SetFont(&Font24);
        BSP_LCD_DisplayStringAt(14, 180, (uint8_t *)"Font24", LEFT_MODE);
        BSP_LCD_SetFont(&Font20);
        BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize() / 2 - 20, 180, (uint8_t *)"Font20", LEFT_MODE);
        BSP_LCD_SetFont(&Font16);
        BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize() - 80, 184, (uint8_t *)"Font16", LEFT_MODE);
        break;

    case 1:

        /* Draw misc. Shapes */
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DrawRect(20, 100, 60, 40);
        BSP_LCD_FillRect(100, 100, 60, 40);

        BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
        BSP_LCD_DrawCircle(BSP_LCD_GetXSize() - 120, 120, 20);
        BSP_LCD_FillCircle(BSP_LCD_GetXSize() - 40, 120, 20);

        BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
        BSP_LCD_DrawPolygon(Points, 3);
        BSP_LCD_FillPolygon(Points2, 3);

        BSP_LCD_SetTextColor(LCD_COLOR_RED);
        BSP_LCD_DrawEllipse(BSP_LCD_GetXSize() - 120, 170, 30, 20);
        BSP_LCD_FillEllipse(BSP_LCD_GetXSize() - 50, 170, 30, 20);

        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DrawHLine(20, BSP_LCD_GetYSize() - 30, BSP_LCD_GetXSize() / 5);
        BSP_LCD_DrawLine(BSP_LCD_GetXSize() - 150, BSP_LCD_GetYSize() - 20, BSP_LCD_GetXSize() - 20,
                         BSP_LCD_GetYSize() - 50);
        BSP_LCD_DrawLine(BSP_LCD_GetXSize() - 150, BSP_LCD_GetYSize() - 50, BSP_LCD_GetXSize() - 20,
                         BSP_LCD_GetYSize() - 20);
        break;

    case 2:
        /* Draw Bitmap */
        BSP_LCD_DrawBitmap(20, 100, (uint8_t *)stlogo);
        HAL_Delay(100);

        BSP_LCD_DrawBitmap(BSP_LCD_GetXSize() / 2 - 40, 100, (uint8_t *)stlogo);
        HAL_Delay(100);

        BSP_LCD_DrawBitmap(BSP_LCD_GetXSize() - 100, 100, (uint8_t *)stlogo);
        HAL_Delay(100);

        BSP_LCD_DrawBitmap(20, BSP_LCD_GetYSize() - 80, (uint8_t *)stlogo);
        HAL_Delay(100);

        BSP_LCD_DrawBitmap(BSP_LCD_GetXSize() / 2 - 40, BSP_LCD_GetYSize() - 80, (uint8_t *)stlogo);
        HAL_Delay(100);

        BSP_LCD_DrawBitmap(BSP_LCD_GetXSize() - 100, BSP_LCD_GetYSize() - 80, (uint8_t *)stlogo);
        HAL_Delay(100);
        break;

    default :
        break;
    }
}
//m^n函数
//返回值:m^n次方.
uint32_t LCD_Pow(uint8_t m, uint8_t n)
{
    uint32_t result = 1;
    while (n--)
    {
        result *= m;
    }
    return result;
}

//显示数字,高位为0,还是显示
//x,y:起点坐标
//num:数值(0~999999999);
//len:长度(即要显示的位数)
//size:字体大小
//mode:
//[7]:0,不填充;1,填充0.
//[6:1]:保留
//[0]:0,非叠加显示;1,叠加显示.
void LCD_ShowxNum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size, uint8_t mode)
{
    uint8_t t, temp;
    uint8_t enshow = 0;
    for (t = 0; t < len; t++)
    {
        temp = (num / LCD_Pow(10, len - t - 1)) % 10;
        if (enshow == 0 && t < (len - 1))
        {
            if (temp == 0)
            {
                if (mode & 0X80)
                {
                    //LCD_ShowChar(x + (size / 2)*t, y, '0', size, mode & 0X01);
                    BSP_LCD_DisplayChar(x + (size / 2)*t, y, '0');
                }
                else
                {
                    // LCD_ShowChar(x + (size / 2)*t, y, ' ', size, mode & 0X01);
                    BSP_LCD_DisplayChar(x + (size / 2)*t, y, ' ');
                }
                continue;
            }
            else
            {
                enshow = 1;
            }

        }
        BSP_LCD_DisplayChar(x + (size / 2)*t, y, temp + '0');
    }
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
