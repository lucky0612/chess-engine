#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sqlite3.h>
#include "../src/core/board.h"
#include "../src/core/move.h"

class OpeningBook
{
public:
    OpeningBook(const std::string &dbPath) : dbPath(dbPath) {}

    void generateFromPGN(const std::string &pgnPath)
    {
        sqlite3 *db;
        if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK)
        {
            std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
            return;
        }

        // Create table if not exists
        const char *createTableSQL =
            "CREATE TABLE IF NOT EXISTS openings ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "fen TEXT NOT NULL,"
            "move TEXT NOT NULL,"
            "weight REAL NOT NULL);";

        char *errMsg = 0;
        if (sqlite3_exec(db, createTableSQL, 0, 0, &errMsg) != SQLITE_OK)
        {
            std::cerr << "SQL error: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }

        // Read PGN file and insert openings
        std::ifstream pgnFile(pgnPath);
        std::string line;
        while (std::getline(pgnFile, line))
        {
            // Parse PGN and insert openings
            // This is a placeholder for the actual PGN parsing logic
            std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
            std::string move = "e2e4";
            double weight = 1.0;

            std::string insertSQL =
                "INSERT INTO openings (fen, move, weight) VALUES ('" +
                fen + "', '" + move + "', " + std::to_string(weight) + ");";

            if (sqlite3_exec(db, insertSQL.c_str(), 0, 0, &errMsg) != SQLITE_OK)
            {
                std::cerr << "SQL error: " << errMsg << std::endl;
                sqlite3_free(errMsg);
            }
        }

        sqlite3_close(db);
    }

private:
    std::string dbPath;
};

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <pgn_file> <db_file>" << std::endl;
        return 1;
    }

    std::string pgnPath = argv[1];
    std::string dbPath = argv[2];

    OpeningBook book(dbPath);
    book.generateFromPGN(pgnPath);

    std::cout << "Opening book generated successfully." << std::endl;
    return 0;
}