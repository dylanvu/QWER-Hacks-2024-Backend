import cryto from "crypto";
export function createUUID() {
    return crypto.randomUUID();
}