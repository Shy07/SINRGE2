#ifndef NGE_MISC_H_
#define NGE_MISC_H_

#include "nge_common.h"

//���ߺ�����
#if defined WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#define nge_sleep(tick) Sleep(tick)

#elif defined _PSP
#include <pspthreadman.h>
#define nge_sleep(tick) sceKernelDelayThread((tick)*1000)

#elif defined __linux__ || defined NGE_IPHONE
#include <unistd.h>
#define nge_sleep(tick) usleep(tick)
#endif

#ifdef __cplusplus
extern "C"{
#endif

/**
 *����һ��min---max�ĸ�����
 *@param[in] min,��Сֵ
 *@param[in] max,���ֵ
 *@return float,���ɵĸ�����
 */
	NGE_API float rand_float(float min, float max);
/**
 *����һ��(min,max)������
 *@param[in] min,��Сֵ
 *@param[in] max,���ֵ
 *@return int,���ɵ�����
 */
	NGE_API int rand_int(int min, int max);

#ifdef __cplusplus
}
#endif

#endif
