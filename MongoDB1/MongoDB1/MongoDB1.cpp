#include <mongocxx/client.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
std::string getEnvironmentVariable(std::string environmentVarKey)
{
	char* pBuffer = nullptr;
	size_t size = 0;
	auto key = environmentVarKey.c_str();
	// Use the secure version of getenv, ie. _dupenv_s to fetch environment variable.
	if (_dupenv_s(&pBuffer, &size, key) == 0 && pBuffer != nullptr)
	{
		std::string environmentVarValue(pBuffer);
		free(pBuffer);
		return environmentVarValue;
	}
	else
	{
		return "";
	}
}
auto mongoURIStr = getEnvironmentVariable("mongodb://192.168.2.125:27017");
static const mongocxx::uri mongoURI = mongocxx::uri{ mongoURIStr };
// Get all the databases from a given client.
vector<string> getDatabases(mongocxx::client& client)
{
	return client.list_database_names();
}
int main()
{
	// Create an instance.
	mongocxx::instance inst{};
	mongocxx::options::client client_options;
	auto api = mongocxx::options::server_api{ mongocxx::options::server_api::version::k_version_1 };
	client_options.server_api_opts(api);
	mongocxx::client conn{ mongoURI, client_options };
	auto dbs = getDatabases(conn);
	for (auto db : dbs)
	{
		cout << db << endl;
	}
	return 0;
}