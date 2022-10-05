#include <sstream>
#include <iomanip>

#include "book.h"
#include "product.h"
#include "util.h"

Book::Book(const std::string category, const std::string name, double price, int qty, std::string isbn, std::string author):Product(category, name, price, qty), isbn_(isbn),  author_(author)
{
	
}

Book::~Book()
{

}

//Returns appropriate keyword to index the product 
std::set<std::string> Book::keywords() const
{
	std::set<std::string> s1 = parseStringToWords(name_); 
	std::set<std::string> s2 = parseStringToWords(author_); 
	std::set<std::string> keys = setUnion(s1, s2); 
	keys.insert(isbn_); 
	return keys; 
}

//Create string that contains prouct info 
std::string Book::displayString() const
{
	std::string str = name_ + "\n" + "Author: " + author_ + " " + "ISBN: " + isbn_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left." + "\n" + "Rating: "; 
	return str; 
}

//Outputs database format of the product info 
void Book::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << std::endl;
}

// Accessors and mutators 
std::string Book::getISBN() const
{
	return isbn_; 
}

std::string Book::getAuthor() const
{
	return author_; 
}