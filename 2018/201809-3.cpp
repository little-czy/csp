#include <iostream>
#include <string.h>

using namespace std;

typedef struct node{
    int height;
    int flag;
    int line;
    char name[80];
    char id[80];
    struct node * child;
    struct node * borther;

}node;

//找到下一行文字在二叉树中的位置
node * find_node(node * root, node * curent_node, char * s, int *b) {
    int dot_num = 0;
    while (s[dot_num] == '.') {
        dot_num++;
    }
    dot_num = dot_num / 2;
    
    if (dot_num < curent_node->height) {
        node * temp_node = root;
        for (int i = 0; i < dot_num; i++) {
            temp_node = temp_node->child;
        }
        while(temp_node->borther) {
            temp_node = temp_node->borther;
        }
        *b = 1;
        return temp_node;
    } else if (dot_num == curent_node->height) {
        *b = 1;
        return curent_node;
    } else {
        *b = 0;
        return curent_node;
    }
}

int have_id(char * s) {  //判断是否存在id
    int i;
    for (i = 0; s[i] != '\n'; i++) {
        if (s[i] == ' ' && s[i+1] == '#') {
            return 1;
        }
    }
    return 0;
}

int get_name(char * source, char * dest) {  //获得选择器名称
    if (source[0] != '\n') {
        int i;
        for (i = 0; source[i] == '.'; i++);
        for (int j = 0; source[i] != ' '; i++, j++) {
            dest[j] = source[i];
        }
        return 1;
    } else {
        return 0;
    }
}

void get_id(char * source, char * dest) {  //获得id
    int i;
    for (i = 0; source[i] != '#'; i++);
    for (int j = 0; source[i] != ' '; i++, j++) {
        dest[j] = source[i];
    }
}

int get_height(char * s) {  //获得选择器在二叉树中的高度
    int dot_num = 2;
    while (s[dot_num] == '.') {
        dot_num++;
    }
    dot_num = dot_num / 2;
    return dot_num;
}

int parting_a_name(char * source, char *dest) {  //从字符串中取出一个选择器/id
    int i = 0;
    if (source[0] != '\n') {
       while (source[i] != ' ') {
            dest[i] = source[i];
            i++;
        } 
        return 1;
    } else {
        return 0;
    }
}

int remove_first_word(char * source, char *dest) {
    int i = 0, j = 0;
    if (source[i] != '\n') {
       while (source[i] != ' ') {
            i++;
        }
        i++;
        while (source[i] != '\n') {
            dest[j] = source[i];
            j++;
            i++;
        }
        return 1; 
    } else 
        return 0;
}

int find_select(node * root, char * s) {
    char s_name[80];
    if (parting_a_name(s, s_name)) {
        if (s_name[0] == '#') {
            if (root->flag && strcmp(s_name, root->id) ==0) {
                char remove_a_name[80];
                if (remove_first_word(s_name, remove_a_name)) {
                    if (root->child)
                        find_select(root->child, remove_a_name);
                    else
                        return 0;
                } else {
                    return root->line;
                }
            } else {
                if (root->borther) {
                    find_select(root->borther, s);
                } else {
                    return 0;
                }
            }
        } else {
            if (strcmp(s_name, root->name) == 0) {
                char remove_a_name[80];
                if (remove_first_word(s_name, remove_a_name)) {
                    if (remove_a_name[0] == '#'){
                        find_select(root, remove_a_name);
                    } else {
                        find_select(root->child, remove_a_name);
                    }
                } else {
                    return root->line;
                }
            } else {
                if (root->borther) {
                    find_select(root->borther, s);
                } else {
                    return 0;
                }
            }
        }
    }
    return root->line;
}

int find_all_select(node * root, char * s) {
    char temp_s[80];
    if (get_name(s, temp_s)) {
        if (s[0] == '#') {
            if (root->flag && strcmp(root->id, temp_s) == 0) {
                cout << find_select(root, s) << endl;
                if (root->child) {
                    find_all_select(root->child, s);
                }
                if (root->borther) {
                    find_all_select(root->borther, s);
                }
            } else {
                if (root->child) {
                    find_all_select(root->child, s);
                }
                if (root->borther) {
                    find_all_select(root->borther, s);
                }
            }
        } else {
            if (strcmp(root->name, temp_s) == 0) {
                cout << find_select(root, s) << endl;
                if (root->child) {
                    find_all_select(root->child, s);
                }
                if (root->borther) {
                    find_all_select(root->borther, s);
                }
            } else {
                if (root->child) {
                    find_all_select(root->child, s);
                }
                if (root->borther) {
                    find_all_select(root->borther, s);
                }
            }
        }
    }
    return 0;
}

int main(){
    int n, m;
    char s[80];
    cin >> n >> m;
    node html, *root = &html, *current_node = root;
    cin >> s;
    html.borther = NULL;
    html.child = NULL;
    html.flag = have_id(s);
    html.height = 1;
    html.line = 1;
    if (html.flag) {
        get_name(s, html.name);
        get_id(s, html.id);
    } else {
        get_name(s, html.name);
    }
    for (int i = 1; i < n; i++) {  //生成左孩子右兄弟二叉树
        cin >> s;
        node *temp_node = (node *)malloc(sizeof(node));
        temp_node->line = i+1;
        temp_node->flag = have_id(s);
        if (temp_node->flag) {
            get_name(s, temp_node->name);
            get_id(s, temp_node->id);
        } else {
            get_name(s, temp_node->name);
        }
        temp_node->child = NULL;
        temp_node->borther = NULL;
        int b;
        current_node = find_node(root, current_node, s, &b);
        if (b) {
            current_node->borther = temp_node;
            current_node = current_node->borther;
        } else {
            current_node->child = temp_node;
            current_node = current_node->child;
        }
    }
    for (int i = 0; i < m; i++) {
        cin >> s;
        find_all_select(root, s);
    }
    system("pause");
    return 0;
}