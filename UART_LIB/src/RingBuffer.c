#include "RingBuffer.h"



void RBInit(ring_buffer_t *rb)
{


    rb->tail=0;
    rb->head=0;
}

unsigned char   RBFree(ring_buffer_t *rb)
{

    unsigned char free;

    if(rb->head >= rb->tail){
        free =RING_BUFFER_SIZE -(rb->head - rb->tail);
    }
    else
    {
        free =rb->tail -rb->head;
    }
    
    return free;
}

unsigned char   RBLength(ring_buffer_t *rb)
{

    unsigned char len;

    if (rb->head >= rb->tail)
    {
        len = rb->head -rb->tail;
    }
    else
    {
        len = RING_BUFFER_SIZE - (rb->tail - rb->head);
    }
    return len;
}

unsigned char   RBReadByte(ring_buffer_t *rb)
{
    unsigned char tail;
    unsigned char RES;

    if(RBLength(rb) == 0)
    {
        return 0;
    }
    RES = rb->data[tail++];
    if(tail >= RING_BUFFER_SIZE)
    {
        tail=0;
    }
    rb->tail = tail;

    return RES;
}

unsigned char   RBWriteByte(ring_buffer_t *rb,unsigned char data)
{
    unsigned char head;
    while(RBFree(rb) < 1 );
    
    rb->data[head++] =data;

    if(head >= RING_BUFFER_SIZE)
    {
        head =0;
    }
    rb->head =head;

    return 1 ;
}

unsigned char   RBRead(ring_buffer_t *rb,unsigned char *data,unsigned char dataL)
{
    unsigned char tail;

    tail =rb->tail;

    if(dataL ==0 || RBLength(rb) ==0)
    {
        return 0;
    }
    
    if(RBLength(rb) < dataL)
    {
        dataL =RBLength(rb);
    }
    
    while(dataL--)
    {
        *data++ =rb->data[tail++];

        if(tail >= RING_BUFFER_SIZE)
        {
            tail = 0;
        }
    }
    rb->tail =tail;

    return 1;
}


unsigned char   RBWrite(ring_buffer_t *rb,unsigned char *data, unsigned char datal)
{
	unsigned char head;
	
	head = rb->head;
	
	if (datal == 0)
	{
		return  0;
	}
	
	while(RBFree(rb) < datal);
	
	while(datal--)
	{
		rb->data[head++] = *data++;
		if (head >= RING_BUFFER_SIZE)
		{
			head = 0;
		}
	}
	
	rb->head = head;
	
	return 1;
}
