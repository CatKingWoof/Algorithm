#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <cstdlib>
#include <string>
#include <math.h>
using namespace std;
class node{
public:
	int node_number;
	int x,y;
	int set;
	node *link;
	node():link(NULL){};
};

class Set{
public:
	node *first_node,*last_node;
	bool visited;
	int predecessor_node,p_connect;
	int set_number;
	int key,position;
	Set():visited(0),predecessor_node(-1),key(100000000),first_node(NULL),last_node(NULL){};
	bool find_distance(Set *visited_set);
};

class BinaryHeap{
public:
		vector<Set*> heap;
		BinaryHeap(){heap.resize(1);};
		void swap(int p1,int p2);
		void MinHeapify(int position,int length);
		void DecreaseKey(int position);
		Set* ExtractMin();
		bool IsEmpty(){return (heap.size()<=1);};
		void BuildHeap();

};

void BinaryHeap::swap(int p1,int p2){
	Set *temp=this->heap[p1];
	heap[p1]=heap[p2];
	heap[p1]->position=p1;
	heap[p2]=temp;
	heap[p2]->position=p2;
}

void BinaryHeap::MinHeapify(int position,int length){
	int left=2*position,right=2*position+1;
	int smallest=position;
	if(left<length&&heap[left]->key<heap[position]->key)
		smallest=left;
	if(right < length && heap[right]->key < heap[smallest]->key)
		smallest = right;
	if(smallest!=position)
	{
		swap(smallest,position);
		MinHeapify(smallest,length);
	}
}
void BinaryHeap::DecreaseKey(int position){
	int parent=position/2;
	while(position>1&&heap[parent]->key>heap[position]->key)
	{
		swap(position,parent);
		position=parent;
		parent=parent/2;
	}
}
Set* BinaryHeap::ExtractMin(){
	Set *min=heap[1];
	heap[1]=heap[heap.size()-1];
	heap[1]->position=1;
	heap.erase(heap.begin()+heap.size()-1);
	MinHeapify(1,int(heap.size()));
	return min;
}
void BinaryHeap::BuildHeap()
{
	for(int i=int(heap.size())/2;i>=1;i--)
	{
		MinHeapify(i,int(heap.size()));
	}
}
int main(int argc,char *argv[]){
    ifstream ifs;
    ofstream ofs;
    ifs.open(argv[1]);
    ofs.open(argv[2]);
	
    if (!ifs.is_open()) {
        cout << "Failed to open file.\n";
    } else
    {
		
     int x,x2,r;
	 node *n1,*n2;
	 node* current,*current_F;
	 ifs>>r;
	 node n[r];
	 Set s[r];
	 bool change;
	 //int weight;
	 Set *source;
	 vector <int> answer;
     for(int i=0;i<r;i++)
	 {
		 n[i].node_number=i;
		 ifs>>x;
		 n[i].x=x;
		 ifs>>x;
		 n[i].y=x;
		 n[i].set=i;
		 s[i].first_node=&n[i];
		 s[i].last_node=&n[i];
		 s[i].set_number=i;
	 }
	 while(ifs>>x)
	 {
		 ifs>>x2;
		 n1=&n[x];
		 n2=&n[x2];
		 s[n2->set].visited=1;
		 current=s[n2->set].first_node;
		 s[n1->set].last_node->link=current;
		 while(current->link)
		 {
			 current->set=n1->set;
			 current=current->link;
		 }
		 current->set=n1->set;
		 s[n1->set].last_node=current;
	 }
	 
	 source=&s[n[0].set];
	 source->key=0;
	 
	 source->visited=1;
	 
	 for(int i=0;i<r;i++)
	 {
		 if(s[i].visited==0)
		 {
			 change=source->find_distance(&s[i]);
			 /*if(weight<s[i].key)
			 {
				 s[i].key=weight;
				 s[i].predecessor_set=source->set_number;
			 }*/
		 }
	 }
	 
	 BinaryHeap min_heap;
	 int p_n=1,min_cost=0,cost;
	 
	 for(int i=0;i<r;i++)
	 {
		if(s[i].visited==0)
		{
			min_heap.heap.push_back(&s[i]);
			s[i].position=p_n;
			p_n+=1;
		}			
	 }
	 /*for(int i=1;i<min_heap.heap.size();i++)
	 {
		 cout<<min_heap.heap[i]->set_number<<" "<<min_heap.heap[i]->key<<endl;
	 }
	 cout<<endl;*/
	 min_heap.BuildHeap();
	 /*for(int i=1;i<min_heap.heap.size();i++)
	 {
		 cout<<min_heap.heap[i]->set_number<<" "<<min_heap.heap[i]->key<<endl;
	 }
	 cout<<endl;*/
	 
	 while(min_heap.heap.size()>1)
	 {
		 source=min_heap.ExtractMin();
		 source->visited=1;
		 answer.push_back(source->predecessor_node);
		 answer.push_back(source->p_connect);
		 cost=source->key;
		 min_cost+=cost;
		 for(int i=0;i<r;i++)
		 {
			 if(s[i].visited==0)
			 {
				change=source->find_distance(&s[i]);
				//cout<<"a";
				if(change)
				{
					//cout<<"b";
					min_heap.DecreaseKey(s[i].position);
				}
			 }
		 }
		 /*for(int i=1;i<min_heap.heap.size();i++)
		 {
			 cout<<min_heap.heap[i]->set_number<<" "<<min_heap.heap[i]->key<<endl;
		 }
		 cout<<endl;*/
	 }
	 
	 ofs<<min_cost;
	 for(int i=0;i<answer.size();i=i+2)
	 {
		ofs<<endl<<answer[i]<<" "<<answer[i+1];
	 }
     
    }
    return 0;
}

bool Set::find_distance(Set *visited_set)
{
	bool change=0;
	int temp=visited_set->key,distance_x,distance_y,distance;
	node *current=this->first_node;
	node *f_current=visited_set->first_node;
	int current_x,current_y;
	while(current)
	{
		current_x=current->x;
		current_y=current->y;
		while(f_current)
		{
			distance_x=current_x-f_current->x;
			distance_y=current_y-f_current->y;
			if(distance_x<0)
			{
				distance_x=-distance_x;
			}
			if(distance_y<0)
			{
				distance_y=-distance_y;
			}
			distance=distance_x+distance_y;
			if(distance<temp)
			{
				temp=distance;
				visited_set->key=distance;
				visited_set->predecessor_node=current->node_number;
				visited_set->p_connect=f_current->node_number;
				change=1;
			}
			f_current=f_current->link;
		}
		current=current->link;
		f_current=visited_set->first_node;
	}
	return change;
}