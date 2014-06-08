
#include "utils/jsonextend.h"
#include <map>

#undef U
#ifndef GTEST_H_
	#define GTEST_H_
	#include "gtest/gtest.h"
#endif
class jsonextendTest: public ::testing::Test {

};


TEST_F(jsonextendTest, create) {

	jsonextend value;
     value["test"] = web::json::value::string("a");
     ASSERT_EQ(value["test"].as_string(),"a");
}

TEST_F(jsonextendTest, castToString) {

	jsonextend value;
     value["test"] = web::json::value::string("a");
     std::string test = static_cast<std::string>(value);
     ASSERT_EQ(test, std::string("{\"test\":\"a\"}"));
}

TEST_F(jsonextendTest, createfromstring) {
    std::string testS("{\"test\":\"a\"}");
	jsonextend value(testS);
     value["test"] = web::json::value::string("a");

     ASSERT_EQ(value["test"].as_string(),"a");
}
TEST_F(jsonextendTest, storeinmap) {
	jsonextend value;
     value["test"] = web::json::value::string("a");
     std::map<jsonextend, std::string> testowa;
     testowa[value] = "ala";

     ASSERT_EQ(testowa[value], "ala");
}

TEST_F(jsonextendTest, throwExectpionWhenWrongJSON) {

	std::string propString = std::string("{\"ampltude\":null,name\":\"nowa\",\"percentageAbove10percentage\":0,\"percentageAbove20percentage\":0,") +
			std::string("\"percentageAbove30percentage\":0,\"percentageAbove40percentage\":0,\"percentageAbove50percentage\":0,\"percentageAbove60percentage\":0,") +
			std::string("\"percentageAbove70percentage\":0,\"percentageAbove80percentage\":0,\"percentageAbove90percentage\":0,\"zeroCrossings\":1185}");
ASSERT_THROW(jsonextend(propString).to_string(), web::json::json_exception);


}