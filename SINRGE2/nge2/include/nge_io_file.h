#ifndef IO_FILE_H_
#define IO_FILE_H_

#include "nge_common.h"

/* PSP��win32�ļ���дͳһ�ӿ� */
#ifdef _PSP
#include <pspiofilemgr.h>
#define IO_RDONLY PSP_O_RDONLY
#define IO_WRONLY PSP_O_RDWR
#define IO_APPEND PSP_O_APPEND

#define IO_SEEK_CUR PSP_SEEK_CUR
#define IO_SEEK_END PSP_SEEK_END
#define IO_SEEK_SET PSP_SEEK_SET
#else
#define IO_RDONLY 0
#define IO_WRONLY 1
#define IO_APPEND 2

#define IO_SEEK_CUR SEEK_CUR
#define IO_SEEK_END SEEK_END
#define IO_SEEK_SET SEEK_SET
#endif

#ifdef __cplusplus
extern "C"{
#endif

/**
 *��(���ش���)�ļ�
 *@param[in] fname �ļ���
 *@param[in] flag �򿪱�־(IO_RDONLY,IO_WRONLY,IO_APPEND��һ��)
 *@return int,�ļ����,��д���ô��ļ�������в���
 */
	NGE_API int io_fopen(const char* fname,int flag);

/**
 *���ļ�����fread���ƣ��ܶ�ȡ�ֽ���Ϊ count * size������ֵ�Ƕ�Ӧ��count��ʵ�ʶ�ȡ��
 *@param[in] buffer �����ȡ���ݵĻ���
 *@param[in] count ��ȡ�ĵ�����ĸ���
 *@param[in] size ��ȡ�ĵ������С
 *@param[in] handle �ļ����
 *@return,ʵ�ʶ�ȡ����
 */
	NGE_API int io_fread(void* buffer,int count,int size,int handle);

/**
 *д�ļ�����fwrite���ƣ���д���ֽ���Ϊ count * size������ֵ�Ƕ�Ӧ��count��ʵ��д����
 *@param[in] buffer ��д���ݵĻ���
 *@param[in] count ��д���ݵ�����ĸ���
 *@param[in] size ��д���ݵ�����Ĵ�С
 *@param[in] handle �ļ����
 *@return,ʵ��д������
 */
	NGE_API int io_fwrite(void* buffer,int count,int size,int handle);

/**
 *�ļ�ָ��ƫ������,��fseek����
 *@param[in] handle �ļ����
 *@param[in] offset ƫ����
 *@param[in] flag seek��־,IO_SEEK_CUR,IO_SEEK_END,IO_SEEK_SET
 *@return int,����0�ɹ�,-1ʧ��
 */
	NGE_API int io_fseek(int handle,int offset,int flag);

/**
 *��õ�ǰ�ļ�ƫ��ֵ
 *@param[in] handle �ļ����
 *@return int �ļ�ƫ��ֵ
 */
	NGE_API int io_ftell(int handle);

/**
 *�ر��ļ�
 *@param[in] handle �ļ����
 *@return int,-1ʧ��
 */
	NGE_API int io_fclose(int handle);

/**
 *�ļ���С
 *@param[in] handle �ļ����
 *@return int,�ļ���С
 */
	NGE_API int io_fsize(int handle);

#ifdef __cplusplus
}
#endif

#endif
