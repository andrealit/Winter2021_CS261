# define TYPE
struct Node {
  TYPE   val;
  struct Node
  struct Node
  int height;
};

/* return height of current*/
int height(struct Node *current){
  if (current == 0) return -1;
  return current->height;
}

/* Rotate left the input node
    - Input: current = height unbalanced node
    - Output: new height-balanced node
    - Pre-conditions: current and current->right are not NULL
*/
struct Node * rotateLeft(struct Node * current) {
    /* FIX ME */
    struct Node * new = current->right; /* 3 points */

    current->right = new->left; /* 3 points */

    new->left = current; /* 3 points */

    setHeight(current); /* 2 points */

    setHeight(new); /* 2 points */

    return new;

}

void setHeight (struct Node* current) {
    int lch = height(current->left);
    int rch = height(current->right);

    if (lch < rch) {
        current->height = 1 + rch;
    } else {
        current->height = 1 + lch;
    }
}