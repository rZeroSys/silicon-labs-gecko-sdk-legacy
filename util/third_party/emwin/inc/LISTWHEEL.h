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
File        : LISTWHEEL.h
Purpose     : LISTWHEEL widget include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef LISTWHEEL_H
#define LISTWHEEL_H

#include "WM.h"
#include "DIALOG_Intern.h"
#include "WIDGET.h"

#if GUI_WINSUPPORT

#if defined(__cplusplus)
  extern "C" {        // Make sure we have C-declarations in C++ programs
#endif

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define LISTWHEEL_CI_UNSEL 0
#define LISTWHEEL_CI_SEL   1

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
typedef WM_HMEM LISTWHEEL_Handle;

/*********************************************************************
*
*       Standard member functions
*
**********************************************************************
*/
/*********************************************************************
*
*       Create functions
*
**********************************************************************
*/
LISTWHEEL_Handle LISTWHEEL_Create        (const GUI_ConstString * ppText, int x0, int y0, int xSize, int ySize, int Flags);
LISTWHEEL_Handle LISTWHEEL_CreateAsChild (const GUI_ConstString * ppText, WM_HWIN hWinParent, int x0, int y0, int xSize, int ySize, int Flags);
LISTWHEEL_Handle LISTWHEEL_CreateIndirect(const GUI_WIDGET_CREATE_INFO * pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK * cb);
LISTWHEEL_Handle LISTWHEEL_CreateEx      (int x0, int y0, int xSize, int ySize, WM_HWIN hParent,
                                          int WinFlags, int ExFlags, int Id, const GUI_ConstString * ppText);
LISTWHEEL_Handle LISTWHEEL_CreateUser    (int x0, int y0, int xSize, int ySize, WM_HWIN hParent,
                                          int WinFlags, int ExFlags, int Id, const GUI_ConstString * ppText, int NumExtraBytes);

/*********************************************************************
*
*       The callback ...
*
* Do not call it directly ! It is only to be used from within an
* overwritten callback.
*/
void LISTWHEEL_Callback(WM_MESSAGE * pMsg);

/*********************************************************************
*
*       Member functions
*
**********************************************************************
*/
void      LISTWHEEL_AddString      (LISTWHEEL_Handle hObj, const char * s);
void *    LISTWHEEL_GetItemData    (LISTWHEEL_Handle hObj, unsigned Index); /* not to be documented */
void      LISTWHEEL_GetItemText    (LISTWHEEL_Handle hObj, unsigned Index, char * pBuffer, int MaxSize);
int       LISTWHEEL_GetItemFromPos (LISTWHEEL_Handle hObj, int yPos);
int       LISTWHEEL_GetLBorder     (LISTWHEEL_Handle hObj);
unsigned  LISTWHEEL_GetLineHeight  (LISTWHEEL_Handle hObj);
int       LISTWHEEL_GetNumItems    (LISTWHEEL_Handle hObj);
int       LISTWHEEL_GetPos         (LISTWHEEL_Handle hObj);
int       LISTWHEEL_GetRBorder     (LISTWHEEL_Handle hObj);
int       LISTWHEEL_GetSel         (LISTWHEEL_Handle hObj);
int       LISTWHEEL_GetSnapPosition(LISTWHEEL_Handle hObj);
int       LISTWHEEL_GetTextAlign   (LISTWHEEL_Handle hObj);
int       LISTWHEEL_GetUserData    (LISTWHEEL_Handle hObj, void * pDest, int NumBytes);
int       LISTWHEEL_IsMoving       (LISTWHEEL_Handle hObj);
void      LISTWHEEL_MoveToPos      (LISTWHEEL_Handle hObj, unsigned int Index);
int       LISTWHEEL_OwnerDraw      (const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
void      LISTWHEEL_SetBkColor     (LISTWHEEL_Handle hObj, unsigned int Index, GUI_COLOR Color);
void      LISTWHEEL_SetDeceleration(LISTWHEEL_Handle hObj, unsigned Deceleration);
void      LISTWHEEL_SetFont        (LISTWHEEL_Handle hObj, const GUI_FONT * pFont);
void      LISTWHEEL_SetItemData    (LISTWHEEL_Handle hObj, unsigned Index, void * pData); /* not to be documented */
void      LISTWHEEL_SetLBorder     (LISTWHEEL_Handle hObj, unsigned BorderSize);
void      LISTWHEEL_SetLineHeight  (LISTWHEEL_Handle hObj, unsigned LineHeight);
void      LISTWHEEL_SetOwnerDraw   (LISTWHEEL_Handle hObj, WIDGET_DRAW_ITEM_FUNC * pfOwnerDraw);
void      LISTWHEEL_SetPos         (LISTWHEEL_Handle hObj, unsigned int Index);
void      LISTWHEEL_SetRBorder     (LISTWHEEL_Handle hObj, unsigned BorderSize);
void      LISTWHEEL_SetSel         (LISTWHEEL_Handle hObj, int Sel);
void      LISTWHEEL_SetSnapPosition(LISTWHEEL_Handle hObj, int SnapPosition);
void      LISTWHEEL_SetText        (LISTWHEEL_Handle hObj, const GUI_ConstString * ppText);
void      LISTWHEEL_SetTextAlign   (LISTWHEEL_Handle hObj, int Align);
void      LISTWHEEL_SetTextColor   (LISTWHEEL_Handle hObj, unsigned int Index, GUI_COLOR Color);
void      LISTWHEEL_SetTimerPeriod (LISTWHEEL_Handle hObj, GUI_TIMER_TIME TimerPeriod);
int       LISTWHEEL_SetUserData    (LISTWHEEL_Handle hObj, const void * pSrc, int NumBytes);
void      LISTWHEEL_SetVelocity    (LISTWHEEL_Handle hObj, int Velocity);

const GUI_FONT * LISTWHEEL_GetFont(LISTWHEEL_Handle hObj);

#if defined(__cplusplus)
  }
#endif

#endif  // GUI_WINSUPPORT
#endif  // LISTWHEEL_H

/*************************** End of file ****************************/