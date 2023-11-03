#include <list/list.h>
#include <gtest/gtest.h>
#include <iostream>
//1
TEST(list_tests,default_constructor) {
	linked_list<int> list = linked_list<int>();
	ASSERT_EQ(list.get_size(), 0);
}
//2
TEST(list_tests, random_value_constructor) {
	linked_list<int> list = linked_list<int>(3);
	ASSERT_EQ(list.get_size(), 3);
}
//3
TEST(list_tests, add_to_tail_value) {
	linked_list<int> list = linked_list<int>(3);
	list.add_to_tail(9);
	ASSERT_EQ(list.get_size(), 4);
}
//4
TEST(list_tests, add_to_tail_list) {
	linked_list<int> list = linked_list<int>(3);
	linked_list<int> list2 = linked_list<int>(9);
	list.add_to_tail(list2);
	ASSERT_EQ(list.get_size(), 12);
}

