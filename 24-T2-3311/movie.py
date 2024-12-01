#!/usr/bin/python3

# COMP3311 24T2 Assignment 2
# Print info about one movie; may need to choose

import sys
import psycopg2
import helpers

### Globals

db = None
usage = f"Usage: {sys.argv[0]} 'PartialMovieName'"

### Command-line args

if len(sys.argv) < 2:
   print(usage)
   exit(1)

movie_name = sys.argv[1]
# process the command-line args ...

### Queries
### Manipulating database
try:
   db = psycopg2.connect("dbname=ass2")
   cursor = db.cursor()

   # Query to find movies matching the partial title
   cursor.execute("""
   SELECT id, title, year
   FROM movies
   WHERE title ILIKE %s
   ORDER BY title, year
   """, (f"%{movie_name}%",))
   movies = cursor.fetchall()

   if not movies:
      print(f"No movie matching: '{movie_name}'")
      exit(1)

   if len(movies) > 1:
      for index, (movie_id, title, year) in enumerate(movies, start=1):
         print(f"{index}. {title} ({year})")
      choice = int(input("Which movie? ")) - 1
      if choice < 0 or choice >= len(movies):
         print(f"Invalid choice")
         exit(1)
      movie_id, title, year = movies[choice]
   else:
      movie_id, title, year = movies[0]

   # Print the selected movie
   print(f"{title} ({year})")

   # Query to find principals for the selected movie
   cursor.execute("""
   SELECT p.id, p.job, COALESCE(r.role, '???') AS role, pe.name
   FROM principals p
   JOIN people pe ON p.person = pe.id
   LEFT JOIN playsrole r ON p.id = r.inmovie
   WHERE p.movie = %s
   ORDER BY p.ord
   """, (movie_id,))
   
   principals = cursor.fetchall()
   if not principals:
      print("No principals found")
      exit(1)
   for person_id, job, role, name in principals:
      if role == '???' and job != 'actor':
         print(f"{name}: {job}")
      else:
         print(f"{name} plays {role}")

except Exception as err:
   print("DB error:", err)
finally:
    if db:
         db.close()