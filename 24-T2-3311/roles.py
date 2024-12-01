#!/usr/bin/python3

# COMP3311 24T2 Assignment 2
# Print a list of character roles played by an actor/actress

import sys
import psycopg2
import helpers
from collections import defaultdict
### Globals

db = None
usage = f"Usage: {sys.argv[0]} FullName"

### Command-line args

if len(sys.argv) < 2:
   print(usage)
   exit(1)

# process the command-line args ...
name = ' '.join(sys.argv[1:]).strip()

### Queries
### Manipulating database
try:
    db = psycopg2.connect("dbname=ass2")
    cursor = db.cursor()

    # Query to find people with the given name
    cursor.execute("""
    SELECT id, name
    FROM people
    WHERE name = %s
    ORDER BY id
    """, (name,))
    people = cursor.fetchall()

    if not people:
        print("No such person")
        exit(1)
    
    found_any_roles = False

    for i, (person_id, person_name) in enumerate(people, start=1):
        # Query to find acting roles for the person
        cursor.execute("""
        SELECT r.role, m.title, m.year, m.rating
        FROM principals p
        JOIN playsrole r ON p.id = r.inmovie
        JOIN movies m ON p.movie = m.id
        WHERE p.person = %s AND (p.job = 'actor' OR p.job = 'self')
        ORDER BY m.year, m.title, r.role
        """, (person_id,))
        roles = cursor.fetchall()
        if not roles and i == len(people) and i == 1:
            print("No acting roles")
            exit(1)
        else:
            
            if len(people) > 1:
                print(f"{person_name} #{i}")
                if not roles:
                    print("No acting roles")
            for role, title, year, rating in roles:
                print(f"{role} in {title} ({year}) {rating:.1f}")
            found_any_roles = True

    if not found_any_roles:
        
        print("No acting roles")

except Exception as err:
    print("DB error:", err)
finally:
    if db:
        db.close()