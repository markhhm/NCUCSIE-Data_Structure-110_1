#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;

struct matrix{
	long long int row;
	long long int col;
	long long int value;
};

long long int numar,numac;
long long int numbr,numbc;
vector<matrix> transpose(vector<matrix>);
void printmatrix(vector<matrix>);
vector<matrix> mult(vector<matrix>,vector<matrix>);
struct matrix storesum(int sum,vector<matrix> r,int row,int column);
int compare(int a,int b);

int main()
{
	//建立稀疏矩陣a
	vector<matrix> a;
	cin>>numar>>numac;
	matrix tmpa1;
	tmpa1.row = numar;
	tmpa1.col = numac;
	a.push_back(tmpa1);
	long long int ia,ja,ta=0;
	for(ia=0;ia<numar;ia++)
	{
		for(ja=0;ja<numac;ja++)
		{
			long long int va;
			matrix tmpa2;
			cin>>va;
			if(va!=0)
			{
				tmpa2.row = ia;
				tmpa2.col = ja;
				tmpa2.value = va;
				a.push_back(tmpa2);
				ta++;
			}
		}
	}
	a[0].value = ta;
	//建立稀疏矩陣b 
	vector<matrix> b;
	cin>>numbr>>numbc;
	matrix tmpb1;
	tmpb1.row = numbr;
	tmpb1.col = numbc;
	b.push_back(tmpb1);
	long long int ib,jb,tb=0;
	for(ib=0;ib<numbr;ib++)
	{
		for(jb=0;jb<numbc;jb++)
		{
			long long int vb;
			matrix tmpb2;
			cin>>vb;
			if(vb!=0)
			{
				tmpb2.row = ib;
				tmpb2.col = jb;
				tmpb2.value = vb;
				b.push_back(tmpb2);
				tb++;
			}
		}
	}
	b[0].value = tb;
	//printmatrix(a);
	//printmatrix(b);
	//printmatrix(transpose(b));
	printmatrix(mult(a,b));
	
}

void printmatrix(vector<matrix> x)
{
	long long int i=0;
	for(; i < x.size(); i++){
        	cout << x[i].row << " " << x[i].col << " "<<x[i].value<<endl;
    }
}
vector<matrix> transpose(vector<matrix> x)
{
	struct matrix newx[x[0].value+1];
	int start_pos[x[0].value];
	int row_terms[x[0].col];
	long long int i,j;
	vector<matrix> r;
	struct matrix tmp;
/*	for(i=0;i<x[0].col;i++)
	{
		long long int amount=0;
		for(j=1;j<x.size();j++)
		{
			if(x[j].col==i)
			{
				amount++;
			}
		}
		row_terms.push_back(amount);		
	}
	for(i=0;i<row_terms.size();i++)
	{
		cout<<i<<" "<<row_terms[i]<<endl;
	}
*///從頭掃描太久了(column*element) 
	for(i=0;i<x[0].col;i++)
	{
		row_terms[i]=0;
	}

	for(i=0;i<=x[0].value;i++)
	{
		newx[i].col = 0;
		newx[i].row = 0;
		newx[i].value = 0;
	}
	
	newx[0].col = x[0].col;
	newx[0].row = x[0].row;
	newx[0].value = x[0].value;
	for(i=1;i<=x[0].value ;i++)
	{
		row_terms[x[i].col]++;
	}
	start_pos[0] = 1;
	for(i=1;i<x[0].col;i++)
	{
		start_pos[i] = start_pos[i-1]+row_terms[i-1];
	}
	for(i=1;i<=x[0].value;i++)
	{
		j = start_pos[x[i].col]++;
		newx[j].row = x[i].col;
		newx[j].col= x[i].row;
		newx[j].value = x[i].value;
	}

	for(i=0; i <= newx[0].value; i++)
	{
        r.push_back(newx[i]);
    }
 
    /*
	cout <<"After transpose "<<endl;
    for(i=0; i <= r[0].value; i++)
	{
        	cout << r[i].row << " " << r[i].col << " "<<r[i].value<<endl;
    }
	*/
    return r;
}

vector<matrix> mult(vector<matrix> a,vector<matrix> b)
{
	
	int i,j,row_begin = 1;
	int num=0;//藉由storesum的執行次數來紀錄result 有幾項
	int sum =0; 
	vector <matrix> result;
	vector<matrix> bt = transpose(b);
	struct matrix tmp;
	tmp.row = a[0].row;
	tmp.col = b[0].col;
	result.push_back(tmp);
	int row = a[1].row,column;
	for(i=1;i<=a[0].value;)
	{
		column = bt[1].row;
		for(j=1;j<=bt[0].value+1;)
		{
		
			if(a[i].row!=row)
			{
				if(sum!=0)
				{
					result.push_back(storesum(sum,result,row,column));
					
					num++;
				} 
				sum = 0;
				i = row_begin;
				for(;bt[j].row == column;j++);
				column = bt[j].row;
			}
			else if(bt[j].row!=column)
			{
				if(sum!=0)
				{
					result.push_back(storesum(sum,result,row,column));
					
					num++;
				} 
				sum = 0;
				i = row_begin;
				column = bt[j].row;
			}
			else switch(compare(a[i].col,bt[j].col))
			{
				case -1:
					i++;
					break;
				case 0:
					sum += (a[i++].value*bt[j++].value);
					break;
				case 1:
					j++;
			}	
		}
		for(;a[i].row == row;i++);
		row_begin = i;
		row = a[i].row;
	}
	result[0].value = num;
	return result;
}
int compare(int a,int b)
{
	if(a<b)
		return -1;
	else if(a==b)
		return 0;
	else if(a>b)
		return 1;
}
struct matrix storesum(int sum,vector<matrix> r,int row,int column)
{
	struct matrix tmp;
		tmp.col = column;
		tmp.row = row;
		tmp.value = sum;
	return tmp;
}