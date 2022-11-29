#include <cstdio>
#include <cstring>
#include <vector>

const int maxS = 100 + 10;

char s[maxS];
bool matched[maxS];
std::vector<int> sta;

int main() {
    scanf("%s", s + 1);
    int len = strlen(s + 1);
    for (int i = 1; i <= len; i++) switch (s[i]) {
        case '(': {
            sta.push_back(i);
            break;
        }
        case '[': {
            sta.push_back(i);
            break;
        }
        case ')': {
            if (!sta.empty() && s[sta.back()] == '(' && !matched[sta.back()]) matched[sta.back()] = true, matched[i] = true, sta.pop_back(); 
            break;
        }
        case ']': {
            if (!sta.empty() && s[sta.back()] == '[' && !matched[sta.back()]) matched[sta.back()] = true, matched[i] = true, sta.pop_back();
            break;
        }
    }
    for (int i = 1; i <= len; i++) if (matched[i]) printf("%c", s[i]); else switch (s[i]) {
        case '(': {
            printf("()");
            break;
        }
        case ')': {
            printf("()");
            break;
        }
        case '[': {
            printf("[]");
            break;
        }
        case ']': {
            printf("[]");
            break;
        }
    }
    return 0;
}