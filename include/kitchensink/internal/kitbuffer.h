#ifndef KITBUFFER_H
#define KITBUFFER_H

#include "kitchensink/kitconfig.h"

typedef enum Kit_BufferState {
    KIT_BUFFER_EMPTY,
    KIT_BUFFER_PARTIALLY_FILLED,
    KIT_BUFFER_FULL,
} Kit_BufferState;

typedef struct Kit_Buffer Kit_Buffer;

typedef void (*Kit_BufferFreeCallback)(void*);

struct Kit_Buffer {
    unsigned int read_p;
    unsigned int write_p;
    unsigned int size;
    Kit_BufferFreeCallback free_cb;
    void **data;
};

KIT_LOCAL Kit_Buffer* Kit_CreateBuffer(unsigned int size, Kit_BufferFreeCallback free_cb);
KIT_LOCAL void Kit_DestroyBuffer(Kit_Buffer *buffer);

KIT_LOCAL void Kit_ClearBuffer(Kit_Buffer *buffer);
KIT_LOCAL void* Kit_ReadBuffer(Kit_Buffer *buffer);
KIT_LOCAL void* Kit_PeekBuffer(const Kit_Buffer *buffer);
KIT_LOCAL void Kit_AdvanceBuffer(Kit_Buffer *buffer);
KIT_LOCAL int Kit_WriteBuffer(Kit_Buffer *buffer, void *ptr);
KIT_LOCAL int Kit_IsBufferFull(const Kit_Buffer *buffer);
KIT_LOCAL int Kit_IsBufferEmpty(const Kit_Buffer *buffer);
KIT_LOCAL Kit_BufferState Kit_GetBufferState(const Kit_Buffer *buffer);

#endif // KITBUFFER_H
