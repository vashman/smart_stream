// input stream using std::unique_ptr for device managment.

//          Copyright Sundeep S. Sangha 2013 - 2014.

#ifndef SMART_STREAM_UNQIUE_ISTREAM_HPP
#define SMART_STREAM_UNQIUE_ISTREAM_HPP

#include <memory>
#include <streambuf>
#include <istream>

namespace smart_stream {

/* unique_istream

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
class  basic_unique_istream : public std::basic_istream<CharT,Traits>{
public:
  typedef std::unique_ptr<std::basic_streambuf<CharT,Traits>
                          , Deleter> ptr_type;

  typedef typename std::basic_istream<CharT,Traits>::char_type char_type;

  typedef typename std::basic_istream<CharT,Traits>
                                     ::traits_type traits_type;

  typedef typename std::basic_istream<CharT,Traits>::int_type int_type;

  typedef typename std::basic_istream<CharT,Traits>::pos_type pos_type;

  typedef typename std::basic_istream<CharT,Traits>::off_type off_type;

  explicit
  basic_unique_istream(
   ptr_type &&
  );

  /*
  Takes Buffer pointer and sets internal ptr_type to manage it. If it is
  not desired that this class detroy Buffer, then use stream rdbuf.
  */
  explicit
  basic_unique_istream(
   std::basic_streambuf<CharT,Traits> * const
  );

  basic_unique_istream(
   basic_unique_istream<CharT,Traits,Deleter> &&
  );

  basic_unique_istream<CharT,Traits,Deleter> &
  operator=(
   basic_unique_istream<CharT,Traits,Deleter> &&
  );

  basic_unique_istream(
   basic_unique_istream<CharT,Traits,Deleter> const &
  ) = delete;

  basic_unique_istream<CharT,Traits,Deleter> &
  operator=(
   basic_unique_istream<CharT,Traits,Deleter> const &
  ) = delete;

  ~basic_unique_istream();

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

typedef basic_unique_istream<char> unique_istream;
typedef basic_unique_istream<wchar_t> wunique_istream;

} /* smart_stream */
#include "bits/unique_istream.hpp"
#endif
