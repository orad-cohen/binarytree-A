#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <queue>
using namespace std;



namespace ariel{
    template <typename T>
class BinaryTree{
    private:
    struct Tree{
        T Value;
        Tree *parent;
        Tree *left;
        Tree *right;
        Tree(const T& val):Value(val){
            parent=nullptr;
            left=nullptr;
            right=nullptr;

        }
    };
    

    public:
    struct Tree * root;
    Tree * FindTree(Tree* node, T data){ 
              
        if(!node){
            return nullptr;
        }
        if(
            node->Value==data){
            
            return node;
        }
       
        Tree * templeft = FindTree(node->left,data);
        Tree * tempright = FindTree(node->right,data);
        
        
        if(templeft){
           
            return templeft;
        }
        
        if(tempright){
            

            return tempright;
        }
        
        
        return nullptr;

    }
    BinaryTree(Tree * n=nullptr):root(n){

    }
    ~BinaryTree(){
        //desctruct(root);

    }
    void desctruct(Tree * bye){
        if(bye->left){
            desctruct(bye->left);
        }
        if(bye->right){
            desctruct(bye->right);
        }
        delete bye;
    }


    BinaryTree<T>& add_root(T data){        
        struct Tree * temp = new Tree(data);        
        temp->Value = data;        
        root = temp;              
        return *this;
    }
        
    
    BinaryTree<T> add_left(T p ,T a){
        
        struct Tree * xparent = FindTree(root,p);
        if(xparent->left){
            xparent-> left->Value =a;
        }
        else{
            struct Tree * child = new Tree(a);
            child->Value = a;
            child->parent = xparent;        
            xparent->left = child;         
        }
        
       
        return *this;
    }
        
    
    BinaryTree<T> add_right(T p,T a){
        
        struct Tree * xparent = FindTree(root,p);
        
        if(xparent->right){
            xparent-> right->Value =a;
        }
        else{
        struct Tree * child = new Tree(a);
        child->Value = a;
        child->parent = xparent;        
        xparent->right = child;         
        }
            
        
        return *this;

    }
       
    
    
    
    enum trav{PRE,IN,POST};

    class iterator{
        struct Tree * Current;
        struct Tree * Previous;
        
        enum trav _Order;
        public:
        iterator(enum trav order =trav::PRE , Tree * current =nullptr):Current(current),_Order(order){
            Previous=nullptr;
            if(_Order==trav::POST){                
                
                ++*this;
            }
            else if(_Order==trav::IN){
                while(Current->left){
                    goLeft();
                }
            }
            
        };
        iterator& operator++(){        
            if(_Order==trav::POST){
                postorder();
            }
            else if(_Order==trav::PRE){
                preorder();
            }
            else{                
                inorder();                
            }

            
            return *this;
        }

        void preorder(){
            if(Current->right!=Previous&&Current->left!=Previous&&Current->left){              
                goLeft();}
            else if(Current->right!=Previous&&Current->right){
                    goRight();}
            else if(!Current->parent){
                Current =nullptr;}
            else{
                goUp();
                ++*this;}
        }

        void inorder(){
           if(Current->left!=Previous&&Current->left&&Current->right!=Previous){
               
                while(Current->left){
                    goLeft();
                }
            }
            else if(Current->right!=Previous&&Current->right){
               
                goRight();
                while(Current->left){
                    goLeft();
                }
            }            
            else{
                               
                if(!Current->parent){
                    Current=nullptr;
                }
                else{
                goUp();
                if(Current->right&&Current->right==Previous){
                    ++*this;
                }
                }
                
            }
        }
        
        void postorder(){

            if(Current->left!=Previous&&Current->left&&Current->right!=Previous){
               
                while(Current->left){
                    goLeft();
                }
            }
            else if(Current->right!=Previous&&Current->right){
               
                goRight();
                while(Current->left){
                    goLeft();
                }
            }            
            else{
                               
                if(!Current->parent){
                    Current=nullptr;
                }
                else{
                goUp();
                if(Current->right&&Current->right!=Previous){
                    ++*this;
                }
                }
                
            }

            
        }

        void goLeft(){
            Previous=Current;
            Current=Current->left;
        }
        void goRight(){
            Previous=Current;
            Current=Current->right;
        }
        void goUp(){
            Previous = Current;
            Current = Current->parent;
        }
        
        T& operator*(){
            return Current->Value;
        }
        T* operator->(){
            return &Current->Value;
        }
        const iterator operator++(int) {
           
			iterator tmp= *this;
            ++tmp;
			return tmp;
		}


		bool operator!=(const iterator& other) const {
           
            //if(!Current){return false;}
            
			return Current!=other.Current;
		}

        T size(){
            return 0;
        }


    };   


    
    iterator begin(){
        
        return iterator{trav::IN,root};
    }
    iterator end(){
        
        return iterator{};
    }
    int size();




    
    
        
    iterator begin_preorder(){
            return iterator{trav::PRE,root};
    }
    iterator end_preorder(){
            return iterator{};
    }
    
    iterator begin_inorder(){
            return iterator{trav::IN,root};
    }

    
    iterator end_inorder(){
        return iterator{};
    }

    iterator begin_postorder(){
        return iterator{trav::POST,root};
    }

    
    iterator end_postorder(){
        return iterator{};
    }
    
    
    int getDepth(Tree * branch,int count){
        
        if(!branch){
            return count-1;
        }
        
        
        return max(getDepth(branch->left,count+1),getDepth(branch->right,count+1));
        

    }
    void getQ(queue<T> * g,Tree * te, int depth,int cutoff){
        
        if(depth==cutoff){
            
            g->push(te->Value);
        }
        else{
            if(te->left){
                getQ(g,te->left,depth+1,cutoff);
            }
            else{
                g->push(root->Value);
            }
            if(te->right){
                
                getQ(g,te->right,depth+1,cutoff);
            }
            else{
                g->push(root->Value);
            }



        }    
        
        
        



    }
    

    friend ostream& operator<<(ostream& os, BinaryTree<T> m){
        queue<T> g;
        
        int depth = m.getDepth(m.root,0);
        Tree * current = m.root;
        
        for (size_t i = 0; i <= depth; i++)
        {
            m.getQ(&g,m.root,0,i);
        }
        
        T x;
        
        while(!g.empty()){
            x = g.front();
            g.pop();
            os <<x<<" ";
        }
      
        
            
        
        

 
       
        return os;
    }
    

    
       
};
}
