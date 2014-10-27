#include <sstream>
#include "../include/shared_stream.hpp"

using smart_stream::shared_stream;

int main(){

/* construct a shared stream from a raw pointer */
shared_stream output(new std::stringstream());

/* pass a constructed shared ptr to the shared stream */
shared_ptr<std::streambuf> ptr(new std::stringstream());
shared_stream output2(ptr);

return 0;
}
