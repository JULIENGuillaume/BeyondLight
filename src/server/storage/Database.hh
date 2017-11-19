//
// Created by Antoine on 11/19/17.
//

#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/types.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include "../user/User.hh"

#ifndef BEYONDLIGHT_DATABASE_HH
#define BEYONDLIGHT_DATABASE_HH

namespace server {
    namespace storage {
        class Database {
        private:
            static Database *dbInstance;
            Database();

        protected:
            mongocxx::client client{mongocxx::uri{}};
            mongocxx::database db;
            mongocxx::collection users;

        public:
            ~Database() = default;
            static Database *getDbInstance() {
                if (!dbInstance)
                    dbInstance = new Database();
                return dbInstance;
            }
            bsoncxx::stdx::optional<mongocxx::result::insert_one> insertUser(const server::user::User &);
            bsoncxx::stdx::optional<mongocxx::result::insert_many> insertMultipleUsers(const std::vector<server::user::User> &);
            server::user::User *getUserByLogin(const std::string &);
            int32_t removeUserByLogin(const std::string &);
        };
    }
}

#endif //BEYONDLIGHT_DATABASE_HH
