// WARNING: this file is auto-generated by the C2 compiler.
// Any changes you make might be lost!

#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include <stdlib.h>
#include "json_parser.h"

#define json_MAX_TEXT 256
#define json_TEXT_INIT_SIZE 256
#define json_NODE_INIT_SIZE 64

typedef enum {
  json_TokenKind_Kw_true,
  json_TokenKind_Kw_false,
  json_TokenKind_Kw_null,
  json_TokenKind_L_brace,
  json_TokenKind_R_brace,
  json_TokenKind_L_sbracket,
  json_TokenKind_R_sbracket,
  json_TokenKind_Colon,
  json_TokenKind_Comma,
  json_TokenKind_Text,
  json_TokenKind_Eof,
  json_TokenKind_Error,
} __attribute__((packed)) json_TokenKind;

typedef struct {
  uint32_t line;
  uint32_t col;
} json_Location;

typedef struct {
  char* data;
  uint32_t cur;
  uint32_t cap;
} json_TextBuffer;

typedef enum {
  json_NodeKind_Object = 0,
  json_NodeKind_Value = 1,
  json_NodeKind_Array = 2,
} __attribute__((packed)) json_NodeKind;

typedef struct __attribute__((packed)) {
  uint32_t next_kind;
  uint32_t name_idx;
  union {
    uint32_t child_idx;
    uint32_t value_idx;
  };
} json_Node;

typedef struct {
  json_Node* data;
  uint32_t cur;
  uint32_t cap;
} json_NodeBuffer;


struct json_Data_ {
  json_TextBuffer names;
  json_TextBuffer values;
  json_NodeBuffer nodes;
};

typedef struct {
  const char* dataStart;
  const char* current;
  json_Location loc;
  char msg[json_MAX_TEXT];
} json_Tokenizer;


typedef struct {
  json_Location loc;
  json_TokenKind kind;
  const char* text;
} json_Token;


typedef struct {
  json_Tokenizer tokenizer;
  json_Token token;
  json_Location prev;
  json_Data* data;
  char inArray;
  uint32_t name_cache[16];
  jmp_buf jmp_err;
  char* msg;
} json_JParser;


static int json_JParser_parse(json_JParser* p, const char* text, char* diagMsg, json_Data* data);
static json_Location json_JParser_consumeToken(json_JParser* p);
static void json_JParser_parseFile(json_JParser* p);
static const char* json_JParser_diagLoc(const json_JParser* p);
static void json_JParser_expect(json_JParser* p, json_TokenKind k);
static void json_JParser_expectAndConsume(json_JParser* p, json_TokenKind k);
static void json_JParser_parseArray(json_JParser* p, uint32_t parent_idx);
static uint32_t json_JParser_addName(json_JParser* p, uint32_t entry_idx, const char* name);
static void json_JParser_parseObject(json_JParser* p, uint32_t parent_idx);
static uint32_t json_JParser_parseValue(json_JParser* p);
static void json_Tokenizer_init(json_Tokenizer* t, const char* text);
static void json_Tokenizer_lex(json_Tokenizer* t, json_Token* result);
static void json_Tokenizer_parseText(json_Tokenizer* t, json_Token* result);
static void json_Tokenizer_parseNumber(json_Tokenizer* t, json_Token* result);
static void json_Tokenizer_parseKeyword(json_Tokenizer* t, json_Token* result);
static void json_Tokenizer_advance(json_Tokenizer* t, uint32_t amount);
static const char* json_getTokenName(json_TokenKind k);
static void json_Token_init(json_Token* t);
static json_Location json_Token_getLoc(const json_Token* t);
static void json_Token_clear(json_Token* t);
static void json_Token_setData(json_Token* t, const char* d);
static const char* json_Token_getName(const json_Token* t);
static json_TokenKind json_Token_getKind(const json_Token* t);
static char json_Token_is(const json_Token* t, json_TokenKind kind);
static char json_Token_isNot(const json_Token* t, json_TokenKind kind);
static const char* json_Token_getText(const json_Token* t);
static void json_Token_setKind(json_Token* t, json_TokenKind kind);
static void json_Token_setLocation(json_Token* t, json_Location loc);
static void json_Location_set(json_Location* loc, uint32_t l, uint32_t c);
static const char* json_Location_str(const json_Location* loc);
static void json_TextBuffer_init(json_TextBuffer* b, uint32_t size);
static void json_TextBuffer_destroy(json_TextBuffer* b);
static void json_TextBuffer_reset(json_TextBuffer* b);
static void json_TextBuffer_resize(json_TextBuffer* b, uint32_t cap2);
static uint32_t json_TextBuffer_add(json_TextBuffer* b, const char* text, uint32_t len);
static void json_TextBuffer_dump(const json_TextBuffer* b, const char* text);
static const char* json_kind2str(json_NodeKind k);
static void json_NodeBuffer_init(json_NodeBuffer* b, uint32_t size);
static void json_NodeBuffer_destroy(json_NodeBuffer* b);
static void json_NodeBuffer_reset(json_NodeBuffer* b);
static uint32_t json_NodeBuffer_getSize(const json_NodeBuffer* b);
static void json_NodeBuffer_resize(json_NodeBuffer* b, uint32_t cap2);
static uint32_t json_NodeBuffer_add(json_NodeBuffer* b, json_NodeKind kind, uint32_t name_idx, uint32_t value_idx);
static void json_NodeBuffer_dump(const json_NodeBuffer* b);
static json_Data* json_Data_create();
static void json_Data_destroy(json_Data* d);
static void json_Data_reset(json_Data* d);
static uint32_t json_Data_addName(json_Data* d, const char* name, uint32_t len);
static uint32_t json_Data_addValue(json_Data* d, const char* value, uint32_t len);
static uint32_t json_Data_addNode(json_Data* d, json_NodeKind kind, uint32_t name_idx, uint32_t value_idx);
static void json_Data_setChild(json_Data* d, uint32_t parent_idx, uint32_t child_idx);
static void json_Data_setNext(json_Data* d, uint32_t prev_idx, uint32_t next_idx);
static void json_Data_dump(const json_Data* d, char verbose);
static void json_Data_dumpNode(const json_Data* d, uint32_t idx, uint32_t indent_);
static uint32_t json_Parser_find_node(const json_Parser* p, const char* key);
static uint32_t json_Parser_find_child(const json_Parser* p, uint32_t parent_idx, const char* name);
static uint32_t json_Iter_find_child(const json_Iter* i, uint32_t idx, const char* name);
static char json_Iter_check_schema_priv(const json_Iter* i, const char** schema);
static const char* json_indent(uint32_t i);

void json_Parser_init(json_Parser* p) {
  p->data = json_Data_create();
  p->message[0] = 0;
}

void json_Parser_destroy(json_Parser* p) {
  json_Data_destroy(p->data);
  p->data = NULL;
}

int json_Parser_parse(json_Parser* p, const char* text) {
  json_Data_reset(p->data);
  p->message[0] = 0;
  json_JParser parser;
  return json_JParser_parse(&parser, text, p->message, p->data);
}

void json_Parser_report(const json_Parser* p) {
  printf("JSON: %u nodes, names: %u bytes, values: %u bytes\n", p->data->nodes.cur, p->data->names.cur, p->data->values.cur);
}

void json_Parser_dump(const json_Parser* p, char verbose) {
  json_Data_dump(p->data, verbose);
}

const char* json_Parser_getDiag(json_Parser* p) {
  return p->message;
}

static int json_JParser_parse(json_JParser* p, const char* text, char* diagMsg, json_Data* data) {
  json_Tokenizer_init(&p->tokenizer, text);
  json_Token_init(&p->token);
  json_Location_set(&p->prev, 0, 0);
  p->msg = diagMsg;
  p->data = data;
  p->inArray = 0;
  memset(p->name_cache, 0, 64);
  int32_t res = setjmp(p->jmp_err);
  if ((res == 0))
  {
    json_JParser_consumeToken(p);
    json_JParser_parseFile(p);
    return 1;
  }
  return 0;
}

static json_Location json_JParser_consumeToken(json_JParser* p) {
  p->prev = json_Token_getLoc(&p->token);
  json_Tokenizer_lex(&p->tokenizer, &p->token);
  if (json_Token_is(&p->token, json_TokenKind_Error))
  {
    strcpy(p->msg, json_Token_getText(&p->token));
    longjmp(p->jmp_err, 1);
  }
  return p->prev;
}

static void json_JParser_parseFile(json_JParser* p) {
  switch (json_Token_getKind(&p->token)) {
    case json_TokenKind_L_brace: {
      uint32_t node_idx = json_Data_addNode(p->data, json_NodeKind_Object, 0, 0);
      json_JParser_parseObject(p, node_idx);
      break;
    }
    case json_TokenKind_L_sbracket: {
      uint32_t node_idx = json_Data_addNode(p->data, json_NodeKind_Array, 0, 0);
      json_JParser_parseArray(p, node_idx);
      break;
    }
    default:
      sprintf(p->msg, "unexpected '%s' %s", json_getTokenName(json_Token_getKind(&p->token)), json_JParser_diagLoc(p));
      longjmp(p->jmp_err, 1);
      break;
  }
  json_JParser_expect(p, json_TokenKind_Eof);
}

static const char* json_JParser_diagLoc(const json_JParser* p) {
  json_Location loc = json_Token_getLoc(&p->token);
  return json_Location_str(&loc);
}

static void json_JParser_expect(json_JParser* p, json_TokenKind k) {
  if (json_Token_isNot(&p->token, k))
  {
    sprintf(p->msg, "expected '%s' %s", json_getTokenName(k), json_JParser_diagLoc(p));
    longjmp(p->jmp_err, 1);
  }
}

static void json_JParser_expectAndConsume(json_JParser* p, json_TokenKind k) {
  json_JParser_expect(p, k);
  json_JParser_consumeToken(p);
}

static void json_JParser_parseArray(json_JParser* p, uint32_t parent_idx) {
  json_JParser_expectAndConsume(p, json_TokenKind_L_sbracket);
  uint32_t prev_idx = 0;
  p->inArray = 1;
  while (1) {
    uint32_t node_idx = 0;
    switch (json_Token_getKind(&p->token)) {
      case json_TokenKind_Kw_true: __attribute__((fallthrough));
      case json_TokenKind_Kw_false: __attribute__((fallthrough));
      case json_TokenKind_Kw_null: __attribute__((fallthrough));
      case json_TokenKind_Text: {
        uint32_t value_idx = json_JParser_parseValue(p);
        node_idx = json_Data_addNode(p->data, json_NodeKind_Value, 0, value_idx);
        break;
      }
      case json_TokenKind_L_brace:
        node_idx = json_Data_addNode(p->data, json_NodeKind_Object, 0, 0);
        json_JParser_parseObject(p, node_idx);
        break;
      case json_TokenKind_L_sbracket:
        node_idx = json_Data_addNode(p->data, json_NodeKind_Array, 0, 0);
        json_JParser_parseArray(p, node_idx);
        break;
      case json_TokenKind_R_sbracket:
        break;
      case json_TokenKind_R_brace: __attribute__((fallthrough));
      case json_TokenKind_Colon: __attribute__((fallthrough));
      case json_TokenKind_Comma: __attribute__((fallthrough));
      case json_TokenKind_Eof: __attribute__((fallthrough));
      case json_TokenKind_Error:
        sprintf(p->msg, "expected '{', '[' or text %s", json_JParser_diagLoc(p));
        longjmp(p->jmp_err, 1);
        break;
    }
    if (prev_idx)
    {
      json_Data_setNext(p->data, prev_idx, node_idx);
    }
    else
    {
      if (parent_idx)
      {
        json_Data_setChild(p->data, parent_idx, node_idx);
      }
    }
    prev_idx = node_idx;
    if (json_Token_isNot(&p->token, json_TokenKind_Comma)) break;
    json_Location commaLoc = json_JParser_consumeToken(p);
    if (json_Token_is(&p->token, json_TokenKind_R_sbracket)) {
        sprintf(p->msg, "superfluous comma %s", json_Location_str(&commaLoc));
        longjmp(p->jmp_err, 1);
    }
  }
  json_JParser_expectAndConsume(p, json_TokenKind_R_sbracket);
  p->inArray = 0;
}

static uint32_t json_JParser_addName(json_JParser* p, uint32_t entry_idx, const char* name) {
  if ((!p->inArray || (entry_idx >= 16)))
  {
    return json_Data_addName(p->data, name, (uint32_t)(strlen(name)));
  }
  uint32_t name_idx = 0;
  uint32_t cache_idx = p->name_cache[entry_idx];
  if ((cache_idx != 0))
  {
    const char* cached = &p->data->names.data[cache_idx];
    if ((strcmp(cached, name) == 0)) return cache_idx;
  }
  name_idx = json_Data_addName(p->data, name, (uint32_t)(strlen(name)));
  p->name_cache[entry_idx] = name_idx;
  return name_idx;
}

static void json_JParser_parseObject(json_JParser* p, uint32_t parent_idx) {
  json_JParser_expectAndConsume(p, json_TokenKind_L_brace);
  uint32_t prev_idx = 0;
  uint32_t entry_idx = 0;
  while (1) {
    if ((json_Token_getKind(&p->token) == json_TokenKind_R_brace)) break;
    json_JParser_expect(p, json_TokenKind_Text);
    char name[json_MAX_TEXT];
    strcpy(name, json_Token_getText(&p->token));
    json_JParser_consumeToken(p);
    uint32_t name_idx = json_JParser_addName(p, entry_idx, name);
    json_JParser_expectAndConsume(p, json_TokenKind_Colon);
    uint32_t node_idx = 0;
    switch (json_Token_getKind(&p->token)) {
      case json_TokenKind_Kw_true: __attribute__((fallthrough));
      case json_TokenKind_Kw_false: __attribute__((fallthrough));
      case json_TokenKind_Kw_null: __attribute__((fallthrough));
      case json_TokenKind_Text: {
        uint32_t value_idx = json_JParser_parseValue(p);
        node_idx = json_Data_addNode(p->data, json_NodeKind_Value, name_idx, value_idx);
        break;
      }
      case json_TokenKind_L_brace:
        node_idx = json_Data_addNode(p->data, json_NodeKind_Object, name_idx, 0);
        json_JParser_parseObject(p, node_idx);
        break;
      case json_TokenKind_L_sbracket:
        node_idx = json_Data_addNode(p->data, json_NodeKind_Array, name_idx, 0);
        json_JParser_parseArray(p, node_idx);
        break;
      case json_TokenKind_R_brace: __attribute__((fallthrough));
      case json_TokenKind_R_sbracket: __attribute__((fallthrough));
      case json_TokenKind_Colon: __attribute__((fallthrough));
      case json_TokenKind_Comma: __attribute__((fallthrough));
      case json_TokenKind_Eof: __attribute__((fallthrough));
      case json_TokenKind_Error:
        sprintf(p->msg, "expected '{', '[' or text %s", json_JParser_diagLoc(p));
        longjmp(p->jmp_err, 1);
        break;
    }
    if (prev_idx)
    {
      json_Data_setNext(p->data, prev_idx, node_idx);
    }
    else
    {
      if (parent_idx)
      {
        json_Data_setChild(p->data, parent_idx, node_idx);
      }
    }
    prev_idx = node_idx;
    if (json_Token_isNot(&p->token, json_TokenKind_Comma)) break;
    json_Location commaLoc = json_JParser_consumeToken(p);
    if (json_Token_is(&p->token, json_TokenKind_R_brace))
    {
      sprintf(p->msg, "superfluous comma %s", json_Location_str(&commaLoc));
      longjmp(p->jmp_err, 1);
    }
    entry_idx++;
  }
  json_JParser_expectAndConsume(p, json_TokenKind_R_brace);
}

static uint32_t json_JParser_parseValue(json_JParser* p) {
  char value[json_MAX_TEXT];
  switch (json_Token_getKind(&p->token)) {
    case json_TokenKind_Kw_true:
      value[0] = '1';
      value[1] = 0;
      break;
    case json_TokenKind_Kw_false:
      value[0] = '0';
      value[1] = 0;
      break;
    case json_TokenKind_Kw_null:
      value[0] = 0;
      break;
    case json_TokenKind_Text:
      strcpy(value, json_Token_getText(&p->token));
      break;
    default:
      sprintf(p->msg, "syntax error %s", json_JParser_diagLoc(p));
      longjmp(p->jmp_err, 1);
      break;
  }
  json_JParser_consumeToken(p);
  return json_Data_addValue(p->data, value, (uint32_t)(strlen(value)));
}

static void json_Tokenizer_init(json_Tokenizer* t, const char* text) {
  t->dataStart = text;
  t->current = text;
  json_Location_set(&t->loc, 1, 1);
}

static void json_Tokenizer_lex(json_Tokenizer* t, json_Token* result) {
  json_Token_clear(result);
  while (1) {
    switch (t->current[0]) {
      case 0:
        json_Token_setLocation(result, t->loc);
        json_Token_setKind(result, json_TokenKind_Eof);
        return;
      case ' ':
        __attribute__((fallthrough));
      case '\t':
        json_Tokenizer_advance(t, 1);
        break;
      case '\r':
        t->current++;
        if ((t->current[0] != '\n'))
        {
          sprintf(t->msg, "unexpected char '%c' %s", t->current[0], json_Location_str(&t->loc));
          json_Token_setKind(result, json_TokenKind_Error);
          json_Token_setData(result, t->msg);
          return;
        }
        __attribute__((fallthrough));
      case '\n':
        t->current++;
        t->loc.line++;
        t->loc.col = 1;
        break;
      case '[':
        json_Token_setLocation(result, t->loc);
        json_Token_setKind(result, json_TokenKind_L_sbracket);
        json_Tokenizer_advance(t, 1);
        return;
      case ']':
        json_Token_setLocation(result, t->loc);
        json_Token_setKind(result, json_TokenKind_R_sbracket);
        json_Tokenizer_advance(t, 1);
        return;
      case '{':
        json_Token_setLocation(result, t->loc);
        json_Token_setKind(result, json_TokenKind_L_brace);
        json_Tokenizer_advance(t, 1);
        return;
      case '}':
        json_Token_setLocation(result, t->loc);
        json_Token_setKind(result, json_TokenKind_R_brace);
        json_Tokenizer_advance(t, 1);
        return;
      case ':':
        json_Token_setLocation(result, t->loc);
        json_Token_setKind(result, json_TokenKind_Colon);
        json_Tokenizer_advance(t, 1);
        return;
      case ',':
        json_Token_setLocation(result, t->loc);
        json_Token_setKind(result, json_TokenKind_Comma);
        json_Tokenizer_advance(t, 1);
        return;
      case '"':
        json_Tokenizer_parseText(t, result);
        return;
      case '-': __attribute__((fallthrough));
      case '0': __attribute__((fallthrough));
      case '1': __attribute__((fallthrough));
      case '2': __attribute__((fallthrough));
      case '3': __attribute__((fallthrough));
      case '4': __attribute__((fallthrough));
      case '5': __attribute__((fallthrough));
      case '6': __attribute__((fallthrough));
      case '7': __attribute__((fallthrough));
      case '8': __attribute__((fallthrough));
      case '9':
        json_Tokenizer_parseNumber(t, result);
        return;
      case 'f': __attribute__((fallthrough));
      case 'n': __attribute__((fallthrough));
      case 't':
        json_Tokenizer_parseKeyword(t, result);
        return;
      default:
        sprintf(t->msg, "unexpected char '%c' %s", t->current[0], json_Location_str(&t->loc));
        json_Token_setKind(result, json_TokenKind_Error);
        json_Token_setData(result, t->msg);
        return;
    }
  }
}

static void json_Tokenizer_parseText(json_Tokenizer* t, json_Token* result) {
  t->current++;
  const char* start = t->current;
  while ((t->current[0] && (t->current[0] != '"'))) t->current++;
  uint32_t len = (uint32_t)((t->current - start));
  if (len >= json_MAX_TEXT) {
        sprintf(t->msg, "text too long %u (max %u) %s", len, json_MAX_TEXT, json_Location_str(&t->loc));
        json_Token_setKind(result, json_TokenKind_Error);
        json_Token_setData(result, t->msg);
        return;
  }
  memcpy(t->msg, start, len);
  t->msg[len] = 0;
  json_Token_setKind(result, json_TokenKind_Text);
  json_Token_setData(result, t->msg);
  json_Token_setLocation(result, t->loc);
  if ((t->current[0] == '"'))
  {
    t->current++;
    len++;
  }
  t->loc.col += (len + 1);
}

static void json_Tokenizer_parseNumber(json_Tokenizer* t, json_Token* result) {
  const char* start = t->current;
  if (t->current[0] == '-') t->current++;
  while (((t->current[0] >= '0') && (t->current[0] <= '9'))) t->current++;
  if (t->current[0] == '.') {
    t->current++;
    while (((t->current[0] >= '0') && (t->current[0] <= '9'))) t->current++;
  }
  uint32_t len = (uint32_t)((t->current - start));
  memcpy(t->msg, start, len);
  t->msg[len] = 0;
  json_Token_setKind(result, json_TokenKind_Text);
  json_Token_setData(result, t->msg);
  json_Token_setLocation(result, t->loc);
  t->loc.col += len;
}

static void json_Tokenizer_parseKeyword(json_Tokenizer* t, json_Token* result) {
  if ((strncmp(t->current, "true", 4) == 0))
  {
    json_Token_setLocation(result, t->loc);
    json_Token_setKind(result, json_TokenKind_Kw_true);
    json_Tokenizer_advance(t, 4);
  }
  else if ((strncmp(t->current, "false", 5) == 0))
{
  json_Token_setLocation(result, t->loc);
  json_Token_setKind(result, json_TokenKind_Kw_false);
  json_Tokenizer_advance(t, 5);
}
else if ((strncmp(t->current, "null", 4) == 0))
{
  json_Token_setLocation(result, t->loc);
  json_Token_setKind(result, json_TokenKind_Kw_false);
  json_Tokenizer_advance(t, 4);
}
else
{
  sprintf(t->msg, "unexpected char '%c' %s", t->current[0], json_Location_str(&t->loc));
  json_Token_setKind(result, json_TokenKind_Error);
  json_Token_setData(result, t->msg);
}
}

static void json_Tokenizer_advance(json_Tokenizer* t, uint32_t amount) {
  t->loc.col += amount;
  t->current += amount;
}

static const char* json_getTokenName(json_TokenKind k) {
  switch (k) {
    case json_TokenKind_Kw_true: return "true";
    case json_TokenKind_Kw_false: return "false";
    case json_TokenKind_Kw_null: return "null";
    case json_TokenKind_L_brace: return "{";
    case json_TokenKind_R_brace: return "}";
    case json_TokenKind_L_sbracket: return "[";
    case json_TokenKind_R_sbracket: return "]";
    case json_TokenKind_Colon: return ":";
    case json_TokenKind_Comma: return ",";
    case json_TokenKind_Text: return "text";
    case json_TokenKind_Eof: return "eof";
    case json_TokenKind_Error: return "error";
  }
  return "?";
}

static void json_Token_init(json_Token* t) {
  json_Location_set(&t->loc, 0, 0);
  t->kind = json_TokenKind_Eof;
  t->text = NULL;
}

static json_Location json_Token_getLoc(const json_Token* t) {
  return t->loc;
}

static void json_Token_clear(json_Token* t) {
  t->text = NULL;
}

static void json_Token_setData(json_Token* t, const char* d) {
  t->text = d;
}

static const char* json_Token_getName(const json_Token* t) {
  return json_getTokenName(t->kind);
}

static json_TokenKind json_Token_getKind(const json_Token* t) {
  return t->kind;
}

static char json_Token_is(const json_Token* t, json_TokenKind kind) {
  return (t->kind == kind);
}

static char json_Token_isNot(const json_Token* t, json_TokenKind kind) {
  return (t->kind != kind);
}

static const char* json_Token_getText(const json_Token* t) {
  return t->text;
}

static void json_Token_setKind(json_Token* t, json_TokenKind kind) {
  t->kind = kind;
}

static void json_Token_setLocation(json_Token* t, json_Location loc) {
  t->loc = loc;
}

static void json_Location_set(json_Location* loc, uint32_t l, uint32_t c) {
  loc->line = l;
  loc->col = c;
}

static const char* json_Location_str(const json_Location* loc) {
  static char msg[32];
  sprintf(msg, "at line %d:%d", loc->line, loc->col);
  return msg;
}

static void json_TextBuffer_init(json_TextBuffer* b, uint32_t size) {
  b->cap = size;
  b->cur = 1;
  b->data = malloc(b->cap);
  b->data[0] = 0;
}

static void json_TextBuffer_destroy(json_TextBuffer* b) {
  free(b->data);
}

static void json_TextBuffer_reset(json_TextBuffer* b) {
    b->cur = 1;
    b->data[0] = 0;
}

static void json_TextBuffer_resize(json_TextBuffer* b, uint32_t cap2) {
  b->cap = cap2;
  char* data2 = malloc(b->cap);
  memcpy(data2, b->data, b->cur);
  free(b->data);
  b->data = data2;
}

static uint32_t json_TextBuffer_add(json_TextBuffer* b, const char* text, uint32_t len) {
  uint32_t left = (b->cap - b->cur);
  if ((len >= left)) json_TextBuffer_resize(b, (b->cap * 2));
  uint32_t idx = b->cur;
  memcpy(&b->data[idx], text, len);
  b->data[(idx + len)] = 0;
  b->cur += (len + 1);
  return idx;
}

static void json_TextBuffer_dump(const json_TextBuffer* b, const char* text) {
  printf("%s:  %u|%u\n", text, b->cur, b->cap);
  uint32_t idx = 1;
  while ((idx < b->cur)) {
    const char* name = &b->data[idx];
    printf("  [%3u] %s\n", idx, name);
    idx += (strlen(name) + 1);
  }
}

static const char* json_kind2str(json_NodeKind k) {
  switch (k) {
    case json_NodeKind_Object: return "<object>";
    case json_NodeKind_Value: return " <value>";
    case json_NodeKind_Array: return " <array>";
  }
  return NULL;
}

static void json_NodeBuffer_init(json_NodeBuffer* b, uint32_t size) {
  b->cap = size;
  b->cur = 1;
  b->data = malloc((size * 12));
}

static void json_NodeBuffer_destroy(json_NodeBuffer* b) {
  free(b->data);
}

static void json_NodeBuffer_reset(json_NodeBuffer* b) {
    b->cur = 1;
}

static uint32_t json_NodeBuffer_getSize(const json_NodeBuffer* b) {
  return (b->cur * 12);
}

static void json_NodeBuffer_resize(json_NodeBuffer* b, uint32_t cap2) {
  b->cap = cap2;
  char* data2 = malloc((b->cap * 12));
  memcpy(data2, b->data, (b->cur * 12));
  free(b->data);
  b->data = (json_Node*)(data2);
}

static uint32_t json_NodeBuffer_add(json_NodeBuffer* b, json_NodeKind kind, uint32_t name_idx, uint32_t value_idx) {
  if ((b->cur == b->cap)) json_NodeBuffer_resize(b, (b->cap * 2));
  uint32_t idx = b->cur;
  json_Node* n = &b->data[idx];
  n->next_kind = ((kind << 30));
  n->name_idx = name_idx;
  n->value_idx = value_idx;
  b->cur++;
  return idx;
}

static void json_NodeBuffer_dump(const json_NodeBuffer* b) {
  printf("Nodes:  %u|%u\n", b->cur, b->cap);
  uint32_t idx = 1;
  while ((idx < b->cur)) {
    const json_Node* n = &b->data[idx];
    json_NodeKind kind = ((json_NodeKind)(((n->next_kind >> 30))));
    printf("  [%3u] %s %3u  [next %3u]", idx, json_kind2str(kind), n->name_idx, ((n->next_kind & 0x3FFFFFFF)));
    switch (kind) {
      case json_NodeKind_Object:
        printf(" %3u\n", n->child_idx);
        break;
      case json_NodeKind_Value:
        printf(" %3u\n", n->value_idx);
        break;
      case json_NodeKind_Array:
        printf(" %3u\n", n->child_idx);
        break;
    }
    idx++;
  }
}

static json_Data* json_Data_create() {
  json_Data* d = malloc(48);
  json_TextBuffer_init(&d->names, json_TEXT_INIT_SIZE);
  json_TextBuffer_init(&d->values, json_TEXT_INIT_SIZE);
  json_NodeBuffer_init(&d->nodes, json_NODE_INIT_SIZE);
  return d;
}

static void json_Data_destroy(json_Data* d) {
  json_TextBuffer_destroy(&d->names);
  json_TextBuffer_destroy(&d->values);
  json_NodeBuffer_destroy(&d->nodes);
  free(d);
}

static void json_Data_reset(json_Data* d) {
    json_TextBuffer_reset(&d->names);
    json_TextBuffer_reset(&d->values);
    json_NodeBuffer_reset(&d->nodes);
}

static uint32_t json_Data_addName(json_Data* d, const char* name, uint32_t len) {
  return json_TextBuffer_add(&d->names, name, len);
}

static uint32_t json_Data_addValue(json_Data* d, const char* value, uint32_t len) {
  return json_TextBuffer_add(&d->values, value, len);
}

static uint32_t json_Data_addNode(json_Data* d, json_NodeKind kind, uint32_t name_idx, uint32_t value_idx) {
  return json_NodeBuffer_add(&d->nodes, kind, name_idx, value_idx);
}

static void json_Data_setChild(json_Data* d, uint32_t parent_idx, uint32_t child_idx) {
  json_Node* n = &d->nodes.data[parent_idx];
  n->child_idx = child_idx;
}

static void json_Data_setNext(json_Data* d, uint32_t prev_idx, uint32_t next_idx) {
  json_Node* n = &d->nodes.data[prev_idx];
  n->next_kind |= next_idx;
}

static void json_Data_dump(const json_Data* d, char verbose) {
  uint32_t used = (((d->nodes.cur * 12) + d->names.cur) + d->values.cur);
  uint32_t cap = (((d->nodes.cap * 12) + d->names.cap) + d->values.cap);
  printf("JSON  (memory: %u|%u)\n", used, cap);
  if (verbose)
  {
    json_NodeBuffer_dump(&d->nodes);
    json_TextBuffer_dump(&d->names, "Names");
    json_TextBuffer_dump(&d->values, "Values");
  }
  if ((d->nodes.cur == 1)) return;
  json_Data_dumpNode(d, 1, 0);
}

static void json_Data_dumpNode(const json_Data* d, uint32_t idx, uint32_t indent_) {
  while ((idx != 0)) {
    const json_Node* n = &d->nodes.data[idx];
    switch (((json_NodeKind)(((n->next_kind >> 30))))) {
      case json_NodeKind_Object:
        printf("%s%s\n", json_indent(indent_), &d->names.data[n->name_idx]);
        if ((n->child_idx != 0)) json_Data_dumpNode(d, n->child_idx, (indent_ + 1));
        break;
      case json_NodeKind_Value:
        printf("%s%s = '%s'\n", json_indent(indent_), &d->names.data[n->name_idx], &d->values.data[n->value_idx]);
        break;
      case json_NodeKind_Array:
        printf("%s %s\n", json_indent(indent_), &d->names.data[n->name_idx]);
        if ((n->child_idx != 0)) json_Data_dumpNode(d, n->child_idx, (indent_ + 1));
        break;
    }
    idx = ((n->next_kind & 0x3FFFFFFF));
  }
}

static uint32_t json_Parser_find_node(const json_Parser* p, const char* key) {
  if ((key[0] == 0)) return 0;
  uint32_t node_idx = 1;
  const char* cp = key;
  while (*cp) {
    const char* start = cp;
    char node_name[64];
    while (*cp) {
      if ((*cp == '.')) break;
      cp++;
    }
    uint32_t len = (uint32_t)((cp - start));
    if ((*cp == '.')) cp++;
    memcpy(node_name, start, len);
    node_name[len] = 0;
    node_idx = json_Parser_find_child(p, node_idx, node_name);
    if ((node_idx == 0)) return 0;
  }
  return node_idx;
}

const char* json_Parser_find_text(const json_Parser* p, const char* key) {
  uint32_t node_idx = json_Parser_find_node(p, key);
  if ((node_idx == 0)) return NULL;
  const json_Node* n = &p->data->nodes.data[node_idx];
  if ((((json_NodeKind)(((n->next_kind >> 30)))) != json_NodeKind_Value)) return NULL;
  return &p->data->values.data[n->value_idx];
}

static uint32_t json_Parser_find_child(const json_Parser* p, uint32_t parent_idx, const char* name) {
  uint32_t next = 1;
  if ((parent_idx != 0))
  {
    const json_Node* n = &p->data->nodes.data[parent_idx];
    next = n->child_idx;
  }
  while ((next != 0)) {
    const json_Node* n = &p->data->nodes.data[next];
    const char* nname = &p->data->names.data[n->name_idx];
    if ((strcmp(nname, name) == 0)) return next;
    next = ((n->next_kind & 0x3FFFFFFF));
  }
  return 0;
}

json_Iter json_Parser_getArrayIter(const json_Parser* p, const char* key) {
  json_Iter iter = { p->data, 0 };
  if ((key == NULL))
  {
    const json_Node* n = &p->data->nodes.data[1];
    if ((((json_NodeKind)(((n->next_kind >> 30)))) != json_NodeKind_Array)) return iter;
    iter.cur_idx = n->child_idx;
  }
  else
  {
    uint32_t node_idx = json_Parser_find_node(p, key);
    if ((node_idx == 0)) return iter;
    const json_Node* n = &p->data->nodes.data[node_idx];
    if ((((json_NodeKind)(((n->next_kind >> 30)))) != json_NodeKind_Array)) return iter;
    iter.cur_idx = n->child_idx;
  }
  return iter;
}

json_Iter json_Parser_getObjectIter(const json_Parser* p, const char* key) {
  json_Iter iter = { p->data, 0 };
  uint32_t node_idx = 1;
  if ((key != NULL)) node_idx = json_Parser_find_node(p, key);
  if ((node_idx == 0)) return iter;
  const json_Node* n = &p->data->nodes.data[node_idx];
  if ((((json_NodeKind)(((n->next_kind >> 30)))) != json_NodeKind_Object)) return iter;
  iter.cur_idx = n->child_idx;
  return iter;
}

char json_Iter_done(const json_Iter* i) {
  return (i->cur_idx == 0);
}

void json_Iter_next(json_Iter* i) {
  if ((i->cur_idx == 0)) return;
  const json_Node* n = &i->data->nodes.data[i->cur_idx];
  i->cur_idx = ((n->next_kind & 0x3FFFFFFF));
}

const char* json_Iter_find_text(const json_Iter* i, const char* key) {
  const json_Node* n = &i->data->nodes.data[i->cur_idx];
  if ((((json_NodeKind)(((n->next_kind >> 30)))) != json_NodeKind_Object)) return NULL;
  uint32_t node_idx = json_Iter_find_child(i, n->child_idx, key);
  if ((node_idx == 0)) return NULL;
  const json_Node* child = &i->data->nodes.data[node_idx];
  if ((((json_NodeKind)(((child->next_kind >> 30)))) != json_NodeKind_Value)) return NULL;
  return &i->data->values.data[child->value_idx];
}

static uint32_t json_Iter_find_child(const json_Iter* i, uint32_t idx, const char* name) {
  uint32_t next = idx;
  while ((next != 0)) {
    const json_Node* n = &i->data->nodes.data[next];
    const char* nname = &i->data->names.data[n->name_idx];
    if ((strcmp(nname, name) == 0)) return next;
    next = ((n->next_kind & 0x3FFFFFFF));
  }
  return 0;
}

const char* json_Iter_getKey(const json_Iter* i) {
  const json_Node* n = &i->data->nodes.data[i->cur_idx];
  if ((((json_NodeKind)(((n->next_kind >> 30)))) != json_NodeKind_Value)) return NULL;
  return &i->data->names.data[n->name_idx];
}

const char* json_Iter_getValue(const json_Iter* i) {
  const json_Node* n = &i->data->nodes.data[i->cur_idx];
  if ((((json_NodeKind)(((n->next_kind >> 30)))) != json_NodeKind_Value)) return NULL;
  return &i->data->values.data[n->value_idx];
}

int json_Iter_isValue(const json_Iter* i) {
  const json_Node* n = &i->data->nodes.data[i->cur_idx];
  if ((((json_NodeKind)(((n->next_kind >> 30)))) == json_NodeKind_Value)) return 1;
  return 0;
}

int json_Iter_isObject(const json_Iter* i) {
  const json_Node* n = &i->data->nodes.data[i->cur_idx];
  if ((((json_NodeKind)(((n->next_kind >> 30)))) == json_NodeKind_Object)) return 1;
  return 0;
}

json_Iter json_Iter_getObjectIter(const json_Iter* i) {
  json_Iter iter = { i->data, 0 };
  const json_Node* n = &i->data->nodes.data[i->cur_idx];
  if ((((json_NodeKind)(((n->next_kind >> 30)))) != json_NodeKind_Object)) return iter;
  iter.cur_idx = n->child_idx;
  return iter;
}

static char json_Iter_check_schema_priv(const json_Iter* i, const char** schema) {
  uint32_t cur_idx = i->cur_idx;
  while ((**schema != 0)) {
    if ((cur_idx == 0))
    {
      if ((**schema == ')')) return 1;
      return 0;
    }
    const json_Node* n = &i->data->nodes.data[cur_idx];
    switch (**schema) {
      case 's':
        if ((((json_NodeKind)(((n->next_kind >> 30)))) != json_NodeKind_Value)) return 0;
        break;
      case 'a':
        if ((((json_NodeKind)(((n->next_kind >> 30)))) != json_NodeKind_Array)) return 0;
        break;
      case 'o':
        if ((((json_NodeKind)(((n->next_kind >> 30)))) != json_NodeKind_Object)) return 0;
        if (((*schema)[1] == '('))
        {
          *schema += 2;
          json_Iter obj = { i->data, n->child_idx };
          if (!json_Iter_check_schema_priv(&obj, schema)) return 0;
        }
        break;
      case '.':
        return 1;
      default:
        return 0;
    }
    cur_idx = ((n->next_kind & 0x3FFFFFFF));
    (*schema)++;
  }
  return ((cur_idx == 0));
}

char json_Iter_check_schema(const json_Iter* i, const char* schema) {
  return json_Iter_check_schema_priv(i, &schema);
}

static const char* json_indent(uint32_t i) {
  static const char Indents[] = "                            ";
  static const uint32_t Max = 28;
  return &Indents[(Max - (i * 2))];
}

void json_Builder_init(json_Builder* b, uint32_t capacity) {
  b->buffer = malloc(capacity);
  b->capacity = capacity;
  json_Builder_reset(b);
}

void json_Builder_free(json_Builder* b) {
  free(b->buffer);
}

void json_Builder_finalize(json_Builder* b) {
  char* orig = &b->buffer[b->size];
  int32_t len = sprintf(orig, "\n");
  b->size += len;
}

const char* json_Builder_getData(const json_Builder* b) {
  return b->buffer;
}

uint32_t json_Builder_getSize(const json_Builder* b) {
  return (b->size + 1);
}

void json_Builder_addNumber(json_Builder* b, const char* key, int64_t value) {
  char* orig = &b->buffer[b->size];
  char* cp = orig;
  if (b->hasEntry[b->indent]) cp += sprintf(cp, ",\n");
  if (b->inArray[b->indent])
  {
    cp += sprintf(cp, "%s%lu", json_indent(b->indent), value);
  }
  else
  {
    cp += sprintf(cp, "%s\"%s\": %lu", json_indent(b->indent), key, value);
  }
  b->size += ((cp - orig));
  b->hasEntry[b->indent] = 1;
}

void json_Builder_addValue(json_Builder* b, const char* key, const char* value) {
  char* orig = &b->buffer[b->size];
  char* cp = orig;
  if (b->hasEntry[b->indent]) cp += sprintf(cp, ",\n");
  if (b->inArray[b->indent])
  {
    cp += sprintf(cp, "%s\"%s\"", json_indent(b->indent), value);
  }
  else
  {
    cp += sprintf(cp, "%s\"%s\": \"%s\"", json_indent(b->indent), key, value);
  }
  b->size += ((cp - orig));
  b->hasEntry[b->indent] = 1;
}

void json_Builder_addObject(json_Builder* b, const char* key) {
  char* orig = &b->buffer[b->size];
  char* cp = orig;
  if (b->hasEntry[b->indent]) cp += sprintf(cp, ",\n");
  if (b->inArray[b->indent])
  {
    cp += sprintf(cp, "%s{\n", json_indent(b->indent));
  }
  else
  {
    cp += sprintf(cp, "%s\"%s\":\n%s{\n", json_indent(b->indent), key, json_indent(b->indent));
  }
  b->size += ((cp - orig));
  b->hasEntry[b->indent] = 1;
  b->indent++;
  b->hasEntry[b->indent] = 0;
  b->inArray[b->indent] = 0;
}

void json_Builder_closeObject(json_Builder* b) {
  b->indent--;
  char* orig = &b->buffer[b->size];
  char* cp = orig;
  *cp++ = '\n';
  cp += sprintf(cp, "%s}", json_indent(b->indent));
  b->size += ((cp - orig));
}

void json_Builder_addArray(json_Builder* b, const char* key) {
  char* orig = &b->buffer[b->size];
  char* cp = orig;
  if (b->hasEntry[b->indent]) cp += sprintf(cp, ",\n");
  if (key)
  {
    cp += sprintf(cp, "%s\"%s\":\n%s[\n", json_indent(b->indent), key, json_indent(b->indent));
  }
  else
  {
    cp += sprintf(cp, "%s[\n", json_indent(b->indent));
  }
  b->size += ((cp - orig));
  b->hasEntry[b->indent] = 1;
  b->indent++;
  b->inArray[b->indent] = 1;
  b->hasEntry[b->indent] = 0;
}

void json_Builder_closeArray(json_Builder* b) {
  b->inArray[b->indent] = 0;
  b->indent--;
  char* orig = &b->buffer[b->size];
  char* cp = orig;
  *cp++ = '\n';
  cp += sprintf(cp, "%s]", json_indent(b->indent));
  b->size += ((cp - orig));
}

void json_Builder_reset(json_Builder* b) {
  b->size = 0;
  for (uint32_t i = 0; (i < 6); i++) b->hasEntry[i] = 0;
  for (uint32_t i = 0; (i < 6); i++) b->inArray[i] = 0;
  b->indent = 0;
  b->size = 0;
}

