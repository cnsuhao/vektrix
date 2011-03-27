#ifndef __std_cpp_ext_H__
#define __std_cpp_ext_H__

/// CLASS SETTERS AND GETTERS
// some underlying implementation macros

/* Implementation for a reference getter */
#define std_cpp_ext_get_impl(type, name) \
	public: const type& get##name() const \
	{ return m##name; }

/* Implementation for a pointer getter */
#define std_cpp_ext_getp_impl(type, name) \
	public: type* get##name() const \
	{ return m##name; }

/* Implementation for a reference setter */
#define std_cpp_ext_set(type, name) \
	public: void set##name(const type& val) \
	{ m##name = val; }

/* Implementation for a pointer setter */
#define std_cpp_ext_setp_impl(type, name) \
	public: void set##name(type* val) \
	{ m##name = val; }

/* Declare a read-only reference attribute */
#define __get(type, name) \
	protected: type m##name; \
	std_cpp_ext_get_impl(type, name)

/* Declare a read-only pointer attribute */
#define __getp(type, name) \
	protected: type* m##name; \
	std_cpp_ext_getp_impl(type, name)

/* Declare a write-only reference attribute */
#define __set(type, name) \
	protected: type m##name; \
	std_cpp_ext_set(type, name)

/* Declare a write-only pointer attribute */
#define __setp(type, name) \
	protected: type* m##name; \
	std_cpp_ext_setp_impl(type, name)

/* Declare a dynamic reference attribute */
#define __getset(type, name) \
	protected: type m##name; \
	std_cpp_ext_get_impl(type, name) \
	std_cpp_ext_set(type, name)

/* Declare a dynamic pointer attribute */
#define __getsetp(type, name) \
	protected: type* m##name; \
	std_cpp_ext_getp_impl(type, name) \
	std_cpp_ext_setp_impl(type, name)

/// easier STL iteration
#define for_each(var, type, container) \
	for(type::iterator var = container.begin(), \
	var##_end = container.end(); \
	var != var##_end; ++var)

#define for_each_const(var, type, container) \
	for(type::const_iterator var = container.begin(), \
	var##_end = container.end(); \
	var != var##_end; ++var)

/// clean namespace declaration
#define __n(a) namespace a {
#define __namespace(a) namespace a {
#define __namespace2(a, b)						__n(a) __n(b)
#define __namespace3(a, b, c)					__n(a) __n(b) __n(c)
#define __namespace4(a, b, c, d)				__n(a) __n(b) __n(c) __n(d)
#define __namespace5(a, b, c, d, e)				__n(a) __n(b) __n(c) __n(d) __n(e)
#define __namespace6(a, b, c, d, e, f)			__n(a) __n(b) __n(c) __n(d) __n(e) __n(f)
#define __namespace7(a, b, c, d, e, f, g)		__n(a) __n(b) __n(c) __n(d) __n(e) __n(f) __n(g)
#define __namespace8(a, b, c, d, e, f, g, h)	__n(a) __n(b) __n(c) __n(d) __n(e) __n(f) __n(g) __n(h)
#define __namespace9(a, b, c, d, e, f, g, h, i)	__n(a) __n(b) __n(c) __n(d) __n(e) __n(f) __n(g) __n(h) __n(i)

#endif
