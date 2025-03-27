#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>

//////////////////////////// Your Code //////////////////////////
std::vector<std::string> positiveWords, negativeWords;
/////////////////////////////////////////////////////////////////

void load_dictionary(const std::string &filename,
                     std::vector<std::string> &positiveWords,
                     std::vector<std::string> &negativeWords);
void load_dataset(const std::string &filename, std::vector<std::string> &titles,
                  std::vector<int> &years, std::vector<double> &ratings,
                  std::vector<std::string> &reviews);

//////////////////////////// Your Code //////////////////////////
// Java Moment
// Returns true if both inputs have the same value when changed to lowercase versions of themselves
bool equalsIgnoreCase(std::string const &word1, std::string const &word2){

  if(word1.size() != word2.size()) { return false; }

  for (int i=0; i < static_cast<int>(word1.size()); ++i){
    if(tolower(word1.at(i)) != tolower(word2.at(i))) { return false; }
  }
  return true;
}

// Returns true if word is found in wordSet regardless of capitalization
bool isInDataset(std::string const &word, std::vector<std::string> const &wordSet){
  for (std::string setWord : wordSet){
    if(equalsIgnoreCase(setWord, word)) { return true; }
  }
  return false;
}

// Returns true if word is found in the positive dataset
bool isPositive(std::string const &word){
  return isInDataset(word, positiveWords);
}
// Returns true if the word is found in the negative dataset
bool isNegative(std::string const &word){
  return isInDataset(word, negativeWords);
}

// Breaks a given string into a vector of its parts, seperated by non-alphanumeric values. Returns the broken up vector.
std::vector<std::string> stringBreak(std::string const &set){
  std::vector<std::string> wordSet;
  std::string newWord;
  for (const char &ch : set){
    if (!isalpha(ch)) { wordSet.push_back(newWord); newWord = ""; }
    else { newWord.push_back(ch); }
  }
  return wordSet;
}

// Sentiment calculator, returns -1 if more negative words are found, 1 if more positive, and 0 if they are equal
int wordTemperature (std::string const &review){
  
  int posCount = 0;
  int negCount = 0;
  
  std::vector<std::string> wordSet = stringBreak(review);
  for(const std::string &word : wordSet){
    if(isPositive(word)) { ++posCount; }
    if(isNegative(word)) { ++negCount; }
  }

  if(posCount > negCount) {return 1;}
  else if (negCount > posCount) {return -1;}
  return 0;
}

// Returns the index of the largest int in the given vector
int maxIndex(std::vector<int> const &list){
  if (static_cast<int>(list.size()) <= 0) {return -1;}
  int index = 0;
  for (int i = 0; i < static_cast<int>(list.size()); ++i){
    if (list.at(i) > list.at(index)) { index = i; }
  }
  return index;
}
// Returns the index of the smallest int in the given vector
int minIndex(std::vector<int> const &list){
  if (static_cast<int>(list.size()) <= 0) {return -1;}
  int index = 0;
  for (int i = 0; i < static_cast<int>(list.size()); ++i){
    if (list.at(i) < list.at(index)) { index = i; }
  }
  return index;
}
// Returns the index of the largest double in the given vector
int maxIndex(std::vector<double> const &list){
  if (static_cast<int>(list.size()) <= 0) {return -1;}
  int index = 0;
  for (int i = 0; i < static_cast<int>(list.size()); ++i){
    if (list.at(i) > list.at(index)) { index = i; }
  }
  return index;
}
// Returns the index of the smallest double in the given vector
int minIndex(std::vector<double> const &list){
  if (static_cast<int>(list.size()) <= 0) {return -1;}
  int index = 0;
  for (int i = 0; i < static_cast<int>(list.size()); ++i){
    if (list.at(i) < list.at(index)) { index = i; }
  }
  return index;
}

// Calculates the mean value of the given vector and returns it
double meanCalc(std::vector<double> const &list){
  double total = 0.0;
  for (double score : list){
    total += score;
  }
  
  return std::round(total / static_cast<double>(list.size()) * 100.0) / 100.0;
}

// Calculates the standard deviation of the given vector and returns it
double stdvCalc(std::vector<double> const &list){
  double mean = meanCalc(list);
  double sum = 0;
  for (double val : list){
    sum += std::pow((val - mean), 2);
  }
  return std::round(std::sqrt(sum / static_cast<double>(list.size())) * 100.0) / 100.0;
}

// Counts the number of positive numbers in a given array
int posCount(std::vector<int> const &list){
  int count = 0;
  for (int num : list) {
    if (num > 0) { ++count; }
  }
  return count;
}
// Counts the number of negative numbers in a given array
int negCount(std::vector<int> const &list){
  int count = 0;
  for (int num : list) {
    if (num < 0) { ++count; }
  }
  return count;
}
// Counts the number of zeros in a given array
int incCount(std::vector<int> const &list){
  int count = 0;
  for (int num : list) {
    if (num == 0) { ++count; }
  }
  return count;
}

/////////////////////////////////////////////////////////////////

// The main function
int main() {
  // File paths
  const std::string dataset1_path{"set1.csv"};
  const std::string dataset2_path{"set2.csv"};
  const std::string dictionary_path{"dictionary.txt"};

  // Load the word dictionary
  load_dictionary(dictionary_path, positiveWords, negativeWords);

  // Load the datasets
  std::vector<std::string> titles1, titles2;
  std::vector<int> years1, years2;
  std::vector<double> ratings1, ratings2;
  std::vector<std::string> reviews1, reviews2;
  std::vector<int> scores1, scores2;

  load_dataset(dataset1_path, titles1, years1, ratings1, reviews1);
  load_dataset(dataset2_path, titles2, years2, ratings2, reviews2);

  //////////////////////////// Your Code //////////////////////////
  // Gets sentiment scores for both sets
  for (int i = 0; i < static_cast<int>(reviews1.size()); ++i) {
    scores1.push_back(wordTemperature(reviews1.at(i)));
  }
  for (int i = 0; i < static_cast<int>(reviews2.size()); ++i){
    scores2.push_back(wordTemperature(reviews2.at(i)));
  }

  // Finds the highest/lowest rated films
  int max1ratingIndex = maxIndex(ratings1); int max2ratingIndex = maxIndex(ratings2);
  int min1ratingIndex = minIndex(ratings1); int min2ratingIndex = minIndex(ratings2);
  std::vector<std::string> combTitles = titles1; for(std::string title : titles2){combTitles.push_back(title);}
  std::vector<double> combRatings = ratings1; for(double rating : ratings2){combRatings.push_back(rating);}
  std::string bestTitle = combTitles.at(maxIndex(combRatings));
  std::string worstTitle = combTitles.at(minIndex(combRatings));

  // Outputs

  // Checks if dataset 1 is valid
  if(!static_cast<int>(titles1.size()) || !static_cast<int>(years1.size()) || !static_cast<int>(ratings1.size()) || 
  !static_cast<int>(reviews1.size()) || !static_cast<int>(scores1.size())) {
    std::cout << "ERROR: Dataset 1 is missing one or more columns. Exiting program." << std::endl;
  }
  // Checks if dataset 2 is valid
  else if(!static_cast<int>(titles2.size()) || !static_cast<int>(years2.size()) || !static_cast<int>(ratings2.size()) || 
  !static_cast<int>(reviews2.size()) || !static_cast<int>(scores2.size())) {
    std::cout << "ERROR: Dataset 2 is missing one or more columns. Exiting program." << std::endl;
  }
  // Output if datasets are valid
  else {
  std::cout << "          Set 1     Set 2\n------------------------------------------------\nCount:    "
            << static_cast<int>(scores1.size()) << "        " << static_cast<int>(scores2.size());
  std::cout << std::fixed << std::setprecision(2)
            << "\nMean:     " << meanCalc(ratings1) << "      " << meanCalc(ratings2)
            << "\nSTDV:     " << stdvCalc(ratings1) << "      " << stdvCalc(ratings2)
            << "\nMin:      " << ratings1.at(min1ratingIndex) << "      " << ratings2.at(min2ratingIndex)
            << "\nMax:      " << ratings1.at(max1ratingIndex) << "      " << ratings2.at(max2ratingIndex);
  // Ensures dictionary has values
  if (static_cast<int>(positiveWords.size()) == 0 || static_cast<int>(negativeWords.size()) == 0 || (static_cast<int>(positiveWords.at(0).size()) == 1 && static_cast<int>(positiveWords.size()) == 1)){
    std::cout << "\nERROR: Dictionary file is empty or missing a sentiment type. Not calculating sentiment analysis." << std::endl;
  } else {
  std::cout << "\nPos:      " << posCount(scores1) << "         " << posCount(scores2) 
            << "\nNeg:      " << negCount(scores1) << "         " << negCount(scores2)
            << "\nInc:      " << incCount(scores1) << "         " << incCount(scores2)
            << "\nOverall Best Title: " << bestTitle;
  std::cout << "\nOverall Worst Title: " << worstTitle << std::endl;
  }
  }

  /////////////////////////////////////////////////////////////////

  return 0;
}

// Loads the dictionary.txt file into two vectors of positiveWords and
// negativeWords
void load_dictionary(const std::string &filename,
                     std::vector<std::string> &positiveWords,
                     std::vector<std::string> &negativeWords) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error opening dictionary file." << std::endl;
    return;
  }
  std::string line;
  std::getline(file, line);
  const char delimiter{','};
  std::string token;
  std::stringstream posStream(line);
  while (std::getline(posStream, token, delimiter)) {
    positiveWords.push_back(token);
  }
  std::getline(file, line);
  std::stringstream negStream(line);
  while (std::getline(negStream, token, delimiter)) {
    negativeWords.push_back(token);
  }
}

// Loads the dataset into tokens representing each column
void load_dataset(const std::string &filename, std::vector<std::string> &titles,
                  std::vector<int> &years, std::vector<double> &ratings,
                  std::vector<std::string> &reviews) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error opening dataset file: " << filename << std::endl;
    return;
  }
  std::string line, title, review;
  int year;
  double rating;
  std::string temp;  // Skip the first line of the datasets (headers)
  getline(file, line);
  while (getline(file, line)) {
    std::stringstream ss(line);

    getline(ss, title, ',');
    getline(ss, temp, ',');
    year = std::stoi(temp);
    getline(ss, temp, ',');
    rating = std::stod(temp);
    getline(ss, review);
    titles.push_back(title);
    years.push_back(year);
    ratings.push_back(rating);
    reviews.push_back(review);
  }
  file.close();
}

//////////////////////////// Your Code //////////////////////////

/////////////////////////////////////////////////////////////////