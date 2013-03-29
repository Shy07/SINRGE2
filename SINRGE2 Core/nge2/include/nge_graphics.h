#ifndef NGE_GRAPHICS_H_
#define NGE_GRAPHICS_H_

#include "nge_common.h"
#include "nge_platform.h"

#ifdef NGE_WIN
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include "nge_image.h"

#define SCREEN_WIDTH_PSP  480
#define SCREEN_HEIGHT_PSP 272

#define SCREEN_WIDTH_IPHONE  320
#define SCREEN_HEIGHT_IPHONE 480

#define SCREEN_WIDTH_ANDROID  240
#define SCREEN_HEIGHT_ANDROID 320

#ifdef NGE_IPHONEOS
#define	SCREEN_WIDTH  SCREEN_WIDTH_IPHONE
#define	SCREEN_HEIGHT SCREEN_HEIGHT_IPHONE
#elif defined NGE_ANDROID
#define	SCREEN_WIDTH  SCREEN_WIDTH_ANDROID
#define	SCREEN_HEIGHT SCREEN_HEIGHT_ANDROID
#else
#define	SCREEN_WIDTH  SCREEN_WIDTH_PSP
#define	SCREEN_HEIGHT SCREEN_HEIGHT_PSP
#endif

#define SCREEN_BPP    32
#define DEFAULT_FPS 60


//we merge *_Trans to Java like function DrawRegion.

#define INVERTED_AXES	 0x4

//sprite transform type
enum TRANS_TYPE{
	TRANS_NONE		    = 0,	//�޷�ת
	TRANS_ROT90		    = 5,	//˳ʱ����ת90
	TRANS_ROT180		= 3,	//˳ʱ����ת180
	TRANS_ROT270		= 6,	//˳ʱ����ת270
	TRANS_MIRROR		= 2,	//FLIPX
	TRANS_MIRROR_ROT90	= 7,	//��ʱ����ת90 ����
	TRANS_MIRROR_ROT180	= 1,	//FLIPY
	TRANS_MIRROR_ROT270	= 4,	//��ʱ����ת270 ����
};

enum ANCHOR_TYPE{
	ANCHOR_SOLID		= 0,
	ANCHOR_HCENTER		= 0x1,		//1
	ANCHOR_VCENTER		= 0x2,		//2
	ANCHOR_LEFT		    = 0x4,		//4
	ANCHOR_RIGHT		= 0x8,		//8
	ANCHOR_TOP		    = 0x10,		//16
	ANCHOR_BOTTOM		= 0x20,		//32
	ANCHOR_BASELINE		= 0x40,		//64
};

/* note: bpp and fullscreen are not used on windows at current */
typedef struct {
	char *name;
	int width;
	int height;
	int bpp;
	int fullscreen;

	int ori_width;
	int ori_height;
	float rate_w;
	float rate_h;
	char  pathname[256];
}screen_context_t, *screen_context_p;

typedef struct{
	float x;
	float y;
} pointf;

typedef struct
{
	float u, v;
	uint32_t color;
	float x,y,z;
}vertexf;

typedef struct{
	vertexf v[4];
	image_p tex;
}quadf;

typedef struct{
	float top;
	float left;
	float right;
	float bottom;
} rectf;

#ifdef __cplusplus
extern "C"{
#endif

/**
 *�õ���Ļ��Ϣ
 *@return ��Ļ��Ϣ
 */
	NGE_API screen_context_p GetScreenContext();

#ifdef NGE_WIN
	//NGE_API void SetNGEhInstance(HINSTANCE hInstance);
	//NGE_API void SetNGEhWnd(HWND m_hWnd);
	NGE_API HWND GetNGEhWnd();
#endif
/**
 * ��ʼ������,��nge2ϵͳ����,�û�������ʽ����
 */
	NGE_API void InitGraphics();
/**
 * ��������,��nge2ϵͳ����,�û�������ʽ����
 */
	NGE_API void FiniGraphics();
/**
 * ��Ļ���ƿ�ʼ����,���л��Ƶ���Ļ����BeginScene,EndScene֮�����
 *@param[in] clear ������־��Ĭ��Ϊ1����
 *@return ��
 */
	NGE_API void BeginScene(uint8_t clear);
/**
 * ��Ļ���ƽ�������,���л��Ƶ���Ļ����BeginScene,EndScene֮�����
 *@return ��
 */
	NGE_API void EndScene();

/**
 * ���Ƶ�ͼƬ��ʼ����,���л��Ƶ�ͼƬ����BeginTarget,EndTarget֮�����
 *@param[in] _img ��Ҫ���Ƶ���ͼƬ
 *@param[in] clear �Ƿ����ԭ����Ϣ,1Ϊ����,0Ϊ������
 *@return ��
 *@remark �˲�������ʹTexBlendEquation��Ϊ��ɫFUNC_ADD,͸����FUNC_MAX,������Ҫ���ģ��������޸�
 */
	NGE_API BOOL BeginTarget(image_p _img,uint8_t clear);
/**
 * ���Ƶ�ͼƬ��������,���л��Ƶ�ͼƬ����BeginTarget,EndTarget֮�����
 *@return ��
 */
	NGE_API void EndTarget();

/**
 * �����Ƿ���ʾFPS�͵�����Ϣ
 *@return ��
 */
	NGE_API float GetRealFps();
	NGE_API void ShowFps();
/**
 * ����֡��
 *@param[in] fps,Ŀ��֡��
 *@return ��
 */
	NGE_API void LimitFps(uint32_t fps);
/**
 * ���òü�������Ŀ�������ڵĲ���ʾ��ͬJ2ME��SetClip
 *@param[in] x Ŀ������x����
 *@param[in] y Ŀ������y����
 *@param[in] w Ŀ������ü���width
 *@param[in] h Ŀ������ü���height
 *@return ��
 */
	NGE_API void SetClip(int x,int y,int w,int h);
/**
 * �����òü����򣬵�ͬ�ڵ���SetClip(0,0,SCREEN_WIDTH,SCREEN_HEIGHT)
 *@return ��
 */
	NGE_API void ResetClip();
/**
 * ���ߺ���1�����������
 *@param[in] x1 ��һ����x����
 *@param[in] y1 ��һ����y����
 *@param[in] x2 �ڶ�����x����
 *@param[in] y2 �ڶ�����y����
 *@param[in] color ��ɫ�������Ӧ�����������õ�5551���������MAKE_RGBA5551
 *@param[in] dtype ��ʾģʽ��������Ķ�Ӧ
 *@return ��
 */
	NGE_API void DrawLine(float x1, float y1, float x2, float y2, int color,int dtype);
/**
 * ���ߺ���2�����������pointf
 *@param[in] p1 ��һ����xy����
 *@param[in] p2 �ڶ�����xy����
 *@param[in] color ��ɫ�������Ӧ�����������õ�5551���������MAKE_RGBA5551
 *@param[in] dtype ��ʾģʽ��������Ķ�Ӧ
 *@return ��
 */
	NGE_API void DrawLineEx(pointf p1,pointf p2, int color,int dtype);
/**
 * �������߿�ĺ���1������Ϊλ�úͿ��
 *@param[in] dx �������Ͻǵ�x����
 *@param[in] dy �������Ͻǵ�y����
 *@param[in] width ���εĿ�
 *@param[in] height ���εĸ�
 *@param[in] color ��ɫ�������Ӧ�����������õ�5551���������MAKE_RGBA5551
 *@param[in] dtype ��ʾģʽ��������Ķ�Ӧ
 *@return ��
 */
	NGE_API void DrawRect(float dx, float dy, float width, float height,int color,int dtype);
/**
 * �������߿�ĺ���2������Ϊ����λ������
 *@param[in] rect ����λ������
 *@param[in] color ��ɫ�������Ӧ�����������õ�5551���������MAKE_RGBA5551
 *@param[in] dtype ��ʾģʽ��������Ķ�Ӧ
 *@return ��
 */
	NGE_API void DrawRectEx(rectf rect,int color,int dtype);
/**
 * �������εĺ���1������Ϊλ�úͿ��
 *@param[in] dx �������Ͻǵ�x����
 *@param[in] dy �������Ͻǵ�y����
 *@param[in] width ���εĿ�
 *@param[in] height ���εĸ�
 *@param[in] color ��ɫ�������Ӧ�����������õ�5551���������MAKE_RGBA5551
 *@param[in] dtype ��ʾģʽ��������Ķ�Ӧ
 *@return ��
 */
	NGE_API void NGE_FillRect(float dx, float dy, float width, float height,int color,int dtype);
#define FillRect NGE_FillRect
/**
 * �������εĺ���2������Ϊ����λ������
 *@param[in] rect ����λ������
 *@param[in] color ��ɫ�������Ӧ�����������õ�5551���������MAKE_RGBA5551
 *@param[in] dtype ��ʾģʽ��������Ķ�Ӧ
 *@return ��
 */
	NGE_API void FillRectEx(rectf rect,int color,int dtype);
/**
 * ����佥����εĺ���1������Ϊλ�úͿ��
 *@param[in] dx �������Ͻǵ�x����
 *@param[in] dy �������Ͻǵ�y����
 *@param[in] width ���εĿ�
 *@param[in] height ���εĸ�
 *@param[in] colors 4�������color,��ɫ�������Ӧ�����������õ�5551���������MAKE_RGBA5551
 *@param[in] dtype ��ʾģʽ��������Ķ�Ӧ
 *@return ��
 */
	NGE_API void FillRectGrad(float dx, float dy, float width, float height,int* colors,int dtype);
/**
 * �������εĺ���2������Ϊ����λ������
 *@param[in] rect ����λ������
 *@param[in] colors 4�������color,��ɫ�������Ӧ�����������õ�5551���������MAKE_RGBA5551
 *@param[in] dtype ��ʾģʽ��������Ķ�Ӧ
 *@return ��
 */
	NGE_API void FillRectGradEx(rectf rect,int* colors,int dtype);
/**
 * ��ͼ����1��Ч��������ImageToScreen>DrawImage>DrawImageMask>RenderQuad;\n
 * sx,sy,sw,sh,���ɴ���ʾ��ͼƬ��Χ������Ҫ��ʾһ��ͼƬ200*200��ͼƬ��\n
 * 20��20��50��50�ߵ���ͼ�飬�����������20,20,50,50�����Ҫ��ʾԭͼ,������0
 * ����.����0����ʾ0,0,tex->w,tex->h��xscale,yscale�ǷŴ���С����1��ԭʼ������\n
 * ����Ŵ�һ��������2����С1����0.5��mask����ɫ���֣����ڶ�ͼƬ���л�ɫ��\n
 * �����͸��Ч���ȣ�Ĭ������ʾԭɫ��������texture->mask����\n
 * ����1:��200*200��ͼƬtex��ʾ����Ļ100��0�������Ŵ�һ����ʾ\n
 * RenderQuad(tex,0,0,0,0,100,0,2,2,0,tex->mask);\n
 * ����2:��ͼƬtex��32��32��ʼ��64��,64�ߵĲ�����ʾ��40��80������ת90��\n
 * RenderQuad(tex,32,32,64,64,40,80,1,1,90,tex->mask);\n
 * ����3:��ͼƬtex(tex��ʾģʽ��8888)��80��80��ʼ��64��,64�ߵĲ�����ʾ��100��100������͸����ʾ\n
 * RenderQuad(tex,80,80,64,64,100,100,1,1,0,MAKE_RGBA_8888(255,255,255,128));\n
 *@param[in] texture ͼƬָ��
 *@param[in] sx ͼƬx����
 *@param[in] sy ͼƬy����
 *@param[in] sw ͼƬ��
 *@param[in] sh ͼƬ��,
 *@param[in] dx ��Ļx����
 *@param[in] dy ��Ļy����
 *@param[in] xscale ͼƬx����Ŵ���С����
 *@param[in] yscale ͼƬy����Ŵ���С����
 *@param[in] angle ��ת�Ƕ�
 *@param[in] mask ��ɫ����
 *@return ��
 */
	NGE_API void RenderQuad(image_p texture,float sx ,float sy ,float sw ,float sh ,float dx ,float dy ,float xscale  ,float yscale ,float angle ,int mask);
/**
 * ��ͼ����2,sw,shΪ0�ǻ�ԭͼ��dw��dhΪ0����ʾsw��dh��С\n
 * ����1:��200*200��ͼƬtex��ʾ����Ļ100��0��\n
 * DrawImage(tex,0,0,0,0,100,0,0,0);\n
 * �������ϸ�ʽ��DrawImage(tex,0,0,200,200,100,0,200,200);\n
 * @see RenderQuad
 *@param[in] texture ͼƬָ��
 *@param[in] sx ͼƬx����
 *@param[in] sy ͼƬy����
 *@param[in] sw ͼƬ��
 *@param[in] sh ͼƬ��
 *@param[in] dx ��Ļx����
 *@param[in] dy ��Ļy����
 *@param[in] dw ��Ļ��
 *@param[in] dh ��Ļ��
 *@return ��
 */
	NGE_API void DrawImage(image_p texture,float sx,float sy,float sw,float sh,float dx,float dy,float dw,float dh);
/**
 * ��ͼ����3\n
 * ͬDrawImage��ֻ�Ƕ��˸�MASK\n
 * @see DrawImage
 *@param[in] tex ͼƬָ��
 *@param[in] sx ͼƬx����
 *@param[in] sy ͼƬy����
 *@param[in] sw ͼƬ��
 *@param[in] sh ͼƬ��
 *@param[in] dx ��Ļx����
 *@param[in] dy ��Ļy����
 *@param[in] dw ��Ļ��
 *@param[in] dh ��Ļ��
 *@param[in] mask ��ɫ����
 *@return ��
 */
	NGE_API void DrawImageMask(image_p tex,float sx , float sy, float sw, float sh, float dx, float dy, float dw, float dh,int mask);
/**
 * ��ͼ����4����򵥵Ļ�ͼ����,��ͼƬ����dx,dy
 *@param[in] texture ͼƬָ��
 *@param[in] dx ��Ļx����
 *@param[in] dy ��Ļy����
 *@return ��
 */
	NGE_API void ImageToScreen(image_p texture,float dx,float dy);
/**
 * ��ͼ����5������������Java������DrawRegion
 *@param[in] tex ͼƬָ��
 *@param[in] sx ͼƬx����
 *@param[in] sy ͼƬy����
 *@param[in] sw ͼƬ��
 *@param[in] sh ͼƬ��
 *@param[in] transform �任��ʽ,ͬJava
 *@param[in] dx ��Ļx����
 *@param[in] dy ��Ļy����
 *@param[in] anchor ê��,ͬJava
 *@return ��
 */
	NGE_API void DrawRegion(image_p	texture, int sx, int sy, int sw, int sh, int transform, int dx, int dy, int anchor);

/**
 *����Ļ���ݱ�����image_p��
 *@return image_p ����image_pָ��,������NULL
 */
	NGE_API image_p ScreenToImage();
/**
 * ����һ��snapshotͼƬ���ļ�,���ͼƬ��png��ʽ��
 *@param[in] filename ����ͼƬ�ļ���
 *@return ��
 */
	NGE_API void ScreenShot(const char* filename);
/**
 *������Ļ��ɫ��r,g,b,a
 *@param[in] r ����r����(0-255)
 *@param[in] g ����g����(0-255)
 *@param[in] b ����b����(0-255)
 *@param[in] a ����a����(0-255)
 *@return uint32_t ��һ����Ļ��ɫֵ,���ú�GET_RGBA_8888�����������ɫ����
 */
	NGE_API uint32_t SetScreenColor(uint8_t r,uint8_t g,uint8_t b,uint8_t a);
/**
 * ���õ�ǰ�Ļ�Ϸ�ʽ\n
 * ������ӵ�ȡֵ������\n
 * BLEND_ZERO: ����ɫ�������ɫ\n
 * BLEND_ONE: ����ɫ��ȫ�����ɫ\n
 * BLEND_SRC_COLOR: ������ȡԴ��ɫ\n
 * BLEND_ONE_MINUS_SRC_COLOR: ��1.0��ȥԴ��ɫ��Ϊ����\n
 * BLEND_SRC_ALPHA: ������ȡĿ����ɫ\n
 * BLEND_ONE_MINUS_SRC_ALPHA: ��1.0��ȥĿ����ɫ��Ϊ����\n
 * BLEND_DST_ALPHA: ������ȡԴ��ɫ��alphaֵ\n
 * BLEND_ONE_MINUS_DST_ALPHA: ��1.0��ȥԴ��ɫ��alphaֵ��Ϊ����\n
 * BLEND_DST_COLOR: ������ȡĿ����ɫ��alphaֵ\n
 * BLEND_ONE_MINUS_DST_COLOR: ��1.0��ȥĿ����ɫ��alphaֵ��Ϊ����\n
 * BLEND_SRC_ALPHA_SATURATE: �����Դ��ɫ��ͬ����ɫ�������в�ͬ�����Ӽ���\n
 *@param[in] src_blend Դ����,��Դ��ɫ���������ģʽ
 *@param[in] des_blend Ŀ������,��Ŀ����ɫ���������ģʽ
 */
	NGE_API void SetTexBlend(int src_blend, int des_blend);
/**
 *����Ϸ�ʽ�ָ�ΪĬ�Ϸ�ʽ
 */
	NGE_API void ResetTexBlend();

/**
 * ���õ�ǰ�Ļ�Ϸ���\n
 * ��Ϸ��̵�ȡֵ������\n
 * FUNC_ADD: ������ӣ����\n
 * FUNC_SUBTRACT: Դ������ȥĿ�����\n
 * FUNC_REVERSE_SUBTRACT: Ŀ�������ȥԴ����\n
 * FUNC_MAX: ȡ�����нϴ���Ǹ�\n
 * FUNC_MIN: ȡ�����н�С���Ǹ�\n
 *@param[in] color_equation ��ɫ����,����ɫ��������ķ���
 *@param[in] alpha_equation ͸���ȷ���,��͸���Ȳ�������ķ���
 *@remark PSPƽ̨�Ͻ�����alpha_equation����
 */
	NGE_API void SetTexBlendEquation(int color_equation, int alpha_equation);
/**
 *����Ϸ��ָ̻�ΪĬ�Ϸ�ʽ
 */
	NGE_API void ResetTexBlendEquation();


/**
 * ����Ļ�ϻ�һ����ĺ���
 *@param[in] x ������
 *@param[in] y ������
 *@param[in] color ��ɫ
 *@param[in] dtype ��ɫ����
 *@return
 */
	NGE_API void PutPix(float x,float y ,int color,int dtype);

/**
 * ��Բ���߿���
 *@param[in] x Բ�ĺ�����
 *@param[in] y Բ��������
 *@param[in] radius Բ�뾶
 *@param[in] color ��ɫ
 *@param[in] dtype ��ɫ����
 *@return
 */
	NGE_API void DrawCircle(float x, float y, float radius, int color,int dtype);

/**
 * ��ʵ��Բ����
 *@param[in] x Բ�ĺ�����
 *@param[in] y Բ��������
 *@param[in] radius Բ�뾶
 *@param[in] color ��ɫ
 *@param[in] dtype ��ɫ����
 *@return
 */
	NGE_API void FillCircle(float x, float y, float radius, int color,int dtype);

/**
 * ����Բ�߿���
 *@param[in] x Բ�ĺ�����
 *@param[in] y Բ��������
 *@param[in] xradius ��Բx�뾶
 *@param[in] yradius ��Բy�뾶
 *@param[in] color ��ɫ
 *@param[in] dtype ��ɫ����
 *@return
 */
	NGE_API void DrawEllipse(float x,float y ,float xradius,float yradius,int color,int dtype);

/**
 * ��ʵ����Բ����
 *@param[in] x Բ�ĺ�����
 *@param[in] y Բ��������
 *@param[in] xradius ��Բx�뾶
 *@param[in] yradius ��Բy�뾶
 *@param[in] color ��ɫ
 *@param[in] dtype ��ɫ����
 *@return
 */
	NGE_API void FillEllipse(float x,float y ,float xradius,float yradius,int color,int dtype);

/**
 * �����������߿���
 * ע�ⶥ��˳����˳ʱ�뷽��
 *@param[in] x �������������
 *@param[in] y ��������������
 *@param[in] count �������
 *@param[in] color ��ɫ
 *@param[in] dtype ��ɫ����
 *@return
 */
	NGE_API void DrawPolygon(float* x, float* y, int count, int color,int dtype);

/**
 * ������ʵ�Ķ���κ���
 * ע�ⶥ��˳����˳ʱ�뷽��
 *@param[in] x �������������
 *@param[in] y ��������������
 *@param[in] count �������
 *@param[in] color ��ɫ
 *@param[in] dtype ��ɫ����
 *@return
 */
	NGE_API void FillPolygon(float* x, float* y, int count, int color,int dtype);

/**
 * ��������ɫ����ʵ�Ķ���κ���
 * ע�ⶥ��˳����˳ʱ�뷽��
 *@param[in] x �������������
 *@param[in] y ��������������
 *@param[in] count �������
 *@param[in] colors ��ɫ����ע���붥�������ͬ
 *@param[in] dtype ��ɫ����
 *@return
 */
	NGE_API void FillPolygonGrad(float* x, float* y, int count, int* colors,int dtype);


/**
 *  �����ʾ����ռ䡣
 */
	NGE_API void ResetGraphicsCache();
/**
 *��BeginTarget��EndTarget֮��ʹ��,ȡ�õ�ǰtarget�е�����,��ȡ��һ���´���image��
 *@param[in] x ������
 *@param[in] y ������
 *@param[in] w ��
 *@param[in] h ��
 *@return image_p ����һ��������image_p,ע����Ҫ�ͷ����image_p
 */
	NGE_API image_p TargetToImage(int x,int y,int width,int height); 

/*�߼��û�ʹ�õ�ģʽ,������ģʽ:
  ��BeginScene(Target)/EndScene(Target)֮��ʹ��
  ���̴�����:
  PushMatrix();//���滷��
  Identity();  //��ʼ������
  Translate/Rotate/Scale
  DrawImageBatch(Image1,NULL);
  Identity();  //��ʼ������
  Translate/Rotate/Scale
  DrawImageBatch(Image2,NULL);
  PopMatrix();//�ָ�����
*/
/**
 * ƽ�Ʊ任
 *@param[in] x ������
 *@param[in] y ������
 */
NGE_API void Translate(float x,float y);
/**
 * ���ű任
 *@param[in] x ���ű���
 *@param[in] y ���ű���
 */
NGE_API void Scale(float x,float y);
/**
 * ��ת�任
 *@param[in] angel ��ת�Ƕ�
 */
NGE_API void Rotate(float angle);
/**
 * ��������
 */
NGE_API void Identity();
/**
 * �������
 */
NGE_API void PushMatrix();
/**
 * ��������
 */
NGE_API void PopMatrix();
/**
 * ������ͼ
 *@param[in] image image_pͼƬָ��
 *@param[in] uv_rect uv������rectf(left,top)��(right,bottom),��дNULL˵��ʹ������ͼƬ
 */
NGE_API void DrawImageBatch(image_p image,rectf* uv_rect);


/**
 *  Internal Use Only
 */
	NGE_API void RealRenderQuad(quadf quad);

#ifdef __cplusplus
}
#endif
#endif
