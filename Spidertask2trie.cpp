#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<string>

using namespace std;

string s[50],sr;
char stemp[100],qrstring[5][100],qrtemp[100];
int qrc[5],small=0,smallloc=4,revno=0,c[10];
struct node
{
	node *par,*a[27]={NULL};
	char val;
	int flag=0,count=0;
	
};

struct node *root;

void addString(string st,node *block, int i)
{
		if(st[i]==' ')
		{
			//cout<<"flag1";
			if(block->a[26]==NULL)
			{
				block->a[26] = new node;
				block->a[26]->val = ' ';
				block->a[26]->par = block;
			}
			//cout<<block->a[26]->val;
			addString(st,block->a[26],i+1);
		}
		
		else if(st[i] == '\0')
		{
			block->flag = 1;
			block->count++;
			
		}
		
		else
		{	//cout<<"flag2";
			int j = (int)st[i]-97;
			
			//cout<<j;
			if(block->a[j]==NULL)
			{
				//cout<<"flag1";
				block->a[j] = new node;
				//cout<<"flag2";
				block->a[j]->val = st[i];
				//cout<<"flag3";
				block->a[j]->par = block;
				//cout<<"flag4"<<'\n';
			}
			//cout<<block->a[j]->val;
			addString(st,block->a[j],i+1);
		}
		
		
}
void removeString(string st,node *block,int i)
{
	if(st[i+1]!='\0')
	{
		int j;
		if(st[i+1]==' ')
		{
			j=26;
			removeString(st,block->a[26],i+1);
		}
		
		else
		{
			j = (int)st[i]-97;
			removeString(st,block->a[j],i+1);
		}
		
		int flag = 1;
	
		for(int k=0;k<27;++k)
		{
			if(block->a[i]!=NULL)
			flag = 0;
		}
	
		if(flag == 1&&(block->flag==0||st[i+1] == '\0'))
		{
			block->par->a[j]=NULL;
			delete block;
		}
	}
	
	
}

void queryString(char st[],node *block,int i)
{
	
	//cout<<strlen(st)<<i;
	if(i<strlen(st))
	{
		int j;
		if(st[i]!=' ')
		{
			 j = (int)st[i]-97;
		}
		else 
		{
			 j =26;
		}
			//cout<<j;
			qrtemp[i]=st[i];
			//cout<<qrtemp[i];
				
		
		
		queryString(st,block->a[j],i+1);
	}
	
	else
	{
		//cout<<"flag";
		/*if(i == strlen(st))
		{
			int j = (int)st[i]-97;
			queryString(st,block->a[j],i+1);
		}*/
		//cout<<qrtemp[i];
		
		
		qrtemp[i-1]=block->val;
		
		//cout<<block->val;
		
		if(block->flag == 1)
		{
			//cout<<block->val;
			//cout<<qrtemp[4];
			//cout<<block->count;
			//cout<<small<<'\n';
			
			
			if(block->count>small)
			{
				int z,loc,y;
				//cout<<strlen(qrtemp);
				for(y=0;y<4&&qrc[y+1]<block->count;++y)
				{
					
					qrc[y]=qrc[y+1];
					//cout<<qrc[y+1]<<block->count<<'\t';
					/*for(z=0;z<=i;++z)
					{
						qrstring[y][z] = qrstring[y+1][z];
					}
				
					for(z=i;z<100;++z)
					{
						qrstring[y][z] = '\0';
					}*/
					
					strcpy(qrstring[y],qrstring[y+1]);	
				}
				
				loc = y;
				
				for(z=0;z<=i;++z)
				{
					qrstring[loc][z] = qrtemp[z];
				}
				
				for(z=i;z<100;++z)
				{
					qrstring[loc][z] = '\0';
				}
				
				//strcpy(qrstring[smallloc],qrtemp);
				
				//cout<<loc;
				//cout<<small<<smallloc;
				//puts(qrstring[loc]);
				qrc[loc] = block->count;
				
				smallloc=0; small = qrc[0];
				for(int c = 1;c<5;++c)
				{
					if(qrc[c] == 1)
					{
						
					}
					if(qrc[c]<=small)
					{
						smallloc = c;
						small = qrc[c];
					}
				}
				
			}
			
			
			
			//strcpy(qrtemp,stemp);
		}
		
			for(int k = 0;k<27;++k)
			{
				if(block->a[k] != NULL)
				queryString(st,block->a[k],i+1);
			}
			
		
	}
	
	/*if(i=0)
	{
		for(int d=0;d<5;++d)
		{
			cout<<qrstring[d];
		}
	}*/
}

int main()
{
	int n,q,i=0,j,k,c=0;
	
	
	std::cin>>n;
	
	root = new node;
	
	while(c<=n)
	{
		//cout<<"flag1";
		
		//cout<<c;
		getline(cin,sr);
		
		//cout<<sr;
		//cout<<"flag2";
		addString(sr,root,0);
		//cout<<"flag3";
		
		++c;
	}
	c=0;
	
	
	std::cin>>q;
	
	for(i=0;i<=q;++i)
	{
		getline(cin,s[i]);
		//cout<<s[i];
		
	}
	
	for(i=0;i<=q;++i)
	{
		//cout<<i;
		if(s[i][0] == 'a')
		{
			for(j=4;j<s[i].length();++j)
			{
				stemp[j-4] = s[i][j];
			}
			cout<<stemp;
			addString(stemp,root,0);
		}
		
		else if(s[i][0] == 'r' && s[i][2] == 'm')
		{
			for(j=7;j<s[i].length();++j)
			{
				stemp[j-7] = s[i][j];
			}
			cout<<stemp;
			removeString(stemp,root,0);
		}
		
		else if(s[i][0] == 'q')
		{
			//cout<<"flag";
			for(j=6;j<s[i].length();++j)
			{
				//cout<<"flag"<<j;
				stemp[j-6] = s[i][j];
				//cout<<stemp[j-6];
			}
			//cout<<"flag";
			//puts(stemp);
			queryString(stemp,root,0);
			
			for(j=0;j<100;++j)
			{
				stemp[j] = '\0';
			}
			
			for(j=4;j>=0;--j)
			{
				//cout<<"flag";
				//for(int z=0;z<strlen(qrstring[j]);++z)
				cout<<qrstring[j];
				
				cout<<'\n';
			}
			
			small = 0; smallloc=0;
			for(j=0;j<100;++j)
			{
				qrtemp[j] = '\0';
				for(k=0;k<5;++k)
				{
					qrstring[k][j] = '\0';
					qrc[k] = 0;
				}
			}
			//cout<<"flag";
		}
		
		if(s[i][0] == 'r' && s[i][2] == 'v')
		{
			for(j=3;j<s[i].length();++j)
			{
				stemp[j-4] = s[i][j];
			}
			
			for(j = strlen(stemp); j>=0; --j)
			{
				revno+=((int)stemp[j]-48)*pow(10,strlen(stemp)-1-j);
			}
			
			j=0;
			k=0;
			while(j<i)
			{
				if(s[i][0] == 'a' || (s[i][0] == 'r' && s[i][2] == 'm'))
				{
					k++;
					
					if(k>revno)
					{
						if(s[i][0] == 'a')
						{
							for(j=4;j<s[i].length();++j)
							{
								stemp[j-4] = s[i][j];
							}
			
							removeString(stemp,root,0);
						}
		
						else if(s[i][0] == 'r' && s[i][2] == 'm')
						{
							for(j=7;j<s[i].length();++j)
							{
								stemp[j-7] = s[i][j];
							}
			
							addString(stemp,root,0);
						}
					}
				}
			}
		}
	}
	
	return 0;
}


