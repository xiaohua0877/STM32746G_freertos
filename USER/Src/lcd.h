#ifndef __LCD_H
#define __LCD_H
//#include "sys.h"
#include "stdlib.h"
#include "main.h"

//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//2.8寸/3.5寸/4.3寸/7寸 TFT液晶驱动
//支持驱动IC型号包括:ILI9341/NT35310/NT35510/SSD1963等
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2015/12/10
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////


//画笔颜色
#define WHITE          LCD_COLOR_WHITE //  0xFFFF
#define BLACK          LCD_COLOR_BLACK//   0x0000
#define BLUE           LCD_COLOR_BLUE //    0x001F
#define BRED           LCD_COLOR_LIGHTBLUE //    0XF81F
#define GRED           LCD_COLOR_LIGHTGREEN    //  0XFFE0
#define GBLUE          LCD_COLOR_LIGHTRED    //    0X07FF
#define RED            LCD_COLOR_RED//       0xF800
#define MAGENTA        LCD_COLOR_DARKMAGENTA//  0xF81F
#define GREEN          LCD_COLOR_GREEN//  0x07E0
#define CYAN           LCD_COLOR_CYAN//  0x7FFF
#define YELLOW         LCD_COLOR_YELLOW //  0xFFE0
#define BROWN          LCD_COLOR_BROWN //  0XBC40 //棕色
#define BRRED          LCD_COLOR_BROWN // 0XFC07 //棕红色
#define GRAY           LCD_COLOR_GRAY //0X8430 //灰色
//GUI颜色


//void BSP_LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
#define LCD_DrawLine( x1,  y1,  x2,  y2)    \
            BSP_LCD_DrawLine(x1,y1,x2,y2)
//画线
#define  LCD_DrawRectangle( x1,  y1,  x2,  y2)     \
        BSP_LCD_FillRect(x1,y1,x2-x1,y2-y1);                     //画矩形

#define LCD_Fill( sx, sy, ex, ey, color) {        \
    BSP_LCD_SetTextColor(color);                    \
    BSP_LCD_FillRect(sx,sy,ex-sx,ey-sy);            \
    }
//;                       //填充单色


//void BSP_LCD_DisplayStringAt(uint16_t Xpos, uint16_t Ypos, uint8_t *Text, Text_AlignModeTypdef Mode)
//void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p);
//显示一个字符串,12/16字体

//#define LCD_ShowString( x, y, width, height, size, *p) {   \
//    BSP_LCD_DisplayStringAt(x,y,p,LEFT_MODE);           \     
//}

#define LCD_ShowString(x,y,width,height,size,p)             \
            BSP_LCD_DisplayStringAt(x,y,p,LEFT_MODE);

void LCD_ShowxNum(uint16_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size, uint8_t mode);

#endif





