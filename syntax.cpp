// shit.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <queue>
#include <map>
#include <stack>
#include <utility>
#include <set>
#include <string>
#include <iomanip>
using namespace std;
const string base_path = "C:\\Users\\coolwyj\\Documents\\Visual Studio 2012\\WebSites\\WebSite1\\";

struct LEX
{
	int line;
	string word,type;
	LEX(){}
	LEX(int a,string b,string c):line(a),word(b),type(c){}
};
vector < LEX > lex;


class EXPRESS
{
#define max_right 105
public:
	int dot_pos;
	string left,last;
	vector <string> right;
	EXPRESS (){}
	EXPRESS (int a,string b,string c,vector <string> d):dot_pos(a),left(b),last(c),right(d){}
	bool operator < (const EXPRESS &x) const
	{
		if(dot_pos != x.dot_pos) return dot_pos < x.dot_pos;
		if(left != x.left) return left < x.left;
		if(last != x.last) return last < x.last;
		if(right != x.right)
		{
			if(right.size() != x.right.size()) return right.size() < x.right.size();
			for(int i=0;i<right.size();i++)
				if(right[i] != x.right[i]) return right[i] < x.right[i];
		}
	}
	bool operator == (const EXPRESS x) const
	{
		if(dot_pos == x.dot_pos && left == x.left && last == x.last && right == x.right) return true;
		return false;
	}
};

class LR1
{
#define max_node 105
#define ACC 100000
#define statusLimit 105
private:
	vector < set<EXPRESS> > I;
	vector <string> yufa;
	vector <EXPRESS> base;
	set <string> VN,VT,Vstar;
	map <string,int> GOTO[max_node],ACTION[max_node];
	stack <int> status_stack;
	stack <string> sign_stack;
	int n;

	void read()
	{
		string tmp;
		fstream cin;
		cin.open(base_path+"syntax_grammar.txt",ios::in);
		getline(cin,tmp);
		int pos = 0;
		for(int i=0;i<tmp.size();i++)
		{
			if(tmp[i] == '-') break;
			else pos = i;
		}
		yufa.push_back("S' -> "+tmp.substr(0,pos));
		yufa.push_back(tmp);
		while(getline(cin,tmp)) yufa.push_back(tmp);
		cin.close();
	}

	vector<string> split(string str,string pattern)
	{
		string::size_type pos;
		vector<string> result;
		str+=pattern;//��չ�ַ����Է������
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

	int getID(EXPRESS x)
	{
		for(int i=0;i<base.size();i++)
		{
			//���Ƚ�dot_pos,��last
			if(base[i].left == x.left && base[i].right == x.right) return i;
		}
		return 0;
	}

	vector <string> getFirst(vector <string> cur)
	{
		vector <string> first;

		for(int i=0;i<cur.size();i++)
		{
			//�����ǰΪ�ս���򷵻���
			if(VT.find(cur[i]) != VT.end() || cur[i]=="��") {first.push_back(cur[i]);return first;}

			bool flag = true;

			string nxt = cur[i];

			for(int j=0;j<yufa.size();j++)
			{
				if(base[j].left == nxt)
				{
					if(nxt == base[j].right[0] && flag==false) continue;
					vector <string> tmp = getFirst(base[j].right);
					if(find(tmp.begin(),tmp.end(),"��") == tmp.end()) flag = false;//û�Цţ�����Ҫ�Һ������
					else {flag = true;continue;}//�����Ĳ���ʽ���Եõ���
					for(int k=0;k<tmp.size();k++)
						first.push_back(tmp[k]);
				}
			}
			if(!flag) break;
		}

		return first;
	}

	EXPRESS set_node(int x)
	{
		EXPRESS res;
		res.dot_pos=0;
		res.last="#";
		vector <string> tmp = split(yufa[x]," ");
		res.left=tmp[0];
		int sz = (int)tmp.size();
		for(int i=2;i<sz;i++)
		{
			res.right.push_back(tmp[i]);
			if(tmp[i] == "��") continue;//�� is not a VN or VT
			Vstar.insert(tmp[i]);
			if( (tmp[i][0]>='A' && tmp[i][0]<='Z')) VN.insert(tmp[i]);
			else VT.insert(tmp[i]);
		}
		return res;
	}

	set <EXPRESS> getClosure(EXPRESS cur)
	{
		set <EXPRESS> res;
		res.insert(cur);
		string nxt = cur.right[cur.dot_pos];

		if(VN.find(nxt) == VN.end()) return res;//dot���Ƿ��ս����ô�����������µ�

		vector <string> first;

		if(cur.dot_pos+1 < cur.right.size())//�������һ�����ţ�Ҫ��first��
		{
			vector <string> tmp;
			for(int i=cur.dot_pos+1;i<cur.right.size();i++)
				tmp.push_back(cur.right[i]);
			tmp.push_back(cur.last);
			first = getFirst(tmp);
		}
		else//��Ϊ���һ�����ţ�first��Ϊcur.last
			first.push_back(cur.last);

		for(int i=0;i<yufa.size();i++)
		{
			if(base[i].left == nxt)
			{
				for(int j=0;j<first.size();j++)
				{
					if(first[j] == "��") continue;
					if(base[i].right[0] == "��") continue;
					EXPRESS tmp(0,nxt,first[j],base[i].right);
					res.insert(tmp);
				}
			}
		}

		return res;
	}

	void build_I()
	{
		for(int i=0;i<yufa.size();i++)
		{
			base.push_back(set_node(i));
		}

		VT.insert("#");

		EXPRESS theLast = base[0];
		theLast.dot_pos++;

		set <EXPRESS> tmp = getClosure(base[0]);//����S'
		while(true)//��հ�
		{
			int presize = tmp.size();
			for(auto k=tmp.begin();k!=tmp.end();k++)
			{
				if(k->dot_pos < k->right.size())
				{
					set <EXPRESS> t = getClosure(*k);
					tmp.insert(t.begin(),t.end());
				}
			}
			if(presize == tmp.size()) break;
		}
		I.push_back(tmp);

		for(int i=0;i<I.size();i++)//������淶��
		{
			for(auto j=Vstar.begin();j!=Vstar.end();j++)//ö�����з���
			{
				set <EXPRESS> tmp;
				for(auto k=I[i].begin();k!=I[i].end();k++)//ö�ٵ�ǰ�������в���ʽ
				{
					if(k->dot_pos < k->right.size() && *j == k->right[k->dot_pos] )
					{
						EXPRESS t(k->dot_pos+1,k->left,k->last,k->right);
						tmp.insert(t);
					}
				}
				while(true)//��հ�
				{
					int presize = tmp.size();
					for(auto k=tmp.begin();k!=tmp.end();k++)
					{
						if(k->dot_pos < k->right.size())
						{
							set <EXPRESS> t = getClosure(*k);
							tmp.insert(t.begin(),t.end());
						}
					}
					if(presize == tmp.size()) break;
				}

				if(tmp.empty()) continue;//Ϊ��ֱ�ӷ���

				//�ж��Ƿ����¼���
				bool flag = true;
				for(int k=0;k<I.size();k++)
				{
					if(I[k] == tmp)
					{
						if(VN.find(*j) != VN.end()) GOTO[i][*j] = k;
						else ACTION[i][*j] = k;
						flag = false;
						break;
					}
				}

				if(flag)
				{
					I.push_back(tmp);
					
					if(VN.find(*j) != VN.end()) GOTO[i][*j] = I.size()-1;
					else ACTION[i][*j] = I.size()-1;
					
					if(tmp.find(theLast) != tmp.end()) 
						ACTION[I.size()-1]["#"] = ACC;
					else
					{
						for(auto k=tmp.begin();k!=tmp.end();k++)
						{
							if(k->dot_pos == k->right.size())
							{
								int id = getID(*k);
								ACTION[I.size()-1][k->last] = id+statusLimit;
							}
						}
					}
				}

			}
		}

	}

	vector <LEX> modifyStatus(int cur,string nxtStr,int i)
	{
		vector <LEX> error;
		if(ACTION[cur][nxtStr] < statusLimit)//is Si
		{
			sign_stack.push(nxtStr);
			status_stack.push(ACTION[cur][nxtStr]);
		}
		else//is ri
		{
			//sign_stack.push(nxtStr);
			//status_stack.push(ACTION[cur][nxtStr]);
			int who = ACTION[cur][nxtStr] - statusLimit;
			int rightSz = base[who].right.size();
			for(int j=0;j<rightSz;j++)
			{
				status_stack.pop();
				sign_stack.pop();
			}
			if(GOTO[status_stack.top()].find(base[who].left) == GOTO[status_stack.top()].end())
			{
				error.push_back(lex[i]);
				return error;
			}
			status_stack.push(GOTO[status_stack.top()][base[who].left]);
			sign_stack.push(base[who].left);
		}
		return error;
	}

	void print()
	{
		fstream cout;
		cout.open(base_path+"project_set.txt",ios::out,ios::_Nocreate);
		for(int i=0;i<I.size();i++)
		{
			cout<<"I"<<i<<":"<<endl;
			for(auto j=I[i].begin();j!=I[i].end();j++)
			{
				cout<<j->left<<" -> ";
				for(int k=0;k<j->dot_pos;k++)
					cout<<j->right[k]<<" ";
				cout<<"��";
				for(int k=j->dot_pos;k<j->right.size();k++)
					cout<<j->right[k]<<" ";
				cout<<" , "<<j->last<<endl;
			}
		}
		cout.close();

		cout.open(base_path+"LR1_table.txt",ios::out,ios::_Nocreate);
		cout<<"     ";
		for(auto i=VT.begin();i!=VT.end();i++)
			cout<<setw(10)<<*i;
		//cout<<setw(10)<<"#";
		for(auto i=VN.begin();i!=VN.end();i++)
			cout<<setw(10)<<*i;
		cout<<endl;

		for(int i=0;i<I.size();i++)
		{
			cout<<setw(5)<<i;
			for(auto j=VT.begin();j!=VT.end();j++)
			{
				if(ACTION[i].find(*j) == ACTION[i].end()) cout<<setw(10)<<" ";
				else
				{
					int p = ACTION[i][*j];
					if(p == ACC) cout<<setw(10)<<"acc";
					else if(p < statusLimit) cout<<setw(10)<<"S"+to_string(p);
					else cout<<setw(10)<<"r"+to_string(p-statusLimit);
				}
			}

			/*if(ACTION[i].find("#") == ACTION[i].end()) cout<<setw(10)<<" ";
			else
			{
				int p = ACTION[i]["#"];
				if(p == ACC) cout<<setw(10)<<"acc";
				else if(p < statusLimit) cout<<setw(10)<<"S"+to_string(p);
				else cout<<setw(10)<<"r"+to_string(p-statusLimit);
			}*/

			for(auto j=VN.begin();j!=VN.end();j++)
			{
				if(GOTO[i].find(*j) == GOTO[i].end()) cout<<setw(10)<<" ";
				else
				{
					cout<<setw(10)<<GOTO[i][*j];
				}
			}
			cout<<endl;
		}

		cout.close();
	}

public:

	void init()
	{
		n = 0;
		read();
		build_I();
		print();
	}

	vector <LEX> run(vector < LEX > lex)
	{
		vector <LEX> error;
		int len = lex.size();
		status_stack.push(0);
		sign_stack.push("#");

		for(int i=0;i<len;i++)
		{
			int cur = status_stack.top();
			string nxtStr = lex[i].word;
			string nxtType = lex[i].type;

			if(ACTION[cur].find(nxtType) != ACTION[cur].end())
			{
				while(nxtType != sign_stack.top())
				{
					error = modifyStatus(status_stack.top(),nxtType,i);//������stack��ı䣬���µ�ǰ�����ı䣬���Դ�top
					if(!error.empty()) return error;
				}
			}
			else if(ACTION[cur].find(nxtStr) != ACTION[cur].end())
			{
				if(nxtStr == "#")
				{
					while(sign_stack.top() != base[0].right[0])
					{
						modifyStatus(status_stack.top(),nxtStr,i);
						if(!error.empty()) return error;
					}
					return error;
				}
				while(nxtStr != sign_stack.top())
				{
					error = modifyStatus(status_stack.top(),nxtStr,i);
					if(!error.empty()) return error;
				}
			}
			else 
			{
				error.push_back(lex[i]);
				return error;
			}
		}
		return error;
	}
};

int main()
{
	int t1;
	string t2,t3;
	fstream cin;
	cin.open(base_path+"lex_analyze.txt",ios::in);
	while(cin>>t1>>t2>>t3) lex.push_back(LEX(t1,t2,t3));
	lex.push_back(LEX(t1,"#","NULL"));
	cin.close();

	LR1 syntax;
	syntax.init();
	vector <LEX> t = syntax.run(lex);

	fstream cout;
	cout.open(base_path+"syntax_analyze.txt",ios::out,ios::_Nocreate);
	if(t.empty()) cout<<"�ó�����ϸ����ķ�"<<endl;
	else
		cout<<"�ó��򲻷��ϸ����ķ�\n"<<"line #"<<t[0].line<<": "<<t[0].word<<endl;
	cout.close();
	return 0;
}