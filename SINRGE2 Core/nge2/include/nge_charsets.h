#ifndef __NGE_CHARSET__H
#define __NGE_CHARSET__H

#include "nge_common.h"

#define NGE_RET_BUFFER_SMALL -1

#ifdef __cplusplus
extern "C"{
#endif

/*���º���Ϊ�ڲ�ʹ��,ͨ���������*/

/**
 *��GBK������ַ�ת��Ϊunicode(ucs-2)�ַ�
 *@remark ע��out buffer��ҪԤ�ȷ����㹻��С.
 *@param[in] in �����ַ���
 *@param[out] out ת����unicode�ַ�����������,ע����ҪԤ�ȷ����㹻��С
 *@param[in] len in�ַ������������ֽڼǣ���strlen����ĸ���
 *@param[in] n out buffer�Ĵ�С�����ֽڼ�
 *@return int,ת������ַ���������uint16_t�����ƣ�0�븺����Ϊerror
 */
	NGE_API int nge_charset_gbk_to_ucs2(const uint8_t* in, uint16_t* out, int len, int n);

/**
 *��utf8������ַ�ת��Ϊunicode(ucs-2)�ַ�
 *@remark ע��out buffer��ҪԤ�ȷ����㹻��С.
 *@param[in] in �����ַ���
 *@param[out] out ת����unicode�ַ�����������,ע����ҪԤ�ȷ����㹻��С
 *@param[in] len in�ַ������������ֽڼǣ���strlen����ĸ���
 *@param[in] n out buffer�Ĵ�С�����ֽڼ�
 *@return int,ת������ַ���������uint16_t�����ƣ�0�븺����Ϊerror
 */
	NGE_API int nge_charset_utf8_to_ucs2(const uint8_t* in, uint16_t* out, int len, int n);

/**
 *��utf8������ַ�ת��Ϊgbk�ַ�
 *@remark ע��out buffer��ҪԤ�ȷ����㹻��С.
 *@param[in] in �����ַ���
 *@param[out] out ת����gbk�ַ�����������,ע����ҪԤ�ȷ����㹻��С
 *@param[in] len in�ַ������������ֽڼǣ���strlen����ĸ���
 *@param[in] n out buffer�Ĵ�С�����ֽڼ�
 *@return int,ת������ַ����������ֽڼƣ�0�븺����Ϊerror
 */
	NGE_API int nge_charsets_utf8_to_gbk(const uint8_t* in, uint8_t* out, int len, int n);

/**
 *��gbk������ַ�ת��Ϊutf8�ַ�
 *@remark ע��out buffer��ҪԤ�ȷ����㹻��С.
 *@param[in] in �����ַ���
 *@param[out] out ת����gbk�ַ�����������,ע����ҪԤ�ȷ����㹻��С
 *@param[in] len in�ַ������������ֽڼǣ���strlen����ĸ���
 *@param[in] n out buffer�Ĵ�С�����ֽڼ�
 *@return int,ת������ַ����������ֽڼƣ�0�븺����Ϊerror
 */
	NGE_API int nge_charsets_gbk_to_utf8(const uint8_t* in, uint8_t* out, int len, int n);

#ifdef __cplusplus
}
#endif

#endif
