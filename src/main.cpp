// main.cpp
#include <iostream>
#include <stdexcept>
#include "include\DSString.h"
#include "include\SentimentClassifier.h"

int main(int argc, char* argv[]) {
    if (argc != 6) {
        std::cerr << "Usage: " << argv[0] 
                  << " <training_file> <test_file> <test_truth_file> "
                  << "<results_file> <accuracy_file>" << std::endl;
        return 1;
    }
    
    try {
        // Create classifier instance
        SentimentClassifier classifier;
        
        // Training phase
        std::cout << "Training classifier..." << std::endl;
        classifier.train(argv[1]);
        
        // Testing phase
        std::cout << "Making predictions..." << std::endl;
        classifier.predict(argv[2]);
        
        // Evaluation phase
        std::cout << "Evaluating results..." << std::endl;
        classifier.evaluatePredictions(argv[3], argv[4], argv[5]);
        
        std::cout << "Classification complete! Check " << argv[4] 
                  << " for results and " << argv[5] << " for accuracy." << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}