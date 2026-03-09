# Debian with PosgtreSQL

#### All commands in terminal will be as `example`

1. Use terminal on linux an use commands `sudo apt update`
2. Install postgres in terminal `sudo apt install postgresql postgresql-contrib -y`
3. After this in your machine will be created postgre user on your linux (admin for all SQL commands and databases):
   - Here you need to authorize as postges user in terminal: `sudo -iu postgres` or `sudo -i -u postgres`
4. In this user you need to go to postgres terminal (ordinary SQL): `psql`
5. Here in SQL, you need to create main user for databases `ALTER USER admin WITH PASSWORD '123';` (you can change username "admin" and password "123" to another)
6. Then create database `CREATE DATABASE test;` (here you can change "test" to change name of your DB)
   - In this terminal you can create tables and some other SQL thing as insert info etc.
7. Exit SQL terminal and postgres user `\q`, then `exit`
8. If you want to use database in your network and not only on your PC you need to change configuration file:
   - `sudo nano /etc/postgresql/*/main/postgresql.conf` (* is your PostgreSQL version, just use TAB to enter currect version)
   - In this file find (use CTRL+F):
     - "#listen_addresses = 'localhost'" and change it to "listen_addresses = '*'"
     - "port = 5433" and change it to "port = 5432" (this port is default for local DB for programs)
   - Then use CTRL+X - Y - ENTER to save changings in file
   - `sudo nano /etc/postgresql/*/main/pg_hba.conf` (* is your PostgreSQL version, just use TAB to enter currect version)
   - In this file find (use CTRL+F):
     - Add at the end sentence "host    all     all     0.0.0.0/0     md5" (spaces is TAB)
   - Then use CTRL+X - Y - ENTER to save changings in file
9. In terminal type `sudo service postgresql restart` to see more commands use `sudo service postgresql` and type ENTER
10. To see, that PostgreSQL is working use `sudo service postgresql status`
11. In another terminal use `ip a` to see your current ip addres  (!! IF YOU USE VIRTUAL MACHINE SELECT "Network Bridge")

# Some usefull commands for PostgreSQL
- In terminal: `sudo -u postgres psql -d test` to check connection to DB
- In "psql" `\l` or `\list` to see all DB's
- In "psql" `\du` or `\dg` to see all users
- In "/etc/postgresql/*/main/postgresql.conf" you can change max connections and some other userful information
- To see all log of connections and commands to ur DB in real time use `sudo tail -f /var/log/postgresql/postgresql-*.log` (* - your version)
