/***************************************************************************
 *            nge_bmp.h
 *
 *  2011/03/25 04:54:17
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

#ifndef _NGE_BMP_H
#define _NGE_BMP_H

#include "nge_common.h"
#include "nge_image.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *����bmpͼƬ,���ļ�����
 *@param[in] filename ͼƬ�ļ���
 *@param[in] displaymode ��ʾģʽ,(DISPLAY_PIXEL_FORMAT_XXX��һ��)
 *@return image_p,����0(����ʧ��),����ͼƬ���˽ṹ
 */
	NGE_API image_p image_load_bmp(const char* filename, int displaymode);
/**
 *����bmpͼƬ,���ڴ����
 *@param[in] mbuf �ڴ��ַ
 *@param[in] bsize ����buffer��С
 *@param[in] displaymode ��ʾģʽ,(DISPLAY_PIXEL_FORMAT_XXX��һ��)
 *@return image_p,����0(����ʧ��),����ͼƬ���˽ṹ
 */
	NGE_API image_p image_load_bmp_buf(const char* mbuf,int bsize, int displaymode);
/**
 *����bmpͼƬ,���ļ�ָ�����
 *@param[in] handle �ļ�ָ��
 *@param[in] fsize �����ļ���С
 *@param[in] autoclose �Ƿ�ر��ļ�,0���ر�,1�ر�
 *@param[in] displaymode ��ʾģʽ,(DISPLAY_PIXEL_FORMAT_XXX��һ��)
 *@return image_p,����0(����ʧ��),����ͼƬ���˽ṹ
 */
	NGE_API image_p image_load_bmp_fp(int handle,int fsize, int autoclose,int displaymode);
/**
 * ͬimage_load_bmp����,ֻ�Ƕ���һ�����ùؼ�ɫ,colorkey��MAKE_RGB�趨
 *@param[in] filename ͼƬ�ļ���
 *@param[in] displaymode ��ʾģʽ,(DISPLAY_PIXEL_FORMAT_XXX��һ��)
 *@param[in] colorkey �ؼ�ɫ,��MAKE_RGB�趨
 *@return image_p,����ͼƬ���˽ṹ
 */
	NGE_API image_p image_load_bmp_colorkey(const char* filename, int displaymode,int colorkey);
/**
 * ͬimage_load_bmp_buf����,ֻ�Ƕ���һ�����ùؼ�ɫ,colorkey��MAKE_RGB�趨
 *@param[in] mbuf �ڴ��ַ
 *@param[in] bsize ����buffer��С
 *@param[in] displaymode ��ʾģʽ,(DISPLAY_PIXEL_FORMAT_XXX��һ��)
 *@param[in] colorkey �ؼ�ɫ,��MAKE_RGB�趨
 *@return image_p,����0(����ʧ��),����ͼƬ���˽ṹ
 */
	NGE_API image_p image_load_bmp_colorkey_buf(const char* mbuf,int bsize, int displaymode,int colorkey);
/**
 * ͬimage_load_bmp_fp����,ֻ�Ƕ���һ�����ùؼ�ɫ,colorkey��MAKE_RGB�趨
 *@param[in] handle �ļ�ָ��
 *@param[in] fsize �����ļ���С
 *@param[in] autoclose �Ƿ�ر��ļ�,0���ر�,1�ر�
 *@param[in] displaymode ��ʾģʽ,(DISPLAY_PIXEL_FORMAT_XXX��һ��)
 *@param[in] colorkey �ؼ�ɫ,��MAKE_RGB�趨
 *@return image_p,����0(����ʧ��),����ͼƬ���˽ṹ
 */
	NGE_API image_p image_load_bmp_colorkey_fp(int handle,int fsize, int autoclose,int displaymode,int colorkey);

#ifdef __cplusplus
}
#endif

#endif /* _NGE_BMP_H */
