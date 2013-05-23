/*
** SINRGE2
** Copyright (C) 2013 Syalon, Shy07
** Gernischt@gmail.com
**
** SINRGE2 Class Video
*/
#include "sin_video.h"
#include <comdef.h>

#include <string>
#include <xstring>

#pragma comment (lib,"strmiids.lib")

#define VD_SAFE_RELEASE(ptr)	{if (ptr) { (ptr)->Release(); (ptr) = NULL; }}

/**
 *	������Ƶ�ļ���׼������
 */
bool CVideoMgr::LoadMovie(const wchar_t * pFileName, int &pOutWidth, int &pOutHeight)
{
    HRESULT hr;

	///<	��ֹͣ��ǰ��Ƶ
    StopMovie();

	///<	����һ���Զ��ͷų�
	CAutoReleasePool<IUnknown> cLocalPool;

	///<	����������ͼ������
	hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)&m_pGraphBuilder);
	if (FAILED(hr))	return false;

    ///<	��ȡ��ع�����
    hr = m_pGraphBuilder->QueryInterface(IID_IMediaControl,		(void**)&m_pMediaControl);
	if (FAILED(hr))	return false;

    hr = m_pGraphBuilder->QueryInterface(IID_IMediaEvent,		(void**)&m_pMediaEvent);
	if (FAILED(hr))	return false;

    hr = m_pGraphBuilder->QueryInterface(IID_IMediaSeeking,		(void**)&m_pMediaSeeking);
	if (FAILED(hr)) return false;

	hr = m_pGraphBuilder->QueryInterface(IID_IBasicAudio,		(void**)&m_pBasicAudio);
	if (FAILED(hr)) return false;

    ///<	��Ӳ���������
	IBaseFilter * pTempFilter;
	hr = AddFilter(m_pGraphBuilder, CLSID_SampleGrabber, L"Sample Grabber", &pTempFilter);
	if (FAILED(hr)) return false;
	cLocalPool.Push(pTempFilter);
    hr = pTempFilter->QueryInterface(IID_ISampleGrabber, (void**)&m_pSampleGrabber);
	if (FAILED(hr)) return false;

    ///<	���ò�����������ز���
	AM_MEDIA_TYPE mt = { 0, };
	{
		mt.majortype	= MEDIATYPE_Video;
		mt.subtype		= MEDIASUBTYPE_RGB32;		///<	MEDIASUBTYPE_RGB24
		mt.formattype	= FORMAT_VideoInfo;
	}
    hr = m_pSampleGrabber->SetMediaType(&mt);		///<	���ò�������
	if (FAILED(hr)) return false;
	hr = m_pSampleGrabber->SetOneShot(FALSE);		///<	���պ�ֹͣ
	if (FAILED(hr)) return false;
	hr = m_pSampleGrabber->SetBufferSamples(TRUE);	///<	����������
	if (FAILED(hr)) return false;

	///<	����Դ������
	IBaseFilter * pSourceFilter = NULL;
	IFileSourceFilter * pFileSourceFilter = NULL;
	hr = AddFilter(m_pGraphBuilder, CLSID_AsyncReader, L"Sin Source", &pSourceFilter);
	if (FAILED(hr)) return false;
	cLocalPool.Push(pSourceFilter);	
	pSourceFilter->QueryInterface(IID_IFileSourceFilter, (void**)&pFileSourceFilter);
	if (FAILED(hr)) return false;
	cLocalPool.Push(pFileSourceFilter);

	///<	������ƵԴ
	hr = pFileSourceFilter->Load(pFileName, NULL);
	if (FAILED(hr)) return false;

	///<	���������ͼ��������ͬ��RenderFile��
	IPin * pSourceFilterOutPint = FindPin(pSourceFilter, PINDIR_OUTPUT);
	if (!pSourceFilterOutPint) return false;
	cLocalPool.Push(pSourceFilterOutPint);
	hr = m_pGraphBuilder->Render(pSourceFilterOutPint);
	if (FAILED(hr)) return false;

	///<	����Graph�������֮�󣨷����ڹ���ͼ��ʱ������Null Renderer�ȵ��²��ܲ���
	IBaseFilter * pNullRendererFilter = NULL;
	hr = AddFilter(m_pGraphBuilder, CLSID_NullRenderer, L"Null Renderer", &pNullRendererFilter);
	if (FAILED(hr)) return false;
	cLocalPool.Push(pNullRendererFilter);

	///<	�滻 Renderer ������ΪNull Renderer
	hr = ReplaceVideoRenderer(pNullRendererFilter);
	if (FAILED(hr)) return false;

	///<	��ȡ��ز���
    AM_MEDIA_TYPE mtt;
    hr = m_pSampleGrabber->GetConnectedMediaType(&mtt);
	if (FAILED(hr)) return false;
    
    VIDEOINFOHEADER * vih = (VIDEOINFOHEADER*)mtt.pbFormat;
    m_iVideoWidth	= vih->bmiHeader.biWidth;
    m_iVideoHeight	= vih->bmiHeader.biHeight;

	pOutWidth		= vih->bmiHeader.biWidth;
	pOutHeight		= vih->bmiHeader.biHeight;

	m_pTempBuffer	= (BYTE*)malloc(m_iVideoWidth * m_iVideoHeight * 4);
	m_is_occupied = true;

    ///<	�ͷ�ý������
	AuxFreeMediaType(mtt);

	return true;
}

/**
 *	��ʼ������Ƶ
 */
void CVideoMgr::PlayMovie(long iVolume)
{
	if (m_pMediaControl)	m_pMediaControl->Run();
	if (m_pBasicAudio)		m_pBasicAudio->put_Volume(iVolume);
}

/**
 *	�ж���Ƶ�Ƿ��ڲ�����
 */
bool CVideoMgr::IsMoviePlaying()
{
	HRESULT hr;

	///<	�ж��¼�
	if (m_pMediaEvent)
	{
		long ev;
		LONG_PTR p1, p2;

		while (SUCCEEDED(m_pMediaEvent->GetEvent(&ev, &p1, &p2, 0)))
		{
			hr = m_pMediaEvent->FreeEventParams(ev, p1, p2);
			if (FAILED(hr))			return false;
			if (ev == EC_COMPLETE)	return false;
		}
	}

	///<	��ȡ״̬
	if (m_pMediaControl)
	{
		OAFilterState pfs;
		hr = m_pMediaControl->GetState(0, &pfs);
		if (FAILED(hr))	return false;
		return (pfs == State_Running);
	}

	return false;
}

/**
 *	������Ƶ��ͼ
 */
void CVideoMgr::UpdateMovieTexture(DWORD * pDstBitmapAddr)
{
    HRESULT hr;
 
    if (!m_pGraphBuilder || !m_pSampleGrabber)
        return;

    long cbBuffer = 0;
    hr = m_pSampleGrabber->GetCurrentBuffer(&cbBuffer, NULL);
	if (FAILED(hr)) return;
    if (cbBuffer <= 0)
        return;
	
    hr = m_pSampleGrabber->GetCurrentBuffer(&cbBuffer, (long*)m_pTempBuffer);
    if (FAILED(hr)) return;

	BYTE r, g, b;
	int i, h, v;
	for (int ly = 0; ly < m_iVideoHeight; ++ly)
	{
		h = m_iVideoWidth * ly * 4;
		v = m_iVideoWidth * (m_iVideoHeight - ly - 1);
		for (int lx = 0; lx < m_iVideoWidth; ++lx)
		{
			i = h + lx * 4;
			b = m_pTempBuffer[i];
			g = m_pTempBuffer[i + 1];
			r = m_pTempBuffer[i + 2];
			pDstBitmapAddr[v + lx] = 0xFF000000 + (r << 16) + (g << 8) + b;//b | (g << 8) | (r << 16) | (255 << 24);
		}
	}
}

/**
 *	ֹͣ��Ƶ����
 */
void CVideoMgr::StopMovie()
{
	if (!m_pGraphBuilder)
		return;

	if (m_pMediaControl)
		m_pMediaControl->Stop();

	VD_SAFE_RELEASE(m_pBasicAudio);
	VD_SAFE_RELEASE(m_pSampleGrabber);
	VD_SAFE_RELEASE(m_pMediaSeeking);
	VD_SAFE_RELEASE(m_pMediaControl);
	VD_SAFE_RELEASE(m_pMediaEvent);
	VD_SAFE_RELEASE(m_pGraphBuilder);

	m_iVideoWidth = 0;
	m_iVideoHeight = 0;
	m_is_occupied = false;

	if (m_pTempBuffer)
		free(m_pTempBuffer);
}

/**
 *	������Ƶ����λ��
 */
void CVideoMgr::RewindMovie()
{
	if (!m_pMediaSeeking) 
		return;

	LONGLONG iCurrPos = 0;
	LONGLONG iStopPos = 0;

	m_pMediaSeeking->SetPositions(&iCurrPos, AM_SEEKING_AbsolutePositioning, &iStopPos, AM_SEEKING_NoPositioning);
}

/**
 *	������Ƶ����
 */
long CVideoMgr::GetVolume() const
{
	if (!m_pBasicAudio)
		return 0;

	long iVolume = 0;
	m_pBasicAudio->get_Volume(&iVolume);
	return iVolume;
}

void CVideoMgr::SetVolume(long iVolume)
{
	if (!m_pBasicAudio)
		return;

	m_pBasicAudio->put_Volume(iVolume);
}

/**************************************************************
 *	���¿�ʼΪ˽�к���
 /************************************************************/

IPin * CVideoMgr::FindPin(IBaseFilter * pFilter, PIN_DIRECTION PinDir, bool bFreePin)
{
	IEnumPins*		pEnumerator;   
	IPin*			pPin;
	IPin*			pLastPin;
	PIN_DIRECTION	tmpDir;

	if (FAILED(pFilter->EnumPins(&pEnumerator)))
		return 0;

	while (S_OK == pEnumerator->Next(1, &pPin, NULL))
	{
		if (SUCCEEDED(pPin->QueryDirection(&tmpDir)) && tmpDir == PinDir)
		{
			if (!bFreePin)
				return pPin;

			HRESULT hr = pPin->ConnectedTo(&pLastPin);
			if (VFW_E_NOT_CONNECTED == hr)
				return pPin;

			pLastPin->Release();
			pPin->Release();
		}
		else
			pPin->Release();
	}

	return 0;
}

void CVideoMgr::CollectFilterPins(IBaseFilter * pFilter, ListPinPtr& vInPins, ListPinPtr& vOutPins)
{
	IPin*			pPin;
	IEnumPins*		pEnumerator;
	PIN_DIRECTION	dir;

	if (FAILED(pFilter->EnumPins(&pEnumerator)))
		return;

	vInPins.clear();
	vOutPins.clear();

	while (S_OK == pEnumerator->Next(1, &pPin, NULL))
	{
		if (SUCCEEDED(pPin->QueryDirection(&dir)))
		{
			if (dir == PINDIR_INPUT)
				vInPins.push_back(pPin);
			else
				vOutPins.push_back(pPin);
		}
		else
			pPin->Release();
	}

	pEnumerator->Release();
}

void CVideoMgr::CollectFilters(IGraphBuilder * pGraph, ListBaseFilterPtr& vFilters)
{
	IEnumFilters*	pEnumerator;
	IBaseFilter*	pFilter;

	if (FAILED(pGraph->EnumFilters(&pEnumerator)))
		return;

	vFilters.clear();

	while (S_OK == pEnumerator->Next(1, &pFilter, NULL))
		vFilters.push_back(pFilter);

	pEnumerator->Release();  
}

HRESULT CVideoMgr::AddFilter(IGraphBuilder * pGraph, const GUID& gClsID, LPCWSTR pName, IBaseFilter ** pOutFilter)
{
	*pOutFilter = 0;

	IBaseFilter * pFilter = 0;
	HRESULT hr = CoCreateInstance(gClsID, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)&pFilter);

	if (SUCCEEDED(hr))
	{
		hr = pGraph->AddFilter(pFilter, pName);
		if (SUCCEEDED(hr))
			*pOutFilter = pFilter;
		else
			pFilter->Release();
	}

	return hr;
}

void CVideoMgr::ReleasePins(ListPinPtr& vPins)
{
	for (ListPinPtr::iterator it = vPins.begin(); it != vPins.end(); ++it)
		(*it)->Release();
}

HRESULT CVideoMgr::ReplaceVideoRenderer(IBaseFilter * pNullRendererFilter)
{
	HRESULT				hr;

	ListPinPtr			vInPins;
	ListPinPtr			vOutPins;
	ListBaseFilterPtr	vFilters;

	IPin*				pCurrInPin	= NULL;
	IPin*				pLastOutPin	= NULL;
	AM_MEDIA_TYPE		sMediaType;

	///<	ö�����й�����
	CollectFilters(m_pGraphBuilder, vFilters);

	///<	�������й��������������һ����Ч��Renderer Filter��
	for (ListBaseFilterPtr::iterator it = vFilters.begin(); it != vFilters.end(); ++it)
	{
		///<	��ȡ�����������е��������Pin
		CollectFilterPins(*it, vInPins, vOutPins);

		///<	���˲���Ҫ�Ĺ�������Renderer����Ӧ��ֻ��һ������&û�������
		if (vInPins.size() != 1 || vOutPins.size() != 0)
		{
			///<	�ͷŹ���������Pin�Լ�����������
			ReleasePins(vInPins);
			ReleasePins(vOutPins);
			continue;
		}
	
		///<	��ȡ����������Pin�ϵ�ý������
		pCurrInPin = vInPins[0];
		hr = pCurrInPin->ConnectionMediaType(&sMediaType);

		///<	��ȡý������ʧ����Ϊδ֪Pin�����Թ� or �Թ�����Ƶ�������
		if (FAILED(hr) || sMediaType.majortype != MEDIATYPE_Video)
		{
			///<	�ͷ�����Pin�Լ�����������
			VD_SAFE_RELEASE(pCurrInPin);
			continue;
		}

		///<	��ȡ����Pin�������ŵ����Pin
		hr = pCurrInPin->ConnectedTo(&pLastOutPin);
		if (VFW_E_NOT_CONNECTED == hr)
		{
			VD_SAFE_RELEASE(pCurrInPin);
			VD_SAFE_RELEASE(pLastOutPin);
			continue;
		}

		break;
	}

	///<	�ͷ����й�����
	for (ListBaseFilterPtr::iterator it = vFilters.begin(); it != vFilters.end(); ++it)
		(*it)->Release();
	vFilters.clear();

	if (!pCurrInPin || !pLastOutPin)
	{
		VD_SAFE_RELEASE(pCurrInPin);
		VD_SAFE_RELEASE(pLastOutPin);
		return E_UNEXPECTED;
	}

	///<	�滻Video RendererΪ Null Renderer
	IPin * pNullRendererInPin = FindPin(pNullRendererFilter, PINDIR_INPUT);   
	if (!pNullRendererInPin)
	{
		VD_SAFE_RELEASE(pCurrInPin);
		VD_SAFE_RELEASE(pLastOutPin);
		return E_UNEXPECTED;
	}

	///<	�Ͽ����Pin
	hr = pLastOutPin->Disconnect();
	if (FAILED(hr))
	{
		VD_SAFE_RELEASE(pCurrInPin);
		VD_SAFE_RELEASE(pLastOutPin);
		VD_SAFE_RELEASE(pNullRendererInPin);
		return hr;
	}

	///<	�Ͽ�����Pin
	hr = pCurrInPin->Disconnect();
	if (FAILED(hr))
	{
		VD_SAFE_RELEASE(pCurrInPin);
		VD_SAFE_RELEASE(pLastOutPin);
		VD_SAFE_RELEASE(pNullRendererInPin);
		return hr;
	}

	///<	�����������Pin��NullRenderer������Pin
	hr = m_pGraphBuilder->Connect(pLastOutPin, pNullRendererInPin); 

	///<	�ͷ�
	VD_SAFE_RELEASE(pCurrInPin);
	VD_SAFE_RELEASE(pLastOutPin);
	VD_SAFE_RELEASE(pNullRendererInPin);

	return hr;
}

void CVideoMgr::AuxFreeMediaType(AM_MEDIA_TYPE& mt)
{
	if (mt.cbFormat != 0)
	{
		CoTaskMemFree((PVOID)mt.pbFormat);
		mt.cbFormat = 0;
		mt.pbFormat = NULL;
	}
	if (mt.pUnk != NULL)
	{
		// Unecessary because pUnk should not be used, but safest.
		mt.pUnk->Release();
		mt.pUnk = NULL;
	}
}

CVideoMgr * CVideoMgr::s_pVideoMgr = 0;

CVideoMgr::CVideoMgr()
	: m_pGraphBuilder(0)

	, m_pMediaControl(0)
	, m_pMediaEvent(0)
	, m_pMediaSeeking(0)

	, m_pSampleGrabber(0)
	, m_pBasicAudio(0)

	, m_iVideoWidth(0)
	, m_iVideoHeight(0)
	, m_pTempBuffer(0)
	, m_is_occupied(false)
{
	s_pVideoMgr = this;
}

CVideoMgr::~CVideoMgr()
{
}

bool CVideoMgr::Init()
{
	if (FAILED(CoInitialize(NULL)))
		return false;

	return true;
}

void CVideoMgr::Destroy()
{
	StopMovie();

	CoUninitialize();
}
