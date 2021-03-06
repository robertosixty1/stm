#ifndef OPERATORS_HPP_
#define OPERATORS_HPP_

typedef enum {
    OP_PUTC,
    OP_PUTI,
    OP_PLUS,
    OP_MINUS,
    OP_MULT,
    OP_DIV,
    OP_PUSH_INT,
    OP_DROP,
    OP_DUP,
    OP_SWAP,
    OP_ROT,
    OP_OVER,
    OP_JMP,
    OP_JMP_IF,
    OP_DEBUG_STACK,
    OP_QUIT,
    OP_EQU,
    OP_LESS,
    OP_GREATER,
    OP_NOT,
    OP_OR,
    OP_AND,
    OP_READK,
    OP_AT,
    OP_NQDEBUG_STACK,
    OP_PRINT,
    OP_TMP_PUSH_INT,
    OP_TMP_DROP,
    OP_NQDEBUG_TMP_BUFF,
    OP_TMP_AT,
    OP_ARR_PUSH_INT,
    OP_ARR_DROP,
    OP_ARR_AT,
    OP_NQDEBUG_TMP_ARR,
    OP_OPEN,
    OP_CLOSE,
    OP_WRITE,
    OP_READ,
    OP_PUT,
    OP_RAND,
    OP_MOD,
    OP_NULL,
    OP_COUNT
} OpType;

typedef struct {
    OpType type;
    int content = 0;
} Op;

#endif // OPERATORS_HPP_
