#include "String.h"
#include "gtest/gtest.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class StringTestFixture: public::testing::Test{
public:
    StringTestFixture():s1("howdy"), s2(s1), s3()
    {
    }

    void SetUp(){
        s1 = "what";
        s2 = "the";
        s3 = "heck";
        s4 = "";

        String t1("brown");
        String t2("chick");
        String t3("cowww");
        String t4("");  
        ts1 = t1;
        ts2 = t2;
        ts3 = t3;
        ts4 = t4;

        svec.push_back(ts1);
        svec.push_back(ts2);
        svec.push_back(ts3);
        svec.push_back(ts4);
    }

    void TearDown(){
    }

    ~StringTestFixture(){
    };


    //String objects from different ways
    String s1;
    String s2;
    String s3;
    String s4;

    String ts1;
    String ts2;
    String ts3;
    String ts4;

    vector<String> svec;
};


TEST_F(StringTestFixture, TestAssignment){
    //move assignment
    s1 = "what";
    s2 = "the";
    s3 = "heck";
    s4 = "";
    ASSERT_TRUE(s1 == "what");
    ASSERT_TRUE(s2 == "the");
    ASSERT_TRUE(s3 == "heck");
    ASSERT_TRUE(s4.Size() == 0);
    ASSERT_TRUE(s4 == "");

    //copy assignment
    s1 = ts1;
    s2 = ts2;
    s3 = ts3;
    s4 = ts4;
    ASSERT_TRUE(s1 == "brown");
    ASSERT_TRUE(s2 == "chick");
    ASSERT_TRUE(s3 == "cowww");
    ASSERT_TRUE(s4.Size() == 0);
    ASSERT_TRUE(s4 == "");
}

TEST_F(StringTestFixture, TestCopyControl){
    //copy constructor
    //move constructor
    vector<String> svec;
    svec.push_back(s1);
    svec.push_back(s2);
    svec.push_back(s3);
    svec.push_back(s4);

    ASSERT_TRUE(svec[0] == "what");
    ASSERT_TRUE(svec[1] == "the");
    ASSERT_TRUE(svec[2] == "heck");
    ASSERT_TRUE(svec[3].Size() == 0);
    ASSERT_TRUE(svec[3] == "");
}

TEST_F(StringTestFixture, TestPushBack){
    s1.push_back('\'');    
    s1.push_back('s');
    ASSERT_TRUE( s1 == "what\'s");
    
    for(auto i = 0; i < 10; ++i){
        ts1.push_back('1');
    }
    ASSERT_TRUE( ts1 == "brown1111111111");

    s4.push_back('h');
    s4.push_back('o');
    s4.push_back('o');
    s4.push_back('r');
    s4.push_back('a');
    s4.push_back('y');
    ASSERT_TRUE( s4 == "hooray");

    ts4.push_back('h');
    ts4.push_back('o');
    ts4.push_back('o');
    ts4.push_back('r');
    ts4.push_back('a');
    ts4.push_back('y');
    ASSERT_TRUE( s4 == ts4);
    
    svec[0].push_back('\'');    
    svec[0].push_back('s');
    ASSERT_TRUE( svec[0] == "brown\'s");
}

TEST_F(StringTestFixture, TestPlus){
    ASSERT_TRUE( s1 + "" ==  "what" );
    ASSERT_TRUE( s1 + "\'s" ==  "what\'s" );
    ASSERT_TRUE( s1 + "hooray" ==  "whathooray" );

    ASSERT_TRUE( (s1 += "") ==  "what" );
    ASSERT_TRUE( (s1 += "\'s") ==  "what\'s" );
    ASSERT_TRUE( (s1 += "hooray") ==  "what\'shooray" );
}

TEST(StringTest, TestConversion){
    String my_str("hey");
    ASSERT_EQ(my_str.Size(), 3);
    String my_str1("");
    ASSERT_EQ(my_str1.Size(), 0);

    ASSERT_TRUE(my_str == "hey");
    ASSERT_TRUE(my_str1 == "");
    ASSERT_FALSE(my_str == "you");
}

TEST(StringTest, TestRelation){
    String s1 = "ashame";
    String s2 = "ashamement";
    String s3 = "abandon";
    String s4 = "curious";
    String s5 = "cure";
    String s6 = "cure";

    ASSERT_TRUE(s1 < s2);
    ASSERT_FALSE(s2 < s3);
    ASSERT_TRUE(s3 < s4);
    ASSERT_TRUE(s5 < s4);
    ASSERT_FALSE(s5 < s6);//consistent with ==
    ASSERT_FALSE(s6 < s5);
    ASSERT_FALSE("" < "");//consistent with ==
    ASSERT_TRUE("" < s1);

    //algorithm
    vector<String> sv = {s1, s2, s3, s4, s5};
    sort(sv.begin(), sv.end());
    ASSERT_TRUE(sv[0] == "abandon");
    ASSERT_TRUE(sv[1] == "ashame");
    ASSERT_TRUE(sv[2] == "ashamement");
    ASSERT_TRUE(sv[3] == "cure");
    ASSERT_TRUE(sv[4] == "curious");
    //associative container
}

TEST(StringTest, TestInputOperator){
    istringstream str("what a crazy world\n");
    String s1;
    String s2;
    String s3;
    String s4;
    String s5;

    str>>s1>>s2>>s3>>s4>>s5;
    ASSERT_TRUE(isspace(' '));
    ASSERT_TRUE(s1 == "what");
    ASSERT_TRUE(s2 == "a");
    ASSERT_TRUE(s3 == "crazy");
    ASSERT_TRUE(s4 == "world");
    ASSERT_TRUE(s5.Empty());
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}