// Carmen Hernandez
// Lab Section 103
// Submission Date: 11/17/2022

#include <iostream>
#include <algorithm>
#include "kmeans.hpp" 
#include <cmath>
using namespace std;

// Function declarations here
void normalization(vector<double> &column, double max, double min);
double distance(car_data &data, car_data &clusters, int current_cluster);

int main()
{
    car_data data;
    input_car_data(data);

    ifstream fin("clusters.csv");
    car_data clusters;
    read_csv(fin, clusters);
    fin.close();

    fin.open("cars.csv");
    car_data cars;
    read_csv(fin, cars);
    fin.close();

    // Find the max and min of each feature from "cars.csv" to normalize clusters and data
    double mpg_max = *max_element(cars.mpg.begin(), cars.mpg.end()); // cars.mpg maximum value
    double mpg_min = *min_element(cars.mpg.begin(), cars.mpg.end()); // cars.mpg minimum value

    double cylinders_max = *max_element(cars.cylinders.begin(), cars.cylinders.end()); // cars.cylinders maximum value
    double cylinders_min = *min_element(cars.cylinders.begin(), cars.cylinders.end()); // cars.cylinders minimum value

    double cub_max = *max_element(cars.cubicinches.begin(), cars.cubicinches.end()); // cars.cubicinches maximum value
    double cub_min = *min_element(cars.cubicinches.begin(), cars.cubicinches.end()); // cars.cubicinches minimum value

    double hp_max = *max_element(cars.hp.begin(), cars.hp.end()); // cars.hp maximum value
    double hp_min = *min_element(cars.hp.begin(), cars.hp.end()); // cars.hp minimum value

    double weight_max = *max_element(cars.weightlbs.begin(), cars.weightlbs.end()); // cars.weightlbs maximum value
    double weight_min = *min_element(cars.weightlbs.begin(), cars.weightlbs.end()); // cars.weightlbs minimum value

    double time_max = *max_element(cars.time260.begin(), cars.time260.end()); // cars.time260 maximum value
    double time_min = *min_element(cars.time260.begin(), cars.time260.end()); // cars.time260 minimum value

    double year_max = *max_element(cars.year.begin(), cars.year.end()); // cars.year maximum value
    double year_min = *min_element(cars.year.begin(), cars.year.end()); // cars.year minimum value

    // Renormalize input data to original car data here
    normalization(data.mpg, mpg_max, mpg_min);
    normalization(data.cylinders, cylinders_max, cylinders_min);
    normalization(data.cubicinches, cub_max, cub_min);
    normalization(data.hp, hp_max, hp_min);
    normalization(data.weightlbs, weight_max, weight_min);
    normalization(data.time260, time_max, time_min);
    normalization(data.year, year_max, year_min);

    // Normalize the clusters
    normalization(clusters.mpg, mpg_max, mpg_min);
    normalization(clusters.cylinders, cylinders_max, cylinders_min);
    normalization(clusters.cubicinches, cub_max, cub_min);
    normalization(clusters.hp, hp_max, hp_min);
    normalization(clusters.weightlbs, weight_max, weight_min);
    normalization(clusters.time260, time_max, time_min);
    normalization(clusters.year, year_max, year_min);

    // Assign clusters here
    double distance1 = distance(data, clusters, 0); // Find distance between input and cluster 1
    double distance2 = distance(data, clusters, 1); // Find distance between input and cluster 2
    double distance3 = distance(data, clusters, 2); // Find distance between input and cluster 3

    // Find the minimum value out of the three distances
    vector<double> find_min{distance1, distance2, distance3};
    double minimum_val = *min_element(find_min.begin(), find_min.end());
    
    // Assign the mystery car type to the cluster with the smallest distance
    if (minimum_val == distance1){
        data.clusters.at(0) = 1;
    }
    else if (minimum_val == distance2){
        data.clusters.at(0) = 2;
    }
    else if (minimum_val == distance3){
        data.clusters.at(0) = 3;
    }

    // Output identity of car
    cout << "Mystery car is type " << data.clusters.at(0) << ".";
    return 0;
}

// Function definitions here

// Create normalization function
void normalization(vector<double> &column, double max, double min){

    double denominator = max - min; // Denominator of normalization formula
    vector<double> numerator; // Set up a vector for the numerator (X - min)

    // Iterate through the column to create a vector of values subtracted by the minimum
    for (int i = 0; i < column.size(); i++){
        numerator.push_back(column[i] - min); // Append (X - min) values into numerator vector
        column[i] = numerator[i]/denominator; // Replace column values with normalization values
    }
}

// Create euclidean distance function between the input and the clusters
double distance(car_data &data, car_data &clusters, int current_cluster){
    // Find sum of the squared difference between the input features and centroid
    double summation = pow(data.mpg.at(0) - clusters.mpg[current_cluster], 2) + 
                       pow(data.cylinders.at(0) - clusters.cylinders[current_cluster], 2) + 
                       pow(data.cubicinches.at(0) - clusters.cubicinches[current_cluster], 2) + 
                       pow(data.hp.at(0) - clusters.hp[current_cluster], 2) +
                       pow(data.weightlbs.at(0) - clusters.weightlbs[current_cluster], 2) + 
                       pow(data.time260.at(0) - clusters.time260[current_cluster], 2) + 
                       pow(data.year.at(0) - clusters.year[current_cluster], 2);

    double distance = sqrt(summation); // Square root of summation to find the actual distance
    return distance;
}