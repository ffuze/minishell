#include "../minishell.h"

//-----------------------------------------------------------------------
void freeList(t_cmds *head)
{
	t_cmds *current = head;
	t_cmds *next_node;
	int i;

	while (current != NULL) {
		next_node = current->next;
		// Free each string in the cmd array
		if (current->cmd) {
			for (i = 0; current->cmd[i] != NULL; i++) {
				free(current->cmd[i]);
			}
			free(current->cmd); // Free the array itself
		}
		// Free the current node
		free(current);
		current = next_node;
	}
}

void	printList(t_cmds *head)
{
	t_cmds	*current;
	int		i;

	current = head;
	i = 0;
	while (current && current->cmd)
	{
		i = 0;
		ft_printf(RED"##"NO_ALL);
		if (current->cmd)
		{
			while (current->cmd[i])
			{
				if (current->cmd[i] != NULL)
                    ft_printf(YELLOW" %s "NO_ALL, current->cmd[i]);
                else
                    ft_printf(YELLOW" (null) "NO_ALL);
                i++;
			}
			if (current->outfile)
			{
				ft_printf(BRCYAN"in: %s, "NO_ALL, current->outfile);
				ft_printf(BRCYAN"append: %d, "NO_ALL, current->append_flag);
			}
		}
		else
            ft_printf(YELLOW" (cmd array is NULL) "NO_ALL);
		ft_printf(GREEN"##\n"NO_ALL);
		current = current->next;
	}
}

t_cmds	*crealista()
{
	t_cmds	*new_node;
	t_cmds	*root;
	t_cmds *current; // Pointer to keep track of the current node
	char *s = "ls -l";//"grep e"
	char *s2 = "wc -l";
	char *s3 = "cat";
   
	// Create the first node
	new_node = ft_calloc(1, sizeof(t_cmds));
	new_node->cmd = ft_split(s, ' ');
	root = new_node; // Set root to the first node
	current = new_node; // Set current to the first node
	
	// Create the second node
	new_node = ft_calloc(1, sizeof(t_cmds));
	new_node->cmd = ft_split(s2, ' ');
	current->next = new_node; // Link the first node to the second
	current = new_node; // Move current to the second node
	
	// Create the third node
	new_node = ft_calloc(1, sizeof(t_cmds));
	new_node->cmd = ft_split(s3, ' ');
	current->next = new_node; // Link the second node to the third
	current = new_node; // Move current to the third node
	
	// Set the next pointer of the last node to NULL
	current->next = NULL;
	
	// Print the list
	// printList(root);

	return root;
}
//-----------------------------------------------------------------------
