#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct pageFrameT {
    unsigned char isValid: 1;
    unsigned char referenced: 1;
    uint8_t counter;
    size_t pageIndex;
};

size_t pageFrameCount;
struct pageFrameT *pageFrames;

void printTable() {
    printf("Page\tCounter\tR\n");

    for (size_t i = 0; i < pageFrameCount; i++) {
        struct pageFrameT *framePtr = pageFrames + i;

        if (framePtr->isValid) {
            printf("%lu\t%hu\t%hu\n", framePtr->pageIndex, framePtr->counter, framePtr->referenced);
        }
    }
}

void resetPageFrame(size_t index) {
    struct pageFrameT *framePtr = pageFrames + index;
    framePtr->isValid = 0;
}

void initializePageTable() {
    pageFrames = (struct pageFrameT *) calloc(sizeof(struct pageFrameT), pageFrameCount);

    for (size_t i = 0; i < pageFrameCount; i++) {
        resetPageFrame(i);
    }
}

void free_page_table() {
    free(pageFrames);
}

int isInPageTable(size_t pageIndex, size_t *frameIndex) {
    for (size_t i = 0; i < pageFrameCount; i++) {
        struct pageFrameT *framePtr = pageFrames + i;

        if (framePtr->isValid && framePtr->pageIndex == pageIndex) {
            *frameIndex = i;
            return 1;
        }
    }

    return 0;
}

int existsEmptyFrame(size_t *emptyFrameIndex) {
    for (size_t i = 0; i < pageFrameCount; i++) {
        if (!pageFrames[i].isValid) {
            *emptyFrameIndex = i;
            return 1;
        }
    }

    return 0;
}

void loadPageToFrame(size_t pageIndex, size_t frameIndex) {
    struct pageFrameT *framePtr = pageFrames + frameIndex;

    framePtr->isValid = 1;
    framePtr->pageIndex = pageIndex;
    framePtr->referenced = 0;
    framePtr->counter = 0;
}

size_t unloadNotFrequentlyUsedFrame() {
    uint8_t minCounter = pageFrames[0].counter;
    size_t minCounterIndex = 0;

    for (size_t i = 1; i < pageFrameCount; i++) {
        struct pageFrameT *framePtr = pageFrames + i;

        if (framePtr->isValid && framePtr->counter < minCounter) {
            minCounter = framePtr->counter;
            minCounterIndex = i;
        }
    }

    resetPageFrame(minCounterIndex);

    return minCounterIndex;
}

void referencePageFrame(size_t frameIndex) {
    pageFrames[frameIndex].referenced = 1;
}

void access_page(size_t pageIndex, size_t *hitsPtr, size_t *missesPtr) {
    size_t frameIndex;

    if (isInPageTable(pageIndex, &frameIndex)) {
        (*hitsPtr)++;
    } else {
        (*missesPtr)++;

        if (!existsEmptyFrame(&frameIndex)) {
            frameIndex = unloadNotFrequentlyUsedFrame();
        }

        loadPageToFrame(pageIndex, frameIndex);
    }

    referencePageFrame(frameIndex);
}

void age() {
    for (size_t i = 0; i < pageFrameCount; i++) {
        struct pageFrameT *framePtr = pageFrames + i;

        if (framePtr->isValid) {
            framePtr->counter >>= 1;
            size_t shiftAmount = sizeof(framePtr->counter) * (8 - 1);
            framePtr->counter += framePtr->referenced * shiftAmount;
            framePtr->referenced = 0;
        }
    }
}

int main(int argc, char **argv) {
    sscanf(argv[1], "%flu", &pageFrameCount);
    initializePageTable();

    FILE *file = fopen("input.txt", "r");

    if (file == NULL) {
        printf("File '%s' does not exist.\n", "input.txt");
        free_page_table();
        return -1;
    }

    size_t pageIndex, hits = 0, misses = 0;

    while (fscanf(file, "%lu", &pageIndex) != EOF) {
        access_page(pageIndex, &hits, &misses);
        age();
    }

    printf("%lu hits/%lu misses. Hit ratio is %f.\n", hits, misses, (float) hits / (float) (hits + misses));
    free_page_table();
    fclose(file);

    return 0;
}