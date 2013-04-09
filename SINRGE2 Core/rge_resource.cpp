/*
*
*
*
*/
extern "C"
{
#include "ruby.h"
//#include "ruby/encoding.h"
}
#include "rge_resource.h"

void ResManager::Init()
{
	int i;

	GetModuleFileName(GetModuleHandle(NULL), szAppPath, sizeof(szAppPath));

	for(i = rgestrlen(szAppPath) - 1; i > 0; --i) if (szAppPath[i] == rgestr('\\')) break;

	szAppPath[i + 1] = 0;
}

void* ResManager::Resource_Load(const rgechar *filename, DWORD *size)
{
	void	*data = 0;
	HANDLE	handle = NULL;
	DWORD	file_size;

	handle = CreateFile(Resource_MakePath(filename), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_RANDOM_ACCESS, NULL);
	if (handle == INVALID_HANDLE_VALUE)
		return 0;
	
	file_size = GetFileSize(handle, NULL);

	if (!(data = xmalloc(file_size)))
		goto failed_return;

	if (ReadFile(handle, data, file_size, &file_size, NULL) == 0)
		goto failed_return;
	
	CloseHandle(handle);

	if(size)	*size = file_size;

	return data;

failed_return:
	if (handle != NULL)
	{
		CloseHandle(handle);
		handle = NULL;
	}
	if (data)
	{
		xfree(data);
		data = 0;
	}
	return 0;
}

void ResManager::Resource_Free(void *data)
{
	if (data)	xfree(data);
}

/*
*	Resource_Load_Without_Suffix(...)
*
*		��Ӳ�̶�ȡ�ļ�������ʡ�Ժ�׺����
*
*	@param
*		utf8_filename	-	׼����ȡ���ļ���
*		size			-	�����ȡ�ɹ�����ļ��ֽ���������Ϊ0��
*		suffixs			-	��ѡ�ĺ�׺������
*		suffixs_size	-	��׺������Ԫ�ظ���
*		suffix_idx		-	�����ȡ�ɹ���ĺ�׺�����ţ�����ȡ��ʵ�����֡���û����Ӻ�׺��ʱ��������Ϊ -1��
*
*	@return
*		�ɹ���������ָ�룬ʧ�ܷ���0�����ص�ָ�벻��֮����ҪResource_Free����
*/
void* ResManager::Resource_Load_Without_Suffix(char *utf8_filename, DWORD *size, char *suffixs[], u32 suffixs_size, int *suffix_idx)
{
	void *data;

	u32	i;

	if (!utf8_filename)	return 0;

	char szTmpFilename[MAX_PATH];

	data = Resource_Load(Kconv::UTF8ToUnicode(utf8_filename), size);		//	UTF8 to Unicode

	if (data)
	{
		if (suffix_idx)	*suffix_idx = -1;
		return data;
	}

	for (i = 0; i < suffixs_size; ++i)
	{
		strcpy_s(szTmpFilename, utf8_filename);
		strcat_s(szTmpFilename, suffixs[i]);

		data = Resource_Load(Kconv::UTF8ToUnicode(szTmpFilename), size);	//	UTF8 to Unicode

		if (data)
		{
			if (suffix_idx)	*suffix_idx = i;
			return data;
		}
	}

	return 0;
}

rgechar* ResManager::Resource_MakePath(const rgechar *filename)
{
	int i;

	if (!filename)
		rgestrcpy(szTmpFilename, szAppPath);
	else if (filename[0] == '\\' || filename[0] == '/' || filename[1] == ':')
		rgestrcpy(szTmpFilename, filename);
	else
	{
		rgestrcpy(szTmpFilename, szAppPath);
		if (filename) rgestrcat(szTmpFilename, filename);
	}

	for (i = 0; szTmpFilename[i]; ++i) { if (szTmpFilename[i] == '/') szTmpFilename[i] = '\\'; }

	return szTmpFilename;
}
