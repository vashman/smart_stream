 Smart Stream Tutorial
==========================================================================
Examples are shown here with the realative snippt, full working examples
can be found in the examples directory.

The examples use the following terms;
*) Stream: the stream object, `std::istream`, `std::ostream`
*) Managed:
*) Buffer: the `std::streambuf` object

Unique/Shared stream examples
==========================================================================
### Use raw `std::streambuf` pointer.
Use an un-managed buffer pointer.

1. set the streams internal buffer to use the raw pointer.
   `stream.rdbuf(raw_ptr);`

#### Switch back to managed `std::streambuf` and remove raw pointer.
After a raw pointer is set, reset the stream to use the internal managed
pointer.

1. set the stream to use the internal managed pointer.
   `delete stream.rebind();`

### Construct Stream

 Unique stream examples
==========================================================================

### Use custom deleter
### Release ownership of `std::streambuf`
To release ownership while avoiding calling the deleter.

1. client takes ownership.
   `auto ptr = stream.auto_rdbuf();`

2. take raw buffer pointer.
   `auto raw_ptr = ptr.get();`

3. call release of the managed buffer.
   `ptr.release();`

 Shared stream examples
==========================================================================
### Use custom deleter
