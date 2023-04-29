#include<iostream>
#include<map>
#include<vector>
using namespace std;
class state{
    public:
    int val;
    bool accept;
};
class NFA{
    public:
    map<int,map<char,vector<state*>>>m;
    string ans="hellohionetwo three";
    int count=1;
    void createNFA(string s,bool b=false,int idx=1){
        state *st=new state();
        st->val=0;
        int newidx=0;
        for(int i=0;i<s.length();i++){
            if((s[i]=='a' || s[i]=='b') && (s[i+1]!='*' && s[i+1]!='+')){
                state *x=new state();
                x->val=count;
                if(i!=0 && s[i-1]=='*') m[idx-1][s[i]].push_back(x);
                else m[count-1][s[i]].push_back(x);
                count++;
                if(s[i+1]=='\0' ||s[i]==')'||s[i+1]=='(' || s[i+1]=='+'){
                    state *x=new state();
                    x->val=newidx;
                    m[count-1]['-'].push_back(x);
                    count++;
                }
            }
            else if((s[i]=='a' || s[i]=='b') && s[i+1]=='+'){
                state *x=new state();
                x->val=count;
                m[count-1][s[i]].push_back(x);
                count++;
                x=new state();
                x->val=count;
                x->accept=true;
                m[count-1]['-'].push_back(x);
                count++;
                if(newidx!=0){
                    state *x=new state();
                    x->val=newidx;
                    m[count-1]['-'].push_back(x);
                }
                newidx=count-1;
            }
            else if(s[i]=='+'){
                state *x=new state();
                x->val=count;
                m[idx-1]['-'].push_back(x);
                if(b){
                    state *y=new state();
                    y->val=idx-1;
                    m[newidx]['-'].push_back(y);
                }
                count++;
            }
            else if((s[i]=='a' || s[i]=='b' )&& s[i+1]=='*'){
                state *x=new state();
                x->val=count-1;
                x->accept=true;
                m[count-1]['-'].push_back(x);
                m[count-1][s[i]].push_back(x);
            }
            else if(s[i]=='('){
                int j=i+1;
                int count1=0;
                while(s[j]!=')' || count1!=0){
                    if(s[j]=='(')count1++;
                    else if(s[j]==')')count1--;
                    j++;
                }
                string s1=s.substr(i+1,j-i-1);
                bool x=false;
                if(s[j-i+1]=='*')x=true;
                int temp=count;
                createNFA(s1,x,temp);
                i=j-1;
            }
            else if(s[i]==')' && s[i+1]!='*'){
                state *x=new state();
                x->val=count;
                m[idx-1]['-'].push_back(x);
                if(b){
                    state *y=new state();
                    y->val=idx-1;
                    m[count-1]['-'].push_back(y);
                }
                count++;
            }
            // if(b) count++;
        }
    }
    string shortest(){
        for(auto x:m){
            
        }
        return ans;
    }
    void print(){
        for(auto x:m){
            cout<<x.first<<endl;
            for(auto y:x.second){
                cout<<y.first<<" v "<<endl;
                for(auto p:y.second){
                    cout<<p->val<<" ";
                }
                cout<<endl;
            }
        }
    }
};
int main(){
    string s;
    cin>>s;
    NFA hi;
    hi.createNFA(s);
    hi.print();
    // cout<<hi.shortString(*(hi.m[0]['-'][0]),"")<<endl;
    hi.print();
return 0;
}