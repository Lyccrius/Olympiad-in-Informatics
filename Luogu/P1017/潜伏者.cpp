#include <bits/stdc++.h>

using namespace std;

char secret[110];
char origin[110];

char message[110];

char key[30];

bool vis_s[30];
bool vis_o[30];

int main() {
    cin >> secret;
    cin >> origin;

    cin >> message;

    for (int i = 0; secret[i] != '\0'; i ++) {
        if (vis_s[secret[i] - 'A'] && key[secret[i] - 'A'] != origin[i]) {
            cout << "Failed" << endl;
            return 0;
        } 

        key[secret[i] - 'A'] = origin[i];
        vis_s[secret[i] - 'A'] = true;
        vis_o[origin[i] - 'A'] = true;
    }

    for (int i = 0; i < 26; i ++) {
        if (!vis_s[i] || !vis_o[i]) {
            cout << "Failed" << endl;
            return 0;
        }
    }

    for (int i = 0; message[i] != '\0'; i ++) cout << key[message[i] - 'A'];

    cout << endl;

    return 0;
}