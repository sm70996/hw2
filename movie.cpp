#include <sstream>
#include <iomanip>
#include <iostream>

#include "movie.h"
#include "product.h"
#include "util.h"

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating): Product(category, name, price, qty), genre_(genre),  rating_(rating)
{
	
}

Movie::~Movie()
{

}

//Returns appropriate keyword to index the product 
std::set<std::string> Movie::keywords() const
{
	std::set<std::string> s1 = parseStringToWords(name_); 
	std::set<std::string> s2 = parseStringToWords(genre_); 
	std::set<std::string> keys = setUnion(s1,s2); 
	return keys;  
}

//Create string that contains prouct info 
std::string Movie::displayString() const
{
	std::string str = name_ + "\n" + "Genre: " + genre_ + " " + "Rating: " + rating_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left." + "\n" + "Rating: "; 
	return str; 
}

//Outputs database format of the product info 
void Movie::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << std::endl;
}

// Accessors and mutators 
std::string Movie::getGenre() const
{
	return genre_; 
}

std::string Movie::getRating() const
{
	return rating_; 
}