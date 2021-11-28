// You can add any members in the class.
// The following 4 functions will be called in test program.
#include <iostream>
#include <cstring>
using namespace std;

class Trie {
private:
    struct node{
        bool leafNode;
        node* letter[26];
        node(){
            leafNode=false;
            for(int i=0;i<26;++i) letter[i]=NULL;
        }
    };
    node*root;
public:
    Trie() {
        root=new node();
        root->leafNode=true;
    }

    void insert(char* word) {
        node*p=root;
        root->leafNode=false;
        for(int i=0;word[i]!='\0';i++){
            if(p->letter[word[i]-'a']==NULL) 
                p->letter[word[i]-'a']=new node();
            p=p->letter[word[i]-'a'];
        }
        p->leafNode=true;
    }
    
    bool search(char* word) {
        node*p=root;
        if(root==NULL) return false;
        for(int i=0;word[i]!='\0';++i){
            if(p->letter[word[i]-'a']==NULL) return false;
            p=p->letter[word[i]-'a'];
        }
        if(p->leafNode) return true;
        return false;
    }
    
    bool startsWith(char* prefix) {
        node*p=root;
        if(root==NULL) return false;
        for(int i=0;prefix[i]!='\0';++i){
            if(p->letter[prefix[i]-'a']==NULL) return false;
            p=p->letter[prefix[i]-'a'];
        }
        return true;     
    }
};

int main(){
    int x;
    Trie trie;
    trie.insert("abc");
    cout<<trie.search("abc")<<endl;
    cout<<trie.search("ab")<<endl;
    cout<<trie.startsWith("abc")<<endl;
}