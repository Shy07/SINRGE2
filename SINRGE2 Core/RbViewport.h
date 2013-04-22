#ifndef __RB_VIEWPORT_H__
#define __RB_VIEWPORT_H__

#include "RbDisplayObject.h"

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
	RbRenderNodePtr*	GetHeadPtr() { return &m_head; }
	RbRenderNodePtr*	GetTailPtr() { return &m_tail; }
	const RbRect*		GetRectPtr() const { return m_rect_ptr; }

protected:
	virtual void		mark();
	virtual VALUE		initialize(int argc, VALUE *argv, VALUE obj);

	virtual	void		render(u32 id);
	
	virtual VALUE		get_z();
	virtual VALUE		set_z(VALUE z);

protected:
	int					m_flash_duration;					//	�ӿ���˸֡��
	int					m_flash_reduce_count_per_frame;		//	�ӿ���˸ÿ֡���͵�͸����
	int					m_flash_hide_spr;					//	�Ƿ���ȥ�ӿڣ�������˸��ɫָ��Ϊnilʱ����ȥ�ӿڡ�
	DWORD				m_flash_color;						//	�ӿ���˸����ɫֵ��

	hgeQuad				m_quad;

	RbRenderNode*		m_node;

	RbRenderNode*		m_tail;
	RbRenderNode*		m_head;

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