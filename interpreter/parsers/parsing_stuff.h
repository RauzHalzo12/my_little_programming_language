#pragma once

#include <string_view>
#include <optional>
#include <vector>
#include <string>

std::pair<std::string_view, std::optional<std::string_view>> SplitTwoStrict(std::string_view line_to_split,
                                                                            std::string_view delimeter = " ");

std::vector<std::string_view> SplitLineIntoTokensViews(std::string_view line, std::string_view delimeter = " ");

std::vector<std::string> SplitLineIntoTokens(std::string_view line, std::string_view delimeter = " ");

std::pair<std::string_view, std::string_view> SplitTwo(std::string_view s, std::string_view delimiter = " ");

std::string_view ReadToken(std::string_view& s, std::string_view delimiter = " ");

double ConvertToDouble(std::string_view line);

std::string GetTextFromFile(std::istream &input);


