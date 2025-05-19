#include "../minishell.h"

//-----------------------------------------------------------------------
void printList(t_cmds *head) {
    t_cmds *current = head;
	int i = 0;

    while (current != NULL) {
		while (current->cmd[i]){
        	printf("%s\n", current->cmd[i]);
			i++;
		}
        current = current->next;
    }
}

t_cmds	*crealista(char *s)
{
	t_cmds	*new_node;
	t_cmds	*root;

	new_node = ft_calloc(1, sizeof(t_cmds));
	new_node -> cmd = ft_split(s, ' ');
	root = new_node;
	new_node = new_node -> next;
	new_node = NULL;
	return (root);
}

//-----------------------------------------------------------------------
