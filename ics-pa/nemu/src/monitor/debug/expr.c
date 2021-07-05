#include <isa.h>
#include <stdlib.h>
#include <stdio.h>
/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>

// TK_NOTYPE = 256, TK_NUM = 257 ..... because the tocken should be excess 256 which belongs to ascii
enum
{
  TK_NOTYPE = 256,
  TK_NUM,

  /* TODO: Add more token types */

};

static struct rule
{
  char *regex;
  int token_type;
} rules[] = {

    /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   * "\\" will be translated to "\"
   */

    {" +", TK_NOTYPE},                   // spaces
    {"\\+", '+'},                        // plus
    {"\\*", '*'},                        //*
    {"/", '/'},                          // /
    {"-", '-'},                          // -
    {"\\(", '('},                        // Left parenthesis
    {"\\)", ')'},                        // Right parenthesis
    {"([1-9][0-9]{1,31})|[0-9]", TK_NUM} //([1-9][0-9]{1,31})|[0-9] can find 12312 string
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0])) // The number of rules' items.

static regex_t re[NR_REGEX] = {}; //store reg instance

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex()
{
  int i;
  char error_msg[128];
  int ret;
  //compile some reg
  for (i = 0; i < NR_REGEX; i++)
  {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0)
    {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
};

typedef struct token
{
  int type;
  char str[32];
} Token;

//_attribute__((used)) tells compiler maintain this variable in the memory
static Token tokens[32] __attribute__((used)) = {};
static int nr_token __attribute__((used)) = 0;

static bool make_token(char *e)
{
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  //test all char of the string
  while (e[position] != '\0')
  {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i++)
    {
      // successfully mached
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0)
      {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */

        switch (rules[i].token_type)
        {
        case TK_NOTYPE:
          break;
        default:
        {
          tokens[nr_token].type = rules[i].token_type;
          strncpy(tokens[nr_token].str, substr_start, substr_len);
          tokens[nr_token].str[substr_len] = '\0';
          nr_token++;
          break;
        }
        }
      }
      // if there is no rule can match the symbol
      if (i == NR_REGEX)
      {
        printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
        return false;
      }
    }
  }
  // end sumbol
  tokens[nr_token].type = -2147483648;
  return true;
};


bool check_parentheses(int p, int q)
{
  char stk[q - p + 1];
  int index = -1;
  for (int i = p; i <= q; i++)
  {
    if (tokens[i].type == '(')
    {
      stk[++index] = '(';
    }
    else if (tokens[i].type == ')')
    {
      if (stk[index] == '(')
        index--;
      else
        return false;
    }
  }
  return true;
};

int eval(int p, int q)
{
  if (p > q)
  {
    assert("bad expression");
  }
  else if (p == q)
  {
    return atoi(tokens[p].str);
  }
  else if (check_parentheses(p, q) == true)
  {
    /* The expression is surrounded by a matched pair of parentheses.
     * If that is the case, just throw away the parentheses.
     */
    return eval(p + 1, q - 1);
  }
  else
  {
    int op = q;
    int score = 3;
    for (int i = q; i >= p; i++)
    {
      if (tokens[i].type == '*' || tokens[i].type == '/')
      {
        if (score >= 2)
        {
          score = 2;
          op = i;
        }
      }
      if (tokens[i].type == '-')
      {
        if (score >= 1)
        {
          score = 1;
          op = i;
        }
      }
      if (tokens[i].type == '+')
      {
        if (score >= 0)
        {
          score = 0;
          op = i;
        }
      }
    }

    int val1 = eval(p, op - 1);
    int val2 = eval(op + 1, q);
    char op_type = tokens[op].type;
    switch (op_type)
    {
    case '+':
      return val1 + val2;
    case '-':
      return val1 - val2;
    case '*':
      return val1 * val2;
    case '/':
      return val1 / val2;
    default:
      assert(0);
    }
  }
  
  return -1;
}
  word_t expr(char *e, bool *success)
  {
    if (!make_token(e))
    {
      *success = false;
      return 0;
    }
    int len = 0;
    // find the length of tokens
    while (tokens[len].type != -2147483648)
    {
      len++;
    }

    printf("%d", eval(0, len));

    return 0;
  }
