#ifndef DISPLAYBUFFER_H
#define DISPLAYBUFFER_H

#define MemorySize 162*16
struct StarDisplayBuffer{
    StarDisplayBuffer();
    virtual ~StarDisplayBuffer();
    int* drawingMemory[MemorySize];
    int* displayMemory[MemorySize];
};
#endif