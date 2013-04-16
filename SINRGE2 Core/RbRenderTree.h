#ifndef __RGE_RENDER_TREE_H__
#define __RGE_RENDER_TREE_H__

#ifdef WIN32
#pragma once
#endif

#include "RbExport.h"
#include "sin_types.h"
#include "hge.h"

//using namespace Sin;

class RbRenderState
{
public:
	typedef struct __RbRenderClipRect
	{
		int x;
		int y;
		int width;
		int height;

		__RbRenderClipRect() : x(0), y(0), width(0), height(0) {}

		void set(int _x, int _y, int _w, int _h)
		{
			x		= _x;
			y		= _y;
			width	= _w;
			height	= _h;
		}

	} RbRenderClipRect;

public:
	RbRenderState()
		: m_render2texture(false)
	{
		s_pHge = hgeCreate(HGE_VERSION);
	}

	~RbRenderState()
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

	inline const RbRenderClipRect& GetClipRect() const { return m_rect; }

	inline void	SetRenderToTexture(bool b)
	{
		m_render2texture = b;
	}

	inline bool	IsRenderToTexture() const
	{
		return m_render2texture;
	}

private:
	RbRenderClipRect			m_rect;
	bool						m_render2texture;

	static HGE*					s_pHge;
};

/*
 *	��Ⱦ����ָ��
 */
typedef	void (*RbRenderProc)(VALUE, u32);

typedef struct __RbRenderNode
{
	RbRenderProc				renderproc;	//	��Ⱦ����ָ��
	VALUE						value;		//	�ý���ruby��������ã�����Sprite��Window�ȡ�
	u32							id;			//	ID��ʶ���������е�ruby���󣬱���Window��������Ⱦ����һ���߿�һ��ʵ�����ݣ��������������ID���б�ʾ��
	s32							z;			//	�ý������Ⱦ���е�z����ֵ����ֵԽ�����ʾ��Խ���档
	VALUE						viewport;	//	��������ӿڣ������ֵΪQnil������£�����ֱ���ڴ�������Ⱦ��������Viewport����Ⱦ��

	struct __RbRenderNode*		prev;		//	��һ�����ָ�롣
	struct __RbRenderNode*		next;		//	��һ�����ָ�롣
} RbRenderNode, *RbRenderNodePtr;

class RbRenderTree
{
public:
	static void					Init();

public:
	static bool					RenderProc();

public:
	static void					ViewportAddToFront(RbRenderNode* node);
	static void					ViewportDelete(RbRenderNode* node);

	static RbRenderNode*		AllocNode(RbRenderProc proc, VALUE value, u32 id, s32 z, VALUE viewport);

	static RbRenderNode*		DeleteNode(RbRenderNode *node);
	static void					InsertNode(RbRenderNode *node);

	static void					DestroyNode(RbRenderNodePtr* node);
	static void					FreeNode(RbRenderNodePtr* node);

private:
	static RbRenderNode*		DoubleLinkAddToFront(RbRenderNode* list, RbRenderNode* node);
	static RbRenderNode*		DoubleLinkDelete(RbRenderNode* list, RbRenderNode* node);

private:
	static RbRenderNode*		s_pRenderHead;
	static RbRenderNode*		s_pRenderTail;
	static RbRenderNode*		s_pViewportLists;
};

#endif	//	__RGE_RENDER_TREE_H__