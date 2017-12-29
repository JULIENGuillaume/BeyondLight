//
// Created by Antoine on 11/19/17.
//

#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/types.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <json.hpp>
#include <unordered_map>
#include "../user/User.hh"

#ifndef BEYONDLIGHT_DATABASE_HH
#define BEYONDLIGHT_DATABASE_HH

namespace bl {
	namespace server {
		namespace storage {
			class Database {
			public:
				Database();
				~Database() = default;

			public:
				void createCollection(const std::string &);
				bsoncxx::stdx::optional<mongocxx::result::insert_one> insert(const std::string &, nlohmann::json &);
				bsoncxx::stdx::optional<mongocxx::result::insert_many> insertMultiple(const std::string &, std::vector<nlohmann::json> &);
				nlohmann::json getByKey(const std::string &, const std::string &, const std::string &);
				int32_t removeByKey(const std::string &, const std::string &, const std::string &);
				bsoncxx::stdx::optional<mongocxx::result::insert_one> update(const std::string &, const std::string &, const std::string &, nlohmann::json &);

			protected:
				static mongocxx::instance m_inst;
				mongocxx::client m_client;
				mongocxx::database m_db;
				std::unordered_map<std::string, mongocxx::collection> m_collections;
			};
		}
	}
}

#endif //BEYONDLIGHT_DATABASE_HH
