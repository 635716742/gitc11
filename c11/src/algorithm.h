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
	//�����м���Ӳ�ң���1 5 10 20 50 100�������������ޡ����ҳ��ܹ����ĳ����Ŀ��������ʹ�����ٵ�Ӳ������
	int coin_max(int num);
	int dp(int num);
	//kmp
	void get_next(const std::string& str, std::vector<int>& next);
	//2sums

	//tree����
	//ǰ�����:���ڵ�ǰ�ڵ㣬������ýڵ㣬Ȼ������������ӣ������������Һ��ӡ�
	void pre_traverse(const tn_intptr root, vec_int& target);
	//�������:���ڵ�ǰ��㣬������������ӣ�Ȼ������ý�㣬�����������Һ���
	void middle_traverse(const tn_intptr root, vec_int& target);
	//�������:���ڵ�ǰ��㣬������������ӣ�Ȼ����������Һ��ӣ��������ý�㡣
	void back_traverse(const tn_intptr root, vec_int& target);
	//�����������лָ���,ǰ������Ԫ�ز��ظ�
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

