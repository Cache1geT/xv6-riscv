#include "../kernel/types.h"
#include "../kernel/param.h"
#include "../kernel/memlayout.h"
#include "../kernel/riscv.h"
#include "../kernel/spinlock.h"
#include "../kernel/proc.h"
#include "../kernel/defs.h"

void recursion(int n) {
  if (n == 0) {
      printf( "Recursion invoke finished.\n");
      return;
  }
  int arrayOnStack[1024];
  printf("Recursion invoke pushing stack[%x]: %d.\n", arrayOnStack, n);
  for (int i = 0; i < 1024; i++) {
    arrayOnStack[i] = n + i;
  }

  recursion(n - 1);
  printf("Recursion invoke popping stack[%x]: %d.\n", arrayOnStack, n);
}

int main() {
  printf("================================\n");
  printf("Stack auto growth test begin. Recursion invoking function.\n");
  recursion(256);
  printf("Stack auto growth test finish.\n");
  printf("================================\n");
  return 1;
}
