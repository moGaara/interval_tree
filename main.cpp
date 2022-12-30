#include <iostream>
using namespace std;
class range{
public:
    int high , low;
    range(int high = 0 , int low = 0):high{high},low{low}{}
};

class Node{
public:
    int Max;
    range *ranges;
    Node *lchild,*rchild;
    Node(): Max{0}, lchild{nullptr}, rchild{nullptr}, ranges{nullptr}{
    }
};

class IntervalTree{
private:
    Node *root;
    range arr[100];
    int cur_pos;
public:
    IntervalTree(): root{nullptr}{
        cur_pos = 0;
    }
    Node* Rinsert(Node *p , int low, int high)
    {
        Node *t;
        if(p == nullptr)
        {
            t = new Node();
            t->ranges = new range(high, low);
            t->Max = t->ranges->high;
            return t;
        }

        // travesre
        if(low < p->ranges->low) p->lchild =Rinsert(p->lchild , low , high);
        else p->rchild =Rinsert(p->rchild , low , high);



        // edite the new max
        if(p->lchild && p->rchild){
            if(p->Max <p->lchild->Max ||p->Max < p->rchild->Max  )p->Max = p->lchild->Max > p->rchild->Max? p->lchild->Max : p->rchild->Max;
        }
        else if(p->lchild){
            if(p->Max<p->lchild->Max) p->Max = p->lchild->Max;
        }
        else if(p->rchild){
            if(p->Max<p->rchild->Max) p->Max = p->rchild->Max;
        }


        return p;

    }
    bool check_overlap(range current_range, range target)
    {
        if ((current_range.low <= target.high && target.low <= current_range.high)
            || (target.low < current_range.low && target.high>current_range.low)
            || (target.low > current_range.low && target.low< current_range.high ))
            return true;
        return false;
    }
    range* iterative_search(Node* p, range i){
        while( (p!= nullptr) && (i.low > p->ranges->high || p->ranges
        ->low > i.high)){
            if(i.low > p->lchild->Max) p = p->rchild;
            else p = p->lchild;
        }
        return p->ranges;
    }
    range *getDeletedNodes(){
        return arr;
    }
    range* interval_search(Node* p, range i){
        if (p == nullptr) return nullptr;
        if (check_overlap(*(p->ranges), i))
            arr[cur_pos++] = *p->ranges;

        if (p->lchild != nullptr && p->lchild->Max >= i.low)
            return interval_search(p->lchild, i);

        return interval_search(p->rchild, i);
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


    Node* del(Node *r, int l, int h) {
        if (!r) {
            return nullptr;
        }
        if (l < r->ranges->low) {
            r->lchild = del(r->lchild, l, h);
        } else if (l >  r->ranges->low) {
            r->rchild = del(r->rchild, l, h);
        } else {
            if (h <  r->ranges->high) {
                r->lchild = del(r->lchild, l, h);
            } else if (h > r->ranges->high) {
                r->rchild = del(root->rchild, l, h);
            } else {
                if (r->lchild == nullptr)
                    return r->rchild;
                else if (r->rchild == nullptr)
                    return r->lchild;
                // Find the minimum value in the right subtree of root
                Node *curr = r->rchild;
                while (curr->lchild != nullptr) {
                    curr = curr->lchild;
                }
                r->ranges->low = curr->ranges->low;
                r->ranges->high = curr->ranges->high;
                r->rchild = del( r->rchild, r->ranges->low, r->ranges->high);
            }
        }
        return r;
    }

    void Inorder(Node *p)
    {
        if(p != nullptr){
            Inorder(p->lchild);
            cout << " " << '[' << p->ranges->low << ',' << p->ranges->high << ']' << "max = " << p->Max;
            Inorder(p->rchild);
        }
    }
    void SetRoot(Node *p){ root = p;}
    Node* GetRoot(){return root;}
};



int main() {
    IntervalTree t;
    t.SetRoot(t.Rinsert(t.GetRoot(), 15, 18));
    t.Rinsert(t.GetRoot() , 1,5);
    t.Rinsert(t.GetRoot() , 50,60);
    t.Rinsert(t.GetRoot() , 70,80);
    t.Rinsert(t.GetRoot() , 7,11);
    t.Rinsert(t.GetRoot() , 7,10);
    cout<<endl;
    t.Inorder(t.GetRoot());
    cout<<endl;
    t.del(t.GetRoot(),50,60);
    t.Inorder(t.GetRoot());
    cout<<endl;

    range target = {12 ,8};
    //range *answer = t.iterative_search(t.GetRoot() ,target);
    range *answer = t.interval_search(t.GetRoot() ,target);
    if(answer == nullptr)cout<<"no overlapping occur\n";
    else cout<<"overlaping occur with ["<<answer->low<<" , "<<answer->high<<"]\n";
    range *ans = t.getDeletedNodes();

    return 0;
}
