#include <iostream>
#include <fstream>
#include <random>
#include <math.h>
#include <cmath>
#include <string>

#define HALF_ROUND_STYLE std::round_to_nearest

#include "half.hpp"

const int numIterations = 1000;
const int numValuesPerIterationLimit = 20000;
const int randomLimitLowerExponent = -8;

using half_float::half;

int main(int argc, const char **argv)
{


	for(double exponent = -25; exponent <= 1; exponent += 1) {
		double randomLimit = std::pow(2.0, exponent);

		std::cout << std::endl << "Experimenting with random limit: " << randomLimit << std::endl;

		std::default_random_engine generator;
		std::uniform_real_distribution<double> distribution(0.0,1.0);
		std::ofstream outFile;
		outFile.open("../data/output_" + std::to_string(randomLimit * 1000.0) + ".csv", std::ofstream::out);

		outFile << "Iteration Count, Average Cumulative Error, Total Double, Total Half, Random Limit = " << randomLimit << std::endl;
		for(int k = 0; k < numValuesPerIterationLimit; k += 25) {
			std::cout << k << " " << std::flush;
			if(k % (15 * 25) == 0) {
				std::cout << std::endl;
			}
			outFile << k;

			double averageSum = 0;
			double totalDouble = 0;
			double totalHalf = 0;

			for(int i = 0; i < numIterations; i++) {
				double doubleValue = 0.0;
				half halfValue(0.0);

				for(int j = 0; j < k; j++) {
					double numberA = distribution(generator);
					double numberB = distribution(generator);
					double number = (numberA * numberB) * randomLimit;
					doubleValue += number;

					halfValue += half_float::half_cast<half, std::round_to_nearest>(number);
				}

				double resultFromHalf = half_float::half_cast<double, std::round_to_nearest>(halfValue);

				double difference = fabs(resultFromHalf - doubleValue);

				double percentageDifference = ((difference / doubleValue) * 100.0);

				totalDouble += doubleValue;
				totalHalf += resultFromHalf;
				
				averageSum += percentageDifference;

				//std::cout << difference << " (" << doubleValue << " vs " << resultFromHalf << ") -> " <<  << "%" << std::endl;
			}

			outFile << ", " << (averageSum / double(numIterations)) << ", " << totalDouble << ", " << totalHalf;

			outFile << std::endl;
		}

		

		outFile.close();
	}
}