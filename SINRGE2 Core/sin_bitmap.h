/*
** SINRGE2
** Copyright (C) 2013 Shy07
** Gernischt@gmail.com
**
** SINRGE2 Bitmap Header
*/
#ifndef __SIN_BITMAP_H__
#define __SIN_BITMAP_H__

#ifdef WIN32
#pragma once
#endif

#include "hge.h"

typedef struct tagBitmap
{
	hgeQuad		quad;
	int			width;	/**< ͼƬ��ͼ�� */
	int			height;	/**< ͼƬ��ͼ�� */
	int			owidth;    /**< ͼƬԭ�� */
	int			oheight;   /**< ͼƬԭ�� */
	//float		rcentrex; /**< ͼ������x */
	//float		rcentrey; /**< ͼ������y */
} bitmap_t, *bitmap_p;

#endif //__SIN_BITMAP_H__