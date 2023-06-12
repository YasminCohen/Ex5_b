#ifndef MY_MAGICALCONTAINER
#define MY_MAGICALCONTAINER

#include <set>
#include <vector>
#include <stdexcept>
#include <string>

using namespace std;

namespace ariel
{

	class MagicalContainer
	{

		private:
			set<int> setOfElement;

			vector<const int *> arrangedInAscendingOrder;
			vector<const int *> arrangedInCrossOrder;
			vector<const int *> OnlyPrimeNumbers;

			void buildarrCross();

			class MyIterator
			{

			protected:
	
				virtual string getType() const = 0;

			public:
				const MagicalContainer *magicalContainer;
				size_t indexOfIterator;
				MyIterator() : magicalContainer(nullptr), indexOfIterator(0){};
				MyIterator(const MagicalContainer *container, size_t index) : magicalContainer(container), indexOfIterator(index){};
				MyIterator(const MyIterator &other) = default;
				MyIterator(MyIterator &&other) = default;
				MyIterator &operator=(const MyIterator &other) = default;
				MyIterator &operator=(MyIterator &&other) = default;
				virtual ~MyIterator() = default;

				bool operator==(const MyIterator &other) const;
				bool operator!=(const MyIterator &other) const;
				bool operator>(const MyIterator &other) const;
				bool operator<(const MyIterator &other) const;
			};

			static bool isPrime(int num);


		public:

			MagicalContainer(){}
			void addElement(int elem);
			void removeElement(int elem);
			size_t size() const;

			////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			class AscendingIterator : public MyIterator
			{
				
				private:
					AscendingIterator(const MagicalContainer *magicalContainer, size_t indexOfIterator) : MyIterator(magicalContainer, indexOfIterator) {}
					string getType() const override;

				public:
					AscendingIterator(const MagicalContainer &container) : MyIterator(&container, 0) {}
					~AscendingIterator() override = default;
					AscendingIterator(const AscendingIterator &other) : MyIterator(other.magicalContainer, other.indexOfIterator) {}
					AscendingIterator(AscendingIterator &&other) noexcept = default;
					AscendingIterator &operator=(const AscendingIterator &other); ///
					AscendingIterator &operator=(AscendingIterator &&other) noexcept = default;

					int operator*() const;
					AscendingIterator &operator++();

					AscendingIterator begin() const;
					AscendingIterator end() const;
			};

			////////////////////////////////////////////////////////////////////////////////////////////////////////////

			class SideCrossIterator : public MyIterator
			{

				private:
					SideCrossIterator(const MagicalContainer *magicalContainer, size_t indexOfIterator) : MyIterator(magicalContainer, indexOfIterator) {}
					string getType() const override;

				public:
					SideCrossIterator(const MagicalContainer &container) : MyIterator(&container, 0) {}
					~SideCrossIterator() override = default;
					SideCrossIterator(const SideCrossIterator &other):MyIterator(other.magicalContainer, other.indexOfIterator){}
					SideCrossIterator(SideCrossIterator &&other) noexcept = default;
					SideCrossIterator &operator=(const SideCrossIterator &other);
					SideCrossIterator &operator=(SideCrossIterator &&other) noexcept = default;

					int operator*() const;
					SideCrossIterator &operator++();

					SideCrossIterator begin() const;
					SideCrossIterator end() const;
			};

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			class PrimeIterator : public MyIterator
			{

				private:
					PrimeIterator(const MagicalContainer *magicalContainer, size_t indexOfIterator) : MyIterator(magicalContainer, indexOfIterator) {}
					string getType() const override;

				public:
					PrimeIterator(const MagicalContainer &container) : MyIterator(&container, 0) {}
					~PrimeIterator() override = default;
					PrimeIterator(const PrimeIterator &other): MyIterator(other.magicalContainer,other.indexOfIterator){}
					PrimeIterator(PrimeIterator &&other) noexcept = default;
					PrimeIterator &operator=(const PrimeIterator &other);
					PrimeIterator &operator=(PrimeIterator &&other) noexcept = default;

					int operator*() const;
					PrimeIterator &operator++();

					PrimeIterator begin() const;
					PrimeIterator end() const;
			};
	};
}
#endif
