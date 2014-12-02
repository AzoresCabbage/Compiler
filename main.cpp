#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <string>
using namespace std;
string str;
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
int main()
{
    system("lex.exe");
    freopen("lex_analyze.txt","r",stdin);
    freopen("syntax_analyze.txt","w",stdout);
    int cnt=0;
    bool flag = true;
    while(!cin.eof())
    {
        getline(cin,str);
        cnt++;
        if(str.find("#error") != string::npos)
        {
            flag = false;
            cout<<str<<endl;
            while(!cin.eof())
            {
                getline(cin,str);
                cout<<str<<endl;
            }
        }
    }
    if(flag && cnt) system("syntax.exe");
    if(cnt==0) 
    {
        printf("请输入有效文件。");
    }
    return 0;
}
