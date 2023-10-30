import { readFileSync, writeFileSync, existsSync } from 'fs';

export const log = (req, message, opId) => {
    var logs;
    if (existsSync('data/system.log'))
        logs = readFileSync("data/system.log", 'utf8');
    else logs = ``;
    logs += `${opId ? `[${opId}] ` : ''}${message}\n`;
    writeFileSync('data/system.log', logs);
};

export const list = () => {
    var logs = readFileSync("data/system.log", 'utf8');
    return logs.split('\n').slice(-100).join('\n');
};