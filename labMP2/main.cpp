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
    
    int numberOfWords = 0;
    int maxOccurence = 100;
    string* words = new string[numberOfWords];
    int** pageOccurences = new int*[maxOccurence];
    int pageNumber = 1;
    int lineNumber = 0;
    int maxLinesNumber = 45;
    ifstream file("test.txt");
    if (file.is_open()) {
        fileReading:
        string line;
        if (getline(file, line)) {
            lineNumber++;
            if (lineNumber == maxLinesNumber + 1) {
                pageNumber++;
                lineNumber = 0;
            }
            string tempWord = "";
            int index = 0; bool exitFlag = false;
            
            line += "\0";
            
            loop:
            bool isSep = !((line[index] >= 65 && line[index] <= 90) || (line[index] >= 97 && line[index] <= 122));
            if (line[index] <= 90 && line[index] >= 65) {
                line[index] = line[index] + 32;
            }
            if (isSep || line[index] == '\0') {
                if (tempWord != "") {
                    if (!isSep) tempWord += line[index];
                    
                    bool isUnique = true;

                    int i = 0;
                    unique_check_loop:
                    if (i < numberOfWords) {
                        if (tempWord == words[i]) {
                            isUnique = false;

                            int j = 0;
                            checking_loop_2:
                            if (j < maxOccurence) {
                                if (pageOccurences[i][j] == -1 || pageOccurences[i][j] == pageNumber) {
                                    pageOccurences[i][j] = pageNumber;
                                    j = maxOccurence;
                                }
                                j++;
                                goto checking_loop_2;
                            }
                            j = 0;
                        }
                        i++;
                        goto unique_check_loop;
                    }
                    if (isUnique) {
                        string* newWords = new string[numberOfWords + 1];
                        
                        int i = 0;
                        int** newOccurences = new int*[numberOfWords + 1];
                        alloc_new_1:
                        if (i < numberOfWords) {
                            newWords[i] = words[i];
                            newOccurences[i] = new int[maxOccurence];
                            int j = 0;
                            alloc_new_inner_1:
                            if (j < maxOccurence) {
                                newOccurences[i][j] = pageOccurences[i][j];
                                j++;
                                goto alloc_new_inner_1;
                            }
                            i++;
                            goto alloc_new_1;
                        }
                        newWords[numberOfWords] = tempWord;
                        newOccurences[numberOfWords] = new int[maxOccurence];
                        i = 0;
                        forming_new_1:
                        if (i < maxOccurence) {
                            newOccurences[numberOfWords][i] = -1;
                            i++;
                            goto forming_new_1;
                        }
                        newOccurences[numberOfWords][0] = pageNumber;
                        
                        i = 0;
                        delete [] words;
                        del_old_1:
                        if (i < numberOfWords) {
                            delete [] pageOccurences[i];
                            i++;
                            goto del_old_1;
                        }
                        delete [] pageOccurences;
                        
                        i = 0;
                        words = new string[++numberOfWords];
                        pageOccurences = new int*[numberOfWords];
                        alloc_old_1:
                        if (i < numberOfWords) {
                            words[i] = newWords[i];
                            pageOccurences[i] = new int[maxOccurence];
                            int j = 0;
                            alloc_old_inner_1:
                            if (j < maxOccurence) {
                                pageOccurences[i][j] = newOccurences[i][j];
                                j++;
                                goto alloc_old_inner_1;
                            }
                            i++;
                            goto alloc_old_1;
                        }
                        
                        i = 0;
                        delete [] newWords;
                        del_new_1:
                        if (i < numberOfWords) {
                            delete [] newOccurences[i];
                            i++;
                            goto del_new_1;
                        }
                        delete [] newOccurences;
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
            int i = 0;
            size_filtering_loop:
            if (i < numberOfWords) {
               
                bool delete_flag = false;
                if (pageOccurences[i][maxOccurence - 1] != -1) {
                    delete_flag = true;
                }
                if (delete_flag) {
                    int j = 0;
                    string* newWords = new string[numberOfWords - 1];
                    int** newOccurences = new int*[numberOfWords - 1];
                    copying_loop:
                    if (j < numberOfWords - 1) {
                        if (j < i) newWords[j] = words[j];
                        else newWords[j] = words[j+1];
                        newOccurences[j] = new int[maxOccurence];
                        int k = 0;
                        copying_loop_inner:
                        if (k < maxOccurence) {
                            if (j < i) newOccurences[j][k] = pageOccurences[j][k];
                            else newOccurences[j][k] = pageOccurences[j+1][k];
                            k++;
                            goto copying_loop_inner;
                        }
                        j++;
                        goto copying_loop;
                    }

                    delete [] words;
                    j = 0;
                    del_old_loop:
                    if (j < numberOfWords) {
                        delete [] pageOccurences[j];
                        j++;
                        goto del_old_loop;
                    }
                    delete [] pageOccurences;

                    numberOfWords--;
                    words = new string[numberOfWords];
                    pageOccurences = new int*[numberOfWords];
                    j = 0;
                    copying_new_loop:
                    if (j < numberOfWords) {
                        words[j] = newWords[j];
                        pageOccurences[j] = new int[maxOccurence];
                        int k = 0;
                        copying_new_loop_inner:
                        if (k < maxOccurence) {
                            pageOccurences[j][k] = newOccurences[j][k];
                            k++;
                            goto copying_new_loop_inner;
                        }
                        j++;
                        goto copying_new_loop;
                    }

                    delete [] newWords;
                    j = 0;
                    del_new_loop:
                    if (j < numberOfWords) {
                        delete [] newOccurences[j];
                        j++;
                        goto del_new_loop;
                    }
                    delete [] newOccurences;
                    goto size_filtering_loop;
                }
                i++;
                goto size_filtering_loop;
            }
            file.close();
        }
    }
    
    int i = 0, j;
    string key_str;
    sort_outer_loop:
    if (i < numberOfWords) {
        key_str = words[i];
        j = i - 1;


        sort_inner_loop:
        if (j >= 0 && words[j] > key_str)
        {
            words[j + 1] = words[j];
            int k = 0;
            swap_array_loop:
            if (k < maxOccurence) {
                int temp = pageOccurences[j][k];
                pageOccurences[j][k] = pageOccurences[j + 1][k];
                pageOccurences[j + 1][k] = temp;
                k++;
                goto swap_array_loop;
            }
            j = j - 1;
            goto sort_inner_loop;
        }
        words[j + 1] = key_str;
        i++;
        goto sort_outer_loop;
    }
    
    i = 0;
    print_loop:
    if (i < numberOfWords) {
        cout << endl << i << ") " << words[i] << " - ";
        int j = 0;
        print_loop_inner:
        if (j < maxOccurence && pageOccurences[i][j] != -1) {
            if (j != 0) {
                cout << ", ";
            }
            cout << pageOccurences[i][j];
            j++;
            goto print_loop_inner;
        }
        cout << endl;
        i++;
        goto print_loop;
    }
}
