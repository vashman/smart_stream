// input / output stream using std::unique_ptr for device managment.

//          Copyright Sundeep S. Sangha 2013 - 2014.

#ifndef STDL_UNQIUE_IOSTREAM_HPP
#define STDL_UNQIUE_IOSTREAM_HPP

#include <streambuf>
#include <istream>
#include <memory>

namespace smart_stream{
/* unique_iostream

Provides a stream with auto_rdbuf taking a unique_ptr which will manage
the lifespan of the underlying Buffer. The smart stream will not hide an
base class's rdbuf(streambuf*), which will allow a client to use a
unmanged Buffer.

The unique_stream takes the following template arguments;
1. CharT, char type used by streambuf and osstream.

2. Traits, char traits used by this, streambuf and istream, defaulting to
   std::char_traits<CharT>.

3. Deleter, unique_ptr deleter for the above Buffer pointer,
   defaulting to std::default_delete.
*/
template <
  typename CharT
, typename Traits = std::char_traits<CharT>
, typename Deleter = std::default_delete <
    std::basic_streambuf<CharT,Traits>
  >
>
class  basic_unique_iostream : public std::basic_iostream<CharT,Traits>{
public:
  typedef std::unique_ptr<std::basic_streambuf<CharT,Traits>
                          , Deleter> ptr_type;

  typedef typename std::basic_iostream<CharT,Traits>::char_type char_type;
  typedef typename std::basic_iostream<CharT,Traits>
                                       ::traits_type traits_type;
  typedef typename std::basic_iostream<CharT,Traits>::int_type int_type;
  typedef typename std::basic_iostream<CharT,Traits>::pos_type pos_type;
  typedef typename std::basic_iostream<CharT,Traits>::off_type off_type;

  explicit
  basic_unique_iostream(
   ptr_type &&
  );

  /*
  Takes Buffer pointer and sets internal ptr_type to manage it. If it is
  not desired that this class detroy Buffer, then use stream rdbuf.
  */
  explicit
  basic_unique_iostream(
   std::basic_streambuf<CharT,Traits> * const
  );

  basic_unique_iostream(
   basic_unique_iostream<CharT,Traits,Deleter> &&
  );

  basic_unique_iostream<CharT,Traits,Deleter> &
  operator=(
   basic_unique_iostream<CharT,Traits,Deleter> &&
  );

  basic_unique_iostream(
   basic_unique_iostream<CharT,Traits,Deleter> const &
  ) = delete;

  basic_unique_iostream<CharT,Traits,Deleter> &
  operator=(
   basic_unique_iostream<CharT,Traits,Deleter> const &
  ) = delete;

  ~basic_unique_iostream();

  /*
  Assigns a new ptr_type to the stream, while moving out the previous
  Buffer.
  */
  ptr_type
  auto_rdbuf(ptr_type &&);

  /*
  Returns previous ptr_type, setting the internal and stream Buffer to
  null.
  */
  ptr_type
  auto_rdbuf();

  /*
  Sets the underlying stream buffer to ptr_type's pointer, while returning
  previous pointer.
  */
  std::basic_streambuf<CharT,Traits> *
  rebind();
private:
  ptr_type uqptr;
};

/* unique_stream ctor */
template <typename CharT, typename Traits, typename Deleter>
basic_unique_iostream<CharT,Traits,Deleter>::basic_unique_iostream(
  typename basic_unique_iostream<CharT,Traits,Deleter>::ptr_type && _ptr
)
  : std::basic_iostream<CharT,Traits> (_ptr.get())
  , uqptr (std::forward<typename basic_unique_iostream<CharT,Traits
                       ,Deleter>::ptr_type>(_ptr)){
}

/* unique_stream ctor */
template <typename CharT, typename Traits, typename Deleter>
basic_unique_iostream<CharT,Traits,Deleter>::basic_unique_iostream(
  std::basic_streambuf<CharT,Traits> * const _ptr
)
  : std::basic_iostream<CharT,Traits> (_ptr)
  , uqptr (_ptr){
}

/* unique_stream move ctor */
template <typename CharT, typename Traits, typename Deleter>
basic_unique_iostream<CharT,Traits,Deleter>::basic_unique_iostream(
  basic_unique_iostream<CharT,Traits,Deleter> && _obj
)
  : uqptr (_obj.uqptr){
}

/* unique_stream operator = */
template <typename CharT, typename Traits, typename Deleter>
basic_unique_iostream<CharT,Traits,Deleter> &
basic_unique_iostream<CharT,Traits,Deleter>::operator=(
  basic_unique_iostream<CharT,Traits,Deleter> && _obj
){
this->uqptr = _obj.uqptr;
return *this;
}

/* unique_stream dtor */
template <typename CharT, typename Traits, typename Deleter>
basic_unique_iostream<CharT,Traits,Deleter>::~basic_unique_iostream(
){
}

/* unique_stream auto_rdbuf */
template <typename CharT, typename Traits, typename Deleter>
typename basic_unique_iostream<CharT,Traits,Deleter>::ptr_type
basic_unique_iostream<CharT,Traits,Deleter>::auto_rdbuf(
  typename basic_unique_iostream<CharT,Traits,Deleter>::ptr_type && _ptr
){
this->flush();
this->uqptr.swap(_ptr);
return std::forward<basic_unique_iostream<CharT,Traits,Deleter>
                    ::ptr_type>(_ptr);
}

/* unique_ptr auto_rdbuf */
template <typename CharT, typename Traits, typename Deleter>
typename basic_unique_iostream<CharT,Traits,Deleter>::ptr_type
basic_unique_iostream<CharT,Traits,Deleter>::auto_rdbuf(
){
this->flush();
this->rdbuf(nullptr);
typename basic_unique_iostream<CharT,Traits,Deleter>
      ::ptr_type temp(this->uqptr.release());
return std::move(temp);
}

/* unique_stream rebind */
template <typename CharT, typename Traits, typename Deleter>
std::basic_streambuf<CharT,Traits> *
basic_unique_iostream<CharT,Traits,Deleter>::rebind(
){
return this->rdbuf(this->uqptr.get());
}

typedef basic_unique_iostream<char> unique_stream;
typedef basic_unique_iostream<wchar_t> wunique_stream;
}
#endif
