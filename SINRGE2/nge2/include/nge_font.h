#ifndef NGE_FONT_H_
#define NGE_FONT_H_

#include "nge_common.h"
#include "nge_image.h"

//show flags
#define FONT_SHOW_NORMAL   0
#define FONT_SHOW_SHADOW   1

#define NGE_ENCODING_GBK   0
#define NGE_ENCODING_UTF_8 1

enum{
	SET_ATTR_FIXWIDTH = 0,
	SET_ATTR_BOLD,
	SET_ATTR_NOBOLD,
	SET_ATTR_ITALICS,
	SET_ATTR_NOITALICS,
	SET_ATTR_MARGIN,
	SET_ATTR_SIZE
};

typedef struct _pfont *PFont;

#ifdef __cplusplus
extern "C"{
#endif

/**
 *��������ϵͳ��ǰ�ı���
 *@param[in] encoding ����ֵ(��NGE_ENCODING_GBK��NGE_ENCODING_UTF_8)
 */
	NGE_API void NGE_SetFontEncoding(uint8_t encoding);

/**
 *����һ��GBK(hzk)font,Ĭ��ΪGBK�ĵ���
 *@param[in] cname �����ֿ�ͨ����GBKxx
 *@param[in] aname Ӣ���ֿ�ͨ����ASCxx
 *@param[in] height �߶�,�����ֿ�ΪGBK16,�������16
 *@param[in] disp ��ʾģʽ,4����ʾģʽ֮һ,�Ƽ�ʹ��5551,4444
 *@return PFont,����fontָ��
 */
	NGE_API PFont create_font_hzk(const char* cname,const char* aname, int height,int disp);

/**
 *��һ���ڴ�buf�ϴ���һ��GBK(hzk)font,Ĭ��ΪGBK�ĵ���
 *@param[in] *cfbuf �����ֿ�bufͨ����GBKxx
 *@param[in] csize ����buf�Ĵ�С
 *@param[in] *afbuf �����ֿ�cbufͨ����ASCxx
 *@param[in] asize ����abuf�Ĵ�С
 *@param[in] height �߶�,�����ֿ�ΪGBK16,�������16
 *@param[in] disp ��ʾģʽ,4����ʾģʽ֮һ,�Ƽ�ʹ��5551,4444
 *@return PFont,����fontָ��
 */
	NGE_API PFont create_font_hzk_buf(const char *cfbuf,int csize,const char* afbuf,int asize, int height,int disp);

/**
 *����һ��ttf(freetype)font
 *@param[in] ttfname freetype�ļ���
 *@param[in] height �߶�����
 *@param[in] disp ��ʾģʽ,4����ʾģʽ֮һ,�Ƽ�ʹ��8888,4444
 *@return PFont,����fontָ��
 */
	NGE_API PFont create_font_freetype(const char* ttfname, int height,int disp);

/**
 *��һ���ڴ�buf�ϴ���һ��ttf(freetype)font
 *@param[in] *cfbuf freetype���ڴ�buf
 *@param[in] csize freetype���ڴ�buf
 *@param[in] height �߶�����
 *@param[in] disp ��ʾģʽ,4����ʾģʽ֮һ,�Ƽ�ʹ��8888,4444
 *@return PFont,����fontָ��
 */
	NGE_API PFont create_font_freetype_buf(const char *cfbuf,int csize, int height,int disp);

/**
 *����һ��nfont
 *@param[in] name nfont�ļ���
 *@param[in] disp ��ʾģʽ,4����ʾģʽ֮һ,�Ƽ�ʹ��8888,4444
 *@return PFont,����fontָ��
 */
	NGE_API PFont create_font_nfont(const char* name,int disp);

/**
 *��һ���ڴ�buf�ϴ���һ��nfont
 *@param[in] *nfbuf nfont���ڴ�buf
 *@param[in] nsize buf�ĳ���
 *@param[in] disp ��ʾģʽ,4����ʾģʽ֮һ,�Ƽ�ʹ��8888,4444
 *@return PFont,����fontָ��
 */
	NGE_API PFont create_font_nfont_buf(const char *nfbuf,int nsize,int disp);

/**
 * ��ʾһ���ֵ��ڴ�ͼtextarea,ע�������create_image�����ڴ�ͼtextarea
 *@param[in] pf ����ָ��,��create_font_xxx����
 *@param[in] text ��ʾ������
 *@param[in] len ��ʾ���ֵĳ���,��strlen����
 *@param[in, out] textarea �ڴ�ͼtextarea
 *@param[in] dx �������ڴ�ͼ��xλ������
 *@param[in] dy �������ڴ�ͼ��yλ������
 *@param[in] flags ��ʾ��־,Ŀǰֻ��0(����),1(��Ӱ)
 *@return ��
 */
	NGE_API void font_drawtext(PFont pf,const char* text,int len,image_p textarea,int dx,int dy,int flags);
/**
 *�������������
 *@param[in, out] pf ����ָ��
 *@param[in] attr ����ֵ
 *@param[in] setflag ��Ҫ���õ����Ա�־
 *@return ��
 */
	NGE_API void font_setattr(PFont pf,int attr,int setflag);
/**
 *�ͷ�һ������
 *@param[in] pf ���ͷŵ�����ָ��
 *@return ��
 */
	NGE_API void font_destory(PFont pf);
/**
 *����������ɫ
 *@param[in, out] pf ����ָ��
 *@param[in] color ������ɫ����ɫֵ�뽨�������dtype��Ӧ,���罨����16λ5551,�������MAKE_RGBA5551����
 *@return int,��һ����ɫ
 */
	NGE_API int font_setcolor(PFont pf,uint32_t color);
/**
 *��ǿ������������ɫ,��֧�ֶ���
 *@param[in, out] pfont ����ָ��
 *@param[in] color_fg ǰ��ɫ(������ɫ)����ɫֵ�뽨�������dtype��Ӧ,���罨����16λ5551,�������MAKE_RGBA5551����
 *@param[in] color_bg ����ɫ����ɫֵ�뽨�������dtype��Ӧ
 *@param[in] color_sh ������Ӱɫ����ɫֵ�뽨�������dtype��Ӧ
 *@return ��
 */
	NGE_API void font_setcolor_ex(PFont pfont, uint32_t color_fg,uint32_t color_bg ,uint32_t color_sh );
/**
 *�õ�һ�����ֵķ�Χ
 *@param[in] pfont ����ָ��
 *@param[in] *text ����ָ��
 *@param[in] cc ���ֳ���
 *@param[out] *pwidth  ��
 *@param[out] *pheight ��
 *@param[out] *pbase   ����
 *@return ��
 */
	NGE_API void font_textsize(PFont pfont, const void *text, int cc,int *pwidth, int *pheight,int *pbase);

#ifdef __cplusplus
}
#endif


#endif
