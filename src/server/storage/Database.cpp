//
// Created by Antoine on 11/19/17.
//

#include <sstream>
#include <iostream>
#include <mongocxx/exception/bulk_write_exception.hpp>
#include "Database.hh"

server::storage::Database *server::storage::Database::dbInstance = nullptr;

server::storage::Database::Database() {
	mongocxx::uri uri("mongodb://localhost:12345");
	client = mongocxx::client(uri);

    db = client["storage"];
}

void server::storage::Database::createCollection(const std::string &collName) {
    collections[collName] = db[collName];
}

bsoncxx::stdx::optional<mongocxx::result::insert_one>
server::storage::Database::insert(const std::string &collName, nlohmann::json &toInsert) {
    bsoncxx::builder::basic::document builder {};

    for (auto it = toInsert.begin(); it != toInsert.end(); ++it) {
        //auto tmp = bsoncxx::builder::basic::kvp(it.key(), it.value().dump());
        builder.append(bsoncxx::builder::basic::kvp(it.key(), it.value().dump()));
    }

    if (collections.find(collName) == collections.end())
        createCollection(collName);

    return collections[collName].insert_one(builder.extract());
}

bsoncxx::stdx::optional<mongocxx::result::insert_many>
server::storage::Database::insertMultiple(const std::string &collName, std::vector<nlohmann::json> &elements) {
    std::vector<bsoncxx::document::value> docs;

    for (auto &element : elements) {
        bsoncxx::builder::basic::document builder {};

        for (auto it = element.begin(); it != element.end(); ++it) {
            builder.append(bsoncxx::builder::basic::kvp(it.key(), it.value().dump()));
        }

        docs.push_back(builder.extract());
    }

    if (collections.find(collName) == collections.end())
        createCollection(collName);

    return collections[collName].insert_many(docs);
}

nlohmann::json server::storage::Database::getByKey(const std::string &collName, const std::string &key, const std::string &value) {
    if (collections.find(collName) == collections.end())
        return nullptr;

    bsoncxx::builder::basic::document builder {};

    builder.append(bsoncxx::builder::basic::kvp(key, value));

    bsoncxx::stdx::optional<bsoncxx::document::value> usrDoc = collections[collName].find_one(builder.extract());

    if (usrDoc) {
        nlohmann::json j;

        for (auto field : usrDoc.value().view()) {
            j[field.key().to_string()] = field.get_utf8().value.to_string();
        }

        return j;
    }

    return nullptr;
}

int32_t server::storage::Database::removeByKey(const std::string &collName, const std::string &key, const std::string &value) {
    if (collections.find(collName) == collections.end())
        return 0;

    bsoncxx::builder::basic::document builder{};

    builder.append(bsoncxx::builder::basic::kvp(key, value));

    auto res = collections[collName].delete_one(builder.extract());

    return res.value().deleted_count();
}