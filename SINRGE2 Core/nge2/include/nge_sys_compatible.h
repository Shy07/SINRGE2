#ifndef NGE_SYS_COMPATIBLE_H_
#define NGE_SYS_COMPATIBLE_H_

#include "nge_common.h"

#define CPU_TYPE_333MHZ 333
#define CPU_TYPE_222MHZ 222
#define CPU_TYPE_111MHZ 111

#ifdef NGE_PSP
#include <time.h>
#include <psptypes.h>
#include <psprtc.h>
typedef pspTime sys_time_t,*sys_time_p;
#else
#include "nge_common.h"
typedef struct st_tm{
	uint16_t  year;
	uint16_t  month;
	uint16_t  day;
	uint16_t  hour;
	uint16_t  minutes;
	uint16_t  seconds;
	uint32_t  microseconds;
}sys_time_t,*sys_time_p;
#endif

#ifdef __cplusplus
extern "C"{
#endif

/**
 *��ȡϵͳ�ı���ʱ��
 *@param[out] tm ϵͳʱ��ṹ
 *@return int,�ɹ�����1,ʧ�ܷ���0
 */
	NGE_API int sys_localtime(sys_time_p tm);

/**
 *��ȡϵͳ��Ψһ��30λ���к�.
 *@return char*,30λ���кŵ��ַ���.
 */
	NGE_API char* sys_get_idstorage();

/**
 *��ȡϵͳ��MAC��ַ�ַ���.
 *@return char*,�����ַ���,XX:XX:XX:XX:XX:XX.
 */
	NGE_API char* sys_get_mac();

/**
 *��ȡϵͳ���û���.
 *@return char*,�����ַ���.
 */
	NGE_API char* sys_get_nickname();

/**
 *����CPU��Ƶ������.
 *@param[in] type ����ΪCPU_TYPE_333MHZ,CPU_TYPE_222MHZ,CPU_TYPE_111MHZ
 *@return int,1���óɹ�,0����ʧ��.
 */
	NGE_API int sys_set_frequency_type(int type);

/**
 *ȡ��CPU��Ƶ������.
 *@return int,����ΪCPU_TYPE_333MHZ,CPU_TYPE_222MHZ,CPU_TYPE_111MHZ
 */
	NGE_API int sys_get_frequency_type();

#ifdef __cplusplus
}
#endif

#endif
