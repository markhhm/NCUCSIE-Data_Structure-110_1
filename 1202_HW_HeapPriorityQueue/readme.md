# 幹，好累
被字串處理髒到
一定要剛剛好才可以，如果有多餘的空間會吃wa
謝謝pp大佬的code，直接無情參考
真的快中風

```c
for (int i = 0; i < total; i++)
{
    int priority;
    char buffer[30];

    scanf("%30s %d", buffer, &priority);
    char *mission = (char *)calloc(strlen(buffer) + 1, sizeof(char));
    strcpy(mission, buffer);
    insert(max_heap, priority, mission);
}
```