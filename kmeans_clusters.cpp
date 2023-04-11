// Carmen Hernandez
// Lab Section 103
// Submission Date: 11/17/2022

#include <iostream>
#include <algorithm>
#include <vector>
#include "kmeans.hpp"
#include <cmath>
using namespace std;

// Function declarations here
void normalization(vector<double> &column); // Normalization function that takes in array of values from each feature
double distance(int car, car_data &centroid, int current_centroid, car_data &data); // Euclidean distance - takes in 
                                                                                    // each normalized data, centroids, 
                                                                                    // and centroid index
double convergence(car_data &new_centroids, car_data &centroid); // Finds convergence between new and old centroids

int main()
{
    double epsilon = 10e-10; // Defining epsilon for convergence

    car_data data;
    ifstream fin("cars.csv");
    // Step 1 - read in data and verify
    read_csv(fin, data);
    fin.close();

    // Find max and min of each feature for denormalization later
    double mpg_max = *max_element(data.mpg.begin(), data.mpg.end()); // data.mpg maximum value
    double mpg_min = *min_element(data.mpg.begin(), data.mpg.end()); // data.mpg minimum value

    double cylinders_max = *max_element(data.cylinders.begin(), data.cylinders.end()); // data.cylinders maximum value
    double cylinders_min = *min_element(data.cylinders.begin(), data.cylinders.end()); // data.cylinders minimum value

    double cub_max = *max_element(data.cubicinches.begin(), data.cubicinches.end()); // data.cubicinches maximum value
    double cub_min = *min_element(data.cubicinches.begin(), data.cubicinches.end()); // data.cubicinches minimum value

    double hp_max = *max_element(data.hp.begin(), data.hp.end()); // data.hp maximum value
    double hp_min = *min_element(data.hp.begin(), data.hp.end()); // data.hp minimum value

    double weight_max = *max_element(data.weightlbs.begin(), data.weightlbs.end()); // data.weightlbs maximum value
    double weight_min = *min_element(data.weightlbs.begin(), data.weightlbs.end()); // data.weightlbs minimum value

    double time_max = *max_element(data.time260.begin(), data.time260.end()); // data.time260 maximum value
    double time_min = *min_element(data.time260.begin(), data.time260.end()); // data.time260 minimum value

    double year_max = *max_element(data.year.begin(), data.year.end()); // data.year maximum value
    double year_min = *min_element(data.year.begin(), data.year.end()); // data.year minimum value

    // Step 2 - Normalize vectors - only columns 1-7 here
    normalization(data.mpg);
    normalization(data.cylinders);
    normalization(data.cubicinches);
    normalization(data.hp);
    normalization(data.weightlbs);
    normalization(data.time260);
    normalization(data.year);
    
    // Step 3 - Initialize centroids
    car_data centroids;
    initialize(centroids);
    centroids.headers = data.headers; // need this because otherwise no headers - error

    // Step 4 - Implement k-mean algorithm to find clusters
    car_data new_centroid; // Initialize new_centroid for while loop
    new_centroid = centroids;
    bool startLoop = true; // Create a condition to start the while loop

    const int N_rows = data.mpg.size(); // Number of cars in dataframe (rows)
    const int N_centroids = 3; // Number of centroids

    double distance1; // Initialize distance between data and centroid 1
    double distance2; // Initialize distance between data and centroid 2
    double distance3; // Initialize distance between data and centroid 3

    while(convergence(new_centroid, centroids) > epsilon || startLoop == true){
        centroids = new_centroid; // Redefine centroids to be the new centroid calculated
        vector<int> counter(3,0); // Initialize counter for cluster rows
        startLoop = false; // End the condition that starts the while loop

        for (int i = 0; i < N_rows; i++){ // For loop through cars
            // Equal distancce1, distance2, distance3 to the distances between the cars and centroids
            distance1 = distance(i, centroids, 0, data);
            distance2 = distance(i, centroids, 1, data);
            distance3 = distance(i, centroids, 2, data);
            
            // Assign cars to the closest cluster
            if (distance1 < distance2 && distance1 < distance3){
                data.clusters.at(i) = 1;
            }
            else if (distance2 < distance1 && distance2 < distance3){
                data.clusters.at(i) = 2;
            }
            else if (distance3 < distance1 && distance3 < distance2){
                data.clusters.at(i) = 3;
            }
        }
        
        reset(new_centroid, 3); // Empty out initialized new_centroid variable to be able to add into it

        for (int i = 0; i < N_rows; i++){
            int current_cluster = data.clusters.at(i) - 1; // Find index of the current cluster

            // Find the new_centroid
            new_centroid.mpg.at(current_cluster) += data.mpg.at(i);
            new_centroid.cylinders.at(current_cluster) += data.cylinders.at(i);
            new_centroid.cubicinches.at(current_cluster) += data.cubicinches.at(i);
            new_centroid.hp.at(current_cluster) += data.hp.at(i);
            new_centroid.weightlbs.at(current_cluster) += data.weightlbs.at(i);
            new_centroid.time260.at(current_cluster) += data.time260.at(i);
            new_centroid.year.at(current_cluster) += data.year.at(i);

            counter.at(current_cluster)++; // Finds the number of rows (cars) in each cluster
        }

        // Find the mean of each feature to find the new centroid
        for (int i = 0; i < N_centroids; i++){
            if (counter.at(i) == 0){
                new_centroid.mpg.at(i) = .5;
            }
            else{
                new_centroid.mpg.at(i)/=counter.at(i);
            }
            if (counter.at(i) == 0){
                new_centroid.cylinders.at(i) = .5;
            }
            else{
                new_centroid.cylinders.at(i)/=counter.at(i);
            }
            if (counter.at(i) == 0){
                new_centroid.cubicinches.at(i) = .5;
            }
            else{
                new_centroid.cubicinches.at(i)/=counter.at(i);
            }
            if (counter.at(i) == 0){
                new_centroid.hp.at(i) = .5;
            }
            else{
                new_centroid.hp.at(i)/=counter.at(i);
            }
            if (counter.at(i) == 0){
                new_centroid.weightlbs.at(i) = .5;
            }
            else{
                new_centroid.weightlbs.at(i)/=counter.at(i);
            }
            if (counter.at(i) == 0){
                new_centroid.time260.at(i) = .5;
            }
            else{
                new_centroid.time260.at(i)/=counter.at(i);
            }
            if (counter.at(i) == 0){
                new_centroid.year.at(i) = .5;
            }
            else{
                new_centroid.year.at(i)/=counter.at(i);
            }
        }
    }

    // Step 5 - print out clustered data and centroids here
    // Denormalize the data
    for (int i = 0; i < N_rows; i++){
        data.mpg.at(i) = data.mpg.at(i) * (mpg_max - mpg_min) + mpg_min;
        data.cylinders.at(i) = data.cylinders.at(i) * (cylinders_max - cylinders_min) + cylinders_min;
        data.cubicinches.at(i) = data.cubicinches.at(i) * (cub_max - cub_min) + cub_min;
        data.hp.at(i) = data.hp.at(i) * (hp_max - hp_min) + hp_min;
        data.weightlbs.at(i) = data.weightlbs.at(i) * (weight_max - weight_min) + weight_min;
        data.time260.at(i) = data.time260.at(i) * (time_max - time_min) + time_min;
        data.year.at(i) = data.year.at(i) * (year_max - year_min) + year_min;
    }

    ofstream outfile("cars_clustered.csv");
    print(outfile,data);

    // Denormalize the centroids
    for (int i = 0; i < N_centroids; i++){
        new_centroid.mpg.at(i) = new_centroid.mpg.at(i) * (mpg_max - mpg_min) + mpg_min;
        new_centroid.cylinders.at(i) = new_centroid.cylinders.at(i) * (cylinders_max - cylinders_min) + cylinders_min;
        new_centroid.cubicinches.at(i) = new_centroid.cubicinches.at(i) * (cub_max - cub_min) + cub_min;
        new_centroid.hp.at(i) = new_centroid.hp.at(i) * (hp_max - hp_min) + hp_min;
        new_centroid.weightlbs.at(i) = new_centroid.weightlbs.at(i) * (weight_max - weight_min) + weight_min;
        new_centroid.time260.at(i) = new_centroid.time260.at(i) * (time_max - time_min) + time_min;
        new_centroid.year.at(i) = new_centroid.year.at(i) * (year_max - year_min) + year_min;
    }
    ofstream out("clusters.csv");
    print(out, new_centroid);
    
    return 0;
}

// Function definitions here

// Create normalization function
void normalization(vector<double> &column){
    double max = *max_element(column.begin(), column.end()); // Column's maximum value
    double min = *min_element(column.begin(), column.end()); // Column's minimum value
    double denominator = max - min; // Denominator of normalization formula
    vector<double> numerator; // Set up a vector for the numerator (X - min)

    // Iterate through the column to create a vector of values subtracted by the minimum
    for (int i = 0; i < column.size(); i++){
        numerator.push_back(column[i] - min); // Append (X - min) values into numerator vector
        column[i] = numerator[i]/denominator; // Replace column values with normalization values
    }
}

// Create euclidean distance function between data and the centroid
double distance(int car, car_data &centroid, int current_centroid, car_data &data){
    // Find sum of the squared difference between the features and centroid
    double summation = pow(data.mpg[car] - centroid.mpg[current_centroid], 2) + 
                       pow(data.cylinders[car] - centroid.cylinders[current_centroid], 2) + 
                       pow(data.cubicinches[car] - centroid.cubicinches[current_centroid], 2) + 
                       pow(data.hp[car] - centroid.hp[current_centroid], 2) +
                       pow(data.weightlbs[car] - centroid.weightlbs[current_centroid], 2) + 
                       pow(data.time260[car] - centroid.time260[current_centroid], 2) + 
                       pow(data.year[car] - centroid.year[current_centroid], 2);

    double distance = sqrt(summation); // Square root the summation for the actual distance
    return distance;
}

// Create euclidean distance function between the new centroids and the old centroids
double convergence(car_data &new_centroids, car_data &centroid){
    const int N_centroids = 3; // Redefine the number of centroids
    double sum = 0; // Initialize the sum
    for (int i = 0; i < N_centroids; i++){
        // Find sum of the squared difference between the new centroids and the old centroids
        sum = sum + pow(new_centroids.mpg[i] - centroid.mpg[i], 2) + 
                    pow(new_centroids.cylinders[i] - centroid.cylinders[i], 2) + 
                    pow(new_centroids.cubicinches[i] - centroid.cubicinches[i], 2) + 
                    pow(new_centroids.hp[i] - centroid.hp[i], 2) +
                    pow(new_centroids.weightlbs[i] - centroid.weightlbs[i], 2) + 
                    pow(new_centroids.time260[i] - centroid.time260[i], 2) + 
                    pow(new_centroids.year[i] - centroid.year[i], 2); 
    }

    double converge = sqrt(sum); // Square root of the sum for the actual distance
    return converge;
}