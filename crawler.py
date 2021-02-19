import re

from bs4 import BeautifulSoup
import requests
import csv

imdb_domain = "https://www.imdb.com"

def get_person_data(movie_url):
  name_attrs = { 'href': re.compile(r'^/name') }
  persons = set()
  soup = BeautifulSoup(requests.get(movie_url).text, 'html.parser')
  for person in soup.find_all('a', attrs = name_attrs):
    if person.string:
      persons.add(person.string.strip())
  return list(persons)

def get_movie_data(url):
  print(url)
  results = []
  html_doc = requests.get(url).text
  soup = BeautifulSoup(html_doc, 'html.parser')
  movie_attrs = { 'href': re.compile(r'^/title') }
  next_attrs = { 'href': re.compile(r'^/search/title') }
  for movie in soup.find_all('a', attrs = movie_attrs):
    if movie.string:
      results.append([movie.string] + get_person_data(imdb_domain + movie['href']))
  if len(results) != 50:
    print("error : ", url)
    print(results.keys())
  next_page = soup.find('a', attrs = next_attrs, string = "Next »")
  if next_page != None:
    results += get_movie_data(imdb_domain + next_page['href'])
  return results

def write_csv(filename, data):
  with open(filename, 'w', newline = '') as csvfile:
    fieldnames = ['movie_name', 'movie_stars']
    writer = csv.writer(csvfile, delimiter="|")

    for row in data:
      writer.writerow(row)

if __name__ == '__main__':
  data = get_movie_data("https://www.imdb.com/search/title/?groups=top_1000&sort=user_rating&view=simple")
  write_csv('/Users/sriankit/Desktop/Coding/imdb/movie_data_final.csv', data)

