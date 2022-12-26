#include <iostream>
#include <stack>
using namespace std;
class range{
public:
    int high , low;
    range(int high , int low):high{high},low{low}{}
};

class Node{
public:
    int Max , low , high;

    Node *lchild,*rchild;
    Node(): Max{0},low{0} , high{0},lchild{nullptr}, rchild{nullptr}{
    }
};

class IntervalTree{
private:
    Node *root;
public:
    IntervalTree(): root{nullptr}{}
    Node* Rinsert(Node *p , int low, int high)
    {
        Node *t;
        if(p == NULL)
        {
            t = new Node();
            t->low = low;
            t->high = high;
            t->Max = high;
            return t;
        }

        if(low < p->low) p->lchild =Rinsert(p->lchild , low , high);
        else p->rchild =Rinsert(p->rchild , low , high);

        if(p->lchild && p->rchild){
            if(p->Max <p->lchild->Max ||p->Max < p->rchild->Max  )p->Max = p->lchild->Max > p->rchild->Max? p->lchild->Max : p->rchild->Max;
        }
        else if(p->lchild){
            if(p->Max<p->lchild->Max) p->Max = p->lchild->Max;
        }
        else if(p->rchild){
            if(p->Max<p->rchild->Max) p->Max = p->rchild->Max;
        }

        //if(p->Max < high) root->Max = high;

        return p;

    }

    Node* RecursiveSearch(Node* t, int key)
    {
        if(t == nullptr)return NULL;
        if(t->Max == key) return t;
        else if(key<t->Max) return RecursiveSearch(t->lchild , key);
        else return RecursiveSearch(t->rchild,key);
    }
    int height(Node *p)
    {
        int x = 0 , y = 0;
        if( p == nullptr) return 0;
        x = height(p->lchild);
        y = height(p->rchild);
        return x>y? x + 1 : y + 1;
    }
    Node* inpre(Node *p)
    {
        while( p && p->rchild != nullptr)
            p = p->rchild;
        return p;
    }
    Node* insucc(Node *p)
    {
        while( p && p->lchild != nullptr)
            p = p->lchild;
        return p;
    }
    Node* Delete(Node* p , int low , int high)
    {
        Node *q;
        if( p == nullptr)return nullptr;
        if(p->lchild == NULL && p->rchild == NULL)
        {
            if( p == root) root = NULL;
            p->Max=0;
            p->low=0;
            p->high=0;
            delete p;
            return NULL;
        }
        if(low < p->low && high < p->low) p->lchild = Delete(p->lchild , low,high);
        else if(low > p->high) p->rchild = Delete(p->rchild , low,high);
        else{
            if(height(p->lchild) > height(p->rchild))
            {
                q = inpre(p->lchild);
                //p->Max = q->Max;
                if(p->lchild && p->rchild){
                    p->Max = p->lchild->Max > p->rchild->Max? p->lchild->Max : p->rchild->Max;
                }
                else if(p->lchild){
                    p->Max = p->lchild->Max;
                }
                else if(p->rchild){
                    p->Max = p->rchild->Max;
                }
                //p->Max = p->lchild->Max > p->rchild->Max? p->lchild->Max : p->rchild->Max;
                p->low = q->low;
                p->high = q->high;
                p->lchild = Delete(p->lchild , q->low,q->high);
                if( (low < p->low && high > p->low) || (low > p->low && high > p->high))Delete(p,p->low,p->high);
            }
            else
            {
                q = insucc(p->rchild);
                //p->Max = q->Max;
                if(p->lchild && p->rchild){
                    p->Max = p->lchild->Max > p->rchild->Max? p->lchild->Max : p->rchild->Max;
                }
                else if(p->lchild){
                    p->Max = p->lchild->Max;
                }
                else if(p->rchild){
                    p->Max = p->rchild->Max;
                }
                p->low = q->low;
                p->high = q->high;
                p->rchild = Delete(p->rchild ,  q->low,q->high);
                if( (low < p->low && high > p->low) || (low > p->low && high > p->high) ||(low > p->low && high < p->high) ||(low == p->low && high == p->high))Delete(p,p->low,p->high);
            }

        }
        return p;
    }


    void Inorder(Node *p)
    {
        if(p != NULL){
            Inorder(p->lchild);
            cout <<" "<<'['<<p->low<<','<<p->high<<']'<<"max = "<<p->Max;
            Inorder(p->rchild);
        }
    }
    void SetRoot(Node *p){ root = p;}
    Node* GetRoot(){return root;}
};
int main() {
    IntervalTree t;
    t.SetRoot(t.Rinsert(t.GetRoot(), 17, 19));
    t.Rinsert(t.GetRoot() , 5,11);
    t.Rinsert(t.GetRoot() , 22,23);
    t.Rinsert(t.GetRoot() , 4,8);
    t.Rinsert(t.GetRoot() , 15,18);
    t.Rinsert(t.GetRoot() , 7,10);
    t.Inorder(t.GetRoot());
    t.Delete(t.GetRoot() , 16,18);
    cout<<endl;
    t.Inorder(t.GetRoot());
    cout<<endl;
    return 0;
}
