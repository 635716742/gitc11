#pragma once
#include <vector>
typedef std::vector<std::vector<int> > Matrix;

struct CSRMatrix
{
	int max_line = 0;
	int max_colum = 0;
	std::vector<int> values;
	std::vector<int> column; //列坐标
	std::vector<int> line_offset; //行偏移

	//全0需要加列偏移
};
class SparseMatrix
{
public:
	SparseMatrix();
	virtual ~SparseMatrix();

	bool CSR(const Matrix& matrix, CSRMatrix& csr_matrix);
	bool UnCSR(const CSRMatrix& csr_matrix, Matrix& matrix);
};

