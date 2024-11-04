#!/bin/bash

# Create bin directory if it doesn't exist
mkdir -p bin

# Compile with all warnings and debugging information
g++ -Wall -g \
    -I./include \
    src/main.cpp \
    src/DSString.cpp \
    src/SentimentClassifier.cpp \
    -o bin/sentiment_analyzer

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful! Executable created as bin/sentiment_analyzer"
else
    echo "Compilation failed!"
fi