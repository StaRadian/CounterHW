#include "queue.h"

//Queue 구현
//호성 제작
void init_queue(quint8_t* u)
{
  u->head = 0;
  u->tail = 0;
}

void push(quint8_t* u, uint8_t data)
{
  u->buffer[u->head] = data;

  u->head++;

  if (u->head >= MAX_SIZE) {
    u->head = 0;
  }
}

uint8_t pop(quint8_t* u)
{
  uint8_t data = u->buffer[u->tail];

  u->tail++;

  if (u->tail >= MAX_SIZE) {
    u->tail = 0;
  }

  return data;
}

uint8_t isEmpty(quint8_t* u)
{  
    return u->head == u->tail;
}