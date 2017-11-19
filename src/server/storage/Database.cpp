//
// Created by Antoine on 11/19/17.
//

#include <sstream>
#include "Database.hh"

server::storage::Database *server::storage::Database::dbInstance = nullptr;

server::storage::Database::Database() {
    db = client.database("users.db");
    users = db.collection("users");
}

bsoncxx::stdx::optional<mongocxx::result::insert_one> server::storage::Database::insertUser(const server::user::User &usr) {
    bsoncxx::builder::basic::document builder {};

    builder.append(bsoncxx::builder::basic::kvp("_id", bsoncxx::types::b_utf8{std::to_string(usr.getId())}),
                   bsoncxx::builder::basic::kvp("login", usr.getLogin()),
                   bsoncxx::builder::basic::kvp("password", "default"));

    return users.insert_one(builder.extract());
}

bsoncxx::stdx::optional<mongocxx::result::insert_many> server::storage::Database::insertMultipleUsers(const std::vector<server::user::User> &usrs) {
    std::vector<bsoncxx::document::value> docs;

    for (const auto &usr : usrs) {
        bsoncxx::builder::basic::document builder {};

        builder.append(bsoncxx::builder::basic::kvp("_id", bsoncxx::types::b_utf8{std::to_string(usr.getId())}),
                       bsoncxx::builder::basic::kvp("login", usr.getLogin()),
                       bsoncxx::builder::basic::kvp("password", "default"));

        docs.push_back(builder.extract());
    }

    return users.insert_many(docs);
}

server::user::User *server::storage::Database::getUserByLogin(const std::string &l) {
    bsoncxx::builder::basic::document builder {};

    builder.append(bsoncxx::builder::basic::kvp("login", l));

    bsoncxx::stdx::optional<bsoncxx::document::value> usrDoc = users.find_one(builder.extract());

    if (usrDoc) {
        std::stringstream ss;

        unsigned long int usrId;
        std::string usrLogin;

        for (auto it : usrDoc.value().view()) {
            if (it.key().to_string() == "_id") {
                ss << it.get_utf8().value.to_string();
                ss >> usrId;
            } else if (it.key().to_string() == "login") {
                usrLogin = it.get_utf8().value.to_string();
            }
        }
        if (usrId && !usrLogin.empty())
            return new server::user::User(usrId, usrLogin);
    }
    return nullptr;
}

int32_t server::storage::Database::removeUserByLogin(const std::string &l) {
    bsoncxx::builder::basic::document builder {};

    builder.append(bsoncxx::builder::basic::kvp("login", l));

    auto res = users.delete_one(builder.extract());

    return res.value().deleted_count();
}

