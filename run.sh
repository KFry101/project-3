#!/bin/bash

# Compile the C++ code
g++ -std=c++17 -o sentiment_analysis DSString.cpp SentimentClassifier.cpp main.cpp

# Run the sentiment analysis program
./sentiment_analysis data/train_dataset_20k.csv data/test_dataset_10k.csv data/test_dataset_sentiment_10k.csv results.csv accuracy.txt