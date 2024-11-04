// main.cpp
#include "DSString.h"
#include "SentimentClassifier.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

// Function to check if a file exists
bool fileExists(const char* filename) {
    std::ifstream file(filename);
    return file.good();
}

// Function to print usage instructions
void printUsage(const char* programName) {
    std::cout << "Usage: " << programName << " <training_file> <test_file> <test_truth_file> <results_file> <accuracy_file>\n";
    std::cout << "\nExample:\n";
    std::cout << programName << " train_dataset_20k.csv test_dataset_10k.csv test_dataset_sentiment_10k.csv results.csv accuracy.txt\n";
}

// Function to print results summary
void printResults(const char* resultsFile, const char* accuracyFile) {
    std::cout << "\nResults Summary:\n";
    std::cout << "================\n";

    // Print accuracy
    std::ifstream accFile(accuracyFile);
    if (accFile.is_open()) {
        std::string accuracy;
        std::getline(accFile, accuracy);
        std::cout << "Accuracy: " << accuracy << "%\n";
        
        // Print first few errors
        std::cout << "\nFirst few misclassifications:\n";
        std::cout << "Predicted,Actual,Tweet_ID\n";
        
        std::string line;
        int errorCount = 0;
        while (std::getline(accFile, line) && errorCount < 5) {
            std::cout << line << "\n";
            errorCount++;
        }
        if (errorCount == 5) {
            std::cout << "...(more errors in " << accuracyFile << ")\n";
        }
    }
    
    // Print sample of classifications
    std::cout << "\nSample of classifications:\n";
    std::cout << "Sentiment,Tweet_ID\n";
    
    std::ifstream resFile(resultsFile);
    if (resFile.is_open()) {
        std::string line;
        int lineCount = 0;
        while (std::getline(resFile, line) && lineCount < 5) {
            std::cout << line << "\n";
            lineCount++;
        }
        std::cout << "...(more results in " << resultsFile << ")\n";
    }
}

int main(int argc, char* argv[]) {
    try {
        // Check command line arguments
        if (argc != 6) {
            std::cerr << "Error: Incorrect number of arguments\n\n";
            printUsage(argv[0]);
            return 1;
        }

        // Check if input files exist
        if (!fileExists(argv[1])) {
            std::cerr << "Error: Training file '" << argv[1] << "' not found\n";
            return 1;
        }
        if (!fileExists(argv[2])) {
            std::cerr << "Error: Test file '" << argv[2] << "' not found\n";
            return 1;
        }
        if (!fileExists(argv[3])) {
            std::cerr << "Error: Truth file '" << argv[3] << "' not found\n";
            return 1;
        }

        // Create classifier
        std::cout << "Initializing sentiment classifier...\n";
        SentimentClassifier classifier;

        // Train classifier
        std::cout << "Training classifier with " << argv[1] << "...\n";
        classifier.train(argv[1]);

        // Make predictions
        std::cout << "Making predictions on " << argv[2] << "...\n";
        classifier.predict(argv[2]);

        // Evaluate and write results
        std::cout << "Evaluating predictions and writing results...\n";
        classifier.evaluatePredictions(argv[3], argv[4], argv[5]);

        // Print results summary
        printResults(argv[4], argv[5]);

        std::cout << "\nFull results have been written to:\n";
        std::cout << "- Classifications: " << argv[4] << "\n";
        std::cout << "- Accuracy report: " << argv[5] << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}