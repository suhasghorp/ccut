#include <gtest/gtest.h>
#include "ccut/field_extractor.hpp"
#include <string>
#include <vector>

class FieldExtractorTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(FieldExtractorTest, ExtractSingleField) {
    std::string line = "f0\tf1\tf2\tf3\tf4";
    std::vector<size_t> fields = {1}; // Extract field 2 (0-indexed)
    
    auto result = ccut::FieldExtractor::extractFields(line, '\t', fields);
    
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result->size(), 1);
    EXPECT_EQ((*result)[0], "f1");
}

TEST_F(FieldExtractorTest, ExtractFirstField) {
    std::string line = "f0\tf1\tf2\tf3\tf4";
    std::vector<size_t> fields = {0}; // Extract field 1 (0-indexed)
    
    auto result = ccut::FieldExtractor::extractFields(line, '\t', fields);
    
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result->size(), 1);
    EXPECT_EQ((*result)[0], "f0");
}

TEST_F(FieldExtractorTest, ExtractLastField) {
    std::string line = "f0\tf1\tf2\tf3\tf4";
    std::vector<size_t> fields = {4}; // Extract field 5 (0-indexed)
    
    auto result = ccut::FieldExtractor::extractFields(line, '\t', fields);
    
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result->size(), 1);
    EXPECT_EQ((*result)[0], "f4");
}

TEST_F(FieldExtractorTest, FieldOutOfRange) {
    std::string line = "f0\tf1\tf2";
    std::vector<size_t> fields = {5}; // Field 6 doesn't exist
    
    auto result = ccut::FieldExtractor::extractFields(line, '\t', fields);
    
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), "Field 6 does not exist");
}

TEST_F(FieldExtractorTest, EmptyLine) {
    std::string line = "";
    std::vector<size_t> fields = {0};
    
    auto result = ccut::FieldExtractor::extractFields(line, '\t', fields);
    
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->size(), 0);
}

TEST_F(FieldExtractorTest, SingleField) {
    std::string line = "single";
    std::vector<size_t> fields = {0};
    
    auto result = ccut::FieldExtractor::extractFields(line, '\t', fields);
    
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result->size(), 1);
    EXPECT_EQ((*result)[0], "single");
}

TEST_F(FieldExtractorTest, ExtractMultipleFields) {
    std::string line = "f0\tf1\tf2\tf3\tf4";
    std::vector<size_t> fields = {0, 2, 4}; // Extract fields 1, 3, 5
    
    auto result = ccut::FieldExtractor::extractFields(line, '\t', fields);
    
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result->size(), 3);
    EXPECT_EQ((*result)[0], "f0");
    EXPECT_EQ((*result)[1], "f2");
    EXPECT_EQ((*result)[2], "f4");
}

TEST_F(FieldExtractorTest, ExtractMultipleFieldsWithCommaDelimiter) {
    std::string line = "Song title,Artist,Year,Progression";
    std::vector<size_t> fields = {0, 1}; // Extract fields 1, 2
    
    auto result = ccut::FieldExtractor::extractFields(line, ',', fields);
    
    ASSERT_TRUE(result.has_value());
    ASSERT_EQ(result->size(), 2);
    EXPECT_EQ((*result)[0], "Song title");
    EXPECT_EQ((*result)[1], "Artist");
}

TEST_F(FieldExtractorTest, ExtractMultipleFieldsOutOfRange) {
    std::string line = "f0\tf1\tf2";
    std::vector<size_t> fields = {0, 5}; // Field 6 doesn't exist
    
    auto result = ccut::FieldExtractor::extractFields(line, '\t', fields);
    
    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), "Field 6 does not exist");
}
