#ifndef __SIN_SPRITE_EX_H__
#define __SIN_SPRITE_EX_H__

#include "hge.h"
#include "hgerect.h"

#include "RbBitmap.h"

class RgeSpriteEx
{
public:
	RgeSpriteEx();
	~RgeSpriteEx();

	void		Render();
	void		Render(float x, float y);

	void		SetTexture(const bitmap_p pTex);
	void		SetTextureRect(int x, int y, int w, int h);
	void		SetColor(DWORD col, int i=-1);
	void		SetZ(float z, int i=-1);
	void		SetBlendMode(int blend) { for (u32 idx = 0; idx < m_quad_cnt; ++idx) m_quads[idx].quad.blend = blend; }
	void		SetBlendColor(int color) { for (u32 idx = 0; idx < m_quad_cnt; ++idx) m_quads[idx].quad.blend_color = color; }

	void		SetOX(float ox) { m_ox = ox; }
	void		SetOY(float oy) { m_oy = oy; }
	void		SetZoomX(float x) { m_zoom_x = x; }
	void		SetZoomY(float y) { m_zoom_y = y; }
	void		SetAngle(float rad) { m_angle = rad; }
	void		SetSrcRectDirty(bool v = true) { m_src_rect_dirty = v; }
	void		SetFlip(bool bX, bool bY, bool bHotSpot = false);

	const bitmap_p GetTexture()										const { return m_tex; }

	bool		GetSrcRectDirty()									const { return m_src_rect_dirty; }
	void		GetTextureRect(int *x, int *y, int *w, int *h)		const { *x=m_rx; *y=m_ry; *w=m_rw; *h=m_rh; }

	DWORD		GetColor(int i = 0)									const { return m_quads.quad.v[i].col; }
	float		GetZ(int i = 0)										const { return m_quads.quad.v[i].z; }
	int			GetBlendMode()										const { return m_quads.quad.blend; }
	DWORD		GetBlendColor()										const { return m_quads.quad.blend_color; }

	float		GetZoomX()											const { return m_zoom_x; }
	float		GetZoomY()											const { return m_zoom_y; }

	float		GetWidth()											const { return m_width; }
	float		GetHeight()											const { return m_height; }
	hgeRect*	GetBoundingBoxEx(float x, float y, hgeRect *rect)	const;

	inline bool	IsFlipX()											const { return m_flip_x < 0.0f; }
	inline bool IsFlipY()											const { return m_flip_y < 0.0f; }

protected:
	struct __RgeQuad
	{
		hgeQuad	quad;			//	С����
		bool	render;			//	��С�����Ƿ����
		float	x[4], y[4];		//	��С����4�����������
	};

	//	����С�ķ��ο��ָ��Ϳ���Ŀ
	struct __RgeQuad			m_quads;
	u32							m_quad_cnt;

	//	����λͼ�Ŀ�Ⱥ͸߶�
	float						m_width, m_height;
	
	//	SRgeTextureָ�������
	/*const*/ bitmap_p				m_tex;
	
	//	�������ת��ԭ�㡢�������Լ���ת
	float						m_angle;
	float						m_ox, m_oy;
	float						m_zoom_x, m_zoom_y;
	float						m_flip_x, m_flip_y;

	//	�Ƿ�תԭ��(ox, oy)
	bool						m_flip_hot_spot;

	//	���鵱ǰ��src_rect
	int							m_rx, m_ry, m_rw, m_rh;

	//	����src_rect�Ĳر��
	bool						m_src_rect_dirty;

	//	���龭��ѡ�����ź���ĸ����������(������ƫ��)
	float						m_x1, m_y1, m_x2, m_y2, m_x3, m_y3, m_x4, m_y4;

protected:
	static HGE*					s_pHge;
};


#endif	//	__SIN_SPRITE_EX_H__

