/***************************************************************************
 *            nge_tga.h
 *
 *  2011/03/25 05:05:01
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

#ifndef _NGE_TGA_H
#define _NGE_TGA_H

#include "nge_common.h"
#include "nge_image.h"

// ImageType Codes
#define TGA_TYPE_MAPPED		1
#define TGA_TYPE_COLOR		2
#define TGA_TYPE_GRAY		3
#define TGA_TYPE_MAPPED_RLE	9
#define TGA_TYPE_COLOR_RLE	10
#define TGA_TYPE_GRAY_RLE	11

/* Image descriptor:
   3-0: attribute (alpha) bpp
   4:   left-to-right ordering
   5:   top-to-bottom ordering
   7-6: zero
*/
// Image Description Bitmasks
#define TGA_DESC_ABITS		0x0f			// Alpha Bits
#define TGA_DESC_HORIZONTAL	0x10			// Left-Right Ordering: 0 = left to right, 1 = right to left
#define TGA_DESC_VERTICAL	0x20			// Top-Bottom Ordering: 0 = bottom to top, 1 = top to bottom

#pragma pack(push, 1)
typedef struct {
    uint8_t	ImageIDSize;
    uint8_t	ColorMapType;
    uint8_t	ImageTypeCode;                          // Image Type (normal/paletted/grayscale/rle)
    uint8_t	ColorMapOrigin[2];
    uint8_t	ColorMapLength[2];                      // Palette Size
    uint8_t	ColorMapESize;							// Size in bits of one Palette entry
    uint8_t	OriginX[2];
    uint8_t	OriginY[2];
    uint8_t	Width[2];                               // Width of Image
    uint8_t	Height[2];                              // Height of Image
    uint8_t	Depth;                                  // Bits per Pixel of Image
    uint8_t	ImageDescrip;
} TGAFILEHEADER;
#pragma pack(pop)

#ifdef __cplusplus
extern "C" {
#endif

/**
 *����tgaͼƬ,���ļ�����
 *@param[in] filename ͼƬ�ļ���
 *@param[in] displaymode ��ʾģʽ,(DISPLAY_PIXEL_FORMAT_XXX��һ��)
 *@return image_p,����0(����ʧ��),����ͼƬ���˽ṹ
 */
	NGE_API image_p image_load_tga(const char* filename, int displaymode);

/**
 *����tgaͼƬ,���ڴ����
 *@param[in] mbuf �ڴ��ַ
 *@param[in] bsize ����buffer��С
 *@param[in] displaymode ��ʾģʽ,(DISPLAY_PIXEL_FORMAT_XXX��һ��)
 *@return image_p,����0(����ʧ��),����ͼƬ���˽ṹ
 */
	NGE_API image_p image_load_tga_buf(const char* mbuf,int bsize, int displaymode);

/**
 *����tgaͼƬ,���ļ�ָ�����
 *@param[in] handle �ļ�ָ��
 *@param[in] fsize �����ļ���С
 *@param[in] autoclose �Ƿ�ر��ļ�,�Ƿ�ر��ļ�,0���ر�,1�ر�
 *@param[in] displaymode ��ʾģʽ,(DISPLAY_PIXEL_FORMAT_XXX��һ��)
 *@return image_p,����0(����ʧ��),����ͼƬ���˽ṹ
 */
	NGE_API image_p image_load_tga_fp(int handle,int fsize, int autoclose,int displaymode);

/**
 * ͬimage_load_tga����,ֻ�Ƕ���һ�����ùؼ�ɫ,colorkey��MAKE_RGB�趨
 *@see image_load_tga
 *@param[in] filename ͼƬ�ļ���
 *@param[in] displaymode ��ʾģʽ,(DISPLAY_PIXEL_FORMAT_XXX��һ��)
 *@param[in] colorkey �ؼ�ɫ,��MAKE_RGB�趨
 *@return image_p,����ͼƬ���˽ṹ
 */
	NGE_API image_p image_load_tga_colorkey(const char* filename, int displaymode,int colorkey);

/**
 * ͬimage_load_tga_buf����,ֻ�Ƕ���һ�����ùؼ�ɫ,colorkey��MAKE_RGB�趨
 *@see image_load_tga_buf
 *@param[in] mbuf �ڴ��ַ
 *@param[in] bsize ����buffer��С
 *@param[in] displaymode ��ʾģʽ,(DISPLAY_PIXEL_FORMAT_XXX��һ��)
 *@param[in] colorkey �ؼ�ɫ,��MAKE_RGB�趨
 *@return image_p,����0(����ʧ��),����ͼƬ���˽ṹ
 */
	NGE_API image_p image_load_tga_colorkey_buf(const char* mbuf,int bsize, int displaymode,int colorkey);

/**
 * ͬimage_load_png_fp����,ֻ�Ƕ���һ�����ùؼ�ɫ,colorkey��MAKE_RGB�趨
 *@see image_load_png_fp
 *@param[in] handle �ļ�ָ��
 *@param[in] fsize �����ļ���С
 *@param[in] autoclose �Ƿ�ر��ļ�,0���ر�,1�ر�
 *@param[in] displaymode ��ʾģʽ,(DISPLAY_PIXEL_FORMAT_XXX��һ��)
 *@param[in] colorkey �ؼ�ɫ,��MAKE_RGB�趨
 *@return image_p,����0(����ʧ��),����ͼƬ���˽ṹ
 */
	NGE_API image_p image_load_tga_colorkey_fp(int handle,int fsize, int autoclose,int displaymode,int colorkey);

/**
 *�洢tgaͼƬ,��image_p�ṹ���ݴ洢Ϊtga�ļ�
 *@param[in] pimage image_p�ṹָ��,���汣��Ϊimage_t������
 *@param[in] filename �����ļ���
 *@param[in] alpha �Ƿ񱣴�Ϊ��alphaͨ����ͼƬ
 *@param[in] rle �Ƿ����rle����ѹ��
 *@return int,����0(����ʧ��)��1(���سɹ�)
 */
	NGE_API int image_save_tga(image_p pimage,const char* filename,uint8_t alpha,uint8_t rle);

#ifdef __cplusplus
}
#endif

#endif /* _NGE_TGA_H */
