#include<iostream>
#include<string>
#include<string.h>
#include<stack>
#include<queue>
#include<fstream>
#include<time.h>
#include<math.h>
using namespace std;
/*
caltype:
		case 1:
				NAND;
		case 2:
				NOR;
		case 3:
				NOT;
		else:
				depend on string Gatename;
*/
void topofunc();
int findhashIndex(string);
void p_nodeinfo();
int typesize;
int tempk;
int tablesize;
void pros_mod(string);
void run(string,string,int);
void parse(string);
int checkt(string);
bool declaretype(string);
void getpath();
bool check(string);
void DFS(string,int);
int findnodeIndex(string);
void constructhash();
int calhash(string);
int calwirehash(string);
void getNode_linklist();
void verifyTruePath();
void exampath(string *,int);
int globalcount;
void finalgeneration();
struct setNode
{
	int time;
	bool output;
	string G_name;
	setNode *next;
	setNode *down;
};
struct inoutInfo
{
	string *info;
	string type;
	int size;
};
struct pros_MOD
{
	int caltype;
	string Gatename;
};
struct InVal
{
	string InNam;
	bool Inbol;
	InVal *next;
	InVal *down;
};
struct Node
{
	int color;
	int use;
	int a_arrival;
	int b_arrival;
	Node *headlink;
	Node *next;
	int index;
	bool bol_input[2];
	string Gate;
	string outWire;
	string input[2];
	string G_name;
	int gatetype;
	int finishedTime;
	bool output;
	bool True_a;
	bool True_b;	
	InVal *down;
};
struct path
{
	string *pth;
	string *realinput;
	path *next;
	path *tail;
	int size;
	bool *inputvec;
};
struct ATPG_node
{
	string endGatename;
	int size;
	string *inputvector;
	string *AT_topoOrder;
	ATPG_node *next;
	int toposize;
};
int truepathcounter;
setNode **hashSet;
ATPG_node *ATPG_head;
int countpath;
inoutInfo Info[3];
int NodeSize;
pros_MOD *posmod;
string *topoOrder;
stack <string>DFStack;
stack <string>topoStack;
int test;
int k11;
void construcwirehash();
void PrintPath(string *,int size);
void ExamTruePath();
void FinishTable();
void delcontrain(int);
void PrintPathvec(string *,int ,bool *);
void findrealinput();
void F_Tpath();
bool checkwinput(string a);
Node *findNode1(string a);
Node *findNode(string);
Node *findwire(string);
Node *ptrtemp;
Node **wireNode;
Node **hashNode;
Node **Graphlink;
Node *Gatenode;
Node *conGate;
path *pthead;
path *Thead;
path *truePath;
setNode *setTemp;
setNode *findSet(string);
void F_endpoint();
void F_inputVector();
int findTopoIndex(string);
void True_cal();
bool onpath(path *,string);
void consSet();
bool T_path(int,bool,int,bool,int,int &,bool &,bool);
void expressVector(string);
void recDFS(setNode *,setNode *);
stack <string> T_gate;
stack <bool> T_bol;
stack <string> Tb_gate;
stack <bool> Tb_bol;
int deltruecounter;
int main(int argc, char** argv)
{
	run(argv[1],argv[2],atoi(argv[3]));
	cout<<"Case: "<<argv[2]<<endl;
	return 0;
}
void run(string a,string b,int constrain)
{
	deltruecounter = 0;
	truepathcounter = 0;
	ptrtemp=new Node;
	ATPG_head = new ATPG_node;
	ATPG_head->next = NULL;
	time_t nStart = time(NULL);
	pros_mod(a);
	parse(b);
	//p_nodeinfo();
	constructhash();
	construcwirehash();
	//p_nodeinfo();
	getNode_linklist();
	//p_nodeinfo();
	getpath();
	topofunc();
	delcontrain(constrain);
	int k=0;
	F_endpoint();
	F_Tpath();
	consSet();
	True_cal();
	time_t end = time(NULL);
	cout<<endl;
	expressVector("U186");
	cout<<endl<<endl<<"Time: "<<end-nStart<<"(seconds)"<<"	Find #path:"<<test<<endl;
	cout<<"After del constrain #path:"<<globalcount<<endl;
	cout<<"After del non true path:"<<deltruecounter<<endl;
	//p_nodeinfo();
	//findrealinput();
	//ExamTruePath();
	/*
	path *outemp = Thead;
	outemp=outemp->next;
	while(outemp!=NULL)
	{
		PrintPathvec(outemp->pth,outemp->size,outemp->inputvec);
		outemp=outemp->next;
		k++;
	}
	cout<<"Find #True path:"<<k<<endl;
	
	//p_nodeinfo();*/
	
}
void finalgeneration()
{
	path *phead = new path;
	phead = pthead;
	phead = phead->next;
	while(phead!=NULL)
	{

		phead = phead -> next;
	}
}
void expressVector(string gatename)
{
	setNode *t = findSet(gatename);
	setNode *tempdown;
	
	if(t!=NULL)
	{
		t = t->down;
		if(t!=NULL)
			t = t->next;
		if(t==NULL)
		{
			deltruecounter++;
		}
		while(t!=NULL)
		{
			tempdown = t->down;
			//recDFS(tempdown->next,(tempdown->next)->next);

			t = t->next;
		}
	}
	
}
void recDFS(setNode *ina,setNode *inb)
{
	bool change = true;
	setNode *right = new setNode;
	right = ina;
	setNode *left = new setNode;
	left = inb;
	right = right->down;
	left = left->down;
	right = right->next;
	left = left->next;
	if(right!=NULL&&right->down==NULL&&right->next==NULL)
	{
		change = false;
		//cout<<right->G_name<<"	"<<endl;
		T_gate.push(right->G_name);
		T_bol.push(right->output);
	}
	if(left!=NULL&&left->down==NULL&&left->next==NULL)
	{
		change = false;
		//cout<<left->G_name<<"	"<<endl;
		T_gate.push(left->G_name);
		T_bol.push(left->output);
	}
	while(right)
	{
		if(right->next!=NULL&&right->down!=NULL)
			recDFS(right,right->next);
		if(right!=NULL)
			right = right->down;
	}
	while(left)
	{
		if(left->next!=NULL&&left->down!=NULL)
			recDFS(left,left->next);
		if(left!=NULL)
			left = left->down;
	}
	if(change == true)
	{
		string tempa[10000];
		bool tempb[10000];
		int tempcounter = 0;
		cout<<"Paht: "<<truepathcounter++<<endl;
		Tb_gate = T_gate;
		Tb_bol = T_bol;
		while(!Tb_gate.empty())
		{
			string _A = Tb_gate.top();
			bool _B = Tb_bol.top();
			bool changetemp = false;
			int judgecounter = 0;
			while(judgecounter<tempcounter)
			{
				if(tempa[judgecounter]==_A)
				{
					changetemp=true;
					break;
				}
				judgecounter++;
			}
			if(!changetemp)
			{
				cout<<"Input:"<<Tb_gate.top();
				cout<<"	bool: "<<Tb_bol.top()<<endl;
				tempa[tempcounter] = Tb_gate.top();
				tempb[tempcounter] = Tb_bol.top();
				tempcounter++;
			}
			Tb_gate.pop();
			Tb_bol.pop();
		}
		T_bol.pop();
		T_gate.pop();
		cout<<"################################################################"<<endl;
	}
	
	
	
	//cout<<"input:"<<left->G_name<<"	bol:"<<left->output<<endl;
	
}
bool onpath(path *pthe,string gname) 
{
	for(int i=0;i<pthe->size;i++)
	{
		if(pthe->pth[i]==gname)
		{
			return true;
		}
	}
	return false;
}
bool T_path(int A_Time,bool com_a,int B_Time,bool com_b,int ctype,int &caltime,bool &bol_out,bool comfrom)
{	
	bool ta = true;
	bool tb = true;
	int aorder = 0;
	if(ctype==3)
	{
		bol_out=!com_a;
	}
	if(ctype==2)
	{
		bol_out=!(com_a|com_b);
	}
	if(ctype==1)
	{
		bol_out=!(com_a&com_b);
	}
	if(A_Time<B_Time) //a faster than b
		aorder=1;
	if(A_Time>B_Time)
		aorder=2;
		
	switch(ctype)
	{
		case 1:
			switch(aorder)
			{
				case 0:
					if(!com_a&&com_b)
						tb=false;
					if(com_a&&!com_b)
						ta=false;
				break;
				case 1:
					if((com_a&&com_b)||(com_a&&!com_b))
						ta=false;
					if((!com_a&&com_b)||(!com_a&&!com_b))
						tb=false;
				break;
				case 2:
					if((com_a&&!com_b)||(!com_a&&!com_b))
						ta=false;
					if((com_a&&com_b)||(!com_a&&com_b))
						tb=false;
				break;
			}
		break;
		case 2:
			switch(aorder)
			{
				case 0:
					if(!com_a&&com_b)
						ta=false;
					if(com_a&&!com_b)
						tb=false;
				break;
				case 1:
					if((!com_a&&com_b)||(!com_a&&!com_b))
						ta=false;
					if((com_a&&com_b)||(com_a&&!com_b))
						tb=false;
				break;
				case 2:
					if((com_a&&com_b)||(!com_a&&com_b))
						ta=false;
					if((com_a&&!com_b)||(!com_a&&!com_b))
						tb=false;
				break;
			}
		break;
	}
	if(ta&&tb)
	{
		caltime = A_Time>B_Time?A_Time:B_Time;
		caltime+=1;
	}
	else if(!ta)
	{
		caltime = B_Time+1;
	}
	else
	{
		caltime = A_Time+1;
	}
	if((!comfrom&&ta)||(comfrom&&tb))
	{
		return true;
	}
	//cout<<endl<<"A_T:	"<<A_Time<<"	B_T:"<<B_Time<<"	A_bol:"<<com_a<<"	B_bol:"<<com_b<<"	FALSE"<<endl;
	return false;
}
void True_cal()
{
	int count=0;
	
	setNode *inputs = new setNode;
	for(int i=NodeSize-Info[0].size;i<NodeSize;i++)
	{
		setNode *no = new setNode;
		string gname = Gatenode[i].G_name;
		inputs = findSet(gname);
		inputs->down=no;
		inputs = no;
		no->G_name=gname;
		setNode *ina = new setNode;
		setNode *inb = new setNode;
		ina->G_name=gname;
		inb->G_name=gname;
		ina->time=0;
		ina->output=true;
		inb->time=0;
		inb->output=false;
		inputs->next=ina;
		ina->next=inb;
		inb->next=NULL;
		setNode *dum = new setNode;
		setNode *dum1 = new setNode;
		ina->down=dum;
		dum->down=NULL;
		inb->down=dum1;
		dum1->down=NULL;
		setNode *s1= new setNode;
		setNode *s2= new setNode;
		s1->G_name = gname;
		dum->next=s1;
		s1->next=NULL;
		dum1->next=s2;
		s2->G_name = gname;
		s2->next=NULL;
		s1->output=true;
		s2->output=false;
	}
	/*
	for(int i=NodeSize-Info[0].size;i<NodeSize;i++)
	{
		string gname = Gatenode[i].G_name;
		inputs = findSet(gname);
		inputs = inputs->down;
		while(inputs->next!=NULL)
		{
			inputs=inputs->next;
			setNode *bb = inputs;
			bb=bb->down;
			bb=bb->next;
			cout<<bb->output<<"	";
		}
	}*/
	

	//give input value 1227git s
	path *ptemp = new path;
	ptemp=pthead;
	ptemp=ptemp->next;
	setNode *_A = new setNode;
	setNode *_B = new setNode;
	setNode *_G = new setNode;
	
	while(ptemp!=NULL)
	{
		string terNode=ptemp->pth[ptemp->size-1]; // find terminated Node
		ATPG_node *A_temp = new ATPG_node;
		int pathcounter = 1;
		string lastNode = ptemp->pth[0];
		A_temp = ATPG_head->next;
		string *G_topo;
		int t_size;
		bool cal_bol;
		int cal_time;
		
		while(A_temp->endGatename!=terNode)//find endNode
		{
			A_temp=A_temp->next;
		}
		
		G_topo = A_temp->AT_topoOrder; //get topofunction
		t_size = A_temp->toposize; // get toposize;
		cout<<"<-------------------------------------------------------------------------------------------->"<<endl;
		//cout<<A_temp->endGatename<<endl;
		for(int i=0;i<ptemp->size;i++)
		{
			cout<<ptemp->pth[i]<<"->";
		}
		cout<<endl;
		for(int i=0;i<t_size;i++)
		{
			//cout<<G_topo[i]<<":"<<endl;
			Node *Gate_ = findNode(G_topo[i]);
			int ctype = checkt(Gate_->Gate);
			setNode *G = new setNode;
			G = findSet(G_topo[i]);			
			_A =findSet(findwire(Gate_->input[0])->G_name);
			
			if(onpath(ptemp,G_topo[i]))//gate on the eva path 若是true path才留下來
			{
				bool comfrom =false;
				if(findwire(Gate_->input[1])->G_name==lastNode)
					comfrom = true;
				if(ctype!=3)
				{
					_B = findSet(findwire(Gate_->input[1])->G_name);
					setNode *F_B = _B->down;
					F_B=F_B->next;
					_A = _A->down;
					_A = _A->next;
					setNode *Gtemp = new setNode;
					G->down = Gtemp;
					Gtemp->next=NULL;
					setNode *GTT = G->down; //0724
					while(_A!=NULL)
					{
						_B =F_B;
						while(_B!=NULL)
						{

							
							if(T_path(_A->time,_A->output,_B->time,_B->output,ctype,cal_time,cal_bol,comfrom))
							{
								T_path(_A->time,_A->output,_B->time,_B->output,ctype,cal_time,cal_bol,comfrom);
								//cout<<"time:"<<cal_time<<"	";
								//cout<<_A->output<<_B->output<<"	bool:"<<cal_bol<<"	";
								Gtemp = G->down;
								while(Gtemp!=NULL)
								{
									if(Gtemp->time==cal_time&&Gtemp->output==cal_bol)
										break;
									Gtemp=Gtemp->next;
								}
								setNode *Gntemp = new setNode;
								setNode *setTemp = new setNode;
								setNode *setA = new setNode;
								setNode *setB = new setNode;
								if(Gtemp==NULL)
								{
									setNode *k = G->down;
									Gntemp->next = k->next;
									Gntemp->time = cal_time;
									Gntemp->output = cal_bol;
									k->next = Gntemp;
									Gntemp->down = setTemp;
									setA->down = _A->down;
									setB->down = _B->down;
									setTemp->next=setA;
									setA->next=setB;
									setB->next=NULL;
								}
								else if(Gtemp!=NULL)
								{
									setTemp->down=Gtemp->down;
									Gtemp->down=setTemp;
									setA->down = _A->down;
									setB->down = _B->down;
									setTemp->next=setA;
									setA->next=setB;
									setB->next=NULL;
								}
							}
							_B = _B->next;
						}
						_A = _A->next;
					}
					/*
					setNode *k = G->down;
					k=k->next;
					while(k!=NULL)
					{
						
						cout<<"time:"<<k->time<<"	";
						cout<<"Bol:"<<k->output<<"	";
						k=k->next;
						
					}
					
					cout<<endl;
					*/

				}
				else //Not Gate always be a true path 直接繼承上一個input 0724 need to redesign
				{
					setNode *AT=_A->down;
					AT= AT->next;
					setNode *GT = G;
					setNode *dow = new setNode;
					GT->down = dow;
					dow->next=NULL;
					dow->down=NULL;
					GT = GT->down;
					while(AT!=NULL)
					{
						//cout<<"bool:"<<AT->output<<"	";
						setNode *top = new setNode;
						top->next = GT->next;
						GT->next = top;
						top->output=!(AT->output);
						top->time = AT->time+1;
						top->down = AT->down;
						AT=AT->next;
					}					
					//cout<<endl;
				}
				lastNode=ptemp->pth[pathcounter];
				pathcounter++;
				
			}
			else
			{
				bool comfrom =false;
				
				if(ctype!=3)
				{
					_B = findSet(findwire(Gate_->input[1])->G_name);
					setNode *F_B = _B->down;
					F_B=F_B->next;
					_A = _A->down;
					_A = _A->next;
					setNode *Gtemp = new setNode;
					G->down = Gtemp;
					Gtemp->next=NULL;
					setNode *GTT = G->down; //0724
					while(_A!=NULL)
					{
						_B =F_B;
						while(_B!=NULL)
						{
							if(true)//T_path(_A->time,_A->output,_B->time,_B->output,ctype,cal_time,cal_bol,comfrom))
							{
								T_path(_A->time,_A->output,_B->time,_B->output,ctype,cal_time,cal_bol,comfrom);
								//cout<<"time:"<<cal_time<<"	";
								//cout<<_A->output<<_B->output<<"	bool:"<<cal_bol<<"	";
								Gtemp = G->down;
								while(Gtemp!=NULL)
								{
									if(Gtemp->time==cal_time&&Gtemp->output==cal_bol)
										break;
									Gtemp=Gtemp->next;
								}
								setNode *Gntemp = new setNode;
								setNode *setTemp = new setNode;
								setNode *setA = new setNode;
								setNode *setB = new setNode;
								if(Gtemp==NULL)
								{
									setNode *k = G->down;
									Gntemp->next = k->next;
									Gntemp->time = cal_time;
									Gntemp->output = cal_bol;
									k->next = Gntemp;
									Gntemp->down = setTemp;
									setA->down = _A->down;
									setB->down = _B->down;
									setTemp->next=setA;
									setA->next=setB;
									setB->next=NULL;
								}
								else if(Gtemp!=NULL)
								{
									setTemp->down=Gtemp->down;
									Gtemp->down=setTemp;
									setA->down = _A->down;
									setB->down = _B->down;
									setTemp->next=setA;
									setA->next=setB;
									setB->next=NULL;
								}
							}
							_B = _B->next;
						}
						
						_A = _A->next;
					}
					/*
					setNode *k = G->down;
					k=k->next;
					while(k!=NULL)
					{
						
						cout<<"time:"<<k->time<<"	";
						cout<<"Bol:"<<k->output<<"	";
						k=k->next;
						
					}
					
					cout<<endl;*/
				}
				else //Not Gate always be a true path 直接繼承上一個input 0724
				{
					setNode *AT=_A->down;
					AT= AT->next;
					setNode *GT = G;
					setNode *dow = new setNode;
					GT->down = dow;
					dow->next=NULL;
					dow->down=NULL;
					GT = GT->down;
					while(AT!=NULL)
					{
						//cout<<"bool:"<<AT->output<<"	";
						setNode *top = new setNode;
						top->next = GT->next;
						GT->next = top;
						top->output=!(AT->output);
						top->time = AT->time+1;
						top->down = AT->down;
						AT=AT->next;
					}					
					//cout<<endl;
				}
				
			
			}
			
		}
		//freeNode動作 1227
		expressVector(terNode);
		for(int i=0;i<NodeSize-Info[0].size;i++)
		{
			findSet(Gatenode[i].G_name)->down=NULL;
		}
		ptemp=ptemp->next;
		
		
	}
}
void F_Tpath()
{
	for(int i=NodeSize-Info[0].size;i<NodeSize;i++)
	{
		Node *temp = findwire(Gatenode[i].G_name);
		temp->finishedTime=0;
		temp->output=false;
		temp->a_arrival=0;
		temp->b_arrival=0;
		temp->True_a=false;
		temp->True_b=false;
		temp = NULL;
		delete temp;
	}
	path *ptemp = new path;
	ptemp=pthead;
	ptemp=ptemp->next;
	string last;
	ATPG_node *Atemp = new ATPG_node;

	while(ptemp->next!=NULL)
	{
		last = ptemp->pth[ptemp->size-1];
		Atemp = ATPG_head;
		while(Atemp->endGatename!=last)
		{
			Atemp=Atemp->next;
		}
		ptemp=ptemp->next;
	}
}
bool checkwinput(string a)
{
	bool che=false;
	Node *temp = new Node;
	temp = findwire(a);
	if(temp->Gate=="input")
		che=true;
	temp = NULL;
	delete temp;
	free(temp);
	return che;
}
void F_inputVector() //need optimize to find topoorder
{
	ATPG_node *temp = new ATPG_node;
	temp = ATPG_head;
	temp = temp->next;
	stack <string> tempStack;
	stack <string> inputstack;
	string gatename;
	Node *topInfo = new Node;
	string ai[1000];
	int tempi=0;
	Node *wtemp = new Node;
	while(temp)
	{
		string tempTopo[100000];
		int tempcounter=0;
		gatename = temp->endGatename;
		tempTopo[tempcounter] = gatename;
		tempcounter++;
		tempStack.push(gatename);
		while(!tempStack.empty())
		{
			gatename=tempStack.top();
			tempStack.pop();
			topInfo = findNode(gatename);
			if(checkt(topInfo->Gate)==3)
			{
				if(checkwinput(topInfo->input[0]))
				{
					inputstack.push(topInfo->input[0]);
					bool che=false;
					for(int i=0;i<tempcounter;i++)
					{
						if(tempTopo[i]==topInfo->G_name)
						{
							che=true;
							break;
						}
					}
					if(che==false)
					{
						tempTopo[tempcounter]=topInfo->G_name;
						tempcounter++;
					}
				}
				else
				{
					wtemp = findwire(topInfo->input[0]);
					tempStack.push(wtemp->G_name);
					bool che=false;
					for(int i=0;i<tempcounter;i++)
					{
						if(tempTopo[i]==wtemp->G_name)
						{
							che=true;
							break;
						}
					}
					if(che==false)
					{
						tempTopo[tempcounter]=wtemp->G_name;
						tempcounter++;
					}
				}
			}
			else if(checkt(topInfo->Gate)==2||checkt(topInfo->Gate)==1)
			{
				bool che=false;
					for(int i=0;i<tempcounter;i++)
					{
						if(tempTopo[i]==topInfo->G_name)
						{
							che=true;
							break;
						}
					}
					if(che==false)
					{
						tempTopo[tempcounter]=topInfo->G_name;
						tempcounter++;
					}
				if(checkwinput(topInfo->input[0]))
				{
					inputstack.push(topInfo->input[0]);
				}
				else
				{
					wtemp = findwire(topInfo->input[0]);
					tempStack.push(wtemp->G_name);
					bool che=false;
					for(int i=0;i<tempcounter;i++)
					{
						if(tempTopo[i]==wtemp->G_name)
						{
							che=true;
							break;
						}
					}
					if(che==false)
					{
						tempTopo[tempcounter]=wtemp->G_name;
						tempcounter++;
					}
				}
				if(checkwinput(topInfo->input[1]))
				{
					inputstack.push(topInfo->input[1]);
				}
				else
				{
					wtemp = findwire(topInfo->input[1]);
					tempStack.push(wtemp->G_name);
					bool che=false;
					for(int i=0;i<tempcounter;i++)
					{
						if(tempTopo[i]==wtemp->G_name)
						{
							che=true;
							break;
						}
					}
					if(che==false)
					{
						tempTopo[tempcounter]=wtemp->G_name;
						tempcounter++;
					}
				}
			}

		}
		temp->AT_topoOrder = new string[tempcounter];
		temp->toposize=tempcounter;
		for(int i=0;i<tempcounter;i++)
		{
			temp->AT_topoOrder[i]=tempTopo[i];
		}
		tempi=0;
		ai[tempi]=inputstack.top();
		inputstack.pop();
		tempi++;
		int ksize = inputstack.size();
		for(int i=0;i<ksize;i++)
		{
			bool ch=false;
			for(int j=0;j<tempi;j++)
			{
				if(ai[j]==inputstack.top())
					ch=true;
			}
			if(!ch)
			{
				ai[tempi]=inputstack.top();
				tempi++;
			}
			inputstack.pop();
		}
		temp->size = tempi;
		temp->inputvector=new string[tempi];
		for(int i=0;i<tempi;i++)
		{
			temp->inputvector[i]=ai[i];
		}
		temp=temp->next;
	}
	topInfo = NULL;
	delete topInfo;
	free(topInfo);
	temp = NULL;
	delete temp;
	free(temp);
}
setNode *findSet(string a)
{
	int temp = calhash(a);
	setTemp = hashSet[temp];
	if(setTemp->next!=NULL)
	{
		setTemp=setTemp->next;
	}
	while(setTemp!=NULL)
	{
		if(setTemp->G_name==a)
			break;
		setTemp=setTemp->next;
	}
	return setTemp;
}
void F_endpoint()
{
	path *ptemp = new path;
	ptemp = pthead;
	ptemp=ptemp->next;
	stack <string> inputstack;
	Node *temp = new Node;
	string last;
	ATPG_node *ATPG_temp = new ATPG_node;
	while(ptemp->next!=NULL)
	{
		last = ptemp->pth[ptemp->size-1];
		ATPG_temp = ATPG_head;
		ATPG_temp = ATPG_temp->next;
		bool csame = false;
		while(ATPG_temp)
		{
			if(ATPG_temp->endGatename==last)
				csame=true;
			ATPG_temp=ATPG_temp->next;
		}
		if(!csame)
		{
			ATPG_node *Atemp = new ATPG_node;
			Atemp->endGatename = last;
			Atemp->next=ATPG_head->next;
			ATPG_head->next=Atemp;
		}
		ptemp=ptemp->next;

	}
	F_inputVector();

	ATPG_temp = ATPG_head; //ATPGinput 0102
	while(ATPG_temp)
	{
		//cout<<ATPG_temp->endGatename<<":"<<endl;
		int *indexary = new int[ATPG_temp->toposize];
		int tsize=ATPG_temp->toposize;
		for(int i=0;i<tsize;i++)
		{
			indexary[i]=findTopoIndex(ATPG_temp->AT_topoOrder[i]);
		}
		for(int i=0;i<tsize;i++)
		{
			for(int j=i;j<tsize;j++)
			{
				if(indexary[j]<indexary[i])
				{
					int temp=indexary[j];
					indexary[j]=indexary[i];
					indexary[i]=temp;
				}
			}
		}
		for(int i=0;i<tsize;i++)
		{
			ATPG_temp->AT_topoOrder[i]=topoOrder[indexary[i]];
			//cout<<ATPG_temp->AT_topoOrder[i]<<"	";
		}


		for(int i=0;i<ATPG_temp->size;i++)
		{
			//cout<<"Input"<<i<<":"<<ATPG_temp->inputvector[i]<<endl;
			indexary[i]=findTopoIndex(ATPG_temp->inputvector[i]);
		}
		
		//cout<<endl;
		ATPG_temp = ATPG_temp->next;
	}
	temp = NULL;
	delete temp;
	free(temp);
	ATPG_temp = NULL;
	delete ATPG_temp;
	free(ATPG_temp);
}
void consSet()
{
	hashSet = new setNode*[NodeSize];
	for(int i=0;i<NodeSize;i++)
	{
		hashSet[i] = new setNode;
		hashSet[i]->next=NULL;
		hashSet[i]->down=NULL;
	}
	for(int i=0;i<NodeSize;i++)
	{
		int temp = calhash(Gatenode[i].G_name);
		setNode *newNode = new setNode;
		newNode->G_name=Gatenode[i].G_name;
		newNode->next=hashSet[temp]->next;
		hashSet[temp]->next=newNode;
	}
	
}
int findTopoIndex(string gname) //t0102
{
	for(int i=0;i<NodeSize-Info[0].size;i++)
	{
		if(topoOrder[i]==gname)
			return i;
	}
	return -1;

}
void findrealinput()
{
	path *ptemp = new path;
	ptemp = pthead;
	ptemp=ptemp->next;
	stack <string> inputstack;
	Node *temp = new Node;
	while(ptemp->next!=NULL)
	{
		for(int i=0;i<ptemp->size;i++)
		{
			temp = findNode(ptemp->pth[i]);
			if(checkt(temp->Gate)==3)
			{
				if(checkwinput(temp->input[0]))
				{
					inputstack.push(temp->input[0]);
				}
			}
			else
			{
				if(checkwinput(temp->input[0]))
				{
					inputstack.push(temp->input[0]);
				}
				if(checkwinput(temp->input[1]))
				{
					inputstack.push(temp->input[1]);
				}
			}
		}
		int stksize=inputstack.size();
		ptemp->realinput=new string[stksize];
		for(int i=0;i<stksize;i++)
		{
			ptemp->realinput[i]=inputstack.top();
			inputstack.pop();
		}
		ptemp=ptemp->next;
	}	
	temp = NULL;
	delete temp;
	free(temp);

}
void delcontrain(int constrained)
{
	int count=0;
	path *ptemp = new path;
	Thead = new path;
	Thead->next = NULL;
	ptemp=pthead;
	path *plast = new path;
	while(ptemp->next!=NULL)
	{
		//count++;
		plast=ptemp;
		ptemp=ptemp->next;
		if(ptemp->size<constrained)
		{
			plast->next=ptemp->next;
			free(ptemp);
			ptemp=plast;
		}

		//cout<<"path:"<<count<<"	";
		//PrintPath(ptemp->pth,ptemp->size);
	}
	/*
	ptemp=pthead;
	ptemp=ptemp->next;
	while(ptemp->next!=NULL)
	{
		count++;
		//cout<<"path:"<<count<<"	";
		//PrintPath(ptemp->pth,ptemp->size);
		ptemp=ptemp->next;
	}*/
	
}
void exampath(string *path1,int size)
{
	bool checkTrue=true;
	bool comsfrom=false;
	string last=path1[0];
	for(int i=1;i<size;i++)
	{
		Node *temp=findNode(path1[i]);
		Node *temp1=findNode(last);
		if(temp1->outWire==temp->input[1])
			comsfrom=true;
		if(comsfrom==false&&temp->True_a!=true)
		{
			checkTrue=false;
			break;
		}
		if(comsfrom==true&&temp->True_b!=true)
		{
			checkTrue=false;
			break;
		}
		last=path1[i];
		temp=NULL;
		delete temp;
		free(temp);
		temp1=NULL;	
		delete temp1;	
		free(temp1);
	}
	if(checkTrue==true)
	{
		path *tempPath = new path;
		tempPath->pth = path1;
		tempPath->size = size;
		tempPath->next=Thead->next;
		Thead->next = tempPath;
		tempPath->inputvec = new bool[Info[0].size];
		int k=0;
		for(int i=NodeSize-Info[0].size;i<NodeSize;i++)
		{
			tempPath->inputvec[k]=Gatenode[i].output;
			k++;
		}
	}
	

}
void verifyTruePath()
{
	path *ptemp = new path;
	ptemp = pthead;
	ptemp=ptemp->next;
	while(ptemp->next!=NULL)
	{
		exampath(ptemp->pth,ptemp->size);
		ptemp=ptemp->next;
	}	

	
}
void ExamTruePath()
{
	int number = pow(2,Info[0].size);
	int counter=0;
	for(int i=NodeSize-Info[0].size;i<NodeSize;i++)
	{
		Node *temp = findwire(Gatenode[i].G_name);
		temp->finishedTime=0;
		temp->output=false;
		temp->a_arrival=0;
		temp->b_arrival=0;
		temp->True_a=false;
		temp->True_b=false;
		temp = NULL;
		delete temp;
	}
	int cou=0;
	//cout<<findNode("U145")->G_name<<endl;
	bool chck=true;
	while(chck)
	{
		int tempcount=NodeSize-1;
		while(Gatenode[tempcount].output!=false)
		{
			chck=true;
			Gatenode[tempcount].output=false;
			tempcount--;
			if(tempcount<NodeSize-Info[0].size)
			{
				chck=false;
				break;
			}
		}
		for(int i=NodeSize-Info[0].size;i<NodeSize;i++)
		{
			cout<<Gatenode[i].output;
		}
		cout<<endl;
		if(chck!=false)
		{
			Gatenode[tempcount].output=true;
			//p_nodeinfo();
			FinishTable();
			verifyTruePath();
			cou++;
		}
	}
	
	
}
void FinishTable()
{
	for(int i=0;i<globalcount;i++)
	{

		Node *temp = findNode(topoOrder[i]);
		Node *inputB;
		Node *inputA;
		inputA=findwire(temp->input[0]);
		temp->True_a=true;
		temp->True_b=true;

		int ctype=checkt(temp->Gate);
		if(ctype==3)
		{
			temp->True_b=false;
			temp->output=!(inputA->output);
		}
		else
		{
			inputB = findwire(temp->input[1]);
		}

		temp->bol_input[0]=inputA->output;
		temp->bol_input[1]=inputB->output;
		temp->a_arrival = inputA->finishedTime;
		temp->b_arrival = inputB->finishedTime;
		int arriveOrder = 0;//a_time the same as b_time
		if(inputA->finishedTime<inputB->finishedTime)//a faster than b
			arriveOrder=1;
		if(inputA->finishedTime>inputB->finishedTime)//a slower than b
			arriveOrder=2;
		switch(ctype)
		{
			temp->True_a=true;
			temp->True_b=true;
			temp->output=!(inputA->output&inputB->output);
			case 1://Nand
			if(arriveOrder==0)
			{
				if(inputA->output==true&&inputB->output==false)
				{
					temp->True_a=false;
				}
				if(inputA->output==false&&inputB->output==true)
				{
					temp->True_b=false;
				}
			}
			else if(arriveOrder==1)
			{
				if((inputA->output==true&&inputB->output==true)||(inputA->output==true&&inputB->output==false))
				{
					temp->True_a=false;
				}
				if((inputA->output==false&&inputB->output==true)||(inputA->output==false&&inputB->output==false))
				{
					temp->True_b=false;
				}
			}
			else 
			{
				if((inputA->output==true&&inputB->output==false)||(inputA->output==false&&inputB->output==false))
				{
					temp->True_a=false;
				}
				if((inputA->output==true&&inputB->output==true)||(inputA->output==false&&inputB->output==true))
				{
					temp->True_b=false;
				}
			}
			break;
			case 2://Nor
			temp->True_a=true;
			temp->True_b=true;
			temp->output=!(inputA->output|inputB->output);
			if(arriveOrder==0)
			{
				if(inputA->output==false&&inputB->output==true)
				{
					temp->True_a=false;
				}
				if(inputA->output==true&&inputB->output==false)
				{
					temp->True_b=false;
				}
			}
			else if(arriveOrder==1)
			{
				if((inputA->output==false&&inputB->output==true)||(inputA->output==false&&inputB->output==false))
				{
					temp->True_a=false;
				}
				if((inputA->output==true&&inputB->output==true)||(inputA->output==true&&inputB->output==false))
				{
					temp->True_b=false;
				}
			}
			else
			{
				if((inputA->output==true&&inputB->output==true)||(inputA->output==false&&inputB->output==true))
				{
					temp->True_a=false;
				}
				if((inputA->output==true&&inputB->output==false)||(inputA->output==false&&inputB->output==false))
				{
					temp->True_b=false;
				}
			}

			break;
		}
		if(temp->True_a==true&&temp->True_b==true)
		{
			temp->finishedTime = (temp->a_arrival >= temp->a_arrival)?temp->a_arrival+1:temp->b_arrival+1;
		}
		else if(temp->True_a==true&&temp->True_b==false)
		{
			temp->finishedTime = temp->a_arrival+1;
		}
		else
		{
			temp->finishedTime = temp->b_arrival+1;
		}
		Node *wtemp =findwire(temp->outWire);
		wtemp->finishedTime=temp->finishedTime;
		wtemp->output=temp->output;
		wtemp->True_a=temp->True_a;
		wtemp->True_b=temp->True_b;
		wtemp->output=temp->output;
		wtemp=NULL;
		delete wtemp;
		free(wtemp);
		inputA=NULL;
		delete inputA;
		free(inputA);
		

	}
}
void getNode_linklist()
{

	Graphlink = new Node*[NodeSize];
	for(int i=0;i<NodeSize;i++)
	{
		Graphlink[i] = new Node;
		Graphlink[i]->next=NULL;
	}
	int max=0;
	int index;
	for(int i=0;i<NodeSize;i++)
	{

		if(checkt(Gatenode[i].Gate)==2||checkt(Gatenode[i].Gate)==1)
		{
			Node *inputa=findwire(Gatenode[i].input[0]);
			index=inputa->index;
			Node *link = Graphlink[index];
			Node *temp = new Node;
			temp->G_name = Gatenode[i].G_name;
			temp->Gate=Gatenode[i].Gate;
			temp->index=Gatenode[i].index;
			temp->next=link->next;
			link->next=temp;
			inputa=findwire(Gatenode[i].input[1]);
			index=inputa->index;
			link = Graphlink[index];
			Node *temp1 = new Node;
			temp1->G_name = Gatenode[i].G_name;
			temp1->Gate=Gatenode[i].Gate;
			temp1->index=Gatenode[i].index;
			temp1->next=link->next;
			link->next=temp1;															
		}
		if(checkt(Gatenode[i].Gate)==3)
		{
			Node *inputa=findwire(Gatenode[i].input[0]);
			index=inputa->index;
			Node *link = Graphlink[index];
			Node *temp = new Node;
			temp->G_name = Gatenode[i].G_name;
			temp->Gate=Gatenode[i].Gate;
			temp->index=Gatenode[i].index;
			temp->next=link->next;
			link->next=temp;
		}


	}
	/*
	for(int i=0;i<NodeSize;i++)
	{
		cout<<Gatenode[i].index<<"	"<<Gatenode[i].G_name<<"	";
		cout<<i;
		Node *cur = new Node;
		cur = Graphlink[i];
		while(cur!=NULL)
		{
			cout<<cur->G_name<<"("<<cur->outWire<<")"<<"->";
			cur=cur->next;
		}
		
		cout<<endl;
	}

	*/
	

}
void topofunc()
{
	topoOrder = new string[globalcount];
	cout<<endl<<endl<<"Topo:";
	int count=0;
	while(!topoStack.empty())
	{
		topoOrder[count]=topoStack.top();
		count++;

		topoStack.pop();		
	}
	for(int i=0;i<globalcount;i++)
	{
		cout<<topoOrder[i]<<"->";
	}
	cout<<endl;

}
Node *findNode(string a)
{
	int hash=calhash(a);
	ptrtemp = hashNode[hash];
	while(a!=ptrtemp->G_name&&ptrtemp->next!=NULL)
	{
		ptrtemp=ptrtemp->next;
	}
	return ptrtemp;
}
Node *findwire(string a)
{
	int hash = calwirehash(a)%NodeSize;
	ptrtemp = wireNode[hash];
	while(ptrtemp->outWire!=a&&ptrtemp->next!=NULL)
	{
		ptrtemp=ptrtemp->next;
	}
	

	return ptrtemp;

}
int calwirehash(string str)
{
	int strsize = str.length();
	int powerten=1;
	int sum=0;
	int count=0;
	for(int j=strsize-1;j>=0;j--)
	{
		sum+=((int)str[j]-48)*powerten;
		if(sum>500000)
		{
			sum%=NodeSize;
			powerten=1;
		}
		powerten*=10;
	}
	return sum%NodeSize;
}
void construcwirehash()
{
	wireNode = new Node*[NodeSize];
	for(int i=0;i<NodeSize;i++)
	{
		wireNode[i] = new Node;
		wireNode[i]->next=NULL;
	}
	Node *temp = new Node;
	Node *link = new Node;
	for(int i=0;i<NodeSize;i++)
	{
		int hash = calwirehash(Gatenode[i].outWire);
		/*temp->color=Gatenode[i].color;
		temp->use=Gatenode[i].use;
		temp->a_arrival=Gatenode[i].a_arrival;
		temp->b_arrival=Gatenode[i].b_arrival;
		temp->index=Gatenode[i].index;
		temp->input[0]=Gatenode[i].input[0];
		temp->input[1]=Gatenode[i].input[1];
		temp->Gate=Gatenode[i].Gate;
		temp->outWire=Gatenode[i].outWire;
		temp->bol_input[0]=Gatenode[i].bol_input[0];
		temp->bol_input[1]=Gatenode[i].bol_input[1];
		temp->G_name=Gatenode[i].G_name;
		temp->gatetype=Gatenode[i].gatetype;
		temp->finishedTime=Gatenode[i].finishedTime;
		temp->output=Gatenode[i].output;
		temp->True_a=Gatenode[i].True_a;
		temp->True_b=Gatenode[i].True_b;*/
		temp=&Gatenode[i];
		link = wireNode[hash];
		temp->next=link->next;
		link->next = temp;
	}
	
	/*
	for(int i=0;i<NodeSize;i++)//output hash table
	{
		cout<<i;
		Node *cur = new Node;
		cur = wireNode[i];
		while(cur->next!=NULL)
		{
			cout<<cur->G_name<<"("<<cur->outWire<<")"<<cur->Gate<<"->";
			cur=cur->next;
		}
		cout<<cur->G_name<<"("<<cur->outWire<<")"<<cur->Gate<<"->";
		cout<<endl;
	}*/
	
}
void constructhash()//hash function = int%nodesize
{
	hashNode = new Node*[NodeSize];
	conGate = new Node[NodeSize];
	for(int i=0;i<NodeSize;i++)
	{
		conGate[i]=Gatenode[i];
	}
	for(int i=0;i<NodeSize;i++)
	{
		hashNode[i] = new Node;
		hashNode[i]->next=NULL;
	}
	Node *temp = new Node;
	for(int i=0;i<NodeSize;i++)
	{
		int hash = calhash(conGate[i].G_name);
		temp=&conGate[i];
		Node *link = new Node;
		link = hashNode[hash%NodeSize];
		temp->next = link->next;
		link->next = temp;
		
	}
	/*
	for(int i=0;i<NodeSize;i++)//output hash table
	{
		cout<<i;
		Node *cur = new Node;
		cur = hashNode[i];
		while(cur->next!=NULL)
		{
			cout<<cur->G_name<<"->";
			cur=cur->next;
		}
		cout<<cur->G_name;
		cout<<endl;
	}
	*/
	

}
void PrintPathvec(string *sary,int size,bool *invec)
{
	string last=sary[0];
	Node *t = new Node;
	Node *x = new Node;
	cout<<"slack:"<<size-1<<"	"<<last<<"->";
	for(int i=1;i<size;i++)
	{
		bool comefrom=true;
		if(findNode(last)->outWire==findNode(sary[i])->input[0])
		{
			comefrom=false;
		}
		if(comefrom==false)
		{
			cout<<sary[i]<<"/A->"<<sary[i]<<"/Y->";
		}
		if(comefrom==true)
		{
			cout<<sary[i]<<"/B->"<<sary[i]<<"/Y->";
		}
		last = sary[i];
	}
	cout<<findNode(last)->outWire<<endl;
	int k=0;
	for(int i=NodeSize-Info[0].size;i<NodeSize;i++)
	{
		cout<<Gatenode[i].G_name<<":"<<invec[k]<<endl;
		k++;
	}
	
}
void PrintPath(string *sary,int size)
{
	string last=sary[0];
	Node *t = new Node;
	Node *x = new Node;
	cout<<"slack:"<<size-1<<"	"<<last<<"->";
	for(int i=1;i<size;i++)
	{
		bool comefrom=true;
		if(findNode(last)->outWire==findNode(sary[i])->input[0])
		{
			comefrom=false;
		}
		if(comefrom==false)
		{
			cout<<sary[i]<<"/A->"<<sary[i]<<"/Y->";
		}
		if(comefrom==true)
		{
			cout<<sary[i]<<"/B->"<<sary[i]<<"/Y->";
		}
		last = sary[i];
	}
	cout<<findNode(last)->outWire<<endl;
	cout<<endl;
	
}
int calhash(string a)
{
	int strsize = a.length();
	int powerten=1;
	int sum=0;
	for(int j=strsize-1;j>=0;j--)
	{
		sum+=((int)a[j]-48)*powerten;
		if(sum>500000)
		{
			sum%=NodeSize;
			powerten=1;
		}
		powerten*=10;
	}
	return sum%NodeSize;
}

void getpath()
{
	pthead = new path;
	pthead->next=NULL;
	pthead->tail=NULL;
	globalcount=0;
	countpath=0;
	tablesize = NodeSize-1;
	tempk = NodeSize-1;
	static stack <string>temp;
	for(int i=NodeSize-Info[0].size;i<NodeSize;i++)
	{
		string startinput = Gatenode[i].G_name;
		DFStack.push(startinput);
		Node *ptr=Graphlink[i];
		ptr=ptr->next;
		while(ptr!=NULL)
		{
			DFS(ptr->G_name,ptr->index);
			ptr=ptr->next;
		}
		DFStack.pop();
		
	}

}
void DFS(string a,int indd)
{
	DFStack.push(a);
	bool change=false;
	int index=indd;
	Node *ptr= new Node;
	ptr = Graphlink[index];
	ptr=ptr->next;

	while(ptr!=NULL)
	{

		change=true;
		DFS(ptr->G_name,ptr->index);
		ptr=ptr->next;

	}
	if(Graphlink[index]->color==0)
	{
		globalcount++;
		topoStack.push(a);
		Graphlink[index]->color=1;
	}
	bool checkout=true;
	if(change==true)
	{
		Node *tempNode=findNode(DFStack.top());
		for(int i=0;i<Info[1].size;i++)
		{
			if(tempNode->outWire==Info[1].info[i])
			{
				checkout=false;
				break;
			}

			
		}

	}

	if(change ==false||checkout==false)
	{

		int b=0;
		stack <string> result;
		stack<string>tempstack=DFStack;
		b=DFStack.size();
		path *ptemp = new path;
		ptemp->pth = new string[b];
		ptemp->size=b;
		if(pthead->next==NULL)
		{
			pthead->tail=ptemp;
		}
		ptemp->next=pthead->next;
		pthead->next=ptemp;
		int countsize=b-1;
		test++;
		//cout<<"path:"<<test<<"	";
		while(!tempstack.empty())
		{
			ptemp->pth[countsize]=tempstack.top();
			tempstack.pop();
			countsize--;
		}
		
		//PrintPath(ptemp->pth,b);
			
	}

	DFStack.pop();
		

}
int findnodeIndex(string a)
{
	bool check = false;
	int index=0;
	while(1)
	{
		if(Gatenode[index].G_name==a)
		{
			check = true;
			break;
		}
		index++;
	}
	if(check==true)
		return index;
	else
		return -1;
}
void p_nodeinfo()
{
	for(int i=0;i<NodeSize;i++)
	{
		cout<<checkt(Gatenode[i].Gate)<<"	"<<"Gate:"<<Gatenode[i].Gate<<"	NodeName:"<<Gatenode[i].G_name<<"	InputA:"<<Gatenode[i].input[0]<<"	inputB:"<<Gatenode[i].input[1]<<"	outWire:"<<Gatenode[i].outWire;
		Node *temp = findNode(Gatenode[i].G_name);
		cout<<"	A_Time:"<<temp->a_arrival<<"	B_Time:"<<temp->b_arrival<<"	A_Tbol:"<<temp->True_a<<"	B_Tbol:"<<temp->True_b<<"	FinishT:"<<temp->finishedTime;
		cout<<"	bol_a:"<<temp->bol_input[0]<<"	bol_b:"<<temp->bol_input[1]<<endl;
	}
}
bool check(string a)
{
	for(int i=0;i<typesize;i++)
	{
		if(posmod[i].Gatename==a)
			return true;
	}
	return false;
}
int checkt(string str)
{
	for(int i=0;i<typesize;i++)
	{
		if(str==posmod[i].Gatename)
		{
			return posmod[i].caltype;
		}
	}
	return 0;
}
void parse(string a)
{
	int countNodesize=0;
	Info[0].type="input";
	Info[1].type="output";
	Info[2].type="wire";
	string str;
	int counter=0;
	int k=0;
	queue <string>temp;
	fstream ifs1;
	string file=a;
	char *filename = new char[file.length()+1];
	strcpy(filename,file.c_str());
	ifs1.open(filename,ios::in);
	queue <string>parsQ;
	while(getline(ifs1,str))
	{
		char *csr = new char[str.length()+1];
		char *token;
		if(str[0]!='/'&&str[1]!='/')
		{
			strcpy(csr,str.c_str());
			token = strtok(csr,";() 	.,");
			while(token!=NULL)
			{
				string a(token);
				parsQ.push(a);
				token = strtok(NULL,";() 	.,");
			}
		}
	}
	while(!parsQ.empty())
	{
		if(parsQ.front()=="module")
		{
			while(!parsQ.empty())
			{
				if(parsQ.front()=="input"||parsQ.front()=="output"||parsQ.front()=="wire")
					break;
				parsQ.pop();
			}
		}
		if(parsQ.front()=="input")
		{
			k=0;
			counter=0;
			parsQ.pop();
			while(!parsQ.empty())
			{
				if(parsQ.front()=="module"||parsQ.front()=="output"||parsQ.front()=="wire")
					break;
				temp.push(parsQ.front());
				counter++;
				parsQ.pop();
			}
			Info[0].info = new string[counter];
			Info[0].size = counter;
			while(!temp.empty())
			{
				Info[0].info[k]=temp.front();
				k++;
				temp.pop();
			}
		}
		if(parsQ.front()=="output")
		{
			counter=0;
			parsQ.pop();
			k=0;
			while(!parsQ.empty())
			{
				if(parsQ.front()=="module"||parsQ.front()=="input"||parsQ.front()=="wire")
					break;
				temp.push(parsQ.front());
				counter++;
				parsQ.pop();
			}
			Info[1].info = new string[counter];
			Info[1].size = counter;
			while(!temp.empty())
			{
				Info[1].info[k]=temp.front();
				k++;
				temp.pop();
			}

		}
		if(parsQ.front()=="wire")
		{
			counter=0;
			parsQ.pop();
			k=0;
			while(!parsQ.empty())
			{
				if(parsQ.front()=="module"||parsQ.front()=="input"||parsQ.front()=="output"||check(parsQ.front())==true)
					break;
				temp.push(parsQ.front());
				counter++;
				parsQ.pop();
			}
			Info[2].info = new string[counter];
			Info[2].size = counter;
			while(!temp.empty())
			{
				Info[2].info[k]=temp.front();
				k++;
				temp.pop();
			}

		}
		else
		{
			if(checkt(parsQ.front())!=0)
				countNodesize++;
			temp.push(parsQ.front());
			parsQ.pop();
		}
		
	}
	NodeSize=countNodesize;
	k11=NodeSize;
	Gatenode = new Node[NodeSize+Info[0].size];
	int countk=0;
	while(!temp.empty())
	{
		if(checkt(temp.front())==3)
		{
			Gatenode[countk].Gate=temp.front();
			temp.pop();
			Gatenode[countk].G_name=temp.front();
			temp.pop();
			temp.pop();
			Gatenode[countk].input[0]=temp.front();
			temp.pop();
			temp.pop();
			Gatenode[countk].outWire=temp.front();

		}
		else if(checkt(temp.front())==2||checkt(temp.front())==1)
		{
			Gatenode[countk].Gate=temp.front();
			temp.pop();
			Gatenode[countk].G_name=temp.front();
			temp.pop();
			if(temp.front()=="A")
			{
				temp.pop();
				Gatenode[countk].input[0]=temp.front();
				temp.pop();
			}
			else if(temp.front()=="B")
			{
				temp.pop();
				Gatenode[countk].input[1]=temp.front();
				temp.pop();
			}
			else if(temp.front()=="Y")
			{
				temp.pop();
				Gatenode[countk].outWire=temp.front();
				temp.pop();
			}
			if(temp.front()=="A")
			{
				temp.pop();
				Gatenode[countk].input[0]=temp.front();
				temp.pop();
			}
			else if(temp.front()=="B")
			{
				temp.pop();
				Gatenode[countk].input[1]=temp.front();
				temp.pop();
			}
			else if(temp.front()=="Y")
			{
				temp.pop();
				Gatenode[countk].outWire=temp.front();
				temp.pop();
			}
			if(temp.front()=="A")
			{
				temp.pop();
				Gatenode[countk].input[0]=temp.front();
			}
			else if(temp.front()=="B")
			{
				temp.pop();
				Gatenode[countk].input[1]=temp.front();
			}
			else if(temp.front()=="Y")
			{
				temp.pop();
				Gatenode[countk].outWire=temp.front();
			}
			
			
		}
		countk++;
		temp.pop();
		
	}
	for(int i=0;i<NodeSize;i++)
	{
		Gatenode[i].color=0;
		Gatenode[i].index=i;
	}
	int count=0;
	for(int i=NodeSize;i<NodeSize+Info[0].size;i++)
	{
		Gatenode[i].color=0;
		Gatenode[i].G_name=Info[0].info[count];
		Gatenode[i].Gate="input";
		Gatenode[i].index=i;
		Gatenode[i].outWire=Info[0].info[count];
		count++;

	}
	NodeSize+=Info[0].size;
	/*
	cout<<"input"<<endl;
	for(int i=0;i<Info[0].size;i++)
	{
		cout<<Info[0].info[i]<<"	";
	}
	cout<<endl<<"output"<<endl;
	for(int i=0;i<Info[1].size;i++)
	{
		cout<<Info[1].info[i]<<"	";
	}
	cout<<endl<<"wire"<<endl;
	for(int i=0;i<Info[2].size;i++)
	{
		cout<<Info[2].info[i]<<"	";
	}
	*/


}
void pros_mod(string c)
{
	int count_pos=0;
	queue <string>str_t;
	queue <string>result_str;
	string str;
	fstream ifs1;
	string file=c;
	char *filename = new char[file.length()+1];
	strcpy(filename,file.c_str());
	ifs1.open(filename,ios::in);
	while(getline(ifs1,str))
	{
		char *csr = new char[str.length()+1];
		char *token;
		strcpy(csr,str.c_str());
		token = strtok(csr,";() 	,");
		while(token!=NULL)
		{
			string a(token);
			str_t.push(a);
			token = strtok(NULL,";() 	,");
		}
		while(!str_t.empty())
		{
			if(declaretype(str_t.front())==true)
			{
				if(str_t.front()=="module")
				{
					count_pos++;
					str_t.pop();
				}
				while(!str_t.empty())
				{
					result_str.push(str_t.front());
					str_t.pop();
				}
			}
			else
			{
				while(!str_t.empty())
				{
					str_t.pop();
				}
			}
		}
	}
	posmod = new pros_MOD[count_pos+3];
		posmod[0].Gatename = "NAND";
		posmod[0].caltype = 1;
		posmod[1].Gatename = "NOR";
		posmod[1].caltype = 2;
		posmod[2].Gatename = "NOT";
		posmod[2].caltype = 3;
		queue <string> a;
		int b=3;
		int evencount=0;
		while(!result_str.empty())
		{
			if(result_str.front()=="Y"||result_str.front()=="A"||result_str.front()=="B"||result_str.front()=="I0")
			{
				result_str.pop();
			}
			else
			{
				a.push(result_str.front());
				result_str.pop();
			}
			
		}
		while(!a.empty())
		{
			if(evencount%2==0)
				posmod[b].Gatename=a.front();
			else
			{
				if(a.front()=="nand")
					posmod[b].caltype=1;
				if(a.front()=="nor")
					posmod[b].caltype=2;
				if(a.front()=="not")
					posmod[b].caltype=3;
				b++;
			}
			evencount++;
			a.pop();
		}
		typesize=count_pos+3;
	
}
bool declaretype(string a)
{
	char *csr = new char[a.length()+1];
	strcpy(csr,a.c_str());
	if(a=="module"||strcmp(csr,"nand")==0||strcmp(csr,"nor")==0||strcmp(csr,"not")==0)
		return true;
	return false;
}