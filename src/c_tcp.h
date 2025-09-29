#include "mrubyc.h"

static void c_open(mrb_vm *vm, mrb_value v[], int argc);
static void c_accept(mrb_vm *vm, mrb_value v[], int argc);
static void c_recv(mrb_vm *vm, mrb_value v[], int argc);
static void c_close(mrb_vm *vm, mrb_value v[], int argc);
