// istream using shared_ptr for device managment

//          Copyright Sundeep S. Sangha 2013 - 2014.

#ifndef SMART_STREAM_SHARED_ISTREAM_HPP
#define SMART_STREAM_SHARED_ISTREAM_HPP

#include <streambuf>
#include <istream>
#include <memory>

namespace smart_stream {
/* basic_shared_istream */
template <typename charT, typename traits = std::char_traits<charT> >
class basic_shared_istream : public std::basic_istream<charT,traits>{
public:
  typedef std::shared_ptr<std::basic_streambuf<charT,traits> > ptr_type;

  typedef typename std::basic_istream<charT,traits>::char_type char_type;

  typedef typename std::basic_istream<charT,traits>::int_type int_type;

  typedef typename std::basic_istream<charT,traits>::pos_type pos_type;

  typedef typename std::basic_istream<charT,traits>::off_type off_type;

  typedef typename std::basic_istream<charT,traits>
                                             ::traits_type traits_type;

  explicit
  basic_shared_istream(
    ptr_type &&
  );

  explicit
  basic_shared_istream(
    ptr_type &
  );

  explicit
  basic_shared_tstream(
    std::basic_streambuf<charT,traits> * const
  );

  template <typename deleter>
  explicit
  basic_shared_istream(
    std::basic_streambuf<charT,traits> * const
  , deleter
  );

  template <typename deleter, typename allocator>
  explicit
  basic_shared_istream(
    std::basic_streambuf<charT,traits> * const
  , deleter
  , allocator
  );

  basic_shared_istream(
    basic_shared_istream<charT,traits> &&
  );

  basic_shared_istream<charT,traits> &
  operator=(
    basic_shared_istream<charT,traits> &&
  );

  basic_shared_istream(
    basic_shared_istream const &
  ) = delete;

  basic_shared_istream<charT,traits> &
  operator=(
    basic_shared_istream<charT,traits> const &
  ) = delete;

  ~basic_shared_istream();

  ptr_type
  auto_rdbuf(
    ptr_type &
  );
  
  ptr_type
  auto_rdbuf(
    ptr_type &&
  );

  ptr_type
  auto_rdbuf() const;

  std::basic_streambuf<charT,traits> *
  rebind();

private:
  ptr_type shptr;
};

typedef basic_shared_istream<char> shared_istream;
typedef basic_shared_istream<wchar_t> wshared_istream;

} /* smart_stream */
#include "./bits/shared_istream.tcc"
#endif
