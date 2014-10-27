 Smart Stream Tutorial
==========================================================================
Examples are shown here with the realative snippt, full working examples
can be found in the examples directory.

The examples use the following terms;
* Stream: the stream object, `std::istream`, `std::ostream`
* Managed:
* Buffer: the `std::streambuf` object

1 Table of Contents
==========================================================================
1. Table of Contents
2. Unique/Shared Stream
  1. Set a streambuf
  2. Unmanged stream via raw pointer
  3. Force switch to managed streambuf
  4. Detect and delete unmanaged streambuf
  5. Using the derived streambuf
3. Unique Stream
4. Shared Stream

2 Unique/Shared Stream
==========================================================================
1 Set a streambuf
--------------------------------------------------------------------------
To set the streambuf object, simply either wrap the pointer in a `smart
pointer` or pass the pointer to the `smart_stream` ctor.

[example: set_unique_buf.cpp](../example/set_unique_buf.cpp)

```c++
unique_stream output(new stringstream());

unique_ptr<streambuf> ptr(new stringstream());

unique_stream output2(ptr);
```

[example: set_shared_buf.cpp](../example/set_shared_buf.cpp)

```c++
shared_stream output(new stringstream());

shared_ptr<streambuf> ptr(new stringstream());

shared_stream output2(ptr);
```

2 Unmanged stream via raw pointer
--------------------------------------------------------------------------
Useing a raw `std::streambuf` pointer it is possible to use a smart_stream
type as a regular i/o stream.

[example: unmanaged.cpp](../example/unmanaged.cpp)

```c++
stream.rdbuf(new filebuf());
```

3 Force switch to managed streambuf
--------------------------------------------------------------------------
Make the smart_stream set the internal streambuf to the manged one. Also
look at 2-4 for deleting the previous ptr.

[example: unmanaged.cpp](../example/unmanaged.cpp)
```c++
stream.rebind();
```

4 Detect and Delete a un-manged streambuf
--------------------------------------------------------------------------
There is always the chance that some code that has access to the smart
stream treats it as a standard stream and changes the underlying streambuf
. If this occurs the manged streambuf is still intact until the end of the
smart stream.

The pointer can be re-bound and the un-manged one delted, or it could just
be checked and left alone.

[example: ](../example/)

```c++
/* rebind first is optional */
auto ptr = stream.rebind();

if (ptr != stream.rdbuf())
  /* pointers are differnt */
  delete ptr;
```

5 Using Derived Streambuf
--------------------------------------------------------------------------
When using smart streams the streambuf is used as a `std::streambuf` type.
This means that any additional funciality is lost when accessing the
streambuf directly via smart streams. To use the derived streambuf without
downcasting, the derived streambuf must kept externally.

[example: external_streambuf.cpp](../example/external_streambuf.cpp)

```c++
shared_ptr<stringstream> ss(new stringstream());
shared_stream out(ss);

out << "test";
```

3 Unique Stream
==========================================================================
1 Custom Deleter
--------------------------------------------------------------------------

2 Release ownership of `std::streambuf`
--------------------------------------------------------------------------
To release ownership while avoiding calling the deleter.

[example: unique_release.cpp](../example/unique_release.cpp)
```c++
auto ptr = stream.auto_rdbuf(); /* client takes ownership. */
auto raw_ptr = ptr.get(); /* take raw buffer pointer. */
ptr.release(); /* call release of the managed buffer. */
```

4 Shared stream examples
==========================================================================
1 Custom Deleter
--------------------------------------------------------------------------
