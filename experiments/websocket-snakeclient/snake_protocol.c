#include <libwebsockets.h>

#include <stdio.h>
#include <string.h>

#include "snake_protocol.h"

typedef struct {
        void *payload;
        size_t len;
        char binary;
        char first;
        char final;
} SnakeClientMessage;

typedef struct {
        struct lws_context *context;
        struct lws_vhost *vhost;
        int *interrupted;
        int *options;
} SnakeVHD;

typedef enum {
        UNKNOWN,
        CONNECT,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        DISCONNECT,
        VALID_MESSAGES
} MESSAGES;

static const char* VALID_MESSAGE_STRINGS[VALID_MESSAGES] = {
        "*",
        "Connect",
        "Up",
        "Down",
        "Left",
        "Right",
        "Disconect"
};

typedef enum {
        CONNECTED,
        OK,
        INVALID,
        NUM_REPLIES
} REPLIES;

static const char* REPLY_STRINGS[NUM_REPLIES] = {
        "Connected",
        "Ok",
        "Invalid"
};

static void
__minimal_destroy_message(void *_msg)
{
        SnakeClientMessage *msg = _msg;
        free(msg->payload);
        msg->payload = NULL;
        msg->len = 0;
}

static REPLIES
__process_message(char* message)
{
        // Compare against each message type.
        MESSAGES type = 0;
        for (int i = 0; i < VALID_MESSAGES; i++) {
                if (strcmp(message, VALID_MESSAGE_STRINGS[i]) == 0) {
                        type = i;
                        break;
                }
        }
        switch (type) {
                case CONNECT:
                        return CONNECTED;
                // Move the snake.
                case UP:
                        /* code */
                        return OK;
                case DOWN:
                        /* code */
                        return OK;
                case LEFT:
                        /* code */
                        return OK;
                case RIGHT:
                        /* code */
                        return OK;
                case DISCONNECT:
                        /* code */
                        return OK;
                // We did not have a match.
                case UNKNOWN:
                default:
                        return INVALID;
        }
}

#include <assert.h>
int
snake_protocol_callback(struct lws *wsi, enum lws_callback_reasons reason,
                void *user, void *in, size_t len) {
        SnakeSessionData *pss = (SnakeSessionData *)user;
        SnakeVHD *vhd = (SnakeVHD *) lws_protocol_vh_priv_get(lws_get_vhost(wsi), lws_get_protocol(wsi));
        const SnakeClientMessage *pmsg;
        SnakeClientMessage amsg;
        int m, n, flags;
        REPLIES reply = 0;
        switch (reason) {
                case LWS_CALLBACK_PROTOCOL_INIT:
                        vhd = lws_protocol_vh_priv_zalloc(lws_get_vhost(wsi), lws_get_protocol(wsi), sizeof(SnakeVHD));
                        if (!vhd) {
                                return -1;
                        }
                        vhd->context = lws_get_context(wsi);
                        vhd->vhost = lws_get_vhost(wsi);
                        /* get the pointers we were passed in pvo */
                        const struct lws_protocol_vhost_options *interrupted = lws_pvo_search((const struct lws_protocol_vhost_options *)in, "interrupted");
                        const struct lws_protocol_vhost_options *options = lws_pvo_search((const struct lws_protocol_vhost_options *)in, "options");
                        if (interrupted != NULL) {
                                // We have been provided interuption instructions.
                                vhd->interrupted = (int *) interrupted->value;
                        }
                        if (options != NULL) {
                                // We have been provided options.
                                vhd->options = (int *) options->value;
                        }
                        break;
                case LWS_CALLBACK_ESTABLISHED:
                        /* generate a block of output before travis times us out */
                        lwsl_warn("LWS_CALLBACK_ESTABLISHED\n");
                        pss->ring = lws_ring_create(sizeof(SnakeClientMessage), RING_DEPTH, __minimal_destroy_message);
                        if (!pss->ring) {
                                return 1;
                        }
                        pss->tail = 0;
                        break;
                case LWS_CALLBACK_SERVER_WRITEABLE:
                        lwsl_user("LWS_CALLBACK_SERVER_WRITEABLE\n");
                        if (pss->write_consume_pending) {
                                /* perform the deferred fifo consume */
                                lws_ring_consume_single_tail(pss->ring, &pss->tail, 1);
                                pss->write_consume_pending = 0;
                        }
                        pmsg = lws_ring_get_element(pss->ring, &pss->tail);
                        if (pmsg && pmsg->len) {
                                printf("Sending Message: %.*s\n", (int) pmsg->len, (char *) pmsg->payload + LWS_PRE);
                        }
                        
                        if (!pmsg) {
                                lwsl_user(" (nothing in ring)\n");
                                break;
                        }
                        flags = lws_write_ws_flags(pmsg->binary ? LWS_WRITE_BINARY : LWS_WRITE_TEXT, pmsg->first, pmsg->final);
                        /* notice we allowed for LWS_PRE in the payload already */
                        m = lws_write(wsi, ((unsigned char *)pmsg->payload) + LWS_PRE, pmsg->len, flags);
                        if (m < (int)pmsg->len) {
                                lwsl_err("ERROR %d writing to ws socket\n", m);
                                return -1;
                        }
                        // lwsl_user(" wrote %d %s: flags: 0x%x first: %d final %d\n", m, flags, pmsg->payload, pmsg->first, pmsg->final);
                        /*
                         * Workaround deferred deflate in pmd extension by only
                         * consuming the fifo entry when we are certain it has been
                         * fully deflated at the next WRITABLE callback.  You only need
                         * this if you're using pmd.
                         */
                        pss->write_consume_pending = 1;
                        lws_callback_on_writable(wsi);
                        if (pss->flow_controlled && (int) lws_ring_get_count_free_elements(pss->ring) > RING_DEPTH - 5) {
                                lws_rx_flow_control(wsi, 1);
                                pss->flow_controlled = 0;
                        }
                        if ((vhd->options && *vhd->options & 1) && pmsg && pmsg->final) {
                                pss->completed = 1;
                        }
                        break;
                case LWS_CALLBACK_RECEIVE:
                        lwsl_user("LWS_CALLBACK_RECEIVE\n");
                        
                        if (len) {
                                ;
                                //puts((const char *)in);
                                //lwsl_hexdump_notice(in, len);
                        }

                        amsg.first = lws_is_first_fragment(wsi);
                        amsg.final = lws_is_final_fragment(wsi);
                        amsg.binary = lws_frame_is_binary(wsi);

                        n = (int)lws_ring_get_count_free_elements(pss->ring);
                        if (!n) {
                                lwsl_user("Not enough space in ring, dropping message\n");
                                break;
                        }

                        if (amsg.final) {
                                pss->msglen = 0;
                        } else {
                                pss->msglen += len;
                        }

                        // printf("Message received: %.*s\n", (int) len, (char *) in);
                        char *message = (char *) malloc(sizeof(char) * (len + 1));
                        memset(message, '\0', len + 1);
                        memcpy(message, (char *) in, len);
                        printf("Message received: %s\n", message);
                        reply = __process_message(message);
                        free(message);

                        amsg.len = strlen(REPLY_STRINGS[reply]);
                        /* notice we over-allocate by LWS_PRE */
                        amsg.payload = malloc(LWS_PRE + strlen(REPLY_STRINGS[reply]));
                        if (!amsg.payload) {
                                lwsl_user("Not enough memory: dropping\n");
                                break;
                        }
                        
                        memcpy((char *)amsg.payload + LWS_PRE, REPLY_STRINGS[reply], strlen(REPLY_STRINGS[reply]));
                        if (!lws_ring_insert(pss->ring, &amsg, 1)) {
                                __minimal_destroy_message(&amsg);
                                lwsl_user("dropping!\n");
                                break;
                        }
                        lws_callback_on_writable(wsi);

                        if (n < 3 && !pss->flow_controlled) {
                                pss->flow_controlled = 1;
                                lws_rx_flow_control(wsi, 0);
                        }

                        break;
                case LWS_CALLBACK_CLOSED:
                        lwsl_user("LWS_CALLBACK_CLOSED\n");
                        lws_ring_destroy(pss->ring);

                        if (*vhd->options & 1) {
                                if (!*vhd->interrupted)
                                        *vhd->interrupted = 1 + pss->completed;
                                lws_cancel_service(lws_get_context(wsi));
                        }
                        break;

                default:
                        break;
                }

        return 0;
}
