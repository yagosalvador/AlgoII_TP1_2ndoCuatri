#include <gtest/gtest.h>
#include <string>
#include "query.hpp"


namespace {
	TEST(Query, Constructor){
		Query q;
		std::string str = "";

		EXPECT_EQ(q.showId(),str);
		EXPECT_EQ(q.showT0(),0);
		EXPECT_EQ(q.showTF(),0);
		EXPECT_EQ(q.isEmpty(),false);
		EXPECT_EQ(q.isBad(),false);
	}

	TEST(Query, Arg_Constructor){
		std::string str = "Sensor";
		size_t x = rand(), y = rand();

		Query q(str,x,y);
		EXPECT_EQ(q.showId(),str);
		EXPECT_EQ(q.showT0(),x);
		EXPECT_EQ(q.showTF(),y);
	}
}