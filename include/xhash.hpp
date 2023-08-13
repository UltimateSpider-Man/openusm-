// xhash internal header
#pragma once
#ifndef _XHASH_
#define _XHASH_
#ifndef RC_INVOKED

#include <cstring>
#include <cwchar>
#include <functional>
#include <list.hpp>
#include <vector.hpp>

#ifdef  _MSC_VER
#pragma pack(push,_CRT_PACKING)
#pragma warning(push,3)

 #pragma warning(disable: 4127)
#endif  /* _MSC_VER */

		// TEMPLATE FUNCTION hash_value
inline constexpr auto _HASH_SEED = static_cast<size_t>(0xdeadbeef);

#ifndef _STDEXT_BEGIN
#define _STDEXT_BEGIN namespace stdext {
#endif

#ifndef _STDEXT_END
#define _STDEXT_END }
#endif

#ifndef _STD_BEGIN
#define _STD_BEGIN namespace _std {
#endif

#ifndef _STD_END
#define _STD_END }
#endif

/* 
We start off by defining a specialisation of hash_value for stdext.
This will work for stdext::hash_map<std::string, ...
If the user is using std::hash_map, we pull the specialisation into std
as well.

This comes at the top of our file before everything else to ensure we
only pull in this one specialisation.
*/

_STDEXT_BEGIN

 #if _HAS_ITERATOR_DEBUGGING
using std::_Debug_message;
using std::_Debug_range;
using std::_Debug_get_cont;
 #endif

template <class _Init>
	inline size_t _Hash_value(_Init _Begin, _Init _End)
	{	// hash range of elements
	size_t _Val = 2166136261U;
	while(_Begin != _End)
        _Val = 16777619U * _Val ^ (size_t) *_Begin++;
    return (_Val);
}

template<class _Elem, class _Traits, class _Alloc>
inline size_t hash_value(
    const std::basic_string<_Elem, _Traits, _Alloc> &_Str) { // hash string to size_t value
    return (_Hash_value(_Str.begin(), _Str.end()));
}

template<class _Kty> inline
	size_t hash_value(const _Kty& _Keyval)
	{	// hash _Keyval to size_t value one-to-one
	return ((size_t)_Keyval ^ _HASH_SEED);
	}

inline size_t hash_value(const char *_Str)
	{	// hash NTBS to size_t value
	return (_Hash_value(_Str, _Str + ::strlen(_Str)));
	}

inline size_t hash_value(const wchar_t *_Str)
	{	// hash NTWCS to size_t value
	return (_Hash_value(_Str, _Str + ::wcslen(_Str)));
}

// TEMPLATE CLASS hash_compare

template<class _Kty,
         class _Pr = std::less<_Kty>>
class hash_compare { // traits class for hash containers
public:
    enum {               // parameters for hash table
        bucket_size = 4, // 0 < bucket_size
        min_buckets = 8
    }; // min_buckets = 2 ^^ N, 0 < N

    hash_compare() : comp() { // construct with default comparator
    }

    hash_compare(_Pr _Pred) : comp(_Pred) { // construct with _Pred comparator
    }

    size_t operator()(const _Kty& _Keyval) const
		{	// hash _Keyval to size_t value by pseudorandomizing transform
		ldiv_t _Qrem = ldiv((long)hash_value(_Keyval), 127773);
		_Qrem.rem = 16807 * _Qrem.rem - 2836 * _Qrem.quot;
		if (_Qrem.rem < 0)
			_Qrem.rem += 2147483647;
		return ((size_t)_Qrem.rem);
		}

	bool operator()(const _Kty& _Keyval1, const _Kty& _Keyval2) const
		{	// test if _Keyval1 ordered before _Keyval2
		return (comp(_Keyval1, _Keyval2));
		}

    protected:
        _Pr comp; // the comparator object
};

// TEMPLATE CLASS _Hash
template<class _Traits>
class _Hash : public _Traits // traits serves as base class
{                            // hash table -- list with vector of iterators for quick access
public:
    typedef _Hash<_Traits> _Myt;
    typedef typename _Traits::key_type key_type;
    typedef typename _Traits::key_compare key_compare;
    typedef typename _Traits::value_compare value_compare;
    enum { // hoist constants from key_compare
        bucket_size = key_compare::bucket_size,
        min_buckets = key_compare::min_buckets,
        _Multi = _Traits::_Multi
    };
    typedef _STD list<typename _Traits::value_type, typename _Traits::allocator_type> _Mylist;

    typedef typename _Mylist::allocator_type allocator_type;
    typedef typename _Mylist::size_type size_type;
    typedef typename _Mylist::difference_type difference_type;
    typedef typename _Mylist::pointer pointer;
    typedef typename _Mylist::const_pointer const_pointer;
    typedef typename _Mylist::reference reference;
    typedef typename _Mylist::const_reference const_reference;

#if _HAS_IMMUTABLE_SETS
    typedef typename _Mylist::iterator _Myiterator;
    typedef typename _Traits::_ITptr _ITptr;
    typedef typename _Traits::_IReft _IReft;

    // CLASS iterator
	class iterator
		: public _Myiterator
		{	// possibly non-mutable iterator
	public:
		typedef _ITptr pointer;
		typedef _IReft reference;

		iterator()
			{	// construct default iterator
			}

		iterator(const _Myiterator& _Iter)
			: _Myiterator(_Iter)
			{	// construct from _Myiterator
			}

		_IReft operator*() const
			{	// change to const_reference
			return ((_IReft)**(_Myiterator *)this);
			}

		_ITptr operator->() const
			{	// change to const_pointer
			return ((_ITptr)&**(_Myiterator *)this);
			}
		};

#else /* _HAS_IMMUTABLE_SETS */
    typedef typename _Mylist::iterator _Myiterator;
    typedef typename _Mylist::iterator iterator;
#endif /* _HAS_IMMUTABLE_SETS */

        typedef typename _Mylist::const_iterator const_iterator;

#if _SECURE_SCL && !_HAS_ITERATOR_DEBUGGING

	// _List_position is used to keep a pointer to a certain position in the list.
	// List iterators can easily be converted to _List_position, and you can get
	// the correctly parented iterator from a _List_position calling _Get_iter() or
	// the helper function _Get_iter_from_vec() below.
	struct _List_position
	{
	public:
		_List_position()
			: _Mypos()
			{
			}

		_List_position(iterator _Iter)
			: _Mypos(_Iter._Mynode(), (_Mylist*)_Iter._Mycont)
			{
			}

		_List_position(const_iterator _Iter)
			: _Mypos(_Iter._Mynode(), (_Mylist*)_Iter._Mycont)
			{
			}

		// default copy constructor and assignment operator

		iterator _Get_iter(const _Mylist &_List) const
			{
			// reparent the iterator
			return _Myiterator(_Mypos._Mynode(), &_List);
			}

		bool operator==(const _List_position &_Right) const
			{
			return (_Mypos._Mynode() == _Right._Mypos._Mynode());
			}

		bool operator!=(const _List_position &_Right) const
			{
			return (!(*this == _Right));
			}

		bool operator==(const const_iterator &_Right) const
			{
			return (_Mypos._Mynode() == _Right._Mynode());
			}

		bool operator!=(const const_iterator &_Right) const
			{
			return (!(*this == _Right));
			}

	protected:
		typename _Mylist::_Iterator<0> _Mypos;
	};

	typedef _List_position _Myvec_value_type;

	inline iterator _Get_iter_from_vec(const _Myvec_value_type &_Pos) const
	{
		return _Pos._Get_iter(_List);
	}

#else

	typedef iterator _Myvec_value_type;

	inline iterator _Get_iter_from_vec(const _Myvec_value_type &_Iter) const
	{
		return _Iter;
	}

#endif

	typedef typename _Mylist::reverse_iterator
		reverse_iterator;
	typedef typename _Mylist::const_reverse_iterator
		const_reverse_iterator;
	typedef typename _Mylist::value_type value_type;

	typedef _STD vector<_Myvec_value_type,
		typename allocator_type::template
			rebind<_Myvec_value_type>::other> _Myvec;
	typedef _STD pair<iterator, bool> _Pairib;
	typedef _STD pair<iterator, iterator> _Pairii;
	typedef _STD pair<const_iterator, const_iterator> _Paircc;

	explicit _Hash(const key_compare& _Parg,
		const allocator_type& _Al)
		: _Traits(_Parg), _List(_Al),
			_Vec(min_buckets + 1, end(), _Al),
			_Mask(1), _Maxidx(1)
		{	// construct empty hash table
		}

	_Hash(const value_type *_First, const value_type *_Last,
		const key_compare& _Parg, const allocator_type& _Al)
		: _Traits(_Parg), _List(_Al),
			_Vec(min_buckets + 1, end(), _Al),
			_Mask(1), _Maxidx(1)
		{	// construct hash table from [_First, _Last) array
		insert(_First, _Last);
		}

	_Hash(const _Myt& _Right)
		: _Traits(_Right.comp), _List(_Right.get_allocator()),
			_Vec(_Right.get_allocator())
		{	// construct hash table by copying right
		_Copy(_Right);
		}

	~_Hash()
		{	// destroy hash table
		}

	_Myt& operator=(const _Myt& _Right)
		{	// replace contents from _Right
		if (this != &_Right)
			_Copy(_Right);
		return (*this);
		}

	iterator begin()
		{	// return iterator for beginning of mutable sequence
		return (_List.begin());
		}

	const_iterator begin() const
		{	// return iterator for beginning of nonmutable sequence
		return (_List.begin());
		}

	iterator end()
		{	// return iterator for end of mutable sequence
		return (_List.end());
		}

	const_iterator end() const
		{	// return iterator for end of nonmutable sequence
		return (_List.end());
		}

	reverse_iterator rbegin()
		{	// return iterator for beginning of reversed mutable sequence
		return (_List.rbegin());
		}

	const_reverse_iterator rbegin() const
		{	// return iterator for beginning of reversed nonmutable sequence
		return (_List.rbegin());
		}

	reverse_iterator rend()
		{	// return iterator for end of reversed mutable sequence
		return (_List.rend());
		}

	const_reverse_iterator rend() const
		{	// return iterator for end of reversed nonmutable sequence
		return (_List.rend());
		}

	size_type size() const
		{	// return length of sequence
		return (_List.size());
		}

	size_type max_size() const
		{	// return maximum possible length of sequence
		return (_List.max_size());
		}

	bool empty() const
		{	// return true only if sequence is empty
		return (_List.empty());
		}

	allocator_type get_allocator() const
		{	// return allocator object for values
        return (_List.get_allocator());
    }

    key_compare key_comp() const { // return object for comparing keys
        return (this->comp);
    }

        value_compare value_comp() const { // return object for comparing values
            return (value_compare(key_comp()));
        }

        _Pairib insert(const value_type &_Val) { // try to insert node with value _Val
            iterator _Plist, _Where;
            if (_Maxidx <= size() / bucket_size) { // too dense, need to grow hash table
                if (_Vec.size() - 1 <= _Maxidx) {  // table full, double its size
                    _Mask = ((_Vec.size() - 1) << 1) - 1;
                    _Vec.resize(_Mask + 2, end());
                } else if (_Mask < _Maxidx)
                    _Mask = (_Mask << 1) + 1;

                size_type _Bucket = _Maxidx - (_Mask >> 1) - 1;
                for (_Plist = _Get_iter_from_vec(_Vec[_Bucket]);
                     _Vec[_Bucket + 1] != _Plist;) { // split old bucket
                    size_type _Newbucket = this->comp(this->_Kfn(*_Plist)) & _Mask;
                    if (_Newbucket == _Bucket) {
                        ++_Plist; // leave element in old bucket
                    }
#if _HAS_ITERATOR_DEBUGGING
                    else if (_Newbucket != _Maxidx)
                        _DEBUG_ERROR("bad hash function");
#endif /* _HAS_ITERATOR_DEBUGGING */

                    else { // move element to new bucket
                        size_type _Idx;
                        iterator _Pnext = _Plist;
                        if (++_Pnext != end()) { // not at end, move it
                            for (_Idx = _Bucket; _Vec[_Idx] == _Plist;
                                 --_Idx) { // update end iterators if moving first
                                _Vec[_Idx] = _Pnext;
                                if (_Idx == 0) {
                                    break;
                                }
                            }
                            _List._Splice(end(), _List, _Plist, _Pnext, 0);
                            _Plist = --end();
                            _Vec[_Maxidx + 1] = end();
                        }

                        for (_Idx = _Maxidx; _Bucket < _Idx;
                             --_Idx) { // update end iterators if new bucket filled
                            if (_Vec[_Idx] != end()) {
                                break;
                            }
                            _Vec[_Idx] = _Plist;
                        }

                        if (_Pnext == end()) {
                            break;
                        } else {
                            _Plist = _Pnext;
                        }
                    }
                }
                ++_Maxidx; // open new bucket for hash lookup
            }

            size_type _Bucket = _Hashval(this->_Kfn(_Val));
            for (_Plist = _Get_iter_from_vec(_Vec[_Bucket + 1]); _Vec[_Bucket] != _Plist;)
                if (this->comp(this->_Kfn(_Val), this->_Kfn(*--_Plist))) {
                    ; // still too high in bucket list
                } else if (this->comp(this->_Kfn(*_Plist),
                                      this->_Kfn(_Val))) { // found insertion point, back up to it
                    ++_Plist;
                    break;
                } else if (_Multi)
                    break; // equivalent, insert only if multi
                else
                    return (_Pairib(_Plist, false)); // already present

            _Where = _List.insert(_Plist, _Val); // insert new element
            for (; _Vec[_Bucket] == _Plist;
                 --_Bucket) { // update end iterators if new first bucket element
                _Vec[_Bucket] = _Where;
                if (_Bucket == 0) {
                    break;
                }
            }

            return (_Pairib(_Where, true)); // return iterator for new element
        }

        iterator insert(iterator,
                        const value_type &_Val) { // try to insert node with value _Val, ignore hint
            return (insert(_Val).first);
        }

        template<class _Iter>
        void insert(_Iter _First, _Iter _Last) { // insert [_First, _Last) one at a time

#if _HAS_ITERATOR_DEBUGGING
            _DEBUG_RANGE(_First, _Last);
            if (_Debug_get_cont(_First) == this)
                _DEBUG_ERROR("hash_map/set insertion overlaps range");
#endif /* _HAS_ITERATOR_DEBUGGING */

            for (; _First != _Last; ++_First) {
                insert(*_First);
            }
        }

        iterator erase(iterator _Where) { // erase element at _Where
            size_type _Bucket = _Hashval(this->_Kfn(*_Where));
            for (; _Vec[_Bucket] == _Where; --_Bucket) { // update end iterators if erasing first
#if _SECURE_SCL && !_HAS_ITERATOR_DEBUGGING
			iterator _Vec_iter = _Get_iter_from_vec(_Vec[_Bucket]);
			++_Vec_iter;
			_Vec[_Bucket] = _Vec_iter;
#else
			++_Vec[_Bucket];
#endif
            if (_Bucket == 0)
                break;
            }
            return (_List.erase(_Where));
        }

        iterator erase(iterator _First, iterator _Last) { // erase [_First, _Last)
            _DEBUG_RANGE(_First, _Last);
            if (_First == begin() && _Last == end()) { // erase all
                clear();
                return (begin());
            } else { // partial erase, one at a time
                while (_First != _Last) {
                    erase(_First++);
                }
                return (_First);
            }
        }

        size_type erase(const key_type &_Keyval) { // erase and count all that match _Keyval
            _Pairii _Where = equal_range(_Keyval);
            size_type Num{0};
            _Distance(_Where.first, _Where.second, Num);
            erase(_Where.first, _Where.second);
            return (Num);
        }

        void erase(const key_type *_First,
                   const key_type *_Last) { // erase all that match array of keys [_First, _Last)
            _DEBUG_RANGE(_First, _Last);
            for (; _First != _Last; ++_First) {
                erase(*_First);
            }
        }

        void clear() { // erase all
            _List.clear();
            _Vec.assign(min_buckets + 1, end());
            _Mask = 1;
            _Maxidx = 1;
        }

        iterator find(
            const key_type &_Keyval) { // find an element in mutable hash table that matches _Keyval
            return (lower_bound(_Keyval));
        }

        const_iterator find(const key_type &_Keyval)
            const { // find an element in nonmutable hash table that matches _Keyval
            return (lower_bound(_Keyval));
        }

        size_type count(const key_type &_Keyval) const { // count all elements that match _Keyval
            _Paircc _Ans = equal_range(_Keyval);
            size_type _Num = 0;
            _Distance(_Ans.first, _Ans.second, _Num);
            return (_Num);
        }

        iterator lower_bound(
            const key_type &_Keyval) { // find leftmost not less than _Keyval in mutable hash table
            size_type _Bucket = _Hashval(_Keyval);
            iterator _Where;
            for (_Where = _Get_iter_from_vec(_Vec[_Bucket]); _Vec[_Bucket + 1] != _Where; ++_Where) {
                if (!this->comp(this->_Kfn(*_Where), _Keyval)) {
                    return (this->comp(_Keyval, this->_Kfn(*_Where)) ? end() : _Where);
                }
            }
            return (end());
        }

        const_iterator lower_bound(const key_type &_Keyval)
            const { // find leftmost not less than _Keyval in nonmutable hash table
            size_type _Bucket = _Hashval(_Keyval);
            const_iterator _Where;
            for (_Where = _Get_iter_from_vec(_Vec[_Bucket]); _Vec[_Bucket + 1] != _Where; ++_Where)
                if (!this->comp(this->_Kfn(*_Where), _Keyval)) {
                    return (this->comp(_Keyval, this->_Kfn(*_Where)) ? end() : _Where);
                }
            return (end());
        }

        iterator upper_bound(
            const key_type &_Keyval) { // find leftmost not greater than _Keyval in mutable hash table
            size_type _Bucket = _Hashval(_Keyval);
            iterator _Where;
            for (_Where = _Get_iter_from_vec(_Vec[_Bucket + 1]); _Vec[_Bucket] != _Where;)
                if (!this->comp(_Keyval, this->_Kfn(*--_Where)))
                    return (this->comp(this->_Kfn(*_Where), _Keyval) ? end() : (iterator) ++_Where);
            return (end());
		}

	const_iterator upper_bound(const key_type& _Keyval) const
		{	// find leftmost not greater than _Keyval in nonmutable hash table
		size_type _Bucket = _Hashval(_Keyval);
		const_iterator _Where;
		for (_Where = _Get_iter_from_vec(_Vec[_Bucket + 1]); _Vec[_Bucket] != _Where; )
			if (!this->comp(_Keyval, this->_Kfn(*--_Where)))
				return (this->comp(this->_Kfn(*_Where),
					_Keyval) ? end() : (const_iterator)++_Where);
		return (end());
		}

	_Pairii equal_range(const key_type& _Keyval)
		{	// find range equivalent to _Keyval in mutable hash table
		size_type _Bucket = _Hashval(_Keyval);
		iterator _First, _Where;
		for (_Where = _Get_iter_from_vec(_Vec[_Bucket]); _Vec[_Bucket + 1] != _Where; ++_Where)
			if (!this->comp(this->_Kfn(*_Where), _Keyval))
				{	// found _First, look for end of range
				for (_First = _Where; _Vec[_Bucket + 1] != _Where; ++_Where)
					if (this->comp(_Keyval, this->_Kfn(*_Where)))
						break;
				if (_First == _Where)
					break;
				return (_Pairii(_First, _Where));
            }
        return (_Pairii(end(), end()));
    }

    _Paircc equal_range(const key_type &_Keyval)
        const { // find range equivalent to _Keyval in nonmutable hash table
        size_type _Bucket = _Hashval(_Keyval);
        iterator _First, _Where;
        for (_Where = _Get_iter_from_vec(_Vec[_Bucket]); _Vec[_Bucket + 1] != _Where; ++_Where) {
            if (!this->comp(this->_Kfn(*_Where), _Keyval)) { // found _First, look for end of range
                for (_First = _Where; _Vec[_Bucket + 1] != _Where; ++_Where) {
                    if (this->comp(_Keyval, this->_Kfn(*_Where))) {
                        break;
                    }
                }

                if (_First == _Where) {
                    break;
                }

                return (_Paircc(_First, _Where));
            }
        }
        return (_Paircc(end(), end()));
    }

    void swap(_Myt &_Right)

#if _HAS_ITERATOR_DEBUGGING
    { // exchange contents with _Right
        _Myt _Tmp = *this;
        *this = _Right, _Right = _Tmp;
    }

#else /* _HAS_ITERATOR_DEBUGGING */
    {                                                    // exchange contents with _Right
        if (get_allocator() == _Right.get_allocator()) { // same allocator, swap control information
            _List.swap(_Right._List);
            std::swap(_Vec, _Right._Vec);
            std::swap(_Mask, _Right._Mask);
			std::swap(_Maxidx, _Right._Maxidx);
			std::swap(this->comp, _Right.comp);
        } else { // different allocator, do multiple assigns
            _Myt _Tmp = *this;
            *this = _Right, _Right = _Tmp;
        }
    }
#endif /* _HAS_ITERATOR_DEBUGGING */

    protected:
        void _Copy(const _Myt &_Right) { // copy entire hash table
            _Vec.resize(_Right._Vec.size(), end());
            _Mask = _Right._Mask;
            _Maxidx = _Right._Maxidx;
            _List.clear();

            _TRY_BEGIN
            _List.insert(end(), _Right._List.begin(), _Right._List.end());
            this->comp = _Right.comp;
            _CATCH_ALL
            _List.clear(); // list or compare copy failed, bail out
            fill(_Vec.begin(), _Vec.end(), end());
            _RERAISE;
            _CATCH_END

            iterator _Whereto = begin();
            const_iterator _Wherefrom = _Right.begin();
            for (size_type _Bucket = 0; _Bucket < _Vec.size();)
                if (_Right._Vec[_Bucket] == _Wherefrom) {
                    _Vec[_Bucket] = _Whereto, ++_Bucket;
                } else {
                    ++_Whereto, ++_Wherefrom;
                }
        }

        size_type _Hashval(const key_type &_Keyval)
            const { // return hash value, masked and wrapped to current table size
            size_type _Num = this->comp(_Keyval) & _Mask;
            if (_Maxidx <= _Num) {
                _Num -= (_Mask >> 1) + 1;
            }
            return (_Num);
        }

    public:
        _Mylist _List;     // the list of elements, must initialize before _Vec
        _Myvec _Vec;       // the vector of list iterators
        size_type _Mask;   // the key mask
        size_type _Maxidx; // current maximum key value
};

        // _Hash TEMPLATE OPERATORS
template<class _Ty> inline
	bool operator==(const _Hash<_Ty>& _Left, const _Hash<_Ty>& _Right)
	{	// test for hash table equality
	return (_Left.size() == _Right.size()
		&& equal(_Left.begin(), _Left.end(), _Right.begin()));
	}

template<class _Ty> inline
	bool operator!=(const _Hash<_Ty>& _Left, const _Hash<_Ty>& _Right)
	{	// test for hash table inequality
	return (!(_Left == _Right));
	}

template<class _Ty> inline
	bool operator<(const _Hash<_Ty>& _Left, const _Hash<_Ty>& _Right)
	{	// test if _Left < _Right for hash tables
	return (lexicographical_compare(_Left.begin(), _Left.end(),
		_Right.begin(), _Right.end()));
	}

template<class _Ty> inline
	bool operator>(const _Hash<_Ty>& _Left, const _Hash<_Ty>& _Right)
	{	// test if _Left > _Right for hash tables
	return (_Right < _Left);
	}

template<class _Ty> inline
	bool operator<=(const _Hash<_Ty>& _Left, const _Hash<_Ty>& _Right)
	{	// test if _Left <= _Right for hash tables
	return (!(_Right < _Left));
	}

template<class _Ty> inline
	bool operator>=(const _Hash<_Ty>& _Left, const _Hash<_Ty>& _Right)
	{	// test if _Left >= _Right for hash tables
	return (!(_Left < _Right));
	}
_STDEXT_END

_STD_BEGIN

	// _Hash implements a performant swap
template <class _Traits>
	class _Move_operation_category<_STDEXT _Hash<_Traits> >
	{
	public:
		typedef _Swap_move_tag _Move_cat;
	};

_STD_END

#ifdef  _MSC_VER
  #pragma warning(default: 4127)

#pragma warning(pop)
#pragma pack(pop)
#endif  /* _MSC_VER */

#endif /* RC_INVOKED */
#endif /* _XHASH_ */

/*
 * Copyright (c) 1992-2005 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
 V4.05:0009 */
