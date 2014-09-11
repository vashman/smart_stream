// create shared stream and avoid deleting cout.

//

#include <iostream>
#include <memory>
#include <sstream>
#include "../src/shared_ostream.hpp"

using std::cout;
using std::stringbuf;
using std::ostream;
using std::streambuf;
using std::shared_ptr;
using smart_stream::shared_ostream;

/*
d functor will check excusly if the managed object is eqivelent to
cout.rdbuf() return value. In which case delete is not called.
*/
struct d{
void operator() (streambuf * _ptr){
  if (_ptr != cout.rdbuf()){
	cout << "\n deleting ptr";
  delete _ptr;
  } else {
  cout << "\nnot deleting ptr";
  }
}
};

int main(){
shared_ostream stream(cout.rdbuf(), d());
stream << "\n testing a string \n";

/*
stream << "no longer works";
the functor d is passed even when the interal deleter is switched.
*/
auto ptr = stream.auto_rdbuf(shared_ptr<streambuf>(new stringbuf()));
return 0;
}
