#!/usr/bin/python3

# COMP3311 24T2 Assignment 2
# Print a list of countries where a named movie was released

import sys
import psycopg2
import helpers

### Globals

db = None
usage = f"Usage: {sys.argv[0]} 'MovieName' Year"

### Command-line args

if len(sys.argv) < 3:
   print(usage)
   exit(1)

title = sys.argv[1]
year = sys.argv[2]

# process the command-line args ...

if not (year.isdigit() and len(year) == 4):
    print("Invalid year")
    exit(1)

### Queries

### Manipulating database
try:
    db = psycopg2.connect("dbname=ass2")
    cursor = db.cursor()

    # Query to get the origin country of the movie
    query_origin = """
    SELECT origin
    FROM movies
    WHERE title = %s AND year = %s;
    """
    cursor.execute(query_origin, (title, year))
    origin_result = cursor.fetchone()
    
    if origin_result is None:
        print("No such movie")
        exit(1)
    
    origin_country_code = origin_result[0]
    
    # Query to get the list of countries where the movie was released
    query_releases = """
    SELECT c.name
    FROM releasedin r
    JOIN countries c ON r.country = c.code
    WHERE r.movie IN (
        SELECT id
        FROM movies
        WHERE title = %s AND year = %s
    );
    """
    cursor.execute(query_releases, (title, year))
    releases = cursor.fetchall()
    
    if not releases:
        print("No releases")
        exit(1)
    
    # Get the list of released countries
    released_countries = sorted(set(country[0] for country in releases))
    
    if len(released_countries) == 1:
        print(f"The movie was only released in its origin country: {released_countries[0]}")
    else:
        for country in released_countries:
            print(country)

except Exception as err:
    print("DB error:", err)
finally:
    if db:
        db.close()