#include "SparseMatrix.h"



SparseMatrix::SparseMatrix()
{
}


SparseMatrix::~SparseMatrix()
{
}

bool SparseMatrix::CSR(const Matrix& matrix, CSRMatrix& csr_matrix)
{
	int count = 0;
	int pre_i = -1;
	size_t i = 0;
	size_t j = 0;
	for (; i < matrix.size(); ++i)
	{
		//bool all_zero = true;
		for (j = 0; j < matrix[i].size(); ++j)
		{
			if (matrix[i][j] != 0)
			{
				if (pre_i != i)
				{
					pre_i = i;
					csr_matrix.line_offset.push_back(csr_matrix.column.size());
				}
				csr_matrix.column.push_back(j);
				csr_matrix.values.push_back(matrix[i][j]);
				count++;
				//all_zero = false;
			}
		}

		//if (all_zero)
		//{
		//	auto iter = csr_matrix.line_offset.rbegin();
		//	if (iter != csr_matrix.line_offset.rend())
		//	{
		//		csr_matrix.line_offset.push_back(*iter);
		//	}
		//}
	}
	csr_matrix.max_line = i;
	csr_matrix.max_colum = j;
	csr_matrix.line_offset.push_back(count);
	return true;
}

bool SparseMatrix::UnCSR(const CSRMatrix& csr_matrix, Matrix& matrix)
{
	for (auto i = 0; i < csr_matrix.max_line; ++i)
	{
		std::vector<int> column;
		for (auto j = 0; j < csr_matrix.max_colum; ++j)
		{
			column.push_back(0);
		}
		matrix.push_back(column);
	}

	size_t i = 0;

	for (size_t j = 0; j < csr_matrix.values.size();++j)
	{
		matrix[i][csr_matrix.column[j]] = csr_matrix.values[j];
		if (i + 1 < csr_matrix.line_offset.size() && j+1 == csr_matrix.line_offset[i + 1])
		{
			i++;
		}
	}
	return true;
}
