#include <iostream>
using namespace std;

typedef struct node {
        struct node *lp=NULL;
        char c;
        struct node *rp=NULL;
} node;

void printchain(node *pointer){ 
    node *p=pointer;
    while (p!=NULL){
        cout <<p->c<<"\t";
        p=p->rp;
    }
    cout<<"\n";
}

void freechain(node *pointer){
    if (pointer==NULL) return;
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

void insertchain(node **head,node *ins,node *des,bool leftright){
    if(ins==des) return;
    if((des->lp==ins)&&(leftright==false))return;
    if((des->rp==ins)&&(leftright==true))return;
    
    //insert to the left
    if(leftright==false){
        if (ins->lp!=NULL) 
            ins->lp->rp=ins->rp; 
        else 
            *head=ins->rp;

        if (ins->rp!=NULL) 
            ins->rp->lp=ins->lp;

        if (des->lp!=NULL) 
            des->lp->rp=ins;
        else
            *head=ins;
        ins->lp=des->lp;
        des->lp=ins;
        ins->rp=des;
    }
    //insert to the right
    if(leftright==true){
        if (ins->lp!=NULL) 
            ins->lp->rp=ins->rp; 
        else 
            *head=ins->rp;

        if (ins->rp!=NULL) 
            ins->rp->lp=ins->lp;

        if (des->rp!=NULL) des->rp->lp=ins;
        ins->rp=des->rp;
        ins->lp=des;
        des->rp=ins;
    }
}

int main(){

    node b1;
    node b2;
    node b3;
    node b4;
    node *newchain;
    node *head=&b1;


    b1.lp=NULL;
    b1.c='S';
    b1.rp=&b2;

    b2.lp=&b1;
    b2.c='M';
    b2.rp=&b3;

    b3.lp=&b2;
    b3.c='L';
    b3.rp=&b4;

    b4.lp=&b3;
    b4.c='X';
    b4.rp=NULL;

    printchain(&b1); 
    insertchain(&head,&b1,&b4,true);
    printchain(head);

    newchain=copychain(head);
    printchain(newchain);
    freechain(newchain);
    printchain(newchain);
}