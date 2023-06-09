#include "../header.h"

using namespace std;

// MENU 14
//
// Function to display the summed up prices of cars and motorcycles. It additionally shows the usage of some C++ features
void displayPrices(Dealership& dealership) {
	vector<int>carPrices;
	vector<int>motorcyclePrices;

	for (int i = 0; i < dealership.getListingsSize(CAR); i++) {
		carPrices.push_back(dealership.getListingPriceWithIndex(CAR, i));
	}

	for (int i = 0; i < dealership.getListingsSize(MOTORCYCLE); i++) {
		motorcyclePrices.push_back(dealership.getListingPriceWithIndex(MOTORCYCLE, i));
	}

	// Usage of ostream iterators (iterator adapter)
	ostream_iterator<int> carOutputIterator(cout, "\n");
	ostream_iterator<int> motorcycleOutputIterator(cout, "\n");

	cout << " Car prices:" << endl;

	// Usage of copy algorythm
	copy(carPrices.begin(), carPrices.end(), carOutputIterator);
	cout << endl;

	cout << " Motorcycle prices:" << endl;

	copy(motorcyclePrices.begin(), motorcyclePrices.end(), motorcycleOutputIterator);
	cout << endl;

	// Sort vectors (function adapter) in descending order
	sort(carPrices.begin(), carPrices.end(), greater<int>());
	sort(motorcyclePrices.begin(), motorcyclePrices.end(), greater<int>());

	// Sorted price display
	cout << " Car sorted prices:" << endl;

	copy(carPrices.begin(), carPrices.end(), carOutputIterator);
	cout << endl;

	cout << " Motorcycle sorted prices:" << endl;

	copy(motorcyclePrices.begin(), motorcyclePrices.end(), motorcycleOutputIterator);
	cout << endl;

	// Lambda expression
	auto sumLambda = [](int sum, int num) {
		return sum + num;
	};

	int carPriceSum = 0, motorcyclePriceSum = 0;

	for_each(carPrices.begin(), carPrices.end(), [&](int num) {
		carPriceSum = sumLambda(carPriceSum, num);
		});

	// Functor
	motorcyclePriceSum = accumulate(motorcyclePrices.begin(), motorcyclePrices.end(), motorcyclePriceSum, plus<int>());

	cout << " Total price of cars: " << carPriceSum << endl;
	cout << " Total price of motorcycles: " << motorcyclePriceSum << endl;

	cin.ignore();
	cin.get();
}