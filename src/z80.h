
enum STOP_REASON {
    STOP_REASON_NONE,
    STOP_REASON_STOP,
    STOP_REASON_HALT,
    STOP_REASON_INTERRUPT_RET,
    STOP_REASON_ERROR,
};

enum GB_FLAGS {
    GB_FLAGS_Z = 0x80,
    GB_FLAGS_N = 0x40,
    GB_FLAGS_H = 0x20,
    GB_FLAGS_C = 0x10,
};

struct Z80State {
    unsigned char a;
    unsigned char f;
    unsigned char b;
    unsigned char c;
    unsigned char d;
    unsigned char e;
    unsigned char h;
    unsigned char l;
    unsigned short sp;
    unsigned short pc;
    unsigned char stopReason;
    unsigned char unused0;
    unsigned short unused1;
};

extern int runZ80CPU(struct Z80State* state, void** memoryMap, int cyclesToRun);

#define GB_MEMORY_MAP_SIZE  0x10000
extern struct Z80State gZ80;
extern unsigned char gbMemory[GB_MEMORY_MAP_SIZE];

extern void zeroMemory(unsigned char* memory, int size);
extern void initializeZ80(struct Z80State* state);