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

};
struct path
{
	string *pth;
	path *next;
	path *tail;
	int size;
	bool *inputvec;
};
Node **wireNode;
Node **hashNode;
Node **Graphlink;
int countpath;
Node *Gatenode;
Node *conGate;
inoutInfo Info[3];
int NodeSize;
pros_MOD *posmod;
string *topoOrder;
stack <string>DFStack;
stack <string>topoStack;
path *truePath;
Node *findNode(string);
int test;
int k11;
path *pthead;
path *Thead;
void construcwirehash();
Node *findwire(string);
void PrintPath(string *,int size);
void ExamTruePath();
void FinishTable();
void delcontrain(int);
void PrintPathvec(string *,int ,bool *);
int main(int argc, char** argv)
{

	run(argv[1],argv[2],0);
	cout<<"Case: "<<argv[2]<<endl;
	return 0;
}
void run(string a,string b,int constrain)
{
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
	time_t end = time(NULL);
	cout<<endl<<endl<<"Time: "<<end-nStart<<"(seconds)"<<"	Find #path:"<<test<<endl;
	//ExamTruePath();
	/*path *outemp = Thead;
	outemp=outemp->next;
	int k=0;
	while(outemp!=NULL)
	{
		PrintPathvec(outemp->pth,outemp->size,outemp->inputvec);
		outemp=outemp->next;
		k++;
	}
	cout<<"Find #True path:"<<k<<endl;
	
	//p_nodeinfo();
	*/
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
	/*ptemp=pthead;
	ptemp=ptemp->next;
	while(ptemp->next!=NULL)
	{
		count++;
		cout<<"path:"<<count<<"	";
		PrintPath(ptemp->pth,ptemp->size);
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
		if(findNode(last)->outWire==temp->input[1])
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
	Node *temp = new Node;
	int hash=calhash(a);
	temp = hashNode[hash];
	while(a!=temp->G_name&&temp->next!=NULL)
	{
		temp=temp->next;
	}
	return temp;
}
Node *findwire(string a)
{
	int hash = calwirehash(a)%NodeSize;
	Node *temp11=new Node;
	temp11 = wireNode[hash];
	while(temp11->outWire!=a&&temp11->next!=NULL)
	{
		temp11=temp11->next;
	}
	

	return temp11;

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
		//cout<<"path:"<<test<<"	";
		while(!tempstack.empty())
		{
			ptemp->pth[countsize]=tempstack.top();
			tempstack.pop();
			countsize--;
		}
		
		//PrintPath(ptemp->pth,b);
		cout<<test<<' ';
		test++;
		
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
			temp.pop();
			Gatenode[countk].input[0]=temp.front();
			temp.pop();
			temp.pop();
			Gatenode[countk].input[1]=temp.front();
			temp.pop();
			temp.pop();
			Gatenode[countk].outWire=temp.front();
			
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