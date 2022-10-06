#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include "product.h"
#include "user.h"
#include "datastore.h"


class MyDataStore: public DataStore{
public:
    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);

		//functionality of amazon 
		void addCart(std::string username, int hitIndex); 
		void buyCart(std::string username); 
		void viewCart(std::string username); 

private:
		std::set<Product*> productList; //productDatabase
		std::set<User*> userList; //userDatabase
    std::vector<Product*> searchProd; //searchVec

		std::map<std::string, std::set<Product*>> keyMap; //myDataStoreMap
		//map username to user 
		std::map<std::string, User*> userMap; //myUserMap
    //map username to products 
    std::map<std::string, std::vector<Product*>> userCart; //usersCartMap

};

#endif

