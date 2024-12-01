#!/usr/bin/python3

# COMP3311 24T2 Assignment 2
# Print a list of countries where a named movie was released

import sys
import psycopg2
import helpers

### Globals

db = None
usage = f"Usage: {sys.argv[0]} Year"

### Command-line args

if len(sys.argv) < 2:
   print(usage)
   exit(1)

# process the command-line args ...
year = sys.argv[1]

# Validate the year
if not (year.isdigit() and len(year) == 4):
    print("Invalid year")
    exit(1)

### Queries

### Manipulating database

try:
    db = psycopg2.connect("dbname=ass2")
    cursor = db.cursor()
    
    # Query to get the average rating for each genre for the specified year
    query = """
    SELECT g.genre, AVG(m.rating) AS avg_rating
    FROM moviegenres g
    JOIN movies m ON g.movie = m.id
    WHERE m.year = %s
    GROUP BY g.genre
    ORDER BY avg_rating DESC, g.genre
    FETCH FIRST 10 ROWS WITH TIES;
    """
    cursor.execute(query, (year,))
    results = cursor.fetchall()
    
    if not results:
        print("No movies")
        exit(1)
    
    for genre, avg_rating in results:
        print(f"{avg_rating:.2f} {genre}")

except Exception as err:
    print("DB error:", err)
finally:
    if db:
        db.close()