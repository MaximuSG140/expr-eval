#include "pch.h"
#include "../ExpressionEvaluation/Evaluate.h"

TEST(SimpleExpressions, EvaluationTesting)
{
	EXPECT_EQ(4, Evaluate("2 + 2"));
	EXPECT_EQ(5, Evaluate("2 + 3"));
	EXPECT_EQ(4, Evaluate("2 * 2"));
	EXPECT_EQ(0, Evaluate("2 - 2"));
	EXPECT_EQ(10, Evaluate("5*2"));
	EXPECT_EQ(10000, Evaluate("100*100"));
	EXPECT_EQ(0, Evaluate("4/5"));
	EXPECT_EQ(132, Evaluate("132/1"));
	EXPECT_EQ(10000, Evaluate("10000* 1"));
	EXPECT_EQ(10000, Evaluate("10000"));
}

TEST(ExpressionsWithBrackets, EvaluationTesting)
{
	EXPECT_EQ(3, Evaluate("(3)"));
	EXPECT_EQ(3, Evaluate("(((((((3)))))))"));
	EXPECT_EQ(4, Evaluate("(3)+1"));
	EXPECT_EQ(4, Evaluate("1 + (3)"));
	EXPECT_EQ(30, Evaluate("(5*5) + 5"));
	EXPECT_EQ(30, Evaluate("5 + (5 * 5)"));
	EXPECT_EQ(Evaluate("(5*5)*5"), Evaluate("5*(5*5)"));
	EXPECT_EQ(10, Evaluate("((3 + 2))*2"));
	EXPECT_EQ(32, Evaluate("(33) - 1"));
	EXPECT_EQ(144, Evaluate("(12)*12"));
	EXPECT_EQ(1, Evaluate("(12)/(6+6)"));
}