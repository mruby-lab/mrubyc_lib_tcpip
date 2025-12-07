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

struct TCPServer_info {
  int sock;
  struct sockaddr_in addr;
};

struct Socket_info {
  int sock;
};


static void c_server_open(mrb_vm *vm, mrb_value v[], int argc)
{
  int port = GET_INT_ARG(1); 
  // mrbc_printf("  port = %d", port);

  struct TCPServer_info info;

  info.sock = socket(AF_INET, SOCK_STREAM, 0);
  if(info.sock < 0){
    mrbc_printf("  open/socket error\n");
    SET_NIL_RETURN();
    return;
  }
    // mrbc_printf("  sock = %d", sock);

  info.addr.sin_family = AF_INET;
  info.addr.sin_port = htons(port);
  info.addr.sin_addr.s_addr = INADDR_ANY;

  if(bind(info.sock, (struct sockaddr *)&info.addr, sizeof(info.addr)) < 0){
    mrbc_printf("  open/bind error\n");
    SET_NIL_RETURN();
    return;
  }

  if(listen(info.sock, 1) < 0){
    mrbc_printf("  open/listen error\n");
    SET_NIL_RETURN();
    return;
  }

    mrbc_class *tcp = mrbc_get_class_by_name("TCPServer");
  mrbc_decref(&v[0]);
  v[0] = mrbc_instance_new(vm, tcp, sizeof(struct TCPServer_info));
  *(struct TCPServer_info *)(v[0].instance->data) = info;
}

static void c_server_accept(mrb_vm *vm, mrb_value v[], int argc)
{
  struct TCPServer_info *info = (struct TCPServer_info *)(v[0].instance->data);
  int len;
  int client_sock = accept(info->sock, (struct sockaddr *)&info->addr, &len);
 
  if(client_sock < 0){
    mrbc_printf("  accept error\n");
    SET_NIL_RETURN();
    return;
  }

  // return values. defined in value.h
  mrbc_decref(&v[0]);
  mrbc_class *cls = mrbc_get_class_by_name("TCPSocket");
  v[0] = mrbc_instance_new(vm, cls, sizeof(struct Socket_info));
  struct Socket_info *socket_info  = (struct Socket_info *)(v[0].instance->data);
  socket_info->sock = client_sock;
}

static void c_socket_recv(mrb_vm *vm, mrb_value v[], int argc)
{
  int number = GET_INT_ARG(1);  
  char buf[number];
  int len = 0;
  mrbc_value str;

  struct Socket_info *info = (struct Socket_info *)(v[0].instance->data);
  len = recv(info->sock, buf, sizeof(buf) - 1, 0);
  mrbc_printf("  len = %d\n", len);

  if (len < 0) {
    mrbc_printf("  recv error: %s\n", strerror(errno));
    SET_NIL_RETURN();
    return;

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

static void c_server_close(mrb_vm *vm, mrb_value v[], int argc)
{
  int sock = *(int *)(v[0].instance->data);
  close(sock);
  
  // return values. defined in value.h
  SET_NIL_RETURN();
}

#if 0
static void c_socket_open(mrb_vm *vm, mrb_value v[], int argc)
{
  const char *src = GET_STRING_ARG(1);
  char ip[32];
  strncpy(ip, src, sizeof(ip) - 1);
  ip[sizeof(ip) - 1] = '\0';
  int port = GET_INT_ARG(2);

  int s_client = socket(AF_INET, SOCK_STREAM, 0);

  if(s_client < 0){
    mrbc_printf("  open/socket error\n");
    SET_NIL_RETURN();
    return;
  }

  memset(&s_addr, 0, sizeof(s_addr));
  s_addr.sin_family = AF_INET;
  s_addr.sin_port = htons(port);
  s_addr.sin_addr.s_addr = inet_addr(ip);

  mrbc_printf("  port = %d\n", port);
  mrbc_printf("  ip = %s\n", ip);  

  if(connect(s_client, (struct sockaddr *)&s_addr, sizeof(s_addr)) < 0){
    mrbc_printf("  open/connect error: %d\n", errno);
    close(s_client);
    SET_NIL_RETURN();
    return;
  }

}
#endif 

static void c_socket_send(mrb_vm *vm, mrb_value v[], int argc)
{
  // int number = GET_INT_ARG(1);  
  const char *buf = GET_STRING_ARG(1);
  int len = 0;

  struct Socket_info *info = (struct Socket_info *)(v[0].instance->data);
  len = send(info->sock, buf, strlen(buf), 0);

  if (len < 0) {
    mrbc_printf("send error: %s\n", strerror(errno));
    SET_NIL_RETURN();
    return;

  }

  SET_INT_RETURN(len);
}

static void c_socket_close(mrb_vm *vm, mrb_value v[], int argc)
{
  close(*(int *)(v[0].instance->data));
  SET_NIL_RETURN();
}


void mrbc_init_class_tcp(void){
  mrbc_class *TCPServer = mrbc_define_class(0, "TCPServer", MRBC_CLASS(Object));
  
  mrbc_define_method(0, TCPServer, "open", c_server_open);
  mrbc_define_method(0, TCPServer, "accept", c_server_accept);
  mrbc_define_method(0, TCPServer, "close", c_server_close);

  mrbc_class *TCPSocket = mrbc_define_class(0, "TCPSocket", MRBC_CLASS(Object));
  
  // mrbc_define_method(0, TCPSocket, "open", c_socket_open);
  mrbc_define_method(0, TCPSocket, "recv", c_socket_recv);
  mrbc_define_method(0, TCPSocket, "send", c_socket_send);
  mrbc_define_method(0, TCPSocket, "close", c_socket_close);
}