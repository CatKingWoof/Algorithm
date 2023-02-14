#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include<math.h>
using namespace std;
class Listnode{
public:
	bool d;
	Listnode *link;
	Listnode(bool b):d(b),link(NULL){}
};

long long r_best[1000001];
long long max_r[1000001];
Listnode *r_dir[1000001];
int main(int argc,char *argv[]) {
	ifstream ifs;
    ofstream ofs;
    string s;
	int A,B,N;
	long long ans;
	bool *finish=0;
	
    ifs.open(argv[1]);
    if (!ifs.is_open()) {
        cout << "Failed to open file.\n";
    } else {
		ifs>>N;
		ifs>>A;
		ifs>>B;
		
		int R[N+1];
		R[0]=0;
        for(int i=0;i<N;i++)
		{
			ifs>>R[i+1];
        }
		
		
		
		
		
		r_best[N]=-R[N];
		//max_r[N]=-R[N];
		
		r_dir[N]=NULL;
		Listnode *current,*last;
		long long f,x;
		int new_n;
		
		
		for(int i=N-1;i>=0;i--)
		{
			f=0;
			last=NULL;
			new_n=N;
			//compare worst case
			/*for(int j=i+1;j<N-1;j++)
			{
				x=(j-i+1);
				x=A-x*x*B;
				if((x+max_r[j+2]<r_best[j+1])&&x<0)
				{
					new_n=j;
					f=r_best[j+1];
					current=new Listnode(0);
					current->link=r_dir[j+1];
					last=current;
					break;
				}
			}*/
			for(int j=i+1;j<N-1;j++)
			{
				x=j-i;
				if(R[j]<x*x*B-A)
				{
					new_n=j;
					f=r_best[j+1];
					current=new Listnode(0);
					current->link=r_dir[j+1];
					last=current;
					break;
				}
			}
			
			for(int j=new_n;j>i;j--)
			{
				long long f1=r_best[j];
				//f+=A-pow(j-i,2)*B;
				x=j-i;
				f+=A-(x)*(x)*B;
				if(f<f1)
				{
					f=f1;
					
					
					
					current=new Listnode(0);
					current->link=r_dir[j];
					last=current;
				}
				else
				{
					
					
					current=new Listnode(1);
					current->link=last;
					last=current;
				}
				
		
			}
			r_best[i]=f-R[i];
			/*if(r_best[i]>max_r[i+1])
			{
				max_r[i]=r_best[i];
			}
			else
			{
				max_r[i]=max_r[i+1];
			}*/
			
			r_dir[i]=last;
		}
		
		ofs.open(argv[2]);
		ofs<<r_best[0]<<endl;
		
		for(Listnode* ptr=r_dir[0];ptr;ptr=ptr->link)
		{
			ofs<<ptr->d;
			if(ptr->link)
			{ofs<<" ";}
		}
		
		
    
	
	
	
	
	
	}
    ifs.close();
    ofs.close();
  
    return 0;
}


