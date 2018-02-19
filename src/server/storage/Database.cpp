//
// Created by Antoine on 11/19/17.
//

#include <sstream>
#include <iostream>
#include <mongocxx/exception/bulk_write_exception.hpp>
#include <mongocxx/client.hpp>
#include "Database.hh"

mongocxx::instance bl::server::storage::Database::m_inst{};

bl::server::storage::Database::Database() {
	try {
		m_client = mongocxx::client(mongocxx::uri{});
		m_db = m_client["BeyondLightDb"];
		auto cursor1 = m_db.list_collections();
		for (const bsoncxx::document::view &doc :cursor1) {
			bsoncxx::document::element ele = doc["name"];
			std::string name = ele.get_utf8().value.to_string();
			std::cout << name << std::endl;
			m_collections[name] = m_db[name];

		}
	} catch (std::exception const &e) {
		std::cerr << e.what() << std::endl;
	}
}

void bl::server::storage::Database::createCollection(const std::string &collName) {
	try {
		m_collections[collName] = m_db[collName];
	} catch (std::exception &e) {
		std::cerr << "Failed to create collection: " << e.what() << std::endl;
	}
}

bsoncxx::stdx::optional<mongocxx::result::insert_one>
bl::server::storage::Database::insert(const std::string &collName, nlohmann::json toInsert) {
	//bsoncxx::builder::basic::document builder{};

	//builder.append(bsoncxx::from_json(toInsert.dump()));
	//builder.append(bsoncxx::builder::basic::kvp("JSON", toInsert.dump()));
	/*for (nlohmann::json::iterator it = toInsert.begin(); it != toInsert.end(); ++it) {
		//auto tmp = bsoncxx::builder::basic::kvp(it.key(), it.value().dump());
		if (it.value().is_string()) {
			std::string str = it.value();
			builder.append(bsoncxx::builder::basic::kvp(it.key(), str));
		} else {
			builder.append(bsoncxx::builder::basic::kvp(it.key(), it.value().dump()));
		}
	}*/

	if (m_collections.find(collName) == m_collections.end())
		createCollection(collName);

	return m_collections[collName].insert_one(bsoncxx::from_json(toInsert.dump()));
}

bsoncxx::stdx::optional<mongocxx::result::insert_many>
bl::server::storage::Database::insertMultiple(const std::string &collName, std::vector<nlohmann::json> &elements) {
	std::vector<bsoncxx::document::value> docs;

	for (auto &element : elements) {
		bsoncxx::builder::basic::document builder{};

		for (nlohmann::json::iterator it = element.begin(); it != element.end(); ++it) {
			builder.append(bsoncxx::builder::basic::kvp(it.key(), it.value().dump()));
		}

		docs.push_back(builder.extract());
	}

	if (m_collections.find(collName) == m_collections.end())
		createCollection(collName);

	return m_collections[collName].insert_many(docs);
}

nlohmann::json bl::server::storage::Database::getByKey(const std::string &collName, const std::string &key, const std::string &value) {
	if (m_collections.find(collName) == m_collections.end()) {
		return nullptr;
	}

	bsoncxx::builder::basic::document builder{};

	builder.append(bsoncxx::builder::basic::kvp(key, value));

	bsoncxx::stdx::optional<bsoncxx::document::value> usrDoc = m_collections[collName].find_one(builder.extract());
	auto cursor = m_collections[collName].find(builder.extract());

	if (usrDoc) {
		return nlohmann::json::parse(bsoncxx::to_json(usrDoc.value().view()).data());
	}

	return nullptr;
}

int32_t bl::server::storage::Database::removeByKey(const std::string &collName, const std::string &key, const std::string &value) {
	if (m_collections.find(collName) == m_collections.end())
		return 0;

	bsoncxx::builder::basic::document builder{};

	builder.append(bsoncxx::builder::basic::kvp(key, value));

	auto res = m_collections[collName].delete_one(builder.extract());

	return res.value().deleted_count();
}

bsoncxx::stdx::optional<mongocxx::result::insert_one> bl::server::storage::Database::update(const std::string &collName,
                                                                                            const std::string &key,
                                                                                            const std::string &value,
                                                                                            nlohmann::json toInsert) {
	std::cout << "Starting to update..." << std::endl;
	try {
		try {
			removeByKey(collName, key, value);
			removeByKey(collName, key, value);//fixme
		} catch (std::exception const& e) {
			std::cerr << "Error in deletion: " << e.what() << std::endl;
		}
		std::cout << "Update succeed ..." << std::endl;
		return this->insert(collName, toInsert);
	} catch (std::exception &e) {
		std::cerr << "Failed to insert in db: " << e.what() << std::endl;
	}
	std::cout << "Update failed..." << std::endl;
	return bsoncxx::stdx::optional<mongocxx::result::insert_one>{};
}
