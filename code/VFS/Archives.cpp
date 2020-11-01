//
// Created by xarvie on 2020/10/7.
//

#include "Archives.h"
#include "fnv1a.h"
#include <cstdio>
#include <cstring>

#include<iostream>
int Archives::createDataFile(const char *ful) {

    FILE *fp = fopen(ful, "rb");
    if (fp != NULL) {
        fclose(fp);
        return -1;
    }

    fp = fopen(ful, "wb+");
    if (f == NULL)
        return -1;

    size_t headSizeReal = (sizeof(HeadLayout) + fileMaxNum * sizeof(ArchivesFileHeadPart));
    char *out = (char *) malloc(headSizeReal);
    memset(out, 0, headSizeReal);
    this->headLayout.fileNum = headList.size();
    this->headLayout.dataFileMaxSize = dataFileMaxSize;
    this->headLayout.version = 0;
    memcpy(out + 0, &this->headLayout, sizeof(HeadLayout));
    int offset = 0;

    FILE *f = fp;

    if (fseek(f, 0, SEEK_SET))
        return -1;
    writeFile2(f, out, headSizeReal);

    fclose(fp);

    return 0;
}

int Archives::createFile(const char *name, char *fileptr, size_t size) {
    HashCode id = stringHash(name);
    if (this->headList.empty()) {
        ArchivesDataHead adh;

        int headSizeReal = sizeof(HeadLayout) + fileMaxNum * sizeof(ArchivesFileHeadPart);


        ArchivesFileHeadPart adhHead;
        adhHead.pos = headSizeReal;
        adhHead.id = id;
        adhHead.size = size;
        adh.head = adhHead;
        adh.name = name;
        this->headList.emplace_back(adh);
        this->headMap[id] = adh;
        headLayout.fileNum = headList.size();

        size_t fileSize = headSizeReal + size;
        char *out = (char *) malloc(fileSize);
        memset(out, 0, fileSize);
        this->headLayout.fileNum = 1;
        this->headLayout.dataFileMaxSize = dataFileMaxSize;
        this->headLayout.version = 0;
        memcpy(out + 0, &this->headLayout, sizeof(HeadLayout));
        memcpy(out + sizeof(HeadLayout), &adhHead, sizeof(ArchivesFileHeadPart));
        memcpy(out + headSizeReal, fileptr, size);


        //fclose(f);
        if (f != NULL) {
            fclose(f);
            f = NULL;
        }


        f = fopen(datapath, "wb");
        if (f == NULL)
            return -1;

        writeFile2(f, out, fileSize);

        free(out);
        fclose(f);
        f = fopen(datapath, "rb+");
        if (f == NULL)
            return -1;
    } else {
        auto &head = headList.front().head;
        int space = head.pos - (sizeof(HeadLayout) + fileMaxNum * sizeof(ArchivesFileHeadPart));
        int64_t spacePos = 0;
        if (space > size) {
            spacePos = (sizeof(HeadLayout) + fileMaxNum * sizeof(ArchivesFileHeadPart));
            ArchivesDataHead adh;
            adh.name = name;
            ArchivesFileHeadPart adhHead;
            adhHead.pos = spacePos;
            adhHead.size = size;
            adhHead.id = id;
            adh.head = adhHead;
            headList.push_front(adh);
            headMap[id] = adh;
            headLayout.fileNum = headList.size();


            size_t headSizeReal = (sizeof(HeadLayout) + fileMaxNum * sizeof(ArchivesFileHeadPart));
            char *out = (char *) malloc(headSizeReal);
            memset(out, 0, headSizeReal);
            this->headLayout.fileNum = headList.size();
            this->headLayout.dataFileMaxSize = dataFileMaxSize;
            this->headLayout.version = 0;
            memcpy(out + 0, &this->headLayout, sizeof(HeadLayout));
            memcpy(out + sizeof(HeadLayout), &adhHead, sizeof(ArchivesFileHeadPart));
            //memcpy(out+ headSizeReal, ptr, size);

            {
                if (fseek(f, 0, SEEK_SET))
                    return -1;
                writeFile2(f, out, headSizeReal);
            }


            {
                if (fseek(f, adhHead.pos, SEEK_SET))
                    return -1;
                writeFile2(f, fileptr, headSizeReal);
            }

        }
        if (spacePos == 0) {
            auto E = headList.begin();
            ArchivesFileHeadPart pre = E->head;
            E++;
            for (; E != headList.end(); pre = E->head, E++) {
                auto &head = E->head;
                space = head.pos - (pre.pos + pre.size);

                if (space > size) {
                    spacePos = pre.pos + pre.size;
                    ArchivesDataHead adh;
                    adh.name = name;
                    ArchivesFileHeadPart adhHead;
                    adhHead.pos = spacePos;
                    adhHead.size = size;
                    adhHead.id = id;
                    adh.head = adhHead;
                    headList.insert(E, adh);
                    headMap[id] = adh;
                    headLayout.fileNum = headList.size();


                    size_t headSizeReal = (sizeof(HeadLayout) + fileMaxNum * sizeof(ArchivesFileHeadPart));
                    char *out = (char *) malloc(headSizeReal);
                    memset(out, 0, headSizeReal);
                    this->headLayout.fileNum = headList.size();
                    this->headLayout.dataFileMaxSize = dataFileMaxSize;
                    this->headLayout.version = 0;
                    memcpy(out + 0, &this->headLayout, sizeof(HeadLayout));
                    int offset = 0;
                    for (auto &E: this->headList) {

                        memcpy(out + sizeof(HeadLayout) + offset, &E.head, sizeof(ArchivesFileHeadPart));
                        offset += sizeof(ArchivesFileHeadPart);
                    }
                    //memcpy(out+ headSizeReal, ptr, size);

                    {
                        if (fseek(f, 0, SEEK_SET))
                            return -1;
                        writeFile2(f, out, headSizeReal);
                    }


                    {
                        if (fseek(f, adhHead.pos, SEEK_SET))
                            return -1;
                        writeFile2(f, fileptr, size);
                    }
                    break;
                }
            }
            if (E == headList.end()) {
                spacePos = headList.back().head.pos + headList.back().head.size;
                ArchivesDataHead adh;
                adh.name = name;
                ArchivesFileHeadPart adhHead;
                adhHead.pos = spacePos;
                adhHead.size = size;
                adhHead.id = id;
                adh.head = adhHead;
                headList.insert(E, adh);
                headMap[id] = adh;
                headLayout.fileNum = headList.size();


                size_t headSizeReal = (sizeof(HeadLayout) + fileMaxNum * sizeof(ArchivesFileHeadPart));
                char *out = (char *) malloc(headSizeReal);
                memset(out, 0, headSizeReal);
                this->headLayout.fileNum = headList.size();
                this->headLayout.dataFileMaxSize = dataFileMaxSize;
                this->headLayout.version = 0;
                memcpy(out + 0, &this->headLayout, sizeof(HeadLayout));
                int offset = 0;
                for (auto &E: this->headList) {

                    memcpy(out + sizeof(HeadLayout) + offset, &E.head, sizeof(ArchivesFileHeadPart));
                    offset += sizeof(ArchivesFileHeadPart);
                }

                //memcpy(out+ headSizeReal, ptr, size);

                {
                    if (fseek(f, 0, SEEK_SET))
                        return -1;
                    writeFile2(f, out, headSizeReal);
                }


                {
                    if (fseek(f, adhHead.pos, SEEK_SET))
                        return -1;
                    writeFile2(f, fileptr, size);
                }
            }
        }
    }


    return 0;
}

std::vector<char> readFile(const char *str) {
    FILE *f = fopen(str, "rb");
    if (f == NULL)
        return std::vector<char>();
    if (fseek(f, 0, SEEK_END))
        return std::vector<char>();
    size_t size = ftell(f);
    if (fseek(f, 0, SEEK_SET))
        return std::vector<char>();
    if (size == -1L || size == 0)
        return std::vector<char>();
    std::vector<char> vecData_(size);
    {
        char *ptr = vecData_.data();
        int64_t allSize = size;
        int wlen = allSize;
        int flushBytes = 1024;
        while (true) {
            int ret = fread(ptr, allSize % flushBytes, 1, f);
            if (ret > 0)
                break;
        }
        wlen -= allSize % flushBytes;
        if (wlen > 0)
            while (true) {
                int ret = fread(ptr + allSize - wlen, flushBytes, 1, f);
                if (ret > 0) {
                    wlen -= flushBytes;
                    if (wlen == 0)
                        break;
                }
            }
    }
    fclose(f);
    return vecData_;
}

std::vector<char> readFile2(FILE *fp, size_t size) {
    if (fp == NULL)
        return std::vector<char>();
    if (size == -1L || size == 0)
        return std::vector<char>();
    std::vector<char> vecData_(size);
    {
        char *ptr = vecData_.data();
        int64_t allSize = size;
        int wlen = allSize;
        int flushBytes = 1024;
        while (true) {
            int ret = fread(ptr, allSize % flushBytes, 1, fp);
            if (ret > 0)
                break;
        }
        
        wlen -= allSize % flushBytes;
        if (wlen > 0)
            while (true) {
                int ret = fread(ptr + allSize - wlen, flushBytes, 1, fp);
                if (ret > 0) {
                    wlen -= flushBytes;
                    if (wlen == 0)
                        break;
                }
            }
    }
    return vecData_;
}

int writeFile(const char *str, const char *dataPtr, int size,
              const char *mode = "rb+") {//rb+ write wb+ cleanwrite ab+ append
    FILE *f = fopen(str, mode);
    if (f == NULL || size < 0)
        return -1;
    if (size > 0) {
        const char *ptr = dataPtr;
        int64_t allSize = size;
        int wlen = allSize;
        int flushBytes = 1024;
        while (true) {
            int ret = fwrite(ptr, allSize % flushBytes, 1, f);
            if (ret > 0)
                break;
        }
        wlen -= allSize % flushBytes;
        if (wlen > 0)
            while (true) {
                int ret = fwrite(ptr + allSize - wlen, flushBytes, 1, f);
                if (ret > 0) {
                    wlen -= flushBytes;
                    if (wlen == 0)
                        break;
                }
            }
    }
    fclose(f);
    return 0;
}

int writeFile2(FILE *f, const char *dataPtr, int size) {//rb+ write wb+ cleanwrite ab+ append
    if (f == NULL || size < 0)
        return -1;
    if (size > 0) {
        const char *ptr = dataPtr;
        int64_t allSize = size;
        int wlen = allSize;
        int flushBytes = 1024;
        while (true) {
            int ret = fwrite(ptr, allSize % flushBytes, 1, f);
            if (ret > 0)
                break;
        }
        wlen -= allSize % flushBytes;
        if (wlen > 0)
            while (true) {
                int ret = fwrite(ptr + allSize - wlen, flushBytes, 1, f);
                if (ret > 0) {
                    wlen -= flushBytes;
                    if (wlen == 0)
                        break;
                }
            }
    }
    return 0;
}

std::vector<char> Archives::readFile(const char *str) {

    auto head = headMap[stringHash(str)].head;
    int64_t pos = head.pos;
    if (fseek(f, pos, SEEK_SET))
        return std::vector<char>();

    return readFile2(f, head.size);
}

void Archives::deleteFile(const char *str) {

}

void Archives::modifyFile(const char *str) {

}

HashCode Archives::stringHash(const char *str) {
    return fnv64(str);
}

int Archives::openDataFile(const char *ful) {
    f = fopen(ful, "rb");
    if (f == NULL)
        return -1;
    this->datapath = ful;
    headParse();
    return 0;
}

int Archives::flushDataFile() {
    return 0;
}
int Archives::close()
{
    if(f != 0)
    {
        fclose(f);
    }
    return 0;
}
int Archives::headParse() {
    if (f == NULL)
        return -1;
    

    ArchivesFileHeadPart buffer[fileMaxNum];// 1G/4K align = 262144 maxFileNum
    size_t len = 0;

    if (fseek(f, 0, SEEK_SET))
        return -1;
    for (int i = 0;;) {
        if (++i > 1000)
            return -1;
        len = fread(&headLayout, sizeof(headLayout), 1, f);
        if (len > 0)
            break;
    }
    headLayout.version;

    this->dataFileMaxSize = headLayout.dataFileMaxSize;
    if (headLayout.fileNum < 0 || headLayout.fileNum > this->fileMaxNum)
        return -1;

    if (headLayout.fileNum > 0) {
        char *ptr = (char *) buffer;
        int64_t allSize = headLayout.fileNum * sizeof(ArchivesFileHeadPart);
        int wlen = allSize;
        int flushBytes = 1024;
        while (true) {
            int ret = fread(ptr, allSize % flushBytes, 1, f);
            if (ret > 0)
                break;
        }

        wlen -= allSize % flushBytes;
        if (wlen > 0)
            while (true) {
                int ret = fread(ptr + allSize - wlen, flushBytes, 1, f);
                if (ret > 0) {
                    wlen -= flushBytes;
                    if (wlen == 0)
                        break;
                }
            }

    }


    //this->fileMaxNum = dataFileMaxSize / align;

    for (int i = 0; i < headLayout.fileNum; i++) {
        ArchivesDataHead adh;
        adh.head = buffer[i];
        adh.name = NULL;
        this->headMap[buffer[i].id] = adh;
        this->headList.push_back(adh);
    }
    fseek(f, 0, SEEK_SET);
    std::cout << "loadFromPath ok" << std::endl;
    return 0;
}
