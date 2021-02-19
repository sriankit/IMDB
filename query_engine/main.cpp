//
//  main.cpp
//  query_engine
//
//  Created by Ankit Srivastava on 2/18/21.
//

#include <iostream>
#include "query_engine.hpp"

int main(int argc, const char * argv[]) {
  std::string kFilename = "/Users/sriankit/Desktop/Coding/imdb/movie_data_final.csv";
  query_engine::QueryEngine query(query_engine::LoadFromCsv(kFilename, '|'));
  for (const auto& query_str : {"Morgan Freeman", "Freeman", "Morgan",
  "Al Pacino James Caan Francis Ford Coppola John Marley",
    "Al Pacino Francis Ford Coppola", "Al", "Al Pacino", "spielberg",
    "Spielberg Hanks"
  }) {
    for (auto res : query.Query(query_str)) {
      std::cout << res << std::endl;
    }
  }
  return 0;
}
