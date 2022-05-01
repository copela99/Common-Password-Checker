#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>

using std::string; using std::vector;
using std::ifstream; using std::ostream_iterator;
using std::cout; using std::cin; using std::endl;
using std::fstream; using std::make_pair; using std::pair;
using std::endl; using std::iterator;


int pswd_diff(string &pswd, string &common_pswd)
{
  //assigning string names by length
  string big, little;
  if (pswd.length() <  common_pswd.length())
  {
    little = pswd;
    big = common_pswd;
  }
  else
  {
    big = pswd;
    little = common_pswd;
  }

  int count = 0;
  for(int i = 0; i < static_cast<int>(little.length()); i++)
  {
    if(little[i] != big[i])
    {
      count++;
    }
  }
  //length plays a factor in calculating the difference
  count = count + (static_cast<int>(big.length()) - static_cast<int>(little.length()));
  return count;
}

vector<pair<string,int>> create_vec(ifstream &in_file, string &pswd)
{
  vector<pair<string,int>> pswd_and_diff;
  string common_pswd;
  //applying a difference integer to each word
  while(getline(in_file,common_pswd,'\n'))
  {
    int diff = pswd_diff(pswd,common_pswd);
    pswd_and_diff.push_back(make_pair(common_pswd,diff));
  }
  //sorting by last name and if they are equal then first name
  auto ans = [](pair<string,int> &p1, pair<string,int> &p2)
  {
    //just like homework 19
    if(p1.second != p2.second)
    {
      return p1.second < p2.second;
    }
    return p1.first < p2.first;
  };
  sort(pswd_and_diff.begin(),pswd_and_diff.end(),ans);
  //returning closest common passwords first
  return pswd_and_diff;
}


void print_final_vec(ifstream &in_file, string &pswd)
{

  vector<string> similar_pswds;
  auto vec = create_vec(in_file,pswd);
  int most_similar_diff = vec.front().second;
  vector<pair<string,int>>::iterator it;
  it = vec.begin();
  //indexing the vector pair to get all of the least common differences 
  int i = 0;
  while(it != vec.end())
  {
    if(vec[i].second == most_similar_diff)
    {
      similar_pswds.push_back(vec[i].first);
    }
    i++;
    it++;
  }
  cout << "You provided a password of: " << pswd << endl;
  cout << "The most similar passwords to " << pswd << " are:" << endl;
  copy(similar_pswds.begin(),similar_pswds.end(),ostream_iterator<string>(cout,","));
  cout << endl;
  cout << "All of which are " << most_similar_diff <<  " character(s) different." << endl;
  cout << endl;
}

int main()
{
  ifstream in_file("common_passwords.txt");
  string pswd;
  cout << "Give me a password: " << endl;
  getline(cin,pswd);
  print_final_vec(in_file,pswd);

}
