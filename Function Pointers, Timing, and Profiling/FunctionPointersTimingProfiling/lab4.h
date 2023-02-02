#define NUM_ENTRIES 40000000
#define NUM_QUEUES 2
#define DEFAULT_RESULT -1
/* Ideally this should be a power of 2. */
#define MIN_SIZE 4

/* Structs for Linked list style queue */
typedef struct LLNode{
	int data;
	struct LLNode *next;
}LLNode;

typedef struct Queue1{
	int length; /* Helper variable :) */
	LLNode *firstNode;
	LLNode *lastNode;
}Queue1;

/* Struct for array based queue */
typedef struct Queue2{
    int length;
    int curFront;
	int arrSize;
    int *entries;
}Queue2;

typedef struct Queue{
	void *Queue;
	void (*enqueue)(void*, int);
	int (*dequeue)(void*);
	int (*length)(void*);
}Queue;


typedef struct Stack1{
	int length;
	LLNode *firstNode;
	LLNode *lastNode;
}Stack1;

typedef struct Stack2{
	int length;
	int arrSize;
	int *entries;
}Stack2;

typedef struct Stack{
	void *Stack;
	void (*push)(void*, int);
	int (*pop)(void*);
	int (*length)(void*);
}Stack;


/* Func declarations */
Queue* newQueue1();
void enqueueQ1(void*, int);
int dequeueQ1(void*);
int lengthQ1(void*);

Queue* newQueue2();
void enqueueQ2(void*, int);
int dequeueQ2(void*);
int lengthQ2(void*);

Stack* newStack1();
void pushS1(void*, int);
int popS1(void*);
int lengthS1(void*);

Stack* newStack2();
void pushS2(void*, int);
int popS2(void*);
int lengthS2(void*);
