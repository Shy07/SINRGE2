/*
** SINRGE2
** Copyright (C) 2013 Syalon, Shy07
** Gernischt@gmail.com
**
** Ruby Class Base
*/
#ifndef __C_RB_CLASS_BASE_H__
#define __C_RB_CLASS_BASE_H__

#ifdef WIN32
#pragma once
#endif

#include "RbExport.h"
#include "hge.h"

/*
 * ��������˸ú���ʹ��Ruby������Ĭ�ϵ��ڴ���������ж��������ͷţ�����ʹ�á�
 */
#define SIN_USE_RUBY_MM		1

#ifdef SIN_USE_RUBY_MM
#include <new>
#endif	//	SIN_USE_RUBY_MM

/*
 *	����ruby��ʵ����������Ӧ���ֲ�����Ŀ��
 */
#define dm_method00(name)				\
	virtual VALUE name();				\
	static	VALUE dm_##name(VALUE obj);	\

#define dm_method01(name)						\
	virtual VALUE name(VALUE);					\
	static	VALUE dm_##name(VALUE obj, VALUE);	\

#define dm_method02(name)								\
	virtual	VALUE name(VALUE, VALUE);					\
	static	VALUE dm_##name(VALUE obj, VALUE, VALUE);	\

#define dm_method03(name)										\
	virtual	VALUE name(VALUE, VALUE, VALUE);					\
	static	VALUE dm_##name(VALUE obj, VALUE, VALUE, VALUE);	\

#define dm_method04(name)											\
	virtual	VALUE name(VALUE, VALUE, VALUE, VALUE);					\
	static	VALUE dm_##name(VALUE obj, VALUE, VALUE, VALUE, VALUE);	\

#define dm_method05(name)													\
	virtual	VALUE name(VALUE, VALUE, VALUE, VALUE, VALUE);					\
	static	VALUE dm_##name(VALUE obj, VALUE, VALUE, VALUE, VALUE, VALUE);	\

#define dm_method06(name)															\
	virtual	VALUE name(VALUE, VALUE, VALUE, VALUE, VALUE, VALUE);					\
	static	VALUE dm_##name(VALUE obj, VALUE, VALUE, VALUE, VALUE, VALUE, VALUE);	\

#define dm_method07(name)																	\
	virtual	VALUE name(VALUE, VALUE, VALUE, VALUE, VALUE, VALUE, VALUE);					\
	static	VALUE dm_##name(VALUE obj, VALUE, VALUE, VALUE, VALUE, VALUE, VALUE, VALUE);	\

#define dm_method_vargs(name)									\
	virtual VALUE name(int argc, VALUE *argv, VALUE obj);		\
	static	VALUE dm_##name(int argc, VALUE *argv, VALUE obj);	\

/*
 *	ʵ��ruby��ʵ����������Ӧ���ֲ�����Ŀ��
 */
#define imp_method00(klass, name)					\
	VALUE klass::dm_##name(VALUE obj)				\
	{												\
		klass * obj_ptr;							\
		Data_Get_Struct(obj, klass, obj_ptr);		\
		return obj_ptr->name();						\
	}												\

#define imp_method01(klass, name)					\
	VALUE klass::dm_##name(VALUE obj, VALUE v1)		\
	{												\
		klass * obj_ptr;							\
		Data_Get_Struct(obj, klass, obj_ptr);		\
		return obj_ptr->name(v1);					\
	}												\

#define imp_method02(klass, name)							\
	VALUE klass::dm_##name(VALUE obj, VALUE v1, VALUE v2)	\
	{														\
		klass * obj_ptr;									\
		Data_Get_Struct(obj, klass, obj_ptr);				\
		return obj_ptr->name(v1, v2);						\
	}														\

#define imp_method03(klass, name)									\
	VALUE klass::dm_##name(VALUE obj, VALUE v1, VALUE v2, VALUE v3)	\
	{																\
		klass * obj_ptr;											\
		Data_Get_Struct(obj, klass, obj_ptr);						\
		return obj_ptr->name(v1, v2, v3);							\
	}																\

#define imp_method04(klass, name)												\
	VALUE klass::dm_##name(VALUE obj, VALUE v1, VALUE v2, VALUE v3, VALUE v4)	\
	{																			\
		klass * obj_ptr;														\
		Data_Get_Struct(obj, klass, obj_ptr);									\
		return obj_ptr->name(v1, v2, v3, v4);									\
	}																			\

#define imp_method05(klass, name)														\
	VALUE klass::dm_##name(VALUE obj, VALUE v1, VALUE v2, VALUE v3, VALUE v4, VALUE v5)	\
	{																					\
		klass * obj_ptr;																\
		Data_Get_Struct(obj, klass, obj_ptr);											\
		return obj_ptr->name(v1, v2, v3, v4, v5);										\
	}																					\

#define imp_method06(klass, name)																	\
	VALUE klass::dm_##name(VALUE obj, VALUE v1, VALUE v2, VALUE v3, VALUE v4, VALUE v5, VALUE v6)	\
	{																								\
		klass * obj_ptr;																			\
		Data_Get_Struct(obj, klass, obj_ptr);														\
		return obj_ptr->name(v1, v2, v3, v4, v5, v6);												\
	}																								\

#define imp_method07(klass, name)																			\
	VALUE klass::dm_##name(VALUE obj, VALUE v1, VALUE v2, VALUE v3, VALUE v4, VALUE v5, VALUE v6, VALUE v7)	\
	{																										\
		klass * obj_ptr;																					\
		Data_Get_Struct(obj, klass, obj_ptr);																\
		return obj_ptr->name(v1, v2, v3, v4, v5, v6, v7);													\
	}																										\

#define imp_method_vargs(klass, name)							\
	VALUE klass::dm_##name(int argc, VALUE *argv, VALUE obj)	\
	{															\
		klass * obj_ptr;										\
		Data_Get_Struct(obj, klass, obj_ptr);					\
		return obj_ptr->name(argc, argv, obj);					\
	}															\

/*
 *	����ruby��ʵ���������޲�����
 */
#define dm_method	dm_method00

/*
 *	ʵ��ruby��ʵ���������޲�����
 */
#define imp_method	imp_method00

/*
 *	����ruby��ֻ����ֻд�Ͷ�д����
 */
#define attr_reader(attr)	dm_method00(get_##attr)
#define attr_writer(attr)	dm_method01(set_##attr)
#define attr_accessor(attr)	\
	attr_reader(attr)		\
	attr_writer(attr)		\

/*
 *	ʵ��ruby��ֻ����ֻд�Ͷ�д����
 */
#define imp_attr_reader(klass, attr)	imp_method00(klass, get_##attr)
#define imp_attr_writer(klass, attr)	imp_method01(klass, set_##attr)
#define imp_attr_accessor(klass, attr)	\
	imp_attr_reader(klass, attr)		\
	imp_attr_writer(klass, attr)		\


/*
 *	����ruby�෽�����޲�����
 */
#define dm_class_method(name)			\
	static	VALUE dm_##name(VALUE obj);	\

/*
 *	����ruby�෽����ָ��������
 */
#define dm_class_method_any(name, ...)				\
	static	VALUE dm_##name(VALUE obj, __VA_ARGS__);\

/*
 *	����ruby�෽��������������
 */
#define dm_class_method_vargs(name)								\
	static	VALUE dm_##name(int argc, VALUE *argv, VALUE obj);	\

/*
 *	�������ֻ������
 */
#define class_attr_reader(attr)				\
	static	VALUE dm_get_##attr(VALUE obj);	\

/*
 *	�������ֻд����
 */
#define class_attr_writer(attr)							\
	static	VALUE dm_set_##attr(VALUE obj, VALUE attr);	\

/*
 *	������Ŀɶ���д����
 */
#define class_attr_accessor(attr)	\
	class_attr_reader(attr)			\
	class_attr_writer(attr)			\


/**
 *	CRbClassBase
 *
 *		Ruby����Ķ�����ࡣ
 */
class CRbClassBase
{
public:
	CRbClassBase() : __obj(Qnil) {}													//	Ruby����Allocate����
	virtual ~CRbClassBase() {}														//	Ruby����Free����������Ӧ�����أ�

public:
	inline bool			IsCppObject() const { return NIL_P(__obj); }				//	�Ƿ���C++�����ж�
	inline VALUE		GetObject() const { return __obj; }							//	��ȡ����Ruby����
	inline void			MarkObject() const { rb_gc_mark(__obj); }					//	�������Ruby����

	static inline VALUE	ReturnObject(CRbClassBase * p)								//	��ȫ����Ruby����
	{
		return (p ? p->GetObject() : Qnil);
	}

	template<class T> 
	static inline T *	GetObjectPtr(VALUE obj)
	{
		return (T *)DATA_PTR(obj);
	}

protected:
	virtual void	mark(){}														//	Ruby����Mark����������Ӧ�����أ�
	virtual VALUE	initialize(int, VALUE *, VALUE obj) { return obj; }				//	Ruby����initialize����������Ӧ�����أ�
	virtual VALUE	clone()			{ return rb_obj_clone(__obj); }
	virtual VALUE	dup()			{ return rb_obj_dup(__obj); }
	virtual VALUE	_dump(VALUE)	{ return Qnil; }
	virtual VALUE	to_string()		{ return rb_sprintf("#<%s:0x%x>", obj_classname(), __obj); }

protected:
	const char *	obj_classname() const { return rb_obj_classname(__obj); }
	VALUE			obj_class()		const { return rb_obj_class(__obj); }

#ifndef SIN_USE_RUBY_MM
protected:
	void *			operator new(size_t size) { return xmalloc(size); }
	void			operator delete(void* ptr) { xfree(ptr); }
#endif	//	SIN_USE_RUBY_MM

protected:
#ifdef SIN_USE_RUBY_MM
	static void		ObjFree(CRbClassBase * baseobj) 
	{ 
		if (baseobj) 
		{
			baseobj->~CRbClassBase();
			xfree(baseobj);
		}
	}
#else
	static void		ObjFree(CRbClassBase * baseobj) { if (baseobj) delete baseobj; }
#endif	//	SIN_USE_RUBY_MM

	static void		ObjMark(CRbClassBase * baseobj) { if (baseobj) baseobj->mark(); }

protected:
	template<class T> static VALUE	ObjAllocate(VALUE klass)
	{
#ifdef SIN_USE_RUBY_MM
		T * dmy = new (xmalloc(sizeof(T))) T();
#else
		T * dmy = new T();
		//if (!dmy)
		//{
		//	RbClassError::RaiseNoMemory();
		//}
#endif	//	SIN_USE_RUBY_MM
		return (dmy->__obj = Data_Wrap_Struct(klass, ObjMark, ObjFree, dmy));
	}

protected:
	static VALUE	dm_initialize(int argc, VALUE * argv, VALUE obj)
	{
		CRbClassBase	* baseobj;
		Data_Get_Struct(obj, CRbClassBase, baseobj);

		return baseobj->initialize(argc, argv, obj);
	}

	static VALUE	dm_clone(VALUE obj)
	{
		CRbClassBase	* baseobj;
		Data_Get_Struct(obj, CRbClassBase, baseobj);

		return baseobj->clone();
	}

	static VALUE	dm_dup(VALUE obj)
	{
		CRbClassBase	* baseobj;
		Data_Get_Struct(obj, CRbClassBase, baseobj);

		return baseobj->dup();
	}

	static VALUE	dm_dump(VALUE obj, VALUE depth)
	{
		CRbClassBase	* baseobj;
		Data_Get_Struct(obj, CRbClassBase, baseobj);

		return baseobj->_dump(depth);
	}

	static VALUE	dm_to_string(VALUE obj)
	{
		CRbClassBase	* baseobj;
		Data_Get_Struct(obj, CRbClassBase, baseobj);

		return baseobj->to_string();
	}

protected:
	VALUE			__obj;														//	�Ը�Ruby�������������
};

#endif