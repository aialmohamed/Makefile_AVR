#define RING_BUFFER_SIZE 128


typedef struct 
{
    unsigned char head;
    unsigned char tail;
    unsigned char data[RING_BUFFER_SIZE];
}ring_buffer_t;



/**
 * 
 * 
 */

void            RBInit(ring_buffer_t *rb);
unsigned char   RBFree(ring_buffer_t *rb);
unsigned char   RBLength(ring_buffer_t *rb);
unsigned char   RBReadByte(ring_buffer_t *rb);
unsigned char   RBWriteByte(ring_buffer_t *rb,unsigned char data);
unsigned char   RBRead(ring_buffer_t *rb,unsigned char *data,unsigned char dataL);
unsigned char   RBWrite(ring_buffer_t *rb,unsigned char *data, unsigned char dataL);