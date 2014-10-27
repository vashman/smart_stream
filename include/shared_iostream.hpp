//

//          Copyright Sundeep S. Sangha 2013 - 2014.

#ifndef SMART_STREAM_SHARED_IOSTREAM_HPP
#define SMART_STREAM_SHARED_IOSTREAM_HPP

#include <streambuf>
#include <iostream>
#include <memory>

namespace smart_stream {

/* basic_shared_iostream */
template <typename charT, typename traits>
class basic_shared_iostream : public std::basic_iostream<charT,traits>{
public:

  ~basic_shared_iostream();

  /* Assigns a new ptr_type to the stream, while moving out the previous
  Buffer.
  */
  ptr_type
  auto_rdbuf(
    ptr_type &&
  );

  /* Returns previous ptr_type, setting the internal and stream Buffer to
  null.
  */
  ptr_type
  auto_rdbuf();

  /* Sets the underlying stream buffer to shptr's pointer, while
  returning previous pointer.
  */
  std::basic_streambuf<charT,traits> *
  rebind();

private:
  ptr_type shptr;
};

typedef basic_shared_iostream<char> shared_stream;
typedef basic_shared_iostream<wchar_t> wshared_stream;

} /* smart_stream */
#include "./bits/shared_iostream.tcc"
#endif
