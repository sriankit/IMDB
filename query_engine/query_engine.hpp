//
//  query_engine.hpp
//  query_engine
//
//  Created by Ankit Srivastava on 2/19/21.
//

#ifndef query_engine_hpp
#define query_engine_hpp

#include <stdio.h>
#include <vector>
#include <utility>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "query_engine_lib.hpp"

namespace query_engine {

// Initialized with the provided names of movies and taxonomies of stars associated with them.
// Responsible for indexing of information and parsing of query.
class QueryEngine{
  
public:
  QueryEngine(const std::vector<MovieData>& movie_data);
  
  // Returns the list of movies matching with the given query text. If we are unable to disambiguate
  // we will return an empty list.
  std::vector<std::string> Query(const std::string& text);
  
private:
  
  // Contains an indexed list of movies.
  std::vector<std::string> movie_;
  
  // Contains an indexed list of star names.
  std::vector<std::string> star_names_;
  
  // Each key represents a star mapping to a set of movies they were cast in.
  std::unordered_map<int, std::unordered_set<int>> star_to_movies_map_;
  
  // Inverse of the star_names_ vector.
  std::unordered_map<std::string, int> star_id_;
  
  // Indexes chunks of people's names. Since, people can have the same first names/last names, we keep a set of everyone having this name.
  std::unordered_map<std::string, std::unordered_set<int>> chunk_id_;
  
};

}  // namespace query_engine
#endif /* query_engine_hpp */
