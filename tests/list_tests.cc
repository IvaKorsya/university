#include <list/list.h>
#include <gtest/gtest.h>
#include <iostream>
//1
TEST(list_tests,default_constructor) {
	linked_list<int> list = linked_list<int>();
	ASSERT_EQ(list.get_size(), 0);
	ASSERT_EQ(list.get_head()->value, 0);
}
//2
TEST(list_tests, random_value_constructor) {
	linked_list<int> list = linked_list<int>(3);
	ASSERT_EQ(list.get_size(), 3);
}
//3
TEST(list_tests, overloaded_brackets) {
	linked_list<int> list = linked_list<int>(3);
	std::cout << list;
	std::cout << list[0].value;
	std::cout << list[1].value;
	std::cout << list[2].value;
	//ASSERT_EQ(list.get_head()->value, 0);
}
