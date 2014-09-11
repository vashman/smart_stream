// use unmanged unique_stream

//

#include <iostream>
#include "../src/unique_ostream.hpp"

using std::ostream;
using std::cout;
using smart_stream::unique_ostream;

int main(){
// unmanged stream, underlying stream should set bad bit with no buffer.
unique_ostream stream(nullptr);

// use base rdbuf to set buffer.
stream.rdbuf(cout.rdbuf());

stream << "\n testing string.";
/*
stream is not manging cout buffer, and only sees
a nullptr at this point, so nothing is deleted.
*/ 
return 0;
}
