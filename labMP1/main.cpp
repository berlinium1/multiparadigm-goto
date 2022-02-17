//
//  main.cpp
//  labMP1
//
//  Created by Берлинский Ярослав Владленович on 02.02.2022.
//

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, const char * argv[]) {
    
    string separators = " ,.:;[]{}|()<>!?^~+\"\"%#=\n";
    int sizeSeparators = 27;
    string stopWords[] = {"the", "on", "in", "at", "upon", "into", "onto", "for", "if", "a", "than", "then", "of", "or", "and", "not", "is", "to", "by"};
    int sizeStopWords = 19;
    int numberOfWords = 0;
    string* words = new string[numberOfWords];
    int N = 25;
    
    ifstream file("test.txt");
    if (file.is_open()) {
        fileReading:
        string line;
        if (file >> line) {
            
            string tempWord = "";
            int index = 0; bool exitFlag = false;
            
            line += "\0";
            
            loop:
            int sepIndex = 0;
            bool isSep = false;
            sepLoop:
            if (line[index] == separators[sepIndex]) {
                isSep = true;
            } else if (sepIndex < sizeSeparators) {
                sepIndex++;
                goto sepLoop;
            }
            if (line[index] <= 90 && line[index] >= 65) {
                line[index] = line[index] + 32;
            }
            if (isSep || line[index] == '\0') {
                if (tempWord != ""){
                    if (!isSep) tempWord += line[index];
                    int stop_words_index = 0; bool isStop = false;
                    stop_words_loop:
                    if (stop_words_index < sizeStopWords) {
                        if (stopWords[stop_words_index] == tempWord) isStop = true;
                        stop_words_index++;
                        goto stop_words_loop;
                    }
                    if (!isStop) {
                        string* wordsTemp = new string[numberOfWords + 1];
                        int indexTmp = 0;
                        loop1:
                        if (indexTmp < numberOfWords) {
                            wordsTemp[indexTmp] = words[indexTmp];
                            indexTmp++;
                            goto loop1;
                        }
                        wordsTemp[indexTmp] = tempWord;
                        words = nullptr;
                        numberOfWords++;
                        words = new string[numberOfWords];
                        indexTmp = 0;
                        loop2:
                        if (indexTmp < numberOfWords) {
                            words[indexTmp] = wordsTemp[indexTmp];
                            indexTmp++;
                            goto loop2;
                        }
                        delete [] wordsTemp;
                    }
                }
                tempWord = "";
                if (line[index] != '\0') {
                    index++;
                    goto loop;
                } else exitFlag = true;
            }
            if (!exitFlag) {
                tempWord += line[index];
                if (line[index] != '\0') {
                    index++;
                    goto loop;
                }
            }
            goto fileReading;
        } else {
            file.close();
        }
    }
    
    int numberOfUnique = 0;
    string* uniqueWords = new string[numberOfUnique];
    int* wordsOccurences = new int[numberOfUnique];
    int words_ind = 0;
    words_iteration_loop:
    if (words_ind < numberOfWords) {
        int temp_index = 0;
        checking_loop:
        if (temp_index < numberOfUnique) {
            if (words[words_ind] == uniqueWords[temp_index]) {
                words_ind++;
                goto words_iteration_loop;
            };
            temp_index++;
            goto checking_loop;
        }
        temp_index = 0;
        int* newUniqueOccurences = new int[numberOfUnique + 1];
        string* newUniqueWords = new string[numberOfUnique + 1];
        
        copy_loop:
        if (temp_index < numberOfUnique) {
            newUniqueOccurences[temp_index] = wordsOccurences[temp_index];
            newUniqueWords[temp_index] = uniqueWords[temp_index];
            temp_index++;
            goto copy_loop;
        }
        
        delete [] wordsOccurences;
        delete [] uniqueWords;
        
        uniqueWords = new string[++numberOfUnique];
        wordsOccurences = new int[numberOfUnique];
        
        temp_index = 0;

        copy_loop2:
        if (temp_index < numberOfUnique - 1) {
            wordsOccurences[temp_index] = newUniqueOccurences[temp_index];
            uniqueWords[temp_index] = newUniqueWords[temp_index];
            temp_index++;
            goto copy_loop2;
        }
        
        delete [] newUniqueWords;
        delete [] newUniqueOccurences;

        int counter = 0;
        temp_index = 0;
        
        word_counter_loop:
        if (temp_index < numberOfWords) {
            if (words[words_ind] == words[temp_index]) counter++;
            temp_index++;
            goto word_counter_loop;
        }
        wordsOccurences[numberOfUnique - 1] = counter;
        uniqueWords[numberOfUnique - 1] = words[words_ind];
        words_ind++;
        goto words_iteration_loop;
    }
    delete [] words;
    
    int i = 0, key_int, j;
    string key_str;
    sort_outer_loop:
    if (i < numberOfUnique) {
        key_int = wordsOccurences[i];
        key_str = uniqueWords[i];
        j = i - 1;


        sort_inner_loop:
        if (j >= 0 && wordsOccurences[j] < key_int)
        {
            uniqueWords[j + 1] = uniqueWords[j];
            wordsOccurences[j + 1] = wordsOccurences[j];
            j = j - 1;
            goto sort_inner_loop;
        }
        uniqueWords[j + 1] = key_str;
        wordsOccurences[j + 1] = key_int;
        i++;
        goto sort_outer_loop;
    }
    
    i = 0;
    print_loop:
    if (i < numberOfUnique && i < N) {
        cout << i << ") " << uniqueWords[i] << " - " << wordsOccurences[i] << endl;
        i++;
        goto print_loop;
    }
    
}
