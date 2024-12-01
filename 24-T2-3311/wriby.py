#!/usr/bin/python3

# COMP3311 24T2 Assignment 2
# Print a list of movies written by a given person

import sys
import psycopg2
import helpers

### Globals

db = None
usage = f"Usage: {sys.argv[0]} FullName"

### Command-line args

if len(sys.argv) < 2:
   print(usage)
   exit(1)

# process the command-line args ...
person_name = sys.argv[1]

### Queries

### Manipulating database

try:
   db = psycopg2.connect("dbname=ass2")
   cur = db.cursor()

   # Find the person by name
   cur.execute("""
       SELECT id FROM People WHERE name = %s
   """, (person_name,))
   people = cur.fetchall()
   if not people:
      print("No such person")
      exit(1)

   person_id = None
   for person in people:
      cur.execute("""
         SELECT job FROM Principals WHERE person = %s
      """, (person[0],))
      jobs = cur.fetchall()
      person_id = person[0]
      if person_id is None or len(jobs) == 1:
         print(f"None of the people called {person_name} has written any films")
         exit(1)
      # List movies written by the person
      cur.execute("""
         SELECT title, year FROM Movies
         JOIN Principals ON Movies.id = Principals.movie
         WHERE Principals.person = %s AND Principals.job = 'writer'
         ORDER BY year, title
      """, (person_id,))
      movies = cur.fetchall()

      if not movies:
         print(f"{person_name} has not written any movies")
         exit(1)
      else:
         for movie in movies:
            print(f"{movie[0]} ({movie[1]})")

except Exception as err:
   print("DB error: ", err)
finally:
   if db:
      db.close()
