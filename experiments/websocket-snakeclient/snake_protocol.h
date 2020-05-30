#ifndef SNAKE_CONTEXT_H
#define SNAKE_CONTEXT_H

#include <libwebsockets.h>
#include <string.h>

#define RING_DEPTH 4096

typedef struct {
        struct lws_ring *ring;
        uint32_t msglen;
        uint32_t tail;
        uint8_t completed:1;
        uint8_t flow_controlled:1;
        uint8_t write_consume_pending:1;
} SnakeSessionData;

int snake_protocol_callback(struct lws *wsi, enum lws_callback_reasons reason,
        void *user, void *in, size_t len);

#define SNAKE_CONTEXT_HANDLER_PROTOCOL \
        { \
                "snake_protocol_callback", \
                snake_protocol_callback, \
                sizeof(SnakeSessionData), \
                1024, \
                0, NULL, 0 \
        }

#endif
