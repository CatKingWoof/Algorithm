#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <vector>
using namespace std;
class path_node{
public:
	int n;
	path_node *link;
	path_node(int n,path_node *path):n(n),link(path){};
};
class node{
	public:
	int n,c,step;
	bool *visited_node;
	path_node *path;
	node(int n,int c,int s,path_node *p,bool *v):n(n),c(c),step(s),visited_node(v){
		path=new path_node(n,p);
		visited_node[n]=1;
	};
};

void Quicksort(node **list,int left,int right);
int main(int argc,char *argv[]){
	clock_t start,stop;
    clock_t check_time[2];
	start = clock();
	ifstream ifs;
    ofstream ofs;
    ifs.open(argv[1]);
	ofs.open(argv[2]);
	int n,m,x1,x2,x3,num=0,cost;
	ifs>>n>>m;
	int adj_matrix[n][n];
	int t;
	node *new_node;
	//construct adjacent matrix
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			adj_matrix[i][j]=-1;
		}
		
	}
	
	for(int i=0;i<m;i++)
	{
		ifs>>x1>>x2>>x3;
		adj_matrix[x1][x2]=x3;
		adj_matrix[x2][x1]=x3;
	}
	
	/*for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cout<<adj_matrix[i][j]<<" ";
		}
		cout<<endl;
		
	}*/
	cout<<endl;
	//vertex stack
	int top=0;
	node *stack[500000];
	bool *visited;
	int step,min_answer=99999999;
	bool finish=0,find;
	bool has_cycle=0;
	//find the adjacent point
	
	vector <node*> node_list;
	visited=new bool[n];
	for(int i=0;i<n;i++)
	{
		visited[i]=0;
	}
	visited[0]=1;
	node *source,*answer,*finish_node;
	path_node *answer_path;
	source=new node(0,0,0,NULL,visited);
	for(int i=0;i<n;i++)
	{
		t=adj_matrix[0][i];
		step=source->step+1;
		if(t>0)
		{
			t=t+source->c;
			visited=new bool[n];
			for(int i=0;i<n;i++)
			{
				visited[i]=source->visited_node[i];
			}
			visited[i]=1;
			new_node=new node(i,t,step,source->path,visited);
			node_list.push_back(new_node);
		}	
	}
	
	//sort the new node
	node **l=&node_list[0];
    Quicksort(l,0,node_list.size()-1);
	/*for(int i=0;i<node_list.size();i++)
	{
		cout<<node_list[i]->n<<" ";
	}
	cout<<endl;*/
	//push to stack by priority
	for(int i=node_list.size()-1;i>=0;i--)
	{
		if(top<500000)
		{
			top++;
			stack[top]=node_list[i];
		}
	}
	
	while(top>0)
	{
		finish=0;
		while(!finish&&top>0)
		{
			//cout<<top;
			//cout<<"pop:"<<stack[top]->n<<" ";
			/*for(int i=0;i<n;i++)
			cout<<stack[top]->visited_node[i];
			cout<<" ";*/
			source=stack[top];
			top--;
			node_list.clear();
			step=source->step+1;
			find=0;
			for(int i=0;i<n;i++)
			{
				t=adj_matrix[source->n][i];
				if(t>0&&t<min_answer&&!source->visited_node[i])
				{
					t=t+source->c;
					visited=new bool[n];
					for(int i=0;i<n;i++)
					{
						visited[i]=source->visited_node[i];
					}
					visited[i]=1;
					new_node=new node(i,t,step,source->path,visited);
					node_list.push_back(new_node);
					find=1;
				}	
			}
			//sort the new node
			if(find)
			{
				l=&node_list[0];
				Quicksort(l,0,node_list.size()-1);
				/*for(int i=0;i<node_list.size();i++)
				{
					cout<<node_list[i]->n<<" ";
				}
				cout<<"step "<<step;*/
			}
			else
			{
				//cout<<endl;
				continue;
			}
			//cout<<"stack"<<stack[1]->n<<" "<<stack[1]->c;
			//cout<<endl;
			//check if finish
			if(step==n-1&&find)
			{
				finish_node=node_list[0];
				if(adj_matrix[finish_node->n][0]>0)
				{
					finish_node->c+=adj_matrix[finish_node->n][0];
					if(finish_node->c<min_answer)
					{
						finish=1;
						has_cycle=1;
						min_answer=finish_node->c;
						answer=finish_node;
						break;
					}
				}
				continue;
			}
			//push to stack by priority
			if(!finish)
			{
				for(int i=node_list.size()-1;i>=0;i--)
				{
					if(top<500000)
					{
						top++;	
						stack[top]=node_list[i];
					}
					else
					{
						//cout<<"overflow!";
						break;
					}
				}
			}
			stop = clock();
            if((double(stop - start) / CLOCKS_PER_SEC)>58)  break ;
		}
		stop = clock();
        if((double(stop - start) / CLOCKS_PER_SEC)>58)  break ;
	}
	if(has_cycle)
	{
		ofs<<"Yes"<<endl;
		ofs<<"Path:";
		answer_path=answer->path;
		while(answer_path)
		{
			ofs<<" "<<answer_path->n;
			answer_path=answer_path->link;
		}
		ofs<<" "<<answer->n<<endl;
		ofs<<"Cost: "<<answer->c;
	}
	else
	{
		ofs<<"No";
	}

	//cout<<double(stop - start) / CLOCKS_PER_SEC;
	return 0;
}


void Quicksort(node **list,int left,int right)
{
	
    if(left<right){
        int i=left;
        int j=right+1;
        int pivot=list[left]->c;
        do{
            do{++i;}while(i<right&&list[i]->c<pivot);
            do{--j;}while(list[j]->c>pivot);
            if(i<j) 
			{
				node* t;
				t=list[i];
				list[i]=list[j];
				list[j]=t;
				
			}
        }while(i<j);
        if(left!=j)
		{
			node* t;
			t=list[left];
			list[left]=list[j];
			list[j]=t;
		}
        if(j-1>left)
        Quicksort(list,left,j-1);
        if(j+1<right)
        Quicksort(list,j+1,right);
    }
}