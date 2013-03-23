/**
 * @file  nge_ref_handle.h
 * @author Kun Wang <ifreedom.cn@gmail.com>
 * @date 2012/03/18 03:14:37
 *
 *  Copyright  2012  Kun Wang <ifreedom.cn@gmail.com>
 *
 */

#ifndef _NGE_REF_HANDLER_H
#define _NGE_REF_HANDLER_H

#include "nge_common.h"

typedef struct ngeRefHandle_s
{
	void* ptr;
} *ngeRefHandle;

#define NGE_REF_CAST(type, ref) ((type)(ref->ptr))

typedef void (*fn_ngeDeleteCallback)(void* ptr);

#ifdef __cplusplus
extern "C" {
#endif

/**
 *��һ���������һ������,��ʹ�����ü���+1
 *@param[in, out] handle Ҫ���õľ��
 */
	NGE_API void ngeRef(ngeRefHandle handle);

/**
 *��һ��������һ������,��ʹ�����ü���-1
 *@param[in, out] handle Ҫ������õľ��
 */
	NGE_API void ngeUnref(ngeRefHandle handle);

/**
 *�½�һ�����,��ʼ���ü���Ϊ1
 *@param[in] cb �ص�����,�ھ��������ʱ����,����Ҫ���ͷſռ����Ϊ
 *@param[in] ptr �����ָ������ָ��
 *@return handle,�½��ľ��
 */
	NGE_API ngeRefHandle ngeRefHandleCreate(fn_ngeDeleteCallback cb, void* ptr);

/**
 *����һ�����,��ʹ�����ü���+1,�¸��Ƶľ�������·���ռ�
 *@param[in, out] handle �����Ƶľ��
 *@return handle,���Ƶõ��ľ��
 */
	NGE_API ngeRefHandle ngeRefHandleCopy(ngeRefHandle handle);

/**
 *�ͷ�һ�����
 *@param[in] handle ���ͷŵľ��
 */
	NGE_API void ngeRefHandleRelease(ngeRefHandle handle);

/**
 *����һ����ͨ���,ɾ������Ϊstdlib.h�е�free()����,����ͬngeRefHandleCreate
 *@param[in] ptr �����ָ������ָ��
 *@return handle,�½��ľ��
 */
	NGE_API ngeRefHandle ngeCreateNormalHandle(void* ptr);
#ifdef __cplusplus
}
#endif

#endif /* _NGE_REF_HANDLER_H */
