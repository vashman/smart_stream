// ostream using std::shared_ptr for device managment.

//          Copyright Sundeep S. Sangha 2013 - 2014.

#ifndef SMART_STREAM_SHARED_OSTREAM_HPP
#define SMART_STREAM_SHARED_OSTREAM_HPP

#include <streambuf>
#include <ostream>
#include <memory>

namespace smart_stream {

/* basic_shared_ostream

Provides a stream with auto_rdbuf taking a shared_ptr which will manage
the lifespan of the underlying streambuf. The smart stream will not hide
the base class's rdbuf(streambuf*), which will allow a client to use a
unmanged streambuf.

The basic_shared_ostream takes the following template arguments;
1. std::basic_ostream<charT,traits>, is the base stream object to inherit from such as;
   std::basic_ostream, std::basic_istream, std::basic_iostream.

2. std::basic_streambuf<charT,traits>, is the base streams streambuffer type, defaulting to
   std::basic_streambuf taking the streams char_type and traits_type.

*/
template <typename charT, typename traits = std::char_traits<charT> >
class  basic_shared_ostream : public std::basic_ostream<charT,traits>{
public:
  typedef std::shared_ptr<std::basic_streambuf<charT,traits>> ptr_type;

  typedef typename std::basic_ostream<charT,traits>::char_type char_type;
  typedef typename std::basic_ostream<charT,traits>
                                     ::traits_type traits_type;
  typedef typename std::basic_ostream<charT,traits>::int_type int_type;
  typedef typename std::basic_ostream<charT,traits>::pos_type pos_type;
  typedef typename std::basic_ostream<charT,traits>::off_type off_type;

  explicit
  basic_shared_ostream(
    ptr_type &&
  );

  /*
  Take referance to ptr_type and then copy to internal ptr_type.
  */
  explicit
  basic_shared_ostream(
    ptr_type &
  ); 

  explicit
  basic_shared_ostream(
    std::basic_streambuf<charT,traits> * const
  );

  /*
  Template argument Deleter, unique_ptr deleter for the streambuf pointer,
  defaulting to std::default_delete.
  */
  template <typename Deleter>
  explicit
  basic_shared_ostream(
    std::basic_streambuf<charT,traits> *
  , Deleter
  );

  /*
  Template argument Allocator, shared_ptr allocator type, defaults to
  std::allocator for std::basic_streambuf<charT,traits> template type.
  Deleter template argument is same as above ctor.
  */
  template <typename Deleter, typename Allocator>
  explicit
  basic_shared_ostream(
    std::basic_streambuf<charT,traits> *
  , Deleter
  , Allocator
  );

  basic_shared_ostream(
    basic_shared_ostream<charT,traits> &&
  );

  basic_shared_ostream<charT,traits> &
  operator=(
     basic_shared_ostream<charT,traits> &&
  );

  basic_shared_ostream(
     basic_shared_ostream<charT,traits> const &
  ) = delete;

  basic_shared_ostream<charT,traits> &
  operator=(
     basic_shared_ostream<charT,traits> const &
  ) = delete;

  ~basic_shared_ostream();

  /*
  Copy referanced ptr_type parameter and move previous ptr_type as return.
  */
  ptr_type
  auto_rdbuf(ptr_type &);

  /*
  Move in ptr_type and move return previous ptr_type.
  */
  ptr_type
  auto_rdbuf(ptr_type &&);

  /*
  Return copy to internal ptr_type.
  */
  ptr_type
  auto_rdbuf() const;

  /*
  Sets the underlying stream buffer to ptr_type's pointer, while returning
  previous pointer.
  */
  std::basic_streambuf<charT,traits> *
  rebind();

private:
  ptr_type shptr;
};

typedef basic_shared_ostream<char> shared_ostream;
typedef basic_shared_ostream<wchar_t> wshared_ostream;

} /* smart_stream */
#include "./bits/shared_ostream.tcc"
#endif
