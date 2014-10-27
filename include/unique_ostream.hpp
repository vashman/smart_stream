// output stream using std::unique_ptr for device managment.

//          Copyright Sundeep S. Sangha 2013 - 2014.

#ifndef SMART_STREAM_UNQIUE_OSTREAM_HPP
#define SMART_STREAM_UNQIUE_OSTREAM_HPP

#include <streambuf>
#include <ostream>
#include <memory>

namespace smart_stream {
/* unique_stream

Provides a stream with auto_rdbuf taking a unique_ptr which will manage
the lifespan of the underlying Buffer. The smart stream will not hide an
base class's rdbuf(streambuf*), which will allow a client to use a
unmanged Buffer.

The unique_stream takes the following template arguments;
1. charT, char type used by streambuf and osstream.

2. traits, char traits used by this, streambuf and ostream, defaulting to
   std::char_traits<charT>.

3. Deleter, unique_ptr deleter for the above Buffer pointer,
   defaulting to std::default_delete.
*/
template <
  typename charT
, typename traits = std::char_traits<charT>
, typename Deleter = std::default_delete <
    std::basic_streambuf<charT,traits>
  >
>
class  basic_unique_ostream : public std::basic_ostream<charT,traits>{
public:
  typedef std::unique_ptr<std::basic_streambuf<charT,traits>
                                                   , Deleter>   ptr_type;

  typedef typename std::basic_ostream<charT,traits>::char_type char_type;

  typedef typename std::basic_ostream<charT,traits>::traits_type
                                                           traits_type;

  typedef typename std::basic_ostream<charT,traits>::int_type int_type;

  typedef typename std::basic_ostream<charT,traits>::pos_type pos_type;

  typedef typename std::basic_ostream<charT,traits>::off_type off_type;

  explicit
  basic_unique_ostream(
   ptr_type &&
  );

  /*
  Takes Buffer pointer and sets internal ptr_type to manage it. If it is
  not desired that this class detroy Buffer, then use stream rdbuf.
  */
  explicit
  basic_unique_ostream(
   std::basic_streambuf<charT,traits> * const
  );

  basic_unique_ostream(
   basic_unique_ostream<charT,traits,Deleter> &&
  );

  basic_unique_ostream<charT,traits,Deleter> &
  operator=(
   basic_unique_ostream<charT,traits,Deleter> &&
  );

  basic_unique_ostream(
   basic_unique_ostream<charT,traits,Deleter> const &
  ) = delete;

  basic_unique_ostream<charT,traits,Deleter> &
  operator=(
   basic_unique_ostream<charT,traits,Deleter> const &
  ) = delete;

  ~basic_unique_ostream();

  /*
  Assigns a new ptr_type to the stream, while moving out the previous
  Buffer.
  */
  ptr_type
  auto_rdbuf(
    ptr_type &&
  );

  /*
  Returns previous ptr_type, setting the internal and stream Buffer to
  null.
  */
  ptr_type
  auto_rdbuf();

  /*
  Sets the underlying stream buffer to this->uqptr pointer,
  while returning previous pointer vid ostream.rdbuf().
  */
  std::basic_streambuf<charT,traits> *
  rebind();

private:
  ptr_type uqptr;
};

typedef basic_unique_ostream<char> unique_ostream;
typedef basic_unique_ostream<wchar_t> wunique_ostream;

} /* smart_stream */
#include "./bits/unique_ostream.tcc"
#endif
