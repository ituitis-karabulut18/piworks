#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
#define MAX_ROW 15 //4

void add_to_array(vector<int>, int**);  //function for the filling number pyramid

int** create_array();                   //function for the creating number pyramid

bool check_prime(int);                  //check the number is prime or not (if its prime return true)

vector<int> sums;                       //hold the sums

void find_the_paths(int**, int, int, int);  //find the path from top to down and fill the sums vector

int return_max_sum();                   //return maximum sum

void delete_array(int**); 


int main(){
    system("clear");                                                                //clear command 
    

    ifstream fileone;                                           //create file object
    fileone.open("../include/inputs_two.txt",ifstream::in);     //open file
    if (!fileone.is_open()) {                                   //if it couldnt be opened send en error
        cerr<<"file couldnt be opened"<<endl;
        exit(1);
    }

    int** number_array = create_array();                       //declare the number array (as pyramid)

    int number;
    vector<int> a;                                              // store all the values in the vector a
    
    while (fileone>>number)                                     //read values one by one
    {
        a.push_back(number);                                    // push to the array
    }


    add_to_array(a, number_array);                              // then create the number_array(as pyramid)

    find_the_paths(number_array, 0, 0, number_array[0][0]);     //find the paths and fill the sums array
    int max_sum = return_max_sum();                             //find the maximum sum
    cout<<max_sum;                                              //print maximum sum
    
    delete_array(number_array);                                 //delete the array

}

int** create_array(){

    int** number_array = new int*[MAX_ROW];                     //create array
    
    for (int i = 0; i < MAX_ROW; i++)
    {
        number_array[i] = new int[i+1];   
    }
    return number_array;
};


void add_to_array(vector<int> a ,int** array){
    
    int index = 0;                              // add to array
    for (int i = 0; i < MAX_ROW; i++)
    {
        for (int b = 0; b < i+1; b++)
        {
            array[i][b]= a[index];
            index++;
        }
    }
    
}

bool check_prime(int number){
    bool flag = false;              //if its prime return true   
    
    if (number == 0 || number == 1 )
    {
        return false;
    }else{
        for (int i = 2; i <= number/2; ++i) {
            if (number % i == 0) {
            flag = false;
            break;
            }
        }
        return flag;
    }
}

void find_the_paths(int** array, int index, int row, int sum){      //finding paths from top to down and filling the sums list by using recurisve approach
    if(row+1==MAX_ROW){                     //if its in the last row fill sums list
        sums.push_back(sum);
    }else{
        int sum_two = sum;                  
        if ( !check_prime(array[row+1][index])){            //check the numbers those on the road. If they are not prime numbers then choose as paths 
            sum = sum +array[row+1][index];
            find_the_paths(array, index, row+1, sum);       //send it back to same function
            }
        if ( !check_prime(array[row+1][index+1])){
            sum_two = sum_two +array[row+1][index+1];
            find_the_paths(array, index+1, row+1, sum_two);
            }
    }
};

int return_max_sum(){
    int max = sums[0];  //set the first value as max
    
    int a = 1;
    while ( a < sums.size())
    {
        if (max<sums[a])        //if max is smaller than any number in the array, set new value of the max 
        {
            max = sums[a];
        }
        a++;
        
    }
    return max;             //return the max
};

void delete_array(int** array){
                         
    for (int i = 0; i < MAX_ROW; i++)   //delete array
    {
        delete[] array[i];   
    }
    delete array;
};
 
