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
	std::string display; 
  std::ostringstream priceFormat; 
  priceFormat << std::fixed << std::setprecision(2) << getPrice(); 
  display = getName() + "\n" + "Size: " + getSize() + " " + "Brand: " + getBrand() + "\n" + priceFormat.str() + " " + std::to_string(qty_) + " left." ; 
  return display; 
}

//Outputs database format of the product info 
void Clothing::dump(std::ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << std::fixed << std::setprecision(2) << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << std::endl;
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