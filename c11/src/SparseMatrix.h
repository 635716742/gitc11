#pragma once
#include <vector>
typedef std::vector<std::vector<int> > Matrix;

struct CSRMatrix
{
	int max_line = 0;
	int max_colum = 0;
	std::vector<int> values;
	std::vector<int> column; //������
	std::vector<int> line_offset; //��ƫ��

	//ȫ0��Ҫ����ƫ��
};
class SparseMatrix
{
public:
	SparseMatrix();
	virtual ~SparseMatrix();

	bool CSR(const Matrix& matrix, CSRMatrix& csr_matrix);
	bool UnCSR(const CSRMatrix& csr_matrix, Matrix& matrix);
};

