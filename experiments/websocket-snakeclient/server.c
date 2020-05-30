#include <libwebsockets.h>

#include <string.h>
#include <signal.h>

#define LWS_PLUGIN_STATIC
#include "snake_protocol.h"

static struct lws_protocols protocols[] = {
        SNAKE_CONTEXT_HANDLER_PROTOCOL,
        { NULL, NULL, 0, 0 } /* terminator */
};

static int interrupted, port = 5444, options;

/* pass pointers to shared vars to the protocol */
static const struct lws_protocol_vhost_options pvo_options = {
        NULL,
        NULL,
        "options",		/* pvo name */
        (void *)&options	/* pvo value */
};
static const struct lws_protocol_vhost_options pvo_interrupted = {
        &pvo_options,
        NULL,
        "interrupted",		/* pvo name */
        (void *)&interrupted	/* pvo value */
};
static const struct lws_protocol_vhost_options pvo = {
        NULL,				/* "next" pvo linked-list */
        &pvo_interrupted,		/* "child" pvo linked-list */
        "lws-minimal-server-echo",	/* protocol name we belong to on this vhost */
        ""				/* ignored */
};

void sigint_handler(int sig)
{
        interrupted = 1;
}

int main(int argc, const char **argv)
{
        signal(SIGINT, sigint_handler);
        struct lws_context_creation_info info;
        struct lws_context *context;
        const char *p;

        int n = 0, logs = LLL_USER | LLL_ERR | LLL_WARN | LLL_NOTICE | LLL_LATENCY;
                        /* for LLL_ verbosity above NOTICE to be built into lws,
                         * lws must have been configured and built with
                         * -DCMAKE_BUILD_TYPE=DEBUG instead of =RELEASE */
        
        if ((p = lws_cmdline_option(argc, argv, "-d")))
                logs = atoi(p);

        lws_set_log_level(logs, NULL);
        lwsl_user("LWS minimal ws client echo + permessage-deflate + multifragment bulk message\n");


        if ((p = lws_cmdline_option(argc, argv, "-p")))
                port = atoi(p);
        if (lws_cmdline_option(argc, argv, "-o"))
                options |= 1;

        memset(&info, 0, sizeof info); /* otherwise uninitialized garbage */
        info.port = port;
        info.protocols = protocols;
        info.pvo = &pvo;

        info.pt_serv_buf_size = 32 * 1024;
        info.options = LWS_SERVER_OPTION_VALIDATE_UTF8 |
                LWS_SERVER_OPTION_HTTP_HEADERS_SECURITY_BEST_PRACTICES_ENFORCE;

        context = lws_create_context(&info);
        if (!context) {
                lwsl_err("lws init failed\n");
                return 1;
        }

        while (n >= 0 && !interrupted)
                n = lws_service(context, 0);

        lws_context_destroy(context);
        lwsl_user("Completed %s\n", interrupted == 2 ? "OK" : "failed");
        return interrupted != 2;
}
