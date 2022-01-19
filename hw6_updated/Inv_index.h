#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <fstream>
//Do not include <unordered_map>

using namespace std;

class Inv_index{
public:
    Inv_index(); //Constructor
    ~Inv_index(); //Destructor

    void construct(string inputfile); //Construct inverted index
    int print_single(string word, int n); //Single word search
    int print_double(string word1, string word2, int n); //Double word search
    
    //And other functions 

private:
    vector<string> tokenizer(string line); //Tokenizer
    string stopwords[153] = {"a", "about", "above", "after", "again", "against", "ain", "all",
    "am", "an", "and", "any", "are", "aren", "as", "at", "be", "because", "been", "before",
    "being", "below", "between", "both", "but", "by", "can", "couldn", "d", "did", "didn",
    "do", "does", "doesn", "doing", "don", "down", "during", "each", "few", "for", "from",
    "further", "had", "hadn", "has", "hasn", "have", "haven", "having", "he", "her", "here",
    "hers", "herself", "him", "himself", "his", "how", "i", "if", "in", "into", "is", "isn",
    "it", "its", "itself", "just", "ll", "m", "ma", "me", "mightn", "more", "most", "mustn",
    "my", "myself", "needn", "no", "nor", "not", "now", "o", "of", "off", "on", "once",
    "only", "or", "other", "our", "ours", "ourselves", "out", "over", "own", "re", "s",
    "same", "shan", "she", "should", "shouldn", "so", "some", "such", "t", "than", "that",
    "the", "their", "theirs", "them", "themselves", "then", "there", "these", "they", "this",
    "those", "through", "to", "too", "under", "until", "up", "ve", "very", "was", "wasn",
    "we", "were", "weren", "what", "when", "where", "which", "while", "who", "whom", "why",
    "will", "with", "won", "wouldn", "y", "you", "your", "yours", "yourself", "yourselves"};
};


vector<string> Inv_index::tokenizer(string line) //Do not change this function
{
    vector<string> tokens;
    const char* delimiters = " ,.'!?:;\"&()-/\r\t";
    char* context;
    char* ptr = strtok_r((&line[0]), delimiters, &context); //Linux
    //char* ptr = strtok_s((&line[0]), delimiters, &context); //Windows
    while (ptr != NULL)
    {
        tokens.push_back(ptr);
        ptr = strtok_r(NULL, delimiters, &context); //Linux
        //ptr = strtok_s(NULL, delimiters, &context); //Windows
    }
        return tokens;
}

void Inv_index::construct(string inputfile)
{
    ifstream open(inputfile, ios::in);
    string line;
    vector<vector<string>> tokens; //you may change this part, it's just example
    while(!open.eof()){
        getline(open, line);
        tokens.push_back(tokenizer(line)); //you may change this part, it's just example
    }
    /* this loop is for checking the tokenizer works well
    for(int j = 0; j < 20; j++){
        for(unsigned int i = 0; i < tokens[j].size(); i++){
            cout<<tokens[j][i]<<endl;
        }
    }
    */
}

int Inv_index::print_single(string word, int n)
{
    /*
    Single word search
    1. Search documents which contain the word.
    2. print the first 'n' many documents. ex) n = 4: 45, 65, 79, 100 
    3. Return the number of documents which contain the word
    */
}

int Inv_index::print_double(string word1, string word2, int n)
{
    /*
    Double word search
    1. Search documents which contain word1 and word2.
    2. print the first 'n' many documents. ex) n = 4: 45, 65, 79, 100 
    3. Return the number of documents which contain the words 
    */
}