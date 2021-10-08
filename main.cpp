#include <iostream>
#include "MyUnique_ptr.hpp"
#include "MyShared_ptr.hpp"
using namespace std;

int main()
{
	my_pointers::MyUnique_ptr<int> unique_iptr(new int());
	my_pointers::MyShared_ptr<int> shared_iptr(new int());

	return 0;
}