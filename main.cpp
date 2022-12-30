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
    int nodeNum;
public:
    IntervalTree(): root{nullptr}{
        cur_pos = 0;
        nodeNum = 1;
    }
    Node* Rinsert(Node *p , int low, int high)
    {
        Node *t;
        if(p == nullptr)
        {
            t = new Node();
            t->ranges = new range(high, low);
            t->Max = t->ranges->high;
            nodeNum++;
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
    int getNumberOfNodes(){return nodeNum;}


    bool check_overlap(range current_range, range target)
    {
        if ((current_range.low <= target.high && target.low <= current_range.high)
            || (target.low < current_range.low && target.high>current_range.low)
            || (target.low > current_range.low && target.low< current_range.high ))
            return true;
        return false;
    }
    range* iterative_search(Node* p, range i){
        while( p && (i.low > p->ranges->high || p->ranges->low > i.high)){
            if(i.low <= p->lchild->Max && p->lchild) p = p->lchild;
            else p = p->rchild;
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

        if (p->lchild && p->lchild->Max >= i.low)
            return interval_search(p->lchild, i);
        else
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

    Node* Delete(Node* p , int target_low , int target_high){
        Node* q = nullptr;
        if( p == nullptr )return nullptr;
        if( p ->rchild == nullptr && p->lchild == nullptr){
            if( p == root) root = nullptr;
            delete p;
            return nullptr;
        }
        if(target_low < p->ranges->low) p->lchild = Delete(p->lchild , target_low,target_high);
        else if(target_low > p->ranges->low)p->rchild = Delete(p->rchild,target_low,target_high);
        else{
            if(height(p->lchild) > height(p->rchild))
            {
                q = inpre(p->lchild);
                if(p->lchild && p->rchild){
                    if(p->Max <p->lchild->Max ||p->Max < p->rchild->Max  )p->Max = p->lchild->Max > p->rchild->Max? p->lchild->Max : p->rchild->Max;
                }
                else if(p->lchild){
                    if(p->Max<p->lchild->Max) p->Max = p->lchild->Max;
                }
                else if(p->rchild){
                    if(p->Max<p->rchild->Max) p->Max = p->rchild->Max;
                }
                p->ranges = q->ranges;
                p->lchild = Delete(p->lchild , q->ranges->low,q->ranges->high);
            }
            else
            {
                q = insucc(p->rchild);
                if(p->lchild && p->rchild){
                    if(p->Max <p->lchild->Max ||p->Max < p->rchild->Max  )p->Max = p->lchild->Max > p->rchild->Max? p->lchild->Max : p->rchild->Max;
                }
                else if(p->lchild){
                    if(p->Max<p->lchild->Max) p->Max = p->lchild->Max;
                }
                else if(p->rchild){
                    if(p->Max<p->rchild->Max) p->Max = p->rchild->Max;
                }
                p->ranges= q->ranges;
                p->rchild = Delete(p->rchild , q->ranges->low,q->ranges->high);
            }
        }

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
    int GetCurrentPosition() const{return cur_pos;}
    void SetRoot(Node *p){ root = p;}
    Node* GetRoot(){return root;}
};

void search_logic(IntervalTree t , range target){

    t.interval_search(t.GetRoot() , target);
    range *deleted_nodes = t.getDeletedNodes();
    if( t.GetCurrentPosition() == 0)cout<<"No overlapping occured\n";
    else{
        cout<<" tree inorder before search: ";
        t.Inorder(t.GetRoot());cout<<endl;
        cout<<"interval ["<<target.low<<" , "<<target.high<<"]\n";
        cout<<"overlapped with intervals: ";
        for(int i = 0 ; i < t.GetCurrentPosition(); i++){
            cout<<"["<<deleted_nodes[i].low<<" , "<<deleted_nodes[i].high<<"]\n";
            t.Delete(t.GetRoot() , deleted_nodes[i].low,deleted_nodes[i].high);
        }
        cout<<"tree inorder after deleting the overlapped intervals: ";
        t.Inorder(t.GetRoot());cout<<endl;
        for(int i = 0 ; i < t.GetCurrentPosition() ; i++){
            t.Rinsert(t.GetRoot(),deleted_nodes[i].low,deleted_nodes[i].high);
        }
    }
}


void searchLogic(IntervalTree t , range target){
    int n = t.getNumberOfNodes();
    int curr = 0;
    range *deleted_nodes = t.getDeletedNodes();
    while(n--){
        t.interval_search(t.GetRoot() , target);
        deleted_nodes = t.getDeletedNodes();
        for(int i = curr ; i < t.GetCurrentPosition(); i++)
        {
            t.Delete(t.GetRoot() , deleted_nodes[i].low,deleted_nodes[i].high);
        }
        curr += t.GetCurrentPosition() - 1;

        if(t.getNumberOfNodes() == 0) break;
    }
    cout<<"tree inorder after deleting the overlapped intervals: " <<endl;
    t.Inorder(t.GetRoot());cout<<endl;
    for(int i = 0 ; i < t.GetCurrentPosition() ; i++)
    {
        t.Rinsert(t.GetRoot(),deleted_nodes[i].low,deleted_nodes[i].high);
    }
    cout<<"Tree inorder after inserting  the deleted intervals: " <<endl;
    t.Inorder(t.GetRoot());
    cout << endl;
}

int main() {
    IntervalTree t;
    t.SetRoot(t.Rinsert(t.GetRoot(), 17, 19));
    t.Rinsert(t.GetRoot() , 5,11);
    t.Rinsert(t.GetRoot() , 30,22);
    t.Rinsert(t.GetRoot() , 15,18);
    t.Rinsert(t.GetRoot() , 7,10);
    t.Rinsert(t.GetRoot() , 22,29);

    t.Inorder(t.GetRoot());
    cout<<endl;

    range target = {20 ,10};

    searchLogic(t,target);



    /*range *answer = t.iterative_search(t.GetRoot() ,target);
    range *answer = t.interval_search(t.GetRoot() ,target);
    if(answer == nullptr)cout<<"no overlapping occur\n";
    else cout<<"overlaping occur with ["<<answer->low<<" , "<<answer->high<<"]\n";
    range *ans = t.getDeletedNodes();*/

    return 0;
}
