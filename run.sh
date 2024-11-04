#!/bin/bash

# Check if executable exists
if [ ! -f bin/sentiment_analyzer ]; then
    echo "Executable not found! Running build script first..."
    ./build.sh
fi

# Run the program with the data files
./bin/sentiment_analyzer \
    data/train_dataset_20k.csv \
    data/test_dataset_10k.csv \
    data/test_dataset_sentiment_10k.csv \
    results.csv \
    accuracy.txt


if [ $? -eq 0 ]; then
    echo -e "\nResults:"
    echo "----------------------------------------"
    echo "Accuracy score:"
    head -n 1 accuracy.txt
    echo "----------------------------------------"
    echo "First few predictions:"
    head -n 5 results.csv
    echo "----------------------------------------"
    echo "Sample misclassifications:"
    tail -n 5 accuracy.txt
fi