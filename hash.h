#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <cctype>

typedef std::size_t HASH_INDEX_T;
//typedef std::unsigned long long HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }

    HASH_INDEX_T operator()(const std::string& k) const
    {
        const int num_chunks = 5;        
    const int chunk_size = 6;       
    const HASH_INDEX_T base = 36;    

    HASH_INDEX_T chunk_values[num_chunks] = {0};  
    int current_chunk = num_chunks - 1;           

    for (int pos = k.length(); pos > 0; pos -= chunk_size) 
    {
        int start = std::max(0, pos - chunk_size);
        int length = pos - start;
        HASH_INDEX_T chunk_result = 0;
        HASH_INDEX_T multiplier = std::pow(base, length - 1);

        // Compute the value of the current chunk
        for (int i = start; i < start + length; ++i) 
        {
            HASH_INDEX_T value = letterDigitToNumber(k[i]);
            chunk_result += value * multiplier;
            multiplier /= base;
        }

        chunk_values[current_chunk--] = chunk_result;
    }

    // Combine the chunks using the provided r vales
    HASH_INDEX_T hash_value = 0;
    for (int i = 0; i < num_chunks; ++i) {
        hash_value += rValues[i] * chunk_values[i];
    }

    return hash_value;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
       letter = std::tolower(letter);

    if (letter >= '0' && letter <= '9') 
    {
        return static_cast<HASH_INDEX_T>(letter - '0' + 26);
    } 
    else if (letter >= 'a' && letter <= 'z') 
    {
        return static_cast<HASH_INDEX_T>(letter - 'a');
    }
    return 0;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif