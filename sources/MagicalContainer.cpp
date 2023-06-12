#include <cmath>
#include <algorithm>
#include "MagicalContainer.hpp"

using namespace std;

namespace ariel{

	bool MagicalContainer::isPrime(int num) {

		if (num < 2){
			return false;
		}
		int i =2;
		while(i<=sqrt(num)){

			if (num % i == 0){
				return false;
			}
			i++;
		}return true;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void MagicalContainer::buildarrCross(){
		
			if(size()!=1){
			size_t counter = size() - 1;
			for (size_t i = 0; i <= counter; i++, counter--) {
				arrangedInCrossOrder.push_back(arrangedInAscendingOrder[i]);
				
				if (i != counter) {
					arrangedInCrossOrder.push_back(arrangedInAscendingOrder[counter]);
				}
			}
				
			}else{
				
				arrangedInCrossOrder.push_back(arrangedInAscendingOrder[0]);
			}
	}

	void MagicalContainer::addElement(int elem) {

		auto Insert = this->setOfElement.insert(elem);
		
		if(Insert.second == true){

			const int* value= &(*Insert.first);
			
			//Insert into the vector in ascending order

			auto index = lower_bound(arrangedInAscendingOrder.begin(), arrangedInAscendingOrder.end(), value, [](const int *lamdaA, const int *lamdaB) {return *lamdaA < * lamdaB;});

			arrangedInAscendingOrder.insert(index, value);

			//insert into the vector in cross order

			arrangedInCrossOrder.clear();

			this->buildarrCross();

			//insert into the vector of prime numbers

			if (isPrime(elem)==true)
			{
				auto index= lower_bound(OnlyPrimeNumbers.begin(), OnlyPrimeNumbers.end(), value);

				OnlyPrimeNumbers.insert(index, value);
			}
		}
	}   
	
	

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void MagicalContainer::removeElement(int elem) {
			
		auto elementToRemove = lower_bound(setOfElement.begin(), setOfElement.end(), elem);

		if (elementToRemove == setOfElement.end() || *elementToRemove != elem)
			throw runtime_error("element not exit");
		
		const int* value= &(*elementToRemove);

		//remove from the vector of prime numbers

		if (isPrime(elem))
		{
			auto removePrime = lower_bound(OnlyPrimeNumbers.begin(), OnlyPrimeNumbers.end(),value );
				OnlyPrimeNumbers.erase(removePrime);
		}

		//remove from the vector in ascending order

		auto remove = lower_bound(arrangedInAscendingOrder.begin(), arrangedInAscendingOrder.end(),value);
		arrangedInAscendingOrder.erase(remove);

		setOfElement.erase(elementToRemove);
		
		//remove from the vector in cross order

		arrangedInCrossOrder.clear();

		if (size() != 0){
			this->buildarrCross();
		}

	}

	size_t  MagicalContainer::size() const {
		return this->setOfElement.size();
	}

	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	bool MagicalContainer::MyIterator::operator==(const MyIterator& other) const{
						
		if(getType() != other.getType()){
			throw runtime_error("An error occurs because the itorets are of different types, and cannot be compared between them");
		}
							
		if (magicalContainer != other.magicalContainer||this->magicalContainer == nullptr || other.magicalContainer == nullptr)
			throw runtime_error("Cannot compare two iterators that have different containers or whose containers are null");
		if(indexOfIterator == other.indexOfIterator){
			return true;
		}
		return false;
	}

	bool MagicalContainer::MyIterator::operator!=(const MyIterator& other) const{

		if(*this == other){
			return false;
		}
		return true;

	}

	bool MagicalContainer::MyIterator::operator>(const MyIterator& other) const{

		if(getType() != other.getType()){
			throw runtime_error("An error occurs because the itorets are of different types, and cannot be compared between them");
		}
							
		if (magicalContainer != other.magicalContainer||this->magicalContainer == nullptr || other.magicalContainer == nullptr)
			throw runtime_error("Cannot compare two iterators that have different containers or whose containers are null");
		if(indexOfIterator > other.indexOfIterator){
			return true;
		}
		return false;
	
	}

	bool MagicalContainer::MyIterator::operator<(const MyIterator& other) const{

		if(*this > other || *this == other ){
			return false;
		}
		return true;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	string MagicalContainer::AscendingIterator:: getType() const{
		return "AscendingIterator";
	}

	MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other) {

		if (this == &other){
			return *this;
		}else{
			if (&magicalContainer != &other.magicalContainer && magicalContainer != nullptr)
				throw runtime_error("Cannot assign two iterators that have different containers and this.containers are not null");

			this->magicalContainer = other.magicalContainer;
			this->indexOfIterator = other.indexOfIterator;
		}

		return *this;
	}

	int MagicalContainer::AscendingIterator::operator*() const {
		if (magicalContainer == nullptr || indexOfIterator > magicalContainer->arrangedInAscendingOrder.size()-1)
			throw runtime_error("container not initial or above the range");

		int result = *(magicalContainer->arrangedInAscendingOrder.at(indexOfIterator));

		return result;
	}

	MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++() {
		
		if (magicalContainer == nullptr || indexOfIterator > magicalContainer->arrangedInAscendingOrder.size()-1)
			throw runtime_error("container not initial or above the range");

		indexOfIterator++;
		return *this;
	}
	
	MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() const
	{
		return AscendingIterator(*magicalContainer);
	}

	MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() const
	{
		return AscendingIterator(magicalContainer, magicalContainer->arrangedInAscendingOrder.size());
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	string MagicalContainer::SideCrossIterator::getType() const{
		return "SideCrossIterator";
	}
	MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other) {
		
		if (this == &other){
			return *this;
		}else{
			if (&magicalContainer != &other.magicalContainer && magicalContainer != nullptr)
				throw runtime_error("Cannot assign two iterators that have different containers and this.containers are not null");

			this->magicalContainer = other.magicalContainer;
			this->indexOfIterator = other.indexOfIterator;
		}

		return *this;
	}

	int MagicalContainer::SideCrossIterator::operator*() const {
		
		if (magicalContainer == nullptr || indexOfIterator > magicalContainer->arrangedInAscendingOrder.size()-1)
			throw runtime_error("container not initial or above the range");

		int result = *(magicalContainer->arrangedInCrossOrder.at(indexOfIterator));

		return result;
	}

	MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() {
		
		if (magicalContainer == nullptr || indexOfIterator > magicalContainer->arrangedInAscendingOrder.size()-1)
			throw runtime_error("container not initial or above the range");

		indexOfIterator++;
		return *this;
	}
	MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() const
	{
		return SideCrossIterator(*magicalContainer);
	}

	MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() const
	{
		return SideCrossIterator(magicalContainer, magicalContainer->arrangedInCrossOrder.size());
	}

	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	string MagicalContainer::PrimeIterator::getType() const{
		return "PrimeIterator";
	}

	MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other) {
		if (this == &other){
			return *this;
		}else{
			if (&magicalContainer != &other.magicalContainer && magicalContainer != nullptr)
				throw runtime_error("Cannot assign two iterators that have different containers and this.containers are not null");

			this->magicalContainer = other.magicalContainer;
			this->indexOfIterator = other.indexOfIterator;
		}

		return *this;
	}

	int MagicalContainer::PrimeIterator::operator*() const {

		if (magicalContainer == nullptr || indexOfIterator > magicalContainer->OnlyPrimeNumbers.size()-1)
			throw runtime_error("container not initial or above the range");

		int result = *(magicalContainer->OnlyPrimeNumbers.at(indexOfIterator));

		return result;
	}

	MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
		
		if (magicalContainer == nullptr || indexOfIterator >= magicalContainer->OnlyPrimeNumbers.size())
			throw runtime_error("container not initial or above the range");

		this->indexOfIterator++;
		return *this;
	}

	MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() const
	{
		return PrimeIterator(*magicalContainer);
	}

	MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() const
	{
		return PrimeIterator(magicalContainer, magicalContainer->OnlyPrimeNumbers.size());
	}
}
