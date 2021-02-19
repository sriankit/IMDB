//
//  query_engine_lib.hpp
//  query_engine
//
//  Created by Ankit Srivastava on 2/19/21.
//

#ifndef query_engine_lib_hpp
#define query_engine_lib_hpp

#include <vector>
#include <string>
#include <stdio.h>

namespace query_engine {

// `first` contains the movie name and second contains a list of people associated.
using MovieData = std::pair<std::string, std::vector<std::string>>;

// Splits the given name at occurences of the delimiter character.
std::vector<std::string> space_split(const std::string& str, char delim);

// Loads the movie data from specified file. Uses delimiter to split.
std::vector<MovieData> LoadFromCsv(const std::string& filename, char delim);

// Converts a given string to it's lowercase form, making the search case-insensitive.
std::string StringToLower(const std::string& input);

}  // namespace query_engine

#endif /* query_engine_lib_hpp */
