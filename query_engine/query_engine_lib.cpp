//
//  query_engine_lib.cpp
//  query_engine
//
//  Created by Ankit Srivastava on 2/19/21.
//

#include "query_engine_lib.hpp"
#include <fstream>

namespace query_engine {

// Splits the given name at occurences of the space character.
std::vector<std::string> space_split(const std::string& str, char delim) {
  std::vector<std::string> result;
  std::string res = "";
  for (char c : str) {
    if (c == delim) {
      result.push_back(res);
      res = "";
    }
    else res += c;
  }
  result.push_back(res);
  return result;
}

std::vector<MovieData> LoadFromCsv(const std::string& filename, char delim) {
  std::ifstream file(filename);
  std::string buffer;
  std::vector<MovieData> result;
  while(std::getline(file, buffer)) {
    auto splits = space_split(buffer, delim);
    MovieData data;
    data.first = splits[0];
    for (int i = 1; i < splits.size(); ++i) {
      data.second.push_back(splits[i]);
    }
    result.push_back(data);
  }
  return result;
}

std::string StringToLower(const std::string& input) {
  std::string output = input;
  std::transform(input.begin(), input.end(), output.begin(),
                 [](unsigned char c){ return std::tolower(c); });
  return output;
}

}  // namespace query_engine

