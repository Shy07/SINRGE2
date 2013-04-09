#ifndef __C_RGE_FONT_H__
#define __C_RGE_FONT_H__

#ifdef WIN32
#pragma once
#endif

#include "RbClassBase.h"

using namespace Sin;

class RbColor;

class RbFont : public RbClassBase
{
public:
	RbFont();
	virtual ~RbFont();

public:
	static void		InitLibrary();

	HFONT			GetHFont() const { return m_hFont; }

protected:
	virtual void	mark();
	virtual VALUE	initialize(int argc, VALUE *argv, VALUE obj);

protected:
	VALUE			m_name;			// mark
	VALUE			m_size;
	VALUE			m_bold;
	VALUE			m_italic;

	// ʵ���������
	HFONT			m_hFont;
	LOGFONTW		m_lfw;

	RbColor*		m_color_ptr;

protected:
	attr_accessor(name)
	attr_accessor(size)
	attr_accessor(bold)
	attr_accessor(italic)
	attr_accessor(color)

	class_attr_accessor(default_name)
	class_attr_accessor(default_size)
	class_attr_accessor(default_bold)
	class_attr_accessor(default_italic)
	class_attr_accessor(default_color)

protected:
	static VALUE	__default_name__;
	static VALUE	__default_size__;
	static VALUE	__default_bold__;
	static VALUE	__default_italic__;
	static VALUE	__default_color__;
};

#endif