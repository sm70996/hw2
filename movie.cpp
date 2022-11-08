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
	std::string display; 
	std::ostringstream priceFormat; 
	priceFormat << std::fixed << std::setprecision(2) << getPrice(); 
	display = getName() + "\n" + "Genre: " + getGenre() + " " + "Rating: " + getRating() + "\n" + priceFormat.str() + " " + std::to_string(qty_) + " left." ; 
	return display; 
}

//Outputs database format of the product info 
void Movie::dump(std::ostream& os) const
{ 
	os << category_ << "\n" << name_ << "\n" << std::fixed << std::setprecision(2) << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << std::endl;
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