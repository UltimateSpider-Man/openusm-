// deque standard header
#pragma once
#ifndef _DEQUE_
#define _DEQUE_

#include "memory.hpp"

#include <stdexcept>

#pragma pack(push,8)
#pragma warning(push,3)

namespace _std {

// TEMPLATE CLASS _Deque_map
template<class _Ty,
	class _Alloc>
	class _Deque_map
	{	// ultimate base class for deque to hold allocator _Almap
protected:
	_Deque_map(_Alloc _Al)
		: _Almap(_Al)
		{	// construct allocator from _Al
		}

	typedef typename _Alloc::template rebind<_Ty>::other::pointer
		_Tptr;

	typename _Alloc::template rebind<_Tptr>::other
		_Almap;	// allocator object for maps
	};

		// TEMPLATE CLASS _Deque_val
template<class _Ty,
	class _Alloc>
	class _Deque_val
		: public _Deque_map<_Ty, _Alloc>
	{	// base class for deque to hold allocator _Alval
protected:
	_Deque_val(_Alloc _Al = _Alloc())
		: _Deque_map<_Ty, _Alloc>(_Al), _Alval(_Al)
		{	// construct allocator and base from _Al
		}

	typedef typename _Alloc::template rebind<_Ty>::other
		_Alty;

	_Alty _Alval;	// allocator object for stored elements
};

// TEMPLATE CLASS deque
template<class _Ty, class _Ax = std::allocator<_Ty>>
class deque : public _Deque_val<_Ty, _Ax> { // circular queue of pointers to blocks
public:
    enum {                // deque parameters
        _DEQUEMAPSIZ = 8, /* minimum map size, at least 1 */
        _DEQUESIZ = sizeof(_Ty) <= 1 ? 16
            : sizeof(_Ty) <= 2       ? 8
            : sizeof(_Ty) <= 4       ? 4
            : sizeof(_Ty) <= 8       ? 2
                                     : 1
    }; // elements per block

    typedef deque<_Ty, _Ax> _Myt;
    typedef _Deque_val<_Ty, _Ax> _Mybase;
    typedef typename _Mybase::_Alty _Alloc;
    typedef _Alloc allocator_type;
    typedef typename _Alloc::size_type size_type;
    typedef typename _Alloc::difference_type _Dift;
    typedef _Dift difference_type;
    typedef typename _Alloc::pointer _Tptr;
    typedef typename _Alloc::const_pointer _Ctptr;
    typedef _Tptr pointer;
    typedef _Ctptr const_pointer;
    typedef _POINTER_X(_Tptr, _Alloc) _Mapptr;
    typedef typename _Alloc::reference _Reft;
    typedef _Reft reference;
    typedef typename _Alloc::const_reference const_reference;
    typedef typename _Alloc::value_type value_type;

    // CLASS const_iterator
    class const_iterator;
	friend class const_iterator;

	class const_iterator
		: public _Ranit<_Ty, _Dift, _Ctptr, const_reference>
		{	// iterator for nonmutable deque
	public:
		typedef random_access_iterator_tag iterator_category;
		typedef _Ty value_type;
		typedef _Dift difference_type;
		typedef _Ctptr pointer;
		typedef const_reference reference;

		const_iterator()
			{	// construct with null deque pointer
			_Mycont = 0;
			_Myoff = 0;
			}

		const_iterator(size_type _Off, const _Myt *_Pdeque)
			{	// construct with offset _Off in *_Pdeque
			_Mycont = _Pdeque;
			_Myoff = _Off;
			}

		const_reference operator*() const
			{	// return designated object
			size_type _Block = _Myoff / _DEQUESIZ;
			size_type _Off = _Myoff - _Block * _DEQUESIZ;
			if (_Mycont->_Mapsize <= _Block)
				_Block -= _Mycont->_Mapsize;
			return ((_Mycont->_Map)[_Block][_Off]);
			}

		_Ctptr operator->() const
			{	// return pointer to class object
			return (&**this);
			}

		const_iterator& operator++()
			{	// preincrement
			++_Myoff;
			return (*this);
			}

		const_iterator operator++(int)
			{	// postincrement
			const_iterator _Tmp = *this;
			++*this;
			return (_Tmp);
			}

		const_iterator& operator--()
			{	// predecrement
			--_Myoff;
			return (*this);
			}

		const_iterator operator--(int)
			{	// postdecrement
			const_iterator _Tmp = *this;
			--*this;
			return (_Tmp);
			}

		const_iterator& operator+=(difference_type _Off)
			{	// increment by integer
			_Myoff += _Off;
			return (*this);
			}

		const_iterator operator+(difference_type _Off) const
			{	// return this + integer
			const_iterator _Tmp = *this;
			return (_Tmp += _Off);
			}

		const_iterator& operator-=(difference_type _Off)
			{	// decrement by integer
			return (*this += -_Off);
			}

		const_iterator operator-(difference_type _Off) const
			{	// return this - integer
			const_iterator _Tmp = *this;
			return (_Tmp -= _Off);
			}

		difference_type operator-(const const_iterator& _Right) const
			{	// return difference of iterators
			return (_Right._Myoff <= _Myoff ? _Myoff - _Right._Myoff
				: -(difference_type)(_Right._Myoff - _Myoff));
			}

		const_reference operator[](difference_type _Off) const
			{	// subscript
			return (*(*this + _Off));
			}

		bool operator==(const const_iterator& _Right) const
			{	// test for iterator equality
			return (_Mycont == _Right._Mycont && _Myoff == _Right._Myoff);
			}

		bool operator!=(const const_iterator& _Right) const
			{	// test for iterator inequality
			return (!(*this == _Right));
			}

		bool operator<(const const_iterator& _Right) const
			{	// test if this < _Right
			return (_Mycont == _Right._Mycont && _Myoff < _Right._Myoff);
			}

		bool operator>(const const_iterator& _Right) const
			{	// test if this > _Right
			return (_Right < *this);
			}

		bool operator<=(const const_iterator& _Right) const
			{	// test if this <= _Right
			return (!(_Right < *this));
			}

		bool operator>=(const const_iterator& _Right) const
			{	// test if this >= _Right
			return (!(*this < _Right));
			}

		friend const_iterator operator+(difference_type _Off,
			const const_iterator& _Right)
			{	// return iterator + integer
			return (_Right + _Off);
			}

	protected:
		const _Myt *_Mycont;	// pointer to deque
		size_type _Myoff;	// offset of element in deque
		};

		// CLASS iterator
	class iterator;
	friend class iterator;

	class iterator
		: public const_iterator
		{	// iterator for mutable deque
	public:
		typedef random_access_iterator_tag iterator_category;
		typedef _Ty value_type;
		typedef _Dift difference_type;
		typedef _Tptr pointer;
		typedef _Reft reference;

		iterator()
			{	// construct with null deque pointer
			}

		iterator(size_type _Off, const deque<_Ty, _Alloc> *_Pdeque)
			: const_iterator(_Off, _Pdeque)
			{	// construct with offset _Off in *_Pdeque
			}

		reference operator*() const
			{	// return designated object
			return ((reference)**(const_iterator *)this);
			}

		_Tptr operator->() const
			{	// return pointer to class object
			return (&**this);
			}

		iterator& operator++()
			{	// preincrement
			++this->_Myoff;
			return (*this);
			}

		iterator operator++(int)
			{	// postincrement
			iterator _Tmp = *this;
			++*this;
			return (_Tmp);
			}

		iterator& operator--()
			{	// predecrement
			--this->_Myoff;
			return (*this);
			}

		iterator operator--(int)
			{	// postdecrement
			iterator _Tmp = *this;
			--*this;
			return (_Tmp);
			}

		iterator& operator+=(difference_type _Off)
			{	// increment by integer
			this->_Myoff += _Off;
			return (*this);
			}

		iterator operator+(difference_type _Off) const
			{	// return this + integer
			iterator _Tmp = *this;
			return (_Tmp += _Off);
			}

		iterator& operator-=(difference_type _Off)
			{	// decrement by integer
			return (*this += -_Off);
			}

		iterator operator-(difference_type _Off) const
			{	// return this - integer
			iterator _Tmp = *this;
			return (_Tmp -= _Off);
			}

		difference_type operator-(const const_iterator& _Right) const
			{	// return difference of iterators
			return ((const_iterator)*this - _Right);
			}

		reference operator[](difference_type _Off) const
			{	// subscript
			return (*(*this + _Off));
			}

		friend iterator operator+(difference_type _Off,
			const iterator& _Right)
			{	// return iterator + integer
			return (_Right + _Off);
			}
		};

	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	deque()
		: _Mybase(), _Map(0),
			_Mapsize(0), _Myoff(0), _Mysize(0)
		{	// construct empty deque
		}

	explicit deque(const _Alloc& _Al)
		: _Mybase(_Al), _Map(0),
			_Mapsize(0), _Myoff(0), _Mysize(0)
		{	// construct empty deque with allocator
		}

	explicit deque(size_type _Count)
		: _Mybase(), _Map(0),
			_Mapsize(0), _Myoff(0), _Mysize(0)
		{	// construct from _Count * _Ty()
		_Construct_n(_Count, _Ty());
		}

	deque(size_type _Count, const _Ty& _Val)
		: _Mybase(), _Map(0),
			_Mapsize(0), _Myoff(0), _Mysize(0)
		{	// construct from _Count * _Val
		_Construct_n(_Count, _Val);
		}

	deque(size_type _Count, const _Ty& _Val, const _Alloc& _Al)
		: _Mybase(_Al), _Map(0),
			_Mapsize(0), _Myoff(0), _Mysize(0)
		{	// construct from _Count * _Val with allocator
		_Construct_n(_Count, _Val);
		}

	deque(const _Myt& _Right)
		: _Mybase(_Right._Alval), _Map(0),
			_Mapsize(0), _Myoff(0), _Mysize(0)
		{	// construct by copying _Right
		_TRY_BEGIN
		insert(begin(), _Right.begin(), _Right.end());
		_CATCH_ALL
		_Tidy();
		_RERAISE;
		_CATCH_END
		}

	template<class _It>
		deque(_It _First, _It _Last)
		: _Mybase(), _Map(0),
			_Mapsize(0), _Myoff(0), _Mysize(0)
		{	// construct from [_First, _Last)
		_Construct(_First, _Last, _Iter_cat(_First));
		}

	template<class _It>
		deque(_It _First, _It _Last, const _Alloc& _Al)
		: _Mybase(_Al), _Map(0),
			_Mapsize(0), _Myoff(0), _Mysize(0)
		{	// construct from [_First, _Last) with allocator
		_Construct(_First, _Last, _Iter_cat(_First));
		}

	template<class _It>
		void _Construct(_It _Count, _It _Val, _Int_iterator_tag)
		{	// initialize from _Count * _Val
		_Construct_n((size_type)_Count, (_Ty)_Val);
		}

	template<class _It>
		void _Construct(_It _First, _It _Last, input_iterator_tag)
		{	// initialize from [_First, _Last), input iterators
		_TRY_BEGIN
		insert(begin(), _First, _Last);
		_CATCH_ALL
		_Tidy();
		_RERAISE;
		_CATCH_END
		}

	void _Construct_n(size_type _Count, const _Ty& _Val)
		{	// construct from _Count * _Val
		_TRY_BEGIN
		_Insert_n(begin(), _Count, _Val);
		_CATCH_ALL
		_Tidy();
		_RERAISE;
		_CATCH_END
		}

	~deque()
		{	// destroy the deque
		_Tidy();
		}

	_Myt& operator=(const _Myt& _Right)
		{	// assign _Right
		if (this == &_Right)
			;
		else if (_Right._Mysize == 0)
			clear();
		else if (_Right._Mysize <= _Mysize)
			{	// new sequence not longer, assign elements and erase unused
			iterator _Mid = copy(_Right.begin(), _Right.end(), begin());
			erase(_Mid, end());
			}
		else
			{	// new sequence longer, assign elements and append rest
			const_iterator _Mid = _Right.begin() + _Mysize;
			copy(_Right.begin(), _Mid, begin());
			insert(end(), _Mid, _Right.end());
			}
		return (*this);
		}

	iterator begin()
		{	// return iterator for beginning of mutable sequence
		return (iterator(_Myoff, this));
		}

	const_iterator begin() const
		{	// return iterator for beginning of nonmutable sequence
		return (const_iterator(_Myoff, this));
		}

	iterator end()
		{	// return iterator for end of mutable sequence
		return (iterator(_Myoff + _Mysize, this));
		}

	const_iterator end() const
		{	// return iterator for end of nonmutable sequence
		return (const_iterator(_Myoff + _Mysize, this));
		}

	reverse_iterator rbegin()
		{	// return iterator for beginning of reversed mutable sequence
		return (reverse_iterator(end()));
		}

	const_reverse_iterator rbegin() const
		{	// return iterator for beginning of reversed nonmutable sequence
		return (const_reverse_iterator(end()));
		}

	reverse_iterator rend()
		{	// return iterator for end of reversed mutable sequence
		return (reverse_iterator(begin()));
		}

	const_reverse_iterator rend() const
		{	// return iterator for end of reversed nonmutable sequence
		return (const_reverse_iterator(begin()));
		}

	void resize(size_type _Newsize)
		{	// determine new length, padding with _Ty() elements as needed
		resize(_Newsize, _Ty());
		}

	void resize(size_type _Newsize, _Ty _Val)
		{	// determine new length, padding with _Val elements as needed
		if (_Mysize < _Newsize)
			_Insert_n(end(), _Newsize - _Mysize, _Val);
		else if (_Newsize < _Mysize)
			erase(begin() + _Newsize, end());
		}

	size_type size() const
		{	// return length of sequence
		return (_Mysize);
		}

	size_type max_size() const
		{	// return maximum possible length of sequence
		return (this->_Alval.max_size());
		}

	bool empty() const
		{	// test if sequence is empty
		return (_Mysize == 0);
		}

	allocator_type get_allocator() const
		{	// return allocator object for values
		return (this->_Alval);
		}

	const_reference at(size_type _Pos) const
		{	// subscript nonmutable sequence with checking
		if (_Mysize <= _Pos)
			_Xran();
		return (*(begin() + _Pos));
		}

	reference at(size_type _Pos)
		{	// subscript mutable sequence with checking
		if (_Mysize <= _Pos)
			_Xran();
		return (*(begin() + _Pos));
		}

	const_reference operator[](size_type _Pos) const
		{	// subscript nonmutable sequence
		return (*(begin() + _Pos));
		}

	reference operator[](size_type _Pos)
		{	// subscript mutable sequence
		return (*(begin() + _Pos));
		}

	reference front()
		{	// return first element of mutable sequence
		return (*begin());
		}

	const_reference front() const
		{	// return first element of nonmutable sequence
		return (*begin());
		}

	reference back()
		{	// return last element of mutable sequence
		return (*(end() - 1));
		}

	const_reference back() const
		{	// return last element of nonmutable sequence
		return (*(end() - 1));
		}

	void push_front(const _Ty& _Val)
		{	// insert element at beginning
		if (_Myoff % _DEQUESIZ == 0
			&& _Mapsize <= (_Mysize + _DEQUESIZ) / _DEQUESIZ)
			_Growmap(1);
		size_type _Newoff = _Myoff != 0 ? _Myoff
			: _Mapsize * _DEQUESIZ;
		size_type _Block = --_Newoff / _DEQUESIZ;
		if (_Map[_Block] == 0)
			_Map[_Block] = this->_Alval.allocate(_DEQUESIZ);
		this->_Alval.construct(_Map[_Block] + _Newoff % _DEQUESIZ, _Val);
		_Myoff = _Newoff;
		++_Mysize;
		}

	void pop_front()
		{	// erase element at beginning
		if (!empty())
			{	// something to erase, do it
			size_type _Block = _Myoff / _DEQUESIZ;
			this->_Alval.destroy(_Map[_Block] + _Myoff % _DEQUESIZ);
			if (_Mapsize * _DEQUESIZ <= ++_Myoff)
				_Myoff = 0;
			if (--_Mysize == 0)
				_Myoff = 0;
			}
		}

	void push_back(const _Ty& _Val)
		{	// insert element at end
		if ((_Myoff + _Mysize) % _DEQUESIZ == 0
			&& _Mapsize <= (_Mysize + _DEQUESIZ) / _DEQUESIZ)
			_Growmap(1);
		size_type _Newoff = _Myoff + _Mysize;
		size_type _Block = _Newoff / _DEQUESIZ;
		if (_Mapsize <= _Block)
			_Block -= _Mapsize;
		if (_Map[_Block] == 0)
			_Map[_Block] = this->_Alval.allocate(_DEQUESIZ);
		this->_Alval.construct(_Map[_Block] + _Newoff % _DEQUESIZ, _Val);
		++_Mysize;
		}

	void pop_back()
		{	// erase element at end
		if (!empty())
			{	// something to erase, do it
			size_type _Newoff = _Mysize + _Myoff - 1;
			size_type _Block = _Newoff / _DEQUESIZ;
			if (_Mapsize <= _Block)
				_Block -= _Mapsize;
			this->_Alval.destroy(_Map[_Block] + _Newoff % _DEQUESIZ);
			if (--_Mysize == 0)
				_Myoff = 0;
			}
		}

	template<class _It>
		void assign(_It _First, _It _Last)
		{	// assign [_First, _Last)
		_Assign(_First, _Last, _Iter_cat(_First));
		}

	template<class _It>
		void _Assign(_It _Count, _It _Val, _Int_iterator_tag)
		{	// assign _Count * _Val
		_Assign_n((size_type)_Count, (_Ty)_Val);
		}

	template<class _It>
		void _Assign(_It _First, _It _Last, input_iterator_tag)
		{	// assign [_First, _Last), input iterators
		erase(begin(), end());
		insert(begin(), _First, _Last);
		}

	void assign(size_type _Count, const _Ty& _Val)
		{	// assign _Count * _Val
		_Assign_n(_Count, _Val);
		}

	iterator insert(iterator _Where, const _Ty& _Val)
		{	// insert _Val at _Where
		if (_Where == begin())
			{	// insert at front
			push_front(_Val);
			return (begin());
			}
		else if (_Where == end())
			{	// insert at back
			push_back(_Val);
			return (end() - 1);
			}
		else
			{	// insert inside sequence
			iterator _Mid;
			size_type _Off = _Where - begin();
			_Ty _Tmp = _Val;	// in case _Val is in sequence

			if (_Off < _Mysize / 2)
				{	// closer to front, push to front then copy
				push_front(front());
				_Mid = begin() + _Off;
				copy(begin() + 2, _Mid + 1, begin() + 1);
				}
			else
				{	// closer to back, push to back then copy
				push_back(back());
				_Mid = begin() + _Off;
				copy_backward(_Mid, end() - 2, end() - 1);
				}

			*_Mid = _Tmp;	// store inserted value
			return (_Mid);
			}
		}

	void insert(iterator _Where, size_type _Count, const _Ty& _Val)
		{	// insert _Count * _Val at _Where
		_Insert_n(_Where, _Count, _Val);
		}

	template<class _It>
		void insert(iterator _Where, _It _First, _It _Last)
		{	// insert [_First, _Last) at _Where
		_Insert(_Where, _First, _Last, _Iter_cat(_First));
		}

	template<class _It>
		void _Insert(iterator _Where, _It _Count, _It _Val,
			_Int_iterator_tag)
		{	// insert _Count * _Val at _Where
		_Insert_n(_Where, (size_type)_Count, (_Ty)_Val);
		}

	template<class _It>
		void _Insert(iterator _Where, _It _First, _It _Last,
			input_iterator_tag)
		{	// insert [_First, _Last) at _Where, input iterators
		size_type _Off = _Where - begin();
		for (; _First != _Last; ++_First, ++_Off)
			insert(begin() + _Off, *_First);
		}

	template<class _It>
		void _Insert(iterator _Where,
			_It _First, _It _Last, bidirectional_iterator_tag)
		{	// insert [_First, _Last) at _Where, bidirectional iterators
		size_type _Off = _Where - begin();
		size_type _Rem = _Mysize - _Off;
		size_type _Oldsize = _Mysize;
		size_type _Count = 0;
		_Distance(_First, _Last, _Count);
		size_type _Num;

		if (_Off < _Rem)
			{	// closer to front
			_TRY_BEGIN
			if (_Off < _Count)
				{	// insert longer than prefix
				_It _Mid = _First;
				advance(_Mid, _Count - _Off);

				for (_It _Next = _Mid; _First != _Next; )
					push_front(*--_Next);	// push head of insert
				for (_Num = _Off; 0 < _Num; --_Num)
					push_front(begin()[_Count - 1]);	// push prefix
				copy(_Mid, _Last, begin() + _Count);	// copy rest of insert
				}
			else
				{	// insert not longer than prefix
				for (_Num = _Count; 0 < _Num; --_Num)
					push_front(begin()[_Count - 1]);	// push part of prefix

				iterator _Mid = begin() + _Count;
				copy(_Mid + _Count, _Mid + _Off, _Mid);	// copy rest of prefix
				copy(_First, _Last, begin() + _Off);	// copy in insert
				}
			_CATCH_ALL
			for (; _Oldsize < _Mysize; )
				pop_front();	// restore old size, at least
			_RERAISE;
			_CATCH_END
			}
		else
			{	// closer to back
			_TRY_BEGIN
			if (_Rem < _Count)
				{	// insert longer than suffix
				_It _Mid = _First;
				advance(_Mid, _Rem);

				for (_It _Next = _Mid; _Next != _Last; ++_Next)
					push_back(*_Next);	// push tail of insert
				for (_Num = 0; _Num < _Rem; ++_Num)
					push_back(begin()[_Off + _Num]);	// push suffix

				copy(_First, _Mid, begin() + _Off);	// copy rest of insert
				}
			else
				{	// insert not longer than suffix
				for (_Num = 0; _Num < _Count; ++_Num)
					push_back(begin()[_Off + _Rem
						- _Count + _Num]);	// push part of suffix

				iterator _Mid = begin() + _Off;
				copy_backward(_Mid, _Mid + _Rem - _Count,
					_Mid + _Rem);	// copy rest of prefix
				copy(_First, _Last, _Mid);	// copy in values
				}
			_CATCH_ALL
			for (; _Oldsize < _Mysize; )
				pop_back();	// restore old size, at least
			_RERAISE;
			_CATCH_END
			}
		}

	iterator erase(iterator _Where)
		{	// erase element at _Where
		return (erase(_Where, _Where + 1));
		}

	iterator erase(iterator _First, iterator _Last)
		{	// erase [_First, _Last)
		size_type _Off = _First - begin();
		size_type _Count = _Last - _First;

		if (_Off < (size_type)(end() - _Last))
			{	// closer to front
			copy_backward(begin(), _First, _Last);	// copy over hole
			for (; 0 < _Count; --_Count)
				pop_front();	// pop copied elements
			}
		else
			{	// closer to back
			copy(_Last, end(), _First);	// copy over hole
			for (; 0 < _Count; --_Count)
				pop_back();	// pop copied elements
			}
		return (begin() + _Off);
		}

	void clear()
		{	// erase all
		_Tidy();
		}

	void swap(_Myt& _Right)
		{	// exchange contents with _Right
		if (this->_Alval == _Right._Alval)
			{	// same allocator, swap control information
			std::swap(_Map, _Right._Map);
			std::swap(_Mapsize, _Right._Mapsize);
			std::swap(_Myoff, _Right._Myoff);
			std::swap(_Mysize, _Right._Mysize);
			}
		else
			{	// different allocator, do multiple assigns
			_Myt _Ts = *this; *this = _Right, _Right = _Ts;
			}
		}

protected:
	void _Assign_n(size_type _Count, const _Ty& _Val)
		{	// assign _Count * _Val
		_Ty _Tmp = _Val;	// in case _Val is in sequence
		erase(begin(), end());
		_Insert_n(begin(), _Count, _Tmp);
		}

	void _Insert_n(iterator _Where,
		size_type _Count, const _Ty& _Val)
		{	// insert _Count * _Val at _Where
		iterator _Mid;
		size_type _Num;
		size_type _Off = _Where - begin();
		size_type _Rem = _Mysize - _Off;
		size_type _Oldsize = _Mysize;

		if (_Off < _Rem)
			{	// closer to front
			_TRY_BEGIN
			if (_Off < _Count)
				{	// insert longer than prefix
				for (_Num = _Count - _Off; 0 < _Num; --_Num)
					push_front(_Val);	// push excess values
				for (_Num = _Off; 0 < _Num; --_Num)
					push_front(begin()[_Count - 1]);	// push prefix

				_Mid = begin() + _Count;
				fill(_Mid, _Mid + _Off, _Val);	// fill in rest of values
				}
			else
				{	// insert not longer than prefix
				for (_Num = _Count; 0 < _Num; --_Num)
					push_front(begin()[_Count - 1]);	// push part of prefix

				_Mid = begin() + _Count;
				_Ty _Tmp = _Val;	// in case _Val is in sequence
				copy(_Mid + _Count, _Mid + _Off, _Mid);	// copy rest of prefix
				fill(begin() + _Off, _Mid + _Off, _Tmp);	// fill in values
				}
			_CATCH_ALL
			for (; _Oldsize < _Mysize; )
				pop_front();	// restore old size, at least
			_RERAISE;
			_CATCH_END
			}
		else
			{		// closer to back
			_TRY_BEGIN
			if (_Rem < _Count)
				{	// insert longer than suffix
				for (_Num = _Count - _Rem; 0 < _Num; --_Num)
					push_back(_Val);	// push excess values
				for (_Num = 0; _Num < _Rem; ++_Num)
					push_back(begin()[_Off + _Num]);	// push suffix

				_Mid = begin() + _Off;
				fill(_Mid, _Mid + _Rem, _Val);	// fill in rest of values
				}
			else
				{	// insert not longer than prefix
				for (_Num = 0; _Num < _Count; ++_Num)
					push_back(begin()[_Off + _Rem
						- _Count + _Num]);	// push part of prefix

				_Mid = begin() + _Off;
				_Ty _Tmp = _Val;	// in case _Val is in sequence
				copy_backward(_Mid, _Mid + _Rem - _Count,
					_Mid + _Rem);	// copy rest of prefix
				fill(_Mid, _Mid + _Count, _Tmp);	// fill in values
				}
			_CATCH_ALL
			for (; _Oldsize < _Mysize; )
				pop_back();	// restore old size, at least
			_RERAISE;
			_CATCH_END
			}
		}

        void _Xlen() const { // report length error
            _THROW(std::length_error, "deque<T> too long");
        }

        void _Xran() const { // report range error
            _THROW(std::out_of_range, "invalid deque<T> subscript");
        }

    void _Growmap(size_type _Count)
		{	// grow map by _Count pointers
		if (max_size() / _DEQUESIZ - _Mapsize < _Count)
			_Xlen();	// result too long

		size_type _Inc = _Mapsize / 2;	// try to grow by 50%
		if (_Inc < _DEQUEMAPSIZ)
			_Inc = _DEQUEMAPSIZ;
		if (_Count < _Inc && _Mapsize <= max_size() / _DEQUESIZ - _Inc)
			_Count = _Inc;
		size_type _Myboff = _Myoff / _DEQUESIZ;
		_Mapptr _Newmap = this->_Almap.allocate(_Mapsize + _Count);
		_Mapptr _Myptr = _Newmap + _Myboff;

		_Myptr = _Uninitialized_copy(_Map + _Myboff,
			_Map + _Mapsize, _Myptr, this->_Almap);	// copy initial to end
		if (_Myboff <= _Count)
			{	// increment greater than offset of initial block
			_Myptr = _Uninitialized_copy(_Map,
				_Map + _Myboff, _Myptr, this->_Almap);	// copy rest of old
			_Uninitialized_fill_n(_Myptr, _Count - _Myboff,
				(_Tptr)0, this->_Almap);	// clear suffix of new
			_Uninitialized_fill_n(_Newmap, _Myboff,
				(_Tptr)0, this->_Almap);	// clear prefix of new
			}
		else
			{	// increment not greater than offset of initial block
			_Uninitialized_copy(_Map,
				_Map + _Count, _Myptr, this->_Almap);	// copy more old
			_Myptr = _Uninitialized_copy(_Map + _Count,
				_Map + _Myboff, _Newmap, this->_Almap);	// copy rest of old
			_Uninitialized_fill_n(_Myptr, _Count,
				(_Tptr)0, this->_Almap);	// clear rest to initial block
			}

		_Destroy_range(_Map + _Myboff, _Map + _Mapsize, this->_Almap);
		if (_Map)
			this->_Almap.deallocate(_Map, _Mapsize);	// free storage for old

		_Map = _Newmap;	// point at new
		_Mapsize += _Count;
		}

	void _Tidy()
		{	// free all storage
		while (!empty())
			pop_back();
		for (size_type _Count = _Mapsize; 0 < _Count; )
			{	// free storage for a block and destroy pointer
			if (*(_Map + --_Count) != 0)
				this->_Alval.deallocate(*(_Map + _Count), _DEQUESIZ);
			this->_Almap.destroy(_Map + _Count);
			}

		if (_Map)
			this->_Almap.deallocate(_Map, _Mapsize);	// free storage for map
		_Mapsize = 0;
		_Map = 0;
		}

	_Mapptr _Map;	// pointer to array of pointers to blocks
	size_type _Mapsize;	// size of map array
    size_type _Myoff;   // offset of initial element
    size_type _Mysize;  // current length of sequence
};

// deque TEMPLATE OPERATORS
template<class _Ty, class _Alloc>
inline void swap(deque<_Ty, _Alloc> &_Left,
                 deque<_Ty, _Alloc> &_Right) { // swap _Left and _Right deques
    _Left.swap(_Right);
}

template<class _Ty,
	class _Alloc> inline
	bool operator==(const deque<_Ty, _Alloc>& _Left,
		const deque<_Ty, _Alloc>& _Right)
	{	// test for deque equality
	return (_Left.size() == _Right.size()
		&& equal(_Left.begin(), _Left.end(), _Right.begin()));
	}

template<class _Ty,
	class _Alloc> inline
	bool operator!=(const deque<_Ty, _Alloc>& _Left,
		const deque<_Ty, _Alloc>& _Right)
	{	// test for deque inequality
	return (!(_Left == _Right));
	}

template<class _Ty,
	class _Alloc> inline
	bool operator<(const deque<_Ty, _Alloc>& _Left,
		const deque<_Ty, _Alloc>& _Right)
	{	// test if _Left < _Right for deques
	return (lexicographical_compare(_Left.begin(), _Left.end(),
		_Right.begin(), _Right.end()));
	}

template<class _Ty,
	class _Alloc> inline
	bool operator<=(const deque<_Ty, _Alloc>& _Left,
		const deque<_Ty, _Alloc>& _Right)
	{	// test if _Left <= _Right for deques
	return (!(_Right < _Left));
	}

template<class _Ty,
	class _Alloc> inline
	bool operator>(const deque<_Ty, _Alloc>& _Left,
		const deque<_Ty, _Alloc>& _Right)
	{	// test if _Left > _Right for deques
	return (_Right < _Left);
}

template<class _Ty, class _Alloc>
inline bool operator>=(const deque<_Ty, _Alloc> &_Left,
                       const deque<_Ty, _Alloc> &_Right) { // test if _Left >= _Right for deques
    return (!(_Left < _Right));
}
} // namespace _std

#pragma warning(pop)
#pragma pack(pop)

#endif /* _DEQUE_ */

/*
 * Copyright (c) 1992-2002 by P.J. Plauger.  ALL RIGHTS RESERVED.
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
 V3.13:0009 */
