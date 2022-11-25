#include "gtest/gtest.h"
#include "XmlParser.h"

using namespace xml_parser;

class ParserTest : public ::testing::Test {
protected:
    void SetUp() override {
        mXmlParser = new XmlParser("/home/yonatan10/development/xml-parser/xml_files/config.xml");
    }   
    void TearDown() override {
        delete mXmlParser;
    }

    XmlParser* mXmlParser;
};

TEST_F(ParserTest, IsInitialized) {
    EXPECT_EQ(mXmlParser->init(), true);
}

TEST_F(ParserTest, ParseFile) {
    EXPECT_EQ(mXmlParser->init(), true);
    EXPECT_EQ(mXmlParser->parseFile(), true);
}