#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    struct node *left;
    struct node *right;
} node_t;

typedef node_t bst_t;

int checkchild(bst_t *t){
    int cnt=0;
    if(t->left!=NULL){
        cnt+=1;
    }
    if(t->right!=NULL){
        cnt+=1;
    }
    return cnt;
}

int find(bst_t *t,int val){
    if(t==NULL){
        return 0;
    } else if(t->data==val){
        return 1;
    }
    if(val>t->data){
        return find(t->right,val);
    } else if(val<t->data){
        return find(t->left,val);
    }
}


bst_t *findparentnode(bst_t *t,int val){
    if(t==NULL){
        return NULL;
    }
    if((t->left!=NULL&&t->left->data==val)||(t->right!=NULL&&t->right->data==val)){
        return t;
    }
    if(t->data<val){
        return findparentnode(t->right,val);
    }
    if(t->data>val){
        return findparentnode(t->left,val);
    }
}

bst_t *find_node(bst_t *t,int val){
    if(t==NULL){
        return NULL;
    }
    if(t->data==val){
        return t;
    }
    if(t->data<val){
        return find_node(t->right,val);
    }
    if(t->data>val){
        return find_node(t->left,val);
    }
}

bst_t *find_minnode(bst_t *t){
    if(t->left==NULL){
        return t;
    } else{
        return find_minnode(t->left);
    }
}
bst_t *find_maxnode(bst_t *t){
    if(t->right==NULL){
        return t;
    } else{
        return find_maxnode(t->right);
    }
}

bst_t *createbstnode(int val){
    bst_t *newnode=(bst_t *)malloc(sizeof(bst_t));
    newnode->data=val;
    newnode->left=NULL;
    newnode->right=NULL;
    return newnode;
}

bst_t *insert(bst_t *t,int val){
    if(t==NULL){
        return createbstnode(val);
    }
    if(t->data<val){
        t->right=insert(t->right,val);
    }
    if(t->data>val){
        t->left=insert(t->left,val);
    }
    return t;
}

bst_t *del0(bst_t *t,int val){
    if(t==NULL||t->data==val){
        return NULL;
    } else if(find(t,val)==1){
        bst_t *markpos=findparentnode(t,val);
        //markpos->left->data==val? markpos->left=NULL:markpos->right=NULL;
        if(markpos->left!=NULL&&markpos->left->data==val){
            markpos->left=NULL;
        } else{
            markpos->right=NULL;
        }
    }
    return t;
}
bst_t *del1(bst_t *t,int val){
    if(t->data==val){
        if(t->left==NULL){
            return t->right;
        }
        if(t->right==NULL){
            return t->left;
        }
    } else if(find(t,val)==1){
        bst_t *parentpos=findparentnode(t,val);
        bst_t *markpos=find_node(t,val);
        if(parentpos->left!=NULL&&parentpos->left==markpos){
            if(markpos->left==NULL){
                parentpos->left=markpos->right;
            } else{
                parentpos->left=markpos->left;
            }
        } else{
            if(markpos->left==NULL){
                parentpos->right=markpos->right;
            } else{
                parentpos->left=markpos->left;
            }
        }
    }
    return t;
}
bst_t *del2(bst_t *t,int val){
    bst_t *parpos=findparentnode(t,val); //perent of markpos
    bst_t *temp; //next markpos data
    int numtemp; //will contain temp->data
    bst_t *markpos=find_node(t,val); //want to delete position
    temp=find_minnode(markpos->right); //min node of right markpos
    numtemp=temp->data;
    if(checkchild(temp)==0){
        t=del0(t,temp->data);
        markpos->data=numtemp;
    }else if(checkchild(temp)==1){
        t=del1(t,temp->data);
        markpos->data=numtemp;
    }
    return t;
}
bst_t *delete(bst_t *t,int val){
    bst_t *markpos=NULL;
    if(t==NULL){
        return t;
    }
    if(t->data==val){
        markpos=t;
    } else{
        markpos=find_node(t,val);
    }
    if(checkchild(markpos)==0){
        return del0(t,val);
    }
    else if(checkchild(markpos)==2){
        return del2(t,val);
    }
    else if(checkchild(markpos)==1){
        return del1(t,val);
    }
}

void treeprint(bst_t *t,int height) {
    if (t!=NULL) {
        for (int i=0;i<height;i++) {
            printf("     ");
        }
        printf("%d\n", t->data);
        treeprint(t->left,height+1);
        treeprint(t->right,height+1);
    }
}

int find_min(bst_t *t){
    return find_minnode(t)->data;
}
int find_max(bst_t *t){
    return find_maxnode(t)->data;
}

int main(void){
    bst_t *t=NULL;
    int n, i;
    int command, data;
    scanf("%d", &n);
    for(i=0;i<n;i++){
        scanf("%d",&command);
        switch(command){
            case 1:
                scanf("%d",&data);
                t=insert(t,data);
                break;
            case 2:
                scanf("%d",&data);
                t=delete(t,data);
                break;
            case 3:
                scanf("%d",&data);
                printf("%d\n", find(t,data));
                break;
            case 4:
                printf("%d\n", find_min(t));
                break;
            case 5:
                printf("%d\n", find_max(t));
                break;
        }
        //treeprint(t, 0);
    }
    return 0;
}
/* test case
16
1 1
1 2
1 3
1 4
4
5
1 5
1 6
1 7
1 8
1 9
1 10
1 11
1 12
4
5


16
1 82
1 79
1 66
1 78
3 79
2 79
3 79
1 93
1 99
1 5
1 61
1 68
1 3
5
2 99
5

7
3 11
1 3
1 90
1 43
3 50
4
5

13
1 50
1 8
1 61
1 1
1 35
1 87
2 50
3 50
2 8
2 61
3 8
3 87
3 61

*/