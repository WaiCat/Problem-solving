#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

const vector<string> handRanks = {
    "Top", "One Pair", "Two Pair", "Triple", "Straight", "Flush", "Full House",
    "Four Card", "Straight Flush"};

map<char, int> valueMap = {
    {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}, {'T', 10}, {'J', 11}, {'Q', 12}, {'K', 13}, {'A', 1}};

int getValue(char c)
{
  return valueMap[c];
}

bool isStraight(vector<int> &values)
{
  sort(values.begin(), values.end());
  if (values[4] - values[0] == 4 && set<int>(values.begin(), values.end()).size() == 5)
  {
    return true;
  }
  // Special case for A, 2, 3, 4, 5 straight
  if (values == vector<int>{2, 3, 4, 5, 14})
  {
    return true;
  }
  return false;
}

bool isFlush(vector<string> &hand)
{
  char suit = hand[0][0];
  for (int i = 1; i < 5; ++i)
  {
    if (hand[i][0] != suit)
    {
      return false;
    }
  }
  return true;
}

int getHandRank(vector<string> &hand)
{
  map<int, int> valueCount;
  map<char, int> suitCount;
  vector<int> values;

  for (const auto &card : hand)
  {
    int value = getValue(card[1]);
    values.push_back(value);
    valueCount[value]++;
    suitCount[card[0]]++;
  }

  bool flush = (suitCount.size() == 1);
  bool straight = isStraight(values);

  if (flush && straight)
  {
    return 8; // Straight Flush
  }

  if (valueCount.size() == 2)
  {
    for (const auto &kv : valueCount)
    {
      if (kv.second == 3)
      {
        return 6; // Full House
      }
    }
    for (const auto &kv : valueCount)
    {
      if (kv.second == 2)
      {
        return 2; // Two Pair
      }
    }
    for (const auto &kv : valueCount)
    {
      if (kv.second == 4)
      {
        return 7; // Four Card
      }
    }
  }

  if (flush)
  {
    return 5; // Flush
  }

  if (straight)
  {
    return 4; // Straight
  }

  if (valueCount.size() == 3)
  {
    for (const auto &kv : valueCount)
    {
      if (kv.second == 3)
      {
        return 3; // Triple
      }
    }
    return 2; // One Pair
  }

  if (valueCount.size() == 4)
  {
    return 1; // One Pair
  }

  return 0; // Top
}

vector<vector<string>> generateCombinations(vector<string> &cards)
{
  vector<vector<string>> combinations;
  int n = cards.size();
  for (int i = 0; i < n - 4; ++i)
  {
    for (int j = i + 1; j < n - 3; ++j)
    {
      for (int k = j + 1; k < n - 2; ++k)
      {
        for (int l = k + 1; l < n - 1; ++l)
        {
          for (int m = l + 1; m < n; ++m)
          {
            combinations.push_back({cards[i], cards[j], cards[k], cards[l], cards[m]});
          }
        }
      }
    }
  }
  return combinations;
}

string findBestHand(vector<string> &cards)
{
  vector<vector<string>> combinations = generateCombinations(cards);
  int bestRank = -1;

  for (auto &hand : combinations)
  {
    int rank = getHandRank(hand);
    if (rank > bestRank)
    {
      bestRank = rank;
    }
  }

  return handRanks[bestRank];
}

int main()
{
  ifstream input("1.inp");
  ofstream output("1.txt");

  int testCaseCount;
  input >> testCaseCount;

  while (testCaseCount--)
  {
    vector<string> cards(7);
    for (int i = 0; i < 7; ++i)
    {
      input >> cards[i];
    }

    string bestHand = findBestHand(cards);
    output << bestHand << endl;
  }

  input.close();
  output.close();

  return 0;
}
