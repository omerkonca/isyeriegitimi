#include <thread>


#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>
#include <bsoncxx/document/value.hpp>
#include <bsoncxx/document/view.hpp>
#include <mongocxx/options/find.hpp>
#include <mongocxx/collection.hpp>
#include <string>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;


void task1(std::string msg)
{
    //std::cout << "task1 says: " << msg;

    // MONGO
   /*  mongocxx::instance inst{};
     mongocxx::client conn{ mongocxx::uri{} };

     bsoncxx::builder::stream::document document{};

     auto collection = conn["testdb"]["testcollection"];
     document << "hello" << "world";

     collection.insert_one(document.view());
     auto cursor = collection.find({});

     for (auto&& doc : cursor) {
         std::cout << bsoncxx::to_json(doc) << std::endl;
     }*/

     ///
    mongocxx::instance inst{};
    mongocxx::client conn{ mongocxx::uri{"mongodb://192.168.2.125:27017" } };

    //  bsoncxx::builder::stream::document document{};

    auto collection = conn["robutel_local_log"]["NSWLog"];
    //document << "hello" << "world";

    //collection.insert_one(document.view());

    auto order = bsoncxx::builder::stream::document{} << "$natural" << -1 << bsoncxx::builder::stream::finalize;

    mongocxx::options::find opts;
    opts.sort(order.view());
    opts.limit(1);

    auto cursor = collection.find({}, opts);

    for (auto&& doc : cursor) {
        std::cout << bsoncxx::to_json(doc) << std::endl;

        bsoncxx::document::element timestamp = doc["Timestamp"];

        bsoncxx::document::element wwa = doc["wWA"];
        bsoncxx::document::element rwa = doc["rWA"];

        bsoncxx::document::element wspeed = doc["wSpeed"];
        bsoncxx::document::element rspeed = doc["rSpeed"];

        bsoncxx::document::element angle = doc["Angle"];
        bsoncxx::document::element x = doc["X"];
        bsoncxx::document::element y = doc["Y"];

        bsoncxx::document::element ti = doc["ti"];
        bsoncxx::document::element ci = doc["ci"];



        // std::cout << std::endl;
        // std::cout << "X: " << curvename.get_int32().value << std::endl;


    }

    /* bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result =
         collection.find_one(document{} << "X" << 82464 << finalize);

     if (maybe_result) {
         std::cout << bsoncxx::to_json(*maybe_result) << "\n";


     }*/

}



int main(int, char**)
{
    ...

        std::thread t1(task1, "Hello");
    t1.join();

    ...
}