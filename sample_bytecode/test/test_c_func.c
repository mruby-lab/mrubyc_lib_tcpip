// mruby/c上でsocket関数を動かすためにC関数をrubyでラップする

#include "mrubyc.h"
#include <stdio.h>

// Rubyから呼び出されるC関数
static void c_hello(mrb_vm *vm, mrb_value *v, int argc) {
  (void)argc; // 引数を使わないので無視
  
  const char *msg = "Hello from c_func!";
  //printf("%s\n", msg);   // C側に出力
  
  // 文字列オブジェクトを作って Ruby に返す
  mrbc_value str = mrbc_string_new_cstr(vm, msg);
  SET_RETURN(str);
}

// 初期化関数（mainから呼ぶ）
void mrbc_init_class_cfunc(struct VM *vm) {
  mrbc_define_method(0, mrbc_class_object, "c_hello", c_hello);
}