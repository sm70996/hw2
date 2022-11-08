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
  std::set<std::string> keySet = p->keywords(); 
  searchProd.push_back(p); 
  for(std::set<std::string>::iterator it = keySet.begin(); it != keySet.end(); ++it){
    if(keyMap.find(*it) == keyMap.end()){
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
  std::vector<Product*> userProd; 
  userCart.insert(std::make_pair(u, userProd));  
  userMap.insert(std::make_pair(u->getName(), u)); 
} 

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){

  std::vector<Product*> vecProd;  
  std::set<Product*> setProd; 
  std::set<Product*> setTerm;  
  /*for(std::vector<std::string>::iterator it = terms.begin(); it != terms.end(); ++it){
    std::map<std::string, std::set<Product*>>::iterator  proIt= keyMap.find(*it); 
    if(proIt != keyMap.end()){
      temp = proIt->second;
      if(search.empty()){
        search = temp; 
      }
      else if(!search.empty()){
        if(type == 0){
          search = setIntersection(temp, search); 
        }
        if(type == 1){
          search = setUnion(temp, search); 
        }
      }
    }
  } */

  for(unsigned int i = 0; i < terms.size(); i++){
    if(type == 0){
      setTerm = keyMap[terms[0]]; 
      setProd = keyMap[terms[i]]; 
      setTerm = setIntersection(setTerm, setProd); 
    }
    else if(type == 1){
      setProd = keyMap[terms[i]]; 
      setTerm = setUnion(setTerm, setProd); 
    }
  }
  for(std::set<Product*>::iterator setIt = setTerm.begin(); setIt != setTerm.end(); ++setIt){
    vecProd.push_back(*setIt); 
  }
  return vecProd; 

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
  for(std::set<User*>::iterator userDumpIt = userList.begin(); userDumpIt != userList.end(); ++userDumpIt){
    (*userDumpIt)->dump(ofile); 
  }
  ofile << "</users>";  
} //done 

void MyDataStore::buyCart(std::string username){
  /*std::map<std::string, std::vector<Product*>>::iterator it = userCart.find(username); 
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
          std::cout << "Insufficient funds." << std::endl; 
        }
      }
    }
    it->second = uCart; 
  }
  else{
    std::cout << "Invalid request." << std::endl; 
    return; 
  }*/

  User* user; 
  if(userMap.find(username) == userMap.end()){
    std::cout << "Invalid username" << std::endl; 
    return; 
  }

  user = userMap.find(username)->second; 
  std::vector<Product*> items = userCart[user]; 
  if(items.begin() == items.end()){
    std::cout << "Cart is empty" << std::endl; 
    return; 
  }
  std::vector<Product*> itemLeft; 
  for(std::vector<Product*>::iterator it = items.begin(); it != items.end(); ++it){
    if((*it)->getPrice() > user->getBalance()){
      std::cout << user->getName() << " doesn't have enough money for: " << (*it)->getName() << " (" << (*it)->getPrice() << ")" << std::endl; 
      itemLeft.push_back(*it); 
    }
    else if((*it)->getQty() == 0){
      std::cout << "We are currently out of stock of: " << (*it)->getName() << std::endl; 
    }
    else{
      user->deductAmount((*it)->getPrice()); 
      (*it)->subtractQty(1); 
      std::cout << user->getName() << " has $" << user->getBalance() << " left." << std::endl; 
    }
  }
  userCart[user] = itemLeft; 
  return; 
}

void MyDataStore::viewCart(std::string username){
  /*std::map<std::string, std::vector<Product*>>::iterator it = userCart.find(username); 
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
  }*/

  User* user; 
  if(userMap.find(username) == userMap.end()){
    std::cout << "Invalid username" << std::endl; 
    return; 
  }
  user = userMap.find(username)->second; 
  std::vector<Product*> items = userCart[user]; 
  if(items.begin() == items.end()){
    std::cout << "Cart is empty!" << std::endl;
    return; 
  }
  int itemNum = 1; 
  for(std::vector<Product*>::iterator it = items.begin(); it != items.end(); ++it){
    std::cout << "Item " << std::setw(3) << itemNum << std::endl; 
    std::cout << (*it)->displayString() << std::endl; 
    std::cout << std::endl; 
    itemNum++; 
  }
}

void MyDataStore::addCart(std::string username, std::string search_hit, std::vector<Product*> hits){
  /*hitIndex = hitIndex-1; 
  const int searchSize = searchProd.size(); 
  if(hitIndex >= searchSize){
    std::cout << "Invalid error" << std::endl; 
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
  } */
  if(hits.empty()){
    std::cout << "No products available" << std::endl; 
    return; 
  }
  unsigned int search_hit_number = stoi(search_hit); 
  User* user; 
  if(search_hit_number > hits.size()){
    std::cout << "Invalid request" << std::endl; 
    return; 
  }
  if(userMap.find(username) == userMap.end()){
    std::cout << "Invalid request" << std::endl; 
    return; 
  }
  else{
    user = userMap.find(username)->second; 
    userCart[user].push_back(hits[search_hit_number - 1]); 
    return; 
  }
}


