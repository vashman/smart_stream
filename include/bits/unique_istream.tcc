//

//          Copyright Sundeep S. Sangha 2013 - 2014.

#ifndef SMART_STREAM_UNQIUE_ISTREAM_TCC
#define SMART_STREAM_UNQIUE_ISTREAM_TCC

namespace smart_stream {

/* unique_stream ctor */
template <typename CharT, typename Traits, typename Deleter>
basic_unique_istream<CharT,Traits,Deleter>::basic_unique_istream(
  typename basic_unique_istream<CharT,Traits,Deleter>::ptr_type && _ptr
)
  : std::basic_istream<CharT,Traits> (_ptr.get())
  , uqptr (std::forward<typename basic_unique_istream<CharT,Traits
                       ,Deleter>::ptr_type>(_ptr)){
}

/* unique_stream ctor */
template <typename CharT, typename Traits, typename Deleter>
basic_unique_istream<CharT,Traits,Deleter>::basic_unique_istream(
  std::basic_streambuf<CharT,Traits> * const _ptr
)
  : std::basic_istream<CharT,Traits> (_ptr)
  , uqptr (_ptr){
}

/* unique_stream move ctor */
template <typename CharT, typename Traits, typename Deleter>
basic_unique_istream<CharT,Traits,Deleter>::basic_unique_istream(
  basic_unique_istream<CharT,Traits,Deleter> && _obj
)
  : uqptr (_obj.uqptr){
}

/* unique_stream operator = */
template <typename CharT, typename Traits, typename Deleter>
basic_unique_istream<CharT,Traits,Deleter> &
basic_unique_istream<CharT,Traits,Deleter>::operator=(
  basic_unique_istream<CharT,Traits,Deleter> && _obj
){
this->uqptr = _obj.uqptr;
return *this;
}

/* unique_stream dtor */
template <typename CharT, typename Traits, typename Deleter>
basic_unique_istream<CharT,Traits,Deleter>::~basic_unique_istream(
){
}

/* unique_stream auto_rdbuf */
template <typename CharT, typename Traits, typename Deleter>
typename basic_unique_istream<CharT,Traits,Deleter>::ptr_type
basic_unique_istream<CharT,Traits,Deleter>::auto_rdbuf(
  typename basic_unique_istream<CharT,Traits,Deleter>::ptr_type && _ptr
){
this->flush();
this->uqptr.swap(_ptr);
return std::forward<basic_unique_istream<CharT,Traits,Deleter>
                    ::ptr_type>(_ptr);
}

/* unique_ptr auto_rdbuf */
template <typename CharT, typename Traits, typename Deleter>
typename basic_unique_istream<CharT,Traits,Deleter>::ptr_type
basic_unique_istream<CharT,Traits,Deleter>::auto_rdbuf(
){
this->flush();
this->rdbuf(nullptr);
typename basic_unique_istream<CharT,Traits,Deleter>
      ::ptr_type temp(this->uqptr.release());
return std::move(temp);
}

/* unique_stream rebind */
template <typename CharT, typename Traits, typename Deleter>
std::basic_streambuf<CharT,Traits> *
basic_unique_istream<CharT,Traits,Deleter>::rebind(
){
return this->rdbuf(this->uqptr.get());
}

} /* smart_stream */
#endif
