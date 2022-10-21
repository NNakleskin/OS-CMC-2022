#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>

enum = { NOT_FOUND = 0 };

struct Tree{
    char name[101];
    unsigned int adress;
    struct Tree* left;
    struct Tree* right;
};

struct Tree* 
insert(struct Tree* root, char* x, unsigned int adress){
    if (!root){
        root = (struct Tree*)malloc(sizeof(struct Tree));
        root->left = 0;
        root->right = 0;
        strcpy(root->name, x);
        root->adress = adress;
    }
    else  if (strcmp(x, root->name) < 0){
        root->left = insert(root->left, x, adress);
    }
    else{
        root->right = insert(root->right, x, adress);
    }
    return root;
}

void 
reemove(struct Tree* root){
    if (!root){
        reemove(root->left);
        reemove(root->right);
        free(root);
    }
}


struct Tree* 
findmin(struct Tree* p) {
    return p->left ? findmin(p->left) : p;
}


struct Tree* 
removemin(struct Tree* p) {
    if (!p->left){
        return p->right;
    }
    p->left = removemin(p->left);
    return p;
}


struct Tree* 
find(struct Tree* p, char* kk)
{
    if (!p) return NOT_FOUND;
    if (strcmp(kk, p->name) < 0){
        return find(p->left, kk);
    }
    else if (strcmp(kk, p->name) > 0){
        return find(p->right, kk);
    }
    else return p;
    return NOT_FOUND;
}


int main(int argc, char **argv)
{
    struct Tree *root;
    if(argc < 2){
        return 0;
    }
    for(int i = 1; i < argc; i++){
        struct stat buf;
        if(lstat(argv[i], &buf) == -1){
            continue;
        }
        if(find(root, buf.ino_t) == NOT_FOUND){
            insert(root, buf.st_ino, argv[i]);
        } else {
            if(strcmp(argv[i], find(root, buf.st_ino)) > 0){
                insert(root, buf.st_ino, argv[i]);
            }   
        }

    }

    return 0;
}
