// use unmanged unique_stream and then rebind to previous managed buffer.

//

#include <iostream>
#include <string>
#include <sstream>
#include "../src/unique_istream.hpp"

using std::string;
using std::stringbuf;
using std::cout;
using std::cin;
using std::getline;
using std::endl;
using smart_stream::unique_istream;

int main(){
auto ptr = new stringbuf();
unique_istream stream(ptr);
ptr->sputn ("This text is displayed last.", 28);

// use base rdbuf to set buffer.
stream.rdbuf(cin.rdbuf());

string temp;

// input from cin
cout << "\nEnter text to display: ";
getline(stream, temp);
cout << "\nstring from cin: " << temp.c_str();

stream.rebind();
getline(stream, temp);
cout <<  "\nstring from orginal buffer: " << temp << endl;

return 0;
}
