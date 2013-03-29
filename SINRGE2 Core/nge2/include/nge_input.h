/***************************************************************************
 *            nge_input.h
 *
 *  2011/03/25 06:18:44
 *  Copyright  2011  Kun Wang <ifreedom.cn@gmail.com>
 ****************************************************************************/
/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef _NGE_INPUT_H
#define _NGE_INPUT_H

#include "nge_common.h"

#if defined NGE_PSP || defined NGE_LINUX || defined NGE_WIN || defined NGE_IPHONE
#define NGE_INPUT_BUTTON_SUPPORT
#define NGE_INPUT_ANALOG_SUPPORT
#if defined NGE_WIN
#define PSP_BUTTON_UP            'W'
#define PSP_BUTTON_DOWN          'S'
#define PSP_BUTTON_LEFT          'A'
#define PSP_BUTTON_RIGHT         'D'
#define PSP_BUTTON_TRIANGLE      'I'
#define PSP_BUTTON_CIRCLE        'L'
#define PSP_BUTTON_CROSS         'K'
#define PSP_BUTTON_SQUARE        'J'
#define PSP_BUTTON_LEFT_TRIGGER  'E'
#define PSP_BUTTON_RIGHT_TRIGGER 'U'
#define PSP_BUTTON_SELECT        'V'
#define PSP_BUTTON_START         'B'
#define PSP_BUTTON_HOME          'N'
#define PSP_BUTTON_HOLD          'M'
#elif defined NGE_LINUX
#include <X11/keysym.h>
#define PSP_BUTTON_UP            XK_w
#define PSP_BUTTON_DOWN          XK_s
#define PSP_BUTTON_LEFT          XK_a
#define PSP_BUTTON_RIGHT         XK_d
#define PSP_BUTTON_TRIANGLE      XK_i
#define PSP_BUTTON_CIRCLE        XK_l
#define PSP_BUTTON_CROSS         XK_k
#define PSP_BUTTON_SQUARE        XK_j
#define PSP_BUTTON_LEFT_TRIGGER  XK_e
#define PSP_BUTTON_RIGHT_TRIGGER XK_u
#define PSP_BUTTON_SELECT        XK_v
#define PSP_BUTTON_START         XK_b
#define PSP_BUTTON_HOME          XK_n
#define PSP_BUTTON_HOLD          XK_m
#elif defined NGE_PSP
#define PSP_BUTTON_UP            8
#define PSP_BUTTON_DOWN          6
#define PSP_BUTTON_LEFT          7
#define PSP_BUTTON_RIGHT         9
#define PSP_BUTTON_TRIANGLE      0
#define PSP_BUTTON_CIRCLE        1
#define PSP_BUTTON_CROSS         2
#define PSP_BUTTON_SQUARE        3
#define PSP_BUTTON_LEFT_TRIGGER  4
#define PSP_BUTTON_RIGHT_TRIGGER 5
#define PSP_BUTTON_SELECT        10
#define PSP_BUTTON_START         11
#define PSP_BUTTON_HOME          12
#define PSP_BUTTON_HOLD          13
#endif

typedef void (*ButtonProc)(int key);
typedef void (*AnalogProc)(unsigned char analog_x,unsigned char analog_y);
#endif

#ifndef NGE_PSP
#define NGE_INPUT_MOUSE_SUPPORT
// ��iphone��android���ô�����ģ�����
// ��ָ�뿪ΪMOUSE_LBUTTON_UP������ΪMOUSE_LBUTTON_DOWN���������ƶ�ΪMouseMove
typedef void (*MouseMoveProc)(int x,int y);
typedef void (*MouseButtonProc)(int type,int x,int y);
#define MOUSE_LBUTTON_DOWN 1
#define MOUSE_LBUTTON_UP   2
#if defined NGE_WIN || defined NGE_LINUX
#define NGE_INPUT_MOUSE_FULL_SUPPORT
#define MOUSE_RBUTTON_DOWN 3
#define MOUSE_RBUTTON_UP   4
#define MOUSE_MBUTTON_DOWN 5
#define MOUSE_MBUTTON_UP   6
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef NGE_INPUT_BUTTON_SUPPORT
/**
 *��ʼ������ϵͳ
 *@param[in] downproc �������µĴ�����Ϣ����
 *@param[in] upproc �����ͷŵĴ�����Ϣ����
 *@param[in] doneflag �Ƿ����д����˳���Ϣ(HOME������ʱ),0(��),1(��)
 *@return ��
 */
	NGE_API void InitInput(ButtonProc downproc,ButtonProc upproc,int doneflag);
#endif

#ifdef NGE_INPUT_ANALOG_SUPPORT
/**
 *��ʼ��ҡ��
 *@param[in] AnalogProc ҡ�˵Ļص�����
 *@return ��
 */
	NGE_API void InitAnalog(AnalogProc analogproc);
#endif

#ifdef NGE_INPUT_MOUSE_SUPPORT
/**
 *��ʼ��mouse-touch
 *@param[in] mouse_btn ��굥���Ļص�����
 *@param[in] mouse_move ����ƶ��Ļص�����
 */
	NGE_API void InitMouse(MouseButtonProc mouse_btn,MouseMoveProc mouse_move);
	NGE_API void EmulateTouchMove(int flag);
#endif
/**
 *���������x,yֵ
 *@param[in] flag �Ƿ񽻻�,0Ϊ������,1Ϊ����
 */
	NGE_API void SetSwapXY(int flag);

#if !defined NGE_IPHONE || !defined NGE_ANDROID
#define NGE_INPUT_HAS_PROC
/**
 *������Ӧ,����ʹ���뿴����test/input_test.cpp
 *@return ��
 */
	NGE_API void InputProc();
#endif

/**
 *�˳�����ϵͳ
 *@return ��
 */
#define FiniInput()

#ifdef __cplusplus
}
#endif

#endif /* _NGE_INPUT_H */
