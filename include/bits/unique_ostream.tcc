// output stream using std::unique_ptr for device managment.

//          Copyright Sundeep S. Sangha 2013 - 2014.

#ifndef SMART_STREAM_UNQIUE_OSTREAM_TCC
#define SMART_STREAM_UNQIUE_OSTREAM_TCC

namespace smart_stream {

/* unique_stream ctor */
template <typename CharT, typename Traits, typename Deleter>
basic_unique_ostream<CharT,Traits,Deleter>::basic_unique_ostream(
  typename basic_unique_ostream<CharT,Traits,Deleter>::ptr_type && _ptr
)
  : std::basic_ostream<CharT,Traits> (_ptr.get())
  , uqptr (std::forward<typename basic_unique_ostream<CharT,Traits
                       ,Deleter>::ptr_type>(_ptr)){
}

/* unique_stream ctor */
template <typename CharT, typename Traits, typename Deleter>
basic_unique_ostream<CharT,Traits,Deleter>::basic_unique_ostream(
  std::basic_streambuf<CharT,Traits> * const _ptr
)
  : std::basic_ostream<CharT,Traits> (_ptr)
  , uqptr (_ptr){
}

/* unique_stream move ctor */
template <typename CharT, typename Traits, typename Deleter>
basic_unique_ostream<CharT,Traits,Deleter>::basic_unique_ostream(
  basic_unique_ostream<CharT,Traits,Deleter> && _obj
)
  : uqptr (_obj.uqptr){
}

/* unique_stream operator = */
template <typename CharT, typename Traits, typename Deleter>
basic_unique_ostream<CharT,Traits,Deleter> &
basic_unique_ostream<CharT,Traits,Deleter>::operator=(
  basic_unique_ostream<CharT,Traits,Deleter> && _obj
){
this->uqptr = _obj.uqptr;
return *this;
}

/* unique_stream dtor */
template <typename CharT, typename Traits, typename Deleter>
basic_unique_ostream<CharT,Traits,Deleter>::~basic_unique_ostream(
){
}

/* unique_stream auto_rdbuf */
template <typename CharT, typename Traits, typename Deleter>
typename basic_unique_ostream<CharT,Traits,Deleter>::ptr_type
basic_unique_ostream<CharT,Traits,Deleter>::auto_rdbuf(
  typename basic_unique_ostream<CharT,Traits,Deleter>::ptr_type && _ptr
){
this->flush();
this->uqptr.swap(_ptr);
return std::forward<basic_unique_ostream<CharT,Traits,Deleter>
                    ::ptr_type>(_ptr);
}

/* unique_ptr auto_rdbuf */
template <typename CharT, typename Traits, typename Deleter>
typename basic_unique_ostream<CharT,Traits,Deleter>::ptr_type
basic_unique_ostream<CharT,Traits,Deleter>::auto_rdbuf(
){
this->flush();
this->rdbuf(nullptr);
typename basic_unique_ostream<CharT,Traits,Deleter>
      ::ptr_type temp(this->uqptr.release());
return std::move(temp);
}

/* unique_stream rebind */
template <typename CharT, typename Traits, typename Deleter>
std::basic_streambuf<CharT,Traits> *
basic_unique_ostream<CharT,Traits,Deleter>::rebind(
){
return this->rdbuf(this->uqptr.get());
}

} /* smart_stream */
#endif
