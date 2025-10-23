#include <iostream>
#include <vector>
#include <string>
#include "ArrayList.h"

using namespace std;

int main()
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	vector<int> vec;
	vec.push_back(120);
	vec.push_back(20);
	vec.push_back(30);
	vec.push_back(40);
	vec.push_back(50);
	vec.push_back(60);
	vec.push_back(70);
	vec.push_back(80);
	vec.push_back(90);
	vec.push_back(100);
	vec.push_back(110);
	vec.push_back(120);

	vector<int> vec2;

	vec2.push_back(500);
	vec2.push_back(600);
	vec2.push_back(700);

	vec2.swap(vec);

	vec.resize(10);

	vec.push_back(130);
	vec.push_back(140);
	vec.push_back(150);
	vec.push_back(160);

	vec2 = vec;

	size_t size = vec.capacity();

	for (int i = 0; i < vec.size(); ++i)
	{
		std::cout << vec[i] << std::endl;
	}

	ArrayList<int> mylist;

	mylist.push_back(10);
	mylist.push_back(20);
	mylist.push_back(30);
	mylist.push_back(50);
	mylist.push_back(60);
	mylist.push_back(70);
	mylist.push_back(80);
	mylist.push_back(90);
	mylist.push_back(100);
	mylist.push_back(110);
	mylist.push_back(120);
	
	ArrayList<int> mylist2(mylist);

	ArrayList<int> mylist3(std::move(mylist));

	ArrayList<int> mylist4 = mylist3;

	ArrayList<int> mylist5;

	mylist5 = mylist4;

	ArrayList<int> mylist7;

	mylist7.push_back(1000);
	mylist7.push_back(1000);
	mylist7.push_back(1000);
	
	mylist7.swap(mylist5);
	
	mylist.clear();


	for (int i = 0; i < mylist.size(); ++i)
	{
		std::cout << mylist[i] << std::endl;
	}

	return 0;
}