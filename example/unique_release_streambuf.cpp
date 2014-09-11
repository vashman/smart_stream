// create unique stream and release ownership before delete.

//

/* works with input, output */
#include "../src/unique_iostream.hpp"
#include <iostream>
#include <memory>

using std::cout;
using smart_stream::unique_stream;

int main(){
unique_stream stream(cout.rdbuf());
stream << "\n testing a string";
auto p = stream.auto_rdbuf(); // stream << "no longer works";
p.release();
return 0;
}
