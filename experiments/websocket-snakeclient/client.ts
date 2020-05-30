import { Application, Router, send } from "https://deno.land/x/oak/mod.ts";
import { WebSocket } from "https://deno.land/x/websocket/mod.ts";

const HTTPS_PORT = 5445;
const WEBSOCKET_PORT = 5444;

const endpoint = `ws://127.0.0.1:${WEBSOCKET_PORT}`;

const ws: WebSocket = new WebSocket(endpoint);
ws.on("open", function() {
  console.log(`ws connected: ${JSON.stringify(ws.webSocket?.conn)}`);
});
ws.on("message", function (message: string) {
  console.log(`Message from Server: ${message}`);
});
ws.on("close", function () {
  console.log(`ws disconnected: ${JSON.stringify(ws.webSocket?.conn)}`);
});

const router = new Router();
router
  .get("/", (context) => {
    context.response.body = `Hello World! Connected via: ${ws.webSocket}`;
  })
  .get("/snake=:command", (context) => {
    const command: string = context.params.command ? context.params.command : '';
    if (!context.params || !context.params.command || command === '') {
      context.response.status = 404;
      context.response.body = 'Command not found.'
    }
    console.log(`Sending command: ${command}`);
    const body = `Command Sent: ${command}`;
    console.log(body);
    context.response.body = body;
  });

const app = new Application();
app.use(router.routes());
app.use(router.allowedMethods());

app.listen({ port: HTTPS_PORT });
console.log(`Listening on  https://localhost:${HTTPS_PORT} and ${endpoint}`);
