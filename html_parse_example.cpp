#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <sstream>

#include <myhtml/api.h>
#include <iostream>

mystatus_t serialization_callback(const char* data, size_t len, void* ctx)
{
    printf("%.*s", (int)len, data);
    return MyCORE_STATUS_OK;
}

int main(int argc, const char * argv[])
{

    std::ifstream file("output.txt");
    if(!file) {
        std::cerr << "File could not be opened!" << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string content = buffer.str();

    const char* html = content.c_str();

    // basic init
    myhtml_t* myhtml = myhtml_create();
    myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);
    
    // first tree init
    myhtml_tree_t* tree = myhtml_tree_create();
    myhtml_tree_init(tree, myhtml);
    
    // parse html
    myhtml_parse(tree, MyENCODING_UTF_8, html, strlen(html));

    char* attr_key = "matchup-link";
    myhtml_collection_t *collection = myhtml_get_nodes_by_attribute_key(tree, NULL, NULL, attr_key, strlen(attr_key), NULL);

    for(size_t i = 0; i<collection->length; i++){
        myhtml_serialization_node_callback(collection->list[i], serialization_callback, NULL);
    }
    
    return 0;
}