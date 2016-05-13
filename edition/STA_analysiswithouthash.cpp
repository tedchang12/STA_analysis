#include<iostream>
#include<string>
#include<stack>
#include<queue>
#include<fstream>
#include<regex>
#include<time.h>
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
void p_nodeinfo();
int typesize;
int tempk;
int tablesize;
void pros_mod();
void run();
void parse();
int checkt(string);
bool declaretype(string);
void getpath();
bool check(string);
void DFS(string);
int findnodeIndex(string);
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
struct nodeTable
{
	int finishTime;
	int index;
	string Gate_name;
	int a_arrival;
	int b_arrival;
	bool bool_output;
	bool bool_a;
	bool bool_b;
	string wire_name;
};
struct Node
{
	int index;
	string Gate;
	string outWire;
	string input[2];
	string G_name;
	int gatetype;
	int Arrival_timeA;
	int Arrival_timeB;
	bool fantype;

};
int countpath;
Node *Gatenode;
inoutInfo Info[3];
int NodeSize;
pros_MOD *posmod;
string *topoOrder;
stack <string>DFStack;
int test;
int main()
{
	run();
	return 0;
}
void run()
{
	time_t nStart = time(NULL);
	pros_mod();
	parse();
	//p_nodeinfo();
	getpath();
	time_t end = time(NULL);
	cout<<endl<<endl<<"time"<<end-nStart<<endl;
}
void getpath()
{
	countpath=0;
	tablesize = Info[0].size+Info[1].size+NodeSize;
	topoOrder = new string[NodeSize];
	tempk = NodeSize-1;
	queue <string>inputq;
	static stack <string>temp;
	for(int i=0;i<Info[0].size;i++)//put input to table
	{
		inputq.push(Info[0].info[i]);
	}
	while(!inputq.empty())
	{
		string startinput = inputq.front();
		DFStack.push(startinput);

		for(int i=0;i<NodeSize;i++)
		{
			test = i;
			if(Gatenode[i].input[0]==DFStack.top()||Gatenode[i].input[1]==DFStack.top())
			{
				DFS(Gatenode[i].G_name);
			}
		}
		DFStack.pop();
		inputq.pop();

	}

}
void DFS(string a)
{
	DFStack.push(a);
	bool change=false;
	for(int i=0;i<NodeSize;i++)
	{
		if(Gatenode[i].input[0]==Gatenode[findnodeIndex(a)].outWire||Gatenode[i].input[1]==Gatenode[findnodeIndex(a)].outWire)
		{
			DFS(Gatenode[i].G_name);
			change = true;
		}
	}
	if(change ==false)
	{

		int b=0;
		stack <string> result;
		stack<string>tempstack=DFStack;
		while(!tempstack.empty())
		{
			result.push(tempstack.top());
			tempstack.pop();
			b++;
		}
		string last = result.top();
		cout<<test<<" "<<"Path:"<<countpath<<" "<<"Slack:"<<b-1<<"	";
		countpath++;
		cout<<last<<"->";
		result.pop();
		while(!result.empty())
		{
			int index = findnodeIndex(result.top());
			int comsfrom=0;
			if(Gatenode[index].input[0]==result.top())
			{
				comsfrom=0;
			}
			else
				comsfrom=1;
			switch(comsfrom)
			{
				case 1:
					cout<<result.top()<<"/A->"<<result.top()<<"/Y->";
				break;
				case 2:
					cout<<result.top()<<"/B->"<<result.top()<<"/Y->";
				break;
			}
			last=result.top();
			result.pop();

		}
		cout<<Gatenode[findnodeIndex(last)].outWire;
		cout<<endl;

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
		cout<<i<<"	"<<"Gate:"<<Gatenode[i].Gate<<"	NodeName:"<<Gatenode[i].G_name<<"	InputA:"<<Gatenode[i].input[0]<<"	inputB:"<<Gatenode[i].input[1]<<"	outWire:"<<Gatenode[i].outWire<<endl;
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
void parse()
{
	int countNodesize=0;
	Info[0].type="input";
	Info[1].type="output";
	Info[2].type="wire";
	string str;
	int counter=0;
	int k=0;
	queue <string>temp;
	ifstream ifs1("input/case1",ifstream::in);
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
	Gatenode = new Node[countNodesize];
	int countk=0;
	cout<<endl<<NodeSize<<endl;
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
void pros_mod()
{
	int count_pos=0;
	queue <string>str_t;
	queue <string>result_str;
	string str;
	ifstream ifs1("input/cadcontest.v",ifstream::in);
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
	for(int i=0;i<6;i++)
		cout<<posmod[i].Gatename<<"	"<<posmod[i].caltype<<endl;
	cout<<endl;
}
bool declaretype(string a)
{
	char *csr = new char[a.length()+1];
	strcpy(csr,a.c_str());
	if(a=="module"||strcmp(csr,"nand")==0||strcmp(csr,"nor")==0||strcmp(csr,"not")==0)
		return true;
	return false;
}