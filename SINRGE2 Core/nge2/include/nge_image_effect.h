#ifndef NGE_IMAGE_EFFECT_H_
#define NGE_IMAGE_EFFECT_H_

#include "nge_common.h"
#include "nge_image.h"
#include "nge_timer.h"

//֧�ֵ�Ч����
enum{
	IMAGE_EFFECT_FADEIN = 0,//<<����
	IMAGE_EFFECT_FADEOUT,	//<<����
	IMAGE_EFFECT_SCALEIN,	//<<������
	IMAGE_EFFECT_SCALEOUT,	//<<���ų�
	IMAGE_EFFECT_SHAKE,		//<<����
	IMAGE_EFFECT_BLUR,		//<<ģ��
	IMAGE_EFFECT_TRANSITIONS//<<ת��
};
//Ч������״̬
enum{
	EFFECT_INIT = 0,//<<��ʼ��
    EFFECT_PLAY,    //<<������
	EFFECT_STOP     //<<Ч�������
};

//seteffect�Ĳ�������Ϊ����������˽�в���
//˽�в��������ж�������
enum{
	//��������
	SET_EFFECT_FPS = 0,
	SET_EFFECT_TIMETICKS,
	//˽�в���for fade in/out
    SET_EFFECT_FADE_SRC,
	SET_EFFECT_FADE_DES,
	SET_EFFECT_SHAKE_X,
	SET_EFFECT_SHAKE_Y,
	//˽�в���for blur
	SET_EFFECT_BLUR_SRC,
	SET_EFFECT_BLUR_DES,
	SET_EFFECT_BLUR_OPTIMIZATION
};

struct tag_image_effect;

//��������draw������ʾ
typedef void (*effect_draw)(struct tag_image_effect* effector,image_p pimg,float dx,float dy);
//��������setparam�������ò���,������float����int���ڱ��־���
typedef float (*effect_setparam)(struct tag_image_effect* effector,float param,int flags);
//��������getparam����ȡ�ò�����
typedef float (*effect_getparam)(struct tag_image_effect* effector,int flags);
//��������getstatus����ȡ��Ч������״̬��
typedef int (*effect_getstatus)(struct tag_image_effect* effector);
//���ٺ���
typedef void (*effect_destroy)(struct tag_image_effect* effector);

//Ч������"����"��ע��˽�еı����������������
typedef struct tag_image_effect{
	int m_type;
	int m_status;
	int m_effect_fps;
	int m_timeticks;
    nge_timer* m_ptimer;
	//��������
	effect_draw draw;
	effect_setparam set_param;
	effect_getparam get_param;
	effect_destroy  destroy;
	effect_getstatus status;
}image_effect_t,*image_effect_p;

#ifdef __cplusplus
extern "C"{
#endif

/**
 *����һ�������Ч����,������alpha��һ��Сֵ�仯��һ����ֵ
 *@param[in] src_alpha ��ʼ��alphaֵ0-255
 *@param[in] des_alpha ������alphaֵ0-255
 *@param[in] timeticks ���ʱ���Ժ����,1000��1��
 *@return image_effect_p,����Ч������ָ��
 */
	NGE_API image_effect_p effect_create_fadein(int src_alpha,int des_alpha,int timeticks);

/**
 *����һ��������Ч����,������alpha��һ����ֵ�仯��һ��Сֵ
 *@param[in] src_alpha ��ʼ��alphaֵ0-255
 *@param[in] des_alpha ������alphaֵ0-255
 *@param[in] timeticks ���ʱ���Ժ����,1000��1��
 *@return image_effect_p,����Ч������ָ��
 */
	NGE_API image_effect_p effect_create_fadeout(int src_alpha,int des_alpha,int timeticks);

/**
 *����һ��������Ч����
 *@param[in] shake_x x�����ϵĶ�����Χ
 *@param[in] shake_y y�����ϵĶ�����Χ
 *@param[in] timeticks ���ʱ���Ժ����,1000��1��
 *@return image_effect_p,����Ч������ָ��
 */
	NGE_API image_effect_p effect_create_shake(float shake_x,float shake_y,int timeticks);

/**
 *����һ��ģ����Ч����
 *@param[in] src_blur ��ʼʱ��ģ���� 0 Ϊ��ģ��
 *@param[in] des_blur ����ʱ��ģ���� 0 Ϊ��ģ��
 *@param[in] timeticks ���ʱ���Ժ����,1000��1��
 *@param[in] optimization �ٶ��Ż�ѡ�0Ϊ���Ż���Ч�����ٶ�����1Ϊһ���Ż����ٶ�Ч��һ�㣬2Ϊ����Ż����ٶ���죬��Ч����һ�������ʹ�� 1
 *@return image_effect_p,����Ч������ָ��
 */
	NGE_API image_effect_p effect_create_blur(int src_blur,int des_blur,int timeticks, int optimization);

/**
 *����һ��ת��Ч����
 *@param[in] effect_img Ч��ͼ��Ч����ʹ�ô�ͼƬ���������Ȳ����м�Ч��
 *@param[in] src_img ԭͼ
 *@param[in] reversed ��תЧ��
 *@param[in] timeticks ���ʱ���Ժ����,1000��1��
 *@return image_effect_p,����Ч������ָ��
 */
	NGE_API image_effect_p effect_create_transitions(image_p effect_img, image_p src_img, int reversed, int timeticks);

#ifdef __cplusplus
}
#endif

#endif
