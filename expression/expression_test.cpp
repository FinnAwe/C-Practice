#include "expression.h"
#include "gtest/gtest.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class ExPressionTestFixture: public::testing::Test{
public:
    ExPressionTestFixture()
    {
    }

    void SetUp(){
    }

    void TearDown(){
    }

    ~ExPressionTestFixture(){
    };

    //String objects from different ways
};


TEST_F(ExPressionTestFixture, TestNormal){
    string e1{"1"};
    string e2{"2"};
    string e3{"1+1"};
    string e4{"2+1"};
    string e5{"2+1-2"};
    string e6{"3*2/3+1-2"};
    string e7{"3/2*2+5*2-1"};
    string e8{"3/2*2+2*(5*2 + 22 + 8)-1"};

    int retCode = 0;
    Expression exp;
    ASSERT_TRUE(exp.ResolveExpression(e1, retCode) == 1);
    ASSERT_TRUE(exp.ResolveExpression(e2, retCode) == 2);
    ASSERT_TRUE(exp.ResolveExpression(e3, retCode) == 2);
    ASSERT_TRUE(exp.ResolveExpression(e4, retCode) == 3);
    ASSERT_TRUE(exp.ResolveExpression(e5, retCode) == 1);
    ASSERT_TRUE(exp.ResolveExpression(e6, retCode) == 1);
    ASSERT_TRUE(exp.ResolveExpression(e7, retCode) == 12);
    ASSERT_TRUE(exp.ResolveExpression(e7, retCode) == 82);

    ASSERT_TRUE(retCode = 0);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}