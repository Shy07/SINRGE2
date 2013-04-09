#ifndef __SIN_BITMAP_H__
#define __SIN_BITMAP_H__

#ifdef WIN32
#pragma once
#endif

#include "SINRGE2.h"

typedef struct tagBitmap{
	hgeQuad		quad;
	int			width;    /**< ͼƬԭ�� */
	int			height;   /**< ͼƬԭ�� */
	int			texw;     /**< ͼƬ��ͼ�� */
	int			texh;     /**< ͼƬ��ͼ�� */
	float		rcentrex; /**< ͼ������x */
	float		rcentrey; /**< ͼ������y */
}bitmap_t, *bitmap_p;

#endif //__SIN_BITMAP_H__