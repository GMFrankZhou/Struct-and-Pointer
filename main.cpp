#include <iostream>
#include <cstring>
using namespace std;

typedef struct node {
        struct node *lp=NULL;
        char c;
        struct node *rp=NULL;
} node;

void printchain(node *pointer){ 
    if (!pointer) {
        cout<<"\n";
        return;
    }
    cout <<pointer->c<<"\t";
    printchain(pointer->rp);
}
        
void freechain(node *pointer){
    if (!pointer) return;
    freechain(pointer->rp);
    free(pointer);
}

node* copychain(node *pointer){
    node *newchain=NULL;
    node *p1=pointer;
    node *p2=NULL;

    while (p1!=NULL){
        node *newnode=(node*)malloc(sizeof(node));
        newnode->c=p1->c;
        if (newchain==NULL){
            newchain=newnode;
            p2=newnode;
        } else {
            p2->rp=newnode;
            newnode->lp=p2;
            p2=newnode;
        }
        p1=p1->rp;
    }
    return newchain;
}

int insertchain(node **head,node *ins,node *des,bool leftright){
    if(ins==des) return 0;
    if((des->lp==ins)&&!leftright)return 0;
    if((des->rp==ins)&&leftright)return 0;
    
    //insert to the left
    if(!leftright){
        if (ins->lp) 
            ins->lp->rp=ins->rp; 
        else 
            *head=ins->rp;

        if (ins->rp) 
            ins->rp->lp=ins->lp;

        if (des->lp) 
            des->lp->rp=ins;
        else
            *head=ins;
        ins->lp=des->lp;
        des->lp=ins;
        ins->rp=des;
    }
    //insert to the right
    if(leftright==true){
        if (ins->lp) 
            ins->lp->rp=ins->rp; 
        else 
            *head=ins->rp;

        if (ins->rp) 
            ins->rp->lp=ins->lp;

        if (des->rp) des->rp->lp=ins;
        ins->rp=des->rp;
        ins->lp=des;
        des->rp=ins;
    }
    return 1;
}

node* assignchain(){
    string s;
    cout <<"Input nodes:";
    cin >>s;
    const char* ch=s.c_str();
    node *p=NULL;
    node *newchain=NULL;
    while (*ch!='\0'){
        node *newnode=(node*)malloc(sizeof(node));
        newnode->c=*ch;
        if (!newchain){
            newchain=newnode;
            p=newchain;
        } else {
            p->rp=newnode;
            newnode->lp=p;
            p=newnode;
        }
        ch++;
    }
    return newchain;
}

int nodepos(node* point){
    int pos;
    if (!point) return 0;
    pos=nodepos(point->lp)+1;
    return pos;
}

int main(){
    
    node *newchain;
    node *head=NULL;

    newchain=assignchain();
    head=newchain;
    printchain(head); 
    cout<<nodepos(head->rp->rp->lp);

}
