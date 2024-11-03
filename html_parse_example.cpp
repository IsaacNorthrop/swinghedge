#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>

#include <myhtml/api.h>
#include <iostream>

int main(int argc, const char * argv[])
{

    FILE* f = fopen("output.txt", "r");
    char* buffer;
    char* html;
    int MAX_LENGTH = 100;

    while(fgets(buffer, MAX_LENGTH, f))
        strcat(html, buffer);

    std::cout << html << std::endl;

    fclose(f);

    
    // basic init
    myhtml_t* myhtml = myhtml_create();
    myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);
    
    // first tree init
    myhtml_tree_t* tree = myhtml_tree_create();
    myhtml_tree_init(tree, myhtml);
    
    // parse html
    myhtml_parse(tree, MyENCODING_UTF_8, html, strlen(html));
    
    return 0;
}