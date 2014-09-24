Sundeep S. Sangha < <sun.sangha@gmail.com> >

July 27, 2014

II. Introduction
==========================================================================
A very brief high level view of your proposal, understandable by C++ committee members who are not necessarily experts in whatever domain you are addressing.


III. Motivation and Scope
==========================================================================
The current model of input/output in the standard couples `std::streambuf`
with a io stream uneedingly. This forces class developers to make
comprimises.

Underlying streambuffer
--------------------------------------------------------------------------
The lifetime and mangament of the `std::streambuf` class can be difficult
to control and understand. A dynamicly allocated buffer provides no
control over ownership when shared with multiple clients, instead it is
simpiler to re-allocate buffers over sharing. Clean up of allocated
buffers are desgined to be used in conjuction of higher level stream
classes.

Stream object
--------------------------------------------------------------------------
Derived stream classes can extend the stream interface to support the
underlying streambuf object. This may cause a conflict with the
`std::ios_base::rdbuf(streambuf*)` function. This removes any gurantee
that a client can provide in there code base about the base interface as
well as whether any extentions added can be supported when switching the
stream class.

It is common for the derived stream to also take ownership and deallocate
the underlying streambuffer. This can make sharing a single streambuffer
object more difficult. While forcing usage of raw pointers in order to use
std::streambuf or derived class functions on the underlying device.

By providing a common interface and memory mangment model for
streambuffers a cleint use a stream interface with a strong gurantee in
what it provides, and side effects. As well as automatic mangment of
streambuffer objects.

These classes provide a consistant interface, with consistant side
effects. Using `std::unique_ptr` or `std::shared_ptr` for memory
managment of streambuf objects.

IV. Impact On the Standard
==========================================================================
This proposal is a pure library extension. It adds six additonal header
each using a standard smart pointer type and; input, output, and both
input/output stream. There are no core language changes, and it has been
implemented in standard C++ with dependcy's on; `ostream, istream
, iostream, streambuf, shared_ptr, unique_ptr`.

V. Design Decisions
==========================================================================
A. Design
--------------------------------------------------------------------------
1. almost identical interface
2. providing no more then what a stream is concerned with.
3. having the stream not rely on the memory object.
4. drop in replacement of `std::basic_ostream, std::basic_istream
, std::basic_iostream`
5. not hiding `std::ios_base::rdbuf`
6. not tieing streams, or manging tied streams

B. Alternatives
--------------------------------------------------------------------------
The main alternative with only the standard libray is to either; and pass the stream as there base class and reply on, or 
1. shared streams vs shared streambuf: error state, formatting data, clarity

C. Gurantee requirements
--------------------------------------------------------------------------
1. support ownership model of smart pointer in use
2. ownership of streambuf

D. Implemation details
--------------------------------------------------------------------------
1. dealing with empty pointers

Why did you choose the specific design that you did? What alternatives did you consider, and what are the tradeoffs? What are the consequences of your choice, for users and implementers?
 What decisions are left up to implementers? If there are any similar libraries in use, how do their design decisions compare to yours?

VI. Technical Specifications
==========================================================================
A. Header `<unique_ostream>` synopsis
--------------------------------------------------------------------------
```cpp
namespace smart_stream {
  template <typename CharT
  , typename Traits = std::char_traits<CharT>
  , typename Deleter = std::default_delete <
          std::basic_streambuf<CharT,Traits>
    >
  >
  class  basic_unique_ostream : public std::basic_ostream<CharT,Traits>{
  public:
  typedef std::unique_ptr<std::basic_streambuf<CharT,Traits>
                          , Deleter> ptr_type;

  typedef typename std::basic_ostream<CharT,Traits>::char_type char_type;
  typedef typename std::basic_ostream<CharT,Traits>
                                     ::traits_type traits_type;
  typedef typename std::basic_ostream<CharT,Traits>::int_type int_type;
  typedef typename std::basic_ostream<CharT,Traits>::pos_type pos_type;
  typedef typename std::basic_ostream<CharT,Traits>::off_type off_type;

  // constructors
  explicit
  basic_unique_ostream(
    ptr_type &&
  );
	
  explicit
  basic_unique_ostream(
   std::basic_streambuf<CharT,Traits> * const
  );
	
  basic_unique_ostream(
   basic_unique_ostream<CharT,Traits,Deleter> &&
  );

  basic_unique_ostream(
   basic_unique_ostream<CharT,Traits,Deleter> const &
  ) = delete;

  // destructor
  ~basic_unique_ostream();

  // assignment
  basic_unique_ostream<CharT,Traits,Deleter> &
  operator=(
   basic_unique_ostream<CharT,Traits,Deleter> &&
  );

  basic_unique_ostream<CharT,Traits,Deleter> &
  operator=(
   basic_unique_ostream<CharT,Traits,Deleter> const &
  ) = delete;

  // modifiders
  ptr_type
  auto_rdbuf(ptr_type &&);

  ptr_type
  auto_rdbuf();

  std::basic_streambuf<CharT,Traits> *
  rebind();
private:
  ptr_type uqptr;
};

// typedefs
typedef basic_unique_ostream<char> unique_ostream;
typedef basic_unique_ostream<wchar_t> wunique_ostream;
}
```

### Class template `basic_unique_ostream`
The class uses a internal ``std::unique_ptr` to store the pointer, and
inherits `std::basic_ostream`.

#### `basic_unique_ostream` constructors

`basic_unique_ostream (unique_ptr<streambuf<CharT,Triats>> && p)`
**************************************************************************
__Requires:__ `unique_ptr` of `std::streambuf<CharT,Traits>` type with
matching class deleter.

__Effects:__ swaps the internal unique_ptr with p, and sets the ostream
streambuffer to the pointer in p.

__Postconditions:__ if `ios::base` or `basic_ostream` change, such as
setting a nullptr which should set the streams badbit.

__Throws:__ throws if swaping `unique_ptr` throws or if underlying stream
is set to throw.
***

`basic_unique_ostream (basic_streambuf<CharT,Traits> * const p)`
*************************************************************************
__Requires:__ pointer to streambuf with matching template types.

__Effects:__ constructs the internal `unique_ptr` with p, and constructs
`basic_ostream<CharT,Traits>` with p.

__Postconditions:__ if `ios::base` or `basic_ostream` change, such as
setting a nullptr which should set the streams badbit.

__Throws:__ throws if swaping `unique_ptr` throws or if underlying stream
is set to throw.
***

#### `basic_unique_ostream` destructor

`~basic_unique_ostream()`
**************************************************************************

__Requires:__ the preconditions for calling the function
__Effects:__ the actions performed by the function
__Postconditions:__ the observable results established by the function
__Returns:__ a description of the value(s) returned by the function
__Throws:__ any exceptions thrown by the function, and the conditions that would cause the exception
__Complexity:__ the time and/or space complexity of the function
__Rationale:__ the rationale for the function's design or existence 

#### `basic_unique_ostream` assigment
#### `basic_unique_ostream` modififers

 B. Header `<unique_istream>` synopsis
--------------------------------------------------------------------------
```cpp

```

### Class template `basic_unique_istream`
This class uses an internal `std::unique_ptr`, and inherits
`std::basic_istream`.

#### `basic_unique_istream` constructors
`basic_unique_istream(unique_ptr<> && p)`
**************************************************************************
`basic_unique_istream(streambuf<> * const p)`
**************************************************************************
`basic_unique_istream(basic_unique_istream<> && s)`
**************************************************************************

#### `basic_unique_istream` destructor
`~basic_unique_istream()`
**************************************************************************

#### `basic_unique_istream` assigment
`basic_unique_istream operator=(basic_unique_istream && r)`
**************************************************************************

#### `basic_unique_istream` modififers
`auto_rdbuf(unique_ptr<streambuf<CharT,Traits>> && p)`
**************************************************************************
`auto_rdbuf()`
**************************************************************************

`rebind()`
**************************************************************************

 C. Header `<unique_iostream>` synopsis
--------------------------------------------------------------------------
```cpp

```

### Class template `basic_unique_iostream`
This

#### `basic_unique_iostream` constructors
`basic_unique_istream(unique_ptr<> && p)`
**************************************************************************
`basic_unique_istream(streambuf<> * const p)`
**************************************************************************
`basic_unique_istream(basic_unique_istream<> && s)`
**************************************************************************

#### `basic_unique_iostream` destructor
`~basic_unique_istream()`
**************************************************************************

#### `basic_unique_iostream` assigment
`basic_unique_istream operator=(basic_unique_istream && r)`
**************************************************************************

#### `basic_unique_iostream` modififers
`auto_rdbuf(unique_ptr<streambuf<CharT,Traits>> && p)`
**************************************************************************
`auto_rdbuf()`
**************************************************************************
`rebind()`
**************************************************************************

 D. Header `<shared_ostream>` synopsis
--------------------------------------------------------------------------
```cpp

```
###Class template `basic_shared_ostream`
This

#### `basic_shared_ostream` constructors
#### `basic_shared_ostream` destructor
#### `basic_shared_ostream` assigment
#### `basic_shared_ostream` modififers
#### `basic_shared_ostream` observers

 E. Header `<shared_istream>` synopsis
--------------------------------------------------------------------------
```cpp

```

###Class template `basic_shared_istream`
This

#### `basic_shared_istream` constructors
#### `basic_shared_istream` destructor
#### `basic_shared_istream` assigment
#### `basic_shared_istream` modififers
#### `basic_shared_istream` observers

 F. Header `<shared_iostream>` synopsis
--------------------------------------------------------------------------
```cpp

```

### Class template `basic_shared_iostream`
This 

#### `basic_shared_iostream` constructors
#### `basic_shared_iostream` destructor
#### `basic_shared_iostream` assigment
#### `basic_shared_iostream` modififers
#### `basic_shared_iostream` observers

 Requirments
--------------------------------------------------------------------------
 Detailed specification
--------------------------------------------------------------------------
The committee needs technical specifications to be able to fully evaluate your proposal. Eventually these technical'
 specifications will have to be in the form of full text for the standard or technical report, often known as "Standardese", but for an initial proposal there are several possibilities:

 Provide some limited technical documentation. This might be OK for a very simple proposal such as a single function, but for anything beyond that the committee will likely ask for more detail.

 Provide technical documentation that is complete enough to fully evaluate your proposal.
This documentation can be in the proposal itself or you can provide a link to documentation available on the web. If the committee likes your proposal,
 they will ask for a revised proposal with formal standardese wording. The committee recognizes that writing the formal ISO specification for a library component can be daunting and will make 
additional information and help available to get you started.

 Provide full "Standardese." A standard is a contract between implementers and users, to make it possible for users to write portable code with specified semantics.
 It says what implementers are permitted to do, what they are required to do, and what users can and can't count on. The "standardese" should match the general style of exposition of the standard,
 and the specific rules set out in 17.5, Method of description (Informative) [description], but it does not have to match the exact margins or fonts or section numbering; 
those things will all be changed anyway.

VII. Acknowledgements
==========================================================================

VIII. References
==========================================================================
