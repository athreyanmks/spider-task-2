#include<iostream>
#include<math.h>

using namespace std;

int w,lvl=3435,count=0;
float t;
string img[64];

struct quad
{
	int val;
	quad *q[4];
};

quad *imgroot,*temp;




void createTree(quad *b,int i,int xb, int xe, int yb, int ye)
{
	
	if(i<lvl)
	{
		//cout<<b->val;
		b->val = -1;
		
		for(int j=0;j<4;++j)
		{
			b->q[j] = new quad;
			
			int mx1,mx2,my1,my2;
			
			mx1 = (xb+xe-1)/2;
			mx2 = (xb+xe+1)/2;
			
			my1 = (yb+ye-1)/2;
			my2 = (yb+ye+1)/2;
			
			if(j == 0)
			createTree(b->q[j],i+1,mx2,xe,yb,my1);
			
			else if(j == 1)
			createTree(b->q[j],i+1,xb,mx1,yb,my1);
			
			else if(j == 2)
			createTree(b->q[j],i+1,xb,mx1,my2,ye);
			
			else
			createTree(b->q[j],i+1,mx2,xe,my2,ye);
		}
	}
	else
	{
	
	
		
		//cout<<b->val;
		b->val = (int)img[yb][xb] - 48;
		
		//cout<<b->val<<'\n';
		
		count++;
	}
}

float branchCount(quad *b, int i)
{
	float total = 0;
	
	for(int j=0;j<4;++j)
	{
		if(b->q[j]->val != -1)
		{
			total+=b->q[j]->val;
		}
		
		else if(b->q[j]->val == -1)
		{
			total+=branchCount(b->q[j],i+1);
		}
	}
	
	//cout<<total/4<<'\n';
	return total/4;
}

void compressTree(quad *b,int i)
{
	float total =0 ;
	int validcount =0;
	int j;

	if(i<lvl)
	{
		for(j=0;j<4;++j)
		{
			compressTree(b->q[j],i+1);
		}
	}

	for(j=0;j<4;++j)
	{
		if(b->q[j]->val != -1)
		{
			total+=b->q[j]->val;
			
		}
		else
		{
			total+=branchCount(b->q[j],i+1);
		}
		
		//cout<<b->q[j]->val;
	}
	//cout<<'\n';
	
/*	for(j=0;j<4;++j)
	{
		
		cout<<b->q[j]->val;
	}
	cout<<'\t'<<total<<'\t'<<i<<'\n';*/
	

		if(total/4>=t/100)
	{
		for(int j=0;j<4;++j)
		{
			b->q[j]->val = 1;
		}

		b->val = 1;

	}

	else if(1-total/4>=t/100)
	{
		for(int j=0;j<4;++j)
		{
			b->q[j]->val = 0;
		}
		b->val = 0;

	}
	

	
	/*for(j=0;j<4;++j)
	{
		
		cout<<b->q[j]->val;
	}
	cout<<'\n';*/
}

void fixTree(quad *b, int i)
{
	if(i<lvl)
	{
		if(b->val != -1)
		{
			for(int j=0;j<4;++j)
			{
				b->q[j]->val = b->val;
				fixTree(b->q[j],i+1);	
			}
			
		}
		
		else
		{
			for(int j=0;j<4;++j)
			{
			
				fixTree(b->q[j],i+1);	
			}
		}
		
		
	}
}

void retrieveTree(quad *b,int i,int xb, int xe, int yb, int ye)
{
	
	if(i<lvl)
	{
		//cout<<b->val;
		//b->val = -1;
		
		for(int j=0;j<4;++j)
		{
			//b->q[j] = new quad;
			
			int mx1,mx2,my1,my2;
			
			mx1 = (xb+xe-1)/2;
			mx2 = (xb+xe+1)/2;
			
			my1 = (yb+ye-1)/2;
			my2 = (yb+ye+1)/2;
			
			if(j == 0)
			retrieveTree(b->q[j],i+1,mx2,xe,yb,my1);
			
			else if(j == 1)
			retrieveTree(b->q[j],i+1,xb,mx1,yb,my1);
			
			else if(j == 2)
			retrieveTree(b->q[j],i+1,xb,mx1,my2,ye);
			
			else
			retrieveTree(b->q[j],i+1,mx2,xe,my2,ye);
		}
	}
	else
	{
	
	
		
		//cout<<b->val<<'\n';
		img[yb][xb] = (char)(b->val + 48);
		
		//cout<<b->val<<'\n';
		
		count++;
	}
}


int main()
{
	int j=0;

	cin>>w;
	cin>>t;

	while(j!=lvl)
	{
		++j;
		if(w == pow(2,j))
		{
			lvl = j;
		}
	}
	//cout<<lvl;
	for(int i=0;i<w;++i)
	{
		cin>>img[i];
	}
	
	imgroot = new quad;

	//cout<<"flag 1";
	createTree(imgroot,0,0,w,0,w);

	//cout<<"flag 2";
	compressTree(imgroot,1);
	
	fixTree(imgroot,0);

	//cout<<"flag 3";
	
	cout<<'\n'<<'\n';
	count = 0;
	retrieveTree(imgroot,0,0,w,0,w);

	for(int i=0;i<w;++i)
	{
		//cout<<"flag"<<i+4;
		cout<<img[i]<<'\n';
	}
return 0;
}
