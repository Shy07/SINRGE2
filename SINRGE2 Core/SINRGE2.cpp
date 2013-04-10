/**
 * @file  System.cpp
 * @author Sherry Lynch (or Shy07) <Gernischt@gmail.com>
 * @date 2013/03/12 13:14:54
 *
 *  Copyright  2013  Sherry Lynch (or Shy07) <Gernischt@gmail.com>
 *
 */
#include "RbExport.h"
#include "SINRGE2.h"
#include "RbRect.h"
#include "RbColor.h"
#include "RbTone.h"
#include "RbFont.h"
#include "RbBitmap.h"
#include <fstream>
#include <iostream>

using namespace Sin;

static SinFrameStruct	m_frm_struct;
static HGE*				m_pHge = 0;

static 	IDirect3D8*			m_ref_d3d;
static 	IDirect3DDevice8*	m_ref_device;
static 	D3DCAPS8			m_d3d_caps;

namespace
{
	/*
	**	call-seq:
	**		msgbox_p(...)		-> nil
	**
	*/
	static VALUE rdf_msgboxp(int argc, VALUE *argv/*, VALUE caller*/)
	{
		int i;

		VALUE str = rb_str_buf_new(0);

		for (i = 0; i < argc; ++i)
		{
			rb_str_buf_append(str, rb_inspect(argv[i]));
			rb_str_buf_append(str, rb_default_rs);
		}
		
		MessageBoxW(GetHwnd(), Kconv::UTF8ToUnicode(RSTRING_PTR(str)), GetTitleW(), 0);

		return Qnil;
	}
	/*
	**	call-seq:
	**		p(...)		-> nil
	**
	*/
	static VALUE rdf_p(int argc, VALUE *argv/*, VALUE caller*/)
	{
		int i;

		VALUE str = rb_str_buf_new(0);

		for (i = 0; i < argc; ++i)
		{
			rb_str_buf_append(str, rb_inspect(argv[i]));
			rb_str_buf_append(str, rb_default_rs);
		}
		
		printf(Kconv::UTF8ToAnsi(RSTRING_PTR(str)));

		return Qnil;
	}
	/*
	**	call-seq:
	**		msgbox(...)		-> nil
	**
	*/
	static VALUE rdf_msgbox(int argc, VALUE *argv/*, VALUE caller*/)
	{
		int i;

		VALUE str = rb_str_buf_new(0);

		rb_encoding* enc = rb_utf8_encoding();
		for (i = 0; i < argc; ++i)
		{
			rb_str_buf_append(str, rb_enc_associate(NIL_P(argv[i]) ? rb_str_new2("nil") : rb_obj_as_string(argv[i]), enc));
		}
		
		MessageBoxW(GetHwnd(), Kconv::UTF8ToUnicode(RSTRING_PTR(str)), GetTitleW(), 0);

		return Qnil;
	}
	/*
	**	call-seq:
	**		print(...)		-> nil
	**
	*/
	static VALUE rdf_print(int argc, VALUE *argv/*, VALUE caller*/)
	{
		int i;

		VALUE str = rb_str_buf_new(0);

		rb_encoding* enc = rb_utf8_encoding();
		for (i = 0; i < argc; ++i)
		{
			rb_str_buf_append(str, rb_enc_associate(NIL_P(argv[i]) ? rb_str_new2("nil") : rb_obj_as_string(argv[i]), enc));
		}
		
		printf(Kconv::UTF8ToAnsi(RSTRING_PTR(str)));

		return Qnil;
	}

	void InitRubyInnerClassExt()
	{
		rb_define_global_function("msgbox_p",		(RbFunc)rdf_msgboxp,		-1);
		rb_define_global_function("msgbox",			(RbFunc)rdf_msgbox,			-1);
		rb_define_global_function("p",				(RbFunc)rdf_p,				-1);
		rb_define_global_function("print",			(RbFunc)rdf_print,			-1);
		ruby_Init_Fiber_as_Coroutine();
		Init_zlib();
		Init_nonblock();
		Init_wait();
	}

	void InitExportSinInterface()
	{
		InitRbGlobal();
		InitRbFrame();
		//InitRbHge();
		InitRbGraphics();
		InitRbImage();

		RbRect::InitLibrary();
		RbColor::InitLibrary();
		RbTone::InitLibrary();
		RbFont::InitLibrary();
		RbBitmap::InitLibrary();
	}
	
	static VALUE _run_sin_in_protect(VALUE argv)
	{
		const ID	id_eval = rb_intern("eval");
		const VALUE	binding = rb_const_get(rb_mKernel, rb_intern("TOPLEVEL_BINDING"));
		const VALUE	line_no = INT2FIX(1);
		
		const VALUE script	= rb_ary_entry(argv, 0);
		const VALUE f_name	= rb_ary_entry(argv, 1);

		VALUE rt = rb_funcall(rb_mKernel, id_eval, 4, script, binding, f_name, line_no);

		return rt;
	}

	static void _on_failed(VALUE err)
	{
		VALUE errmsg;

		VALUE source_ary	= rb_eval_string("matchstr = $!.is_a?(SyntaxError) ? $!.to_s : $@[0]; matchstr =~ /(.*):([0-9]+)/; ary = [$1.to_s, $2.to_i]; ary");
		VALUE sourcefile	= rb_ary_entry(source_ary, 0);
		VALUE sourceline	= rb_ary_entry(source_ary, 1);

		const VALUE message			= rb_funcall(err, rb_intern("message"), 0);
		const VALUE message_str		= rb_funcall(message, rb_intern("gsub"), 2, rb_str_new2("\n"), rb_str_new2("\r\n"));

		const char* clsname			= rb_obj_classname(err);
		const char* msg				= RSTRING_PTR(message_str);

		if (rb_obj_is_kind_of(err, rb_eSyntaxError))
			errmsg = rb_sprintf("Script '%s' line %d: %s occurred.", RSTRING_PTR(sourcefile), NUM2INT(sourceline), clsname);
		else
			errmsg = rb_sprintf("Script '%s' line %d: %s occurred.\n\n%s", RSTRING_PTR(sourcefile), NUM2INT(sourceline), clsname, msg);

		MessageBoxW(GetHwnd(), Kconv::AnsiToUnicode(RSTRING_PTR(errmsg)), GetTitleW(),  MB_ICONWARNING);
	}

}

void Sin::SINRGE2Initialize()
{
	///<	初始化解释器
	int		argc = 0;
	char**	argv = 0;

	ruby_sysinit(&argc, &argv);
	{
		RUBY_INIT_STACK
		ruby_init();
		ruby_set_argv(argc - 1, argv + 1);
		//	rb_set_kcode("utf8");
		//  ruby_init_loadpath();
		ruby_incpush("./");
		ruby_script("SINRGE2");
	}

	m_frm_struct.Default();
	//ResManager::Instance()->Init();

	///<	内部类扩展
	InitRubyInnerClassExt();
	///<	导出Sin内部接口
	InitExportSinInterface();
}

int Sin::SINRGE2Eval(const char* script)
{
	int status = -1;

	rb_eval_string_protect(script, &status);

	if ( status )
	{
		rb_eval_string_protect("print $!", &status);
		return 1;
	}

	return 0;
}

int	Sin::SINRGE2Entry(const char* rubyfile)
{
	SINRGE2Initialize();

	std::fstream _file;
    _file.open(rubyfile, std::ios::in);
    if(!_file)
	{
		MessageBoxW(GetHwnd(), L"Failed to load script.", GetTitleW(),  MB_ICONWARNING);
		return 1;
	}
	_file.close();

	int state = 0;

	VALUE rbread = rb_file_open(rubyfile, "rb");
	VALUE script = rb_funcall(rbread, rb_intern("read"), 0);
	(void)rb_io_close(rbread);
	VALUE name	 = rb_str_new2(rubyfile);

	VALUE argv = rb_ary_new2(2);
	rb_ary_push(argv, script);
	rb_ary_push(argv, name);
	rb_ary_freeze(argv);

	VALUE result = rb_protect(_run_sin_in_protect, argv, &state);

	if (state)
	{
		VALUE err = rb_errinfo();
		if (!rb_obj_is_kind_of(err, rb_eSystemExit))
		{
			_on_failed(err);
		}
	}

	return state;
}

void Sin::SetRubyLibHandle(HINSTANCE hModule)
{
	rb_set_lib_handle(hModule);
}

HWND Sin::GetHwnd()
{
	return NULL;
}

SinFrameStruct* Sin::GetFrmStructPtr()
{
	return &m_frm_struct;
}

HGE* Sin::GetHgePtr()
{
	return m_pHge;
}

void Sin::CreateHge()
{
	m_pHge = hgeCreate(HGE_VERSION);
}

bool Sin::HackD3D()
{
	//	Hack the D3D pointer & D3DDevice pointer
	HTEXTURE pTmpTex = m_pHge->Texture_Create(2, 2); 
	if (!pTmpTex)
		goto failed_return;

	if (FAILED((reinterpret_cast<LPDIRECT3DTEXTURE8>(pTmpTex))->GetDevice(&m_ref_device)))
		goto failed_return;

	if (FAILED(m_ref_device->GetDirect3D(&m_ref_d3d)))
		goto failed_return;

	if (FAILED(m_ref_d3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_d3d_caps)))
		goto failed_return;

	m_pHge->Texture_Free(pTmpTex);
	pTmpTex = NULL;

	return true;

failed_return:
	if (pTmpTex)
	{
		m_pHge->Texture_Free(pTmpTex);
		pTmpTex = NULL;
	}
	return false;
}

IDirect3D8* Sin::GetD3DPtr()
{
	return m_ref_d3d;
}

IDirect3DDevice8* Sin::GetD3DDevicePtr()
{
	return m_ref_device;
}

D3DCAPS8* Sin::GetD3DCapsPtr()
{
	return &m_d3d_caps;
}

//char* GetTitle()
//{
//	return "SINRGE2 Ver. Draft";
//}
//
//wchar_t* Sin::GetTitleW()
//{
//	return L"SINRGE2 Ver. Draft";
//}
