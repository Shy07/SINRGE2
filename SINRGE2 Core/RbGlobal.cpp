/**
 * @file  RbGlobal.cpp
 * @author Sherry Lynch (or Shy07) <Gernischt@gmail.com>
 * @date 2013‎/3‎/‎12‎ 12:40:48
 *
 *  Copyright  2013  Sherry Lynch (or Shy07) <Gernischt@gmail.com>
 *
 */
#include "RbExport.h"
#include "SINRGE2.h"

namespace Sin
{
	VALUE rb_mSin = Qnil;
	//VALUE rb_mNge = Qnil;
	
	VALUE rb_eSINBaseError;
	VALUE rb_eSINDisposedObjectError;

	void InitRbGlobal()
	{
		///<	定义Sin顶层模块
		rb_mSin = rb_define_module("SIN");
		//rb_mNge = rb_define_module_under(rb_mSin, "NGE");
		
		rb_define_const(rb_mSin, "VERSION", rb_str_freeze(rb_str_new2(SIN_VERSION)));
		rb_define_const(rb_mSin, "SINNAME", rb_str_freeze(rb_str_new2(SIN_NAME)));
		
		rb_eSINBaseError = rb_define_class_under(rb_mSin, "BaseError", rb_eStandardError);
		rb_eSINDisposedObjectError = rb_define_class_under(rb_mSin, "DisposedObjectError", rb_eSINBaseError);
		//bind_input();
	}
}