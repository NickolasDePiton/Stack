#include <stack.cpp>
#include <catch.hpp>
#include <iostream>
using namespace std;

SCENARIO("count", "[count]"){
  stack<int> s;
  s.push(1);
  REQUIRE(s.count()==1);
}

SCENARIO("push", "[push]"){
  stack<int> s;
  s.push(1);
  REQUIRE(s.count()==1);
}

SCENARIO("pop", "[pop]"){
  stack<int> s;
  s.push(1);
  REQUIRE(*(s.pop())==1);	
  REQUIRE(s.count()==0);
}

SCENARIO("prisv", "[prisv]"){
  stack<int> s;
  s.push(1);
  stack<int> s2;
  s2=s;
  REQUIRE(s.count()==1);
}

SCENARIO("empty", "[empty]"){
  stack<int> s1, s2;
  s1.push(1);
  REQUIRE(!s1.empty());
  REQUIRE(s2.empty());
}

SCENARIO("threads", "[threads]"){
  stack<int> s;
  s.push(1);
  s.push(2);
  s.push(3);
	std::thread t1([&s](){
		for (int i = 0; i < 5; i++) {
			s.push(i + 4);
		}
	});
	std::thread t2([&s](){
		for (int i = 0; i < 5; i++)
		{
			s.pop();
		}
	});
	t1.join();
	t2.join();
  REQUIRE(s.count()==3);
}
