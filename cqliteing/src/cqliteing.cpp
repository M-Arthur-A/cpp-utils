#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>


int main() {
	try {
		// Open a database file
		SQLite::Database    db("/home/arthur/Downloads/database.sqlite");

		// Compile a SQL query, containing one parameter (index 1)
		SQLite::Statement   query(db, "SELECT * FROM notes");
		while (query.executeStep()) {
			std::cout << query.getColumn(3) << std::endl;
		}
	}
	catch (std::exception& e)
	{
	    std::cout << "exception: " << e.what() << std::endl;
	}
	return 0;
}
