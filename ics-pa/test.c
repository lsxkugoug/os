#include<stdio.h>
typedef struct {
  //lab1.3
  union {
    long _32;
    int _16;
  } gpr[8];

  /* Do NOT change the order of the GPRs' definitions. */

  /* In NEMU, rtlreg_t is exactly uint32_t. This makes RTL instructions
   * in PA2 able to directly access these registers.
   */
  long eax = gpr[0];

} x86_CPU_state;

int main(){
    x86_CPU_state cpu;
    
}