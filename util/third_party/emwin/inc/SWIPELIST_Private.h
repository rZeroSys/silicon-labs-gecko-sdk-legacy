/***************************************************************************//**
 * # License
 * 
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is Third Party Software licensed by Silicon Labs from a third party
 * and is governed by the sections of the MSLA applicable to Third Party
 * Software and the additional terms set forth below.
 * 
 ******************************************************************************/

/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2016  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.34 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The  software has  been licensed  to Silicon Labs Norway, a subsidiary
of Silicon Labs Inc. whose registered office is 400 West Cesar Chavez,
Austin,  TX 78701, USA solely for  the purposes of creating  libraries 
for its  ARM Cortex-M3, M4F  processor-based devices,  sublicensed and 
distributed  under the  terms and conditions  of the  End User License  
Agreement supplied by Silicon Labs.
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
Licensing information

Licensor:                 SEGGER Software GmbH
Licensed to:              Silicon Laboratories Norway
Licensed SEGGER software: emWin
License number:           GUI-00140
License model:            See Agreement, dated 20th April 2012
Licensed product:         - 
Licensed platform:        Cortex M3, Cortex M4F
Licensed number of seats: -
----------------------------------------------------------------------
File        : SWIPELIST.h
Purpose     : SWIPELIST include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef SWIPELIST_PRIVATE_H
#define SWIPELIST_PRIVATE_H

#include "SWIPELIST.h"
#include "GUI_Private.h"
#include "GUI_ARRAY.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Object definition
*
**********************************************************************
*/
typedef struct {
  WM_HWIN hWin;
  int     xPos;
  int     yPos;
} SWIPELIST_WIN;

typedef struct {
  GUI_ARRAY      WinArray;
  GUI_ARRAY      TextArray;
  int            TextSize;
  WM_HMEM        hDrawObj;
  GUI_COLOR      SepColor;
  int            SepSize;
  int            Pos;
  int            Size;
  int            BitmapAlign;
  int            TextAlign;
  U8             Flags;
  U32            UserData;
} SWIPELIST_ITEM;

typedef struct {
  const GUI_FONT * pSepFont;
  const GUI_FONT * pHeaderFont;
  const GUI_FONT * pTextFont;
  GUI_COLOR        aTextColor[5];
  GUI_COLOR        aBkColor[3];
  int              BitmapSpace;
  int              aBorderSize[4];
  U8               Flags;
} SWIPELIST_PROPS;

typedef struct {
  WIDGET                  Widget;
  SWIPELIST_PROPS         Props;
  WIDGET_DRAW_ITEM_FUNC * pfDrawItem;
  GUI_ARRAY               ItemArray;
  int                     Pos;
  int                     Size;
  int                     FirstVisible;
  int                     LastVisible;
  int                     Sel;
  int                     ReleasedItem;
} SWIPELIST_OBJ;

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/
#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  #define SWIPELIST_INIT_ID(p) p->Widget.DebugId = SWIPELIST_ID
#else
  #define SWIPELIST_INIT_ID(p)
#endif

#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  SWIPELIST_OBJ * SWIPELIST_LockH(SWIPELIST_Handle h);
  #define SWIPELIST_LOCK_H(h)   SWIPELIST_LockH(h)
#else
  #define SWIPELIST_LOCK_H(h)   (SWIPELIST_OBJ *)GUI_LOCK_H(h)
#endif

/*********************************************************************
*
*       Module internal data
*
**********************************************************************
*/
extern SWIPELIST_PROPS SWIPELIST__DefaultProps;
extern GUI_COLOR       SWIPELIST__DefaultSepColor;
extern int             SWIPELIST__DefaultSepSize;
extern int             SWIPELIST__DefaultTextAlign;

/*********************************************************************
*
*       Private functions
*
**********************************************************************
*/
void SWIPELIST__SetDrawObj   (SWIPELIST_Handle hObj, int Index, int Align, GUI_DRAW_HANDLE hDrawObj);
void SWIPELIST__CalcItemPos  (GUI_ARRAY ItemArray, int StartIndex, int EndIndex, int AddSize);
int  SWIPELIST__CalcItemSize (SWIPELIST_Handle hObj, int ItemIndex);

#endif   /* if GUI_WINSUPPORT */
#endif   /* SWIPELIST_PRIVATE_H */
