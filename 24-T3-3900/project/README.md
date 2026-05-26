# MacOS
1. cd backend
2. python3 -m venv env
3. source env/bin/activate
4. pip3 install -r requirements.txt

# Win
1. cd backend
2. python -m venv env
3. source env/Scripts/activate
4. Run "pip3 install -r requirements.txt"

# DB initialising
1. flask shell
2. db.create_all()
3. cd ..

# Run Program
1. docker-compose up --build

# To view the database:
1. Install "SQLite Viewer"
2. Go to /backend/instance/db.sqlite3

# To clear or initialise database:
1. cd backend
2. bash db_controller.sh <clear/init/test>

# ENV File
1. Create .env file in same directory as .env.template
2. Copy content inside .env.template
3. Set FLASK_SECRET_KEY field to any string (e.g. JEMMA)
