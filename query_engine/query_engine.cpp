//
//  query_engine.cpp
//  query_engine
//
//  Created by Ankit Srivastava on 2/19/21.
//

#include "query_engine.hpp"
#include <unordered_set>
#include <iostream>

namespace query_engine {

int InsertIfNotFound(const std::string& star_name,
                   std::unordered_map<std::string, int>* known_stars,
                   std::vector<std::string>* star_names) {
  if (known_stars->count(star_name)) return known_stars->at(star_name);
  int star_id = (*known_stars)[star_name] = int(star_names->size());
  star_names->push_back(star_name);
  return star_id;
}

QueryEngine::QueryEngine(const std::vector<MovieData>& movie_data) {
  movie_.resize(movie_data.size());
  
  for (int movie_idx = 0; movie_idx < movie_data.size(); ++movie_idx) {
    movie_[movie_idx] = movie_data[movie_idx].first;
    for (const auto& star : movie_data[movie_idx].second) {
      std::string star_name = StringToLower(star);
      // We will split up the star's name into chunks and then associate each of them
      // with index of a star.
      int star_id = InsertIfNotFound(star_name, &star_id_, &star_names_);
      star_to_movies_map_[star_id].insert(movie_idx);
      chunk_id_[star_name].insert(star_id);
      for (const std::string& chunk : space_split(star_name, ' ')) {
        chunk_id_[chunk].insert(star_id);
      }
    }
  }
}

std::vector<std::string> QueryEngine::Query(const std::string& text) {
  auto split_text = space_split(StringToLower(text), ' ');
  int n = int(split_text.size());
  std::unordered_set<int> found_stars;
  for (int i = 0; i < n; ) {
    // We try to match the longest string first to disambiguate similar names.
    // For example, we may have 'Jennifer Aniston' or 'Jennifer Lawrence' in the query.
    // By greedily matching with the longest chunk, we are able to disambiguate.
    bool matched = false;
    int len = std::min(3, n - i);
    for (; len >= 1; --len) {
      std::string query_str = split_text[i];
      for (int j = i + 1; j < i + len && j < split_text.size(); ++j) {
        query_str += ' ' + split_text[j];
      }
      if (chunk_id_.count(query_str)) {
        found_stars.insert(chunk_id_.at(query_str).begin(), chunk_id_.at(query_str).end());
        matched = true;

        break;
      }
    }
    if (!matched) return {};
    i += len;
  }
  std::cout << text << std::endl;
  for (auto star : found_stars) {
    std::cout << star_names_[star] << " ";
  }
  std::cout << std::endl;
  std::unordered_set<int> movies_intersection = star_to_movies_map_[*found_stars.begin()];
  // Retain only those movies that have all the stars identified in the query.
  for (int star : found_stars) {
    auto movies_candidates = star_to_movies_map_[star];
    for (auto it = movies_intersection.begin(); it != movies_intersection.end();
         ) {
      if (!movies_candidates.count(*it)) it = movies_intersection.erase(it);
      else ++it;
    }
  }
  std::vector<std::string> results(movies_intersection.size());
  std::transform(movies_intersection.begin(), movies_intersection.end(), results.begin(), [this](int movie_idx) {return this->movie_[movie_idx];});
  return results;
}

}  // namespace query_engine
