#ifndef NGE_GRAPHICS_EXT_H
#define NGE_GRAPHICS_EXT_H

#include "nge_common.h"
#include "nge_image.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * ���� src ͼ��ĻҶȰ汾
 *
 *@param[in] src Դͼ��
 *@param[in] gray �Ҷ� 0 �� 100, 0 ΪԴͼ��, 100 Ϊ����ɫͼ��
 *@return image_p,���ɵ�ͼ��ĻҶȰ汾
 */
	NGE_API image_p create_gray_image(image_p src, int gray);

/**
 * ���� src ͼ������ȣ����ͶȰ汾
 *
 * @param[in] src Դͼ��
 * @param[in] saturation ���϶� -100(�Ҷ�ͼ��) �� 100(�߲�ɫ��ͼ��)
 * @param[in] brightness ���� -100(ȫ��) �� 100(ȫ��)
 */
	NGE_API image_p create_saturation_brightness_image(image_p src, int saturation, int brightness);

/**
 * ���� src ͼ���������ɫģʽͼƬ
 * @param[in] src Դͼ��
 * @param[in] dtype ��ɫģʽ,DISPLAY_PIXEL_FORMAT_XXXX��һ��
 * @return image_p ���ɵ�ͼƬ
 */
	NGE_API image_p image_conv(image_p src, int dtype);

/**
 * ���� src ͼ�������ͼ���ṩ0-4���������˾�
 * @param[in] src Դͼ��
 * @param[in] w ���ŵĿ�
 * @param[in] h ���ŵĸ�
 * @param[in] mode ����ģʽ0-4
 * @return image_p ����ͼ
 */
	NGE_API image_p image_scale(image_p src, int w, int h,int mode);

/**
 * ��ͼƬ���нǶ�Ϊrot��ɫ����ת
 * @remark ��������������,�Ҷ��ʹ�ûᶪʧͼƬ����,������
 * @param[in] pimage Դͼ��
 * @param[in] rot ɫ����ת�ĽǶ�
 * @return int �ɹ�1,ʧ��0
 */
	NGE_API int image_hue_rotate(image_p pimage, float rot);

#ifdef __cplusplus
}
#endif

#endif
