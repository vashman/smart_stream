Smart Stream
==========================================================================
1 Table of Contents
==========================================================================
1. Table of Contents
2. Introduction
3. Motivation and Scope
  1. Underlying streambuffer
4. Impact On the Standard
5. Desgin Decisions
6. Technical Specifications

2 Introduction
==========================================================================
Smart Stream is a implementation of; `basic_ostream`, `basic_istream`,
`basic_iostream` that provies a common interface to mangage the internal
`basic_streambuf` instance.


3 Motivation and Scope
==========================================================================
Currently the stream object is designed specifiall for a streambuffer
implemenatation. While the basic stream objects only provide a raw basic
interface for managing the stream. This library uses the concept of smart
pointers to provide a common interface for managing stream objects and
thier underlying stream buffer.

1 Underlying streambuffer
--------------------------------------------------------------------------
The lifetime and mangament of the `std::streambuf` class can be difficult
to control and understand through ou the program. When a dynamicly
allocated buffer is used there is no way to control ownership and the
lifetime.

4 Impact On the Standard
==========================================================================
This proposal is a pure library extension.

It adds six additonal headers, each using a standard smart pointer type
and. There are no core language changes, and it has been implemented in
standard C++ with dependcy's on; `ostream, istream, iostream, streambuf
and memory headers.

5 Design Decisions
==========================================================================

6 Technical Specifications
==========================================================================
1. Header `<unique_ostream>` synopsis
--------------------------------------------------------------------------
```c++
class
```

### Class template `basic_unique_ostream`
The class uses a internal ``std::unique_ptr` to store the pointer, and
inherits `std::basic_ostream`.

#### `basic_unique_ostream` constructors

##### `basic_unique_ostream (unique_ptr<streambuf<CharT,Triats>> && p)`
__Requires:__
`unique_ptr` of `std::streambuf<CharT,Traits>` type with matching class
deleter.

__Effects:__
swaps the internal `unique_ptr` with p, and sets the ostream streambuffer
to the pointer in p.

__Postconditions:__
if `ios::base` or `basic_ostream` change, such as setting a nullptr which
should set the streams badbit.

__Throws:__
throws if swaping `unique_ptr` throws or if underlying stream is set to
throw.

##### `basic_unique_ostream (basic_streambuf<CharT,Traits> * const p)`
__Requires:__
pointer to streambuf with matching template types.

__Effects:__
constructs the internal `unique_ptr` with p, and constructs
`basic_ostream<CharT,Traits>` with p.

__Postconditions:__
if `ios::base` or `basic_ostream` change, such as setting a nullptr which
should set the streams badbit.

__Throws:__
throws if swaping `unique_ptr` throws or if underlying stream is set to
throw.

#### `basic_unique_ostream` destructor

##### `~basic_unique_ostream()`
__Requires:__
the preconditions for calling the function

__Effects:__
the actions performed by the function

__Postconditions:__
the observable results established by the function

__Returns:__
a description of the value(s) returned by the function

__Throws:__
any exceptions thrown by the function, and the conditions that would cause
the exception

__Complexity:__
the time and/or space complexity of the function

__Rationale:__
the rationale for the function's design or existence 

#### `basic_unique_ostream` assigment
#### `basic_unique_ostream` modififers

 B. Header `<unique_istream>` synopsis
--------------------------------------------------------------------------
```c++
class
```

### Class template `basic_unique_istream`
This class uses an internal `std::unique_ptr`, and inherits
`std::basic_istream`.

#### `basic_unique_istream` constructors
#####`basic_unique_istream(unique_ptr<> && p)`
##### `basic_unique_istream(streambuf<> * const p)`
##### `basic_unique_istream(basic_unique_istream<> && s)`

#### `basic_unique_istream` destructor
#####`~basic_unique_istream()`

#### `basic_unique_istream` assigment
#####`basic_unique_istream operator=(basic_unique_istream && r)`

#### `basic_unique_istream` modififers
##### `auto_rdbuf(unique_ptr<streambuf<CharT,Traits>> && p)`
##### `auto_rdbuf()`

##### `rebind()`

 C. Header `<unique_iostream>` synopsis
--------------------------------------------------------------------------
```cpp
class
```

### Class template `basic_unique_iostream`
This

#### `basic_unique_iostream` constructors
#####`basic_unique_istream(unique_ptr<> && p)`
##### `basic_unique_istream(streambuf<> * const p)`
##### `basic_unique_istream(basic_unique_istream<> && s)`

#### `basic_unique_iostream` destructor
#####`~basic_unique_istream()`

#### `basic_unique_iostream` assigment
##### `basic_unique_istream operator=(basic_unique_istream && r)`

#### `basic_unique_iostream` modififers
##### `auto_rdbuf(unique_ptr<streambuf<CharT,Traits>> && p)`
##### `auto_rdbuf()`
##### `rebind()`

D. Header `<shared_ostream>` synopsis
--------------------------------------------------------------------------
```cpp
class
```
### Class template `basic_shared_ostream`
This

#### `basic_shared_ostream` constructors
#### `basic_shared_ostream` destructor
#### `basic_shared_ostream` assigment
#### `basic_shared_ostream` modififers
#### `basic_shared_ostream` observers

 E. Header `<shared_istream>` synopsis
--------------------------------------------------------------------------
```cpp
class
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
class
```

### Class template `basic_shared_iostream`
This 

#### `basic_shared_iostream` constructors
#### `basic_shared_iostream` destructor
#### `basic_shared_iostream` assigment
#### `basic_shared_iostream` modififers
#### `basic_shared_iostream` observers
