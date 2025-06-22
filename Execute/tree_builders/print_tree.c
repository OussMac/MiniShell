#include "../execute.h"

// convert the enum tupe to human readable string.
const char *cmd_id_to_str(t_cmd_id id)
{
    if (id == O_CMD)    
        return ("CMD");
    else if (id == O_REDIR)  
        return ("REDIR");
    else if (id == O_PIPE)   
        return ("PIPE");
    else if (id == O_OR)     
        return ("OR");
    else if (id == O_AND)    
        return ("AND");
    else if (id == GROUP)    
        return ("GROUP");
    return ("UNKNOWN");
}

// print single node data.
static void print_node(t_cmd *node)
{
    if (!node) 
        return ;
    printf("%s", cmd_id_to_str(node->id));
    if (node->id == O_CMD && node->argv)
    {
        printf(" [");
        int i = 0;
        while (node->argv[i])
        {
            if (i) printf(" ");
            printf("%s", node->argv[i]);
            i++;
        }
        printf("]");
    }
}

// recursive helper for debugging
//   prefix: kayb9a ydir spaces to indent in tree levels, branches
//   is_last: whether this node is the last child of its parent  
static void ft_print_tree(t_cmd *node, const char *prefix, int is_last)
{
    // base case wslna lend dial lbranch
    if (!node) 
        return ;

    // draw the branch
    // the drawing logic.
    printf("%s", prefix);
    // ila kan last branch dir lo hka
    if (is_last)
        printf("└─ ");
    else
        printf("├─ ");

    // print this node
    print_node(node);
    printf("\n");

    // prepare new prefix for children
    size_t len = ft_strlen(prefix);
    char new_prefix[len + 4];
    strcpy(new_prefix, prefix);
    if (is_last)
        ft_strcat(new_prefix, "   ");
    else
        ft_strcat(new_prefix, "│  ");

    // children: left then right
    // count how many non-null children to decide “last”
    int child_count = 0;
    if (node->left) 
        child_count++;
    if (node->right) 
        child_count++;
    int index = 0;

    if (node->left)
    {
        index++;
        ft_print_tree(node->left, new_prefix, index == child_count);
    }
    if (node->right)
    {
        index++;
        ft_print_tree(node->right, new_prefix, index == child_count);
    }
}

// we call this function first to check
void print_tree(t_cmd *root)
{
    if (!root) 
        return ;
    // root has no prefix and is considered “last”
    ft_print_tree(root, "", 1);
}
