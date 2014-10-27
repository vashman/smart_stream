#include <sstream>
#include "../include/unique_stream.hpp"

using smart_stream::unique_stream;

int main(){

/**/
unique_stream output(new std::stringstream());

/**/
unique_ptr<std::streambuf> ptr(new std::stringstream());
unique_stream output2(ptr);

return 0;
}
