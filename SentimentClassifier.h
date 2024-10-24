// SentimentClassifier.h
#ifndef SENTIMENT_CLASSIFIER_H
#define SENTIMENT_CLASSIFIER_H

#include "DSString.h"
#include <vector>
#include <map>

class WordSentiment {
private:
    DSString word;
    int positiveCount;
    int negativeCount;

public:
    WordSentiment(const DSString& w) : word(w), positiveCount(0), negativeCount(0) {}
    
    void updateCount(bool isPositive) {
        if (isPositive) positiveCount++;
        else negativeCount++;
    }
    
    double getSentimentScore() const {
        int total = positiveCount + negativeCount;
        if (total == 0) return 0.0;
        return (double)(positiveCount - negativeCount) / total;
    }
    
    const DSString& getWord() const { return word; }
};

class SentimentClassifier {
private:
    std::map<DSString, WordSentiment> wordStats;
    std::vector<std::pair<DSString, int>> predictions;  // (tweet_id, sentiment)

    // Helper methods
    std::vector<DSString> tokenizeTweet(const DSString& tweet);
    void processTweet(const DSString& tweet, const DSString& id, bool isPositive);
    int classifyTweet(const DSString& tweet);
    DSString cleanTweet(const DSString& tweet);
    
public:
    SentimentClassifier() = default;
    
    // Main interface methods
    void train(const char* trainingFile);
    void predict(const char* testFile);
    void evaluatePredictions(const char* truthFile, const char* resultsFile, const char* accuracyFile);
};
#endif 