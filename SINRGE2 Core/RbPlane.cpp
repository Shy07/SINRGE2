#include "RbExport.h"
#include "RbBitmap.h"
#include "RbViewport.h"
#include "RbColor.h"
#include "RbTone.h"
#include "RbRect.h"
#include "RbPlane.h"
#include "SinSprite.h"
#include "SINRGE2.h"

using namespace Sin;

VALUE rb_cPlane;

/*
 *	����
 */
RbPlane::RbPlane()
	: m_opacity(255)
	, m_blend_type(RUBY_0)
	, m_ref_bitmap_modify_count(-1)
	, m_ref_tone(0x0)
	, m_tone_tex(0)
	, m_node(0)
	, m_bitmap_ptr(0)
	, m_color_ptr(0)
	, m_tone_ptr(0)
{
	m_pSpr = new SinSprite();
}

/*
 *	�ͷ�
 */
RbPlane::~RbPlane()
{
	if (m_tone_tex)
		GetHgePtr()->Texture_Free(m_tone_tex);
	
	SAFE_DELETE(m_pSpr);

	RenderTree::DestroyNode(&m_node);
}

void RbPlane::InitLibrary()
{
	rb_cPlane = rb_define_class_under(rb_mSin, "Plane", rb_cObject);

	// special method
	rb_define_alloc_func(rb_cPlane, ObjAllocate<RbPlane>);
	rb_define_method(rb_cPlane, "initialize",	(RbFunc)dm_initialize,		-1);

	// instance method
	rb_define_method(rb_cPlane, "dispose",		(RbFunc)dm_dispose,			0);
	rb_define_method(rb_cPlane, "disposed?",	(RbFunc)dm_is_disposed,		0);

	rb_define_method(rb_cPlane, "invisible_reason",	(RbFunc)dm_invisible_reason,		0);

	// object attribute
	rb_define_method(rb_cPlane, "viewport",		(RbFunc)dm_get_viewport,	0);
	rb_define_method(rb_cPlane, "viewport=",	(RbFunc)dm_set_viewport,	1);

	// object attribute
	rb_define_method(rb_cPlane, "bitmap",		(RbFunc)dm_get_bitmap,		0);
	rb_define_method(rb_cPlane, "bitmap=",		(RbFunc)dm_set_bitmap,		1);
	rb_define_method(rb_cPlane, "visible",		(RbFunc)dm_get_visible,		0);
	rb_define_method(rb_cPlane, "visible=",		(RbFunc)dm_set_visible,		1);
	rb_define_method(rb_cPlane, "z",			(RbFunc)dm_get_z,			0);
	rb_define_method(rb_cPlane, "z=",			(RbFunc)dm_set_z,			1);
	rb_define_method(rb_cPlane, "ox",			(RbFunc)dm_get_ox,			0);
	rb_define_method(rb_cPlane, "ox=",			(RbFunc)dm_set_ox,			1);
	rb_define_method(rb_cPlane, "oy",			(RbFunc)dm_get_oy,			0);
	rb_define_method(rb_cPlane, "oy=",			(RbFunc)dm_set_oy,			1);
	rb_define_method(rb_cPlane, "zoom_x",		(RbFunc)dm_get_zoom_x,		0);
	rb_define_method(rb_cPlane, "zoom_x=",		(RbFunc)dm_set_zoom_x,		1);
	rb_define_method(rb_cPlane, "zoom_y",		(RbFunc)dm_get_zoom_y,		0);
	rb_define_method(rb_cPlane, "zoom_y=",		(RbFunc)dm_set_zoom_y,		1);

	rb_define_method(rb_cPlane, "opacity",		(RbFunc)dm_get_opacity,		0);
	rb_define_method(rb_cPlane, "opacity=",		(RbFunc)dm_set_opacity,		1);
	rb_define_method(rb_cPlane, "blend_type",	(RbFunc)dm_get_blend_type,	0);
	rb_define_method(rb_cPlane, "blend_type=",	(RbFunc)dm_set_blend_type,	1);
	rb_define_method(rb_cPlane, "color",		(RbFunc)dm_get_color,		0);
	rb_define_method(rb_cPlane, "color=",		(RbFunc)dm_set_color,		1);
	rb_define_method(rb_cPlane, "tone",			(RbFunc)dm_get_tone,		0);
	rb_define_method(rb_cPlane, "tone=",		(RbFunc)dm_set_tone,		1);

	// supplement
 	rb_define_method(rb_cPlane, "to_s",			(RbFunc)dm_to_string,		0);
}

/*
 *	���
 */
void RbPlane::mark()
{
	if (m_viewport_ptr) m_viewport_ptr->MarkObject();
	if (m_bitmap_ptr)	m_bitmap_ptr->MarkObject();
	if (m_color_ptr)	m_color_ptr->MarkObject();
	if (m_tone_ptr)		m_tone_ptr->MarkObject();
}

/**
 *	@call
 *		Plane.new				-> plane ���� ��
 *		Plane.new(viewport)		-> plane ����
 *
 *	@desc
 *		���� Plane ����
 */
VALUE RbPlane::initialize(int argc, VALUE *argv, VALUE obj)
{
	VALUE viewport, color, tone;

	//	������
	rb_scan_args(argc, argv, "01", &viewport);

	if (!NIL_P(viewport))
	{
		SafeViewportValue(viewport);
		m_viewport_ptr = GetObjectPtr<RbViewport>(viewport);
	}

	//	�����������Ⱦ���
	m_node = RenderTree::AllocNode(RenderProc, obj, 0, 0, viewport);
	RenderTree::InsertNode(m_node);

	m_visible = Qtrue;

	//	����color��tone����
	VALUE __argv[] = {RUBY_0, RUBY_0, RUBY_0, RUBY_0};
	
	color = rb_class_new_instance(4, __argv, rb_cColor);
	tone = rb_class_new_instance(4, __argv, rb_cTone);

	m_color_ptr = GetObjectPtr<RbColor>(color);
	m_tone_ptr = GetObjectPtr<RbTone>(tone);

	//	ȡ���ͷű��
	m_disposed = false;

	return obj;
}

/*
 *	��Ⱦ����棩
 */
void RbPlane::render(u32 id)
{
	//	��Ч�Լ��
	if (!m_bitmap_ptr)
		return;

	if (m_bitmap_ptr->IsDisposed())
		return;

	//	������ű���С��0��ֱ�ӷ���
	if (m_pSpr->GetZoomX() <= 0.0f || m_pSpr->GetZoomY() <= 0.0f)
		return;

	//	��Ⱦ��������
	s32		save_blend_mode = -1;
	f32		ofs_x, ofs_y;
	u32		wrap_w, wrap_h;
	{
		if (m_color_ptr->GetColor() != 0)
		{
			save_blend_mode = m_pSpr->GetBlendMode();
			m_pSpr->SetBlendMode(save_blend_mode | BLEND_COLORBLNED);
			m_pSpr->SetBlendColor(m_color_ptr->GetColor());
		}

		// set the sprite's opacity
		m_pSpr->SetColor(ARGB(m_opacity, 255, 255, 255));

		// render the sprite to the screen
		
		if (!m_viewport_ptr || GetRenderState()->IsRenderToTexture())
		{
			wrap_w = GetFrameWidth();
			wrap_h = GetFrameHeight();

			ofs_x = 0;
			ofs_y = 0;
		}
		else
		{
			const RbRect* rect_ptr = m_viewport_ptr->GetRectPtr();

			wrap_w = rect_ptr->width;
			wrap_h = rect_ptr->height;

			ofs_x = rect_ptr->x - m_viewport_ptr->m_ox;
			ofs_y = rect_ptr->y - m_viewport_ptr->m_oy;
		}
	}

	//	����ɫ��
	process_tone_texture();

	//	����Դ����
	m_pSpr->SetTextureRect(0, 0, m_bitmap_ptr->GetMemWidth(), m_bitmap_ptr->GetMemHeight());

	//	��Ⱦ
	{
		int zoom_w = (int)(m_bitmap_ptr->GetMemWidth() * m_pSpr->GetZoomX());
		int zoom_h = (int)(m_bitmap_ptr->GetMemHeight() * m_pSpr->GetZoomY());

		int ox = (int)m_ox % zoom_w;
		int oy = (int)m_oy % zoom_h;

		if (ox < 0) ox += zoom_w;
		if (oy < 0) oy += zoom_h;

		int xloop = (wrap_w + zoom_w - 1) / zoom_w; 
		int yloop = (wrap_h + zoom_h - 1) / zoom_h; 

		for (int j = 0; j <= yloop; ++j)
		{
			for (int i = 0; i <= xloop; ++i)
			{
				m_pSpr->Render(ofs_x - ox + i * zoom_w, ofs_y - oy + j * zoom_h);
			}
		}
	}

	//	�ָ�����
	if (save_blend_mode > 0)
	{
		m_pSpr->SetBlendMode(save_blend_mode);
		m_pSpr->SetBlendColor(0);
		save_blend_mode = -1;
	}
}

void RbPlane::process_tone_texture()
{
	bool change = false;

	HGE* hge = GetHgePtr();

	if (m_tone_ptr->GetColor() != m_ref_tone)
	{
		m_ref_tone = m_tone_ptr->GetColor();

		if (m_ref_tone != 0)
		{
			m_ref_bitmap_modify_count = m_bitmap_ptr->GetModifyCount();
			change = true;
		}
		else
		{
			m_pSpr->SetTexture(m_bitmap_ptr->GetBitmapPtr()->quad.tex);
			if (m_tone_tex)
				GetHgePtr()->Texture_Free(m_tone_tex);
		}
	}
	else if (m_ref_bitmap_modify_count != m_bitmap_ptr->GetModifyCount())
	{
		m_ref_bitmap_modify_count = m_bitmap_ptr->GetModifyCount();

		if (m_tone_tex)
			change = true;
	}

	if (change)
	{
		if (m_tone_tex)
			hge->Texture_Free(m_tone_tex);

		m_tone_tex = hge->Texture_Create(m_bitmap_ptr->GetMemWidth(), m_bitmap_ptr->GetMemHeight());
		if (!m_tone_tex)
			rb_raise(rb_eSINBaseError,"Create Texture Error !");

		if (RbBitmap::AdjustTexturesToneDouble(m_bitmap_ptr->GetBitmapPtr(), m_tone_tex, m_ref_tone))
		{
			m_pSpr->SetTexture(m_tone_tex);
			m_pSpr->SetSrcRectDirty();
		}
		else
		{
			m_pSpr->SetTexture(m_bitmap_ptr->GetBitmapPtr()->quad.tex);
			
			if (m_tone_tex)
				hge->Texture_Free(m_tone_tex);
		}
	}
}

/*
 *	����Ϊruby������cʵ��
 */
VALUE RbPlane::invisible_reason()
{
#pragma message("		Unfinished Function " __FUNCTION__)

	return Qnil;
}

VALUE RbPlane::get_bitmap()
{
	return ReturnObject(m_bitmap_ptr);
}

VALUE RbPlane::set_bitmap(VALUE bitmap)
{
	if (m_disposed)	
		return Qnil;

	// ����λͼ�޸ļ���ֵΪ-1
	m_ref_bitmap_modify_count = -1;

	if (NIL_P(bitmap))
	{
		m_bitmap_ptr = 0;
	}
	else
	{
		SafeBitmapValue(bitmap);

		m_bitmap_ptr = GetObjectPtr<RbBitmap>(bitmap);

		m_pSpr->SetTexture(m_bitmap_ptr->GetBitmapPtr()->quad.tex);
		m_pSpr->SetSrcRectDirty();
	}

	return Qnil;
}

VALUE RbPlane::get_zoom_x()
{
	return rb_float_new(m_pSpr->GetZoomX());
}

VALUE RbPlane::set_zoom_x(VALUE zoom_x)
{
	SafeNumericValue(zoom_x);

	m_pSpr->SetZoomX((float)NUM2DBL(zoom_x));
	m_pSpr->SetSrcRectDirty();

	return Qnil;
}

VALUE RbPlane::get_zoom_y()
{
	return rb_float_new(m_pSpr->GetZoomY());
}

VALUE RbPlane::set_zoom_y(VALUE zoom_y)
{
	SafeNumericValue(zoom_y);

	m_pSpr->SetZoomY((float)NUM2DBL(zoom_y));
	m_pSpr->SetSrcRectDirty(true);

	return Qnil;
}

VALUE RbPlane::get_opacity()
{
	return INT2FIX(m_opacity);
}

VALUE RbPlane::set_opacity(VALUE opacity)
{
	SafeFixnumValue(opacity);

	m_opacity = FIX2INT(opacity);
	m_opacity = SinBound(m_opacity, 0, 255);

	return Qnil;
}

VALUE RbPlane::get_blend_type()
{
	return m_blend_type;
}

VALUE RbPlane::set_blend_type(VALUE blend_type)
{
	m_blend_type = blend_type;
	return Qnil;
}

VALUE RbPlane::get_color()
{
	return ReturnObject(m_color_ptr);
}

VALUE RbPlane::set_color(VALUE color)
{
	SafeColorValue(color);
	m_color_ptr = GetObjectPtr<RbColor>(color);
	return Qnil;
}

VALUE RbPlane::get_tone()
{
	return ReturnObject(m_tone_ptr);
}

VALUE RbPlane::set_tone(VALUE tone)
{
	SafeToneValue(tone);
	m_tone_ptr = GetObjectPtr<RbTone>(tone);
	return Qnil;
}

VALUE RbPlane::set_z(VALUE z)
{
	SafeFixnumValue(z);

	if (m_z != FIX2INT(z))
	{
		m_z = FIX2INT(z);
		m_node->z = m_z;
		RenderTree::InsertNode(RenderTree::DeleteNode(m_node));
	}

	return Qnil;
}

VALUE RbPlane::set_viewport(VALUE viewport)
{
	if (NIL_P(viewport))
	{
		m_viewport_ptr = 0;
	}
	else
	{
		SafeViewportValue(viewport);
		m_viewport_ptr = GetObjectPtr<RbViewport>(viewport);
	}

	RenderTree::DeleteNode(m_node);
	m_node->viewport = viewport;
	RenderTree::InsertNode(m_node);

	return Qnil;
}

/*
 *	���¶���ruby����
 */
imp_attr_accessor(RbPlane, bitmap)
imp_attr_accessor(RbPlane, zoom_x)
imp_attr_accessor(RbPlane, zoom_y)
imp_attr_accessor(RbPlane, opacity)
imp_attr_accessor(RbPlane, blend_type)
imp_attr_accessor(RbPlane, color)
imp_attr_accessor(RbPlane, tone)