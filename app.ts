import express from "express";
import http from "http";
import { WebSocketServer } from "ws";
import cors from "cors";

const app = express();
const port = 3000;
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
})

server.listen(port, () => {
    console.log(`Example app listening on port ${port}`)
})