#include <stdio.h>
#include <stdlib.h>
#include "mrubyc.h"
#include "c_tcp.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#if !defined(MRBC_MEMORY_SIZE)
#define MRBC_MEMORY_SIZE (1024*40)
#endif
static uint8_t memory_pool[MRBC_MEMORY_SIZE];

int sock, client_sock;
struct sockaddr_in addr, client, client_addr;
socklen_t len = sizeof(client);

static void c_open(mrb_vm *vm, mrb_value v[], int argc)
{
  int port = GET_INT_ARG(1); 
  // mrbc_printf("  v = %d \n");
  // mrbc_printf("  port = %d", port);
  // mrbc_p( port );

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if(sock < 0){
    mrbc_printf("  open/socket error\n");
    SET_NIL_RETURN();   // エラー時は nil を返す
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr =  INADDR_ANY;

  
  if(bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0){
    mrbc_printf("  open/bind error\n");
    SET_NIL_RETURN();   // エラー時は nil を返す
  }

  if(listen(sock, 1) < 0){
    mrbc_printf("  open/listen error\n");
    SET_NIL_RETURN();   // エラー時は nil を返す
  }

  // return values. defined in value.h
  SET_INT_RETURN(sock);
}

static void c_accept(mrb_vm *vm, mrb_value v[], int argc)
{
  client_sock = accept(sock, (struct sockaddr *)&client, &len);

  if(client_sock < 0){
    mrbc_printf("  accept error\n");
    SET_NIL_RETURN();   // エラー時は nil を返す
  }

  // return values. defined in value.h
  SET_INT_RETURN(client_sock);
}

static void c_recv(mrb_vm *vm, mrb_value v[], int argc)
{
  int number = GET_INT_ARG(1);  
  char buf[number];
  int len = 0;
  mrbc_value str;

  len = recv(client_sock, buf, sizeof(buf) - 1, 0);

  if (len < 0) {
    mrbc_printf("  recv error\n");
    SET_NIL_RETURN();

  }else if(len > 0){
    buf[len] = '\0';
    // mrbc_printf("buf = %s\n",buf);

    str = mrbc_string_new_cstr(vm, buf);
    // mrbc_printf("  len = %d\n", len);
    // mrbc_printf("  number = %d\n", number);  
    // mrbc_printf("  str = %s\n",str.string->data);
  }

  // return values. defined in value.h
  SET_RETURN(str);
}

static void c_close(mrb_vm *vm, mrb_value v[], int argc)
{
  close(client_sock);
  close(sock);
  
  // return values. defined in value.h
  SET_INT_RETURN(1);
}

void mrbc_init_class_tcp(void){
  mrbc_class *TCPServer = mrbc_define_class(0, "TCPServer", MRBC_CLASS(Object));
  
  mrbc_define_method(0, TCPServer, "open", c_open);
  mrbc_define_method(0, TCPServer, "accept", c_accept);
  mrbc_define_method(0, TCPServer, "recv", c_recv);
  mrbc_define_method(0, TCPServer, "close", c_close);
}