//

//          Copyright Sundeep S. Sangha 2013 - 2014.

#ifndef SMART_STREAM_SHARED_ISTREAM_TCC
#define SMART_STREAM_SHARED_ISTREAM_TCC

namespace smart_stream {
/* basic_shared_istream ctor */
template <typename charT, typename traits>
basic_shared_istream<charT,traits>::basic_shared_istream(
  typename basic_shared_istream<charT,traits>::ptr_type && _ptr
)
  : std::basic_istream<charT,traits> (_ptr.get())
  , shptr (std::forward<typename basic_shared_istream<charT,triats>
           ::ptr_type> (_ptr)) {
}

/* basic_shared_istream ctor */
template <typename charT, typename traits>
basic_shared_istream<charT,traits>::basic_shared_istream(
  std::basic_streambuf<charT,traits> * const _ptr
)
  : std::basic_istream<charT,traits> (_ptr)
  , shptr (_ptr) {
}

/* basic_shared_istream ctor */
template <typename charT, typename traits>
template <typename deleter>
basic_shared_istream<charT,traits>::basic_shared_istream(
  std::basic_streambuf<charT,traits> * const _ptr
,	deleter _deleter
)
  : std::basic_istream<charT,traits> (_ptr)
  , shptr (_ptr, _deleter){
}


/* basic_shared_istream ctor */
template <typename charT, typename traits>
template <typename deleter, typename allocator>
basic_shared_istream<charT,traits>::basic_shared_istream(
  std::basic_streambuf<charT,traits> * const _ptr
,	deleter _deleter
, allocator _allocator
)
  : std::basic_istream<charT,traits> (_ptr)
  , shptr (_ptr, _deleter, _allocator){
}

/* basic_shared_istream move ctor */
template <typename charT, typename traits>
basic_shared_istream<charT,traits>::basic_shared_istream(
  basic_shared_istream<charT,traits> && _obj
)
  : shptr (_obj.shptr){
}

/* basic_shared_istream move operator = */
template <typename charT, typename traits>
basic_shared_istream<charT,traits> &
basic_shared_istream<charT,traits>::operator=(
  basic_shared_istream<charT,traits> && _obj
){
this->shptr = _obj.shptr;
return *this;
}

/* basic_shared_istream copy ctor */
template <typename charT, typename traits>
basic_shared_istream<charT,traits>::basic_shared_istream(
  basic_shared_istream<charT,traits> const & _obj
){
}

/* basic_shared_istream auto_rdbuf copy */
template <typename charT, typename traits>
typename basic_shared_istream<charT,traits>::ptr_type
basic_shared_istream<charT,traits>::auto_rdbuf(
  typename basic_shared_istream<charT,traits>::ptr_type & _ptr
){
typename basic_shared_istream<charT,traits>::ptr_type temp (this->shptr);
this->shptr = _ptr;
this->rdbuf(this->shptr.get());
return temp;
}

/* basic_shared_istream auto_rdbuf move */
template <typename charT, typename traits>
typename basic_shared_istream<charT,traits>::ptr_type
basic_shared_istream<charT,traits>::auto_rdbuf(
  typename basic_shared_istream<charT,traits>::ptr_type && _ptr
){
typename basic_shared_istream<charT,traits>::ptr_type temp (this->shptr);
this->shptr = _ptr;
this->rdbuf(this->shptr.get());
return temp;
}

/* basic_shared_istream auto_rdbuf */
template <typename charT, typename traits>
typename basic_shared_istream<charT,traits>::ptr_type
basic_shared_istream<charT,traits>::auto_rdbuf(
) const {
return this->shptr;
}

/* basic_shared_istream rebind */
template <typename charT, typename traits>
std::basic_streambuf<charT,traits> *
basic_shared_istream<charT,traits>::rebind(
){
return this->rdbuf(this->shptr.get());
}

} /* smart_stream */
#endif
