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

    const char* attr_value = "matchup-link";
    const char* attr_key = "class";
    myhtml_collection_t *collection = myhtml_get_nodes_by_attribute_value(tree, NULL, NULL, true, 
    NULL, 0, attr_value, sizeof(attr_value), NULL);

    std::cout << collection->length << std::endl;

    for(size_t i = 0; i<collection->length; i++){
        myhtml_serialization_node_callback(collection->list[i], serialization_callback, NULL);
    }

    myhtml_collection_destroy(collection);
    myhtml_tree_destroy(tree);
    myhtml_destroy(myhtml);
    return 0;
}