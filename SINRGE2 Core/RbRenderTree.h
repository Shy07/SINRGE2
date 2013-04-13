#ifndef __RGE_RENDER_TREE_H__
#define __RGE_RENDER_TREE_H__

#ifdef WIN32
#pragma once
#endif

#include "RbExport.h"
#include "sin_types.h"
#include "hge.h"

using namespace Sin;

class RenderState
{
public:
	typedef struct __RenderClipRect
	{
		int x;
		int y;
		int width;
		int height;

		__RenderClipRect() : x(0), y(0), width(0), height(0) {}

		void set(int _x, int _y, int _w, int _h)
		{
			x		= _x;
			y		= _y;
			width	= _w;
			height	= _h;
		}

	} RenderClipRect;

public:
	RenderState()
		: m_render2texture(false)
	{
		s_pHge = hgeCreate(HGE_VERSION);
	}

	~RenderState()
	{
		s_pHge->Release();
	}

public:
	inline void	Clip(int x, int y, int w, int h)
	{
		s_pHge->Gfx_SetClipping(x, y, w, h);
	}

	inline void	Restore()
	{
		s_pHge->Gfx_SetClipping(m_rect.x, m_rect.y, m_rect.width, m_rect.height);
	}

	inline void	Save(int x, int y, int w, int h)
	{
		m_rect.set(x, y, w, h);
	}

	inline void	ClipAndSave(int x, int y, int w, int h)
	{
		Save(x, y, w, h);
		Clip(x, y, w, h);
	}

	inline const RenderClipRect& GetClipRect() const { return m_rect; }

	inline void	SetRenderToTexture(bool b)
	{
		m_render2texture = b;
	}

	inline bool	IsRenderToTexture() const
	{
		return m_render2texture;
	}

private:
	RenderClipRect				m_rect;
	bool						m_render2texture;

	static HGE*					s_pHge;
};

/*
 *	��Ⱦ����ָ��
 */
typedef	void (*RbRenderProc)(VALUE, u32);

typedef struct __RenderNode
{
	RbRenderProc				renderproc;	//	��Ⱦ����ָ��
	VALUE						value;		//	�ý���ruby��������ã�����Sprite��Window�ȡ�
	u32							id;			//	ID��ʶ���������е�ruby���󣬱���Window��������Ⱦ����һ���߿�һ��ʵ�����ݣ��������������ID���б�ʾ��
	s32							z;			//	�ý������Ⱦ���е�z����ֵ����ֵԽ�����ʾ��Խ���档
	VALUE						viewport;	//	��������ӿڣ������ֵΪQnil������£�����ֱ���ڴ�������Ⱦ��������Viewport����Ⱦ��

	struct __RenderNode*		prev;		//	��һ�����ָ�롣
	struct __RenderNode*		next;		//	��һ�����ָ�롣
} RenderNode, *RenderNodePtr;

class RenderTree
{
public:
	static void				Init();

public:
	static bool				RenderProc();

public:
	static void				ViewportAddToFront(RenderNode* node);
	static void				ViewportDelete(RenderNode* node);

	static RenderNode*		AllocNode(RbRenderProc proc, VALUE value, u32 id, s32 z, VALUE viewport);

	static RenderNode*		DeleteNode(RenderNode *node);
	static void				InsertNode(RenderNode *node);

	static void				DestroyNode(RenderNodePtr* node);
	static void				FreeNode(RenderNodePtr* node);

private:
	static RenderNode*		DoubleLinkAddToFront(RenderNode* list, RenderNode* node);
	static RenderNode*		DoubleLinkDelete(RenderNode* list, RenderNode* node);

private:
	static RenderNode*		s_pRenderHead;
	static RenderNode*		s_pRenderTail;
	static RenderNode*		s_pViewportLists;
};

#endif	//	__RGE_RENDER_TREE_H__