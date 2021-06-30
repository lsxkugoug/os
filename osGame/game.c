# include <stdio.h>
# include <curses.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/time.h>
# include <stdbool.h>

# define CHAR_BIRD 'O'  // bird
# define CHAR_STONE '*'  // obstacle
# define CHAR_BLANK ' '  // space

typedef struct node {
    int x, y;
    struct node *next;
}node, *Node;

int main(){
    Node n;
    n->x = 8;

}