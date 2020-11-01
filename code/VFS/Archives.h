//
// Created by xarvie on 2020/10/7.
//

#ifndef VFS_ARCHIVES_H
#define VFS_ARCHIVES_H

#include <cstdint>
#include <vector>
#include <unordered_map>
#include <list>
#include <cstdio>

typedef int64_t HashCode;

struct ArchivesFileHeadPart{
    HashCode id;
    uint64_t size;
    uint64_t pos;
};

struct HeadLayout{
    int64_t version;

    int64_t dataFileMaxSize;
    int64_t fileNum;
};
struct ArchivesDataHead{
    ArchivesFileHeadPart head;
    const char* name;
};
extern std::vector<char> readFile(const char* str);
extern std::vector<char> readFile2(FILE* fp, size_t size);
extern int writeFile(const char* str);
extern int writeFile2(FILE* f, const char* dataPtr, int size);
class Archives {
public:
    int createDataFile(const char* ful);

    int createFile(const char* name, char* ptr, size_t size);
    std::vector<char> readFile(const char* str);
    void deleteFile(const char* str);
    void modifyFile(const char* str);
    HashCode stringHash(const char* str);
    int openDataFile(const char* ful);
    int flushDataFile();

    int headParse();

    int close();
    char dataFileName[512];
    FILE* f;
    const char* datapath;

    int dataFileMaxSize = 1*1024*1024*1024;
    int fileMaxNum = 10000;
    int dataFileHeadMaxSize = fileMaxNum * sizeof(ArchivesFileHeadPart);
    int fileNum = 0;
    std::unordered_map<HashCode, ArchivesDataHead> headMap;
    std::list<ArchivesDataHead> headList;
    HeadLayout headLayout;
};


#endif //VFS_ARCHIVES_H
