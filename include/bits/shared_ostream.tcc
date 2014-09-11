//

//          Copyright Sundeep S. Sangha 2013 - 2014.

#ifndef SMART_STREAM_SHARED_STREAM_HPP
#define SMART_STREAM_SHARED_STREAM_HPP

namespace smart_stream {

/* basic_shared_ostream ctor */
template <typename CharT, typename Traits>
basic_shared_ostream<CharT,Traits>::basic_shared_ostream(
  typename basic_shared_ostream<CharT,Traits>::ptr_type && _ptr
)
  : std::basic_ostream<CharT,Traits> (_ptr.get())
  , shptr (std::forward<typename basic_shared_ostream<CharT,Traits>
                        ::ptr_type>(_ptr)){
}

/* basic_shared_ostream ctor */
template <typename CharT, typename Traits>
basic_shared_ostream<CharT,Traits>::basic_shared_ostream(
  std::basic_streambuf<CharT,Traits> * const _ptr
)
  : std::basic_ostream<CharT,Traits> (_ptr)
  , shptr (_ptr){
}

/* basic_shared_ostream ctor */
template <typename CharT, typename Traits>
template <typename Deleter>
basic_shared_ostream<CharT,Traits>::basic_shared_ostream(
  std::basic_streambuf<CharT,Traits> * const _ptr
,	Deleter _deleter
)
  : std::basic_ostream<CharT,Traits> (_ptr)
  , shptr (_ptr, _deleter){
}


/* basic_shared_ostream ctor */
template <typename CharT, typename Traits>
template <typename Deleter, typename Allocator>
basic_shared_ostream<CharT,Traits>::basic_shared_ostream(
  std::basic_streambuf<CharT,Traits> * const _ptr
,	Deleter _deleter
, Allocator _allocator
)
  : std::basic_ostream<CharT,Traits> (_ptr)
  , shptr (_ptr, _deleter, _allocator){
}

/* basic_shared_ostream move ctor */
template <typename CharT, typename Traits>
basic_shared_ostream<CharT,Traits>::basic_shared_ostream(
  basic_shared_ostream<CharT,Traits> && _obj
)
  : shptr (_obj.shptr){
}

/* basic_shared_ostream move operator = */
template <typename CharT, typename Traits>
basic_shared_ostream<CharT,Traits> &
basic_shared_ostream<CharT,Traits>::operator=(
  basic_shared_ostream<CharT,Traits> && _obj
){
this->shptr = _obj.shptr;
return *this;
}

/* basic_shared_ostream dtor */
template <typename CharT, typename Traits>
basic_shared_ostream<CharT,Traits>::~basic_shared_ostream(){
}

/* basic_shared_ostream auto_rdbuf copy */
template <typename CharT, typename Traits>
typename basic_shared_ostream<CharT,Traits>::ptr_type
basic_shared_ostream<CharT,Traits>::auto_rdbuf(
  typename basic_shared_ostream<CharT,Traits>::ptr_type & _ptr
){
typename basic_shared_ostream<CharT,Traits>::ptr_type temp (this->shptr);
this->shptr = _ptr;
this->rdbuf(this->shptr.get());
return temp;
}

/* basic_shared_ostream auto_rdbuf move */
template <typename CharT, typename Traits>
typename basic_shared_ostream<CharT,Traits>::ptr_type
basic_shared_ostream<CharT,Traits>::auto_rdbuf(
  typename basic_shared_ostream<CharT,Traits>::ptr_type && _ptr
){
typename basic_shared_ostream<CharT,Traits>::ptr_type temp (this->shptr);
this->shptr = _ptr;
this->rdbuf(this->shptr.get());
return temp;
}

/* basic_shared_ostream auto_rdbuf */
template <typename CharT, typename Traits>
typename basic_shared_ostream<CharT,Traits>::ptr_type
basic_shared_ostream<CharT,Traits>::auto_rdbuf(
) const {
return this->shptr;
}

/* basic_shared_ostream rebind */
template <typename CharT, typename Traits>
std::basic_streambuf<CharT,Traits> *
basic_shared_ostream<CharT,Traits>::rebind(
){
return this->rdbuf(this->shptr.get());
}

} /* smart_stream */
#endif
