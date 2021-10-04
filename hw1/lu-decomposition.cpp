#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip> 
using namespace std;

bool LU_de(double matrix[][10][10], double low_tri[][10][10], double P[][10][10], double false_ma[][10][10], int M, int N, int num_count)
{
	bool re=true;
	double mul, temp, temp_P;
	
	for(int i=0; i<M; i++)
	{
		for(int j=0; j<M; j++)
		{
			low_tri[num_count][i][j]=0;
			P[num_count][i][j]=0;
		}
		low_tri[num_count][i][i]=1;
		P[num_count][i][i]=1;
	}
	
	for(int num=0; num<N; num++)
	{
		for(int i=num+1; i<M; i++)
		{
			mul = matrix[num_count][i][num] / matrix[num_count][num][num];
			
			if(isnan(mul) or isinf(mul) or isinf(-mul))
			{
				for(int j=num; j<N;j++)
				{
					temp=matrix[num_count][num][j];
					matrix[num_count][num][j] = matrix[num_count][i][j];
					matrix[num_count][i][j] = temp;
					
				}
				for(int j=0; j<M; j++)
				{
					temp_P=P[num_count][num][j];
					P[num_count][num][j] = P[num_count][i][j];
					P[num_count][i][j] = temp_P;
					
					temp=false_ma[0][num][j];
					false_ma[0][num][j] = false_ma[0][i][j];
					false_ma[0][i][j] = temp;
				}
				re=false;
				continue;
			}

			low_tri[num_count][i][num] = mul;
			for(int j=num; j<N; j++)
			{
				matrix[num_count][i][j] = matrix[num_count][i][j] - matrix[num_count][num][j] * mul;
			}
		}
	}
		
	return re;
}

int main()
{
	int num, ma_index=0, M, N, element;
	double matrix[10][10][10], low_tri[10][10][10], P[10][10][10], false_ma[1][10][10];
	
	ifstream inFile("input.txt", ios::in);
	ofstream outFile("output.txt", ios::out);
	
	outFile << fixed << setprecision(2);
	
	inFile >> num;
	outFile << num << " " << endl;
	
	for(int i=0; i<num; i++)
	{
		inFile >> M >> N;
		for(int j=0; j<M; j++)
		{
			for(int k=0; k<N; k++)
			{
				inFile >> element;
				matrix[ma_index][j][k] = element;
			}
		}
		for(int i=0; i<M; i++)
			for(int j=0; j<N; j++)
				false_ma[0][i][j]=matrix[ma_index][i][j];
		
		if(LU_de(matrix, low_tri, P, false_ma, M, N, ma_index))
			outFile << "True " << endl;
		else
		{
			outFile << "False " << endl;
			outFile << M << " " << M << " " << endl;
			for(int j=0; j<M; j++)
			{
				for(int k=0; k<M; k++)
					outFile << P[ma_index][j][k] << " ";
				outFile << endl;
			}
			
			for(int i=0; i<M; i++)
				for(int j=0; j<N; j++)
					matrix[ma_index][i][j] = false_ma[0][i][j];
			LU_de(matrix, low_tri, P, false_ma, M, N, ma_index);
		}
			
		outFile << M << " " << M << " " << endl;
		for(int j=0; j<M; j++)
		{
			for(int k=0; k<M; k++)
				outFile << low_tri[ma_index][j][k] << " ";
			outFile << endl;
		}
		
		outFile << M << " " << N << " " << endl;
		for(int j=0; j<M; j++)
		{
			for(int k=0; k<N; k++)
				outFile << matrix[ma_index][j][k] << " ";
			outFile << endl;
		}
		
		ma_index++;
		
	}
			
	return 0;	
}

