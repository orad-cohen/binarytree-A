#include "doctest.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <array>
#include "BinaryTree.hpp"
using namespace std;



using namespace ariel;



TEST_CASE("GOOD TREE"){
    BinaryTree<int> Int_Tree;
    Int_Tree.add_root(10);
    Int_Tree.add_left(10,15);
    Int_Tree.add_left(15,12);
    Int_Tree.add_right(10,7);
    Int_Tree.add_right(7,4);
    Int_Tree.add_left(7,2);
    Int_Tree.add_right(15,11);
    array<int,7> inorder={12,15,11,10,2,7,4};
    array<int,7> preorder={10,15,12,11,7,2,4};
    array<int,7> postorder={12,11,15,2,4,7,10};
    size_t index =0;
    cout<<Int_Tree<<endl;
    for(int& a : Int_Tree){
      cout<<a<<" ";
      CHECK_EQ(inorder.at(index++),a);
    }
    index=0;
    for(auto it=Int_Tree.begin_preorder(); it!=Int_Tree.end_preorder(); ++it){
      cout<<*it<<" ";
      CHECK_EQ(inorder.at(index++),*it);
    }
    index=0;
    for(auto it=Int_Tree.begin_postorder(); it!=Int_Tree.end_postorder(); ++it){
      cout<<*it<<" ";
      CHECK_EQ(inorder.at(index++),*it);
    }
  



}






