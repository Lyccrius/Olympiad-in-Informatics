#include<iostream>
#include<cstring>
#include<cstdio>
#include<map>

const int maxn = 100 + 10;

int n;
int cnt;

std::map<std::string, std::string> dictionary;
std::map<std::string, int> id;
bool visited[maxn], deleted[maxn];

void define(std::string str) {
    std::string name = "", content = "";
    int i;

    for (i = 8; str[i] != ' '; i++) {
        name += str[i];
    }
    for (i++; i <= str.length(); i++) {
        content += str[i];
    }

    dictionary[name] = content;
    id[name] = ++cnt;

    return;
}

void undef(std::string str) {
    int i;
    std::string name = "";

    for (i = 7; i < str.length(); i++) {
        name += str[i];
    }

    deleted[id[name]] = true;

    return;
}

bool check(char c) {
    if (c >= 'a' && c <= 'z' ||
        c >= 'A' && c <= 'Z') {
        return true;
    }

    if (c >= '0' && c <= '9') {
        return true;
    }

    if (c == '_') {
        return true;
    }

    return false;
}

void translate(std::string str) {
    std::string name = "";
    str += " ";
    for (int i = 0; i < str.length(); i++) {
        if (check(str[i])) {
            name += str[i];
            continue;
        }
        
        if (dictionary.find(name) == dictionary.end()) {
            std::cout << name;
        } else {
            if (deleted[id[name]] || visited[id[name]]) {
                std::cout << name;
            } else {
                visited[id[name]] = true;
                translate(dictionary[name]);
                visited[id[name]] = false;
            }
        }

        name = "";

        if (i != str.length() - 1 && str[i] != 0) {
            std::cout << str[i];
        }
    }

    return;
}

int main() {
    scanf("%d\n", &n);

    for (int i = 1; i <= n; i++) {
        std::string str;
        std::getline(std::cin, str);

        if (str[0] == '#') {
            if(str[1] == 'd') {
                define(str);
            } else {
                undef(str);
            }
        } else {
            translate(str);
        }
        
        printf("\n");
    }

    return 0;
}