#include <iostream>
#include <string>
#include <map>
#include <vector>

#include <assert.h>
#include <leveldb/db.h>
#include <clip.h>

void printHelpMsg(char** argv) {
    std::cout << "Usage :\n";
    std::cout << "\t" << argv[0] << "<command> <name> [<value>]\n" << std::endl;
    std::cout << "Type of <command> : get, set, list" << std::endl;
}

std::map<std::string, std::string> parseArgs(int argc, char** argv) {
    std::map<std::string, std::string> ret_dict;

    int command_idx = 1;
    int name_idx = 2;
    int value_idx = 3;
    ret_dict["command"] = argv[command_idx];

    if (ret_dict["command"] == "get") {
        ret_dict["name"] = argv[name_idx];
    } else if (ret_dict["command"] == "set") {
        ret_dict["name"] = argv[name_idx];
        ret_dict["value"] = argv[value_idx];
    }

    return ret_dict;
}

void checkDBStatus(leveldb::Status &status) {
    if (!status.ok()) {
        std::cerr << status.ToString() << std::endl;
        exit(1);
    }
}

int main(int argc, char** argv) {
    if (argc <= 1) {
        printHelpMsg(argv);
        exit(1);
    }

    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "/tmp/clipboard_db", &db);
    checkDBStatus(status);

    auto arg_dict = parseArgs(argc, argv);
    auto command = arg_dict["command"];
    if (command == "get") {
        auto name = arg_dict["name"];

        std::string value;
        status = db->Get(leveldb::ReadOptions(), name, &value);
        checkDBStatus(status);

        clip::set_text(value);

        std::cout << "Copying the data to clipboard..." << std::endl;
    } else if (command == "set") {
        auto name = arg_dict["name"];
        auto value = arg_dict["value"];

        status = db->Put(leveldb::WriteOptions(), name, value);
        checkDBStatus(status);

        std::cout << "Saving the data to DB..." << std::endl;
    } else if (command == "list") {
        std::cout << "Name\t\tValue" << std::endl;

        auto* it = db->NewIterator(leveldb::ReadOptions());
        for (it->SeekToFirst(); it->Valid(); it->Next()) {
            std::cout << it->key().ToString() << "\t\t" << it->value().ToString() << '\n';
        }
    } else {
       std::cout << "Error : unknown command" << std::endl;
       exit(1);
    }

    return 0;
}
