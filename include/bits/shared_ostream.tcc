//

//          Copyright Sundeep S. Sangha 2013 - 2014.

#ifndef SMART_STREAM_SHARED_OSTREAM_TCC
#define SMART_STREAM_SHARED_OSTREAM_TCC

namespace smart_stream {

/* basic_shared_ostream ctor */
template <typename charT, typename traits>
basic_shared_ostream<charT,traits>::basic_shared_ostream(
  typename basic_shared_ostream<charT,traits>::ptr_type && _ptr
)
  : std::basic_ostream<charT,traits> (_ptr.get())
  , shptr (std::forward<typename basic_shared_ostream<charT,traits>
                        ::ptr_type>(_ptr)){
}

/* basic_shared_ostream ctor */
template <typename charT, typename traits>
basic_shared_ostream<charT,traits>::basic_shared_ostream(
  std::basic_streambuf<charT,traits> * const _ptr
)
  : std::basic_ostream<charT,traits> (_ptr)
  , shptr (_ptr){
}

/* basic_shared_ostream ctor */
template <typename charT, typename traits>
template <typename Deleter>
basic_shared_ostream<charT,traits>::basic_shared_ostream(
  std::basic_streambuf<charT,traits> * const _ptr
,	Deleter _deleter
)
  : std::basic_ostream<charT,traits> (_ptr)
  , shptr (_ptr, _deleter){
}


/* basic_shared_ostream ctor */
template <typename charT, typename traits>
template <typename Deleter, typename Allocator>
basic_shared_ostream<charT,traits>::basic_shared_ostream(
  std::basic_streambuf<charT,traits> * const _ptr
,	Deleter _deleter
, Allocator _allocator
)
  : std::basic_ostream<charT,traits> (_ptr)
  , shptr (_ptr, _deleter, _allocator){
}

/* basic_shared_ostream move ctor */
template <typename charT, typename traits>
basic_shared_ostream<charT,traits>::basic_shared_ostream(
  basic_shared_ostream<charT,traits> && _obj
)
  : shptr (_obj.shptr){
}

/* basic_shared_ostream move operator = */
template <typename charT, typename traits>
basic_shared_ostream<charT,traits> &
basic_shared_ostream<charT,traits>::operator=(
  basic_shared_ostream<charT,traits> && _obj
){
this->shptr = _obj.shptr;
return *this;
}

/* basic_shared_ostream dtor */
template <typename charT, typename traits>
basic_shared_ostream<charT,traits>::~basic_shared_ostream(){
}

/* basic_shared_ostream auto_rdbuf copy */
template <typename charT, typename traits>
typename basic_shared_ostream<charT,traits>::ptr_type
basic_shared_ostream<charT,traits>::auto_rdbuf(
  typename basic_shared_ostream<charT,traits>::ptr_type & _ptr
){
typename basic_shared_ostream<charT,traits>::ptr_type temp (this->shptr);
this->shptr = _ptr;
this->rdbuf(this->shptr.get());
return temp;
}

/* basic_shared_ostream auto_rdbuf move */
template <typename charT, typename traits>
typename basic_shared_ostream<charT,traits>::ptr_type
basic_shared_ostream<charT,traits>::auto_rdbuf(
  typename basic_shared_ostream<charT,traits>::ptr_type && _ptr
){
typename basic_shared_ostream<charT,traits>::ptr_type temp (this->shptr);
this->shptr = _ptr;
this->rdbuf(this->shptr.get());
return temp;
}

/* basic_shared_ostream auto_rdbuf */
template <typename charT, typename traits>
typename basic_shared_ostream<charT,traits>::ptr_type
basic_shared_ostream<charT,traits>::auto_rdbuf(
) const {
return this->shptr;
}

/* basic_shared_ostream rebind */
template <typename charT, typename traits>
std::basic_streambuf<charT,traits> *
basic_shared_ostream<charT,traits>::rebind(
){
return this->rdbuf(this->shptr.get());
}

} /* smart_stream */
#endif
