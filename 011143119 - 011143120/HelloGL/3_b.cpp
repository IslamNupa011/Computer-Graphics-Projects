#include <bits/stdc++.h>

using namespace std;

char str_s[200000 + 10];
char str_t[200000 + 10];

int notmatch[300][200000 + 10];
int pos[300];

int main()
{
    freopen("input.txt", "r", stdin);
    int i, j;
    int n;
    int a, b;
    int dist;
    int found;
    int temp;
    a = -1, b = -1;
    dist = 0;
    found = 0;
    scanf("%d", &n);
    scanf("%s%s", str_s, str_t);
    printf("%s", str_s);
    for(i = 0; i < n; i++){
        if(str_s[i] != str_t[i]){
            dist++;
            if(notmatch[ str_t[i] ][0] != 56 && found == 0){
                temp = str_t[i];
                a = notmatch[ temp ][0];
                b = i;
                for(j = 0; notmatch[temp][j] != 0; j++){
                    if(notmatch[temp][j] == str_t[i]){
                        found = 1;
                        dist -= 1;
                    }
                }
            }
            else{
                notmatch[str_s[i]][pos[str_s[i]]++] = i;
                dist++;
            }
        }
    }
    printf("%d\n", dist);
    printf("%d %d\n", a, b);
}
