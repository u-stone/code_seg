#include <iostream>
using namespace std;
#include "newhandler.h"
#include <stdlib.h>

class ctestnh : public INewSpec<ctestnh>{
public:
	ctestnh(){}
	~ctestnh(){}
private:
	char buf[1024];
};

void except_err(){
	cout << "failed in ctest class" << endl;
	exit(-1);
}
void except_err2(){
	cout << "called in ctest class" << endl;
}


int main()
{
    ctestnh::set_new_handler(except_err);
	ctestnh* pt = new ctestnh[0xFFFFFFF];
    return 0;
}

//output:
//failed in ctest class