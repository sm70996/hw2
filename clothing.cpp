#include <sstream>
#include <iomanip>

#include "clothing.h"
#include "product.h"
#include "util.h"

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, std::string brand, std::string size):Product(category, name, price, qty), brand_(brand), size_(size)
{
	
}

Clothing::~Clothing()
{

}

//Returns appropriate keyword to index the product 
std::set<std::string> Clothing::keywords() const
{
	std::set<std::string> s1 = parseStringToWords(name_); 
	std::set<std::string> s2 = parseStringToWords(brand_); 
	std::set<std::string> keys = setUnion(s1,s2); 
	return keys; 
}

//Create string that contains product info 
std::string Clothing::displayString() const
{
	std::string str = name_ + "\n" + "Size: " + size_ + " " + "Brand: " + brand_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + 
	" left." + "\n" + "Rating: "; 
	return str;
}

//Outputs database format of the product info 
void Clothing::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << std::endl;
}

//Accessoors and mutators 
std::string Clothing::getBrand() const
{
	return brand_; 
}

std::string Clothing::getSize() const
{
	return size_; 
}