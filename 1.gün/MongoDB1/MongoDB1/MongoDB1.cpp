//#include <iostream>
//
//#include <bsoncxx/builder/stream/document.hpp>
//#include <bsoncxx/json.hpp>
//
//#include <mongocxx/client.hpp>
//#include <mongocxx/instance.hpp>
//
//int main(int, char**) {
//	mongocxx::instance inst{};
//	mongocxx::client conn{ mongocxx::uri{"mongodb://192.168.68.121:27017"} };
//
//	bsoncxx::builder::stream::document document{};
//
//	auto collection = conn["admin"]["isim"];
//	//document << "hello" << "world";
//
//	collection.insert_one(document.view());
//	auto cursor = collection.find({});
//
//	for (auto&& doc : cursor) {
//		std::cout << bsoncxx::to_json(doc) << std::endl;
//	}
//}
//
//// mongocxx::client conn{mongocxx::uri{"mongodb://<username>:<password>@<host>:<27017>"}};
//
//


#include <iostream>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>

int main() {
    mongocxx::instance instance{}; // MongoDB istemci nesnesi oluşturuluyor
    mongocxx::client client{ mongocxx::uri{"mongodb://192.168.68.121:27017"} }; // MongoDB sunucusuna bağlanılıyor
    auto collection = client["admin"]["isim"]; // "testdb" veritabanına ve "testcollection" koleksiyonuna erişiliyor
    auto builder = bsoncxx::builder::stream::document{}; // Belge oluşturma nesnesi
    bsoncxx::document::value doc_value = builder
        << "name" << "John"
        << "age" << 28
        << bsoncxx::builder::stream::finalize; // Oluşturulan belge, adı "doc_value" olan bir değer nesnesinde saklanıyor
    bsoncxx::stdx::optional<mongocxx::result::insert_one> result = collection.insert_one(doc_value.view()); // Belge, "testcollection" koleksiyonuna ekleniyor
    //if (result) {
    //    std::cout << "Belge başarıyla eklendi: " << bsoncxx::to_json(result->inserted_id()) << "\n"; // Eklenen belgenin ObjectId'si yazdırılıyor
    //}
    return 0;
}