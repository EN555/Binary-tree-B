//
// Created by eviat on 5/21/2021.
//

#include "doctest.h"
#include "BinaryTree.hpp"
#include "preorder_traversal.hpp"
#include "postorder_traversal.hpp"
#include "inorder_traversal.hpp"
#include<iostream>

using namespace ariel;
using namespace std;

/*
 * check ints order
 *check string order
 * check double order
 * check objects order
 */

//-----------------helper struct for tests-------------------
struct keep_num{
    int val;
};

bool operator==(const keep_num& other1, const keep_num& other2){
    return (other1.val) == (other2.val);
}

//--------------------------------------------------------------

TEST_CASE("Tree Building") {    //root left right

    //------------Check Root---------------
    //          ---string---
    BinaryTree<string> tree_of_strings;

    tree_of_strings.add_root("root").add_root("hi").add_root("bi").add_root("ls")
            .add_root("pt").add_root("pp");
    auto iter_ = tree_of_strings.begin();
            CHECK(!(*iter_).compare("pp"));
    //check if the rest of the tree change or only the root
    tree_of_strings.add_left("pp","ls").add_root("rr").add_right("rr","lr");
    auto it_ = tree_of_strings.begin();
    // <ls, rr , lr>
            CHECK(!(*it_).compare("ls"));
            CHECK(!(*(++it_)).compare("rr"));
            CHECK(!(*(++it_)).compare("lr"));
    //add to non exist location
    CHECK_THROWS(tree_of_strings.add_right("ko","lr"));
    CHECK_THROWS(tree_of_strings.add_right("pp","ls"));
    CHECK_THROWS(tree_of_strings.add_left("pp","lc"));
    CHECK_THROWS(tree_of_strings.add_right("pp","lq"));
    CHECK_THROWS(tree_of_strings.add_left("pp","lk"));
    CHECK_THROWS(tree_of_strings.add_right("pp","lx"));

    //          ---int---
    BinaryTree<int> tree_of_ints;
    tree_of_ints.add_root(10).add_root(9).add_root(111).add_root(5)
            .add_root(6).add_root(1).add_root(28).add_root(91);
    CHECK(*(tree_of_ints.begin()) == 91);
            //check if the rest of the tree change or only the root
    tree_of_ints.add_left(91,10).add_root(9).add_right(9,111);
    auto it = tree_of_ints.begin();
    // <10, 9 , 11>
    CHECK(*it == 10);
    CHECK(*(++it) == 9);
    CHECK(*(++it) == 111);
    //add to non exist location
    CHECK_THROWS(tree_of_ints.add_left(1000,10));
    CHECK_THROWS(tree_of_ints.add_right(131,10));
    CHECK_THROWS(tree_of_ints.add_left(-7,10));
    CHECK_THROWS(tree_of_ints.add_right(91,10));
    CHECK_THROWS(tree_of_ints.add_left(91,10));
    CHECK_THROWS(tree_of_ints.add_right(-8,10));

    //          ---double---
    BinaryTree<double> tree_of_doubles;
    tree_of_doubles.add_root(10.1).add_root(9.2).add_root(11.5).add_root(5.3)
            .add_root(11.5);
    auto iter = tree_of_doubles.begin();
    CHECK(*iter == 11.5);
    //check if the rest of the tree change or only the root
    tree_of_doubles.add_left(11.5,10.5).add_root(9.2).add_right(9.2,111.6);
    auto iter_oth = tree_of_doubles.begin();
    // <10.5, 9.2 , 111.6>
            CHECK(*iter_oth == 10.5);
            CHECK(*(++iter_oth) == 9.2);
            CHECK(*(++iter_oth) == 111.6);
    //add to non exist location
    CHECK_THROWS(tree_of_doubles.add_left(11.5,10.4));
    CHECK_THROWS(tree_of_doubles.add_right(11.5,10.3));
    CHECK_THROWS(tree_of_doubles.add_left(11.5,10.9));
    CHECK_THROWS(tree_of_doubles.add_right(11.5,11.2));
    CHECK_THROWS(tree_of_doubles.add_left(11.5,13.2));
    CHECK_THROWS(tree_of_doubles.add_right(11.5,13.5));
}


TEST_CASE("pre_order") {    //root left right

    //----------------CHECK STRINGS----------------------//

    //------------tree----------------
    BinaryTree<string> tree_of_strings;
    tree_of_strings.add_root("root").add_left("root", "hi").add_left("hi", "bi").add_right("hi", "ls")
            .add_right("ls","pt" ).add_left("ls", "pp");
    //--------------------------------
    vector<string> res{"root", "hi", "bi", "ls", "pp", "pt"};
    auto oth = res.begin();
    int counter=0;
    for(auto it = tree_of_strings.begin_preorder();counter< 3; ++it){
                CHECK(!(*it).compare(*oth));
        counter++;
        ++oth;
    }

    //----------------CHECK INTEGERS NUMBERS----------------------//

    //------------tree----------------
    BinaryTree<int> tree_of_ints;
    tree_of_ints.add_root(10).add_left(10, 9).add_right(10, 11).add_left(9, 5)
            .add_right(11, 6).add_left(6, 1).add_left(1, 28).add_right(28, 91);
    //--------------------------------
    vector<int> vec{10, 9, 5, 11, 6, 1, 28, 91};
    auto ot = vec.begin();
    for(auto it = tree_of_ints.begin_preorder(); it != tree_of_ints.end_preorder(); ++it){
                CHECK(*it == *ot);
                ++ot;
    }
    //----------------CHECK DOUBLE NUMBERS----------------------//

    //------------tree----------------
    BinaryTree<double> tree_of_doubles;
    tree_of_doubles.add_root(10.1).add_left(10.1, 9.2).add_right(10.1, 11.5).add_left(9.2, 5.3)
            .add_right(11.5, 6).add_left(6, 1).add_left(1, 28).add_right(28, 91);
    //--------------------------------
    vector<double> vec_{10.1, 9.2, 5.3, 11.5, 6., 1, 28, 91};
    auto ot_ = vec_.begin();
    for(auto it = tree_of_doubles.begin_preorder(); it != tree_of_doubles.end_preorder(); ++it){
                CHECK(*it == *ot_);
        ++ot_;
    }

    //----------------CHECK OBJECTS----------------------//

    keep_num n1;
    keep_num n2;
    keep_num n3;
    keep_num n4;
    keep_num n5;
    keep_num n6;
    keep_num n7;
    keep_num n8;
    n1.val =10;
    n2.val = 9;
    n3.val =5;
    n4.val =11;
    n5.val =6;
    n6.val =1;
    n7.val =28;
    n8.val =91;

    //------------tree----------------
    BinaryTree<keep_num> tree_of_objects;
    tree_of_objects.add_root(n1).add_left(n1,n2).add_right(n1, n3).add_left(n3, n4)
            .add_right(n3, n5).add_left(n5, n6).add_left(n6, n7).add_right(n7, n8);
    //--------------------------------
    vector<keep_num> vect{n1, n2, n3, n4, n5, n6, n7, n8};
    auto ott = vect.begin();
    for(auto it = tree_of_objects.begin_preorder(); it != tree_of_objects.end_preorder(); ++it){
                CHECK((*it).val == ott->val);
        ++ott;
    }

}

TEST_CASE("in_order"){

    //----------------CHECK STRINGS----------------------//

    //------------tree----------------
    BinaryTree<string> tree_of_strings;
    tree_of_strings.add_root("root").add_left("root", "hi").add_left("hi", "bi").add_right("hi", "ls")
            .add_right("ls","pt" ).add_left("ls", "pp");
    //--------------------------------
    vector<string> res{"bi", "hi", "pp", "ls", "pt", "root"};
    auto oth = res.begin();
    int counter = 6;
    for(auto it = tree_of_strings.begin_inorder(); counter < 6; ++it){
                CHECK(!(*it).compare(*oth));
        counter++;
        ++oth;
    }

    //----------------CHECK INTEGERS NUMBERS----------------------//

    //------------tree----------------
    BinaryTree<int> tree_of_ints;
    tree_of_ints.add_root(10).add_left(10, 9).add_right(10, 11).add_left(9, 5)
            .add_right(11, 6).add_left(6, 1).add_left(1, 28).add_right(28, 91);
    //--------------------------------
    vector<int> vec{5, 9, 10, 11, 28, 91, 1, 6};
    auto ot = vec.begin();
    for(auto it = tree_of_ints.begin_inorder(); it != tree_of_ints.end_inorder(); ++it){
                CHECK(*it == *ot);
        ++ot;
    }
    //----------------CHECK DOUBLE NUMBERS----------------------//

    //------------tree----------------
    BinaryTree<double> tree_of_doubles;
    tree_of_doubles.add_root(10.1).add_left(10.1, 9.2).add_right(10.1, 11.5).add_left(9.2, 5.3)
            .add_right(11.5, 6).add_left(6, 1).add_left(1, 28).add_right(28, 91);
    //--------------------------------
    vector<double> vec_{5.3, 9.2, 10.1, 11.5, 28, 91, 1, 6};
    auto ot_ = vec_.begin();
    for(auto it = tree_of_doubles.begin_inorder(); it != tree_of_doubles.end_inorder(); ++it){
                CHECK(*it == *ot_);
        ++ot_;
    }

    //----------------CHECK OBJECTS----------------------//

    keep_num n1;
    keep_num n2;
    keep_num n3;
    keep_num n4;
    keep_num n5;
    keep_num n6;
    keep_num n7;
    keep_num n8;
    n1.val =10;
    n2.val = 9;
    n3.val =5;
    n4.val =11;
    n5.val =6;
    n6.val =1;
    n7.val =28;
    n8.val =91;

    //------------tree----------------
    BinaryTree<keep_num> tree_of_objects;
    tree_of_objects.add_root(n1).add_left(n1,n2).add_right(n1, n3).add_left(n3, n4)
            .add_right(n3, n5).add_left(n5, n6).add_left(n6, n7).add_right(n7, n8);
    //--------------------------------
    vector<keep_num> vect{n2, n1, n4, n3, n7, n8, n6, n5};
    auto ott = vect.begin();
    for(auto it = tree_of_objects.begin_inorder(); it != tree_of_objects.end_inorder(); ++it){
                CHECK((*it).val == (*ott).val);
        ++ott;
    }

}


TEST_CASE("post_order"){

    //----------------CHECK STRINGS----------------------//

    //------------tree----------------
    BinaryTree<string> tree_of_strings;
    tree_of_strings.add_root("root").add_left("root", "hi").add_left("hi", "bi").add_right("hi", "ls")
            .add_right("ls","pt" ).add_left("ls", "pp");
    //--------------------------------
    vector<string> res{"root", "hi", "bi", "ls", "pp", "pt"};
    auto oth = res.begin();
    int counter = 6;
    for(auto it = tree_of_strings.begin_inorder(); counter < 6; ++it){
                CHECK(!(*it).compare(*oth));
        counter++;
        ++oth;
    }

    //----------------CHECK INTEGERS NUMBERS----------------------//

    //------------tree----------------
    BinaryTree<int> tree_of_ints;
    tree_of_ints.add_root(10).add_left(10, 9).add_right(10, 11).add_left(9, 5)
            .add_right(11, 6).add_left(6, 1).add_left(1, 28).add_right(28, 91);
    //--------------------------------
    vector<int> vec{5, 9, 91, 28, 1, 6, 11, 10};
    auto ot = vec.begin();
    for(auto it = tree_of_ints.begin_postorder(); it != tree_of_ints.end_postorder(); ++it){
                CHECK(*it == *ot);
        ++ot;
    }
    //----------------CHECK DOUBLE NUMBERS----------------------//

    //------------tree----------------
    BinaryTree<double> tree_of_doubles;
    tree_of_doubles.add_root(10.1).add_left(10.1, 9.2).add_right(10.1, 11.5).add_left(9.2, 5.3)
            .add_right(11.5, 6).add_left(6, 1).add_left(1, 28).add_right(28, 91);
    //--------------------------------
    vector<double> vec_{5.3, 9.2, 91, 28, 1, 6, 11.5, 10.1};
    auto ot_ = vec_.begin();
    for(auto it = tree_of_doubles.begin_postorder(); it != tree_of_doubles.end_postorder(); ++it){
                CHECK(*it == *ot_);
        ++ot_;
    }

    //----------------CHECK OBJECTS----------------------//

    keep_num n1;
    keep_num n2;
    keep_num n3;
    keep_num n4;
    keep_num n5;
    keep_num n6;
    keep_num n7;
    keep_num n8;
    n1.val =10;
    n2.val = 9;
    n3.val =5;
    n4.val =11;
    n5.val =6;
    n6.val =1;
    n7.val =28;
    n8.val =91;

    //------------tree----------------
    BinaryTree<keep_num> tree_of_objects;
    tree_of_objects.add_root(n1).add_left(n1,n2).add_right(n1, n3).add_left(n3, n4)
            .add_right(n3, n5).add_left(n5, n6).add_left(n6, n7).add_right(n7, n8);
    //--------------------------------
    vector<keep_num> vect{n2, n4, n8, n7, n6, n5, n3, n1};
    auto ott = vect.begin();
    for(auto it = tree_of_objects.begin_postorder(); it != tree_of_objects.end_postorder(); ++it){
                CHECK((*it).val == (*ott).val);
        ++ott;
    }
}

TEST_CASE("For Each"){
    //use inorder traversal
    //----------------CHECK INTEGERS NUMBERS----------------------//

    //------------tree----------------
    BinaryTree<int> tree_of_ints;
    tree_of_ints.add_root(10).add_left(10, 9).add_right(10, 11).add_left(9, 5)
            .add_right(11, 6).add_left(6, 1).add_left(1, 28).add_right(28, 91);
    //--------------------------------
    vector<int> vec{5, 9, 10, 11, 28, 91, 1, 6};
    auto ot = vec.begin();
    for(int num: tree_of_ints){
        CHECK_EQ(num ,*ot);
        ++ot;
    }
    //----------------CHECK DOUBLE NUMBERS----------------------//

    //------------tree----------------
    BinaryTree<double> tree_of_doubles;
    tree_of_doubles.add_root(10.1).add_left(10.1, 9.2).add_right(10.1, 11.5).add_left(9.2, 5.3)
            .add_right(11.5, 6).add_left(6, 1).add_left(1, 28).add_right(28, 91);
    //--------------------------------
    vector<double> vec_{5.3, 9.2, 10.1, 11.5, 28, 91, 1, 6};
    auto ot_ = vec_.begin();
    for(double iterable:tree_of_doubles){
                CHECK_EQ(iterable, *ot_);
        ++ot_;
    }

    //----------------CHECK STRINGS----------------------//

    //------------tree----------------
    BinaryTree<string> tree_of_strings;
    tree_of_strings.add_root("root").add_left("root", "hi").add_left("hi", "bi").add_right("hi", "ls")
            .add_right("ls","pt" ).add_left("ls", "pp");
    //--------------------------------
    vector<string> res_{"bi", "hi", "pp", "ls", "pt", "root"};
    auto oth_ = res_.begin();
    for(string sv: tree_of_strings){
        CHECK(sv == *oth_);
        ++oth_;
    }

}