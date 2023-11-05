#include <list/list.h>
#include <gtest/gtest.h>
#include <iostream>
//1
TEST(list_tests,default_constructor) {
	linked_list<int> list = linked_list<int>();
	ASSERT_EQ(list.get_size(), 1);
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
//5
TEST(list_tests, add_to_head_value) {
	linked_list<int> list = linked_list<int>(3);
	list.add_to_head(5);
	ASSERT_EQ(list.get_size(), 4);
}
//6
TEST(list_tests, copy_constr) {
	linked_list<int> list = linked_list<int>(3);
	auto list_copy(list);
	ASSERT_EQ(list.get_size(), 3);
}
//7
TEST(list_tests, operator_eq) {
	linked_list<int> list = linked_list<int>(3);
	auto list_copy=list;
	ASSERT_EQ(list.get_size(), 3);
}
//8
TEST(list_tests,add_to_head_list) {
	linked_list<int> list = linked_list<int>(3);
	linked_list<int> list2 = linked_list<int>(3);
	list.add_to_head(list2);
	ASSERT_EQ(list.get_size(), 6);
}
//9
TEST(list_tests, pop_head) {
	linked_list<int> list = linked_list<int>(3);
	
	list.pop_head();
	
	//ASSERT_EQ(list.get_size(), 6);
}
//9
TEST(list_tests, get_tail) {
	linked_list<int> list = linked_list<int>(3);
	
	
	//ASSERT_EQ(list.get_size(), 6);
}
//9
TEST(list_tests, pop_tail) {
	linked_list<int> list = linked_list<int>(0);

	list.pop_tail();

	//std::cout << list.get_tail()->value;


	//ASSERT_EQ(list.get_size(), 6);
}

