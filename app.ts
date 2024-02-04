import express from "express";
import http from "http";
import { WebSocketServer, WebSocket } from "ws";
import cors from "cors";
import { createUUID } from "./util/util";

const app = express();
const port = 3001;
app.use(cors());
app.use(express.json());

// create the room system
let clientList: Record<string, WebSocket> = {}

const server = http.createServer(app);

const wss = new WebSocketServer({ server: server });

app.get('/', (req, res) => {
    res.send('Hello World!')
})

wss.on("connection", (socket) => {
    console.log("A user has connected!");

    // create a UUID, and add to clientList
    const uuid = createUUID();
    clientList[uuid] = socket;

    console.log(Object.keys(clientList));

    socket.on("message", (message) => {
        const messageString = message.toString();
        // console.log(messageString);
        let messageEvent = JSON.parse(messageString);
        // try {
        //     messageEvent = JSON.parse(message.toString()); // Get the UTF-8 buffered data, turn to string, then turn to JS object with event and data attributes
        // } catch (e) {
        //     console.error(e);
        // }
        if (messageEvent.shoot) {
            console.log(messageEvent);
        }
        wss.clients.forEach((client) => {
            client.send(JSON.stringify(messageEvent));
        });
    });

    socket.on('close', () => {
        console.log('Client disconnected');
        // remove client from the room
        delete clientList[uuid];
        console.log(Object.keys(clientList));
    });
})

server.listen(port, () => {
    console.log(`Example app listening on port ${port}`)
})