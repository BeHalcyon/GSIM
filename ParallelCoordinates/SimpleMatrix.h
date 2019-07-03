/***************************************************************
*  Copyright (C) 2013 Quan Wang <wangq10@rpi.edu> 
*  Signal Analysis and Machine Perception Laboratory 
*  Department of Electrical, Computer, and Systems Engineering 
*  Rensselaer Polytechnic Institute, Troy, NY 12180, USA
* 
*  Related publication: 
*  Quan Wang, Kim L. Boyer. 
*  Feature Learning by Multidimensional Scaling and its Applications in Object Recognition. 
*  2013 26th SIBGRAPI Conference on Graphics, Patterns and Images (Sibgrapi). IEEE, 2013. 
***************************************************************/

#ifndef SIMPLE_MATRIX_H
#define SIMPLE_MATRIX_H

#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <ctime>
#include <cmath>

#define MAX_LINE_LENGTH 100000
#define EPSILON 0.0000001

namespace smat
{

	/**********************************************
	* Declaration part
	**********************************************/

	template<class T>
	class Matrix
	{
	public:
		Matrix(int rows, int columns); // initialization without assigning values
		Matrix(int rows, int columns, T value); // initialization with all same values
		Matrix(int rows, int columns, std::string type); // special matrix such as I
		Matrix(const char * filename); // load matrix from txt file
		Matrix(int dim, T* data);
		~Matrix(); // destruction
		
		void set(int r, int c, T value); // row, column, value
		T get(int r, int c); // row, column
		int rows(); // number of rows
		int columns(); // number of columns
		T** getData();
		
		void print(); // print the matrix
		Matrix * copy(); // copy itself to a new matrix
		
		void saveTxt(const char * filename); // save matrix to txt file
		
		// B=M'
		Matrix * transpose();
		// B=M(r1:r2,c1:c2)
		Matrix * sub(int r1, int r2, int c1, int c2); // submatrix
		// B=|M|
		Matrix * abs(); // absolute values
		
		// numbers of matrix
		T trace(); // trace
		float fnorm(); // Frobenius norm
		float pnorm(float p); // p-norm
		T maxEl(int &r, int &c); // max element
		T minEl(int &r, int &c); // min element
		float mean(); // mean of elements
		T sum(); // sum of elements
		float std(); // standard deviation of elements
		
		
		// M=M+a
		void addNumberSelf(T value); // add a number to itself in space
		// M=M*a
		void multiplyNumberSelf(T value); // add a number to itself in space
		
		// M=M+A
		void addMatrixSelf(Matrix * A); // add a matrix to itself in space
		// M=M.*A
		void dotMultiplyMatrixSelf(Matrix * A); // dot multiply a matrix to itself in space
		
		// B=M+A
		Matrix * addMatrixNew(Matrix * A); // add a matrix to itself with new matrix
		// B=M.*A
		Matrix * dotMultiplyMatrixNew(Matrix * A); // dot multiply a matrix to itself with new matrix
		// B=M*A
		Matrix * multiplyMatrixNew(Matrix * A); // multiply a matrix to itself with new matrix

	private:
		int rows_;
		int columns_;
		T **v;
	};



	/**********************************************
	* Utilities part
	**********************************************/

	template<class T>
	T min(T v1, T v2)
	{
		if(v1<v2) return v1;
		else return v2;
	}
	
	template<class T>
	T max(T v1, T v2)
	{
		if(v1>v2) return v1;
		else return v2;
	}
	
	template<class T>
	void swap(T &v1, T &v2)
	{
		T v3=v1;
		v1=v2;
		v2=v3;
	}
	
	template<class T>
	float sign(T v)
	{
		if(v>0) return 1.0;
		else if(v<0) return -1.0;
		else return 0.0;
	}
	
	/**********************************************
	* Implementation part
	**********************************************/
	
	template<class T>
	Matrix<T>::Matrix(int rows, int columns) // initialization without assigning values
	{
		if(rows<1||columns<1)
		{
			printf("Invalid construction arguments: rows=%d, columns=%d\n",rows,columns);
			exit(1);
		}
		
		rows_=rows;
		columns_=columns;
		
		v=new T *[rows];
		for(int i=0;i<rows;i++)
		{
			v[i]=new T[columns];
		}
	}
	
	template<class T>
	Matrix<T>::Matrix(int rows, int columns, T value) // initialization with all same values
	{
		if(rows<1||columns<1)
		{
			printf("Invalid construction arguments: rows=%d, columns=%d\n",rows,columns);
			exit(1);
		}
		
		rows_=rows;
		columns_=columns;
		
		v=new T *[rows];
		for(int i=0;i<rows;i++)
		{
			v[i]=new T[columns];
			
			for(int j=0;j<columns;j++)
			{
				v[i][j]=value;
			}
		}
	}
	
	template<class T>
	Matrix<T>::Matrix(int dim, T* data) // initialization with all same values
	{
		if(dim<1)
		{
			printf("Invalid construction arguments: dim=%d\n",dim);
			exit(1);
		}

		rows_=dim;
		columns_=dim;

		v=new T *[dim];
		for(int i=0;i<dim;i++)
		{
			v[i]=new T[dim];

			for(int j=0;j<dim;j++)
			{
				v[i][j]=data[i * dim + j];
			}
		}
	}

	template<class T>
	Matrix<T>::Matrix(int rows, int columns, std::string type) // special matrix such as I
	{
		if(rows<1||columns<1)
		{
			printf("Invalid construction arguments: rows=%d, columns=%d\n",rows,columns);
			exit(1);
		}
		rows_=rows;
		columns_=columns;
		
		v=new T *[rows];
		for(int i=0;i<rows;i++)
		{
			v[i]=new T[columns];
		}
		
		if(type.compare("I")==0)
		{
			for(int i=0;i<rows;i++)
			{
				for(int j=0;j<columns;j++)
				{
					if(i==j) v[i][j]=(T)1;
					else v[i][j]=(T)0;
				}
			}
		}
		
		else if(type.compare("rand")==0) // all elements between 0 and 1
		{
			srand (time(NULL));
			int r1;
			float r2;
			for(int i=0;i<rows_;i++)
			{
				for(int j=0;j<columns_;j++)
				{
					r1=rand()*rand()+rand()*rand()+rand();
					if(r1<0) r1=-r1;
					r2=float(r1%1000001)/1000000;
				
					v[i][j]=(T)r2;
				}
			}
		}
		
		else if(type.compare("rand_int")==0)
		{
			srand (time(NULL));
			for(int i=0;i<rows_;i++)
			{
				for(int j=0;j<columns_;j++)
				{
					v[i][j]=(T)rand();
				}
			}
		}
		
		else if(type.compare("randperm")==0) // random permutation, each column is a randperm vector of size rows*1
		{
			srand (time(NULL));
			for(int j=0;j<columns;j++)
			{
				for(int i=0;i<rows;i++)
				{
					v[i][j]=i+1;
				}
				
				for(int i=0;i<rows;i++)
				{
					int k=rand()%rows;
					if(k>=rows || k<0)
					{
						printf("Invalid row index: %d\n",k);
						exit(1);
					}
					T temp=v[i][j];
					v[i][j]=v[k][j];
					v[k][j]=temp;
				}
			}
		}
		
		else
		{
			printf("Undefined matrix type: %s\n",type.c_str());
			exit(1);
		}
	}
	
	template<class T>
	Matrix<T>::Matrix(const char * filename)
	{
		FILE * pFile;
		// first pass: matrix size
		int rows=0;
		int columns=0;
		
		pFile=fopen(filename,"r");
		if(pFile==NULL)
		{
			printf("File \"%s\" cannot be found.\n",filename);
			exit(1);
		}
		char line[MAX_LINE_LENGTH];
		char * token=NULL;
		while( fgets (line , MAX_LINE_LENGTH , pFile) != NULL )
		{
			rows++;
			if(rows==1) // count the number of columns
			{
				token=strtok(line," ,\t");
				while(token!=NULL && token[0]>=32)
				{
					columns++;
					token=strtok(NULL," ,\t");
				}
			}
			else // check whether every row contains the same number of elements with the first row
			{
				int check=0;
				token=strtok(line," ,\t");
				while(token!=NULL && token[0]>=32)
				{
					check++;
					token=strtok(NULL," ,\t");
				}
				if(check<columns)
				{
					rows--;
					break;
				}
			}
		}
		fclose (pFile);
		printf("Reading matrix from file \"%s\": %d rows, %d columns\n",filename,rows,columns);
		
		// second pass: read data
		rows_=rows;
		columns_=columns;
		v=new T *[rows];
		for(int i=0;i<rows;i++)
		{
			v[i]=new T[columns];
		}
		
		pFile=fopen(filename,"r");
		if(pFile==NULL)
		{
			printf("File \"%s\" cannot be found.\n",filename);
			exit(1);
		}
		int i=0;
		while( fgets (line , MAX_LINE_LENGTH , pFile) != NULL )
		{
			if(i>=rows) break;
			for(int j=0;j<columns;j++)
			{
				if(j==0) token=strtok(line," ,\t");
				else token=strtok(NULL," ,\t");
				v[i][j]=(T)atof(token);
			}
			i++;
		}
		fclose (pFile);
	}
	
	template<class T>
	Matrix<T>::~Matrix() // destruction
	{
		for(int i=0;i<rows_;i++)
		{
			delete[] (T *)v[i];
		}
		delete[] v;
	}
		
	template<class T>
	void Matrix<T>::set(int r, int c, T value) // row, column, value
	{
		if(r<0 || r>=rows_ || c<0 || c>=columns_)
		{
			printf("Invalid index in set(): r=%d, c=%d\n",r,c);
			exit(1);
		}
		v[r][c]=value;
	}
	
	template<class T>
	T Matrix<T>::get(int r, int c) // row, column
	{
		if(r<0 || r>=rows_ || c<0 || c>=columns_)
		{
			printf("Invalid index in get(): r=%d, c=%d\n",r,c);
			exit(1);
		}
		return v[r][c];
	}
	
	template<class T>
	int Matrix<T>::rows() // number of rows
	{
		return rows_;
	}
	
	template<class T>
	int Matrix<T>::columns() // number of columns
	{
		return columns_;
	}
	
	template<class T>
	T** Matrix<T>::getData() // number of rows
	{
		return v;
	}

	template<class T>
	void Matrix<T>::print() // print the matrix
	{
		printf("\n");
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				printf("%8.3f    ",(float)v[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
	
	template<class T>
	Matrix<T> * Matrix<T>::copy() // copy itself to a new matrix
	{
		Matrix<T> * A=new Matrix<T>(rows_,columns_);
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				A->set(i,j,v[i][j]);
			}
		}
		return A;
	}
	
	template<class T>
	void Matrix<T>::saveTxt(const char * filename)
	{
		FILE * pFile;
		pFile=fopen(filename,"w");
		if(pFile==NULL)
		{
			printf("Cannot save to file \"%s\".\n",filename);
			exit(1);
		}
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				fprintf(pFile,"%f  ",(float)v[i][j]);
			}
			fprintf(pFile,"\n");
		}
		fclose(pFile);
		printf("Matrix saved to file \"%s\"\n",filename);
	}
	
	template<class T>
	Matrix<T> * Matrix<T>::transpose()
	{
		Matrix<T> * A=new Matrix<T>(columns_,rows_);
		for(int i=0;i<columns_;i++)
		{
			for(int j=0;j<rows_;j++)
			{
				A->set(i,j,v[j][i]);
			}
		}
		return A;
	}
	
	template<class T>
	Matrix<T> * Matrix<T>::sub(int r1, int r2, int c1, int c2) // submatrix
	{
		if(r1<0 || r1>=rows_ || r2<0 || r2>=rows_ || r2<r1 || c1<0 || c1>=columns_ || c2<0 || c2>columns_ || c2<c1)
		{
			printf("Invalid submatrix indices.\n");
			exit(1);
		}
		
		int newRows=r2-r1+1;
		int newColumns=c2-c1+1;
		Matrix<T> * A=new Matrix<T>(newRows,newColumns);
		for(int i=0;i<newRows;i++)
		{
			for(int j=0;j<newColumns;j++)
			{
				A->set(i,j,v[i+r1][j+c1]);
			}
		}
		return A;
	}
	
	template<class T>
	Matrix<T> * Matrix<T>::abs() // absolute values
	{
		Matrix<T> * A=new Matrix<T>(rows_,columns_);
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				A->set(i,j,v[i][j]>0?v[i][j]:-v[i][j]);
			}
		}
		return A;
	}
	
	template<class T>
	T Matrix<T>::trace() // trace
	{
		T x=0;
		for(int i=0;i<min<int>(rows_,columns_);i++)
		{
			x+=v[i][i];
		}
		return x;
	}
	
	template<class T>
	float Matrix<T>::fnorm() // Frobenius norm
	{
		float x=0;
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				x+=(v[i][j]*v[i][j]);
			}
		}
		return sqrt(x);
	}
	
	template<class T>
	float Matrix<T>::pnorm(float p) // p-norm
	{
		float x=0;
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				x+= pow(fabs((float)v[i][j]),p);
			}
		}
		return pow(x,1/p);
	}
	
	template<class T>
	T Matrix<T>::maxEl(int &r, int &c) // max element
	{
		T x=v[0][0];
		r=0;
		c=0;
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				if(v[i][j]>x)
				{
					x=v[i][j];
					r=i;
					c=j;
				}
			}
		}
		return x;
	}
	
	template<class T>
	T Matrix<T>::minEl(int &r, int &c) // min element
	{
		T x=v[0][0];
		r=0;
		c=0;
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				if(v[i][j]<x)
				{
					x=v[i][j];
					r=i;
					c=j;
				}
			}
		}
		return x;
	}
	
	template<class T>
	float Matrix<T>::mean() // mean of elements
	{
		float x=0;
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				x+=(float)v[i][j];
			}
		}
		return x/rows_/columns_;
	}
	
	template<class T>
	T Matrix<T>::sum() // sum of elements
	{
		T x=0;
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				x+=v[i][j];
			}
		}
		return x;
	}
	
	template<class T>
	float Matrix<T>::std() // standard deviation of elements
	{
		float m=mean();
		float s=0;
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				s+= (v[i][j]-m)*(v[i][j]-m);
			}
		}
		s=s/rows_/columns;
		return sqrt(s);
	}
	
	template<class T>
	void Matrix<T>::addNumberSelf(T value) // add a number to itself in space
	{
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				v[i][j]+=value;
			}
		}
	}
	
	template<class T>
	void Matrix<T>::multiplyNumberSelf(T value) // add a number to itself in space
	{
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				v[i][j]*=value;
			}
		}
	}
	
	template<class T>
	void Matrix<T>::addMatrixSelf(Matrix * A) // add a matrix to itself in space
	{
		if(rows_!=A->rows() || columns_!=A->columns())
		{
			printf("Unmatched matrix sizes in matrix summation.\n");
			exit(1);
		}
		
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				v[i][j]+=A->get(i,j);
			}
		}
	}
	
	template<class T>
	void Matrix<T>::dotMultiplyMatrixSelf(Matrix * A) // dot multiply a matrix to itself in space
	{
		if(rows_!=A->rows() || columns_!=A->columns())
		{
			printf("Unmatched matrix sizes in matrix dot multiplication.\n");
			exit(1);
		}
		
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				v[i][j]*=A->get(i,j);
			}
		}
	}
	
	template<class T>
	Matrix<T> * Matrix<T>::addMatrixNew(Matrix * A) // add a matrix to itself with new matrix
	{
		if(rows_!=A->rows() || columns_!=A->columns())
		{
			printf("Unmatched matrix sizes in matrix summation.\n");
			exit(1);
		}
		
		Matrix<T> * B=new Matrix<T>(rows_,columns_);
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				B->set(i,j,v[i][j]+A->get(i,j));
			}
		}
		return B;
	}
	
	template<class T>
	Matrix<T> * Matrix<T>::dotMultiplyMatrixNew(Matrix * A) // dot multiply a matrix to itself with new matrix
	{
		if(rows_!=A->rows() || columns_!=A->columns())
		{
			printf("Unmatched matrix sizes in matrix dot multiplication.\n");
			exit(1);
		}
		
		Matrix<T> * B=new Matrix<T>(rows_,columns_);
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<columns_;j++)
			{
				B->set(i,j,v[i][j]*A->get(i,j));
			}
		}
		return B;
	}
	
	template<class T>
	Matrix<T> * Matrix<T>::multiplyMatrixNew(Matrix * A) // multiply a matrix to itself with new matrix
	{
		if(columns_!=A->rows())
		{
			printf("Unmatched matrix sizes in matrix multiplication.\n");
			exit(1);
		}
		
		Matrix<T> * B=new Matrix<T>(rows_,A->columns());
		T temp;
		for(int i=0;i<rows_;i++)
		{
			for(int j=0;j<A->columns();j++)
			{
				temp=0;
				for(int k=0;k<columns_;k++)
				{
					temp+= (v[i][k]*A->get(k,j));
				}
				B->set(i,j,temp);
			}
		}
		return B;
	}
}


void EuclideanDistanceMatrix(smat::Matrix<float> * X, smat::Matrix<float> * D);
void ElementCopy(smat::Matrix<float> * X, smat::Matrix<float> * Y);
smat::Matrix<float> * MDS_UCF(smat::Matrix<float> * D, smat::Matrix<float> * X0, int dim, int iter);
smat::Matrix<float> * MDS_SMACOF(smat::Matrix<float> * D, smat::Matrix<float> * X0, int dim, int iter);

#endif
