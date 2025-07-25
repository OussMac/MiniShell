#include "../execute.h"

t_cmd   *create_leaf(char *input, t_cmd_id id, t_osdata *osdata)
{
    t_cmd   *leaf; 
    leaf = malloc(sizeof(t_cmd));
    if (!leaf)
    {
        perror("malloc");
        return (NULL);
    }
    
    // Initialize the root node
    leaf->id = id; // assigning the id of this node
    leaf->argv = ft_split(input, ' '); // Split input into arguments
    leaf->osdata = osdata; // ptr to my data.
    leaf->left = NULL;
    leaf->right = NULL;

    return (leaf);
}

t_cmd   *add_right(t_cmd **root, char *input, t_cmd_id id)
{
    t_cmd   *new_leaf;

    // fail checks
    if (!root)
    {
        perror("No Root: ");
        return (NULL);
    }
    new_leaf = malloc(sizeof(t_cmd));
    if (!new_leaf)
    {
        perror("malloc");
        return (NULL);
    }
    (*root)->right = new_leaf;
    new_leaf->id = id; // assigning the id of this node
    new_leaf->argv = ft_split(input, ' '); // Split input into arguments
    new_leaf->left = NULL;
    new_leaf->right = NULL;
    return (new_leaf);
}

t_cmd   *add_left(t_cmd **root, char *input, t_cmd_id id)
{
    t_cmd   *new_leaf;

    // fail checks
    if (!root)
    {
        perror("No Root: ");
        return (NULL);
    }
    new_leaf = malloc(sizeof(t_cmd));
    if (!new_leaf)
    {
        perror("malloc");
        return (NULL);
    }
    (*root)->left = new_leaf;
    new_leaf->id = id; // assigning the id of this node
    new_leaf->argv = ft_split(input, ' '); // Split input into arguments
    new_leaf->left = NULL;
    new_leaf->right = NULL;
    return (new_leaf);
}

// t_cmd *create_tree(char *input)
// {
//     t_cmd *root = malloc(sizeof(t_cmd));
//     if (!root)
//     {
//         perror("malloc");
//         return (NULL);
//     }
    
//     // Initialize the root node
//     root->id = O_CMD; // Assuming the root is a command
//     // (will use aymane parsing for better tokenization)
//     root->argv = ft_split(input, ' '); // Split input into arguments
//     root->left = NULL;
//     root->right = NULL;

//     // here you would typically parse the input further to build the tree structure
//     // for simplicity, we are only creating a single command node.

//     return (root);
// }