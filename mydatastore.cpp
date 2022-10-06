#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <set> 
#include "book.h"
#include "product.h"
#include "util.h"
#include "datastore.h"
#include "mydatastore.h"


void MyDataStore::addProduct(Product* p){
	productList.insert(p); 
	std::set<std::string> s = p->keywords(); 
	for(std::set<std::string>::iterator it = s.begin(); it != s.end(); ++it){
		if(s.find(*it) == s.end()){
			std::set<Product*> prodSet;
			prodSet.insert(p); 
			keyMap.insert(std::make_pair(*it, prodSet)); 
		}
		else{
			keyMap[*it].insert(p); 
		}
	}

} 

void MyDataStore::addUser(User* u){
 
	userList.insert(u); 
	std::string username = u->getName(); 
	userMap.insert(std::make_pair(username, u)); 
} 

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){

	searchProd.clear(); 
	std::set<Product*> temp; 
	std::set<Product*> search; 
	for(std::vector<std::string>::iterator it = terms.begin(); it != terms.end(); ++it){
		std::map<std::string, std::set<Product*>>::iterator  proIt= keyMap.find(*it); 
		if(proIt != keyMap.end()){
			temp = proIt->second;
			if(search.empty()){
				search = temp; 
			}
			else if(!search.empty){
				if(type == 0){
					search = setIntersection(temp, search); 
				}
				if(type == 1){
					search = setUnion(temp, search); 
				}
			}
		}
	}
	for(std::set<Product*>::iterator setIt = search.begin(); setIt != search.end(); ++setIt){
		searchProd.push_back(*setIt); 
	}
	return searchProd; 
}

void MyDataStore::dump(std::ostream& ofile){
	//output products 
	ofile << "<products>" << std::endl;  
	for(std::set<Product*>::iterator proDumpIt = productList.begin(); proDumpIt != productList.end(); ++proDumpIt){
		(*proDumpIt)->dump(ofile); 
	} 
	ofile << "</products>" << std::endl; 
	//output users 
	ofile << "<users>" << std::endl; 
	for(std::set<User*>::iterator userDumpIt = userList.begin(); it != userList.end(); ++userDumpIt){
		(*userDumpIt)->dump(ofile); 
	}
	ofile << "</users>"
} //done 

void MyDataStore::buyCart(std::string username){
	std::map<std::string, std::vector<Product*>>::iterator it = userCart.find(username); 
	if(it != userCart.end()){
		std::vector<Product*> uCart = it->second; 
		for(unsigned int i = 0; i < uCart.size(); i++){
			int quant = uCart[i]->getQty(); 
			double price = uCart[i]->getPrice(); 
			std::map<std::string, User*>::iterator it0 = userMap.find(username); 
			User* currUser = it0->second; 
			int balance = currUser->getBalance(); 
			if(quant > 0 && balance >= price){
				uCart[i]->subtractQty(1); 
				currUser->deductAmount(price); 
				uCart.erase(uCart.begin() + i); 
			}
			else{
				if(quant < 0){
					std::cout << "Item no longer in stock." << std::endl; 
				}
				if(price > balance){
					std::cout << "Insufficient funds." std::endl; 
				}
			}
		}
		it->second = uCart; 
	}
	else{
		std::cout << "Invalid request." << std::endl; 
		return; 
	}
}

void MyDataStore::viewCart(std::string username){
	std::map<std::string, std::vector<Product*>>::iterator it = userCart.find(username); 
	if(it != userCart.end()){
		int count = 1; 
		std::vector<Product*> uCart = it->second; 
		for(std::vector<Product*>::iterator it1 = uCart.begin(); it1 != uCart.end(); ++it1){
			Product* p = *it1; 
			std::string prodName = p->getName(); 
			prodName = convToLower(prodName); 
			std::cout << count << ": " << prodName << std::endl; 
			count++; 
		}
	}
	else{
		std::cout << "Invalid request." << std::endl; 
		return; 
	}
}

void MyDataStore::addCart(std::string username, int hitIndex){
	hitIndex = hitIndex-1; 
	const int searchSize = searchProd.size(); 
	if(hitIndex >= searchSize){
		std::cout << "Invalid request." << std::endl; 
		return; 
	}
	std::map<std::string, User*>::iterator userFinder = userMap.find(username); 
	if(userFinder != userMap.end()){
		std::map<std::string, std::vector<Product*>>::iterator it = userCart.find(username); 
		if(it != userCart.end()){
			it->second.push_back(searchProd[hitIndex]);
		}
		else if(it == userCart.end()){
			std::vector<Product*> newProdVec; 
			newProdVec.push_back(searchProd[hitIndex]); 
			userCart.insert(std::make_pair(username, newProdVec)); 
		}
	}
	else{
		std::cout << "Invalid request" << std::endl; 
	}
}

