#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <myhtml/api.h>
#include <iostream>
#include <vector>
#include <regex>

std::vector<std::string> links;

mystatus_t serialization_callback(const char *data, size_t len, void *ctx)
{
    const char* start_point = "<";
    if(!strcmp(data, start_point))
        links.push_back("");

    std::string str(data, len);
    links[links.size()-1] += str;
    return MyCORE_STATUS_OK;
}

std::vector<std::string> get_links(std::string response)
{

    const char *html = response.c_str(); // the html is confirmed in a C string

    // basic init
    myhtml_t *myhtml = myhtml_create();
    myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);

    // first tree init
    myhtml_tree_t *tree = myhtml_tree_create();
    myhtml_tree_init(tree, myhtml);

    // parse html
    myhtml_parse(tree, MyENCODING_UTF_8, html, strlen(html));

    const char *attr_key = "class";
    const char *attr_val = "matchup-link";
    myhtml_collection_t *collection = myhtml_get_nodes_by_attribute_value(tree, NULL, NULL, true, attr_key, strlen(attr_key),
                                                                        attr_val, strlen(attr_val), NULL);
    
    for (size_t i = 0; i < collection->length; i++)
    {
        myhtml_serialization_node_callback(collection->list[i], serialization_callback, NULL);
    }

    for(size_t i = 0; i<links.size(); i++){
        std::string matchup_link = links[i].substr(links[i].find("href=\"", links[i].size()-1)); // out of range
        std::cout << matchup_link << std::endl;
    }

    printf("%d\n", links.size());
    for(int i = 0; i<links.size(); i++){
        std::cout<<links[i];
        printf("\n");
    }
    myhtml_tree_node_t *node = myhtml_tree_get_document(tree);
    //print_tree(tree, myhtml_node_child(node), 0);

    myhtml_collection_destroy(collection);
    myhtml_tree_destroy(tree);
    myhtml_destroy(myhtml);
    return links;
}