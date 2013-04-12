#ifndef __C_RGE_VIEWPORT_H__
#define __C_RGE_VIEWPORT_H__

#include "sin_display_object.h"

class RbRect;
class RbColor;
class RbTone;

class RbViewport : public DisplayObject
{
public:
	RbViewport();
	virtual ~RbViewport();

public:
	static void			InitLibrary();

public:
	RenderNodePtr*		GetHeadPtr() { return &m_head; }
	RenderNodePtr*		GetTailPtr() { return &m_tail; }
	const RbRect*		GetRectPtr() const { return m_rect_ptr; }

protected:
	virtual void		mark();
	virtual VALUE		initialize(int argc, VALUE *argv, VALUE obj);

	virtual	void		render(u32 id);

	virtual VALUE		set_z(VALUE z);

protected:
	inline bool			render_to_texture() const;

protected:
	int					m_flash_duration;					//	视口闪烁帧数
	int					m_flash_reduce_count_per_frame;		//	视口闪烁每帧降低的透明度
	int					m_flash_hide_spr;					//	是否消去视口，仅当闪烁颜色指定为nil时才消去视口。
	DWORD				m_flash_color;						//	视口闪烁的颜色值。

	hgeQuad				m_quad;

	RenderNode*			m_node;
	RenderNode*			m_node_to_texture;	//	渲染到纹理，如果纹理的尺寸超过显卡纹理最大尺寸，需要几张纹理的情况如何处理？？？

	RenderNode*			m_tail;
	RenderNode*			m_head;

	RbRect*				m_rect_ptr;
	RbColor*			m_color_ptr;
	RbTone*				m_tone_ptr;

protected:
	dm_method(update)
	dm_method02(flash)
	attr_accessor(rect)
	attr_accessor(color)
	attr_accessor(tone)
	
protected:
	static HGE*			s_pHge;
};

#endif