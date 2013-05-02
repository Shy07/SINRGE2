/*
** SINRGE2
** Copyright (C) 2013 Syalon, Shy07
** Gernischt@gmail.com
**
** Ruby Class DisplayObject
*/
#include "RbDisplayObject.h"
#include "RbViewport.h"

DisplayObject::DisplayObject()
	: m_x(0), m_y(0), m_z(0)
	, m_ox(0.0f), m_oy(0.0f)
	, m_visible(Qfalse), m_disposed(true)
	, m_viewport_ptr(0)
{
}

void DisplayObject::render(u32 id)
{
}

void DisplayObject::RenderProc(VALUE obj, u32 id)
{
	DisplayObject * dobj;
	Data_Get_Struct(obj, DisplayObject, dobj);

	//	�����Ѿ��ͷŻ���󲻿ɼ���ֱ�ӷ���
	if (dobj->m_disposed || !RTEST(dobj->m_visible))
		return;

	//	��������viewport��Ϊnil�Ҹ�viewport�Ѿ��ͷ���ֱ�ӷ���
	if (dobj->m_viewport_ptr && dobj->m_viewport_ptr->m_disposed)
		return;

	//	��Ⱦ����
	dobj->render(id);
}

/*
 *	����Ϊruby������cʵ��
 */
VALUE DisplayObject::dispose()
{
	return Qnil;
}

VALUE DisplayObject::is_disposed()
{
	return C2RbBool(m_disposed);
}

VALUE DisplayObject::get_x()
{
	return INT2FIX((int)m_x);
}

VALUE DisplayObject::set_x(VALUE x)
{
	SafeNumericValue(x);
	m_x = (float)NUM2INT(x);
	return x;
}

VALUE DisplayObject::get_y()
{
	return INT2FIX((int)m_y);
}

VALUE DisplayObject::set_y(VALUE y)
{
	SafeNumericValue(y);
	m_y = (float)NUM2INT(y);
	return y;
}

VALUE DisplayObject::get_z()
{
	return Qnil;
}

VALUE DisplayObject::set_z(VALUE z)
{
	return Qnil;
}

VALUE DisplayObject::get_ox()
{
	return INT2FIX((int)m_ox);
}

VALUE DisplayObject::set_ox(VALUE ox)
{
	SafeNumericValue(ox);
	m_ox = (float)NUM2INT(ox);
	return ox;
}

VALUE DisplayObject::get_oy()
{
	return INT2FIX((int)m_oy);
}

VALUE DisplayObject::set_oy(VALUE oy)
{
	SafeNumericValue(oy);
	m_oy = (float)NUM2INT(oy);
	return oy;
}

VALUE DisplayObject::get_visible()
{
	return m_visible;
}

VALUE DisplayObject::set_visible(VALUE visible)
{
	m_visible = Ruby2RbBool(visible);
	return Qnil;
}

VALUE DisplayObject::get_viewport()
{
	return ReturnObject(m_viewport_ptr);
}

VALUE DisplayObject::set_viewport(VALUE viewport)
{
	return Qnil;
}

/*
 *	���¶���ruby����
 */
imp_method(DisplayObject, dispose)
imp_method(DisplayObject, is_disposed)

imp_attr_accessor(DisplayObject, x)
imp_attr_accessor(DisplayObject, y)
imp_attr_accessor(DisplayObject, z)
imp_attr_accessor(DisplayObject, ox)
imp_attr_accessor(DisplayObject, oy)
imp_attr_accessor(DisplayObject, visible)
imp_attr_accessor(DisplayObject, viewport)
