#include "./compiler.h"

#define OP_PUTC              1;
#define OP_PUTI              2;
#define OP_PLUS              3;
#define OP_MINUS             4;
#define OP_MULT              5;
#define OP_DIV               6;
#define OP_PUSH_INT          7;
#define OP_DROP              8;
#define OP_DUP               9;
#define OP_SWAP             10;
#define OP_ROT              11;
#define OP_OVER             12;
#define OP_JMP              13;
#define OP_JMP_IF           14;
#define OP_DEBUG_STACK      15;
#define OP_QUIT             16;
#define OP_EQU              17;
#define OP_LESS             18;
#define OP_GREATER          19;
#define OP_NOT              20;
#define OP_OR               21;
#define OP_AND              22;
#define OP_READK            23;
#define OP_AT               24;
#define OP_NQDEBUG_STACK    25;
#define OP_PRINT            26;
#define OP_TMP_PUSH_INT     27;
#define OP_TMP_DROP         28;
#define OP_NQDEBUG_TMP_BUFF 29;
#define OP_TMP_AT           30;
#define OP_ARR_PUSH_INT     31;
#define OP_ARR_DROP         32;
#define OP_ARR_AT           33;
#define OP_NQDEBUG_TMP_ARR  34;
#define OP_OPEN             35;
#define OP_CLOSE            36;
#define OP_WRITE            37;
#define OP_READ             38;
#define OP_PUT              39;
#define OP_RAND             40;
#define OP_MOD              41;
#define OP_NULL             42;
#define OP_COUNT            43;

#define PROGRAM_CAP 1024
char program[PROGRAM_CAP] = {0};
size_t program_sz;

#define TOKENS_CAP 1024
void translate_line(String_View line)
{
    String_View tokens[1024];
    size_t tokens_sz = 0;

    line = sv_trim(sv_chop_by_delim(&line, ';'));
    String_View inst;
    while (line.count > 0) {
        inst = sv_trim(sv_chop_by_delim(&line, ' '));
        if (inst.count > 0) {
            tokens[tokens_sz++] = inst;
        }
    }

    for (size_t i = 0; i < tokens_sz; ++i) {
        if (sv_eq(tokens[i], sv_from_cstr("pushi")))
        {
            program[program_sz++] = OP_PUSH_INT;
            program[program_sz++] = (char) sv_to_int(tokens[++i]);
        }
        else if (sv_eq(tokens[i], sv_from_cstr("plus")))
        {
            program[program_sz++] = OP_PLUS;
        }
        else if (sv_eq(tokens[i], sv_from_cstr("minus")))
        {
            program[program_sz++] = OP_MINUS;
        }
        else if (sv_eq(tokens[i], sv_from_cstr("mult")))
        {
            program[program_sz++] = OP_MULT;
        }
        else if (sv_eq(tokens[i], sv_from_cstr("div")))
        {
            program[program_sz++] = OP_DIV;
        }
        else if (sv_eq(tokens[i], sv_from_cstr("mod")))
        {
            program[program_sz++] = OP_MOD;
        }
        else if (sv_eq(tokens[i], sv_from_cstr("rand")))
        {
            program[program_sz++] = OP_RAND;
        }
        else if (sv_eq(tokens[i], sv_from_cstr("puti")))
        {
            program[program_sz++] = OP_PUTI;
        }
        else
        {
            fprintf(stderr, "ERROR: Unknown instruction: "SV_Fmt"\n",
                    (int) tokens[i].count, tokens[i].data);
            exit(1);
        }
    }
}

void compile_program(const char* fpath)
{
    FILE* file = fopen(fpath, "rb");
    char* buffer = 0;
    size_t length;

    if (file == NULL)
    {
        fprintf(stderr, "ERROR: Could not open `%s`: %s\n",
                fpath, strerror(errno));
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    buffer = malloc(length);

    if (buffer == NULL)
    {
        fprintf(stderr, "ERROR: Could not allocate memory for file: %s",
                strerror(errno));
        exit(1);
    }
    fread(buffer, 1, length, file);
    fclose(file);
    String_View source = sv_from_cstr(buffer);

    while (source.count > 0) {
        String_View line = sv_trim(sv_chop_by_delim(&source, '\n'));
        if (line.count > 0) {
            translate_line(line);
        }
    }

    FILE* output = fopen("output.stm", "wb");
    fwrite(program, sizeof(program[0]), sizeof(program[0]) * program_sz,
           output);
    fclose(output);
}
