# Remuneration Calculator

The Practical part of the second Software Development and Database implementation course Assignment 2

## Dependencies

This program depends on a number of external libraries for it's compiltion
 - ncurses - for controlling the screen in the interactive mode
 - libpqxx - for a C++ interface to the postgres database
 - libpq - as a dependency for libpqxx
 - boost::program_options - to parse command line arguments
 - boost::uuids - To handle uuid fields nicely in employee ids
 - boost::lexical_cast - To cast between the string representations returned by the database and internal numerical representation of data