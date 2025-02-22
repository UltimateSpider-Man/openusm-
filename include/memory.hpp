// memory standard header
#pragma once
#ifndef _MEMORY_
#define _MEMORY_
#ifndef RC_INVOKED
#include <iterator>
#include <xmemory.hpp>

#ifdef _MSC_VER
#pragma pack(push,_CRT_PACKING)
#pragma warning(push,3)
#endif  /* _MSC_VER */

#define _TRY_BEGIN __try {
#define _CATCH_ALL \
    }              \
    catch (...) {
#define _RERAISE //RaiseException()
#define _CATCH_END }

#define _SECURE_SCL 0

_STDEXT_BEGIN

template<class _InIt, class _FwdIt>
inline _FwdIt unchecked_uninitialized_copy(_InIt _First, _InIt _Last, _FwdIt _Dest);

template<class _InIt, class _FwdIt, class _Alloc>
inline _FwdIt unchecked_uninitialized_copy(_InIt _First, _InIt _Last, _FwdIt _Dest, _Alloc &_Al);

_STDEXT_END

_STD_BEGIN

// TEMPLATE FUNCTION get_temporary_buffer
template<class _Ty>
inline pair<_Ty _FARQ *, _PDFT> get_temporary_buffer(
    _PDFT _Count) { // get raw temporary buffer of up to _Count elements
    _Ty _FARQ *_Pbuf;

    if (_Count <= 0)
        _Count = 0;
    else if (((size_t)(-1) / _Count) < sizeof(_Ty))
        throw std::bad_alloc();

    for (_Pbuf = 0; 0 < _Count; _Count /= 2)
        if ((_Pbuf = (_Ty _FARQ *) operator new ((_SIZT) _Count * sizeof(_Ty), std::nothrow_t{})) !=
            0)
            break;

    return (pair<_Ty _FARQ *, _PDFT>(_Pbuf, _Count));
}

// TEMPLATE FUNCTION return_temporary_buffer
template<class _Ty> inline
	void return_temporary_buffer(_Ty *_Pbuf)
	{	// delete raw temporary buffer
	operator delete(_Pbuf);
	}

		// TEMPLATE FUNCTION uninitialized_copy
template<class _InIt,
	class _FwdIt> inline
	_FwdIt _Uninit_copy(_InIt _First, _InIt _Last, _FwdIt _Dest,
		_Nonscalar_ptr_iterator_tag, _Range_checked_iterator_tag)
	{	// copy [_First, _Last) to raw _Dest, arbitrary type
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Dest);
	_FwdIt _Next = _Dest;

	_TRY_BEGIN
	for (; _First != _Last; ++_Dest, ++_First)
		_Construct(&*_Dest, *_First);
	_CATCH_ALL
	for (; _Next != _Dest; ++_Next)
		_Destroy(&*_Next);
	_RERAISE;
	_CATCH_END
	return (_Dest);
	}

template<class _Ty1,
	class _Ty2> inline
	_Ty2 _Uninit_copy(_Ty1 _First, _Ty1 _Last, _Ty2 _Dest,
		_Scalar_ptr_iterator_tag, _Range_checked_iterator_tag)
	{	// copy [_First, _Last) to raw _Dest, scalar type
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Dest);
	size_t _Count = (size_t)(_Last - _First);
	_Ty2 _Result = _Dest + _Count;
	if (_Count > 0)
		_CRT_SECURE_MEMMOVE(&*_Dest, _Count * sizeof (*_First), &*_First, _Count * sizeof (*_First));	// NB: non-overlapping move
	return _Result;
	}

#if _SECURE_SCL

template<class _InIt,
	class _FwdIt> inline
_IF_CHK(_FwdIt) uninitialized_copy(_InIt _First, _InIt _Last, _FwdIt _Dest)
	{	// copy [_First, _Last) to raw _Dest
	return (_Uninit_copy(_CHECKED_BASE(_First), _CHECKED_BASE(_Last), _Dest,
		_Ptr_cat(_First, _Dest), _STD _Range_checked_iterator_tag()));
	}

template<class _InIt, class _FwdElem, size_t _Size>
inline
_FwdElem* uninitialized_copy(_InIt _First, _InIt _Last, _FwdElem (&_Dest)[_Size])
	{	// copy [_First, _Last) to raw _Dest
	return (uninitialized_copy(_First, _Last,
		_STDEXT make_checked_array_iterator(_Dest, _Size)).base());
	}

template<class _InIt,
	class _FwdIt> inline
_SCL_INSECURE_DEPRECATE
_IF_NOT_CHK(_FwdIt) uninitialized_copy(_InIt _First, _InIt _Last, _FwdIt _Dest)
	{	// copy [_First, _Last) to raw _Dest
	return (_Uninit_copy(_CHECKED_BASE(_First), _CHECKED_BASE(_Last), _Dest,
		_Ptr_cat(_First, _Dest), _STD _Range_checked_iterator_tag()));
	}

#else

template<class _InIt,
	class _FwdIt> inline
	_FwdIt uninitialized_copy(_InIt _First, _InIt _Last, _FwdIt _Dest)
	{	// copy [_First, _Last) to raw _Dest
	return (_Uninit_copy(_CHECKED_BASE(_First), _CHECKED_BASE(_Last), _Dest,
		_Ptr_cat(_First, _Dest), _STD _Range_checked_iterator_tag()));
	}

#endif

		// TEMPLATE FUNCTION _Uninitialized_copy WITH ALLOCATOR
template<class _InIt,
	class _FwdIt,
	class _Alloc> inline
	_FwdIt _Uninit_copy(_InIt _First, _InIt _Last, _FwdIt _Dest,
		_Alloc& _Al, _Nonscalar_ptr_iterator_tag, _Range_checked_iterator_tag)
	{	// copy [_First, _Last) to raw _Dest, using _Al, arbitrary type
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Dest);
	_FwdIt _Next = _Dest;

	_TRY_BEGIN
	for (; _First != _Last; ++_Dest, ++_First)
		_Al.construct(_Dest, *_First);
	_CATCH_ALL
	for (; _Next != _Dest; ++_Next)
		_Al.destroy(_Next);
	_RERAISE;
	_CATCH_END
	return (_Dest);
	}

template<class _InIt,
	class _FwdIt,
	class _Alloc> inline
	_FwdIt _Uninit_copy(_InIt _First, _InIt _Last, _FwdIt _Dest,
		_Alloc&, _Scalar_ptr_iterator_tag, _Range_checked_iterator_tag)
	{	// copy [_First, _Last) to raw _Dest, scalar type
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Dest);
	size_t _Count = (size_t)(_Last - _First);
	_FwdIt _Result = _Dest + _Count;
	if (_Count > 0)
		_CRT_SECURE_MEMMOVE(&*_Dest, _Count * sizeof (*_First), &*_First, _Count * sizeof (*_First));	// NB: non-overlapping move
	return _Result;
	}

#if _SECURE_SCL

template<class _InIt,
	class _FwdIt,
	class _Alloc> inline
_IF_CHK(_FwdIt) _Uninitialized_copy(_InIt _First, _InIt _Last, _FwdIt _Dest,
		_Alloc& _Al)
	{	// copy [_First, _Last) to raw _Dest, using _Al
	return (_Uninit_copy(_CHECKED_BASE(_First), _CHECKED_BASE(_Last), _Dest, _Al,
		_Ptr_cat(_First, _Dest), _STD _Range_checked_iterator_tag()));
	}

template<class _InIt, class _FwdElem, class _Alloc, size_t _Size>
inline
_FwdElem* _Uninitialized_copy(_InIt _First, _InIt _Last, _FwdElem (&_Dest)[_Size],
		_Alloc& _Al)
	{	// copy [_First, _Last) to raw _Dest, using _Al
	return (_Uninitialized_copy(_First, _Last,
		_STDEXT make_checked_array_iterator(_Dest, _Size), _Al).base());
	}

template<class _InIt,
	class _FwdIt,
	class _Alloc> inline
_SCL_INSECURE_DEPRECATE
_IF_NOT_CHK(_FwdIt) _Uninitialized_copy(_InIt _First, _InIt _Last, _FwdIt _Dest,
		_Alloc& _Al)
	{	// copy [_First, _Last) to raw _Dest, using _Al
	return (_Uninit_copy(_CHECKED_BASE(_First), _CHECKED_BASE(_Last), _Dest, _Al,
		_Ptr_cat(_First, _Dest), _STD _Range_checked_iterator_tag()));
	}

#else

template<class _InIt,
	class _FwdIt,
	class _Alloc> inline
	_FwdIt _Uninitialized_copy(_InIt _First, _InIt _Last, _FwdIt _Dest,
		_Alloc& _Al)
	{	// copy [_First, _Last) to raw _Dest, using _Al
	return (_Uninit_copy(_CHECKED_BASE(_First), _CHECKED_BASE(_Last), _Dest, _Al,
		_Ptr_cat(_First, _Dest), _STD _Range_checked_iterator_tag()));
	}

#endif

    // TEMPLATE FUNCTION _Uninitialized_move WITH ALLOCATOR
    template<class _InIt, class _FwdIt, class _Alloc, class _MoveCatTy>
    inline _FwdIt _Uninit_move(
        _InIt _First,
        _InIt _Last,
        _FwdIt _Dest,
        _Alloc &_Al,
        _MoveCatTy,
        _Range_checked_iterator_tag) { // move defaults to copy if there is not a more effecient way
        return _STDEXT unchecked_uninitialized_copy(_First, _Last, _Dest, _Al);
    }

template<class _InIt, class _FwdIt, class _Alloc>
inline
	_FwdIt _Uninit_move(_InIt _First, _InIt _Last, _FwdIt _Dest,
		_Alloc& _Al, _Swap_move_tag, _Range_checked_iterator_tag)
	{	// use swap to instead of the copy constructor
	_DEBUG_RANGE(_First, _Last);
	_DEBUG_POINTER(_Dest);
	_FwdIt _Next = _Dest;
	// empty value used in the construction
	typename _Alloc::value_type _Val;

	_TRY_BEGIN
	for (; _First != _Last; ++_Dest, ++_First)
		{
		_Al.construct(_Dest, _Val);
		_STD swap(*_Dest, *_First);
		}
	_CATCH_ALL
	for (; _Next != _Dest; ++_Next)
		_Al.destroy(_Next);
	_RERAISE;
	_CATCH_END
	return (_Dest);
	}

#if _SECURE_SCL

template<class _InIt, class _FwdIt, class _Alloc>
inline
_IF_CHK(_FwdIt) _Uninitialized_move(_InIt _First, _InIt _Last, _FwdIt _Dest,
		_Alloc& _Al)
	{	// move [_First, _Last) to raw _Dest, using _Al
	return (_Uninit_move(_CHECKED_BASE(_First), _CHECKED_BASE(_Last), _Dest, _Al,
		_Move_cat(_Dest), _STD _Range_checked_iterator_tag()));
	}

template<class _InIt, class _FwdElem, class _Alloc, size_t _Size>
inline
_FwdElem* _Uninitialized_move(_InIt _First, _InIt _Last, _FwdElem (&_Dest)[_Size],
		_Alloc& _Al)
	{	// move [_First, _Last) to raw _Dest, using _Al
	return (_Uninitialized_move(_First, _Last,
		_STDEXT make_checked_array_iterator(_Dest, _Size), _Al).base());
	}

template<class _InIt, class _FwdIt, class _Alloc>
inline
_SCL_INSECURE_DEPRECATE
_IF_NOT_CHK(_FwdIt) _Uninitialized_move(_InIt _First, _InIt _Last, _FwdIt _Dest,
		_Alloc& _Al)
	{	// move [_First, _Last) to raw _Dest, using _Al
	return (_Uninit_move(_CHECKED_BASE(_First), _CHECKED_BASE(_Last), _Dest, _Al,
		_Move_cat(_Dest), _STD _Range_checked_iterator_tag()));
	}

#else

template<class _InIt, class _FwdIt, class _Alloc>
inline
	_FwdIt _Uninitialized_move(_InIt _First, _InIt _Last, _FwdIt _Dest,
		_Alloc& _Al)
	{	// move [_First, _Last) to raw _Dest, using _Al
	return (_Uninit_move(_CHECKED_BASE(_First), _CHECKED_BASE(_Last), _Dest, _Al,
		_Move_cat(_Dest), _STD _Range_checked_iterator_tag()));
	}

#endif

    // TEMPLATE FUNCTION uninitialized_fill
template<class _FwdIt,
	class _Tval> inline
	void _Uninit_fill(_FwdIt _First, _FwdIt _Last, const _Tval& _Val,
		_Nonscalar_ptr_iterator_tag)
	{	// copy _Val throughout raw [_First, _Last), arbitrary type
	_DEBUG_RANGE(_First, _Last);
	_FwdIt _Next = _First;

	_TRY_BEGIN
	for (; _First != _Last; ++_First)
		_Construct(&*_First, _Val);
	_CATCH_ALL
	for (; _Next != _First; ++_Next)
		_Destroy(&*_Next);
	_RERAISE;
	_CATCH_END
	}

template<class _Ty,
	class _Tval> inline
	void _Uninit_fill(_Ty *_First, _Ty *_Last, const _Tval& _Val,
		_Scalar_ptr_iterator_tag)
	{	// copy _Val throughout raw [_First, _Last), scalar type
	std::fill(_First, _Last, _Val);
	}

template<class _FwdIt,
	class _Tval> inline
	void uninitialized_fill(_FwdIt _First, _FwdIt _Last, const _Tval& _Val)
	{	// copy _Val throughout raw [_First, _Last)
	_Uninit_fill(_CHECKED_BASE(_First), _CHECKED_BASE(_Last), _Val, _Ptr_cat(_First, _First));
	}

		// TEMPLATE FUNCTION uninitialized_fill_n
template<class _FwdIt,
	class _Diff,
	class _Tval> inline
	void _Uninit_fill_n(_FwdIt _First, _Diff _Count, const _Tval& _Val,
		_Nonscalar_ptr_iterator_tag, _Range_checked_iterator_tag)
	{	// copy _Count *_Val to raw _First, arbitrary type

 #if _HAS_ITERATOR_DEBUGGING
//	if (_Count < 0)
//		_DEBUG_ERROR("negative count in uninitialized fill");
 #endif /* _HAS_ITERATOR_DEBUGGING */

	_FwdIt _Next = _First;

	_TRY_BEGIN
	for (; 0 < _Count; --_Count, ++_First)
		_Construct(&*_First, _Val);
	_CATCH_ALL
	for (; _Next != _First; ++_Next)
		_Destroy(&*_Next);
	_RERAISE;
	_CATCH_END
	}

template<class _FwdIt,
	class _Diff,
	class _Tval> inline
	void _Uninit_fill_n(_FwdIt _First, _Diff _Count, const _Tval& _Val,
		_Scalar_ptr_iterator_tag, _Range_checked_iterator_tag)
	{	// copy _Count *_Val to raw _First, scalar type
	_STDEXT unchecked_fill_n(&*_First, _Count, _Val);
	}

#if _SECURE_SCL

template<class _FwdIt,
	class _Diff,
	class _Tval> inline
_IF_CHK_(_FwdIt, void) uninitialized_fill_n(_FwdIt _First, _Diff _Count, const _Tval& _Val)
	{	// copy _Count *_Val to raw _First
	_Uninit_fill_n(_First, _Count, _Val, _Ptr_cat(_First, _First), _STD _Range_checked_iterator_tag());
	}

template<class _FwdElem, class _Diff, class _Tval, size_t _Size>
inline
void uninitialized_fill_n(_FwdElem (&_First)[_Size], _Diff _Count, const _Tval& _Val)
	{	// copy _Count *_Val to raw _First
	uninitialized_fill_n(_STDEXT make_checked_array_iterator(_First, _Size), _Count, _Val);
	}

template<class _FwdIt,
	class _Diff,
	class _Tval> inline
_SCL_INSECURE_DEPRECATE
_IF_NOT_CHK_(_FwdIt, void) uninitialized_fill_n(_FwdIt _First, _Diff _Count, const _Tval& _Val)
	{	// copy _Count *_Val to raw _First
	_Uninit_fill_n(_First, _Count, _Val, _Ptr_cat(_First, _First), _STD _Range_checked_iterator_tag());
	}

#else

template<class _FwdIt,
	class _Diff,
	class _Tval> inline
	void uninitialized_fill_n(_FwdIt _First, _Diff _Count, const _Tval& _Val)
	{	// copy _Count *_Val to raw _First
	_Uninit_fill_n(_First, _Count, _Val, _Ptr_cat(_First, _First), _STD _Range_checked_iterator_tag());
	}

#endif

		// TEMPLATE FUNCTION _Uninitialized_fill_n WITH ALLOCATOR
template<class _FwdIt,
	class _Diff,
	class _Tval,
	class _Alloc> inline
	void _Uninit_fill_n(_FwdIt _First, _Diff _Count,
		const _Tval& _Val, _Alloc& _Al, _Nonscalar_ptr_iterator_tag, _Range_checked_iterator_tag)
	{	// copy _Count *_Val to raw _First, using _Al, arbitrary type

 #if _HAS_ITERATOR_DEBUGGING
//	if (_Count < 0)
//		_DEBUG_ERROR("negative count in uninitialized fill");
 #endif /* _HAS_ITERATOR_DEBUGGING */

	_FwdIt _Next = _First;

	_TRY_BEGIN
	for (; 0 < _Count; --_Count, ++_First)
		_Al.construct(_First, _Val);
	_CATCH_ALL
	for (; _Next != _First; ++_Next)
		_Al.destroy(_Next);
	_RERAISE;
	_CATCH_END
	}

template<class _FwdIt,
	class _Diff,
	class _Tval,
	class _Alloc> inline
	void _Uninit_fill_n(_FwdIt _First, _Diff _Count,
		const _Tval& _Val, _Alloc&, _Scalar_ptr_iterator_tag, _Range_checked_iterator_tag)
	{	// copy _Count *_Val to raw _First, using _Al, scalar type
		_STDEXT unchecked_fill_n(_First, _Count, _Val);
	}

#if _SECURE_SCL

template<class _FwdIt,
	class _Diff,
	class _Tval,
	class _Alloc> inline
_IF_CHK_(_FwdIt, void) _Uninitialized_fill_n(_FwdIt _First, _Diff _Count,
		const _Tval& _Val, _Alloc& _Al)
	{	// copy _Count *_Val to raw _First, using _Al
	_Uninit_fill_n(_First, _Count, _Val, _Al,
		_Ptr_cat(_First, _First), _STD _Range_checked_iterator_tag());
	}

template<class _FwdElem, class _Diff, class _Tval, class _Alloc, size_t _Size>
inline
void _Uninitialized_fill_n(_FwdElem (&_First)[_Size], _Diff _Count,
		const _Tval& _Val, _Alloc& _Al)
	{	// copy _Count *_Val to raw _First, using _Al
	_Uninitialized_fill_n(_STDEXT make_checked_array_iterator(_First, _Size), _Count, _Val, _Al);
	}

template<class _FwdIt,
	class _Diff,
	class _Tval,
	class _Alloc> inline
_SCL_INSECURE_DEPRECATE
_IF_NOT_CHK_(_FwdIt, void) _Uninitialized_fill_n(_FwdIt _First, _Diff _Count,
		const _Tval& _Val, _Alloc& _Al)
	{	// copy _Count *_Val to raw _First, using _Al
	_Uninit_fill_n(_First, _Count, _Val, _Al,
		_Ptr_cat(_First, _First), _STD _Range_checked_iterator_tag());
	}

#else

template<class _FwdIt,
	class _Diff,
	class _Tval,
	class _Alloc> inline
	void _Uninitialized_fill_n(_FwdIt _First, _Diff _Count,
		const _Tval& _Val, _Alloc& _Al)
	{	// copy _Count *_Val to raw _First, using _Al
	_Uninit_fill_n(_First, _Count, _Val, _Al,
		_Ptr_cat(_First, _First), _STD _Range_checked_iterator_tag());
	}

#endif

		// TEMPLATE CLASS raw_storage_iterator
template<class _FwdIt,
	class _Ty>
	class raw_storage_iterator
		: public _Outit
	{	// wrap stores to raw buffer as output iterator
public:
	typedef _FwdIt iterator_type;	// retained
	typedef _FwdIt iter_type;	// retained
	typedef _Ty element_type;	// retained

	explicit raw_storage_iterator(_FwdIt _First)
		: _Next(_First)
		{	// construct with iterator
		}

	raw_storage_iterator<_FwdIt, _Ty>& operator*()
		{	// pretend to return designated value
		return (*this);
		}

	raw_storage_iterator<_FwdIt, _Ty>& operator=(const _Ty& _Val)
		{	// construct value designated by stored iterator
		_Construct(&*_Next, _Val);
		return (*this);
		}

	raw_storage_iterator<_FwdIt, _Ty>& operator++()
		{	// preincrement
		++_Next;
		return (*this);
		}

	raw_storage_iterator<_FwdIt, _Ty> operator++(int)
		{	// postincrement
		raw_storage_iterator<_FwdIt, _Ty> _Ans = *this;
		++_Next;
		return (_Ans);
		}

private:
	_FwdIt _Next;	// the stored iterator
	};

		// TEMPLATE CLASS _Temp_iterator
template<class _Ty>
	class _Temp_iterator
		: public _Outit
	{	// wrap stores to temporary buffer as output iterator
public:
	typedef _Ty _FARQ *_Pty;

#if _SECURE_SCL
	typedef _Range_checked_iterator_tag _Checked_iterator_category;
#endif

	_Temp_iterator(_PDFT _Count = 0)
		{	// construct from desired temporary buffer size
		_Buf._Begin = 0;
		_Buf._Current = 0;
		_Buf._Hiwater = 0;
		_Buf._Size = _Count;	// memorize size for lazy allocation
		_Pbuf = &_Buf;
		}

	_Temp_iterator(const _Temp_iterator<_Ty>& _Right)
		{	// construct from _Right (share active buffer)
		_Buf._Begin = 0;	// clear stored buffer, for safe destruction
		_Buf._Current = 0;
		_Buf._Hiwater = 0;
		_Buf._Size = 0;
		*this = _Right;
		}

	~_Temp_iterator()
		{	// destroy the object
		if (_Buf._Begin != 0)
			{	// destroy any constructed elements in buffer
			for (_Pty _Next = _Buf._Begin;
				_Next != _Buf._Hiwater; ++_Next)
                _Destroy(&*_Next);
            _std::return_temporary_buffer(_Buf._Begin);
        }
        }

	_Temp_iterator<_Ty>& operator=(const _Temp_iterator<_Ty>& _Right)
		{	// assign _Right (share active buffer)
		_Pbuf = _Right._Pbuf;
		return (*this);
		}

	_Temp_iterator<_Ty>& operator=(const _Ty& _Val)
		{	// assign or construct value into active buffer, and increment
		if (_Pbuf->_Current < _Pbuf->_Hiwater)
			*_Pbuf->_Current++ = _Val;	// below high water mark, assign
		else
			{	// above high water mark, construct
			_SCL_SECURE_VALIDATE((_Pbuf->_Current - _Pbuf->_Begin) < _Pbuf->_Size);
			_Pty _Ptr = &*_Pbuf->_Current;
			_Construct(_Ptr, _Val);
			_Pbuf->_Hiwater = ++_Pbuf->_Current;
			}
		return (*this);
		}

	_Temp_iterator<_Ty>& operator*()
		{	// pretend to return designated value
		return (*this);
		}

	_Temp_iterator<_Ty>& operator++()
		{	// pretend to preincrement
		return (*this);
		}

	_Temp_iterator<_Ty>& operator++(int)
		{	// pretend to postincrement
		return (*this);
		}

	_Temp_iterator<_Ty>& _Init()
		{	// set pointer at beginning of buffer
		_Pbuf->_Current = _Pbuf->_Begin;
		return (*this);
		}

	_Pty _First() const
		{	// return pointer to beginning of buffer
		return (_Pbuf->_Begin);
		}

	_Pty _Last() const
		{	// return pointer past end of buffer contents
		return (_Pbuf->_Current);
		}

	_PDFT _Maxlen()
		{	// return size of buffer
		if (_Pbuf->_Begin == 0 && 0 < _Pbuf->_Size)
			{	// allocate buffer on first size query
            pair<_Pty, _PDFT> _Pair = _std::get_temporary_buffer<_Ty>(_Pbuf->_Size);

            _Pbuf->_Begin = _Pair.first;
			_Pbuf->_Current = _Pair.first;
			_Pbuf->_Hiwater = _Pair.first;
            _Pbuf->_Size = _Pair.second;
        }
        return (_Pbuf->_Size);
    }

    static void _Xinvarg() { // report an invalid_argument error
        _THROW(std::invalid_argument, "invalid _Temp_iterator<T> argument");
    }

private:
	struct _Bufpar
		{	// control information for a temporary buffer
		_Pty _Begin;	// pointer to beginning of buffer
		_Pty _Current;	// pointer to next available element
		_Pty _Hiwater;	// pointer to first unconstructed element
		_PDFT _Size;	// length of buffer
		};
	_Bufpar _Buf;	// buffer control stored in iterator
	_Bufpar *_Pbuf;	// pointer to active buffer control
	};

		// TEMPLATE CLASS auto_ptr
template<class _Ty>
	class auto_ptr;

template<class _Ty>
	struct auto_ptr_ref
		{	// proxy reference for auto_ptr copying
	auto_ptr_ref(void *_Right)
		: _Ref(_Right)
		{	// construct from generic pointer to auto_ptr ptr
		}

	void *_Ref;	// generic pointer to auto_ptr ptr
	};

template<class _Ty>
	class auto_ptr
		{	// wrap an object pointer to ensure destruction
public:
	typedef _Ty element_type;

	explicit auto_ptr(_Ty *_Ptr = 0) _THROW0()
		: _Myptr(_Ptr)
		{	// construct from object pointer
		}

	auto_ptr(auto_ptr<_Ty>& _Right) _THROW0()
		: _Myptr(_Right.release())
		{	// construct by assuming pointer from _Right auto_ptr
		}

	auto_ptr(auto_ptr_ref<_Ty> _Right) _THROW0()
		{	// construct by assuming pointer from _Right auto_ptr_ref
		_Ty **_Pptr = (_Ty **)_Right._Ref;
		_Ty *_Ptr = *_Pptr;
		*_Pptr = 0;	// release old
		_Myptr = _Ptr;	// reset this
		}

	template<class _Other>
		operator auto_ptr<_Other>() _THROW0()
		{	// convert to compatible auto_ptr
		return (auto_ptr<_Other>(*this));
		}

	template<class _Other>
		operator auto_ptr_ref<_Other>() _THROW0()
		{	// convert to compatible auto_ptr_ref
		_Other *_Testptr = (_Ty *)_Myptr;	// test implicit conversion
		auto_ptr_ref<_Other> _Ans(&_Myptr);
		return (_Testptr != 0 ? _Ans : _Ans);
		}

	template<class _Other>
		auto_ptr<_Ty>& operator=(auto_ptr<_Other>& _Right) _THROW0()
		{	// assign compatible _Right (assume pointer)
		reset(_Right.release());
		return (*this);
		}

	template<class _Other>
		auto_ptr(auto_ptr<_Other>& _Right) _THROW0()
		: _Myptr(_Right.release())
		{	// construct by assuming pointer from _Right
		}

	auto_ptr<_Ty>& operator=(auto_ptr<_Ty>& _Right) _THROW0()
		{	// assign compatible _Right (assume pointer)
		reset(_Right.release());
		return (*this);
		}

	auto_ptr<_Ty>& operator=(auto_ptr_ref<_Ty> _Right) _THROW0()
		{	// assign compatible _Right._Ref (assume pointer)
		_Ty **_Pptr = (_Ty **)_Right._Ref;
		_Ty *_Ptr = *_Pptr;
		*_Pptr = 0;	// release old
		reset(_Ptr);	// set new
		return (*this);
		}

	~auto_ptr()
		{	// destroy the object
		delete (_Ty *)_Myptr;
		}

	_Ty& operator*() const _THROW0()
		{	// return designated value

 #if _HAS_ITERATOR_DEBUGGING
		if (_Myptr == 0)
			_DEBUG_ERROR("auto_ptr not dereferencable");
 #endif /* _HAS_ITERATOR_DEBUGGING */

		__analysis_assume(_Myptr);

		return (*(_Ty *)_Myptr);
		}

	_Ty *operator->() const _THROW0()
		{	// return pointer to class object
		return (&**this);
		}

	_Ty *get() const _THROW0()
		{	// return wrapped pointer
		return ((_Ty *)_Myptr);
		}

	_Ty *release() _THROW0()
		{	// return wrapped pointer and give up ownership
		_Ty *_Tmp = (_Ty *)_Myptr;
		_Myptr = 0;
		return (_Tmp);
		}

	void reset(_Ty* _Ptr = 0)
		{	// destroy designated object and store new pointer
		if (_Ptr != _Myptr)
			delete (_Ty *)_Myptr;
		_Myptr = _Ptr;
		}

private:
	const _Ty *_Myptr;	// the wrapped object pointer
	};
_STD_END

_STDEXT_BEGIN

template<class _InIt,
	class _FwdIt> inline
	_FwdIt unchecked_uninitialized_copy(_InIt _First, _InIt _Last, _FwdIt _Dest)
	{	// copy [_First, _Last) to raw _Dest
		return (_STD _Uninit_copy(_CHECKED_BASE(_First), _CHECKED_BASE(_Last), _Dest,
			_STD _Ptr_cat(_First, _Dest), _STD _Range_checked_iterator_tag()));
	}

template<class _InIt,
	class _FwdIt> inline
_IF_CHK(_FwdIt) checked_uninitialized_copy(_InIt _First, _InIt _Last, _FwdIt _Dest)
	{	// copy [_First, _Last) to raw _Dest
	return (_STD _Uninit_copy(_CHECKED_BASE(_First), _CHECKED_BASE(_Last), _Dest,
		_STD _Ptr_cat(_First, _Dest), _STD _Range_checked_iterator_tag()));
	}

template<class _InIt, class _FwdElem, size_t _Size>
inline
_FwdElem* checked_uninitialized_copy(_InIt _First, _InIt _Last, _FwdElem (&_Dest)[_Size])
	{	// copy [_First, _Last) to raw _Dest
	return (checked_uninitialized_copy(_First, _Last,
		_STDEXT make_checked_array_iterator(_Dest, _Size)).base());
	}

template<class _InIt,
	class _FwdIt> inline
_SCL_CHECKED_ALGORITHM_WARN
_IF_NOT_CHK(_FwdIt) checked_uninitialized_copy(_InIt _First, _InIt _Last, _FwdIt _Dest)
	{	// copy [_First, _Last) to raw _Dest
	return (_STD _Uninit_copy(_CHECKED_BASE(_First), _CHECKED_BASE(_Last), _Dest,
		_STD _Ptr_cat(_First, _Dest), _STD _Range_checked_iterator_tag()));
	}

template<class _InIt,
	class _FwdIt,
	class _Alloc> inline
	_FwdIt unchecked_uninitialized_copy(_InIt _First, _InIt _Last, _FwdIt _Dest,
		_Alloc& _Al)
	{	// copy [_First, _Last) to raw _Dest, using _Al
		return (_STD _Uninit_copy(_CHECKED_BASE(_First), _CHECKED_BASE(_Last), _Dest, _Al,
			_STD _Ptr_cat(_First, _Dest), _STD _Range_checked_iterator_tag()));
	}

template<class _InIt,
	class _FwdIt,
	class _Alloc> inline
_IF_CHK(_FwdIt) checked_uninitialized_copy(_InIt _First, _InIt _Last, _FwdIt _Dest,
		_Alloc& _Al)
	{	// copy [_First, _Last) to raw _Dest, using _Al
	return (_STD _Uninit_copy(_CHECKED_BASE(_First), _CHECKED_BASE(_Last), _Dest, _Al,
		_STD _Ptr_cat(_First, _Dest), _STD _Range_checked_iterator_tag()));
	}

template<class _InIt, class _FwdElem, class _Alloc, size_t _Size>
inline
_FwdElem* checked_uninitialized_copy(_InIt _First, _InIt _Last, _FwdElem (&_Dest)[_Size],
		_Alloc& _Al)
	{	// copy [_First, _Last) to raw _Dest, using _Al
	return (checked_uninitialized_copy(_First, _Last,
		_STDEXT make_checked_array_iterator(_Dest, _Size), _Al).base());
	}

template<class _InIt,
	class _FwdIt,
	class _Alloc> inline
_SCL_CHECKED_ALGORITHM_WARN
_IF_NOT_CHK(_FwdIt) checked_uninitialized_copy(_InIt _First, _InIt _Last, _FwdIt _Dest,
		_Alloc& _Al)
	{	// copy [_First, _Last) to raw _Dest, using _Al
	return (_STD _Uninit_copy(_CHECKED_BASE(_First), _CHECKED_BASE(_Last), _Dest, _Al,
		_STD _Ptr_cat(_First, _Dest), _STD _Range_checked_iterator_tag()));
	}

template<class _InIt,
	class _FwdIt,
	class _Alloc> inline
	_FwdIt _Unchecked_uninitialized_move(_InIt _First, _InIt _Last, _FwdIt _Dest,
		_Alloc& _Al)
	{	// move [_First, _Last) to raw _Dest, using _Al
		return (_STD _Uninit_move(_CHECKED_BASE(_First), _CHECKED_BASE(_Last), _Dest, _Al,
			_STD _Move_cat(_Dest), _STD _Range_checked_iterator_tag()));
	}

template<class _InIt, class _FwdIt, class _Alloc>
inline
_IF_CHK(_FwdIt) _Checked_uninitialized_move(_InIt _First, _InIt _Last, _FwdIt _Dest,
		_Alloc& _Al)
	{	// move [_First, _Last) to raw _Dest, using _Al
	return (_STD _Uninit_move(_CHECKED_BASE(_First), _CHECKED_BASE(_Last), _Dest, _Al,
		_STD _Move_cat(_Dest), _STD _Range_checked_iterator_tag()));
	}

template<class _InIt, class _FwdElem, class _Alloc, size_t _Size>
inline
_FwdElem* _Checked_uninitialized_move(_InIt _First, _InIt _Last, _FwdElem (&_Dest)[_Size],
		_Alloc& _Al)
	{	// move [_First, _Last) to raw _Dest, using _Al
	return (_Checked_uninitialized_move(_First, _Last,
		_STDEXT make_checked_array_iterator(_Dest, _Size), _Al).base());
	}

template<class _InIt, class _FwdIt, class _Alloc>
inline
_SCL_CHECKED_ALGORITHM_WARN
_IF_NOT_CHK(_FwdIt) _Checked_uninitialized_move(_InIt _First, _InIt _Last, _FwdIt _Dest,
		_Alloc& _Al)
	{	// move [_First, _Last) to raw _Dest, using _Al
	return (_STD _Uninit_move(_CHECKED_BASE(_First), _CHECKED_BASE(_Last), _Dest, _Al,
		_STD _Move_cat(_Dest), _STD _Range_checked_iterator_tag()));
	}

template<class _FwdIt,
	class _Diff,
	class _Tval> inline
	void unchecked_uninitialized_fill_n(_FwdIt _First, _Diff _Count, const _Tval& _Val)
	{	// copy _Count *_Val to raw _First
		_STD _Uninit_fill_n(_First, _Count, _Val, _STD _Ptr_cat(_First, _First), _STD _Range_checked_iterator_tag());
	}

template<class _FwdIt,
	class _Diff,
	class _Tval> inline
_IF_CHK_(_FwdIt, void) checked_uninitialized_fill_n(_FwdIt _First, _Diff _Count, const _Tval& _Val)
	{	// copy _Count *_Val to raw _First
	_STD _Uninit_fill_n(_First, _Count, _Val, _STD _Ptr_cat(_First, _First), _STD _Range_checked_iterator_tag());
	}

template<class _FwdElem, class _Diff, class _Tval, size_t _Size>
inline
void checked_uninitialized_fill_n(_FwdElem (&_First)[_Size], _Diff _Count, const _Tval& _Val)
	{	// copy _Count *_Val to raw _First
	checked_uninitialized_fill_n(_STDEXT make_checked_array_iterator(_First, _Size), _Count, _Val);
	}

template<class _FwdIt,
	class _Diff,
	class _Tval> inline
_SCL_CHECKED_ALGORITHM_WARN
_IF_NOT_CHK_(_FwdIt, void) checked_uninitialized_fill_n(_FwdIt _First, _Diff _Count, const _Tval& _Val)
	{	// copy _Count *_Val to raw _First
	_STD _Uninit_fill_n(_First, _Count, _Val, _STD _Ptr_cat(_First, _First), _STD _Range_checked_iterator_tag());
	}

template<class _FwdIt,
	class _Diff,
	class _Tval,
	class _Alloc> inline
	void unchecked_uninitialized_fill_n(_FwdIt _First, _Diff _Count,
		const _Tval& _Val, _Alloc& _Al)
	{	// copy _Count *_Val to raw _First, using _Al
		_STD _Uninit_fill_n(_First, _Count, _Val, _Al,
			_STD _Ptr_cat(_First, _First), _STD _Range_checked_iterator_tag());
	}

template<class _FwdIt,
	class _Diff,
	class _Tval,
	class _Alloc> inline
_IF_CHK_(_FwdIt, void) checked_uninitialized_fill_n(_FwdIt _First, _Diff _Count,
		const _Tval& _Val, _Alloc& _Al)
	{	// copy _Count *_Val to raw _First, using _Al
	_STD _Uninit_fill_n(_First, _Count, _Val, _Al,
		_STD _Ptr_cat(_First, _First), _STD _Range_checked_iterator_tag());
	}

template<class _FwdElem, class _Diff, class _Tval, class _Alloc, size_t _Size>
inline
void checked_uninitialized_fill_n(_FwdElem (&_First)[_Size], _Diff _Count,
		const _Tval& _Val, _Alloc& _Al)
	{	// copy _Count *_Val to raw _First, using _Al
	checked_uninitialized_fill_n(_STDEXT make_checked_array_iterator(_First, _Size), _Count, _Val, _Al);
	}

template<class _FwdIt,
	class _Diff,
	class _Tval,
	class _Alloc> inline
_SCL_CHECKED_ALGORITHM_WARN
_IF_NOT_CHK_(_FwdIt, void) checked_uninitialized_fill_n(_FwdIt _First, _Diff _Count,
		const _Tval& _Val, _Alloc& _Al)
	{	// copy _Count *_Val to raw _First, using _Al
	_STD _Uninit_fill_n(_First, _Count, _Val, _Al,
		_STD _Ptr_cat(_First, _First), _STD _Range_checked_iterator_tag());
	}

_STDEXT_END

#ifdef  _MSC_VER
#pragma warning(pop)
#pragma pack(pop)
#endif  /* _MSC_VER */

#endif /* RC_INVOKED */
#endif /* _MEMORY_ */

/*
 * Copyright (c) 1992-2005 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
 */

/*
 * This file is derived from software bearing the following
 * restrictions:
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this
 * software and its documentation for any purpose is hereby
 * granted without fee, provided that the above copyright notice
 * appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation.
 * Hewlett-Packard Company makes no representations about the
 * suitability of this software for any purpose. It is provided
 * "as is" without express or implied warranty.
 V4.05:0009 */
