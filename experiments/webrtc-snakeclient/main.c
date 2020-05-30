#include <emscripten/emscripten.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // for sleep
#include <ctype.h>

#include "rtc/rtc.h"

typedef struct {
        rtcState state;
        rtcGatheringState gatheringState;
        int pc;
        int dc;
        bool connected;
} Peer;

Peer *peer = NULL;
static bool exit_on;

static void descriptionCallback(const char *sdp, const char *type, void *ptr) {
        // Peer *peer = (Peer *)ptr;
        printf("Description %s:\n%s\n", "answerer", sdp);
}

static void candidateCallback(const char *cand, const char *mid, void *ptr) {
        // Peer *peer = (Peer *)ptr;
        printf("Candidate %s: %s\n", "answerer", cand);
}

static void stateChangeCallback(rtcState state, void *ptr) {
        Peer *peer = (Peer *)ptr;
        peer->state = state;
}

static void gatheringStateCallback(rtcGatheringState state, void *ptr) {
        Peer *peer = (Peer *)ptr;
        peer->gatheringState = state;
        // printf("Gathering state %s: %s\n", "answerer", rtcGatheringState_print(state));
}

static void closedCallback(void *ptr) {
        Peer *peer = (Peer *)ptr;
        peer->connected = false;
}

static void messageCallback(const char *message, int size, void *ptr) {
        // // Peer *peer = (Peer *)ptr;
        // if (size < 0) { // negative size indicates a null-terminated string
        //         printf("Message %s: %s\n", "answerer", message);
        // } else {
        //         printf("Message %s: [binary of size %d]\n", "answerer", size);
        // }
}

static void deletePeer(Peer *peer) {
        if (peer) {
                if (peer->dc)
                        rtcDeleteDataChannel(peer->dc);
                if (peer->pc)
                        rtcDeletePeerConnection(peer->pc);
                free(peer);
        }
}

static void dataChannelCallback(int dc, void *ptr) {
        Peer *peer = (Peer *)ptr;
        peer->dc = dc;
        peer->connected = true;
        rtcSetClosedCallback(dc, closedCallback);
        rtcSetMessageCallback(dc, messageCallback);
        char buffer[256];
        if (rtcGetDataChannelLabel(dc, buffer, 256) >= 0)
                return;
                // printf("DataChannel %s: Received with label \"%s\"\n", "answerer", buffer);
}

int all_space(const char *str) {
        while (*str) {
                if (!isspace(*str++)) {
                        return 0;
                }
        }
        return 1;
}

/**
 * Set the description.
 */
void EMSCRIPTEN_KEEPALIVE set_description (char* description) {
        rtcSetRemoteDescription(peer->pc, description, "offer");
}

/**
 * Add a candidate.
 */
void EMSCRIPTEN_KEEPALIVE add_candidate (char* candidate) {
        rtcAddRemoteCandidate(peer->pc, candidate, "0");
}

/**
 * Attempt to send a message.
 */
int EMSCRIPTEN_KEEPALIVE send_message(char* message) {
        if (!peer->connected) {
                return 1;
        }
        rtcSendMessage(peer->dc, message, -1);
        return 0;
}

/**
 * Return the current peer state.
 */
int EMSCRIPTEN_KEEPALIVE get_status(void) {
        return peer->state;
}

/**
 * Terminate the connection.
 */
int EMSCRIPTEN_KEEPALIVE terminate(void) {
        exit_on = true;
}

int EMSCRIPTEN_KEEPALIVE main(int argc, char **argv) {
        // Create peer
        rtcConfiguration config;
        memset(&config, 0, sizeof(config));
        peer = (Peer *)malloc(sizeof(Peer));
        if (!peer) {
                printf("Error allocating memory for peer\n");
                deletePeer(peer);
        }
        memset(peer, 0, sizeof(Peer));

        // Create peer connection
        peer->pc = rtcCreatePeerConnection(&config);
        rtcSetUserPointer(peer->pc, peer);
        rtcSetLocalDescriptionCallback(peer->pc, descriptionCallback);
        rtcSetLocalCandidateCallback(peer->pc, candidateCallback);
        rtcSetStateChangeCallback(peer->pc, stateChangeCallback);
        rtcSetGatheringStateChangeCallback(peer->pc, gatheringStateCallback);
        rtcSetUserPointer(peer->dc, NULL);
        rtcSetDataChannelCallback(peer->pc, dataChannelCallback);

        exit_on = false;
        while (!exit_on);
        deletePeer(peer);
        return 0;
}
