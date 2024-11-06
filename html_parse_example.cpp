#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <sstream>

#include <myhtml/api.h>
#include <iostream>

mystatus_t serialization_callback(const char *data, size_t len, void *ctx)
{
    printf("%.*s", (int)len, data);
    return MyCORE_STATUS_OK;
}

void print_node_attr(myhtml_tree_node_t *node)
{
    myhtml_tree_attr_t *attr = myhtml_node_attribute_first(node);

    while (attr)
    {
        const char *name = myhtml_attribute_key(attr, NULL);

        if (name)
        {
            printf(" %s", name);

            const char *value = myhtml_attribute_value(attr, NULL);

            if (value)
                printf("=\"%s\"", value);
        }

        attr = myhtml_attribute_next(attr);
    }
}

void print_tree(myhtml_tree_t *tree, myhtml_tree_node_t *node, size_t inc)
{
    while (node)
    {
        for (size_t i = 0; i < inc; i++)
            printf("\t");

        // print current element
        const char *tag_name = myhtml_tag_name_by_id(tree, myhtml_node_tag_id(node), NULL);

        if (tag_name)
            printf("<%s", tag_name);
        else
            // it can not be
            printf("<!something is wrong!");

        // print node attributes
        print_node_attr(node);

        if (myhtml_node_is_close_self(node))
            printf(" /");

        myhtml_tag_id_t tag_id = myhtml_node_tag_id(node);

        if (tag_id == MyHTML_TAG__TEXT || tag_id == MyHTML_TAG__COMMENT)
        {
            const char *node_text = myhtml_node_text(node, NULL);
            printf(">: %s\n", node_text);
        }
        else
        {
            printf(">\n");
        }

        // print children
        print_tree(tree, myhtml_node_child(node), (inc + 1));
        node = myhtml_node_next(node);
    }
}

int main(int argc, const char *argv[])
{

    std::ifstream file("output.txt");
    if (!file)
    {
        std::cerr << "File could not be opened!" << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string content = buffer.str();

    const char *html = content.c_str(); // the html is confirmed in a C string

    // basic init
    myhtml_t *myhtml = myhtml_create();
    myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);

    // first tree init
    myhtml_tree_t *tree = myhtml_tree_create();
    myhtml_tree_init(tree, myhtml);

    // parse html
    myhtml_parse(tree, MyENCODING_UTF_8, html, strlen(html));

    const char *attr_key = "div";
    myhtml_collection_t *collection = myhtml_get_nodes_by_attribute_key(tree, NULL, NULL, attr_key,
                                                                        strlen(attr_key), NULL);

    std::cout << collection->length << std::endl;

    for (size_t i = 0; i < collection->length; i++)
    {
        myhtml_serialization_node_callback(collection->list[i], serialization_callback, NULL);
    }

    myhtml_tree_node_t *node = myhtml_tree_get_document(tree);
    print_tree(tree, myhtml_node_child(node), 0);

    myhtml_collection_destroy(collection);
    myhtml_tree_destroy(tree);
    myhtml_destroy(myhtml);
    return 0;
}