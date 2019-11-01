//
// Created by Haochen Yang on 10/27/19.
//
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>

using namespace std;

#ifndef PROJECT1_DICTIONARY_H
#define PROJECT1_DICTIONARY_H

struct SecondHashTable{
    int **secondMatrix;
    vector<string>** secondHash;
    int numOfCollision;
    vector<string> tempStoreNames;
    int secondHashTableSize;
    int matrixSize;
};

class Dictionary {
public:

    // Insert an input set of n keys to the dictionary. This method should print out the following information:
    // 1. The hash functions comprising the perfect hash (both levels)
    // 2. The sum of squares of the number of keys mapped to each bin of the first level hash function, and
    // 3. The number of trials needed to generate each hash function.
    void bulkInsert(int n, string *keys);

    // Insert a key to the dictionary.
    // Print out whether the insertion caused a collision in the second level hash.
    // Handle collision with separate chaining.
    void insert(string key);

    // Remove a key from the dictionary, if it exists.
    void remove(string key);

    // Return whether a key is found in the dictionary.
    // Print the buckets (both first and second level) accessed during the operation.
    bool find(string key);

    // Find the first hash matrix
    void getFirstHashFunction(int n, string *keys);

    int** getSecondHashFunction(int n, string *keys);

    void print();

private:

    int** firstHashMatrix;
    int   firstMatrixRow;
    SecondHashTable** firstHashTable;


};

void printMatrix(int **matrix, int rows, int columns){
    for(int row = 0; row < rows; row++){
        for(int column = 0; column < columns; column++){
            cout << matrix[row][column];
        }
        cout << endl;
    }
}

//create a random hash matrix with 0 and 1
int** randomMatrix(int rows, int columns){
    //create a matrix for the first hashing
    int **matrix = new int *[rows];
    for(int row = 0; row < rows; row++){
        matrix[row] = new int [columns];
    }

    //set a second random matrix
    for(int row = 0; row < rows; row++){
        for(int column = 0; column < columns; column++){
            matrix[row][column] = rand() % 2;
        }
    }

    return matrix;
}

uint64_t hash1(const std::string& input) {
    uint32_t hash = 0;
    for(uint8_t byte: input) {
        hash += byte;
        hash += hash << 10;
        hash ^= hash >> 6;
    }

    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}

int* Array_keys(string k){
    int* a=new int[32];
    uint32_t hex_number=hash1(k);
    for(int j=31;j>=0;j--){
        a[j]=(hex_number>>j)&1;
    }
    return a;
}

// change names to number
int namesChangeToNumber(string name){
    name = "        " + name;
    int* array = Array_keys(name.substr(name.length()-8));
    int sum    = 0;
    for(int f = 0;f < 32;f++){
        sum += (array[f]*pow(2,f));
    }
    return sum;
}

int numberTimesMatrix(int** newMatrix, int matrix_row, int input){
    int* array = new int[32];
    for(int j = 31; j >= 0; j--){
        array[j] = (input>>j)&1;
    }

    int position[matrix_row];

    for(int k=0; k<matrix_row; k++){
        int result = 0;
        for(int i=0; i<32; i++){
            result += (newMatrix[k][i])*array[i];

        }
        position[k]=result%2;
    }

    int int_position=0;
    for(int b=0; b<matrix_row; b++){
        int_position+=position[b]*pow(2,b);
    }

    return int_position;
}



#endif //PROJECT1_DICTIONARY_H
