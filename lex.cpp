// fuck.cpp : 定义控制台应用程序的入口点。
//


#include "stdafx.h"

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <queue>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <utility>
#include <map>
#include <set>
#include <ctype.h>
#include <string>
#include <fstream>
using namespace std;
#define max_keyword 40

#pragma warning(disable:4996)

struct ERR
{
	int err_code;
	int line;
	string word;
	ERR(){}
	ERR(int a_code,int b_line,string c):err_code(a_code),line(b_line),word(c){}
};

const string base_path = "C:\\Users\\coolwyj\\Documents\\Visual Studio 2012\\WebSites\\WebSite1\\";
map <string,int> keyword;
map <int,string> msg_err;
vector < ERR > error;
string str;

bool isAlpha(char ch)
{
	if(ch >='A' && ch<='Z') return true;
	if(ch >='a' && ch<='z') return true;
	return false;
}

bool isNum(char ch)
{
	if(ch >= '0' && ch <= '9') return true;
	return false;
}

class DFA
{
#define Z 105
#define VirPoint Z-1
#define via first
#define to second
private:
	vector <string> wenfa,name;
	vector < pair<int,int> > NFA_edge[Z+1],DFA_edge[Z+1];
	vector <int> success[Z+1];
	map <string,int> node;
	set <int> st[Z+1];
	set <int> VT,VN;
	int deg[Z+1];
	int id,DFA_id;
	void read(char filename[])
	{
		string tmp;
		fstream cin;
		cin.open(base_path+filename,ios::in);
		while(getline(cin,tmp)) 
		{
			if(tmp.find('#') == string::npos)
				wenfa.push_back(tmp);
			else
				name.push_back(tmp);
		}
		cin.close();
	}

	vector<string> split(string str,string pattern)
	{
		string::size_type pos;
		vector<string> result;
		str+=pattern;//扩展字符串以方便操作
		int size=str.size();

		for(int i=0; i<size; i++)
		{
			pos=str.find(pattern,i);
			if(pos<size)
			{
				string s=str.substr(i,pos-i);
				result.push_back(s);
				i=pos+pattern.size()-1;
			}
		}
		return result;
	}

	int getID(string tmp)
	{
		if(node.find(tmp) == node.end()) node[tmp] = id++;
		return node[tmp];
	}

	void build_NFA()
	{
		for(int i=0;i<wenfa.size();i++)
		{
			vector <string> res = split(wenfa[i]," ");//split wenfa by space

			//特殊处理第一部分

			int cur = getID(res[0]);
			VN.insert(cur);
			//处理剩余部分
			for(int j=2;j<res.size();j++)
			{
				if(res[j].compare("|") == 0) continue;

				int pos = -1;
				for(int k=0;k<res[j].size();k++)
				{
					if(res[j][k]>='A' && res[j][k]<='Z') {pos = k;break;}
				}
				if(pos == -1)
				{
					int via = getID(res[j]);
					NFA_edge[cur].push_back(make_pair(via,Z));
					VN.insert(Z);
					VT.insert(via);
					deg[Z]++;
				}
				else
				{
					int via = getID(res[j].substr(0,pos));
					int to = getID(res[j].substr(pos,res[j].size()-pos));
					NFA_edge[cur].push_back(make_pair(via,to));
					VN.insert(to);
					VT.insert(via);
					deg[to]++;
				}
			}

		}
	}

	set<int> bfs(int u,int who)
	{		
		set <int> res;
		for(set <int> :: iterator set_it = st[u].begin();set_it!=st[u].end();set_it++)
		{
			for(int i=0;i<NFA_edge[*set_it].size();i++)
			{
				int to = NFA_edge[*set_it][i].to;
				int via = NFA_edge[*set_it][i].via;
				if(via != who) continue;
				res.insert(to);
			}
		}
		return res;
	}

	vector <int> build_DFA_graph(int u,int start_id)
	{
		vector <int> res;
		queue <int> q;
		st[start_id].clear();
		st[start_id].insert(u);
		q.push(start_id);
		DFA_id = start_id;
		while(!q.empty())
		{
			int cur = q.front();
			int nxt = cur+1;
			q.pop();
			for(set <int> :: iterator set_it=VT.begin();set_it!=VT.end();set_it++)
			{
				bool flag = true;
				st[nxt] = bfs(cur,*set_it);
				if(st[nxt].empty()) continue;
				for(int i=start_id;i<=DFA_id;i++)
				{
					if(st[nxt] == st[i])
					{
						DFA_edge[cur].push_back(make_pair(*set_it,i));
						flag = false;
					}
				}
				if(flag) 
				{
					DFA_edge[cur].push_back(make_pair(*set_it,nxt));
					if(st[nxt].find(Z) != st[nxt].end()) res.push_back(nxt);
					q.push(nxt);
					nxt++;
					DFA_id++;
				}
				st[nxt].clear();
			}
		}
		return res;
	}

	void build_DFA()
	{
		//设置虚点，连接所有起始点，任意输入可达。
		for(set <int> :: iterator set_it=VN.begin();set_it!=VN.end();set_it++)
		{
			if(deg[*set_it] == 0)
			{
				DFA_edge[VirPoint].push_back(make_pair(VirPoint,*set_it));
			}
		}
		int sz = DFA_edge[VirPoint].size();
		for(int i=0;i<sz;i++)
		{
			success[DFA_edge[VirPoint][i].to] = build_DFA_graph(DFA_edge[VirPoint][i].to,DFA_edge[VirPoint][i].to);
		}
	}

	int run(string s,int u,int cur,int last)
	{
		if(cur == s.size() || s[cur]==' ')//字符串尾部
		{
			int sz = success[last].size();
			for(int i=0;i<sz;i++)
				if(u == success[last][i]) return cur-1;
			return -1;
		}
		int sz = DFA_edge[u].size();
		string tmp = "";	tmp.append(1,s[cur]);
		if(node.find(tmp) == node.end())//无此非终结符，即无法到下一个状态，当前的还应该判断是否分成一个词
			return -1;
		int me = node[tmp];
		for(int i=0;i<sz;i++)
		{
			int t = DFA_edge[u][i].via;
			if(me == t)	return run(s,DFA_edge[u][i].to,cur+1,last);
		}
		//未在上述分支return则说明由tmp无法到达新状态
		sz = success[last].size();
		for(int i=0;i<sz;i++)
			if(u == success[last][i]) return cur-1;
		return -1;
	}

public:
	void init(char filename[])
	{
		memset(deg,0,sizeof(deg));
		DFA_id = id = 0;
		read(filename);
		build_NFA();
		build_DFA();
	}

	string judge(string s,int &pos)
	{
		int sz = DFA_edge[VirPoint].size();
		string res = "";
		int tmp = 0;
		for(int i=0;i<sz;i++)
		{
			if( (tmp = run(s,DFA_edge[VirPoint][i].to,0,DFA_edge[VirPoint][i].to)) != -1 ) 
			{
				pos+=tmp;
				res=name[i];
				break;
			}
		}
		return res;
	}

};

void init()
{
	string tmp;
	fstream cin;
	cin.open(base_path+"keyword.txt",ios::in);
	int i=0;
	while(cin>>tmp) keyword[tmp] = i++;
	cin.close();

	msg_err[0] = "unknown character";

}

void rec_err(int err_code,int line,string word)
{
	error.push_back(ERR(err_code,line,word));
}

void print_err()
{
	fstream cout;
	cout.open(base_path+"lex_analyze.txt",ios::out|ios::app);
	int sz = error.size();
	for(int i=0;i<sz;i++)
		cout<<"#error "<<i+1<<": "<<msg_err[error[i].err_code]<<" "<<error[i].word<<" in line "<<error[i].line<<endl;
	cout.close();
}

bool iskeyword(string s)
{
	if(keyword.find(s) != keyword.end()) return true;
	return false;
}

int main()
{
	init();
	DFA my_dfa;
	my_dfa.init("lex_grammar.txt");

	fstream cin;
	cin.open(base_path+"code.txt",ios::in);

	fstream cout;
	cout.open(base_path+"lex_analyze.txt",ios::out,ios::_Nocreate);

	int line = 0;
	if(!cin.is_open()) return 0;
	while(!cin.eof())
	{
		line++;
		getline(cin,str);
		if(str.find("#include") != string::npos) continue;//header file 就先不处理了
		int sz = str.size();
		for(int i=0;i<sz;i++)
		{
			while(str[i] == ' ' || str[i] == '\n' || str[i] == '\r' || str[i] == '\t') 
			{
				i++;
			}
			if(i >= sz) break;
			int pos = i;
			
			string type = my_dfa.judge(str.substr(i,str.size()-i),pos);

			string word = str.substr(i,pos-i+1);
			
			if(iskeyword(word))//取出的词要先判是否为keyword
			{
				cout<<line<<" "<<word<<" #keyword"<<endl;
			}
			else
			{
				if("" != type)
					cout<<line<<" "<<word<<" "<<type<<endl;
				else
					rec_err(0,line,word);
			}
			i = pos;
		}
	}
	cout.close();
	cin.close();

	print_err();
	
	return 0;
}