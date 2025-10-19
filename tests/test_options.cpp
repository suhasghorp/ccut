#include <gtest/gtest.h>
#include "ccut/options.hpp"
#include <vector>

class OptionsTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(OptionsTest, ParseBasicArgs) {
    const char* argv[] = {"ccut", "-f2", "test.tsv"};
    int argc = 3;
    
    auto result = ccut::parseArgs(argc, const_cast<char**>(argv));
    
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->fields.size(), 1);
    EXPECT_EQ(result->fields[0], 1); // Field 2 is 0-indexed as 1
    EXPECT_EQ(result->delimiter, '\t');
    EXPECT_EQ(result->filename, "test.tsv");
}

TEST_F(OptionsTest, ParseWithCustomDelimiter) {
    const char* argv[] = {"ccut", "-f1", "-d,", "test.csv"};
    int argc = 4;
    
    auto result = ccut::parseArgs(argc, const_cast<char**>(argv));
    
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->fields.size(), 1);
    EXPECT_EQ(result->fields[0], 0); // Field 1 is 0-indexed as 0
    EXPECT_EQ(result->delimiter, ',');
    EXPECT_EQ(result->filename, "test.csv");
}

TEST_F(OptionsTest, ParseWithDelimiterFirst) {
    const char* argv[] = {"ccut", "-d,", "-f1", "test.csv"};
    int argc = 4;
    
    auto result = ccut::parseArgs(argc, const_cast<char**>(argv));
    
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->fields.size(), 1);
    EXPECT_EQ(result->fields[0], 0);
    EXPECT_EQ(result->delimiter, ',');
    EXPECT_EQ(result->filename, "test.csv");
}

TEST_F(OptionsTest, ParseMultipleFieldsCommaSeparated) {
    const char* argv[] = {"ccut", "-f1,2,3", "test.tsv"};
    int argc = 3;
    
    auto result = ccut::parseArgs(argc, const_cast<char**>(argv));
    
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->fields.size(), 3);
    EXPECT_EQ(result->fields[0], 0); // Field 1
    EXPECT_EQ(result->fields[1], 1); // Field 2
    EXPECT_EQ(result->fields[2], 2); // Field 3
    EXPECT_EQ(result->delimiter, '\t');
    EXPECT_EQ(result->filename, "test.tsv");
}

TEST_F(OptionsTest, ParseMultipleFieldsSpaceSeparated) {
    const char* argv[] = {"ccut", "-f1 2 3", "test.tsv"};
    int argc = 3;
    
    auto result = ccut::parseArgs(argc, const_cast<char**>(argv));
    
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->fields.size(), 3);
    EXPECT_EQ(result->fields[0], 0); // Field 1
    EXPECT_EQ(result->fields[1], 1); // Field 2
    EXPECT_EQ(result->fields[2], 2); // Field 3
    EXPECT_EQ(result->delimiter, '\t');
    EXPECT_EQ(result->filename, "test.tsv");
}

TEST_F(OptionsTest, ParseMultipleFieldsWithCustomDelimiter) {
    const char* argv[] = {"ccut", "-d,", "-f1,2", "test.csv"};
    int argc = 4;
    
    auto result = ccut::parseArgs(argc, const_cast<char**>(argv));
    
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->fields.size(), 2);
    EXPECT_EQ(result->fields[0], 0); // Field 1
    EXPECT_EQ(result->fields[1], 1); // Field 2
    EXPECT_EQ(result->delimiter, ',');
    EXPECT_EQ(result->filename, "test.csv");
}

TEST_F(OptionsTest, MissingFilename) {
    const char* argv[] = {"ccut", "-f1"};
    int argc = 2;
    
    auto result = ccut::parseArgs(argc, const_cast<char**>(argv));
    
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), "No filename specified");
}

TEST_F(OptionsTest, MissingFields) {
    const char* argv[] = {"ccut", "test.tsv"};
    int argc = 2;
    
    auto result = ccut::parseArgs(argc, const_cast<char**>(argv));
    
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), "No fields specified");
}

TEST_F(OptionsTest, InvalidFieldNumber) {
    const char* argv[] = {"ccut", "-f0", "test.tsv"};
    int argc = 3;
    
    auto result = ccut::parseArgs(argc, const_cast<char**>(argv));
    
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), "Invalid field number: 0");
}

TEST_F(OptionsTest, InvalidDelimiter) {
    const char* argv[] = {"ccut", "-f1", "-dab", "test.tsv"};
    int argc = 4;
    
    auto result = ccut::parseArgs(argc, const_cast<char**>(argv));
    
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), "Delimiter must be exactly one character");
}

TEST_F(OptionsTest, UnknownOption) {
    const char* argv[] = {"ccut", "-x", "test.tsv"};
    int argc = 3;
    
    auto result = ccut::parseArgs(argc, const_cast<char**>(argv));
    
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), "Unknown option: -x");
}