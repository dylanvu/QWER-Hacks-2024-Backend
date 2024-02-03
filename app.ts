import express from "express";
import http from "http";
import { WebSocketServer } from "ws";
import cors from "cors";

const app = express();
const port = 3001;
app.use(cors());
app.use(express.json());

// create the
const server = http.createServer(app);

const wss = new WebSocketServer({ server: server });

app.get('/', (req, res) => {
    res.send('Hello World!')
})

wss.on("connection", (socket) => {
    console.log("A user has connected!");

    socket.on("message", (message) => {
        const messageEvent = JSON.parse(message.toString()); // Get the UTF-8 buffered data, turn to string, then turn to JS object with event and data attributes
        console.log(messageEvent);
    });

    socket.on('close', () => {
        console.log('Client disconnected');
    });
})

server.listen(port, () => {
    console.log(`Example app listening on port ${port}`)
})