#include <gtest/gtest.h>
#include "Tree.h"
using namespace dataStructure;
TEST(TreeTest, get_result)
{
	Tree tree1;

	Node n1(4); Node n2(2); Node n3(1); Node n4(3); Node n5(6);
	tree1.add(&n1); 
	tree1.add(&n2); 
	tree1.add(&n3); 
	tree1.add(&n4); 
	tree1.add(&n5); 
	

	std::vector<int> result;
	std::vector<int> result_true = {1, 2, 3, 4, 6};
	tree1.LdrRecursion(result);
	std::string str1, str2;
	for (auto i : result) {
		str1 += std::to_string(i) + " ";
	}
	for (auto i : result_true) {
		str2 += std::to_string(i) + " ";
	}
	ASSERT_STREQ(str1.data(), str2.data());
}