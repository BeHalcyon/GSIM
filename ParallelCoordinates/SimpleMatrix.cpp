#include "SimpleMatrix.h"

using namespace smat;

/**********************************************
	* Algorithm part
	**********************************************/	
	
// Calculate the pairwise interpoint Euclidean distances
// X is data matrix, D is distance matrix
void EuclideanDistanceMatrix(Matrix<float> * X, Matrix<float> * D)
{
	int i,j,k;
	float temp;
	if(D==NULL)
	{
		printf("Input matrix pointer is NULL.\n");
		exit(1);
	}
	else if(X->rows()!=D->rows() || X->rows()!=D->columns())
	{
		printf("Invalid distance matrix dimension.\n");
		exit(1);
	}
		
	for(i=0;i<D->rows();i++) D->set(i,i,0.0);
		
	for(i=0;i<D->rows()-1;i++)
	{
		for(j=i+1;j<D->columns();j++)
		{
			temp=0;
			for(k=0;k<X->columns();k++)
			{
				temp+= pow(X->get(i,k)-X->get(j,k),2);
			}
			D->set(i,j,sqrt(temp));
		}
	}
		
	for(i=1;i<D->rows();i++)
	{
		for(j=0;j<i;j++)
		{
			D->set(i,j,D->get(j,i));
		}
	}
}
	
// Copy all elements of X to Y
void ElementCopy(Matrix<float> * X, Matrix<float> * Y)
{
	if(Y==NULL)
	{
		printf("Input matrix pointer is NULL.\n");
		exit(1);
	}
	else if(X->rows()!=Y->rows() || X->columns()!=Y->columns())
	{
		printf("Invalid matrix dimension.\n");
		exit(1);
	}
	for(int i=0;i<X->rows();i++)
	{
		for(int j=0;j<X->columns();j++)
		{
			Y->set(i,j,X->get(i,j));
		}
	}
}
	
// Multidimensional scaling (MDS)
// This function re-implements Laurens van der Maaten's MDS in his Matlab Toolbox for Dimensionality Reduction
// The Matlab MDS can be downloaded at http://crcv.ucf.edu/source/dimension
Matrix<float> * MDS_UCF(Matrix<float> * D, Matrix<float> * X0, int dim, int iter)
{
	if(D->rows()!=D->columns())
	{
		printf("Input distance matrix to MDS is not square.\n");
		exit(1);
	}
	if(dim<1)
	{
		printf("Invalid dimension for MDS.\n");
		exit(1);
	}
	if(iter<1)
	{
		printf("Invalid number of iterations for MDS.\n");
		exit(1);
	}
		
	Matrix<float> * X=NULL;
		
	// with initialization
	if(X0!=NULL)
	{
		if(X0->rows()!=D->rows() || X0->columns()!=dim)
		{
			printf("Input initialization to MDS has invalid dimension.\n");
			exit(1);
		}
		X=X0->copy();
	}
	// without initialization
	else
	{
		X=new Matrix<float>(D->rows(),dim,"rand");
		float D_mean=D->mean(); // mean value of distance matrix
		X->addNumberSelf(-0.5); // move to the center
		X->multiplyNumberSelf(0.1*D_mean/(1.0/3.0*sqrt((float)dim))); // before this step, mean distance is 1/3*sqrt(d)
	}
		
	float lr=0.05; // learning rate
	float r=2; // metric
	int n=D->rows(); // number of vectors
		
		
	Matrix<float> * dh=new Matrix<float>(n,n,0.0);
	Matrix<float> * pmat=new Matrix<float>(n,dim);
	Matrix<float> * dhdum=new Matrix<float>(n,1);
	Matrix<float> * dhmat=new Matrix<float>(n-1,dim,0);
		
	Matrix<int> * RP=new Matrix<int>(n,iter,"randperm"); // the matrix for random permutation numbers
	int i,j;
	float temp;
	int m;
		
	printf("MDS iteration:"); 
	for(int it=0;it<iter;it++) // iterations
	{
		if(it%10==0) printf("\n");
		printf("%3d  ",it+1); 
		for(int rp=0;rp<n;rp++) // work on each vector in a randomly permuted order
		{
			m=RP->get(rp,it)-1;
				
			for(i=0;i<n;i++)
			{
				for(j=0;j<dim;j++)
				{
					pmat->set(i,j,  X->get(m,j)-X->get(i,j)  );
				}
			}
				
			for(i=0;i<n;i++)
			{
				temp=0;
				for(j=0;j<dim;j++)
				{
					temp+= pow(fabs(pmat->get(i,j)), r);
				}
				dhdum->set(i,0,  pow(temp,1/r)  );
			}

			for(i=0;i<n;i++)
			{
				if(i==m) continue;
					
				dh->set(m,i,  dhdum->get(i,0)  );
				dh->set(i,m,  dhdum->get(i,0)  );
			}

			for(i=0;i<n-1;i++)
			{
				int ii=i;
				if(i>=m) ii=i+1;
				temp=lr * ( dhdum->get(ii,0)-D->get(ii,m) ) * pow( dhdum->get(ii,0), 1-r );
				for(j=0;j<dim;j++)
				{
					dhmat->set(i,j,  temp  );
				}
			}
				
			for(i=0;i<n-1;i++)
			{
				int ii=i;
				if(i>=m) ii=i+1;
				for(j=0;j<dim;j++)
				{
					temp=X->get(ii,j);
					temp+= dhmat->get(i,j) * pow(fabs( pmat->get(ii,j) ),r-1) * sign<float>(pmat->get(ii,j));
						
					X->set(ii,j,temp);
				}
			}
		}
	}
		
	printf("\n");
		
	delete dh;
	delete pmat;
	delete dhdum;
	delete dhmat;
	delete RP;
		
	return X;
}
	
// Multidimensional scaling (MDS) with SMACOF
// This code re-implements Michael Bronstein's SMACOF in his Matlab Toolbox for Surface Comparison and Analysis
// The Matlab SMACOF can be downloaded at http://tosca.cs.technion.ac.il/
Matrix<float> * MDS_SMACOF(Matrix<float> * D, Matrix<float> * X0, int dim, int iter)
{
	if(D->rows()!=D->columns())
	{
		printf("Input distance matrix to MDS is not square.\n");
		exit(1);
	}
	if(dim<1)
	{
		printf("Invalid dimension for MDS.\n");
		exit(1);
	}
	if(iter<1)
	{
		printf("Invalid number of iterations for MDS.\n");
		exit(1);
	}
		
	Matrix<float> * X=NULL;
		
	// with initialization
	if(X0!=NULL)
	{
		if(X0->rows()!=D->rows() || X0->columns()!=dim)
		{
			printf("Input initialization to MDS has invalid dimension.\n");
			exit(1);
		}
		X=X0->copy();
	}
	// without initialization
	else
	{
		X=new Matrix<float>(D->rows(),dim,"rand");
		float D_mean=D->mean(); // mean value of distance matrix
		X->addNumberSelf(-0.5); // move to the center
		X->multiplyNumberSelf(0.1*D_mean/(1.0/3.0*sqrt((float)dim))); // before this step, mean distance is 1/3*sqrt(d)
	}
		
		
	Matrix<float> * Z=X->copy();
	Matrix<float> * D_=new Matrix<float>(D->rows(),D->columns());
	Matrix<float> * B=new Matrix<float>(D->rows(),D->columns());
	int i,j,k;
	float temp;
		
	EuclideanDistanceMatrix(X,D_);

	printf("MDS iteration:"); 
	for(int it=0;it<iter;it++) // iterations
	{
		if(it%10==0) printf("\n");
		printf("%3d  ",it+1); 

		// B = calc_B(D_,D);
		for(i=0;i<D->rows();i++)
		{
			for(j=0;j<D->columns();j++)
			{
				if(i==j || fabs(D_->get(i,j))<EPSILON)
				{
					B->set(i,j,0.0);
				}
				else
				{
					B->set(i,j, -D->get(i,j)/D_->get(i,j) );
				}
			}
		}

		for(j=0;j<D->columns();j++)
		{
			temp=0;
			for(i=0;i<D->rows();i++)
			{
				temp+=B->get(i,j);
			}
			B->set(j,j,-temp);
		}

    	// X = B*Z/size(D,1);
    	for(i=0;i<X->rows();i++)
    	{
    		for(j=0;j<X->columns();j++)
    		{
    			temp=0;
    			for(k=0;k<B->columns();k++)
    			{
    				temp+= ( B->get(i,k)*Z->get(k,j));
    			}
    			X->set(i,j,temp/(float)D->rows());
    		}
    	}
    		
    	// D_ = calc_D (X);
    	EuclideanDistanceMatrix(X,D_);
	
    	// Z = X;
		ElementCopy(X,Z);
	}
    	
	printf("\n");
		
	delete Z;
	delete D_;
	delete B;
		
	return X;
}