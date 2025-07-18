#include "../execute.h"

int short_circuit_operand(t_cmd *node, t_cmd_id operand_id, t_osdata *osdata)
{
    int left_status = recursive_execution(node->left, osdata);
    if (operand_id == O_AND) // A && B
    {
        if (left_status == EXIT_SUCCESS) 
            return (recursive_execution(node->right, osdata)); // if A succeeds exec B
        else
            return (left_status);
    }
    else if (operand_id == O_OR) // A || B
    {
        if (left_status != EXIT_SUCCESS)
            return (recursive_execution(node->right, osdata)); // if A fail exec B
        else
            return (left_status);
    }
    return (EXIT_FAILURE); // should never return from here.
}
