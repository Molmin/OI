import Express from 'express'
import { readFileSync, writeFileSync } from 'fs'
import Path from 'path'
import { fileURLToPath } from 'url'
import cors from 'cors'
import BodyParser from 'body-parser'
import CookieParser from 'cookie-parser'
import { checkloginByReq } from './src/lib/admin.js'

const app = Express();
app.use(cors());
app.use(BodyParser.json());
app.use(BodyParser.urlencoded({ extended: false }));
app.use(CookieParser());
var System = JSON.parse(readFileSync('./data/system.json'));

var password = parseInt(Math.random() * 1000000);
if (System.password) password = System.password;
else console.log(`Password is: ${password}`);
writeFileSync("password", `${password}`, (err) => { });

app.all('*', (req, res, next) => {
    if (checkloginByReq(req))
        req.logined = true;
    else
        res.cookie('oiblog-cookie', ''),
            req.logined = false;
    res.set('Access-Control-Allow-Origin', '*');
    res.set('Access-Control-Allow-Methods', 'GET');
    res.set('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type');
    if ('OPTIONS' == req.method) return res.send(200);
    next();
});

app.get("/", (req, res) => {
    res.redirect(`/${System.on}`);
});

const __filename = fileURLToPath(import.meta.url);
const __dirname = Path.dirname(__filename);

app.use("/file", Express.static(Path.join(__dirname, 'src/assets')));
app.use(`/${System.on}/pub`, Express.static(Path.join(__dirname, 'src/assets/public')));

import PreviewHandler from './src/preview.js'
import AdminHandler from './src/admin.js'

app.use(`/${System.on}`, PreviewHandler);
app.use(`/admin`, AdminHandler);

app.listen(System.port, () => {
    console.log(`Port :${System.port} is opened`);
});