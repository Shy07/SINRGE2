/***************************************************************************
 *            nge_image.h
 *
 *  2011/03/25 04:56:54
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

#ifndef _NGE_IMAGE_H
#define _NGE_IMAGE_H

#include "nge_common.h"
#include "nge_color.h"

#define IMAGE_FLIP_H 1
#define IMAGE_FLIP_V 2

typedef struct tagImage{
	uint32_t  w;        /**< ͼƬԭ�� */
	uint32_t  h;        /**< ͼƬԭ�� */
	uint32_t  texw;     /**< ͼƬ��ͼ�� */
	uint32_t  texh;     /**< ͼƬ��ͼ�� */
	uint8_t   bpb;      /**< ÿ�����ֽ���(16λ2�ֽ�,32λ4�ֽ�) */
	uint8_t   swizzle;  /**< �Ƿ��data swizzle �Ż�*/
	uint32_t  mode;     /**< GSM��ʾmode for psp */
	uint32_t  dtype;    /**< ��ʾģʽ(DISPLAY_PIXEL_FORMAT_XXX��һ��) */
	uint8_t*  data;     /**< ͼ������ */
	float   rcentrex; /**< ͼ������x */
	float   rcentrey; /**< ͼ������y */
	uint32_t  texid;    /**< ͼ��id */
	uint8_t   modified; /**< ǿ�Ƹ����Դ�*/
	uint8_t   dontswizzle; /**ǿ�Ʋ�swizzle �Ż�*/
	int     mask;     /**< ��ɫ����,������ʾ����Ч��*/
	uint8_t   filter;   /**< FILTER_NEAREST,FILTER_LINEAR(default) */
}image_t,*image_p;

extern uint32_t image_tid;

#ifdef __cplusplus
extern "C" {
#endif

/**
 *����ͼƬ,���ļ�����
 *@param[in] filename ͼƬ�ļ���
 *@param[in] displaymode ��ʾģʽ,(DISPLAY_PIXEL_FORMAT_XXX��һ��)
 *@param[in] swizzle �Ƿ����Ż�,��0�����Ż�,ͨ����1
 *@return image_p,����0(����ʧ��),����ͼƬ���˽ṹ
 */
	NGE_API image_p image_load(const char* filename, int displaymode,int swizzle);

/**
 *����ͼƬ,���ڴ����
 *@param[in] mbuf �ڴ��ַ
 *@param[in] bsize ����buffer��С
 *@param[in] displaymode ��ʾģʽ,(DISPLAY_PIXEL_FORMAT_XXX��һ��)
 *@param[in] swizzle �Ƿ����Ż�,��0�����Ż�,ͨ����1
 *@return image_p,����0(����ʧ��),����ͼƬ���˽ṹ
 */
	NGE_API image_p image_load_buf(const char* mbuf,int bsize, int displaymode,int swizzle);

/**
 *����ͼƬ,���ļ�ָ�����
 *@param[in] handle �ļ�ָ��
 *@param[in] fsize �����ļ���С
 *@param[in] autoclose �Ƿ�ر��ļ�,�Ƿ�ر��ļ�,0���ر�,1�ر�
 *@param[in] displaymode ��ʾģʽ,(DISPLAY_PIXEL_FORMAT_XXX��һ��)
 *@param[in] swizzle �Ƿ����Ż�,��0�����Ż�,ͨ����1
 *@return image_p,����0(����ʧ��),����ͼƬ���˽ṹ
 */
	NGE_API image_p image_load_fp(int handle,int fsize, int autoclose,int displaymode,int swizzle);

/**
 * ͬimage_load����,ֻ�Ƕ���һ�����ùؼ�ɫ,colorkey��MAKE_RGB�趨
 *@param[in] filename ͼƬ�ļ���
 *@param[in] displaymode ��ʾģʽ,(DISPLAY_PIXEL_FORMAT_XXX��һ��)
 *@param[in] colorkey �ؼ�ɫ,��MAKE_RGB�趨
 *@param[in] swizzle �Ƿ����Ż�,��0�����Ż�,ͨ����1
 *@return image_p,����0(����ʧ��),����ͼƬ���˽ṹ
 */
	NGE_API image_p image_load_colorkey(const char* filename, int displaymode,int colorkey,int swizzle);

/**
 * ͬimage_load_buf����,ֻ�Ƕ���һ�����ùؼ�ɫ,colorkey��MAKE_RGB�趨
 *@param[in] mbuf �ڴ��ַ
 *@param[in] bsize ����buffer��С
 *@param[in] displaymode ��ʾģʽ,(DISPLAY_PIXEL_FORMAT_XXX��һ��)
 *@param[in] colorkey �ؼ�ɫ,��MAKE_RGB�趨
 *@param[in] swizzle �Ƿ����Ż�,��0�����Ż�,ͨ����1
 *@return image_p,����0(����ʧ��),����ͼƬ���˽ṹ
 */
	NGE_API image_p image_load_colorkey_buf(const char* mbuf,int bsize, int displaymode,int colorkey,int swizzle);

/**
 *����һ��image�ṹ,��ʾģʽ��displaymode
 *@param[in] w image�Ŀ�
 *@param[in] h image�ĸ�
 *@param[in] displaymode ��ʾģʽ,(DISPLAY_PIXEL_FORMAT_XXX��һ��)
 *@return image_p,����imageָ��
 */
	NGE_API image_p image_create(int w,int h,int displaymode);

/**
 *����һ��image�ṹ,��ʾģʽ��displaymode
 *@param[in] w image�Ŀ�
 *@param[in] h image�ĸ�
 *@param[in] color ��ɫ,Ϊ��֤����������MAKE_RGBA_XXXX���������ɫ
 *@param[in] displaymode ��ʾģʽ,����ɫһ��,(DISPLAY_PIXEL_FORMAT_XXX��һ��)
 *@return image_p,����imageָ��
 */
	NGE_API image_p image_create_ex(int w,int h,int color,int displaymode);

/**
 *��image���棬�����ļ����жϱ���ĸ�ʽ��Ŀǰ֧��png��tga��ʽ
 *@param[in] pimage �������imageָ��
 *@param[in] filename ������ļ���
 *@param[in] alpha �Ƿ񱣴�Ϊ��alphaͨ����ͼƬ
 *@param[in] rle �Ƿ񱣴�Ϊrleѹ����ʽ��ͼƬ
 *@return int,����0(����ʧ��)��1(���سɹ�)
 */
	NGE_API int image_save(image_p pimage,const char* filename,uint8_t alpha,uint8_t rle);

/**
 *�ͷ�һ��image
 *@param[in] pimage ���ͷŵ�imageָ��
 *@return void,�޷���
 */
	NGE_API void image_free(image_p pimage);

/**
 *cloneһ��image,����image_p����һ��pimage�����
 *@param[in] pimage ��clone��imageָ��
 *@return image_p,pimage�����
 */
	NGE_API image_p image_clone(image_p pimage);

/**
 *���������,ͼ���Ϊ��ɫ͸��
 *@param[in, out] pimage �������imageָ��
 *@return void,�޷���
 */
	NGE_API void image_clear(image_p pimage);

/**
 *��Դimage_p src������image_p des.
 *@remark ע��˺���ͨ��ֻ������������ʹ��,ͨ��ֱ����DrawImage��screen��Ӳ������.
 *@param[in] src Դ�ڴ�ͼ
 *@param[in, out] des Ŀ���ڴ�ͼ
 *@param[in] dx Ŀ���ڴ�ͼ��x����
 *@param[in] dy Ŀ���ڴ�ͼ��y����
 *@return ��
 */
	NGE_API void image_to_image(const image_p src,const image_p des,int32_t dx,int32_t dy);

/**
 *��Դimage_p src��sx,sh,sw,sh������image_p des.
 *@remark ע��˺���ͨ��ֻ������������ʹ��,ͨ��ֱ����DrawImage��screen��Ӳ������.
 *@param[in] src Դ�ڴ�ͼ
 *@param[in, out] des Ŀ���ڴ�ͼ
 *@param[in] sx Դ�ڴ�ͼ��x����
 *@param[in] sy Դ�ڴ�ͼ��y����
 *@param[in] sw Դ�ڴ�ͼ�Ŀ�
 *@param[in] sh Դ�ڴ�ͼ�ĸ�
 *@param[in] dx Ŀ���ڴ�ͼ��x����
 *@param[in] dy Ŀ���ڴ�ͼ��y����
 *@param[in] flag ��ת��־,IMAGE_FLIP_H��ʾ��Դͼ����ˮƽ��ת,IMAGE_FLIP_V��ʾ��Դͼ����ֱ��ת,������|����,����ת����0
 *@return ��
 */
	NGE_API void image_to_image_ex(const image_p src,const image_p des,int32_t sx,int32_t sy,int32_t sw,int32_t sh,int32_t dx,int32_t dy,int flag);

/**
 *��Դimage_p src������image_p des ��alpha���.
 *@remark ע��˺���ͨ��ֻ������������ʹ��,ͨ��ֱ����DrawImage��screen��Ӳ������.
 *@param[in] src Դ�ڴ�ͼ
 *@param[in, out] des Ŀ���ڴ�ͼ
 *@param[in] dx Ŀ���ڴ�ͼ��x����
 *@param[in] dy Ŀ���ڴ�ͼ��y����
 *@param[in] alpha alpha���ֵ,0-255(͸��->��͸��),����128���ǰ�͸��
 *@return ��
 */
	NGE_API void image_to_image_alpha(const image_p src,const image_p des,int32_t dx,int32_t dy,int alpha);

/**
 *��Դimage_p src��sx,sh,sw,sh������image_p des.
 *@remark ע��˺���ͨ��ֻ������������ʹ��,ͨ��ֱ����DrawImage��screen��Ӳ������.
 *@param[in] src Դ�ڴ�ͼ
 *@param[in, out] des Ŀ���ڴ�ͼ
 *@param[in] sx Դ�ڴ�ͼ��x����
 *@param[in] sy Դ�ڴ�ͼ��y����
 *@param[in] sw Դ�ڴ�ͼ�Ŀ�
 *@param[in] sh Դ�ڴ�ͼ�ĸ�
 *@param[in] dx Ŀ���ڴ�ͼ��x����
 *@param[in] dy Ŀ���ڴ�ͼ��y����
 *@param[in] alpha alpha���ֵ,0-255(͸��->��͸��),����128���ǰ�͸��
 *@param[in] flag ��ת��־,IMAGE_FLIP_H��ʾ��Դͼ����ˮƽ��ת,IMAGE_FLIP_V��ʾ��Դͼ����ֱ��ת,������|����,����ת����0
 *@return ��
 */
	NGE_API void image_to_image_alpha_ex(const image_p src,const image_p des,int32_t sx,int32_t sy,int32_t sw,int32_t sh,int32_t dx,int32_t dy,int alpha,int flag);

/**
 *��ԭʼλͼ��ʽ���ݿ�����image,���ǵ�Ч������,ֻ֧��ͬ��displaymode,
 *@remark ע��˴�δ���ж�,������Ҫ��֤data������ȷ��
 *@param[in] data λͼ����
 *@param[in, out] des imageָ��,Ŀ��image
 *@param[in] x ������image�ϵ�dxλ��
 *@param[in] y ������image�ϵ�dyλ��
 *@param[in] w data��w
 *@param[in] h data��h
 *@return void,�޷���
 */
	NGE_API void rawdata_to_image(void* data,const image_p des,int32_t x,int32_t y,int32_t w,int32_t h);

/**
 * ��ͼ����ˮƽ��ת��ͼ������x����
 *@param[in, out] pimage ����תͼ��
 *@return int,�ɹ�1,ʧ��0
 */
	NGE_API int image_fliph(image_p pimage);

/**
 * ��ͼ������ֱ��ת����ת��x��Գ�
 *@param[in, out] pimage ����תͼ��
 *@return int,�ɹ�1,ʧ��0
 */
	NGE_API int image_flipv(image_p pimage);

/**
 * ���ͼƬ��һ���������
 * @param[in] pimage Դͼ��
 * @param[in] x ���������ϽǾ���߾���
 * @param[in] y ���������ϽǾ��ϱ߾���
 * @param[in] w �����ο�
 * @param[in] h �����θ�
 * @param[in] color Ҫ������ɫ
 * @return ��
 */
	NGE_API void image_fillrect(image_p pimage, int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color);

//���º���Ϊ�ڲ�ʹ��
int GET_PSM_COLOR_MODE(int dtype);
int roundpower2(int width);

#ifdef NGE_PSP
void swizzle_swap(image_p pimage);
void unswizzle_swap(image_p pimage);
#else
#define swizzle_swap(p)
#define unswizzle_swap(p)
#endif

#define CHECK_AND_UNSWIZZLE(img)				\
	if(img->swizzle ==1) {						\
		unswizzle_swap(img);					\
	}

#define CHECK_AND_SWIZZLE(img)					\
	if(img->swizzle ==1) {						\
		swizzle_swap(img);						\
	}

#define CHECK_AND_UNSWIZZLE_ALL(src, des)		\
	CHECK_AND_UNSWIZZLE(src);					\
	CHECK_AND_UNSWIZZLE(des)

#ifdef __cplusplus
}
#endif

#endif /* _NGE_IMAGE_H */
