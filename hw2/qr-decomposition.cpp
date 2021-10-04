#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip> 
using namespace std;

void compute_q(double matrix[][10][10], int ma_index, int M, int N, double q[][10][10])
{
	double A[M][N], length_A=0, q_inner_a=0;
	
	for(int j=0; j<N; j++)
		for(int i=0; i<M; i++)
			A[i][j]=0;
	
	for(int j=0; j<N; j++)
		for(int i=0; i<M; i++)
			A[i][j] = matrix[ma_index][i][j];
	
	for(int j=0; j<N; j++)
	{
		length_A=0;
		for(int i=0; i<M; i++)
			length_A = length_A + A[i][j] * A[i][j];
		length_A = sqrt(length_A);
		
		for(int i=0; i<M; i++)
			q[ma_index][i][j] = A[i][j] / length_A;
			
		if(j!=N-1)
		{
			for(int k=0; k<j+1; k++)
			{
				q_inner_a=0;
				
				for(int i=0; i<M; i++)
					q_inner_a = q_inner_a + q[ma_index][i][k]*matrix[ma_index][i][j+1];
					
				for(int i=0; i<M; i++)
					A[i][j+1] = A[i][j+1] - q_inner_a*q[ma_index][i][k];
			}
		}
	}
}

void compute_R(double matrix[][10][10], int ma_index, int M, int N, double q[][10][10], double R[][10][10])
{
	double q_inner_a;
	
	for(int j=0; j<N; j++)
		for(int i=0; i<M; i++)
			R[ma_index][i][j]=0;
			
	for(int j=0; j<N; j++)
	{
		for(int k=0; k<j+1; k++)
		{
			q_inner_a=0;
				
			for(int i=0; i<M; i++)
				q_inner_a = q_inner_a + q[ma_index][i][k]*matrix[ma_index][i][j];
			R[ma_index][k][j] = q_inner_a;
		}
	} 
}

int main()
{
	int num, ma_index=0, M, N, element;
	double matrix[10][10][10], q[10][10][10], R[10][10][10];
	
	ifstream inFile("input.txt", ios::in);
	ofstream outFile("output.txt", ios::out);
	
	outFile << fixed << setprecision(2);
	
	inFile >> num;
	outFile << num << " " << endl;
	
	for(int n=0; n<num; n++)
	{
		inFile >> M >> N;
		for(int i=0; i<M; i++)
		{
			for(int j=0; j<N; j++)
			{
				inFile >> element;
				matrix[ma_index][i][j] = element;
			}
		}
				
		compute_q(matrix, ma_index, M, N, q);
		outFile << M << " " << N << " " << endl;
		for(int i=0; i<M; i++)
		{
			for(int j=0; j<N; j++)
			{
				if(abs(q[ma_index][i][j]) < 0.005)
					q[ma_index][i][j]=0;
				outFile << q[ma_index][i][j] << " ";
			}
			outFile << endl;
		}
		
		compute_R(matrix, ma_index, M, N, q, R);
		outFile << N << " " << N << " " << endl;
		for(int i=0; i<N; i++)
		{
			for(int j=0; j<N; j++)
				outFile << R[ma_index][i][j] << " ";
			outFile << endl;
		}
		ma_index++;
	}
			
	return 0;	
}
