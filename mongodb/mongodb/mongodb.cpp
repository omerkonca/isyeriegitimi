#pragma once

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

auto mongoURIStr = getEnvironmentVariable("MONGODB_URI");
static const mongocxx::uri mongoURI = mongocxx::uri{ mongoURIStr };


// ********************************************** Database Methods **********************************************

// Get all the databases from a given client.
vector<string> getDatabases(mongocxx::client& client)
{
	return client.list_database_names();
}


// ********************************************** Collection Methods **********************************************

// Create a new collection in the given database.
void createCollection(mongocxx::database& db, const string& collectionName)
{
	db.create_collection(collectionName);
}

// Print the contents of the given collection.
void printCollection(mongocxx::collection& collection)
{
	// Check if collection is empty.
	if (collection.count_documents({}) == 0)
	{
		cout << "Collection is empty." << endl;
		return;
	}

	auto cursor = collection.find({});

	for (auto&& doc : cursor)
	{
		cout << bsoncxx::to_json(doc) << endl;
	}
}

// ********************************************** Document Methods **********************************************

// Create a document from the given key-value pairs.
bsoncxx::document::value createDocument(const vector<pair<string, string>>& keyValues)
{
	bsoncxx::builder::stream::document document{};

	for (auto& keyValue : keyValues)
	{
		document << keyValue.first << keyValue.second;
	}

	return document << bsoncxx::builder::stream::finalize;
}

// Insert a document into the given collection.
void insertDocument(mongocxx::collection& collection, const bsoncxx::document::value& document)
{
	collection.insert_one(document.view());
}

// Delete a document from a given collection.
void deleteDocument(mongocxx::collection& collection, const bsoncxx::document::value& document)
{
	collection.delete_one(document.view());
}

// Update the document with given key-value pair.
void updateDocument(mongocxx::collection& collection, const string& key, const string& value, const string& newKey, const string& newValue)
{
	collection.update_one(bsoncxx::builder::stream::document{} << key << value << bsoncxx::builder::stream::finalize,
		bsoncxx::builder::stream::document{} << "$set" << bsoncxx::builder::stream::open_document << newKey << newValue << bsoncxx::builder::stream::close_document << bsoncxx::builder::stream::finalize);
}

// Find the document with given key-value pair.
void findDocument(mongocxx::collection& collection, const string& key, const string& value)
{
	// Create the query filter
	auto filter = bsoncxx::builder::stream::document{} << key << value << bsoncxx::builder::stream::finalize;

	//Add query filter argument in find
	auto cursor = collection.find({ filter });

	for (auto&& doc : cursor)
	{
		cout << bsoncxx::to_json(doc) << endl;
	}
}


// ********************************************** I/O Methods **********************************************

// Input student record.
void inputStudentRecord(mongocxx::collection& collection)
{
	string name, rollNo, branch, year;

	cout << "Enter name: ";
	cin >> name;

	cout << "Enter roll number: ";
	cin >> rollNo;

	cout << "Enter branch: ";
	cin >> branch;

	cout << "Enter year: ";
	cin >> year;

	insertDocument(collection, createDocument({ {"name", name}, {"rollNo", rollNo}, {"branch", branch}, {"year", year} }));
}

// Update student record.
void updateStudentRecord(mongocxx::collection& collection)
{
	string rollNo, newBranch, newYear;

	cout << "Enter roll number: ";
	cin >> rollNo;

	cout << "Enter new branch: ";
	cin >> newBranch;

	cout << "Enter new year: ";
	cin >> newYear;

	updateDocument(collection, "rollNo", rollNo, "branch", newBranch);
	updateDocument(collection, "rollNo", rollNo, "year", newYear);
}

// Find student record.
void findStudentRecord(mongocxx::collection& collection)
{
	string rollNo;

	cout << "Enter roll number: ";
	cin >> rollNo;

	findDocument(collection, "rollNo", rollNo);
}

// Delete student record.
void deleteStudentRecord(mongocxx::collection& collection)
{
	string rollNo;

	cout << "Enter roll number: ";
	cin >> rollNo;

	deleteDocument(collection, createDocument({ {"rollNo", rollNo} }));
}

// Print student records.
void printStudentRecords(mongocxx::collection& collection)
{
	printCollection(collection);
}


// ********************************************** Main **********************************************
int main()
{
	if (mongoURI.to_string().empty())
	{
		cout << "URI is empty";
		return 0;
	}

	// Create an instance.
	mongocxx::instance inst{};

	mongocxx::options::client client_options;
	auto api = mongocxx::options::server_api{ mongocxx::options::server_api::version::k_version_1 };
	client_options.server_api_opts(api);
	mongocxx::client conn{ s_Cluster0_uri, client_options };

	const string dbName = "StudentRecords";
	const string collName = "StudentCollection";

	auto dbs = getDatabases(conn);
	// Check if database already exists.
	if (!(std::find(dbs.begin(), dbs.end(), dbName) != dbs.end()))
	{
		// Create a new database & collection for students.
		conn[dbName];
	}

	auto studentDB = conn.database(dbName);
	auto allCollections = studentDB.list_collection_names();

	// Check if collection already exists.
	if (!(std::find(allCollections.begin(), allCollections.end(), collName) != allCollections.end()))
	{
		createCollection(studentDB, collName);
	}

	auto studentCollection = studentDB.collection(collName);

	// Create a menu to for user interaction
	int choice = -1;

	do while (choice != 0)
	{
		//system("cls");
		cout << endl << "**************************************************************************************************************" << endl;

		cout << "Enter 1 to input student record" << endl;
		cout << "Enter 2 to update student record" << endl;
		cout << "Enter 3 to find student record" << endl;
		cout << "Enter 4 to delete student record" << endl;
		cout << "Enter 5 to print all student records" << endl;
		cout << "Enter 0 to exit" << endl;
		cout << "Enter Choice : ";
		cin >> choice;

		cout << endl;

		switch (choice)
		{
		case 1:
			inputStudentRecord(studentCollection);
			break;
		case 2:
			updateStudentRecord(studentCollection);
			break;
		case 3:
			findStudentRecord(studentCollection);
			break;
		case 4:
			deleteStudentRecord(studentCollection);
			break;
		case 5:
			printStudentRecords(studentCollection);
			break;
		case 0:
			break;
		default:
			cout << "Invalid choice" << endl;
			break;
		}

	} while (choice != 0);

	return 0;
}