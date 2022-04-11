#include<bits/stdc++.h>
using namespace std;
struct node
{
    bool is_data;
    set<int> st;
    map<int,pair<node*,node*>> mp;
    node* par;
};
int d,t,c1=0,c2=0;
node* root =new node;
void dis()
{
    cout<<c1<<' '<<c2<<' ';

    auto it=root->st.begin();
    while(it!=root->st.end())
    {
        cout<<*it<<' ';
        it++;

    }
    cout<<'\n';
    return;
}
void split(node* x)
{
    if(x->is_data==1)
    {
        c2++;
        auto y=new node;
        y->is_data=1;
        auto it=x->st.begin();
        for(int i=0;i<d;i++)it++;
        for(int i=0;i<d+1;i++)
        {
            y->st.insert(*it);
            it++;
        }
        it=y->st.begin();
        for(int i=0;i<d+1;i++)
        {
            x->st.erase(*it);
            it++;
        }
        if(x->par==NULL)
        {
            node* yy=new node;
            c1++;
            yy->st.insert(*(y->st.begin()));
            yy->mp[*(y->st.begin())].first=x;
            yy->mp[*(y->st.begin())].second=y;
            root=yy;
            yy->is_data=0;
            yy->par=NULL;
            x->par=yy;
            y->par=yy;
            return;
        }
        auto parr=x->par;
        pair<int,pair<node*,node*>> yy={*(y->st.begin()),{x,y}};
        parr->mp.insert(yy);
        parr->st.insert(yy.first);
        it=parr->st.find(yy.first);
        it++;
        if(it!=parr->st.end())
        {
            parr->mp[*it].first=y;
        }
        y->par=x->par;
        if(parr->st.size()==2*t+2)split(parr);
    }
    else
    {

        c1++;
        auto y=new node;
        y->par=x->par;
        y->is_data=0;
        auto it=x->st.begin();
        auto it2=x->mp.begin();
        for(int i=0;i<t+1;i++)it++,it2++;
        for(int i=0;i<t+1;i++)
        {
            y->st.insert(*it);
            y->mp.insert(*it2);
            it++;
            it2++;
        }
        it=y->st.begin();
        it2=y->mp.begin();
        for(int i=0;i<t+1;i++)
        {
            x->st.erase(*it);
            x->mp[(*it2).first].first->par=y;
            x->mp[(*it2).first].second->par=y;
            x->mp.erase(it2);
            it++;
            it2++;
        }

        if(x->par==NULL)
        {
            c1++;
            node* yy=new node;
            int kk;
            auto it=x->st.end();
            it--;
            kk=*it;
            yy->st.insert(kk);
            yy->mp[kk]={x,y};
            auto it2=x->mp.end();
            it2++;
            yy->par=NULL;
            x->par=yy;
            y->par=yy;
            x->st.erase(it);
            x->mp.erase(it2);
            root=yy;
            return;
        }
        auto parr=x->par;
        int kk;
        it=x->st.end();

        it--;
        kk=*it;
        parr->st.insert(kk);
        parr->mp[kk]={x,y};
        auto itt=parr->st.find(kk);
        itt++;
        if(itt!=parr->st.end())
        {
            parr->mp[*itt].first=y;
        }
        if(parr->st.size()==2*t+2)split(parr);
    }
    return;
}
void ins(int x)
{
    if(root->is_data==1)
    {
        if(root->st.size()==0)c2++;
        root->st.insert(x);
        if(root->st.size()==2*d+1)
        {
            split(root);
        }
    }
    else
    {
        auto temp=root;
        while(temp->is_data==0)
        {
            auto it=temp->st.begin();
            int xmin=*it; it=temp->st.end(); it--;
            int xmax=*it;
            if(x<xmin) temp=temp->mp[xmin].first;
            else if(x>xmax) temp=temp->mp[xmax].second;
            else
            {
                int xx=*(temp->st.upper_bound(x));
                temp=temp->mp[xx].first;
            }
        }
        temp->st.insert(x);
        if(temp->st.size()==2*d+1)
        split(temp);
    }
    return;
}
int main()
{
cin>>d>>t;
    root->is_data=1;
    root->par=NULL;
    while(1)
    {
        int ty;
        cin>>ty;
        if(ty==1)
        {
            int x;
            cin>>x;
            ins(x);
        }
        if(ty==2)
        {
            dis();
        }

        if(ty==3)break;
    }
    return 0;
}
