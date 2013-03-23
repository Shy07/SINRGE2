#ifndef NGE_TIMER_H_
#define NGE_TIMER_H_

#include "nge_common.h"

struct tagTimer;

typedef uint32_t (*fp_proc_int)(struct tagTimer*);
typedef void (*fp_proc_void)(struct tagTimer*);

typedef struct tagTimer{
	fp_proc_int		get_ticks; /**<  ��ȡtime tick */
	fp_proc_void	start;     /**<  ��ʼtimer */
	fp_proc_void	stop;      /**<  ֹͣtimer */
	fp_proc_void	pause;     /**<  ��ͣtimer */
	fp_proc_void	unpause;   /**<  �ָ�timer */
	fp_proc_int		is_started;/**<  ��ȡtimer�Ƿ�ʼ */
	fp_proc_int		is_paused; /**<  ��ȡtimer�Ƿ���ͣ */
	//privated
	uint32_t startTicks;
    uint32_t pausedTicks;
    uint8_t  paused;
    uint8_t  started;
}nge_timer;

#ifdef __cplusplus
extern "C"{
#endif

/**
 *����һ��timer
 *@return nge_timer*,����timer��ָ��
 */
	NGE_API nge_timer* nge_timer_create();

/**
 *�ͷ�һ��timer
 *@param[in, out] timer ���ͷŵ�timerָ��
 *@return ��
 */
	NGE_API void nge_timer_free(nge_timer* timer);

/**
 * �õ�ϵͳ��ǰticks
 *@return ticks
 */
	NGE_API uint32_t nge_get_tick();

#ifdef __cplusplus
}
#endif

#endif
