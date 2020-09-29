#pragma once
#include <vector>
#include <string>
#include <tuple>

template<typename T>
struct TreeNode
{
	T value;
	TreeNode<T>* left = NULL;
	TreeNode<T>* right = NULL;
};
typedef TreeNode<int> tn_int;
typedef TreeNode<int>* tn_intptr;

class my_algorithm
{
public:
	//假设有几种硬币，如1 5 10 20 50 100，并且数量无限。请找出能够组成某个数目的找零所使用最少的硬币数。
	int coin_max(int num);
	int dp(int num);
	//kmp
	void get_next(const std::string& str, std::vector<int>& next);
	//2sums

	//tree遍历
	//前序遍历:对于当前节点，先输出该节点，然后输出他的左孩子，最后输出他的右孩子。
	void pre_traverse(const tn_intptr root, vec_int& target);
	//中序遍历:对于当前结点，先输出它的左孩子，然后输出该结点，最后输出它的右孩子
	void middle_traverse(const tn_intptr root, vec_int& target);
	//后序遍历:对于当前结点，先输出它的左孩子，然后输出它的右孩子，最后输出该结点。
	void back_traverse(const tn_intptr root, vec_int& target);
	//任意两个序列恢复树,前提序列元素不重复
	enum 
	{
		PRE_MIDDLE,
		PRE_BACK,
		MIDDLE_BACK
	};
	void recover_tree(int type, const vec_int& seq1, const vec_int& seq2, tn_intptr root);
private:
	int _coin_max(const int& coin_value, int& num);
	void _pm_tree(vec_int& seq1, vec_int& seq2, tn_intptr root);
	void _pb_tree(vec_int& seq1, vec_int& seq2, tn_intptr root);
	void _mb_tree(vec_int& seq1, vec_int& seq2, tn_intptr root);

};

