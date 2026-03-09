# See all main info about DB
#### At first read and set up [PostgreSQL in Debian](PostgreSQL_in_Debian.md) on Virtual or other machine

- Download Cmake
- Download on Windows pqxx using vcpkg or on MacOS download pqxx using brew (all intallation this libraries is in other projects as [University Records](https://github.com/qwinkki/UniversityRecords/blob/master/README.md))

1. Type `git clone https://github.com/qwinkki/testDebianPostgres.git` in cmd or terminal
2. Here use `mkdir build` to create build folder
3. `cd build` then to build project type `cmake ..`
4. And to compile project `cmale --build .`
5. And start the running file

If you do everything as in the PostgreSQL in Debian file, when you start the file type:
- ip: (On debian machine `ip a` and your own ip)
- port: 5432 (as you changed to default in config file)
- database name: test
- enter usermane: admin
- enter password: 123

##### This program shows you main info about DB, tables, and machine on which it is running
