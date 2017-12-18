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
#include "include/json.hpp"

#ifndef BEYONDLIGHT_DATABASE_HH
#define BEYONDLIGHT_DATABASE_HH

namespace server {
    namespace storage {
        class Database {
        private:
            static Database *dbInstance;
            Database();

        protected:
            mongocxx::client client;
            mongocxx::database db;
            std::unordered_map<std::string, mongocxx::collection> collections;

        public:
            ~Database() = default;
            static Database *getDbInstance() {
                if (!dbInstance)
                    dbInstance = new Database();
                return dbInstance;
            }

            void createCollection(const std::string &);

            bsoncxx::stdx::optional<mongocxx::result::insert_one> insert(const std::string &, nlohmann::json &);
            bsoncxx::stdx::optional<mongocxx::result::insert_many> insertMultiple(const std::string &, std::vector<nlohmann::json> &);
            nlohmann::json getByKey(const std::string &, const std::string &, const std::string &);
            int32_t removeByKey(const std::string &, const std::string &, const std::string &);
        };
    }
}

#endif //BEYONDLIGHT_DATABASE_HH
