#ifndef __QUEUE_H__
#define __QUEUE_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>

#define MAX_SIZE    255

typedef struct{
  uint8_t head;
  uint8_t tail;
  uint8_t buffer[MAX_SIZE];
}quint8_t;

void init_queue(quint8_t* u);
void push(quint8_t* u, uint8_t data);
uint8_t pop(quint8_t* u);
uint8_t isEmpty(quint8_t* u);

#ifdef __cplusplus
}
#endif

#endif