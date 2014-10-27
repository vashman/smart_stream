// use unmanged unique_stream

//

#include <iostream>
#include <sstream>
#include "../include/unique_stream.hpp"
#include "../include/shared_stream.hpp"

using smart_stream::unique_stream;
using smart_stream::shared_stream;

int main(){
/* A unmanged stream, the underlying stream should set with a bad bit
since there is no stream buffer.
*/
unique_stream stream1(nullptr);

/* A normal shared stream with string stream buffer. */
shared_stream stream2(new std::stringstream());

/* use stream1 base rdbuf to set buffer to use cout's streambuf.
Stream1 is now a unmanged stream.
*/
stream1.rdbuf(std::cout.rdbuf());
stream1 << "\n testing stream1 now.";

/**/
stream2.rdbuf(std::cout.rdbuf());
stream2 << "\n testing stream2 now.";

/* stream2 is rebound to use the stringstream buffer it had
orginally.
*/
stream2.rebind();
stream2 << "\n testing stream2 now.";

/* Stream1 is not manging the cout buffer, and only has a nullptr.
At this point nothing is deleted when the stream is destructed.

Stream2 will call delete on the stringstream buffer whether it was
rebound or not since it was constructed as a shared_ptr instread of a
raw pointer.
*/ 
return 0;
}
