#include "cachelab.h"
#include "getopt.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE_LENGTH 100

int hit = 0;
int miss = 0;
int evictions = 0;


// 定义内存访问结构
typedef struct {
    char type;        // 操作类型
    unsigned long address; // 64 位十六进制地址
    int size;        // 访问的字节数
} MemoryAccess;

typedef struct {
    int isValid;
    int time;
    unsigned long tag;
} CacheLine;


void CacheHit(char* Filename,CacheLine* cacheArray,int B,int S,int E,int v_flag);

void accessCache(MemoryAccess* memoryAccess,CacheLine* cacheArray, int blockSize,int S ,int E);

int main(int argc, char *argv[])
{
    int opt;
    int s_param = -1; // 用于存储 -s 参数
    int e_param = -1; // 用于存储 -E 参数
    int b_param = -1; // 用于存储 -b 参数
    char *t_param = NULL; // 用于存储 -t 参数
    int v_flag = -1; // 详细模式

    // 定义选项字符串，`s:` 和 `b:` 表示需要参数，`E` 表示不需要参数
    while ((opt = getopt(argc, argv, "s:b:E:t:v")) != -1) {
        switch (opt) {
            case 's':
                s_param = atoi(optarg); // 将 -s 的参数转换为整数
                break;
            case 'b':
                b_param = atoi(optarg); // 将 -b 的参数转换为整数
                break;
            case 'E':
                e_param = atoi(optarg); // 将 -E 的参数转换为整数
                break;
            case 't':
                t_param = optarg; // 存储 -t 的参数
                break;
            case 'v':
                v_flag = 1;
                break;
            case '?':
                fprintf(stderr, "Unknown option: %c\n", optopt);
                return 1;
        }
    }

    if (s_param == -1) {
        fprintf(stderr, "Error: Option -s is required.\n");
        return 1;
    }
    if (b_param == -1) {
        fprintf(stderr, "Error: Option -b is required.\n");
        return 1;
    }
    if (e_param == -1) {
        fprintf(stderr, "Error: Option -E is required.\n");
        return 1;
    }
    if (t_param == NULL){
        fprintf(stderr, "Error: Option -t is required.\n");
        return 1;
    }
    
    // printf("Option -s selected with value: %d\n", s_param);
    // printf("Option -b selected with value: %d\n", b_param);
    // printf("Option -E selected with value: %d\n", e_param);

    int S = 1<<s_param;
    int B = 1<<b_param;

    //访问CacheLine[i][j] = CacheLine[i*E+j]
    CacheLine* cacheArray = (CacheLine*)malloc(S*e_param*sizeof(CacheLine));

    //初始化
    for(int i = 0;i < S*e_param;i ++){
        cacheArray[i].isValid = 0; // 初始化为无效
        cacheArray[i].time = -1;    // 初始化时间戳
        cacheArray[i].tag = -1;    // 初始化标签
    }   

    //CacheHit
    CacheHit(t_param,cacheArray,B,S,e_param,v_flag);
    

    printf("hits:%d misses:%d evictions:%d",hit,miss,evictions);
    printSummary(hit, miss, evictions);
    return 0;
}

void CacheHit(char* Filename,CacheLine* cacheArray,int B,int S,int E,int v_flag){
    MemoryAccess access;
    FILE *file;
    char line[MAX_LINE_LENGTH];

    // 打开文件
    file = fopen(Filename, "r");
    if (file == NULL) {
        perror("Error opening file");
    }

    // 逐行读取文件内容
    while (fgets(line, sizeof(line), file)) {

        // 解析每一行
        if (line[0] == 'I') {
            // "I" 表示指令加载，直接在第一列
            sscanf(line, "%c %lx,%d", &access.type, &access.address, &access.size);
        } else {
            // "M"、"L" 和 "S" 在第二列，前有空格
            sscanf(line+1, "%c %lx,%d", &access.type, &access.address, &access.size);
        }
        
        
        
        switch (access.type)
        {
            case 'L':
            case 'S':{
                int lastHIt = hit,lastMiss = miss,lastEvictions = evictions;
                accessCache(&access,cacheArray,B,S,E); 
            if(v_flag == -1) break;
            if(lastEvictions < evictions && lastMiss < miss){
                printf("%c %lx,%d miss eviction\n",access.type,access.address,access.size);
            }else if(lastMiss < miss){
                printf("%c %lx,%d miss\n",access.type,access.address,access.size);
            }
            if(lastHIt < hit){
                printf("%c %lx,%d hit\n",access.type,access.address,access.size);
            }
            break;
            }
            case 'M':{
                int lastHIt = hit,lastMiss = miss,lastEvictions = evictions;
                accessCache(&access,cacheArray,B,S,E); 
                accessCache(&access,cacheArray,B,S,E); 
                if(v_flag == -1) break;
                if(lastEvictions < evictions && lastMiss < miss){
                    printf("%c %lx,%d miss eviction hit\n",access.type,access.address,access.size);
                }else if(lastMiss < miss){
                    printf("%c %lx,%d miss hit\n",access.type,access.address,access.size);
                }else if(lastHIt < hit){
                    printf("%c %lx,%d hit\n",access.type,access.address,access.size);
                }
                break;
            }
            
            default:
            break;
        
        }
    }

    // 关闭文件
    fclose(file);
}

void accessCache(MemoryAccess* memoryAccess, CacheLine* cacheArray, int blockSize, int S, int E) {
    unsigned long address = memoryAccess->address;
    unsigned long index = (address / blockSize) % S;
    unsigned long tag = (address / blockSize) / S;

    int isHit = 0;

    // 检查命中
    for (int i = 0; i < E; i++) {
        CacheLine* line = &cacheArray[index * E + i];
        if (line->isValid && line->tag == tag) {
            // 命中
            hit++;
            line->time = 1; // 重置命中缓存行的时间戳
            isHit = 1;
        } else {
            line->time++; // 未命中时增加其他缓存行的时间戳
        }
    }
    if (isHit == 1) return;

    // 未命中，需替换
    miss++;
    CacheLine* lineToReplace = NULL;

    // 找到无效行或最旧的行
    for (int i = 0; i < E; i++) {
        CacheLine* line = &cacheArray[index * E + i];
        if (!line->isValid) {
            lineToReplace = line; // 找到无效行
            break; // 立即退出循环
        } else if (lineToReplace == NULL || line->time > lineToReplace->time) {
            lineToReplace = line; // 找到最旧的行
        }
    }

    if (lineToReplace->isValid) {
        evictions++; // 如果替换的行是有效的，增加驱逐计数
    }

    // 替换缓存行
    lineToReplace->isValid = 1;
    lineToReplace->tag = tag;
    lineToReplace->time = 1; // 重置时间戳
}