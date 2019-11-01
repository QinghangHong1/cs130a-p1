//
// Created by Haochen Yang on 10/27/19.
//

#include "Dictionary.h"

// Implement Dictionary methods.
#include "Dictionary.h"
#include <string>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

void Dictionary::bulkInsert(int n, string *keys) {

    int numberOfBucket = pow(2, ceil(log2(n)));
//    cout << "numberOfBucket is " << numberOfBucket << endl;
    getFirstHashFunction(n, keys);


    //create first hash table
    SecondHashTable** firstHashTable = new SecondHashTable* [numberOfBucket];

    //print the first hash matrix
//    cout << "The first hash matrix is: " << endl;
//    printMatrix(firstHashMatrix, firstMatrixRow, 32);

    //find the collision number and create the second hash table and number of vectors to store name
    //this hash table consists with collision number for each bucket
//    int *collisionTable = new int[n];

    // create an array to store each number of keys
    int *keyNumbers = new int[n];
    for(int each = 0; each < n; each++) {
        keyNumbers[each] = namesChangeToNumber(keys[each]);
//        cout << keyNumbers[each] << endl;
    }

    //for each bucket in first hash table, create second hash table
    for (int num = 0; num < numberOfBucket; num++) {
        //create a matrix for the second hashing
        //use rows and columns as collision numbers in every bucket and every key number size
        SecondHashTable* secondHashTable = new SecondHashTable;
        secondHashTable->numOfCollision      = 0;
        secondHashTable->secondHashTableSize = 0;
        secondHashTable->matrixSize          = 0;

//        secondHashTable->secondHash = new vector<string>;

        firstHashTable[num] = secondHashTable;
    }

    //for each key that have been changed to number, calculate its position and put it into the bucket
    for(int num = 0; num < n; num++){
        int number = keyNumbers[num];

        int firstHashTablePosition = numberTimesMatrix(firstHashMatrix, firstMatrixRow, number);
//        cout << "number is "<< number << endl;
//        cout << "position is " << firstHashTablePosition << endl;

        // put the name in keys into the secondHash vector<string> temporarily
        // and collision number increase by 1
        firstHashTable[firstHashTablePosition]->tempStoreNames.push_back(keys[num]);
        firstHashTable[firstHashTablePosition]->numOfCollision++;

//        cout << "key is " << keys[num] << endl;
//        cout << "store in " << firstHashTablePosition << endl;
//        cout << "numOfCollision is "  << firstHashTable[firstHashTablePosition].numOfCollision << endl;
    }

    //print all the elements in the second hash table
//    for(int i = 0; i < numberOfBucket; i++){
//        if(!firstHashTable[i].tempStoreNames.empty()){
//            cout << "in the firstHashTable[" << i << "]:" << endl;
//            for (int j = 0; j < firstHashTable[i].tempStoreNames.size(); j++)
//                cout << firstHashTable[i].tempStoreNames.at(j) << endl;
//        }
//        cout << "-----" << endl;
//    }

    //find the second hash matrix, store it and names with same matrix
    for(int num = 0; num < numberOfBucket; num++) {
        SecondHashTable* tempHashTable = firstHashTable[num];
        int collision = tempHashTable->numOfCollision;
//        cout << "collision is " << collision << endl;

        if (collision != 0) {

            //create the square of collision number of space in secondHash
            int size            = ceil(log2(collision * collision));
            int numberOfBucket  = pow(2, ceil(log2(collision * collision)));
            if(collision == 1){
                size           = 1;
                numberOfBucket = 1;
            }
            tempHashTable->matrixSize = size;

            tempHashTable->secondHash = new vector<string>*[numberOfBucket];

            for(int i = 0; i < numberOfBucket; i++){
                tempHashTable->secondHash[i] = new vector<string>[1];
            }

            tempHashTable->secondHashTableSize = numberOfBucket;
//            tempHashTable->secondHash->resize(size);

            //create an array to check the collision times after using second hash matrix
            int *checkCollision = new int[numberOfBucket];
            for(int temp = 0; temp < numberOfBucket; temp++){
                checkCollision[temp] = 0;
            }

            string name_array[collision];
//            vector* names = firstHashTable[num]->tempStoreNames;
            for(vector<string>::iterator i = firstHashTable[num]->tempStoreNames.begin(); i < firstHashTable[num]->tempStoreNames.end(); i++){
                name_array[collision] = (*i);
            }
            tempHashTable->secondMatrix = getSecondHashFunction(numberOfBucket, name_array);
            printMatrix(tempHashTable->secondMatrix, size, 32);

            //check the second hash matrix in order to keep every names in different position
//            bool matrixWorks    = true;
//            int **secondMatrix  = randomMatrix(size, 32);
//            cout << "in the firstHashTable[" << num << "]:" << endl;
//            cout << "The second matrix is: " << endl;
//            printMatrix(secondMatrix, size, 32);

//            //check the collision in the second hash matrix first and store all names in distinct position
//            while(matrixWorks){
//
//                secondMatrix = randomMatrix(size, 32);
//
//                //calculate the position of names in second hash table
//                int tempPostion = 0;
//                int elementsNumberOfKey     = 0;
//                int secondHashTablePosition = 0;
////                cout << collision << endl;
////                cout << tempHashTable->tempStoreNames.size() << endl;
//
//                while(tempPostion < collision){
//                    secondMatrix = randomMatrix(size, 32);
//
//                    elementsNumberOfKey = namesChangeToNumber(tempHashTable->tempStoreNames[tempPostion]);
//                    secondHashTablePosition = numberTimesMatrix(secondMatrix, size, elementsNumberOfKey);
//
////                    // if the position is larger than bucket should be, continue the loop
////                    if(secondHashTablePosition >= numberOfBucket) continue;
//
//                    checkCollision[secondHashTablePosition]++;
//                    cout << "-------------" << endl;
//                    cout << "for " << tempHashTable->tempStoreNames[tempPostion] << endl;
//                    cout << "its key number is " << elementsNumberOfKey << endl;
//                    cout << "checkCollision[" << secondHashTablePosition << "] is" << endl;
//                    cout << checkCollision[secondHashTablePosition] << endl;
//                    cout << "secondHashTablePosition is " << secondHashTablePosition << endl;
//                    cout << "-----------" << endl;
//                    tempPostion++;
//                    cout << "tempPostion is " << tempPostion << endl;
//                    cout << "collision is " << collision << endl;
//                }
//
//                //check the collision list that each number have been put in the different place
////                matrixWorks = false;
//
////                for(int each = 0; each < numberOfBucket; each++){
////                        cout << checkCollision[each] << endl;
//////                        matrixWorks = true;
//////                        break;
////                }
//                matrixWorks = false;
//
//                for(int each = 0; each < numberOfBucket; each++){
//                    if(checkCollision[each] > 1){
////                        cout << checkCollision[each] << endl;
//                        matrixWorks = true;
//                        break;
//                    }
//                }
//            }



//            tempHashTable->secondMatrix = getSecondHashFunction()

            //print out the second matrix for every bucket
//            cout << "when the bucket is " << num << " in the first hash table, "
//                 << "the second matrix is :" << endl;
//            printMatrix(tempHashTable->secondMatrix, size, 32);

            //set every name in second hash table into its vector unique position
            for(int each = 0; each < collision; each++){
//                cout<<"one"<<endl;
                string name = tempHashTable->tempStoreNames[each];
//                string name = name_array[each];
//                cout << name << endl;
                cout << "name is " << name << endl;
                int elementsNumberOfKey     = namesChangeToNumber(name);
                int secondHashTablePosition = numberTimesMatrix(tempHashTable->secondMatrix, size, elementsNumberOfKey);
                cout<<secondHashTablePosition<<endl;
//                cout << "0000" << endl;
//                cout << elementsNumberOfKey << endl;
//                cout << secondHashTablePosition << endl;
//                cout << tempHashTable->secondHash->size() << endl;

                tempHashTable->secondHash[secondHashTablePosition] = new vector<string>[1];
                tempHashTable->secondHash[secondHashTablePosition]->push_back(name);
                cout << "finish" << endl;
            }
        }else{
            tempHashTable->secondHash = new vector<string>*[1];
            tempHashTable->secondHash[0] = new vector<string>[1];

            cout << "finish 2" << endl;
        }
    }

    this->firstHashTable = firstHashTable;
}

void Dictionary::insert(string key) {
    if(key.empty()){
        cout << "empty input" << endl;
        return;
    }

    if(firstHashMatrix == NULL){
        cout << "there is no exist hash table" << endl;
        return;
    }

    if(find(key)){
        cout << "The key has already in the dictionary" << endl;
        return;
    }

    //change key to number and get Position in first hash table
    int number = namesChangeToNumber(key);
    int firstPosition = numberTimesMatrix(firstHashMatrix, firstMatrixRow, number);

    int** secondMatrix = firstHashTable[firstPosition]->secondMatrix;
    int secondMatrixRow = firstHashTable[firstPosition]->matrixSize;
    int secondPosition = numberTimesMatrix(secondMatrix, secondMatrixRow, number);

    firstHashTable[firstPosition]->secondHash[secondPosition]->push_back(key);
    return;
}

void Dictionary::remove(string key) {
    if(key.empty()){
        cout << "empty input" << endl;
        return;
    }

    if(firstHashMatrix == NULL){
        cout << "there is no exist hash table" << endl;
        return;
    }

    if(!find(key)){
        cout << "The key does not exist in the dictionary" << endl;
        return;
    }

    //change key to number and get Position in first hash table
    int number = namesChangeToNumber(key);
    int firstPosition = numberTimesMatrix(firstHashMatrix, firstMatrixRow, number);

    //get position in second hash table
    int** secondMatrix = firstHashTable[firstPosition]->secondMatrix;
    int secondMatrixRow = firstHashTable[firstPosition]->matrixSize;
    int secondPosition = numberTimesMatrix(secondMatrix, secondMatrixRow, number);

    //delete the element
    vector<string>* secondHashTable = firstHashTable[firstPosition]->secondHash[secondPosition];
    for(vector<string>::iterator it = secondHashTable->begin(); it != secondHashTable->end(); ) {
        if (*it == key) {
            it = secondHashTable->erase(it);
            return;
        } else {
            ++it;
        }
    }
}

bool Dictionary::find(string key) {
    if(key.empty() || firstHashMatrix == NULL) return false;

    //change key to number and get Position in first hash table
    int number = namesChangeToNumber(key);
    int firstPosition = numberTimesMatrix(firstHashMatrix, firstMatrixRow, number);

    if(firstHashTable[firstPosition]->secondMatrix == NULL) return false;

    //get position in second hash table
    int** secondMatrix = firstHashTable[firstPosition]->secondMatrix;
    int secondMatrixRow = firstHashTable[firstPosition]->matrixSize;
    int secondPosition = numberTimesMatrix(secondMatrix, secondMatrixRow, number);

    if(firstHashTable[firstPosition]->secondHash == NULL) return false;

    vector<string>* secondHashTable = firstHashTable[firstPosition]->secondHash[secondPosition];
    for(int i = 0; i < secondHashTable->size(); i++){
        if(key == secondHashTable->at(i))
            return true;
    }
    return false;
}

void Dictionary::getFirstHashFunction(int n, string *keys){
    int matrix_row       = ceil(log2(n));
    this->firstMatrixRow = matrix_row;

    while(true){
        int** Newmatrix=randomMatrix(matrix_row,32);

        int collision_array[int(pow(2,matrix_row))];

        for(int c=0;c<matrix_row;c++){
            collision_array[c]=0;
        }

        for(int d=0;d<n;d++){
            keys[d] = "        " + keys[d];
            int* array=Array_keys(keys[d].substr(keys[d].length()-8));
            int position[matrix_row];
            for(int k=0; k<matrix_row; k++){
                int result=0;
                for(int i=0; i<32; i++){
                    result+=(Newmatrix[k][i])*array[i];
                }
                position[k]=result%2;
            }
            int int_position=0;
            for(int b=0; b<matrix_row; b++){
                int_position+=position[b]*pow(2,b);
            }
            collision_array[int_position]+=1;
        }

        int sum=0;
        for(int e=0;e<pow(2,matrix_row);e++){
            sum+=pow(collision_array[e],2);
        }
        if (sum<(4*n)) {
            this->firstHashMatrix = Newmatrix;
//            return Newmatrix;
            break;
        }
    }
}

int** Dictionary::getSecondHashFunction(int n, string *keys){
    int matrix_row       = ceil(log2(n));
//    this-> = matrix_row;

    while(true){
        int** Newmatrix=randomMatrix(matrix_row,32);

        int collision_array[int(pow(2,matrix_row))];

        for(int c=0;c<matrix_row;c++){
            collision_array[c]=0;
        }

        for(int d=0;d<n;d++){
            keys[d] = "        " + keys[d];
            int* array=Array_keys(keys[d].substr(keys[d].length()-8));
            int position[matrix_row];
            for(int k=0; k<matrix_row; k++){
                int result=0;
                for(int i=0; i<32; i++){
                    result+=(Newmatrix[k][i])*array[i];
                }
                position[k]=result%2;
            }
            int int_position=0;
            for(int b=0; b<matrix_row; b++){
                int_position+=position[b]*pow(2,b);
            }
            collision_array[int_position]+=1;
        }

        int sum=0;
        for(int e=0;e<pow(2,matrix_row);e++){
            sum+=pow(collision_array[e],2);
        }
        if (sum<(4*n)) {
//            this->firstHashMatrix = Newmatrix;
            return Newmatrix;
//            break;
        }
    }
}

void Dictionary::print(){
    //print the first hash matrix
    cout << "The first hash matrix is: " << endl;
    printMatrix(firstHashMatrix, firstMatrixRow, 32);

    int numberOfBucket = pow(2, this->firstMatrixRow);
    //print all second hash matrix and elements
    for(int each = 0; each < numberOfBucket; each++){
        if(firstHashTable[each]->secondHashTableSize != 0) {
            cout << "in the firstHashTable[" << each << "]:" << endl;
            cout << "The second matrix is: " << endl;
            printMatrix(firstHashTable[each]->secondMatrix, firstHashTable[each]->matrixSize, 32);

            for (int j = 0; j < firstHashTable[each]->secondHashTableSize; j++) {
//                cout << firstHashTable[each]->secondHash[j]->size() << endl;
                if (!firstHashTable[each]->secondHash[j]->empty()) {
                    for(int i = 0; i < firstHashTable[each]->secondHash[j]->size(); i++)
                        cout << "The elements stored in position " << i << " is: "
                         << firstHashTable[each]->secondHash[j]->at(i) << endl;
                }
            }
        }
    }
}

int main(){

//    Dictionary dic;
//    string* key = new string[3];
//    key[1] = "2asdfkgkygghdjrdjdfgjffsdfafdsafsffghmklughlh";
//    key[2] = "asdfweghmfkulhlhiuohiuhksdfsdfsafdsafasdf";
//    key[0] = "yhjykgkguguasdfasdfasflyluyhuluhliughhuhiuhoisdfsafdaf";
//
//    int** matrix = dic.getFirstHashFunction(3, key);
//    printMatrix(matrix, 2, 32);
//    for(int i = 0; i < 3; i++) {
//        int number   = namesChangeToNumber(key[i]);
//        cout << key[i] << " number is " << number << endl;
//        int position = numberTimesMatrix(matrix, 2, number);
//        cout << key[i] << " position is " << position << endl;
//    }

//    int** matrix = randomMatrix(3, 4);
//    printMatrix(matrix, 3, 4);


//    string s = "ssqqqqq";
//    int a = namesChangeToNumber(s);
//    cout << a << endl;
//    int **matrix = randomMatrix(4,32);
//    printMatrix(matrix, 4, 32);
//    int c = numberTimesMatrix(matrix, 4, 100);
//    cout << c << endl;

    Dictionary dic;
    string* key = new string[7];
    key[1] = "2asdfkgkygghdjrdjdfgjfffghm";
    key[2] = "asdfweghmfhk";
    key[0] = "yhjykgkgugulyluyhuluh";
    key[3] = "weqrwezxsdfsdf";
    key[4] = "aseqwerqwr";
    key[5] = "aseqwersdfaqqwerzz";
    key[6] = "122123asdaserqwerolxzc";
    dic.bulkInsert(7, key);
    dic.print();

}