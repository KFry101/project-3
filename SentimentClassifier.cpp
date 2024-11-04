
// SentimentClassifier.cpp
#include "SentimentClassifier.h"
#include <fstream>
#include <sstream>
#include <iomanip>

DSString SentimentClassifier::cleanTweet(const DSString& tweet) {
    // Convert to lowercase and remove special characters
    std::string temp = tweet.c_str();
    std::string result;
    
    for (char c : temp) {
        if (isalnum(c) || c == ' ') {
            result += tolower(c);
        }
    }
    
    return DSString(result.c_str());
}

std::vector<DSString> SentimentClassifier::tokenizeTweet(const DSString& tweet) {
    std::vector<DSString> tokens;
    std::string temp = tweet.c_str();
    std::stringstream ss(temp);
    std::string token;
    
    while (ss >> token) {
        tokens.push_back(DSString(token.c_str()));
    }
    
    return tokens;
}

void SentimentClassifier::processTweet(const DSString& tweet, const DSString& id, bool isPositive) {
    DSString cleanedTweet = cleanTweet(tweet);
    std::vector<DSString> words = tokenizeTweet(cleanedTweet);
    
    for (const DSString& word : words) {
        auto it = wordStats.find(word);
        if (it == wordStats.end()) {
            wordStats.emplace(word, WordSentiment(word));
            it = wordStats.find(word);
        }
        it->second.updateCount(isPositive);
    }
}

void SentimentClassifier::train(const char* trainingFile) {
    std::ifstream file(trainingFile);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open training file");
    }
    
    std::string line;
    // Skip header line
    std::getline(file, line);
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string sentiment, id, date, query, user, text;
        
        // Parse CSV line
        std::getline(ss, sentiment, ',');
        std::getline(ss, id, ',');
        std::getline(ss, date, ',');
        std::getline(ss, query, ',');
        std::getline(ss, user, ',');
        std::getline(ss, text);
        
        // Process tweet
        bool isPositive = (sentiment == "4");
        processTweet(DSString(text.c_str()), DSString(id.c_str()), isPositive);
    }
}

int SentimentClassifier::classifyTweet(const DSString& tweet) {
    DSString cleanedTweet = cleanTweet(tweet);
    std::vector<DSString> words = tokenizeTweet(cleanedTweet);
    
    double totalScore = 0.0;
    int wordCount = 0;
    
    for (const DSString& word : words) {
        auto it = wordStats.find(word);
        if (it != wordStats.end()) {
            totalScore += it->second.getSentimentScore();
            wordCount++;
        }
    }
    
    if (wordCount == 0) return 0;  // Default to negative if no known words
    return (totalScore / wordCount > 0) ? 4 : 0;
}

void SentimentClassifier::predict(const char* testFile) {
    std::ifstream file(testFile);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open test file");
    }
    
    std::string line;
    // Skip header line
    std::getline(file, line);
    
    predictions.clear();
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id, date, query, user, text;
        
        // Parse CSV line
        std::getline(ss, id, ',');
        std::getline(ss, date, ',');
        std::getline(ss, query, ',');
        std::getline(ss, user, ',');
        std::getline(ss, text);
        
        // Classify and store prediction
        int sentiment = classifyTweet(DSString(text.c_str()));
        predictions.push_back({DSString(id.c_str()), sentiment});
    }
}

void SentimentClassifier::evaluatePredictions(const char* truthFile, const char* resultsFile, const char* accuracyFile) {
    // Read truth file
    std::map<DSString, int> truth;
    std::ifstream truthF(truthFile);
    std::string line;
    while (std::getline(truthF, line)) {
        std::stringstream ss(line);
        std::string sentiment, id;
        std::getline(ss, sentiment, ',');
        std::getline(ss, id);
        
        int sentimentValue;
        try {
            sentimentValue = std::stoi(sentiment);
        } catch (const std::invalid_argument&) {
            // If sentiment is not an integer, assume it's "0" for negative, "4" for positive
            sentimentValue = (sentiment == "0" || sentiment == "negative") ? 0 : 4;
        }
        
        truth[DSString(id.c_str())] = sentimentValue;
    }
    
    // Write predictions to results file
    std::ofstream resultsF(resultsFile);
    for (const auto& pred : predictions) {
        resultsF << pred.second << "," << pred.first.c_str() << std::endl;
    }
    
    // Calculate accuracy and write to accuracy file
    int correct = 0;
    std::vector<std::tuple<int, int, DSString>> errors;  // (predicted, actual, id)
    
    for (const auto& pred : predictions) {
        int actualSentiment = truth[pred.first];
        if (pred.second == actualSentiment) {
            correct++;
        } else {
            errors.push_back({pred.second, actualSentiment, pred.first});
        }
    }
    
    double accuracy = (double)correct / predictions.size();
    
    std::ofstream accuracyF(accuracyFile);
    accuracyF << std::fixed << std::setprecision(3) << accuracy << std::endl;
    
    for (const auto& error : errors) {
        accuracyF << std::get<0>(error) << "," << std::get<1>(error) << "," 
                 << std::get<2>(error).c_str() << std::endl;
    }
}